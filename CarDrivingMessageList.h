#pragma once

#include "CarExceptionCode.h"

enum eCarDrivingNetworkMessage
{
	eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE_REQUEST = 0,//HW ID
	eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT,//HW ID
	//
	eCDNM_C2S_CAR_STATUS,//tag ID
	eCDNM_S2C_CAR_GO_TO_DESTINATION_REQUEST,//
	eCDNM_C2S_CAR_GO_TO_DESTINATION_RESULT,
	//
	eCDNM_S2C_RFID_INFO,
	eCDNM_S2C_RFID_INFO_RESULT,
	//eCDNM_S2C_CAR_GO_TO_DESTINATION_END,//node type
	eCDNM_S2C_ASK_CAR_STOP,//emgency situation!?
	eCDNM_S2C_VOICE_TEST,//
	//Feb/17/2020 added
	//if car still stay at deliver point chancel order or make car slow down and stop at chancel deliver point and wait go home
	//if car already apart and pass over chancel deliver,car keep going and keep deliver
	eCDNM_S2C_CANCEL_DELIVER_ORDER_REQUEST,
	eCDNM_C2S_CANCEL_DELIVER_ORDER_RESULT,//
	//
	eCDNM_S2C_ALL_RFID_AND_NODE_ID_INFO,
	//
	eCDNM_S2C_LED_HW_TEST,//
	eCDNM_S2C_LID_MOTOR_HW_TEST,//
	//
	eCDNM_S2C_COLLISION_TEST,
	//
	eCDNM_C2S_CAR_EXCEPTION_HAPPEN,
	//
	eCDNM_S2C_LID_MOTOR_STATUC_CHANGE_REQUEST,
	eCDNM_C2S_LID_MOTOR_STATUC_CHANGE_RESULT,
	//
	eCDNM_S2C_TABLET_SEND_CAR_REJOIN_REQUEST,
	//
	eCDNM_C2S_SEND_CAR_DRIVING_ROUTE_DATA,
	//
	eCDNM_S2C_TIME_SYNC,
	//
	eCDNM_MAX
};


enum eNodeType
{
	eNT_ROAD = 0,
	eNT_CUSTOMER,
	eNT_CHARGE_POINT,//all car don't need battery now,it's not chage point,it's a wait to deliver point point.
	eNT_DELIVER_POINT,//it also is a charge point,need this one?.server need to detect the deliver point is empty and ask idle card to move to next charge point or to deliver point!?
	eNT_TURN_POUNT_R15,//15
	eNT_TURN_POUNT_R30,//30
	eNT_TURN_POUNT_R45,//45
	eNT_TURN_POUNT_R60,//60
	eNT_TURN_POUNT_R75,//75
	eNT_TURN_POUNT_R90,//90
	eNT_TURN_POUNT_R105,//105,10
	eNT_TURN_POUNT_R120,//120
	eNT_TURN_POUNT_R135,//135
	eNT_TURN_POUNT_R150,//150
	eNT_TURN_POUNT_R165,//165
	eNT_TURN_POUNT_R180,//180
	eNT_TURN_POUNT_L15,//15
	eNT_TURN_POUNT_L30,//30
	eNT_TURN_POUNT_L45,//45
	eNT_TURN_POUNT_L60,//60
	eNT_TURN_POUNT_L75,//75,20
	eNT_TURN_POUNT_L90,//90
	eNT_TURN_POUNT_L105,//105
	eNT_TURN_POUNT_L120,//120
	eNT_TURN_POUNT_L135,//135
	eNT_TURN_POUNT_L150,//150
	eNT_TURN_POUNT_L165,//165
	eNT_TURN_POUNT_L180,//180
	eNT_DUMMY_POINT_FOR_COLLISION_TEST,//a not exists node (no rfid card),only for route collision test,void cCarSendA_TO_B_MessageController::StripDummyNodeCarDrivingRouteData()
	//some turn position don't have wall,so make a more quick turn.
	eNT_TURN_POUNT_RAPID_L90,//
	eNT_TURN_POUNT_RAPID_L180,//30
	eNT_TURN_POUNT_RAPID_R90,//
	eNT_TURN_POUNT_RAPID_R180,//
	//for extend more special data
	eNT_EXT1,
	eNT_EXT2,
	eNT_EXT3,
	eNT_EXT4,
	eNT_EXT5,
	eNT_EXT6,
	eNT_EXT7,
	eNT_EXT8,//40
	eNT_EXT9,
	eNT_EXT10,
	eNT_WAIT_TRAFFIC_POINT,
	eNT_CANCEL_DELIVER_AND_WAIT_FOR_GO_HOME_POINT,
	//eNT_WAIT_FOR_TO_COLLECT_GARBAGE_POINT_POINT,
	//eNT_COLLECT_GARBAGE_POINT,
	eNT_MAX,
};

