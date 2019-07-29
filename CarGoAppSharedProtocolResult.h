#pragma once

//enum eNetworkResultCode
//{
//	eNRC_OK = 0,
//	eNRC_AUTHORITY_NOT_PERMIT,
//	eNRC_USER_PWD_NOT_MATCH_ERROR,
//	eNRC_MACHINE_EXISTS,
//	eNRC_MACHINE_NOT_EXISTS,
//	eNRC_REPORT_CODE_VERSION_NOT_MATCH,
//	eNRC_REPORT_CODE_SOCKET_AND_ID_NOT_MATCH,
//	eNRC_CURD_USER_EXISTS,
//	eNRC_CURD_USER_NOT_EXISTS,
//	eNRC_CURD_DB_FIND_ONE_ERROR,
//	eNRC_CURD_DB_INSERT_ERROR,
//	eNRC_CURD_DB_DELETE_ERROR,
//	eNRC_CURD_DB_EXCEPTION,
//	eNRC_CURD_DB_UPDATE_ERROR,
//	eNRC_CURD_MAX
//};

enum eCarGoAppSharedProtocolResult
{
	eCGASPR_OK = 0,
	eCGASPR_VERSION_NOT_MATCH,
	eCGASPR_VERSION_MAP_NAME_NOT_MATCH,
	eCGASPR_DELIVERPOINT_OCCUPIED_BY_OTHER_CAR_GO_APP,
	eCGASPR_DELIVERPOINT_NO_CAR,
	eCGASPR_SERVER_ERROR_PLEASE_RELOGIN_AGAIN,//
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
		default:
			return L"not support result";
			break;
	}
	return L"not support result";
}