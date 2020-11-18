#pragma once
#if defined(WIN32) || defined(ANDROID)
#include "../CarDrivingNodes/Code/Src/Core/AllCommonInclude.h"
#endif

#include "SharedProtocolCommonDefine.h"
#include <functional>
enum eFileTransfer
{
	//reserved those message for file transfer
	eFT_C2S_FILE_TRANSFER_START_REQUIRED = 56745,	//start to send file
	eFT_C2S_FILE_TRANSFER_START_RESULT,				//create file result  for ok else for failed
	eFT_C2S_FILE_TRANSFER_DATA_REQUIRED,			//send packet.
	eFT_C2S_FILE_TRANSFER_DATA_RESULT				//if data file size not match return 1,if packet not sequence 2.0 for ok.
};

//
LAZY_MESSAGE_HEADER_STAR(eFT_C2S_FILE_TRANSFER_START_REQUIRED)
	char	strFileFullName[60];
	int		iFileSize;
	int		iNumPacket;
LAZY_MESSAGE_HEADER_END(eFT_C2S_FILE_TRANSFER_START_REQUIRED)

LAZY_RESULT_MESSAGE_HEADER_STAR(eFT_C2S_FILE_TRANSFER_START_RESULT)
	int iID;
//iResultCode 0 for create file failed 1 for success
LAZY_RESULT_MESSAGE_HEADER_END(eFT_C2S_FILE_TRANSFER_START_RESULT)


#define	TRANSFER_FILE_PACK_SIZE	4096
LAZY_MESSAGE_HEADER_STAR(eFT_C2S_FILE_TRANSFER_DATA_REQUIRED)
	int		iPacketIndex;
	char	cData[TRANSFER_FILE_PACK_SIZE];
	int		iDataLen;
LAZY_MESSAGE_HEADER_END(eFT_C2S_FILE_TRANSFER_DATA_REQUIRED)


LAZY_RESULT_MESSAGE_HEADER_STAR(eFT_C2S_FILE_TRANSFER_DATA_RESULT)
//iResultCode 0 for ok,1 for packet index not correct,2 for size not match
	int iID;
LAZY_RESULT_MESSAGE_HEADER_END(eFT_C2S_FILE_TRANSFER_DATA_RESULT)


class cFileReceiver:public NamedTypedObject, public cMessageSender
{
	NvFile*				m_pFile;
	std::string			m_strFileFullName;
	int					m_iFileSize;
	int					m_iReceivedFileSize;
	int					m_iNumPacket;
	int					m_iCurrentPacketIndex;
	UT::sTimeCounter	m_TimeOutTC;
	bool				m_bReceiveFileStart;
	//
	cGameNetwork*		m_pGameNetwork;
	int					m_iID;//
	//
	bool				Process_eFT_C2S_FILE_TRANSFER_START_REQUIRED(sNetworkReceivedPacket* e_pData);
	bool				Process_eFT_C2S_FILE_TRANSFER_DATA_REQUIRED(sNetworkReceivedPacket* e_pData);
	//
public:
	cFileReceiver(cGameNetwork* e_pGameNetwork,int e_iID);
	virtual ~cFileReceiver();
	void		Update(float e_fElpaseTime);
	int			GetProgress();
	bool		IsTimeout();
	bool		IsReceiveFileStart() { return m_bReceiveFileStart; }
};

class cFileSender :public NamedTypedObject,public cCPP11Thread,public cMessageSender
{
	template<class TYPE>bool		SendData(TYPE* e_Data, bool e_bDoMultothread, bool e_bSendToClient);

	bool				OpenFileCollectData(const char* e_strFileName, const char* e_strTragetMachineFullFileName);
	void				SendFileThreadUpdate(float e_fElpaseTime);
	NvFile*				m_pFile;
	std::string			m_strTagetMachineFileFullName;
	std::string			m_strSelectFile;
	float				m_fProgress;
	int					m_iFileSize;
	int					m_iNumPacket;
	int					m_iCurrentPacketIndex;
	int					m_iRestDataToSendFileSize;
	bool				m_bSendToClient;
	//for internet.
	UT::sTimeCounter	m_TimeOutTC;
	cGameNetwork*		m_pGameNetwork;
	bool				Process_eFT_C2S_FILE_TRANSFER_START_RESULT(sNetworkReceivedPacket* e_pData);
	bool				Process_eFT_C2S_FILE_TRANSFER_DATA_RESULT(sNetworkReceivedPacket* e_pData);
public:
	cFileSender();
	virtual ~cFileSender();
	bool		SendFile(const char* e_strFileName,const char*e_strTragetMachineFullFileName,cGameNetwork*e_pGameNetwork,bool e_bToClient);
	int			GetProgress();
	bool		IsTimeout();
	std::string GetInfo();
	bool		IsFinish();
	void		Render(Vector2 e_vRenderPos);
};

template<class TYPE>bool				cFileSender::SendData(TYPE* e_Data, bool e_bDoMultothread, bool e_bSendToClient)
{
	if (e_bSendToClient)
	{
		return m_pGameNetwork->SendDataToAllClient<TYPE>(e_Data, e_bDoMultothread);
	}
	return m_pGameNetwork->SendDataToServer<TYPE>(e_Data, e_bDoMultothread);
}