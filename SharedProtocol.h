#pragma once

#include	"MessageList.h"

#define		NETWORK_MESSAGE_VERSION		1.0f//float

#define		CAR_DRIVING_APP_TARGET_PORT	8888
#define		USER_ID_LENGTH				20



#define		MESSAGE_ID_ASSIGN(TYPE,ID)			TYPE():sBaseNetworkMessage(ID){iSize = sizeof(TYPE);}
#define		RESULT_MESSAGE_ID_ASSIGN(TYPE,ID)	TYPE():sBaseNetworkResultMessage(ID){iSize = sizeof(TYPE);}

#define		RESULT_STRUCT_ASSIGN(TYPE,ID)								\
				struct TYPE:public sBaseNetworkResultMessage			\
				{														\
					TYPE():sBaseNetworkResultMessage(ID) {}				\
					virtual int Size()override { return sizeof(TYPE); }	\
				};


struct sBaseNetworkMessage
{
	int		iSize;
	int		iMessageID;
	sBaseNetworkMessage(int e_iID) :iMessageID(e_iID){}
};

struct sBaseNetworkResultMessage :public sBaseNetworkMessage
{
	int		iResultCode;//basicly 0 for false 1 for true
	sBaseNetworkResultMessage(int e_iID) :sBaseNetworkMessage(e_iID) {}
};

struct sS2CTestMessage_eCDNM_S2C_TEST_MESSAGE :public sBaseNetworkMessage
{
	//int8	i8__1 = 1;
	//int16	i16_2 = 2;
	//int8	i32_3 = 3;
	//int8	i64_4 = 4;
	//wchar_t	wc__5 = 5;
	int8	i8__1;
	int16	i16_2;
	int8	i32_3;
	int8	i64_4;
	wchar_t	wc__5;
	MESSAGE_ID_ASSIGN(sS2CTestMessage_eCDNM_S2C_TEST_MESSAGE, eCDNM_S2C_TEST_MESSAGE);
};

struct sC2STestMessage_eCDNM_C2S_TEST_MESSAGE :public sBaseNetworkMessage
{
	int8	i8__1;
	int16	i16_2;
	int8	i32_3;
	int8	i64_4;
	wchar_t	wc__5;
	MESSAGE_ID_ASSIGN(sC2STestMessage_eCDNM_C2S_TEST_MESSAGE, eCDNM_C2S_TEST_MESSAGE);
};


//=====================================
struct sTleeServerWhoYouAre_eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE :public sBaseNetworkMessage
{
	float	fVersion;
	MESSAGE_ID_ASSIGN(sTleeServerWhoYouAre_eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE,eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE);
};

struct sTleeServerWhoYouAreResult_eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT :public sBaseNetworkMessage
{
	char	strID[USER_ID_LENGTH];
	float	fVersion;
//	MESSAGE_ID_ASSIGN(sTleeServerWhoYouAreResult_eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT, eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT);
};


//RESULT_STRUCT_ASSIGN(sAddUserMessage_eNM_C2S_ADD_USER_RESULT, eNM_C2S_UPDATE_USER_RESULT);