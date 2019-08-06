#pragma once


enum eCarGoAppSharedProtocolResult
{
	eCGASPR_OK = 0,
	eCGASPR_VERSION_NOT_MATCH,
	eCGASPR_VERSION_MAP_NAME_NOT_MATCH,
	eCGASPR_DELIVERPOINT_OCCUPIED_BY_OTHER_CAR_GO_APP,
	eCGASPR_DELIVERPOINT_NO_CAR,
	eCGASPR_SERVER_ERROR_PLEASE_RELOGIN_AGAIN,//
	eCGASPR_CAR_GO_FAILED,
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
			return L"no cat at this deliver point";
		case eCGASPR_SERVER_ERROR_PLEASE_RELOGIN_AGAIN:
			return L"server shut down please restart app.";
		case eCGASPR_CAR_GO_FAILED:
			return L"ask car to go failed!,already received message!?";
		default:
			return L"not support result";
			break;
	}
	return L"not support result";
}

enum eCarDrivingStatus
{
	eCDS_WAIT_FOR_INITIAL = 0,//wait HW ID,basiclly it won't happen
	eCDS_WAIT_FOR_WHERE_I_AM,//fetch HW ID but have no idea where car is(lost connection and get still to re send HWID again).
	eCDS_STAY_AT_CHARGE_POINT,//some resturant may design 3 charge point at a line and the first charge point is deliver,,if deliver car left make rest car queue up and moving.
	eCDS_STAY_AT_DELIVERY_POINT,//car ready to go
	eCDS_STAY_AT_POINT,//nor charge nor deliver nor customer
	eCDS_STAY_AT_CUSTOMER_POINT,
	eCDS_STAY_AT_CUSTOMER_POINT_MEAL_IS_EMPTY_MAKE_CAR_GO_HOME,
	eCDS_WAIT_CHECK_TRAFFIC,//ask car go to some where,wait car send me it's going
	eCDS_SEND_CAR_GO_SIGNAL_TO_CAR,//traffic is safe to go then send message to car
	eCDS_WAY_TO_CUSTOMER,//
	eCDS_WAY_TO_CHARGE_POINT,//
	eCDS_WAY_TO_DELIVER_POINT,//
	eCDS_WAY_TO_POINT,//
	eCDS_WAIT_FOR_CUSTOMER_FETCH_MEAL,
	eCDS_EMRGENCY_STOP,//no reason and don't know why,for safty
	//
	eCDS_CONNECTION_LOST,//network problem
	//
	eCDS_OUT_OF_CONTROL_ASK_USER_TO_TAKE_IT_TO_FIXT_IT,//still have connection but no RFID Signal,car problem.
	eCDS_CAR_DISAPPEAR,//uset take car off
	eCDS_TRAFFIC_STUCK_WAIT_TOO_LONG,//target point was occupied by somecar?
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
	case eCDS_TRAFFIC_STUCK_WAIT_TOO_LONG:
		return L"traffic struck too long";
		break;
	default:
		return L"not support status";
		break;
	}
	return L"not support status";
}
