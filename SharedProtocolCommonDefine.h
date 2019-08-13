#pragma once


#define		MESSAGE_ID_ASSIGN(TYPE,ID)TYPE():sBaseNetworkMessage(){memset(this,0,sizeof(TYPE));iMessage = ID;iSize = (int)sizeof(TYPE);}};
#define		RESULT_MESSAGE_ID_ASSIGN(TYPE,ID)TYPE():sBaseNetworkResultMessage(){memset(this,0,sizeof(TYPE));iMessage = ID;iSize = (int)sizeof(TYPE);}};


#define		LAZY_MESSAGE_HEADER_STAR(ID)						struct sNetwork_##ID:public sBaseNetworkMessage{
#define		LAZY_MESSAGE_HEADER_END(ID)							MESSAGE_ID_ASSIGN(sNetwork_##ID,ID)

#define		LAZY_RESULT_MESSAGE_HEADER_STAR(ID)					struct sNetwork_##ID:public sBaseNetworkResultMessage{
#define		LAZY_RESULT_MESSAGE_HEADER_END(ID)					RESULT_MESSAGE_ID_ASSIGN(sNetwork_##ID,ID)

#define		CAR_GO_APP_LAZY_SIZE_LOG(TYPE,YOUR_SIZE)						{auto l_strInfo = UT::ComposeMsgByFormat("%s,ExpectedSize:%d,RealSize:%d", #TYPE, sizeof(TYPE), YOUR_SIZE);FMLog::LogWithFlag(l_strInfo, CAR_GOAPP_NETWORK, true);}
#define		CAR_GO_APP_DO_RETURN_FALSE_IF_SIZE_INCORRECT(TYPE,YOUR_SIZE)	if(sizeof(TYPE)!=YOUR_SIZE){ CAR_GO_APP_LAZY_SIZE_LOG(TYPE,YOUR_SIZE); return false;}


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