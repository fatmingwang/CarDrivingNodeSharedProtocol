#pragma once

#include "SharedProtocolCommonDefine.h"
#include "CarGoAppSharedProtocolResult.h"

//20201103
//add setup IP at AppInfoPage
//CarGoApp/Setup.xml add Amin attribute if 1 the CarGoApp won't be kicked,if the deliver point was selected
//20200311 bind version for server and car
//20200930 eCarControlCarBehaviorList add eCCCBL_MOVE_LEFT_180,eCCCBL_MOVE_RIGHT_180
//20201103 add eCGANM_S2C_CAR_EXCEPTION_CODE

#define		CAR_GO_APP_VERSION					20201119

#define		CAR_GO_APP_TCP_IP_PORT				5978
#define		CAR_GO_APP_NETWORK_MESSAGE_VERSION	20201103
#define		DELIVER_POINT_DATA_LENGTH			20
#define		CUSTOMER_POINT_DATA_LENGTH			80
#define		COLLECT_PLATE_POINT_DATA_LENGTH		5
#define		MAX_CAR_COUNT						10

//1
//eCGANM_C2S_VERSION_AND_MAP_INFOR
//2
//eCGANM_C2S_REQUIRE_DELIVER_POINT_INFO
//3
//eCGANM_C2S_SELECTED_DELIVER_POINT
//4 every 1 second
//eCGANM_C2S_QUERY_DELIVERPOINT_CAR_REQUEST

//5
//ask car to go from A to B
//eCGANM_C2S_CAR_GO
//warning for customer did't fetch the meal
//eCGANM_S2C_MEAL_NOT_BEEN_FETCHED
//car stuck ono the way or lost connection
//eCGANM_C2S_CAR_ACCIDENT_HAPPEN
//ask car to home,iCarStatus = 2:car go home
//eCGANM_C2S_CAR_TROUBLESHOOTING_CAR_STATUS_CHANGE_REQUEST
//car info where car stay and goes.
//eCGANM_C2S_QUERY_DELIVERPOINT_CAR_REQUEST
enum eCarGoAppNetworkMessage
{
	eCGANM_C2S_VERSION_AND_MAP_INFOR = 100000,//tell me your deliver point and map infomation and else...
	eCGANM_S2C_VERSION_AND_MAP_INFOR_RESULT,
	//
	eCGANM_C2S_REQUIRE_DELIVER_POINT_INFO,
	eCGANM_S2C_REQUIRE_DELIVER_POINT_INFO_RESULT,
	//
	eCGANM_C2S_SELECTED_DELIVER_POINT,
	eCGANM_S2C_SELECTED_DELIVER_POINT_RESULT,
	//below 2 useless but need to keep because remove will ID change.
	eCGANM_C2S_QUERY_DELIVER_POINT_CAR_INFORMATION,
	eCGANM_S2C_QUERY_DELIVER_POINT_CAR_INFORMATION_RESULT,
	//
	eCGANM_C2S_CAR_GO,
	eCGANM_S2C_CAR_GO_RESULT,
	//
	eCGANM_S2C_MEAL_NOT_BEEN_FETCHED,//100010

