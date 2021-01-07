#pragma once

#include "SharedProtocolCommonDefine.h"
#include "CarDrivingSharedProtocol.h"

#define	TEST_APP_NETWORK_VERSION		20210107

#define	DB_SERVER_TCPIP_PORT			9991

#define	CAR_ID_LENGTH_FOR_DB			20
#define	TESTER_ID_LENGTH_FOR_DB			20

#define	CAR_TESULT_COUNT				20
//#define	COLLECTION_ID_LENGTH_FOR_DB		20

//
//
//Car									CAR
//CarDriving server is server			S
//Mongo DB server is client				DBS
//TestApp	is client					TA
//
//
enum eTestAppNetworkMessageEnum
{
	eTANME_C2S_TELL_CDS_WHO_YOU_ARE_REQUEST = 20000,
	eTANME_S2C_TELL_CDS_WHO_YOU_ARE_RESULT,
	//test app to Car server then to DB.
	eTANME_TA2S2DBS_CREATE_NEW_TEST_REQUEST,
	//db to server then to test app.
	eTANME_DBS2S2TA_CREATE_NEW_TEST_RESULT,
	//car server to DB and TA(car to CDS)
	eTANME_CDS2DBS_ADD_CAR_ROUTE_DATA_REQUEST,
	eTANME_DBS2CDS_ADD_CAR_ROUTE_DATA_RESULT,
	//
	eTANME_TA2S_TEST_STATUS_CHANGE_REQUEST,
	eTANME_S2TA_TEST_STATUS_CHANGE_RESULT,
	//
	//server to db and Test app
	eTANME_CDS2DBS_UPDATE_TEST_RESULT_REQUEST,
	eTANME_DBS2CDS_UPDATE_TEST_RESULT_RESULT,
	//
	eTANME_TA2DBS_QUERY_CAR_RESULT_HISTORY_REQUEST,
	eTANME_DBS2TA_QUERY_CAR_RESULTHISTORY_RESULT,

	eTANME_MAX
};

enum eTestAppNetworkResultEnum
{
	eTANRE_OK = 0,
	//for no reason,I am lazy.
	eTANRE_LAZY_FAILED,
	eTANRE_VER_NOT_MATCH,
	eTANRE_DBS_NOT_EXITS,
	eTANRE_TA_NOT_EXITS,
	eTANRE_MAX,
};

enum eTestResult
{
	eTR_NOT_FINISH = 0,
	eTR_PASS,
	eTR_FAILED,
	eTR_MAX
};


static const char* g_strTestResultString[eTestResult::eTR_MAX] = {
	"not finish",
	"Pass",
	"Failed"
};

inline const char* GetTestResultString(int e_iValue)
{
	if (e_iValue > -1 && e_iValue < eTR_MAX)
	{
		return g_strTestResultString[e_iValue];
	}
	return "unsupport TestResult value";
}

inline eTestResult GetTestResult(const char*e_strResult)
{
	for (int i = 0; i < eTestResult::eTR_MAX; ++i)
	{
		if (!strcmp(e_strResult, g_strTestResultString[i]))
		{
			return (eTestResult)i;
		}
	}
	return eTestResult::eTR_MAX;
}

enum eTestApp_WhoIAm
{
	eTA_UNKNOW = 0,
	eTA_TA,
	eTA_CDS,
	eTA_DB,
	eTA_MAX,
};
#pragma pack(push,1)
LAZY_MESSAGE_HEADER_STAR(eTANME_C2S_TELL_CDS_WHO_YOU_ARE_REQUEST)
	int	iRole;//eTestApp_WhoIAm
	int	iVer;//TEST_APP_NETWORK_VERSION
LAZY_MESSAGE_HEADER_END(eTANME_C2S_TELL_CDS_WHO_YOU_ARE_REQUEST)
#pragma pack(pop)

