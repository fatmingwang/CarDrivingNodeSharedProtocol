#pragma once

//#define		MAGIC_ID_COUNT					4
//const static uint8	g_HeaderCode[MAGIC_ID_COUNT] = { 0x80,0x63,0x68,0x55 };
//#define		ASSIGN_MAGIC_ID(Data)			memcpy(Data, g_HeaderCode,MAGIC_ID_SIZE);
#include	"SharedProtocolCommonDefine.h"
#include	"CarDrivingMessageList.h"
#include	"CarDrivingResultMessage.h"

#define		CAR_DRIVING_SERVER_NETWORK_MESSAGE_VERSION			1
#define		CAR_DRIVING_SERVER_NETWORK_TARGET_PORT				2978

//data
#define		CAR_A_TO_B_DATA_LENGTH			80
#define		ROUTE_KEY_POINT_DATA_LENGTH		20

#ifndef		MAP_NAME_ARRAY_LENGTH
#define		MAP_NAME_ARRAY_LENGTH			40
#endif

enum eCarDrivingTurnAngleList
{
	eCDTAL_0 = 0,
	eCDTAL_LEFT90,
	eCDTAL_LEFT180,
	eCDTAL_RIGHT90,
	eCDTAL_RIGHT180,
	eCDTAL_MAX
};

#define		CAR_WHEEL_COUNT		2
#define		NODE_ANGLE_COUNT	eCarDrivingTurnAngleList::eCDTAL_MAX
#define		NODE_ANGLE_0		eCDTAL_0
#define		NODE_ANGLE_L90		eCDTAL_LEFT90
#define		NODE_ANGLE_L180		eCDTAL_LEFT180
#define		NODE_ANGLE_R90		eCDTAL_RIGHT90
#define		NODE_ANGLE_R180		eCDTAL_RIGHT180

struct sSlowDownParameters
{
	int16	i16SafeSlowDownDis[NODE_ANGLE_COUNT][CAR_WHEEL_COUNT];
	int16	i16GoSafeSlowDownAcc[NODE_ANGLE_COUNT][CAR_WHEEL_COUNT];
	int16	i16GoSafeSlowDownSpeed[NODE_ANGLE_COUNT][CAR_WHEEL_COUNT];
	sSlowDownParameters()
	{
		memset(this, 0, sizeof(sSlowDownParameters));
	}
};

//=====================================
LAZY_MESSAGE_HEADER_STAR(eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE_REQUEST)
	int					iVersion;
	char				strMapFileName[MAP_NAME_ARRAY_LENGTH];
	sSlowDownParameters	SlowDownParameters;
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE_REQUEST)

LAZY_RESULT_MESSAGE_HEADER_STAR(eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT)
	int		iCarID;
	int		iVersion;
	char	strMapFileName[MAP_NAME_ARRAY_LENGTH];
LAZY_RESULT_MESSAGE_HEADER_END(eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT)

LAZY_MESSAGE_HEADER_STAR(eCDNM_C2S_CAR_STATUS)
	int	iCarID;
	int	iTagID;
	int	i1Status;//eCarSendingStatus
LAZY_MESSAGE_HEADER_END(eCDNM_C2S_CAR_STATUS)


struct sRouteDividedIntoSmallPartData
{
	int8	i8AngleType;
	int16	i16StartTagID;
	int16	i16EndTagID;
	int16	i16Distance[CAR_WHEEL_COUNT];
	int16	i16Acc[CAR_WHEEL_COUNT];
	int16	i16Speed[CAR_WHEEL_COUNT];
	//for safe driving to avoid accident.
	int16	i16SafeDistance[CAR_WHEEL_COUNT];
	int16	i16SafeAcc[CAR_WHEEL_COUNT];
	int16	i16SafeSpeed[CAR_WHEEL_COUNT];
};

LAZY_MESSAGE_HEADER_STAR(eCDNM_S2C_CAR_GO_TO_DESTINATION_REQUEST)
	int								iCount;//or do if Tag ID is -1 end?,2
	int								iSmallPartDataCount;
	int								iCarID;
	int16							i16TagIDArray[CAR_A_TO_B_DATA_LENGTH];//160
	//i16DistanceArray,i8AngleTypeArray not necessary data,because put data into RouteDividedIntoSmallPartDataArray
	int16							i16DistanceArray[CAR_A_TO_B_DATA_LENGTH];
	int8							i8AngleTypeArray[CAR_A_TO_B_DATA_LENGTH];
	sRouteDividedIntoSmallPartData	RouteDividedIntoSmallPartDataArray[ROUTE_KEY_POINT_DATA_LENGTH];
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_CAR_GO_TO_DESTINATION_REQUEST)

LAZY_RESULT_MESSAGE_HEADER_STAR(eCDNM_C2S_CAR_GO_TO_DESTINATION_RESULT)
	int	iCarID;
	int	iCount;
LAZY_RESULT_MESSAGE_HEADER_END(eCDNM_C2S_CAR_GO_TO_DESTINATION_RESULT)



//struct sDataAndLength
//{
//	char*	pData;
//	int		iSize;
//	void	Add(char*e_pData,int e_iSize);
//	void	Strip(int e_iBeforeIndexDataDelete);
//};
//struct sPacketParse
//{
//	sDataAndLength	DataAndLength;
//	bool	GetMagicIDIndex(char*e_pData,int e_iDataSize,int&e_iNumMagicMatched,int&e_iFirstMatchedIndex);
//	int		GetCheckSum(char*e_pData, int e_iDataSize);
//	bool	GetData(char*e_pOutData,int&e_iDataSize);
//	static  char*GetHeader(int e_iDataSize)
//	{
//
//	}
//};