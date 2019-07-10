#pragma once

enum eCarDrivingNetworkMessage
{
	eCDNM_S2C_TEST_MESSAGE = 0,
	eCDNM_C2S_TEST_MESSAGE,

	eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE,//HW ID
	eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT,//HW ID
	eCDNM_C2S_RFID_SINGNAL,//tag ID
	eCDNM_S2C_CAR_GO_TO_DESTINATION_ID_1,//id,int16
	eCDNM_C2S_CAR_GO_TO_DESTINATION_ID_1_RESULT,
	eCDNM_S2C_CAR_GO_TO_DESTINATION_SPEED_2,//speed,int16
	eCDNM_C2S_CAR_GO_TO_DESTINATION_SPEED_2_RESULT,
	eCDNM_S2C_CAR_GO_TO_DESTINATION_ANGLE_3,//turn angle,int8
	eCDNM_C2S_CAR_GO_TO_DESTINATION_ANGLE_3_RESULT,
	eCDNM_S2C_CAR_GO_TO_DESTINATION_DISTANCE_4,//distance,int16,1unit is 1 cm
	eCDNM_C2S_CAR_GO_TO_DESTINATION_DISTANCE_4_RESULT,
	//eCDNM_S2C_CAR_GO_TO_DESTINATION_END,//node type
	eCDNM_S2C_CAR_STOP,//emgency situation!?
	//eCDNM_S2C_CAR_WAIT,//
	//
	eCDNM_MAX
};

enum eNodeType
{
	eNT_ROAD = 0,
	eNT_CUSTOMER,
	eNT_CHARGE_POINT,
	eNT_DELIVER_POINT,//it also is a charge point,need this one?.server need to detect the deliver point is empty and ask idle card to move to next charge point or to deliver point!?
	eNT_TURN_POUNT_R15,//15
	eNT_TURN_POUNT_R30,//30
	eNT_TURN_POUNT_R45,//45
	eNT_TURN_POUNT_R60,//60
	eNT_TURN_POUNT_R75,//75
	eNT_TURN_POUNT_R90,//90
	eNT_TURN_POUNT_R105,//105
	eNT_TURN_POUNT_R120,//120
	eNT_TURN_POUNT_R135,//135
	eNT_TURN_POUNT_R150,//150
	eNT_TURN_POUNT_R165,//165
	eNT_TURN_POUNT_R180,//180
	eNT_TURN_POUNT_L15,//15
	eNT_TURN_POUNT_L30,//30
	eNT_TURN_POUNT_L45,//45
	eNT_TURN_POUNT_L60,//60
	eNT_TURN_POUNT_L75,//75
	eNT_TURN_POUNT_L90,//90
	eNT_TURN_POUNT_L105,//105
	eNT_TURN_POUNT_L120,//120
	eNT_TURN_POUNT_L135,//135
	eNT_TURN_POUNT_L150,//150
	eNT_TURN_POUNT_L165,//165
	eNT_TURN_POUNT_L180,//180
	eNT_MAX,
};

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
	50,//eNT_TURN_POUNT_R105,//105
	50,//eNT_TURN_POUNT_R120,//120
	50,//eNT_TURN_POUNT_R135,//135
	50,//eNT_TURN_POUNT_R150,//150
	50,//eNT_TURN_POUNT_R165,//165
	50,//eNT_TURN_POUNT_R180,//180
	50,//eNT_TURN_POUNT_L15,//15
	50,//eNT_TURN_POUNT_L30,//30
	50,//eNT_TURN_POUNT_L45,//45
	50,//eNT_TURN_POUNT_L60,//60
	50,//eNT_TURN_POUNT_L75,//75
	50,//eNT_TURN_POUNT_L90,//90
	50,//eNT_TURN_POUNT_L105,//105
	50,//eNT_TURN_POUNT_L120,//120
	50,//eNT_TURN_POUNT_L135,//135
	50,//eNT_TURN_POUNT_L150,//150
	50,//eNT_TURN_POUNT_L165,//165
	50//eNT_TURN_POUNT_L180,//180
};