//although path is inverted but same wheel with nagative speed,so just give same type is fine.
inline eNodeType	GetInvertNodeType(eNodeType e_eNodeType)
{
	return e_eNodeType;
	//if (e_eNodeType >= eNT_TURN_POUNT_R15 && e_eNodeType <= eNT_TURN_POUNT_R180)
	//{
	//	int l_iOffset = e_eNodeType - eNT_TURN_POUNT_R15;
	//	return (eNodeType)(eNT_TURN_POUNT_L15+l_iOffset);
	//}
	//else
	//if (e_eNodeType >= eNT_TURN_POUNT_L15 && e_eNodeType <= eNT_TURN_POUNT_L180)
	//{
	//	int l_iOffset = e_eNodeType - eNT_TURN_POUNT_L15;
	//	return (eNodeType)(eNT_TURN_POUNT_R15 + l_iOffset);
	//}
	//else
	//{
	//	if (e_eNodeType == eNT_TURN_POUNT_RAPID_L90)
	//		return eNT_TURN_POUNT_RAPID_R90;
	//	if (e_eNodeType == eNT_TURN_POUNT_RAPID_L180)
	//		return eNT_TURN_POUNT_RAPID_R180;
	//	if (e_eNodeType == eNT_TURN_POUNT_RAPID_R90)
	//		return eNT_TURN_POUNT_RAPID_L90;
	//	if (e_eNodeType == eNT_TURN_POUNT_RAPID_R180)
	//		return eNT_TURN_POUNT_RAPID_L180;
	//}		
	//return e_eNodeType;
}

static int16 g_si16NodeTypeSpeed[eNT_MAX] = 
{
	100,//eNT_ROAD = 0,
	0,//eNT_CUSTOMER,
	0,//eNT_CHARGE_POINT,
	0,//eNT_DELIVER_POINT,//it also is a charge point,need this one?.server need to detect the deliver point is empty and ask idle card to move to next charge point or to deliver point!?
	50,//eNT_TURN_POUNT_R15,//15
	50,//eNT_TURN_POUNT_R30,//30
	50,//eNT_TURN_POUNT_R45,//45
	50,//eNT_TURN_POUNT_R60,//60
	50,//eNT_TURN_POUNT_R75,//75
	50,//eNT_TURN_POUNT_R90,//90
	50,//eNT_TURN_POUNT_R105,//105,10
	50,//eNT_TURN_POUNT_R120,//120
	50,//eNT_TURN_POUNT_R135,//135
	50,//eNT_TURN_POUNT_R150,//150
	50,//eNT_TURN_POUNT_R165,//165
	50,//eNT_TURN_POUNT_R180,//180
	50,//eNT_TURN_POUNT_L15,//15
	50,//eNT_TURN_POUNT_L30,//30
	50,//eNT_TURN_POUNT_L45,//45
	50,//eNT_TURN_POUNT_L60,//60
	50,//eNT_TURN_POUNT_L75,//75,//20
	50,//eNT_TURN_POUNT_L90,//90
	50,//eNT_TURN_POUNT_L105,//105
	50,//eNT_TURN_POUNT_L120,//120
	50,//eNT_TURN_POUNT_L135,//135
	50,//eNT_TURN_POUNT_L150,//150
	50,//eNT_TURN_POUNT_L165,//165
	50,//eNT_TURN_POUNT_L180,//180
	50,//eNT_DUMMY_POINT_FOR_COLLISION_TEST,//180,28
	50,//eNT_TURN_POUNT_RAPID_L90,//
	50,//eNT_TURN_POUNT_RAPID_L180,//30
	50,//eNT_TURN_POUNT_RAPID_R90,//
	50,//eNT_TURN_POUNT_RAPID_R180,//
	50,//eNT_EXT1,
	50,//eNT_EXT2,
	50,//eNT_EXT3,
	50,//eNT_EXT4,
	50,//eNT_EXT5,
	50,//eNT_EXT6,
	50,//eNT_EXT7,
	50,//eNT_EXT8,40
	50,//eNT_EXT9,
	50,//eNT_EXT10,
	50,//eNT_WAIT_TRAFFIC_POINT,
	50//eNT_CANCEL_DELIVER_AND_WAIT_FOR_GO_HOME_POINT,
};


enum eCarSendingStatus
{
	eCSS_IDLE_AND_MEAL_EMPTY = 0,
	eCSS_IDLE_AND_MEAL_FILLED,
	eCSS_DRIVING,
	eCSS_CAR_GOT_ACCIDENT_STRUCK_ON_THE_WAY,
	eCSS_ARDUINO_NO_SIGNAL,
	eCSS_REVERSING,
	eCSS_RFID_NOT_CORRECT,
	//
	eCSS_CAR_HW_ERROR_LID_OPEN_FAILED,
	//
	eCSS_CAR_GET_COLLIDED,
	eCSS_MAX
};