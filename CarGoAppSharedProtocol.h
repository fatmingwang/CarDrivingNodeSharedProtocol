#pragma once

#define		NETWORK_MESSAGE_VERSION			1
#define		TCP_IP_PORT						430

#define		MESSAGE_ID_ASSIGN(TYPE,ID)TYPE():sBaseNetworkMessage(ID,sizeof(TYPE)){}
#define		RESULT_MESSAGE_ID_ASSIGN(TYPE,ID)TYPE():sBaseNetworkResultMessage(ID,sizeof(TYPE)){}



#define		LAZY_MESSAGE_HEADER_STAR(ID)						struct sNetwork##TYPE:public sBaseNetworkMessage{
#define		LAZY_MESSAGE_HEADER_END(ID)							MESSAGE_ID_ASSIGN(sNetwork##TYPE,ID)

#define		LAZY_RESULT_MESSAGE_HEADER_STAR(ID)					struct sNetwork##TYPE:public sBaseNetworkResultMessage{
#define		LAZY_RESULT_MESSAGE_HEADER_END(ID)					MESSAGE_ID_ASSIGN(sNetwork##TYPE,ID)



enum eCarGoAppNetworkMessage
{
	eCGANM_C2S_VERSION_AND_MAP_INFOR= 0,//tell me your deliver point and map infomation and else...
	eCGANM_C2S_SELECTED_DELIVER_POINT_INFO,

	eCGANM_C2S_QUERY_DELIVER_POINT_CAR_INFORMATION,//every 1 second try to fetch information.
	eCGANM_S2C_QUERY_DELIVER_POINT_CAR_INFORMATION_RESULT,
	//eCGANM_S2C_CAR_AT_DELIVER_POINT,
	//eCGANM_S2C_CAR_LEAVE_DELIVERPOINT,
	eCGANM_MAX,
};


enum eNetworkResultCode
{
	eNRC_OK = 0,
	eNRC_AUTHORITY_NOT_PERMIT,
	eNRC_USER_PWD_NOT_MATCH_ERROR,
	eNRC_MACHINE_EXISTS,
	eNRC_MACHINE_NOT_EXISTS,
	eNRC_REPORT_CODE_VERSION_NOT_MATCH,
	eNRC_REPORT_CODE_SOCKET_AND_ID_NOT_MATCH,
	eNRC_CURD_USER_EXISTS,
	eNRC_CURD_USER_NOT_EXISTS,
	eNRC_CURD_DB_FIND_ONE_ERROR,
	eNRC_CURD_DB_INSERT_ERROR,
	eNRC_CURD_DB_DELETE_ERROR,
	eNRC_CURD_DB_EXCEPTION,
	eNRC_CURD_DB_UPDATE_ERROR,
	eNRC_CURD_MAX
};

//tcpip 1 packet default maximum size is 65k

struct sBaseNetworkMessage
{
	int		iSize;
	int		iMessage;
	sBaseNetworkMessage(int e_iID,int e_iSize) :iMessage(e_iID) { iSize= e_iSize;	}
};

