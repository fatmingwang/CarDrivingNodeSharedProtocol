#pragma once

#include	"SharedProtocolCommonDefine.h"
#include	"CarDrivingMessageList.h"
#include	"CarDrivingResultMessage.h"
//first version 20200102
//20200304 add motor speed eCDNM_C2S_CAR_STATUS:iMotorSpeed
//20200311 add eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE_REQUEST:fSendHardwareDataToServerTC
//20200423 add eCSS_RFID_NOT_CORRECT event while car has accidently reach wrong RFID
//20200617 add RFID_DATA_TYPE
//20200819 immediately stop RFID change to deliver and charge point
//20200914 Enlarge the maximum count of RFID cards(TOTAL_CARD_COUNT)
//20200915 ROUTE_KEY_POINT_DATA_LENGTH		from 20 to 30
//20200925 protocol add eMSL_GET_COLLIDED
//20200926 add sRouteDividedIntoSmallPartData::i8DoOpenLoopTransfer;
//20201012 i8DoOpenLoopTransfer change to eLoopTransferType
//20201023 add eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE_REQUEST::RFID_DATA_TYPE		i64CustomerPoint[CUSTOMER_POINT_COUNT];,wait traffic point should not open upper Lid.
//20201030 eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE_REQUEST add fMotorWarningAsErrorTC
//20201110 eCDNM_S2C_LED_HW_TEST add char	strUpdateName[20];
#define		CAR_DRIVING_SERVER_NETWORK_MESSAGE_VERSION			20201023
#define		CAR_DRIVING_SERVER_NETWORK_TARGET_PORT				2978
//for fetch meal type
//0 for detect weight
//1 for detect door open and close
enum eFetchMealHouseType
{
	eFMHT_WEIGHT_DECTOR = 0,
	eFMHT_WANG_DOUBLE_COW_MAGNATIC_GATE,
	//server size behavior  just like eFMHT_WANG_DOUBLE_COW_MAGNATIC_GATE,all rest thing will be done by Car.
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


#define		CHARGE_POINT_COUNT				15
#define		DELIVER_POINT_COUNT				5
#define		CUSTOMER_POINT_COUNT			50

#define		CAR_A_TO_B_DATA_LENGTH			80
#define		ROUTE_KEY_POINT_DATA_LENGTH		30
#define		TOTAL_CARD_COUNT				165				//202010104 from 150 to 165

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
	RFID_DATA_TYPE		i64DeliverPoint[DELIVER_POINT_COUNT];
	RFID_DATA_TYPE		i64ChargePoint[CHARGE_POINT_COUNT];
	RFID_DATA_TYPE		i64CustomerPoint[CUSTOMER_POINT_COUNT];
	float				fSendHardwareDataToServerTC;//
	int16				i16MaxAllowMotorOverLoading;//
	float				fMotorWarningAsErrorTC;		//while motor keeps warning for a while treat it as error
	float				fNodeToNodeTCStright;
	float				fNodeToNodeTC90;
	float				fNodeToNodeTC180;
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE_REQUEST)
#pragma pack(pop)
//
#pragma pack(push,1)
LAZY_RESULT_MESSAGE_HEADER_STAR(eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT)
	int		iCarID;
	int		iNetworkProtocolVersion;
	int		iCarDrivingVersion;
	int64	i64RASPI_SN;
	int 	iFetchMealType;
	int 	iTargetDeliverPointID;
	char	strMapFileName[MAP_NAME_ARRAY_LENGTH];
LAZY_RESULT_MESSAGE_HEADER_END(eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT)
#pragma pack(pop)
//
#pragma pack(push,1)
struct sCarRunningData
{
	double	dbAppRunningTime;
	double	dbDrivingTime;
	int64	i64LeftWheelMovingDistance;
	int64	i64RighttWheelMovingDistance;
	sCarRunningData() { memset(this, 0, sizeof(sCarRunningData)); }
};
#pragma pack(pop)
//
#pragma pack(push,1)
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
	int				iCPUTemperature;
	int				iMotorEncoderTemperature[2];
	sCarRunningData	CarRunningData;