	eCGANM_C2S_CAR_ACCIDENT_HAPPEN,
	//query deliver point status,every 1 second try to fetch information.
	eCGANM_C2S_QUERY_DELIVERPOINT_CAR_REQUEST,
	eCGANM_S2C_QUERY_DELIVERPOINT_CAR_RESULT,
	//
	eCGANM_C2S_CAR_TROUBLESHOOTING_INFO_REQUEST,
	eCGANM_S2C_CAR_TROUBLESHOOTING_INFO_RESULT,
	eCGANM_C2S_CAR_TROUBLESHOOTING_CAR_STATUS_CHANGE_REQUEST,
	eCGANM_S2C_CAR_TROUBLESHOOTING_CAR_STATUS_CHANGE_RESULT,
	eCGANM_C2S_CAR_TROUBLESHOOTING_CAR_EMGENCY_STOP_REQUEST,
	eCGANM_S2C_CAR_TROUBLESHOOTING_CAR_EMGENCY_STOP_RESULT,
	//
	eCGANM_C2S_CHANGE_PARAMETER_SETTING_REQUEST,
	eCGANM_S2C_CHANGE_PARAMETER_SETTING_RESULT,
	eCGANM_C2S_QUERY_PARAMETER_SETTING_REQUEST,
	eCGANM_S2C_QUERY_PARAMETER_SETTING_RESULT,
	//chancel deliver order,
	//if car still park at deliver point,reset car status
	//if car is on the way to customer point
	//1.if car pass over park node,car keep its status
	//2.if car not pass over park node stay at park node and wait server coomand to home.
	//make car park and gohome
	eCGANM_C2S_CANCEL_DELIVER_ORDER_REQUEST,
	eCGANM_S2C_CANCEL_DELIVER_ORDER_RESULT,
	//
	eCGANM_C2S_CAR_CONTROL_PAGE_CAR_BEHAVIOR_CHANGE_REQUEST,
	eCGANM_C2S_CAR_CONTROL_PAGE_CAR_BEHAVIOR_CHANGE_RESULT,
	//
	//eCGANM_C2S_ASK_ALL_PIT_CHARGE_REQUEST,
	//eCGANM_C2S_ASK_PIT_AUTO_CHARGE_CHANGE_REQUEST,
	//if plate were colleted user want car go home just send 
	//eCGANM_C2S_CAR_TROUBLESHOOTING_CAR_STATUS_CHANGE_REQUEST::iCarStatus = eTBT_GO_HOME = 2;
	//
	eCGANM_S2C_CAR_EXCEPTION_CODE,
	//
	//eCGANM_C2S_ASK_CAR_TO_COLLECT_PLATE_REQUEST,
	//eCGANM_S2C_ASK_CAR_TO_COLLECT_PLATE_RESULT,
	//eCGANM_C2S_COLLECT_PLATE_FINISH_REQUEST,
	//eCGANM_C2S_COLLECT_PLATE_FINISH_RESULT,
	eCGANM_C2S_LID_STATUS_CHANGE_REQUEST,
	eCGANM_C2S_LID_STATUS_CHANGE_RESULT,
	//
	//basicly useless...but boss want it.
	eCGANM_C2S_QUERY_COLLECT_PLATE_NODE_ID_REQUEST,
	eCGANM_S2C_QUERY_COLLECT_PLATE_NODE_ID_RESULT,
	//
	eCGANM_MAX,
};
//
enum eCarQuickMoingDirection
{
	eCQMD_LEFT = 0,
	eCQMD_FORWARD,
	eCQMD_RIGHT,
	eCQMD_RESERVE,
	eCQMD_LEFT_180,
	eCQMD_RIGHT_180,
	eCQMD_MAX
};
static const wchar_t* g_ssCarQuickMoingDirectionString[eCQMD_MAX] =
{
   L"Forward",
   L"Left",
   L"Right",
   L"Reserve",
   L"Left180",
   L"Right180"
};

////=====================================
LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_VERSION_AND_MAP_INFOR)
	int		iVersion;//CAR_GO_APP_NETWORK_MESSAGE_VERSION
	char	strMapName[MAP_NAME_ARRAY_LENGTH];//Maps/Wang_DoubleCow.xml
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_VERSION_AND_MAP_INFOR)
//

LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_VERSION_AND_MAP_INFOR_RESULT)
	int	iUserID;
	int	iDeliverPointNodeIDArray[DELIVER_POINT_DATA_LENGTH];
	int	iCustomerPointNodeIDArray[CUSTOMER_POINT_DATA_LENGTH];//customer tabler ID or node ID not RFID
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_VERSION_AND_MAP_INFOR_RESULT)


LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_REQUIRE_DELIVER_POINT_INFO)
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_REQUIRE_DELIVER_POINT_INFO)

LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_REQUIRE_DELIVER_POINT_INFO_RESULT)
	bool	bDeliverPointOccupied[DELIVER_POINT_DATA_LENGTH];//eCGANM_S2C_VERSION_AND_MAP_INFOR_RESULT::iDeliverPointNodeIDArray is any point occupied?
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_REQUIRE_DELIVER_POINT_INFO_RESULT)


LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_SELECTED_DELIVER_POINT)
	int	iUserID;//eCGANM_S2C_VERSION_AND_MAP_INFOR_RESULT:iUserID
	int iSelectDeliverPointID;//one of eCGANM_S2C_VERSION_AND_MAP_INFOR_RESULT::iDeliverPointNodeIDArray
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_SELECTED_DELIVER_POINT)

LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_SELECTED_DELIVER_POINT_RESULT)
	bool	bDeliverPointOccupied[DELIVER_POINT_DATA_LENGTH];//if result is not ok,it's possible someone occupied the deliver point,renew buttons again
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_SELECTED_DELIVER_POINT_RESULT)

LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_CAR_GO)
	int		iStartID;//deliver point
	int		iEndID;//customer table ID
	//if true don't wait customer fetch meal
	bool	bDemoMode;
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_CAR_GO)

