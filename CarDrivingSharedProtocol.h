#pragma once

#include	"SharedProtocolCommonDefine.h"
#include	"CarDrivingMessageList.h"
#include	"CarDrivingResultMessage.h"
//first version 20200102
//20200304 add motor speed eCDNM_C2S_CAR_STATUS:iMotorSpeed
//20200311 add eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE_REQUEST:fSendHardwareDataToServerTC
//20200423 add eCSS_RFID_NOT_CORRECT event while car has accidently reach wrong RFID
//20200617 add RFID_DATA_TYPE

#define		CAR_DRIVING_SERVER_NETWORK_MESSAGE_VERSION			20200519
#define		CAR_DRIVING_SERVER_NETWORK_TARGET_PORT				2978
//for fetch meal type
//0 for detect weight
//1 for detect door open and close
enum eFetchMealHouseType
{
	eFMHT_WEIGHT_DECTOR = 0,
	eFMHT_WANG_DOUBLE_COW_MAGNATIC_GATE,
	eFMHT_MOTOR_UPPER_LID_GATE,
	eFMHT_PLATE_COLLECTOR,
	eFMHT_MAX
};

//#define		WAIT_FETCH_MEAL_TYPE_WEIGHT_DETECT	0
//#define		WAIT_FETCH_MEAL_TYPE_GATE_DETECT	1
//
//#define		WAIT_FETCH_MEAL_TYPE_MOTOR_LID		2
//#define		WAIT_FETCH_MEAL_TYPE_PLATE_COLLECT	3


#define		LID_OPEN_STATUS_CLOSE_NO_FOOD		0
#define		LID_OPEN_STATUS_CLOSE_WITH_FOOD		1
#define		LID_OPEN_STATUS_OPEN_WITH_FOOD		2
#define		LID_OPEN_STATUS_OPEN_NO_FOOD		4

#define		GATE_CLOSE	true
#define		GATE_OPEN	false

//data

#define		IMMEDIATELY_STOP_RFID_COUNT		20

#define		CAR_A_TO_B_DATA_LENGTH			80
#define		ROUTE_KEY_POINT_DATA_LENGTH		20
#define		TOTAL_CARD_COUNT				100


#ifndef		MAP_NAME_ARRAY_LENGTH
#define		MAP_NAME_ARRAY_LENGTH			40
#endif
#define		RFID_DATA_TYPE					int64
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
#pragma pack(push,1)// push current alignment to stack,set alignment to n byte boundary
LAZY_MESSAGE_HEADER_STAR(eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE_REQUEST)
	int					iVersion;
	char				strMapFileName[MAP_NAME_ARRAY_LENGTH];
	int					iDontSendBackToServer;//for server test slowbreak.
	int					iSlowBreakAcc;
	int					iSlowBreakSpeed;
	int					iSlowBreakDis;
	RFID_DATA_TYPE		i64DeliverPointRFID[IMMEDIATELY_STOP_RFID_COUNT];
	//int					iFetchMealType;//
	float				fSendHardwareDataToServerTC;//
	int16				i16MaxAllowMotorOverLoading;//
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE_REQUEST)
#pragma pack(pop)

LAZY_RESULT_MESSAGE_HEADER_STAR(eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT)
	int		iCarID;
	int		iNetworkProtocolVersion;
	int		iCarDrivingVersion;
	int		iArduinoVersion;
	int64	i64RASPI_SN;
	int 	iFetchMealType;
	int 	iTargetDeliverPointID;
	char	strMapFileName[MAP_NAME_ARRAY_LENGTH];
LAZY_RESULT_MESSAGE_HEADER_END(eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT)

struct sCarRunningData
{
	double	dbAppRunningTime;
	double	dbDrivingTime;
	int64	i64LeftWheelMovingDistance;
	int64	i64RighttWheelMovingDistance;
	sCarRunningData() { memset(this, 0, sizeof(sCarRunningData)); }
};

