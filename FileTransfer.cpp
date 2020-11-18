#include "stdafx.h"
#include "FileTransfer.h"
#include "CarGoAppSharedProtocol.h"
#define	RECEIVE_PACKET_TIME_OUT	3.f
#ifdef WIN32
#pragma warning( disable : 4996 )
#endif
cFileReceiver::cFileReceiver(cGameNetwork* e_pGameNetwork, int e_iID)
{
	m_iID = e_iID;
	m_pGameNetwork = e_pGameNetwork;
	m_pFile = nullptr;
	m_iFileSize = -1;
	m_iReceivedFileSize = -1;
	m_iNumPacket = -1;
	m_iCurrentPacketIndex = -1;
	m_bReceiveFileStart = false;
	m_TimeOutTC.SetTargetTime(RECEIVE_PACKET_TIME_OUT);
	REG_NET_MESSAGE_FUNCTION(eFT_C2S_FILE_TRANSFER_START_REQUIRED, &cFileReceiver::Process_eFT_C2S_FILE_TRANSFER_START_REQUIRED);
	REG_NET_MESSAGE_FUNCTION(eFT_C2S_FILE_TRANSFER_DATA_REQUIRED, &cFileReceiver::Process_eFT_C2S_FILE_TRANSFER_DATA_REQUIRED);
}

cFileReceiver::~cFileReceiver()
{
	if (m_pFile)
		NvFClose(m_pFile);
}


bool cFileReceiver::Process_eFT_C2S_FILE_TRANSFER_START_REQUIRED(sNetworkReceivedPacket* e_pData)
{
	CAR_GO_APP_DO_RETURN_FALSE_IF_SIZE_INCORRECT(sNetwork_eFT_C2S_FILE_TRANSFER_START_REQUIRED, e_pData->iSize);
	sNetwork_eFT_C2S_FILE_TRANSFER_START_REQUIRED*l_pData = (sNetwork_eFT_C2S_FILE_TRANSFER_START_REQUIRED*)e_pData->pData;
	m_iFileSize = l_pData->iFileSize;
	m_strFileFullName = l_pData->strFileFullName;
	m_iNumPacket = l_pData->iNumPacket;
	m_iCurrentPacketIndex = 0;
	m_iReceivedFileSize = 0;
	if (m_pFile)
	{
		NvFClose(m_pFile);
		m_pFile = nullptr;
	}
	m_pFile = MyFileOpen(m_strFileFullName.c_str(),"w");
	if (!m_pFile)
	{
		m_bReceiveFileStart = false;
		sNetwork_eFT_C2S_FILE_TRANSFER_START_RESULT l_Data;
		l_Data.iResultCode = 0;
		l_Data.iID = m_iID;;
		m_pGameNetwork->SendDataToServer<sNetwork_eFT_C2S_FILE_TRANSFER_START_RESULT>(&l_Data,false);
	}
	else
	{
		m_bReceiveFileStart = true;
	}
	return true;
}

bool cFileReceiver::Process_eFT_C2S_FILE_TRANSFER_DATA_REQUIRED(sNetworkReceivedPacket* e_pData)
{
	if (!m_bReceiveFileStart)
		return false;
	CAR_GO_APP_DO_RETURN_FALSE_IF_SIZE_INCORRECT(sNetwork_eFT_C2S_FILE_TRANSFER_DATA_REQUIRED, e_pData->iSize);
	sNetwork_eFT_C2S_FILE_TRANSFER_DATA_REQUIRED*l_pData = (sNetwork_eFT_C2S_FILE_TRANSFER_DATA_REQUIRED*)e_pData->pData;
	bool l_bFailed = false;
	if (this->m_iCurrentPacketIndex != l_pData->iPacketIndex)
	{
		l_bFailed = true;
	}
	if (m_pFile)
	{
		auto l_uiSize = NvFWrite(l_pData->cData, 1, l_pData->iDataLen, m_pFile);
		if (l_pData->iDataLen != l_uiSize)
		{
			l_bFailed = true;
		}
		else
		{
			m_iReceivedFileSize += l_pData->iDataLen;
		}
	}
	if (l_bFailed)
	{
		m_bReceiveFileStart = false;
		sNetwork_eFT_C2S_FILE_TRANSFER_DATA_RESULT l_Data;
		l_Data.iResultCode = 0;
		l_Data.iID = m_iID;
		m_pGameNetwork->SendDataToServer<sNetwork_eFT_C2S_FILE_TRANSFER_DATA_RESULT>(&l_Data, false);
		NvFClose(m_pFile);
		m_pFile = nullptr;
	}
	else
	{
		this->m_bReceiveFileStart = false;
		m_TimeOutTC.Start();
		++m_iCurrentPacketIndex;
		if (m_iCurrentPacketIndex == m_iNumPacket &&
			m_iReceivedFileSize == m_iFileSize)
		{//finish
			NvFClose(m_pFile);
			m_pFile = nullptr;
		}
		
	}
	return false;
}

void cFileReceiver::Update(float e_fElpaseTime)
{
	if (this->m_bReceiveFileStart)
	{
		m_TimeOutTC.Update(e_fElpaseTime);
	}
}

int cFileReceiver::GetProgress()
{
	if (m_iFileSize != 0)
	{
		return (int)(((float)m_iReceivedFileSize / m_iFileSize)*100);
	}
	return 0;
}

bool cFileReceiver::IsTimeout()
{
	if (m_TimeOutTC.bTragetTimrReached)
		return true;
	return false;
}

cFileSender::cFileSender()
{
	m_pFile = nullptr;
	m_fProgress = 0.f;
	m_TimeOutTC.SetTargetTime(RECEIVE_PACKET_TIME_OUT);
	m_iRestDataToSendFileSize = 0;
	m_bSendToClient = false;
}

