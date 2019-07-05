#pragma once

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

enum eCarDrivingNetworkMessage
{
	eCDNM_S2C_TEST_MESSAGE = 0,
	eCDNM_C2S_TEST_MESSAGE,
	eCDNM_S2C_TELL_SERVER_WHO_YOU_ARE,
	eCDNM_C2S_TELL_SERVER_WHO_YOU_ARE_RESULT,
	eCDNM_C2S_RFID_SINGNAL,
	eCDNM_S2C_ALL_CAR_STOP,
	eCDNM_S2C_CAR_GO_TO_DESTINATION_1,//id
	eCDNM_S2C_CAR_GO_TO_DESTINATION_2,//time
	eCDNM_S2C_CAR_GO_TO_DESTINATION_3,//speed
	eCDNM_S2C_CAR_GO_TO_DESTINATION_END,//node type
	eCDNM_S2C_CAR_STOP,
	eCDNM_S2C_CAR_WAIT,
	//
	eCDNM_MAX
};