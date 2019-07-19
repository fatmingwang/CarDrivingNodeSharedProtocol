#pragma once

#include	"MessageList.h"

//network 
//2:	sTleeServerWhoYouAre_eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE	add i16ChargePointTagID
//		sRFIDData_eCDNM_C2S_CAR_STATUS							add i1Status
#define		NETWORK_MESSAGE_VERSION			2
#define		CAR_DRIVING_APP_TARGET_PORT		8063

//header
#define		PACKET_SIZE_LIMIT				256
#define		MAGIC_ID_COUNT					4
#define		MAGIC_ID_SIZE					(sizeof(uint8)*MAGIC_ID_COUNT)
#define		PACKET_SIZE_SIZE				sizeof(uint16)
#define		CHECK_SUM_SIZE					sizeof(uint16)
#define		HEADER_SIZE						(MAGIC_ID_SIZE+PACKET_SIZE_SIZE+CHECK_SUM_SIZE)

#define		MAGIC_ID_INDEX					0
#define		PACKET_SIZE_INDEX				MAGIC_ID_SIZE
#define		CHECK_SUM_INDEX					(PACKET_SIZE_INDEX+PACKET_SIZE_SIZE)

//const static uint8	g_HeaderCode[MAGIC_ID_COUNT] = { 0x80,0x63,0x68,0x55 };
const static uint8	g_HeaderCode[MAGIC_ID_COUNT] = { 0x55,0x68,0x63,0x80 };

#define		ASSIGN_MAGIC_ID(Data)			memcpy(Data, g_HeaderCode,MAGIC_ID_SIZE);

//data
#define		CHARGE_POINT_DATA_LENGTH		20
#define		CAR_A_TO_B_DATA_LENGTH			80
#define		RFID_CARD_COUNT					40


#define	LAZY_HEADER_STAR(TYPE)								struct TYPE{int8 i8MagicID[MAGIC_ID_COUNT]; int16	i16PacketSize; uint16	i16CheckSum; int16 i16Message;int16	i16HWID;
#define	LAZY_HEADER_END(TYPE,ID)							TYPE(){ memset(this,0,sizeof(TYPE));ASSIGN_MAGIC_ID(i8MagicID);i16PacketSize = sizeof(TYPE)-HEADER_SIZE; i16CheckSum = 0;i16Message = ID;i16HWID = -1;} };


#define	LAZY_SIZE_LOG(TYPE,YOUR_SIZE)						{auto l_strInfo = UT::ComposeMsgByFormat("%s,ExpectedSize:%d,RealSize:%d", #TYPE, sizeof(TYPE), YOUR_SIZE);FMLog::LogWithFlag(l_strInfo, CAR_NET_WORK_LOG_FLAG, true);}
#define	DO_RETURN_FALSE_IF_SIZE_INCORRECT(TYPE,YOUR_SIZE)	if(sizeof(TYPE)!=YOUR_SIZE){ LAZY_SIZE_LOG(TYPE,YOUR_SIZE); return false;}


LAZY_HEADER_STAR(sPacketBase)
LAZY_HEADER_END(sPacketBase, eCDNM_MAX)




#ifdef WIN32

