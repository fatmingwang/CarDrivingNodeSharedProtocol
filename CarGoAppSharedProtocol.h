#pragma once

#include "SharedProtocolCommonDefine.h"
#include "CarGoAppSharedProtocolResult.h"


#define		CAR_GO_APP_TCP_IP_PORT				5978
#define		CAR_GO_APP_NETWORK_MESSAGE_VERSION	20191224
#define		MAP_NAME_ARRAY_LENGTH				40
#define		DELIVER_POINT_DATA_LENGTH			20
#define		CUSTOMER_POINT_DATA_LENGTH			80
#define		MAX_CAR_COUNT						10
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
	//
	eCGANM_C2S_QUERY_DELIVER_POINT_CAR_INFORMATION,//every 1 second try to fetch information.
	eCGANM_S2C_QUERY_DELIVER_POINT_CAR_INFORMATION_RESULT,
	//
	eCGANM_C2S_CAR_GO,
	eCGANM_S2C_CAR_GO_RESULT,
	//
	eCGANM_S2C_MEAL_NOT_BEEN_FETCHED,

	eCGANM_C2S_CAR_ACCIDENT_HAPPEN,
	//for demo page
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
	//
	eCGANM_MAX,
};

////=====================================
LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_VERSION_AND_MAP_INFOR)
	int		iVersion;
	char	strMapName[MAP_NAME_ARRAY_LENGTH];
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_VERSION_AND_MAP_INFOR)
//

LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_VERSION_AND_MAP_INFOR_RESULT)
	int	iUserID;
	int	iDeliverPointNodeIDArray[DELIVER_POINT_DATA_LENGTH];
	int	iCustomerPointNodeIDArray[CUSTOMER_POINT_DATA_LENGTH];//node ID not RFID
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_VERSION_AND_MAP_INFOR_RESULT)


LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_REQUIRE_DELIVER_POINT_INFO)
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_REQUIRE_DELIVER_POINT_INFO)

LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_REQUIRE_DELIVER_POINT_INFO_RESULT)
	bool	bDeliverPointOccupied[DELIVER_POINT_DATA_LENGTH];
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_REQUIRE_DELIVER_POINT_INFO_RESULT)


LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_SELECTED_DELIVER_POINT)
	int	iUserID;
	int iSelectDeliverPointID;
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_SELECTED_DELIVER_POINT)

LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_SELECTED_DELIVER_POINT_RESULT)
	bool	bDeliverPointOccupied[DELIVER_POINT_DATA_LENGTH];
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_SELECTED_DELIVER_POINT_RESULT)

LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_CAR_GO)
	int		iStartID;
	int		iEndID;
	//if true don't wait customer fetch meal
	bool	bDemoMode;
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_CAR_GO)

LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_CAR_GO_RESULT)
	int iCarID;
	int iStartID;
	int iEndID;
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_CAR_GO_RESULT)


LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_MEAL_NOT_BEEN_FETCHED)
	int		iCarID;
	int		iTableID;
	float	fWaitSeconds;
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_MEAL_NOT_BEEN_FETCHED)



LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_C2S_CAR_ACCIDENT_HAPPEN)
	int		iCarID;
	int		iNodeID;
	int		iInProblem;//0 false; 1 yes
	int		iExceptionCode[2];
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_C2S_CAR_ACCIDENT_HAPPEN)




LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_CAR_TROUBLESHOOTING_INFO_REQUEST)
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_CAR_TROUBLESHOOTING_INFO_REQUEST)


LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_CAR_TROUBLESHOOTING_INFO_RESULT)
	int	iNumCar;
	int iCarIDArray[MAX_CAR_COUNT];
	int iNodeIDArray[MAX_CAR_COUNT];
	int iCarStatusArray[MAX_CAR_COUNT];
	int iBatteryArray[MAX_CAR_COUNT];
	int iExceptionCodeArray[MAX_CAR_COUNT];
	int iWIFIStrengthArray[MAX_CAR_COUNT];
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_CAR_TROUBLESHOOTING_INFO_RESULT)


LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_CAR_TROUBLESHOOTING_CAR_STATUS_CHANGE_REQUEST)
	int iCarID;
	int iCarStatus;//enum eTurobleshootingButtonType{eTBT_CAR_REMOVE = 0,eTBT_REJOIN,eTBT_GO_HOME,eTBT_MAX};
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_CAR_TROUBLESHOOTING_CAR_STATUS_CHANGE_REQUEST)


LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_CAR_TROUBLESHOOTING_CAR_STATUS_CHANGE_RESULT)
	int iCarID;
	int iNodeID;
	int iCarStatus;
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_CAR_TROUBLESHOOTING_CAR_STATUS_CHANGE_RESULT)



LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_QUERY_DELIVERPOINT_CAR_REQUEST)
	int	iDeliverPoint;
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_QUERY_DELIVERPOINT_CAR_REQUEST)

LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_QUERY_DELIVERPOINT_CAR_RESULT)
	int		iCarID;//-1 no car
	int		iCarStatus;//eCarDrivingStatus,show car is waiting or read y to go.
	bool	bMealSettled;
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
	bool	bCarWillGoStableESoIgnoeLastOverlapNode;
	int		iCarWayToFirstHitIndexSafeStep;
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