#pragma once


enum eCarGoAppSharedProtocolResult
{
	eCGASPR_OK = 0,
	//below for eCGANM_S2C_VERSION_AND_MAP_INFOR_RESULT
	eCGASPR_VERSION_NOT_MATCH,
	eCGASPR_VERSION_MAP_NAME_NOT_MATCH,
	//below for eCGANM_S2C_SELECTED_DELIVER_POINT_RESULT
	eCGASPR_DELIVERPOINT_OCCUPIED_BY_OTHER_CAR_GO_APP,
	eCGASPR_DELIVERPOINT_NO_CAR,
	eCGASPR_SERVER_ERROR_PLEASE_RELOGIN_AGAIN,//5
	//below for eCGANM_S2C_CAR_GO_RESULT
	eCGASPR_CAR_GO_FAILED,
	eCGASPR_CAR_NOT_EXISTS,
	eCGASPR_CAR_GATE_OPEN,
	//eCGASPR_CAR_POWER_NOT_100,
	//below for eCGANM_S2C_CANCEL_DELIVER_ORDER_RESULT
	eCGASPR_CAR_CANCEL_DELIVER_ORDER_CAR_STAY_AT_DELIVER_POINT_OK,
	eCGASPR_CAR_CANCEL_DELIVER_ORDER_STOP_AT_CANCEL_DELIVER_POINT_OK,//10
	eCGASPR_CAR_CANCEL_DELIVER_ORDER_CAR_PASS_OVER_DELIVER_POINT_FAILED,
	eCGASPR_CAR_CANCEL_DELIVER_ORDER_CAR_NOT_START_FROM_DELIVER_POINT_FAILED,
	eCGASPR_CAR_CANCEL_DELIVER_ORDER_CAR_ID_NOT_EORRECT_FAILED,
	//
	eCGASPR_CAR_IS_MOVING_NOT_ALLOW_OPEN_LID,
	//
	eCGASPR_CAR_NO_FOOD_NOT_ALLOW_TO_GO,//15
	//
	//Dec/25/2020
	eCGASPR_CAR_CANNT_OPEN_LID,
	eCGASPR_MAX
};

inline const wchar_t* ResultToString(eCarGoAppSharedProtocolResult e_eCarGoAppSharedProtocolResult)
{
	switch (e_eCarGoAppSharedProtocolResult)
	{
		case eCGASPR_OK:
			return L"Ok";
		case eCGASPR_VERSION_NOT_MATCH:
			return L"version is not matched";
		case eCGASPR_VERSION_MAP_NAME_NOT_MATCH:
			return L"map file name is not matched";
		case eCGASPR_DELIVERPOINT_OCCUPIED_BY_OTHER_CAR_GO_APP:
			return L"deliver point is occupied by other car go app";
		case eCGASPR_DELIVERPOINT_NO_CAR:
			return L"no car at this deliver point";
		case eCGASPR_SERVER_ERROR_PLEASE_RELOGIN_AGAIN:
			return L"server shut down please restart app.";
		case eCGASPR_CAR_GO_FAILED:
			return L"ask car to go failed!,already received message!?";
		case eCGASPR_CAR_CANCEL_DELIVER_ORDER_CAR_STAY_AT_DELIVER_POINT_OK:
			return L"order canceled";
		case eCGASPR_CAR_CANCEL_DELIVER_ORDER_STOP_AT_CANCEL_DELIVER_POINT_OK:
			return L"car will stop at cancel deliver point";
		case eCGASPR_CAR_CANCEL_DELIVER_ORDER_CAR_PASS_OVER_DELIVER_POINT_FAILED:
			return L"car pass over stop point,please call it back to home or wait 30 seconds car will go home.";
		case eCGASPR_CAR_CANCEL_DELIVER_ORDER_CAR_NOT_START_FROM_DELIVER_POINT_FAILED:
			return L"car not start from deliver point";
		case eCGASPR_CAR_CANCEL_DELIVER_ORDER_CAR_ID_NOT_EORRECT_FAILED:
			return L"cancel deliver order:no such car";
			break;
		case eCGASPR_CAR_IS_MOVING_NOT_ALLOW_OPEN_LID:
			return L"car is moving not allow open lid";
			break;
		case eCGASPR_CAR_NO_FOOD_NOT_ALLOW_TO_GO:
			return L"No food not allow to go";
			break;
		default:
			return L"not support result";
			break;
	}
	return L"not support result";
}