inline uint8_t GetChecksum(uint16_t dp[], uint16_t Size, uint16_t *Checksum)
{
#ifdef DEBUG
	uint8 l_Temp[999];
	memset(l_Temp, 0, 999);
	memcpy(l_Temp, dp, Size);
#endif
	uint16_t cks = 0;	uint16_t i;	if (Checksum == NULL)	return 0;
	for (i = 0; i < (Size >> 1); i++){cks += dp[i];}
	if (Size & 0x0001){cks += (uint16_t)((uint8_t)(dp[i]));}
	*Checksum = (cks ^ 0xffff) + 1;
	return 1;
}
inline	bool	IsCheckSumOk(uint8*e_pData, int e_iSize)
{
	uint16	l_uint16CheckSum = 0;	
	GetChecksum((uint16*)e_pData, e_iSize, &l_uint16CheckSum);	
	return l_uint16CheckSum==0?true:false; 
}
inline	int		FindHeaderIndex(uint8*e_pData,int e_iSize)
{
	for (int i = 0; i < e_iSize - 4; ++i)
	{
		  //if (e_pData[i] == g_HeaderCode[1] &&e_pData[i+1] == g_HeaderCode[0] && e_pData[i+2]== g_HeaderCode[3] &&  e_pData[i+3] == g_HeaderCode[2])
		if (e_pData[i] == g_HeaderCode[0] &&e_pData[i+1] == g_HeaderCode[1] &&e_pData[i+2] == g_HeaderCode[2] &&	e_pData[i+3] == g_HeaderCode[3])
		{
			return i;
		}
	}	return -1;
}
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
#pragma pack(push)
#pragma pack(1) 
LAZY_HEADER_STAR(sS2CTestMessage_eCDNM_S2C_TEST_MESSAGE)
	int8	i8__1;
	int16	i16_2;
	int32	i32_3;
	int64	i64_4;
LAZY_HEADER_END(sS2CTestMessage_eCDNM_S2C_TEST_MESSAGE, eCDNM_S2C_TEST_MESSAGE)
#pragma pack(pop)   /* restore original alignment from stack */

#pragma pack(push)
#pragma pack(1) 
LAZY_HEADER_STAR(sS2CTestMessage_eCDNM_C2S_TEST_MESSAGE)
	int8	i8__1;
	int16	i16_2;
	int8	i32_3;
	int8	i64_4;
LAZY_HEADER_END(sS2CTestMessage_eCDNM_C2S_TEST_MESSAGE, eCDNM_C2S_TEST_MESSAGE)
#pragma pack(pop)   /* restore original alignment from stack */



//=====================================
#pragma pack(push)
#pragma pack(1)
LAZY_HEADER_STAR(sTleeServerWhoYouAre_eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE)
	int16	i16Version;
	int16	i16ChargePointTagID[CHARGE_POINT_DATA_LENGTH];
	//int16	i16TagIDArrayCount;//or do if Tag ID is -1 end?,2
	//int32	i32RFID[RFID_CARD_COUNT];//160
LAZY_HEADER_END(sTleeServerWhoYouAre_eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE, eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE)
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
LAZY_HEADER_STAR(sTleeServerWhoYouAreResult_eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT)
	int16	i16Version;
	//int16	i16NumRFID;
	//int16	i16RFIDCheckSum;
LAZY_HEADER_END(sTleeServerWhoYouAreResult_eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT, eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT)
#pragma pack(pop)
//=====================================
#pragma pack(push)
#pragma pack(1)
LAZY_HEADER_STAR(sRFIDData_eCDNM_C2S_CAR_STATUS)
	int16	i16TagID;
	int16	i1Status;
LAZY_HEADER_END(sRFIDData_eCDNM_C2S_CAR_STATUS, eCDNM_C2S_CAR_STATUS)
//=====================================
#pragma pack(1)
//A TO B start
LAZY_HEADER_STAR(sCar_A_TO_B_eCDNM_S2C_CAR_GO_TO_DESTINATION_ID_1)
	int16	i16TagIDArrayCount;//or do if Tag ID is -1 end?,2
	int16	i16TagIDArray[CAR_A_TO_B_DATA_LENGTH];//160
LAZY_HEADER_END(sCar_A_TO_B_eCDNM_S2C_CAR_GO_TO_DESTINATION_ID_1, eCDNM_S2C_CAR_GO_TO_DESTINATION_ID_1)
#pragma pack(pop)
#pragma pack(push)
#pragma pack(1)
LAZY_HEADER_STAR(sCar_A_TO_B_eCDNM_C2S_CAR_GO_TO_DESTINATION_ID_1_RESULT)
	int16	iCount;