struct sBaseNetworkResultMessage :public sBaseNetworkMessage
{
	int		iResultCode;//basicly 0 for false 1 for true
	sBaseNetworkResultMessage(int e_iID,int e_iSize) :sBaseNetworkMessage(e_iID, e_iSize) {}
};
////=====================================
//struct sLoginMessage_eNM_C2S_LOGIN_REQUEST :public sBaseNetworkMessage
//{
//	char	strPwd[USER_PWD_LENGTH];
//	float	fVersion;
//	MESSAGE_ID_ASSIGN(sLoginMessage_eNM_C2S_LOGIN_REQUEST, eNM_C2S_LOGIN_REQUEST);
//};
//
//struct sLoginResultMessage_eNM_S2C_LOGIN_RESULT :public sBaseNetworkResultMessage
//{
//	enum eResult//for iResultCode
//	{
//		eR_NO_USER = 0,
//		eR_LOGIN_OK,
//		eR_PWD_ERROR,
//		eR_MAX
//	};
//	const char*GetResultString(eResult e_eResult)
//	{
//		if (e_eResult == eR_NO_USER)
//			return "ID not exist";
//		if (e_eResult == eR_LOGIN_OK)
//			return "Ok";
//		if (e_eResult == eR_PWD_ERROR)
//			return "Password is not correct";
//		return "sLoginResultMessage_eNM_S2C_LOGIN_RESULT::GetResultString Error";
//	}
//	//iResultCode,0 no such user,1 pw and user name correct,2 pwd is wrong
//	int		iUserAuthority;
//	int		iMachineIDArray[MAX_MACHINE_COUNT];//0 for empty
//	RESULT_MESSAGE_ID_ASSIGN(sLoginResultMessage_eNM_S2C_LOGIN_RESULT, eNM_S2C_LOGIN_RESULT);
//};
//
//struct sAddUserMessage_eNM_C2S_ADD_USER_REQUEST :public sBaseNetworkMessage
//{
//	char	strTargetID[USER_ID_LENGTH];
//	char	strPwd[USER_PWD_LENGTH];
//	char	strDescription[USER_DESCRIPTION_LENGTH];
//	MESSAGE_ID_ASSIGN(sAddUserMessage_eNM_C2S_ADD_USER_REQUEST, eNM_C2S_ADD_USER_REQUEST);
//};
//
//RESULT_STRUCT_ASSIGN(sAddUserMessage_eNM_C2S_ADD_USER_RESULT, eNM_C2S_UPDATE_USER_RESULT);
//
//struct sDeleteUserMessage_eNM_C2S_DELETE_USER_REQUEST :public sBaseNetworkMessage
//{
//	char	strTargetID[USER_ID_LENGTH];
//	char	strPwd[USER_PWD_LENGTH];//ASK pwd TO AVOID ACCIDENT.
//	MESSAGE_ID_ASSIGN(sDeleteUserMessage_eNM_C2S_DELETE_USER_REQUEST, eNM_C2S_DELETE_USER_REQUEST);
//};
//
//RESULT_STRUCT_ASSIGN(sDeleteUserMessage_eNM_S2C_DELETE_USER_RESULT, eNM_S2C_DELETE_USER_RESULT);
//
//struct sUpdateUserDataInfo_eNM_C2S_UPDATE_USER_REQUEST :public sBaseNetworkMessage
//{
//	char strTargetID[USER_ID_LENGTH];
//	char strPWD[USER_PWD_LENGTH];
//	char strNewPWD[USER_PWD_LENGTH];
//	char strDescription[USER_DESCRIPTION_LENGTH];
//	MESSAGE_ID_ASSIGN(sUpdateUserDataInfo_eNM_C2S_UPDATE_USER_REQUEST, eNM_C2S_UPDATE_USER_REQUEST);
//};
//
//RESULT_STRUCT_ASSIGN(sUpdateUserDataInfo_eNM_C2S_UPDATE_USER_RESULT, eNM_C2S_UPDATE_USER_RESULT);
//
//struct sUpdateUserOwnMachine_eNM_C2S_UPDATE_USER_OWN_MACHINE_REQUEST :public sBaseNetworkMessage
//{
//	char	strTargetID[USER_ID_LENGTH];
//	bool	bAddNewMachine;//true for add false or delete
//	int		iMachineID;
//	MESSAGE_ID_ASSIGN(sUpdateUserOwnMachine_eNM_C2S_UPDATE_USER_OWN_MACHINE_REQUEST, eNM_C2S_UPDATE_USER_OWN_MACHINE_REQUEST);
//};
//
//RESULT_STRUCT_ASSIGN(sUpdateUserDataInfo_eNM_C2S_UPDATE_USER_OWN_MACHINE_RESULT, eNM_C2S_UPDATE_USER_OWN_MACHINE_RESULT);
//
//
////bool	GenerateReportCode(char*e_strReportCodeOutData, uint64 e_i64ExchangeIn, uint64 e_i64ExchangeOut, uint64 e_iBulletCount, int e_iReportCount, sTwLeadStreamProductData e_sTwLeadStreamProductData);
//struct sCodeReportRequest_eNM_C2S_DO_CODE_REPORT_REQUEST :public sBaseNetworkMessage
//{
//	struct sNetworkworkTwLeadStreamProductData//from fish -FishGameParameterize-FISG_GAME_PARAMETERIZE::sTwLeadStreamProductData
//	{
//		int		iProductTypeNumber = 0;
//		int		iMachineID = 0;
//	};
//	uint64	i64ExchangeIn;
//	uint64  i64ExchangeOut;
//	int		iReportCount;
//	uint64  i64BulletCount;
//	char	ReportCodeVersion[10];
//	char	ParameterCode[50];
//	sNetworkworkTwLeadStreamProductData TwLeadStreamProductData;
//	MESSAGE_ID_ASSIGN(sCodeReportRequest_eNM_C2S_DO_CODE_REPORT_REQUEST, eNM_C2S_DO_CODE_REPORT_REQUEST);
//};
//
//struct sCodeReportResult_eNM_S2C_DO_CODE_REPORT_RESULT :public sBaseNetworkResultMessage
//{
//	char	strReportCodeResult[50];
//	RESULT_MESSAGE_ID_ASSIGN(sCodeReportResult_eNM_S2C_DO_CODE_REPORT_RESULT, eNM_S2C_DO_CODE_REPORT_RESULT);
//};
//
//struct sQueryUserMachineHistory_eNM_C2S_QUERY_MACHINE_HISTORY_REQUEST :public sBaseNetworkMessage
//{
//	int	iMachineID;
//	MESSAGE_ID_ASSIGN(sQueryUserMachineHistory_eNM_C2S_QUERY_MACHINE_HISTORY_REQUEST, eNM_C2S_QUERY_MACHINE_HISTORY_REQUEST);
//};
