#pragma once

#include "SharedProtocolCommonDefine.h"
#include "CarDrivingSharedProtocol.h"

#define	DB_SERVER_TCPIP_PORT			9991

#define	CAR_ID_LENGTH_FOR_DB			20
#define	TESTER_ID_LENGTH_FOR_DB			20

#define	CAR_TESULT_COUNT				20
//#define	COLLECTION_ID_LENGTH_FOR_DB		20

//
//
//Car									CAR
//CarDriving server is client			CDS
//Mongo DB server is server				DBS
//TestApp								TA
//
//
enum eCarDrivingServerToDBServerMessage
{
	//test app to DB and Car server.
	eCDSTDBSM_TA2CDS_DBS_CREATE_NEW_TEST_REQUEST = 200000,
	//db and server return ok to test app?
	eCDSTDBSM_DBS2TA_CREATE_NEW_TEST_RESULT,
	//car to car server to DB
	eCDSTDBSM_CDS2DBS_ADD_CAR_ROUTE_DATA_REQUEST,
	eCDSTDBSM_DBS2CDS_ADD_CAR_ROUTE_DATA_RESULT,
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