LAZY_HEADER_END(sCar_A_TO_B_eCDNM_C2S_CAR_GO_TO_DESTINATION_ID_1_RESULT, eCDNM_C2S_CAR_GO_TO_DESTINATION_ID_1_RESULT)
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
LAZY_HEADER_STAR(sCar_A_TO_B_eCDNM_S2C_CAR_GO_TO_DESTINATION_SPEED_2)
	int16	i16SpeedArrayCount;//or do if Tag ID is -1 end?
	int16	i16SpeedArray[CAR_A_TO_B_DATA_LENGTH];
LAZY_HEADER_END(sCar_A_TO_B_eCDNM_S2C_CAR_GO_TO_DESTINATION_SPEED_2, eCDNM_S2C_CAR_GO_TO_DESTINATION_SPEED_2)
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
LAZY_HEADER_STAR(sCar_A_TO_B_eCDNM_C2S_CAR_GO_TO_DESTINATION_SPEED_2_RESULT)
	int16	i16Count;
LAZY_HEADER_END(sCar_A_TO_B_eCDNM_C2S_CAR_GO_TO_DESTINATION_SPEED_2_RESULT, eCDNM_C2S_CAR_GO_TO_DESTINATION_SPEED_2_RESULT)
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
LAZY_HEADER_STAR(sCar_A_TO_B_eCDNM_S2C_CAR_GO_TO_DESTINATION_ANGLE_3)
	int16	i16AngleArrayCount;
	int8	i8AngleTypeArray[CAR_A_TO_B_DATA_LENGTH];
LAZY_HEADER_END(sCar_A_TO_B_eCDNM_S2C_CAR_GO_TO_DESTINATION_ANGLE_3, eCDNM_S2C_CAR_GO_TO_DESTINATION_ANGLE_3)
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
LAZY_HEADER_STAR(sCar_A_TO_B_eCDNM_C2S_CAR_GO_TO_DESTINATION_ANGLE_3_RESULT)
	int16	iCount;
LAZY_HEADER_END(sCar_A_TO_B_eCDNM_C2S_CAR_GO_TO_DESTINATION_ANGLE_3_RESULT, eCDNM_C2S_CAR_GO_TO_DESTINATION_ANGLE_3_RESULT)
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
LAZY_HEADER_STAR(sCar_A_TO_B_eCDNM_S2C_CAR_GO_TO_DESTINATION_DISTANCE_4)
	int16	i16DistanceArrayCount;
	int16	i16DistanceArray[CAR_A_TO_B_DATA_LENGTH];
LAZY_HEADER_END(sCar_A_TO_B_eCDNM_S2C_CAR_GO_TO_DESTINATION_DISTANCE_4, eCDNM_S2C_CAR_GO_TO_DESTINATION_DISTANCE_4)
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
LAZY_HEADER_STAR(sCar_A_TO_B_eCDNM_C2S_CAR_GO_TO_DESTINATION_DISTANCE_4_RESULT)
	int16	i16Count;
LAZY_HEADER_END(sCar_A_TO_B_eCDNM_C2S_CAR_GO_TO_DESTINATION_DISTANCE_4_RESULT, eCDNM_C2S_CAR_GO_TO_DESTINATION_DISTANCE_4_RESULT)
#pragma pack(pop)


#pragma pack(push)
#pragma pack(1)
LAZY_HEADER_STAR(sRFIDInfo_eCDNM_S2C_RFID_INFO)
	int16	i16TotalSendingTime;
	int16	i16CurrentSendingIndex;
	int16	i16RFIDCardCount;
	int32	i32RFID[RFID_CARD_COUNT];
LAZY_HEADER_END(sRFIDInfo_eCDNM_S2C_RFID_INFO, eCDNM_S2C_RFID_INFO)
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
LAZY_HEADER_STAR(sRFIDInfoResult_eCDNM_S2C_RFID_INFO_RESULT)
	int16	i16CurrentSendingIndex;
LAZY_HEADER_END(sRFIDInfoResult_eCDNM_S2C_RFID_INFO_RESULT, eCDNM_S2C_RFID_INFO_RESULT)
#pragma pack(pop)




//A TO B end
//=====================================