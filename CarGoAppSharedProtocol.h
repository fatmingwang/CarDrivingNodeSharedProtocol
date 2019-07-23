#pragma once

#include "CarGoAppSharedProtocolResult.h"

#define		CAR_GO_APP_NETWORK_MESSAGE_VERSION			1
#define		TCP_IP_PORT									430

#define		MESSAGE_ID_ASSIGN(TYPE,ID)TYPE():sBaseNetworkMessage(ID,sizeof(TYPE)){memset(this,0,sizeof(TYPE));}};
#define		RESULT_MESSAGE_ID_ASSIGN(TYPE,ID)TYPE():sBaseNetworkResultMessage(ID,sizeof(TYPE)){}};



#define		LAZY_MESSAGE_HEADER_STAR(ID)						struct sNetwork##ID:public sBaseNetworkMessage{
#define		LAZY_MESSAGE_HEADER_END(ID)							MESSAGE_ID_ASSIGN(sNetwork##ID,ID)

#define		LAZY_RESULT_MESSAGE_HEADER_STAR(ID)					struct sNetwork##ID:public sBaseNetworkResultMessage{
#define		LAZY_RESULT_MESSAGE_HEADER_END(ID)					RESULT_MESSAGE_ID_ASSIGN(sNetwork##ID,ID)

#define		MAP_NAME_ARRAY_LENGTH		20
#define		DELIVER_POINT_DATA_LENGTH	20
#define		CUSTOMER_POINT_DATA_LENGTH	80

enum eCarGoAppNetworkMessage
{
	eCGANM_C2S_VERSION_AND_MAP_INFOR= 0,//tell me your deliver point and map infomation and else...
	eCGANM_S2C_VERSION_AND_MAP_INFOR_RESULT,
	eCGANM_C2S_SELECTED_DELIVER_POINT_INFO,

	eCGANM_C2S_QUERY_DELIVER_POINT_CAR_INFORMATION,//every 1 second try to fetch information.
	eCGANM_S2C_QUERY_DELIVER_POINT_CAR_INFORMATION_RESULT,
	//eCGANM_S2C_CAR_AT_DELIVER_POINT,
	//eCGANM_S2C_CAR_LEAVE_DELIVERPOINT,
	eCGANM_MAX,
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
LAZY_MESSAGE_HEADER_STAR(eCGANM_C2S_VERSION_AND_MAP_INFOR)
	int		iVersion;
	char	strMapName[MAP_NAME_ARRAY_LENGTH];
LAZY_MESSAGE_HEADER_END(eCGANM_C2S_VERSION_AND_MAP_INFOR)
//

LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_VERSION_AND_MAP_INFOR_RESULT)
	int	iDeliverPointNodeID[DELIVER_POINT_DATA_LENGTH];
	int	iCustomerPointNodeID[CUSTOMER_POINT_DATA_LENGTH];
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_VERSION_AND_MAP_INFOR_RESULT)


LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_C2S_QUERY_DELIVER_POINT_CAR_INFORMATION)
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_C2S_QUERY_DELIVER_POINT_CAR_INFORMATION)

LAZY_RESULT_MESSAGE_HEADER_STAR(eCGANM_S2C_QUERY_DELIVER_POINT_CAR_INFORMATION_RESULT)
	bool	bDeliverPointOccupied[DELIVER_POINT_DATA_LENGTH];
LAZY_RESULT_MESSAGE_HEADER_END(eCGANM_S2C_QUERY_DELIVER_POINT_CAR_INFORMATION_RESULT)