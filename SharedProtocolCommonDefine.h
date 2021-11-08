#pragma once


#define		MESSAGE_ID_ASSIGN(TYPE,ID)TYPE():sBaseNetworkMessage(){memset(this,0,sizeof(TYPE));iMessage = ID;iSize = (int)sizeof(TYPE);}};
#define		RESULT_MESSAGE_ID_ASSIGN(TYPE,ID)TYPE():sBaseNetworkResultMessage(){memset(this,0,sizeof(TYPE));iMessage = ID;iSize = (int)sizeof(TYPE);}};


#define		LAZY_MESSAGE_HEADER_STAR(ID)						struct sNetwork_##ID:public sBaseNetworkMessage{
#define		LAZY_MESSAGE_HEADER_END(ID)							MESSAGE_ID_ASSIGN(sNetwork_##ID,ID)

#define		LAZY_RESULT_MESSAGE_HEADER_STAR(ID)					struct sNetwork_##ID:public sBaseNetworkResultMessage{
#define		LAZY_RESULT_MESSAGE_HEADER_END(ID)					RESULT_MESSAGE_ID_ASSIGN(sNetwork_##ID,ID)

#define		CAR_GO_APP_LAZY_SIZE_LOG(TYPE,YOUR_SIZE)						{auto l_strInfo = UT::ComposeMsgByFormat("Error:%s,ExpectedSize:%d,RealSize:%d", #TYPE, sizeof(TYPE), YOUR_SIZE);FMLog::Log(l_strInfo.c_str(), false);}
#define		CAR_GO_APP_DO_RETURN_FALSE_IF_SIZE_INCORRECT(TYPE,YOUR_SIZE)	if(sizeof(TYPE)!=YOUR_SIZE){ CAR_GO_APP_LAZY_SIZE_LOG(TYPE,YOUR_SIZE); return false;}


#define		LAZY_GET_NETWORK_DATA_AND_COMPARE_SIZE(TYPE)																	\
						CAR_GO_APP_DO_RETURN_FALSE_IF_SIZE_INCORRECT(sNetwork_##TYPE, e_pNetworkReceivedPacket->iSize)		\
						sNetwork_##TYPE* l_pData = (sNetwork_##TYPE*)e_pNetworkReceivedPacket->pData;

#define		UE4_LAZY_GET_DATA(TYPE)																							 \
										if (sizeof(sNetwork_##TYPE) != e_pUNetWorkMessageDelegateData->m_iSize)							 \
										{																					 \
											UE_LOG(LogTemp, Error, TEXT(#TYPE),TEXT(" size is not correct!"));				 \
											return;																	 \
										}																					 \
										sNetwork_##TYPE*l_pData = (sNetwork_##TYPE*)e_pUNetWorkMessageDelegateData->m_pData;

//for map file name
#define		MAP_NAME_ARRAY_LENGTH			40
//Oct/25/2021
#define		HC_PRODUCT_ID_LENGTH			80
//tcpip 1 packet default maximum size is 65k
struct sBaseNetworkMessage
{
	int		iSize;
	int		iMessage;
	//sBaseNetworkMessage(int e_iID,int e_iSize) :iMessage(e_iID) { iSize= e_iSize;	}
	sBaseNetworkMessage() { iSize = 0; iMessage = 0; }
};


struct sBaseNetworkResultMessage :public sBaseNetworkMessage
{
	int		iResultCode;//basicly 0 for false 1 for true
	sBaseNetworkResultMessage() {}
};


struct sUniqueIDStruct
{
	unsigned int	uiID;
	sUniqueIDStruct()
	{
		uiID = 0;
	}
	void	AssignUniqueID()
	{
		static unsigned int l_siID = 0;
		uiID = l_siID;
		++l_siID;
	}
};

struct sBaseNetworkMessageWithUniqueID :public sBaseNetworkMessage,public sUniqueIDStruct
{
};

struct sBaseNetworkResultMessageWithUniqueID :public sBaseNetworkResultMessage, public sUniqueIDStruct
{
};



#define		UNIQUE_MESSAGE_ID_ASSIGN(TYPE,ID)TYPE(){memset(this,0,sizeof(TYPE));iMessage = ID;iSize = (int)sizeof(TYPE);AssignUniqueID();}};



#define		LAZY_MESSAGE_WITH_UNIQUE_HEADER_STAR(ID)			struct sNetwork_##ID:public sBaseNetworkMessageWithUniqueID{
#define		LAZY_MESSAGE_WITH_UNIQUE_HEADER_END(ID)				UNIQUE_MESSAGE_ID_ASSIGN(sNetwork_##ID, ID)



#define		LAZY_RESULT_WITH_UNIQUE_MESSAGE_HEADER_STAR(ID)					struct sNetwork_##ID:public sBaseNetworkResultMessageWithUniqueID{
#define		LAZY_RESULT_WITH_UNIQUE_MESSAGE_HEADER_END(ID)					UNIQUE_MESSAGE_ID_ASSIGN(sNetwork_##ID, ID)