#pragma once

enum eAskCarGoResultMessage
{
	eACGRM_OK = 0,
	eACGRM_VERSION_NOT_MATCH,
	eACGRM_MAP_NOT_MATCH,
	eACGRM_NO_SUCH_HW_ID,
	eACGRM_LOST_CONNECTION,
	eACGRM_CAR_DRIVING,
	eACGRM_WAIT_CUSTOMER_FETCH_MEAL,
	eACGRM_CAR_WAITING_TRAFFIC,
	eACGRM_CAR_NOT_AT_POINT,//not expected car node ID,eCGANM_C2S_COLLECT_PLATE_FINISH_REQUEST
	eACGRM_ASK_TO_GO_AGAIN,//in eACGRM_CAR_WAITING_TRAFFIC status.
	eACGRM_ASK_TO_GO_DATA_IS_NOT_CORRECT,
	eACGRM_OUT_OF_CONTROL,//some object is not exists(nullptr)
	eACGRM_NO_ROUTE_DATA,
	eACGRM_NODE_ID_WRONG,//eCGANM_C2S_ASK_CAR_TO_COLLECT_PLATE_REQUEST
	eACGRM_COLLECT_PLATE_TARGET_DELIVER_NODE_ID_WRONG,
	eACGRM_MAX
};

inline const char*GetAskCarGoResultMessageString(eAskCarGoResultMessage e_eAskCarGoResultMessage)
{
	switch (e_eAskCarGoResultMessage)
	{
		case eACGRM_OK:
			return "Ok";
		case eACGRM_NO_SUCH_HW_ID:
			return "no ID";
		case eACGRM_LOST_CONNECTION:
			return "lost connection";
		case eACGRM_CAR_DRIVING:
			return "car is on the way";
		case eACGRM_WAIT_CUSTOMER_FETCH_MEAL:
			return "waitting for customer fetch meal";
		case eACGRM_CAR_WAITING_TRAFFIC:
			return "waitting for traffic";
		case eACGRM_CAR_NOT_AT_POINT:
			return "car's current node ID is not as expected";
		case eACGRM_ASK_TO_GO_AGAIN:
			return "car already have go to destination command";
		case eACGRM_ASK_TO_GO_DATA_IS_NOT_CORRECT:
			return "ask to go route data is not correct";
		case eACGRM_OUT_OF_CONTROL:
			return "out of control";
		case eACGRM_NO_ROUTE_DATA:
			return "route data is not correct";
		case eACGRM_NODE_ID_WRONG:
			return "Node ID is wrong";
		case eACGRM_COLLECT_PLATE_TARGET_DELIVER_NODE_ID_WRONG:
			return "collect plate node ID is wrong";
		default:
			return "not supporn result";
	}
	return "not supporn result";
}