LAZY_MESSAGE_HEADER_STAR(eCDNM_C2S_CAR_STATUS)
	int				iCarID;
	RFID_DATA_TYPE	i64RFID;
	int				i1Status;//eCarSendingStatus
	int				iBattery;
	int				iExceptionCode;
	int				iWIFISignalStrength;
	int				iMotorMovedDistance[2];
	int				iMotorLoading[2];
	int				iMotorSpeed[2];
	int				iMotorExceptionCode;
	sCarRunningData	CarRunningData;
LAZY_MESSAGE_HEADER_END(eCDNM_C2S_CAR_STATUS)

#pragma pack(push,1)// push current alignment to stack,set alignment to n byte boundary
struct sRouteDividedIntoSmallPartData
{
	int8			i8AngleType;
	//RFID_DATA_TYPE	i64StartRFID;
	//RFID_DATA_TYPE	i64EndRFID;
	int8			i8StartNodeID;
	int8			i8EndNodeID;
	int16			i16Distance[CAR_WHEEL_COUNT];
	int16			i16Acc[CAR_WHEEL_COUNT];
	int16			i16Speed[CAR_WHEEL_COUNT];
	//for safe driving to avoid accident.
	int16			i16SafeDistance[CAR_WHEEL_COUNT];
	int16			i16SafeAcc[CAR_WHEEL_COUNT];
	int16			i16SafeSpeed[CAR_WHEEL_COUNT];
};
#pragma pack(pop)

#pragma pack(push,1)// push current alignment to stack,set alignment to n byte boundary
LAZY_MESSAGE_HEADER_STAR(eCDNM_S2C_CAR_GO_TO_DESTINATION_REQUEST)
	int								iCount;//or do if Tag ID is -1 end?,2
	int								iSmallPartDataCount;
	int								iCarID;
	int8							i8StopNodeID;//play sound by customer node ID
	//RFID_DATA_TYPE					i64RFIDArray[CAR_A_TO_B_DATA_LENGTH];//160
	int8							i8NodeIDArray[CAR_A_TO_B_DATA_LENGTH];//160
	sRouteDividedIntoSmallPartData	RouteDividedIntoSmallPartDataArray[ROUTE_KEY_POINT_DATA_LENGTH];
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_CAR_GO_TO_DESTINATION_REQUEST)
#pragma pack(pop)

#pragma pack(push,1)
LAZY_RESULT_MESSAGE_HEADER_STAR(eCDNM_C2S_CAR_GO_TO_DESTINATION_RESULT)
	int	iCarID;
	int	iCount;
LAZY_RESULT_MESSAGE_HEADER_END(eCDNM_C2S_CAR_GO_TO_DESTINATION_RESULT)
#pragma pack(pop)

LAZY_MESSAGE_HEADER_STAR(eCDNM_S2C_ASK_CAR_STOP)
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_ASK_CAR_STOP)


LAZY_MESSAGE_HEADER_STAR(eCDNM_S2C_VOICE_TEST)
	int iVoiceID;
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_VOICE_TEST)


LAZY_MESSAGE_HEADER_STAR(eCDNM_S2C_LID_HW_TEST)
	unsigned char	ucColor[3];
	int		iSpeed;
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_LID_HW_TEST)





LAZY_MESSAGE_HEADER_STAR(eCDNM_S2C_CANCEL_DELIVER_ORDER_REQUEST)
	RFID_DATA_TYPE	i64StopRFID;
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_CANCEL_DELIVER_ORDER_REQUEST)

//result code 0 car pass over,1 car will stop at chancel deliver point
LAZY_RESULT_MESSAGE_HEADER_STAR(eCDNM_C2S_CANCEL_DELIVER_ORDER_RESULT)
	int	iCarID;
LAZY_RESULT_MESSAGE_HEADER_END(eCDNM_C2S_CANCEL_DELIVER_ORDER_RESULT)


#pragma pack(push,1)
LAZY_MESSAGE_HEADER_STAR(eCDNM_S2C_ALL_RFID_AND_NODE_ID_INFO)
	int32			iCount;
	RFID_DATA_TYPE	i64RFIDArray[TOTAL_CARD_COUNT];
	int8			i8NodeIDArray[TOTAL_CARD_COUNT];
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_ALL_RFID_AND_NODE_ID_INFO)
#pragma pack(pop)

//result code 0 car pass over,1 car will stop at chancel deliver point

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