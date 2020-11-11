#include "stdafx.h"
#include "FileTransfer.h"
#include "CarGoAppSharedProtocol.h"

cFileReceiver::cFileReceiver()
{
	m_pFile = nullptr;
}

cFileReceiver::~cFileReceiver()
{
	if (m_pFile)
		NvFClose(m_pFile);
}


bool cFileReceiver::Process_FILE_TRANSFER_START_REQUIRED(sNetworkReceivedPacket* e_pData)
{
	CAR_GO_APP_DO_RETURN_FALSE_IF_SIZE_INCORRECT(sNetwork_eFT_C2S_FILE_TRANSFER_START_REQUIRED, e_pData->iSize);
	sNetwork_eFT_C2S_FILE_TRANSFER_START_REQUIRED*l_pData = (sNetwork_eFT_C2S_FILE_TRANSFER_START_REQUIRED*)e_pData->pData;
	m_iFileSize = l_pData->iFileSize;
	m_strFileFullName = l_pData->strFileFullName;
	m_iNumPacket = l_pData->iNumPacket;
	m_iCurrentPacketIndex = 0;
	m_iReceivedFileSize = 0;
	m_TC.Update();
	return false;
}

bool cFileReceiver::Process_FILE_TRANSFER_DATA_REQUIRED(sNetworkReceivedPacket* e_pData)
{
	CAR_GO_APP_DO_RETURN_FALSE_IF_SIZE_INCORRECT(sNetwork_eFT_C2S_FILE_TRANSFER_DATA_REQUIRED, e_pData->iSize);
	sNetwork_eFT_C2S_FILE_TRANSFER_DATA_REQUIRED*l_pData = (sNetwork_eFT_C2S_FILE_TRANSFER_DATA_REQUIRED*)e_pData->pData;
	l_pData->iPacketIndex;
	l_pData->iDataLen;
	l_pData->iSize;
	l_pData->cData;
	return false;
}

void cFileReceiver::Update(float e_fElpaseTime)
{
}

int cFileReceiver::GetProgress()
{
	if (m_iFileSize != 0)
	{
		return ((float)m_iReceivedFileSize / m_iFileSize)*100;
	}
	return 0;
}

bool cFileReceiver::IsTimeout()
{
	if (m_TC.fElpaseTime > 1.f)
		return true;
	return false;
}
