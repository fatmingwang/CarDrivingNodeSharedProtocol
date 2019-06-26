#pragma once


enum eNodeType
{
	eNT_ROAD = 0,
	eNT_CUSTOMER,
	eNT_CHARGE_POINT,
	eNT_DELIVER_POINT,//need this one?.server need to detect the deliver point is empty and ask idle card to move to next charge point or to deliver point!?
	eNT_MAX,
};




struct sNodeData
{
	uint8	i8NodeType;//eNodeType
	uint16	ui16Speed;
	uint16	i16ID;
};