enum eCarDrivingStatus
{
	eCDS_WAIT_FOR_INITIAL = 0,//wait HW ID,basiclly it won't happen
	eCDS_WAIT_FOR_WHERE_I_AM,//fetch HW ID but have no idea where car is(lost connection and get still to re send ID again).
	eCDS_STAY_AT_CHARGE_POINT,//some resturant may design 3 charge point at a line and the first charge point is deliver,,if deliver car left make rest car queue up and moving.
	eCDS_STAY_AT_DELIVERY_POINT,//car ready to go
	eCDS_STAY_AT_POINT,//nor charge nor deliver nor customer
	eCDS_STAY_AT_CUSTOMER_POINT,//5
	eCDS_STAY_AT_CUSTOMER_POINT_MEAL_IS_EMPTY_MAKE_CAR_GO_HOME,
	//
	eCDS_WAIT_CHECK_TRAFFIC,//ask car go to some where,wait car send me it's going
	eCDS_SEND_CAR_GO_SIGNAL_TO_CAR,//traffic is safe to go then send message to car
	//
	eCDS_WAY_TO_CUSTOMER,//
	eCDS_WAY_TO_CHARGE_POINT,//10
	eCDS_WAY_TO_DELIVER_POINT,//
	eCDS_WAY_TO_POINT,//
	//
	eCDS_WAIT_FOR_CUSTOMER_FETCH_MEAL,
	eCDS_EMRGENCY_STOP,//no reason and don't know why,for safty
	//
	eCDS_CONNECTION_LOST,//network problem,15
	//
	eCDS_OUT_OF_CONTROL_ASK_USER_TO_TAKE_IT_TO_FIXT_IT,//still have connection but no RFID Signal or else,car got problem.
	eCDS_CAR_ARDUINI_NOT_WORKING,
	eCDS_CAR_REMOVED_FROME_MAP,//uset take car off
	eCDS_TRAFFIC_STUCK_WAIT_TOO_LONG,//target point was occupied by somecar?
	//add at Feb/02/2020.new function for cat stop at specific point for go home or to customer point
	eCDS_WAY_TO_DELIVER_TRAFFIC_WAIT_POINT,//20
	eCDS_WAY_TO_CANCEL_DELIVER_AND_WAIT_FOR_GO_HOME_POINT,//
	eCDS_STAY_AT_WAIT_TRAFFIC_POINT,
	eCDS_STAY_AT_CANCEL_DELIVER_AND_WAIT_FOR_GO_HOME_POINT,//23
	//eCDS_CAR_SEND_STATUS_INFO_TIME_OUT,//24
	//
	//eCDS_STAY_AT_COLLECT_GARBAGE_POINT,
	//eCDS_WAY_TO_COLLECT_GARBAGE,
	//eCDS_WAIT_FOR_COLLECT_GARBAGE,
	//eCDS_WAIT_FOR_COLLECT_GARBAGE,
	eCDS_MAX
};


inline const wchar_t * GetCarDrivingStatusString(eCarDrivingStatus e_eCarDrivingStatus)
{
	switch (e_eCarDrivingStatus)
	{
	case eCDS_WAIT_FOR_INITIAL:
		return L"wait for init";
		break;
	case eCDS_WAIT_FOR_WHERE_I_AM:
		return L"wait for where I am";
		break;
	case eCDS_STAY_AT_CHARGE_POINT:
		return L"stay at chage point";
		break;
	case eCDS_STAY_AT_DELIVERY_POINT:
		return L"stay at deliver point";
		break;
	case eCDS_STAY_AT_POINT:
		return L"stay at point";
		break;
	case eCDS_STAY_AT_CUSTOMER_POINT_MEAL_IS_EMPTY_MAKE_CAR_GO_HOME:
		return L"stay at customer point and meal is empty,ready to home";
		break;
	case eCDS_STAY_AT_CUSTOMER_POINT:
		return L"stay at cusomter point";
		break;
	case eCDS_WAIT_CHECK_TRAFFIC:
		return L"check traffic";
		break;
	case eCDS_SEND_CAR_GO_SIGNAL_TO_CAR:
		return L"send car go message to car";
		break;
	case eCDS_WAY_TO_CUSTOMER://
		return L"way to customer";
		break;
	case eCDS_WAY_TO_CHARGE_POINT://
		return L"way to charge point";
		break;
	case eCDS_WAY_TO_DELIVER_POINT://
		return L"way to deliver point";
		break;
	case eCDS_WAY_TO_POINT://
		return L"way to point";
		break;
	case eCDS_WAIT_FOR_CUSTOMER_FETCH_MEAL:
		return L"wait for customer fetch meal";
		break;
	case eCDS_EMRGENCY_STOP:
		return L"emgency stop";
		break;
	case eCDS_CONNECTION_LOST:
		return L"lost connection";
		break;
	case eCDS_OUT_OF_CONTROL_ASK_USER_TO_TAKE_IT_TO_FIXT_IT:
		return L"out of control ask user to take to fix it";
		break;
	case eCDS_CAR_ARDUINI_NOT_WORKING:
		return L"Car Arduino no signal";
		break;
	case eCDS_CAR_REMOVED_FROME_MAP:
		return L"car removed";
		break;
	case eCDS_TRAFFIC_STUCK_WAIT_TOO_LONG:
		return L"traffic struck too long";
		break;
	case eCDS_WAY_TO_DELIVER_TRAFFIC_WAIT_POINT:
		return L"way to deliver traffic wait point";
		break;
	case eCDS_WAY_TO_CANCEL_DELIVER_AND_WAIT_FOR_GO_HOME_POINT:
		return L"way to chancel deliver and go home point";
		break;
	case eCDS_STAY_AT_WAIT_TRAFFIC_POINT:
		return L"stay at wait traffic point";
		break;
	case eCDS_STAY_AT_CANCEL_DELIVER_AND_WAIT_FOR_GO_HOME_POINT:
		return L"stay at chancel deliver and go home point";
		break;
	//case eCDS_CAR_SEND_STATUS_INFO_TIME_OUT:
	//	return L"car send status info time out";
	//	break;
	default:
		return L"not support status";
		break;
	}
	return L"not support status";
}


inline bool IsCarDriving(eCarDrivingStatus e_eCarDrivingStatus)
{
	if (e_eCarDrivingStatus == eCDS_WAY_TO_CUSTOMER ||
		e_eCarDrivingStatus == eCDS_WAY_TO_CHARGE_POINT ||
		e_eCarDrivingStatus == eCDS_WAY_TO_DELIVER_POINT ||
		e_eCarDrivingStatus == eCDS_WAY_TO_POINT ||
		e_eCarDrivingStatus == eCDS_SEND_CAR_GO_SIGNAL_TO_CAR ||
		e_eCarDrivingStatus == eCDS_WAY_TO_DELIVER_TRAFFIC_WAIT_POINT ||
		e_eCarDrivingStatus == eCDS_WAY_TO_CANCEL_DELIVER_AND_WAIT_FOR_GO_HOME_POINT)
		return true;
	return false;
}
