#pragma once
#ifdef WIN32
#include "../CarDrivingNodes/Code/Src/Core/AllCommonInclude.h"
#endif

#include "SharedProtocolCommonDefine.h"
enum eFileTransfer
{
	//reserved those message for file transfer
	eFT_C2S_FILE_TRANSFER_START_REQUIRED = 56745,
	eFT_C2S_FILE_TRANSFER_DATA_REQUIRED = 56746,
	eFT_C2S_FILE_TRANSFER_DATA_RESULT = 56747,//if data file size not match return 1,if packet not sequence 2.
};

//
LAZY_MESSAGE_HEADER_STAR(eFT_C2S_FILE_TRANSFER_START_REQUIRED)
	char	strFileFullName[60];
	int		iFileSize;
	int		iNumPacket;
LAZY_MESSAGE_HEADER_END(eFT_C2S_FILE_TRANSFER_START_REQUIRED)

#define	TRANSFER_FILE_PACK_SIZE	4096
LAZY_MESSAGE_HEADER_STAR(eFT_C2S_FILE_TRANSFER_DATA_REQUIRED)
	int		iPacketIndex;
	char	cData[TRANSFER_FILE_PACK_SIZE];
	int		iDataLen;
LAZY_MESSAGE_HEADER_END(eFT_C2S_FILE_TRANSFER_DATA_REQUIRED)

class cFileReceiver:public NamedTypedObject
{
	NvFile*				m_pFile;
	std::string			m_strFileFullName;
	int					m_iFileSize;
	int					m_iReceivedFileSize;
	int					m_iNumPacket;
	int					m_iCurrentPacketIndex;
	UT::sTimeAndFPS		m_TC;
	bool				Process_FILE_TRANSFER_START_REQUIRED(sNetworkReceivedPacket* e_pData);
	bool				Process_FILE_TRANSFER_DATA_REQUIRED(sNetworkReceivedPacket* e_pData);
public:
	cFileReceiver();
	virtual ~cFileReceiver();
	void		Update(float e_fElpaseTime);
	int			GetProgress();
	bool		IsTimeout();
};


class cFileSender :public NamedTypedObject
{
	void		SendFileUpdate(float e_fElpaseTime);
public:
	cFileSender();
	virtual ~cFileSender();
	void		SendFile(const char* e_strFileName,const char*e_strTragetMachineFullFileName);
	int			GetProgress();
	bool		IsTimeout();
};