cFileSender::~cFileSender()
{
}

bool cFileSender::OpenFileCollectData(const char* e_strFileName, const char* e_strTragetMachineFullFileName)
{
	m_fProgress = 0.f;
	m_pFile = MyFileOpen(e_strFileName, "r");
	if (m_pFile)
	{
		m_strSelectFile = UT::GetFileNameWithoutFullPath(e_strFileName);
		m_strTagetMachineFileFullName = e_strTragetMachineFullFileName;
		m_iFileSize = (int)GetFileSize(m_pFile);
		m_iRestDataToSendFileSize = m_iFileSize;
		m_iNumPacket = m_iFileSize / TRANSFER_FILE_PACK_SIZE;
		if (m_iFileSize % TRANSFER_FILE_PACK_SIZE == 0)
			m_iNumPacket += 1;
		m_iCurrentPacketIndex = 0;
		m_TimeOutTC.Start();
		return true;
	}
	return false;
}

void cFileSender::SendFileThreadUpdate(float e_fElpaseTime)
{
	bool l_bSentOk = false;
	if (m_iCurrentPacketIndex == 0)
	{
		sNetwork_eFT_C2S_FILE_TRANSFER_START_REQUIRED l_Data;
		l_Data.iFileSize = m_iFileSize;
		l_Data.iNumPacket = m_iNumPacket;
		sprintf(l_Data.strFileFullName,"%s",m_strTagetMachineFileFullName.c_str());
		this->m_pGameNetwork->SendDataToServer<sNetwork_eFT_C2S_FILE_TRANSFER_START_REQUIRED>(&l_Data);
	}
	else
	{
		sNetwork_eFT_C2S_FILE_TRANSFER_DATA_REQUIRED l_Data;
		l_Data.iPacketIndex = m_iCurrentPacketIndex;
		if(m_iRestDataToSendFileSize >= TRANSFER_FILE_PACK_SIZE)
			l_Data.iDataLen = TRANSFER_FILE_PACK_SIZE;
		else
			l_Data.iDataLen = m_iRestDataToSendFileSize;
		bool l_bFileCorrect = false;
		if (NvFSeek(m_pFile, m_iCurrentPacketIndex * TRANSFER_FILE_PACK_SIZE, SEEK_SET) == 0)
		{
			if (NvFRead(l_Data.cData, 1, l_Data.iDataLen, m_pFile) == l_Data.iDataLen)
			{
				l_bSentOk = SendData<sNetwork_eFT_C2S_FILE_TRANSFER_DATA_REQUIRED>(&l_Data,false, m_bSendToClient);
				if (l_bSentOk)
				{
					m_iRestDataToSendFileSize -= l_Data.iDataLen;
					if (m_iRestDataToSendFileSize == 0)
					{
						FMLog::Log("send file finish",true);
					}
				}
				l_bFileCorrect = true;
			}			
		}
		if (!l_bFileCorrect)
		{
			l_Data.iDataLen = -1;
		}
	}
	++m_iCurrentPacketIndex;
	if (m_iCurrentPacketIndex >= m_iNumPacket)
	{
		NvFClose(this->m_pFile);
		m_pFile = nullptr;
		this->m_bLeaveThread = true;
	}
	if (!l_bSentOk)
	{
		m_TimeOutTC.Update(e_fElpaseTime);
	}
	else
	{
		m_TimeOutTC.Start();
	}
}


bool cFileSender::SendFile(const char* e_strFileName, const char* e_strTragetMachineFullFileName, cGameNetwork* e_pGameNetwork, bool e_bToClient)
{
	m_pGameNetwork = e_pGameNetwork;
	if (IsThreadWorking())
		return false;
	if (OpenFileCollectData(e_strFileName, e_strTragetMachineFullFileName))
	{
		m_bSendToClient = e_bToClient;
		this->ThreadDetach(std::bind(&cFileSender::SendFileThreadUpdate, this, std::placeholders::_1), "cFileSender::SendFileThreadUpdate");
		return true;
	}
	return false;
}

int cFileSender::GetProgress()
{
	if (m_iNumPacket == 0)
		return -1;
	return (int)(((float)m_iCurrentPacketIndex / m_iNumPacket)*100);
}

bool cFileSender::IsTimeout()
{
	return m_TimeOutTC.bTragetTimrReached;
}

std::string cFileSender::GetInfo()
{
	int l_iProgress = this->GetProgress();
	bool l_bTimeout = this->IsTimeout();
	std::string l_str = "Send File";
	l_str += this->m_strSelectFile;
	l_str += " to target machine ";
	l_str += this->m_strTagetMachineFileFullName;
	l_str += ",";
	if (l_iProgress == 100)
	{
		l_str += "upload success,please click screen to exit.";
	}
	else
	if (l_bTimeout)
	{
		l_str += "upload time out FAILED!,please click screen to exit.";
	}
	else
	if (!m_pFile)
	{
		l_str += "open file failed!";
	}
	else
	{
		if (this->m_bSendToClient)
		{
			l_str += "Progress:";
			l_str += ValueToString(GetProgress());
		}
	}
	return l_str;
}

bool cFileSender::IsFinish()
{
	if (GetProgress() >= 100 || IsTimeout())
	{
		return true;
	}
	return false;
}

void cFileSender::Render(Vector2 e_vRenderPos)
{
	//GLRender::RenderFilledRectangle(Vector2(0, 0), cGameApp::m_spOpenGLRender->m_vGameResolution.x, cGameApp::m_spOpenGLRender->m_vGameResolution.y, Vector4(0.5f, 0.5f, 0.5f, 0.8f), 0);
	//auto l_str = GetInfo();
	//cGameApp::RenderFont(Vector2(200, 600), ValueToStringW(l_str).c_str());
}