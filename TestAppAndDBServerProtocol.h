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
//CarDriving server is server			CDS
//Mongo DB server is client				DBS
//TestApp	is client					TA
//
//
enum eCarDrivingServerToDBServerMessage
{
	eCDSTDBSM_TELL_CDS_WHO_YOU_ARE = 20000,
	//test app to DB and Car server.
	eCDSTDBSM_TA2CDS_DBS_CREATE_NEW_TEST_REQUEST,
	//db and server return ok to test app?
	eCDSTDBSM_DBS2TA_CREATE_NEW_TEST_RESULT,
	//car server to DB and TA(car to CDS)
	eCDSTDBSM_CDS2DBS_ADD_CAR_ROUTE_DATA_REQUEST,
	eCDSTDBSM_DBS2CDS_ADD_CAR_ROUTE_DATA_RESULT,
	//
	//server to db and Test app
	eCDSTDBSM_CDS2DBS_UPDATE_TEST_RESULT_REQUEST,
	eCDSTDBSM_DBS2CDS_UPDATE_TEST_RESULT_RESULT,
	//
	eCDSTDBSM_TA2DBS_QUERY_CAR_RESULT_HISTORY_REQUEST,
	eCDSTDBSM_DBS2TA_QUERY_CAR_RESULTHISTORY_RESULT,

	eCDSTDBSM_MAX
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
LAZY_MESSAGE_HEADER_STAR(eCDSTDBSM_TELL_CDS_WHO_YOU_ARE)
	int	iRole;//eTestApp_WhoIAm
	int	iVer;//TEST_APP_NETWORK_VERSION
LAZY_MESSAGE_HEADER_END(eCDSTDBSM_TELL_CDS_WHO_YOU_ARE)
#pragma pack(pop)

#pragma pack(push,1)
LAZY_MESSAGE_HEADER_STAR(eCDSTDBSM_TA2CDS_DBS_CREATE_NEW_TEST_REQUEST)
	char	strCarID[CAR_ID_LENGTH_FOR_DB];
	char	strTesterID[TESTER_ID_LENGTH_FOR_DB];
	//key filter
	//int64	i64StartTime;
LAZY_MESSAGE_HEADER_END(eCDSTDBSM_TA2CDS_DBS_CREATE_NEW_TEST_REQUEST)
#pragma pack(pop)

#pragma pack(push,1)
LAZY_RESULT_MESSAGE_HEADER_STAR(eCDSTDBSM_DBS2TA_CREATE_NEW_TEST_RESULT)
	char	strCarID[CAR_ID_LENGTH_FOR_DB];
	char	strTesterID[TESTER_ID_LENGTH_FOR_DB];
	int		iNumPassed;
	int		iNumFailed;
	int		iNumTested;
	//key filter
	int64	i64StartTime;
LAZY_RESULT_MESSAGE_HEADER_END(eCDSTDBSM_DBS2TA_CREATE_NEW_TEST_RESULT)
#pragma pack(pop)


LAZY_MESSAGE_HEADER_STAR(eCDSTDBSM_CDS2DBS_ADD_CAR_ROUTE_DATA_REQUEST)
	//key filter
	int64	i64StartTime;
	int		iDataCount;
	char    strRouteName[PATH_NAME_LENGTH];
	sCarDrivingPathData Data[ROUTE_KEY_POINT_DATA_LENGTH];
LAZY_MESSAGE_HEADER_END(eCDSTDBSM_CDS2DBS_ADD_CAR_ROUTE_DATA_REQUEST)


LAZY_MESSAGE_HEADER_STAR(eCDSTDBSM_CDS2DBS_UPDATE_TEST_RESULT_REQUEST)
	//key filter
	int64	i64StartTime;
	int64	i64EndTime;
	int		iTestResult;//eTestResult
LAZY_MESSAGE_HEADER_END(eCDSTDBSM_CDS2DBS_UPDATE_TEST_RESULT_REQUEST)

struct sTestResult
{
	int		iTestResult;;//eTestResult
	int64	i64Time;
};
LAZY_MESSAGE_HEADER_STAR(eCDSTDBSM_TA2DBS_QUERY_CAR_RESULT_HISTORY_REQUEST)
	char	strCarID[CAR_ID_LENGTH_FOR_DB];
LAZY_MESSAGE_HEADER_END(eCDSTDBSM_TA2DBS_QUERY_CAR_RESULT_HISTORY_REQUEST)

LAZY_MESSAGE_HEADER_STAR(eCDSTDBSM_DBS2TA_QUERY_CAR_RESULTHISTORY_RESULT)
	char		strCarID[CAR_ID_LENGTH_FOR_DB];
	int			iCount;
	sTestResult	TestResult[CAR_TESULT_COUNT];
LAZY_MESSAGE_HEADER_END(eCDSTDBSM_DBS2TA_QUERY_CAR_RESULTHISTORY_RESULT)