//eTestAppNetworkResultEnum
#pragma pack(push,1)
LAZY_RESULT_MESSAGE_HEADER_STAR(eTANME_S2C_TELL_CDS_WHO_YOU_ARE_RESULT)
LAZY_RESULT_MESSAGE_HEADER_END(eTANME_S2C_TELL_CDS_WHO_YOU_ARE_RESULT)
#pragma pack(pop)



#pragma pack(push,1)
LAZY_MESSAGE_HEADER_STAR(eTANME_TA2S2DBS_CREATE_NEW_TEST_REQUEST)
	char	strCarID[CAR_ID_LENGTH_FOR_DB];
	char	strTesterID[TESTER_ID_LENGTH_FOR_DB];
LAZY_MESSAGE_HEADER_END(eTANME_TA2S2DBS_CREATE_NEW_TEST_REQUEST)
#pragma pack(pop)

#pragma pack(push,1)
LAZY_RESULT_MESSAGE_HEADER_STAR(eTANME_DBS2S2TA_CREATE_NEW_TEST_RESULT)
	char	strCarID[CAR_ID_LENGTH_FOR_DB];
	char	strTesterID[TESTER_ID_LENGTH_FOR_DB];
	int		iNumPassed;
	int		iNumFailed;
	int		iNumTested;
	//key filter
	int64	i64StartTime;
LAZY_RESULT_MESSAGE_HEADER_END(eTANME_DBS2S2TA_CREATE_NEW_TEST_RESULT)
#pragma pack(pop)


LAZY_MESSAGE_HEADER_STAR(eTANME_CDS2DBS_ADD_CAR_ROUTE_DATA_REQUEST)
	//key filter
	int64	i64StartTime;
	int		iDataCount;
	char    strRouteName[PATH_NAME_LENGTH];
	sCarDrivingPathData Data[ROUTE_KEY_POINT_DATA_LENGTH];
LAZY_MESSAGE_HEADER_END(eTANME_CDS2DBS_ADD_CAR_ROUTE_DATA_REQUEST)


LAZY_MESSAGE_HEADER_STAR(eTANME_CDS2DBS_UPDATE_TEST_RESULT_REQUEST)
	//key filter
	int64	i64StartTime;
	int64	i64EndTime;
	int		iTestResult;//eTestResult
LAZY_MESSAGE_HEADER_END(eTANME_CDS2DBS_UPDATE_TEST_RESULT_REQUEST)


enum eCarServerTestStatus
{
	eCSTS_NONE = 0,
	eCSTS_START,
	eCSTS_PAUSE,
	eCSTS_STOP,
	eCSTS_FINISH,
	eCSTS_MAX,
};

LAZY_MESSAGE_HEADER_STAR(eTANME_TA2S_TEST_STATUS_CHANGE_REQUEST)
	int iStatus;//eCarServerTestStatus
LAZY_MESSAGE_HEADER_END(eTANME_TA2S_TEST_STATUS_CHANGE_REQUEST)

LAZY_RESULT_MESSAGE_HEADER_STAR(eTANME_S2TA_TEST_STATUS_CHANGE_RESULT)
LAZY_RESULT_MESSAGE_HEADER_END(eTANME_S2TA_TEST_STATUS_CHANGE_RESULT)



struct sTestResult
{
	int		iTestResult;;//eTestResult
	int64	i64Time;
};
LAZY_MESSAGE_HEADER_STAR(eTANME_TA2DBS_QUERY_CAR_RESULT_HISTORY_REQUEST)
	char	strCarID[CAR_ID_LENGTH_FOR_DB];
LAZY_MESSAGE_HEADER_END(eTANME_TA2DBS_QUERY_CAR_RESULT_HISTORY_REQUEST)

LAZY_MESSAGE_HEADER_STAR(eTANME_DBS2TA_QUERY_CAR_RESULTHISTORY_RESULT)
	char		strCarID[CAR_ID_LENGTH_FOR_DB];
	int			iCount;
	sTestResult	TestResult[CAR_TESULT_COUNT];
LAZY_MESSAGE_HEADER_END(eTANME_DBS2TA_QUERY_CAR_RESULTHISTORY_RESULT)