//result eCarGoAppSharedProtocolResult
LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_CAR_GO_RESULT)
	int iCarID;
	int iStartID;
	int iEndID;
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_CAR_GO_RESULT)

//show warning message
LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_MEAL_NOT_BEEN_FETCHED)
	int		iCarID;
	int		iTableID;
	float	fWaitSeconds;
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_MEAL_NOT_BEEN_FETCHED)


//show error message
LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_C2S_CAR_ACCIDENT_HAPPEN)
	int		iCarID;
	int		iNodeID;
	int		iInProblem;//0 false; 1 yes
	int		iExceptionCode[2];
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_C2S_CAR_ACCIDENT_HAPPEN)


//show error message
LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_CAR_EXCEPTION_CODE)
	int		iCarID;
	int		iCarExceptionCode;
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_CAR_EXCEPTION_CODE)


LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_CAR_TROUBLESHOOTING_INFO_REQUEST)

LAZY_MESSAGE_HEADER_END(eCGANM_C2S_CAR_TROUBLESHOOTING_INFO_REQUEST)

//query car status.
LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_CAR_TROUBLESHOOTING_INFO_RESULT)
	int	iNumCar;
	int iCarIDArray[MAX_CAR_COUNT];
	int iNodeIDArray[MAX_CAR_COUNT];//where the car is
	int iCarStatusArray[MAX_CAR_COUNT];
	int iBatteryArray[MAX_CAR_COUNT];
	int iExceptionCodeArray[MAX_CAR_COUNT];
	int iWIFIStrengthArray[MAX_CAR_COUNT];
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_CAR_TROUBLESHOOTING_INFO_RESULT)

enum eTurobleshootingButtonType { eTBT_CAR_REMOVE = 0, eTBT_REJOIN, eTBT_GO_HOME, eTBT_MAX };
LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_CAR_TROUBLESHOOTING_CAR_STATUS_CHANGE_REQUEST)
	int iCarID;
	int iCarStatus;//enum eTurobleshootingButtonType{eTBT_CAR_REMOVE = 0,eTBT_REJOIN = 1,eTBT_GO_HOME = 2,eTBT_MAX};
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_CAR_TROUBLESHOOTING_CAR_STATUS_CHANGE_REQUEST)


LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_CAR_TROUBLESHOOTING_CAR_STATUS_CHANGE_RESULT)
	int iCarID;
	int iNodeID;
	int iCarStatus;
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_CAR_TROUBLESHOOTING_CAR_STATUS_CHANGE_RESULT)



LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_QUERY_DELIVERPOINT_CAR_REQUEST)
	int	iDeliverPoint;
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_QUERY_DELIVERPOINT_CAR_REQUEST)


struct sCarCurrentAndTargetInfo
{
	int		CarID;
	int		CarCurrentCustomerTableID;
	int		CarTargetCustomerTableID;
};

LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_QUERY_DELIVERPOINT_CAR_RESULT)
	int							iCarID;//-1 no car
	int							iCarStatus;//eCarDrivingStatus,show car is waiting or read y to go.
	bool						bMealSettled;//gate open(0) or close(1)
	int							iNumCar;
	sCarCurrentAndTargetInfo	CarCurrentAndTargetInfoArray[MAX_CAR_COUNT];
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_QUERY_DELIVERPOINT_CAR_RESULT)



LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_CAR_TROUBLESHOOTING_CAR_EMGENCY_STOP_REQUEST)
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_CAR_TROUBLESHOOTING_CAR_EMGENCY_STOP_REQUEST)


LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_CAR_TROUBLESHOOTING_CAR_EMGENCY_STOP_RESULT)
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_CAR_TROUBLESHOOTING_CAR_EMGENCY_STOP_RESULT)


struct sServerParameter
{
	float	fCarDrivingStayAtSameNodeTooLongIsOutOfControlTC;
	float	fFetchMealTimeOutTC;
	float	fRFIDTimeOutTC;
	float	fDrmoModeCarGoHomeTC;
	float	fChargePointToDeliverPointTC;
	float	fMealEmptyWaitNSscondsToHome;
	float	fAskCarWhoYouAraTC;
	float	fTrafficCheckTC;
	float	fTrafficStruckTC;
	bool	bCarWillGoStableESoIgnoeLastOverlapNode;//10
	int		iCarWayToFirstHitIndexSafeStep;
	bool	bDoWheelOffsetForWall;
	bool	bWheelOffsetForWallSameSettingIgnore;
	float	fCarLoginChargePointToDeliverPointDelayTC;
	float	fCarDrivingSafeGoDistanc;//15
};

LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_CHANGE_PARAMETER_SETTING_REQUEST)
	sServerParameter ServerParameter;
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_CHANGE_PARAMETER_SETTING_REQUEST)


LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_CHANGE_PARAMETER_SETTING_RESULT)
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_CHANGE_PARAMETER_SETTING_RESULT)

LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_QUERY_PARAMETER_SETTING_REQUEST)
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_QUERY_PARAMETER_SETTING_REQUEST)

LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_QUERY_PARAMETER_SETTING_RESULT)
	sServerParameter ServerParameter;
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_QUERY_PARAMETER_SETTING_RESULT)


LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_CANCEL_DELIVER_ORDER_REQUEST)
	int	iCarID;
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_CANCEL_DELIVER_ORDER_REQUEST)

//result code 
//eCGASPR_CAR_CANCEL_DELIVER_ORDER_STOP_AT_CANCEL_DELIVER_POINT_OK car will stop at chancel deliver point
//eCGASPR_CAR_CANCEL_DELIVER_ORDER_CAR_STAY_AT_DELIVER_POINT_OK car stay at deliver point ,now order canceled
//eCGASPR_CAR_CANCEL_DELIVER_ORDER_CAR_PASS_OVER_DELIVER_POINT_FAILED car pass over,please wait 30 seconds or make it go home after it arrived destination
//eCGASPR_CAR_CANCEL_DELIVER_ORDER_CAR_NOT_START_FROM_DELIVER_POINT_FAILED cat start point is not deliver point
LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_CANCEL_DELIVER_ORDER_RESULT)
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_CANCEL_DELIVER_ORDER_RESULT)

enum eCarControlCarBehaviorList
{
	eCCCBL_MOVE_LEFT = 0,
	eCCCBL_MOVE_FORWARD,
	eCCCBL_MOVE_RIGHT,
	eCCCBL_MOVE_REVERSE,
	eCCCBL_STOP,
	eCCCBL_GO_HOME,
	eCCCBL_DELIVER_CONTINUE,
	eCCCBL_MOVE_LEFT_180,
	eCCCBL_MOVE_RIGHT_180,
	eCCCBL_MAX
};
LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_CAR_CONTROL_PAGE_CAR_BEHAVIOR_CHANGE_REQUEST)
	int	iCarID;
	int	iBehavior;//eCarControlCarBehaviorList
	int	iMovingScale;
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_CAR_CONTROL_PAGE_CAR_BEHAVIOR_CHANGE_REQUEST)


//LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_ASK_ALL_PIT_CHARGE_REQUEST)
//	int	iChargeTime;
//LAZY_MESSAGE_HEADER_END(eCGANM_C2S_ASK_ALL_PIT_CHARGE_REQUEST)
//
//
//LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_ASK_PIT_AUTO_CHARGE_CHANGE_REQUEST)
//	bool bOn;
//LAZY_MESSAGE_HEADER_END(eCGANM_C2S_ASK_PIT_AUTO_CHARGE_CHANGE_REQUEST)

//LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_ASK_CAR_TO_COLLECT_PLATE_REQUEST)
//	int	iNodeID;
//LAZY_MESSAGE_HEADER_END(eCGANM_C2S_ASK_CAR_TO_COLLECT_PLATE_REQUEST)
//
//LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_ASK_CAR_TO_COLLECT_PLATE_RESULT)
//	int iCarID;
//LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_ASK_CAR_TO_COLLECT_PLATE_RESULT)
//
//
//LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_COLLECT_PLATE_FINISH_REQUEST)
//	int iCarID;
//	int	iNodeID;
//LAZY_MESSAGE_HEADER_END(eCGANM_C2S_COLLECT_PLATE_FINISH_REQUEST)
//
//LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_C2S_COLLECT_PLATE_FINISH_RESULT)
//LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_C2S_COLLECT_PLATE_FINISH_RESULT)


LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_LID_STATUS_CHANGE_REQUEST)
	int		iCarID;
	bool	bLidOpen;
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_LID_STATUS_CHANGE_REQUEST)


LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_C2S_LID_STATUS_CHANGE_RESULT)
	//eACGRM_CAR_DRIVING
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_C2S_LID_STATUS_CHANGE_RESULT)


LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_QUERY_COLLECT_PLATE_NODE_ID_REQUEST)
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_QUERY_COLLECT_PLATE_NODE_ID_REQUEST)

LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_QUERY_COLLECT_PLATE_NODE_ID_RESULT)
	int	iParckPlateCollectCarPointNodeIDArray[COLLECT_PLATE_POINT_DATA_LENGTH];
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_QUERY_COLLECT_PLATE_NODE_ID_RESULT)