LAZY_MESSAGE_HEADER_END(eCDNM_C2S_CAR_STATUS)
#pragma pack(pop)
//=======================
enum eLoopTransferType
{
	eLTT_BOTH_OPEN = 0,
	eLTT_LEFT_CLOSE_RIGHT_OPEN,//1
	eLTT_RIGHTT_CLOSE_LEFT_OPEN,//2
	eLTT_BOTH_CLOSE,//3
	eLTT_MAX
};
#pragma pack(push,1)// push current alignment to stack,set alignment to n byte boundary
struct sRouteDividedIntoSmallPartData
{
	int8			i8LoopTransferType;//eLoopTransferType
	int8			i8AngleType;
	uint8			ui8StartNodeID;
	uint8			ui8EndNodeID;
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
	//node(RFID) count
	int								iCount;//or do if Tag ID is -1 end?,2
	int								iSmallPartDataCount;
	int								iCarID;
	uint8							ui8StopNodeID;//play sound by customer node ID
	uint8							ui8NodeIDArray[CAR_A_TO_B_DATA_LENGTH];//160
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


LAZY_MESSAGE_HEADER_STAR(eCDNM_S2C_LED_HW_TEST)
	unsigned char	ucColor[3];
	int				iSpeed;
	float			fLimunance;
	char			strUpdateName[20];
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_LED_HW_TEST)


enum eLidBehaviorType
{
	eLBT_OPEN = 0,
	eLBT_CLOSE,
	eLBT_TEST,
	eLBT_MAX
};
#pragma pack(push,1)
LAZY_MESSAGE_HEADER_STAR(eCDNM_S2C_LID_MOTOR_HW_TEST)
	int		iAngle;
	int		iType;//eLidBehaviorType
	int		iSpeed;
	int		iAcc;
	bool	bSaveFile;
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_LID_MOTOR_HW_TEST)
#pragma pack(pop)



#pragma pack(push,1)
LAZY_MESSAGE_HEADER_STAR(eCDNM_S2C_CANCEL_DELIVER_ORDER_REQUEST)
	RFID_DATA_TYPE	i64StopRFID;
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_CANCEL_DELIVER_ORDER_REQUEST)
#pragma pack(pop)
//result code 0 car pass over,1 car will stop at chancel deliver point
#pragma pack(push,1)
LAZY_RESULT_MESSAGE_HEADER_STAR(eCDNM_C2S_CANCEL_DELIVER_ORDER_RESULT)
	int	iCarID;
LAZY_RESULT_MESSAGE_HEADER_END(eCDNM_C2S_CANCEL_DELIVER_ORDER_RESULT)
#pragma pack(pop)

#pragma pack(push,1)
LAZY_MESSAGE_HEADER_STAR(eCDNM_S2C_ALL_RFID_AND_NODE_ID_INFO)
	int32			iCount;
	RFID_DATA_TYPE	i64RFIDArray[TOTAL_CARD_COUNT];
	uint8			ui8NodeIDArray[TOTAL_CARD_COUNT];
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_ALL_RFID_AND_NODE_ID_INFO)
#pragma pack(pop)

#pragma pack(push,1)
LAZY_MESSAGE_HEADER_STAR(eCDNM_S2C_COLLISION_TEST)
	bool bHitted;
LAZY_MESSAGE_HEADER_END(eCDNM_S2C_COLLISION_TEST)
#pragma pack(pop)


#pragma pack(push,1)
LAZY_MESSAGE_HEADER_STAR(eCDNM_C2S_CAR_EXCEPTION_HAPPEN)
	int	iCarID;
	int iCarExceptionCode;
LAZY_MESSAGE_HEADER_END(eCDNM_C2S_CAR_EXCEPTION_HAPPEN)
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