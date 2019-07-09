#pragma once

#include	"MessageList.h"

//network 
#define		NETWORK_MESSAGE_VERSION			1.0f//float
#define		CAR_DRIVING_APP_TARGET_PORT		8063

//header
#define		PACKET_SIZE_LIMIT				256
#define		MAGIC_ID_COUNT					4
#define		MAGIC_ID_SIZE					sizeof(uint8)*MAGIC_ID_COUNT
#define		PACKET_SIZE_SIZE				sizeof(uint16)
#define		CHECK_SUM_SIZE					sizeof(uint16)
#define		HEADER_SIZE						(MAGIC_ID_SIZE+PACKET_SIZE_SIZE+CHECK_SUM_SIZE)

#define		MAGIC_ID_INDEX					0
#define		PACKET_SIZE_INDEX				MAGIC_ID_SIZE
#define		CHECK_SUM_INDEX					(PACKET_SIZE_INDEX+PACKET_SIZE_SIZE)

const static uint8	g_HeaderCode[MAGIC_ID_COUNT] = { 0x80,0x63,0x68,0x55 };

#define		ASSIGN_MAGIC_ID(Data)			memcpy(Data, g_HeaderCode,MAGIC_ID_SIZE);

//data
//#define		USER_ID_LENGTH					20

//struct sPacketBase
//{
//	uint8	i8MagicID[HEADER_SIZE];
//	uint16	i16PacketSize;
//	uint16	i16CheckSum;
//};

#define	LAZY_HEADER_STAR(TYPE)								struct TYPE{int8 i8MagicID[4]; int16	i16PacketSize; uint16	i16CheckSum; int16 i16Message;
#define	LAZY_HEADER_END(TYPE,ID)							TYPE(){ memset(this,0,sizeof(TYPE));ASSIGN_MAGIC_ID(i8MagicID);i16PacketSize = sizeof(TYPE); i16CheckSum = 0;i16Message = ID;} };


#define	LAZY_SIZE_LOG(TYPE,YOUR_SIZE)						{auto l_strInfo = UT::ComposeMsgByFormat("%s,ExpectedSize:%d,RealSize:%d", #TYPE, sizeof(TYPE), YOUR_SIZE);FMLog::LogWithFlag(l_strInfo, CAR_NET_WORK_LOG_FLAG, true);}
#define	DO_RETURN_FALSE_IF_SIZE_INCORRECT(TYPE,YOUR_SIZE)	if(sizeof(TYPE)!=YOUR_SIZE){ LAZY_SIZE_LOG(TYPE,YOUR_SIZE); return false;}




#ifdef WIN32

inline uint8_t GetChecksum(uint16_t dp[], uint16_t Size, uint16_t *Checksum)
{
	uint16_t cks = 0;	uint16_t i;	if (Checksum == NULL)	return 0;
	for (i = 0; i < (Size >> 1); i++){	cks += dp[i];}
	if (Size & 0x0001){	cks += (uint16_t)((uint8_t)(dp[i]));}
	*Checksum = (cks ^ 0xffff) + 1;
	return 1;
}
inline	bool	IsCheckSumOk(uint8*e_pData, int e_iSize){	uint16	l_uint16CheckSum = 0;	GetChecksum((uint16*)e_pData, e_iSize, &l_uint16CheckSum);	return l_uint16CheckSum==0?true:false; }
inline	int		FindHeaderIndex(uint8*e_pData,int e_iSize){	for (int i = 0; i < e_iSize - 4; ++i){	if (e_pData[i  ] == g_HeaderCode[0] &&e_pData[i+1] == g_HeaderCode[1] &&e_pData[i+2] == g_HeaderCode[2] &&	e_pData[i+3] == g_HeaderCode[3]){return i;}	}	return -1;}
#endif
//struct sBaseNetworkMessage
//{
//	int		iSize;
//	int		iMessageID;
//	sBaseNetworkMessage(int e_iID) :iMessageID(e_iID){}
//};
//
//struct sBaseNetworkResultMessage
//{
//	int		iResultCode;//basicly 0 for false 1 for true
//	sBaseNetworkResultMessage(int e_iID) :sBaseNetworkMessage(e_iID) {}
//};
#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */
LAZY_HEADER_STAR(sS2CTestMessage_eCDNM_S2C_TEST_MESSAGE)
	int8	i8__1;
	int16	i16_2;
	int32	i32_3;
	int64	i64_4;
LAZY_HEADER_END(sS2CTestMessage_eCDNM_S2C_TEST_MESSAGE, eCDNM_S2C_TEST_MESSAGE)
#pragma pack(pop)   /* restore original alignment from stack */



#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */
LAZY_HEADER_STAR(sS2CTestMessage_eCDNM_C2S_TEST_MESSAGE)
	int8	i8__1;
	int16	i16_2;
	int8	i32_3;
	int8	i64_4;
LAZY_HEADER_END(sS2CTestMessage_eCDNM_C2S_TEST_MESSAGE, eCDNM_C2S_TEST_MESSAGE)
#pragma pack(pop)   /* restore original alignment from stack */



//=====================================
#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */
LAZY_HEADER_STAR(sTleeServerWhoYouAre_eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE)
	float	fVersion;
LAZY_HEADER_END(sTleeServerWhoYouAre_eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE, eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE)
#pragma pack(pop)   /* restore original alignment from stack */



#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */
LAZY_HEADER_STAR(sTleeServerWhoYouAreResult_eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT)
	//char	strID[USER_ID_LENGTH];
	int32	i32HWID;
	float	fVersion;
LAZY_HEADER_END(sTleeServerWhoYouAreResult_eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT, eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT)
#pragma pack(pop)   /* restore original alignment from stack */



LAZY_HEADER_STAR(sRFIDData_eCDNM_C2S_RFID_SINGNAL)
	int16	i16ID;
LAZY_HEADER_END(sRFIDData_eCDNM_C2S_RFID_SINGNAL, eCDNM_C2S_RFID_SINGNAL)



LAZY_HEADER_STAR(sCarGo_eCDNM_S2C_CAR_GO_TO_DESTINATION_1)
	int16	i16ID;
LAZY_HEADER_END(sCarGo_eCDNM_S2C_CAR_GO_TO_DESTINATION_1, eCDNM_S2C_CAR_GO_TO_DESTINATION_1)

