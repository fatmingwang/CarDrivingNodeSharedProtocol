#pragma once

#include "StreamingDataReceiver.h"

enum eArduinoRasPIMessage
{
	eARM_R2A_VERSION_REQUEST = 0,
	eARM_A2R_VERSION_RESULT,
	eARM_A2R_HWARDWARE_INFO,
	eARM_R2A_COMMAND,
	eARM_R2A_COUNT_TEST_REQUEST,
	eARM_A2R_COUNT_TEST_RESULT,
	eARM_A2R_MAX
};
//arduino is 16 bit processor
#define	PACK_SIZE	2


//#define	MOTOR_OVER_HEAT	1<<1
//#define	EXP_1			2<<1
//#define	EXP_2			3<<1

//Sep/7/2019 version 1
//remove uint32 ui32TagID from eARM_R2A_COMMAND.
//add version check.
#define		RASPI_ARDUINO_COMMUNCIATUION_VERSION	1

#pragma pack(push,PACK_SIZE)// push current alignment to stack,set alignment to n byte boundary
LAZY_HEADER_STAR(eARM_R2A_VERSION_REQUEST)
	uint32	ui32Version;
LAZY_HEADER_END(eARM_R2A_VERSION_REQUEST)
#pragma pack(pop)

#pragma pack(push,PACK_SIZE)// push current alignment to stack,set alignment to n byte boundary
LAZY_HEADER_STAR(eARM_A2R_VERSION_RESULT)
uint32	ui32Version;
LAZY_HEADER_END(eARM_A2R_VERSION_RESULT)
#pragma pack(pop)


//make sure
#pragma pack(push,PACK_SIZE)// push current alignment to stack,set alignment to n byte boundary
LAZY_HEADER_STAR(eARM_A2R_HWARDWARE_INFO)
	uint16	ui16ExpcptionCode;				//異常代碼 0=正常  1=馬達異常 2=避障感測器觸發  
	uint16  ui16motorerrorCode;				//異常代碼 0=正常  其他=異常(參考下面的馬達故障代碼表)
	uint32	ui32TagID;						//目前最新讀到的TAG ID  範圍0000000~FFFFFFF  
	uint16  ui16RfidReadStatus;				//rfid的當次迴圈的讀取狀態 1=有讀取 0=沒讀取
	uint16	ui16MealSettle;					//餐盤感測器狀態   00=沒有   01=第一節車有 10=第二節車有  11=兩節車都有     
	uint16	ui16Power;						//電池電量   0~100(%)
	int16	i16LeftSpeed;					//讀取左馬達速度 +/- 0~100(%)    
	int16	i16RightSpeed;					//讀取右馬達速度 +/- 0~100(%)  
	uint32	ui32LeftDistabce;				//讀取左馬達轉動距離 範圍0~2147483648(單位mm) 
	uint32	ui32RightDistabce;				//讀取右馬達轉動距離 範圍0~2147483648(單位mm) 
	uint16	ui16LeftMotorLoading;			//讀取左馬達負載量 範圍0~100(%) 
	uint16	ui16RightMotorLoading;			//讀取右馬達負載量 範圍0~100(%) 
	uint16	ui16ReceivedMessageCount;		//回傳arduino收到正確封包的次數
LAZY_HEADER_END(eARM_A2R_HWARDWARE_INFO)
#pragma pack(pop)

//--------------------------------
//馬達故障代碼表
//正常 = 0
//左馬達電流超過限制 = 1
//右馬達電流超過限制 = 2
//緊急停止(電路) = 3
//左馬達溫度錯誤 = 4
//右馬達溫度錯誤 = 5
//馬達電源電壓錯誤 = 6
//編碼器電源電壓過高 = 7
//編碼器電源電壓過低 = 8
//左馬達驅動異常故障 = 9
//右馬達驅動異常故障 = 10
//馬達電源電壓過高 = 11
//馬達電源電壓過低 = 12
//左馬達溫度過高(85度c) =  13
//右馬達溫度過高(85度c) =  14
//左馬達編碼器異常 = 15
//右馬達編碼器異常 = 16
//--------------------------------


#pragma pack(push,PACK_SIZE)// push current alignment to stack,set alignment to n byte boundary
LAZY_HEADER_STAR(eARM_R2A_COMMAND)
	uint16	ui16DistanceLeft;  //設定左馬達轉動距離 範圍0~2147483648(單位mm) 
	uint16	ui16DistanceRight; //設定右馬達轉動距離 範圍0~2147483648(單位mm)
	uint8	ui8AcceLeft;     //設定左馬達加速度 範圍0~300(%)
	uint8	ui8AcceRight;    //設定右馬達加速度 範圍0~300(%)
	int16	i16SpeedLeft;    //設定左馬達速度  範圍+/- 0~100(%)
	int16	i16SpeedRight;   //設定右馬達速度  範圍+/- 0~100(%)
	uint8	ui8voice;        //設定語音模組  0=停止   xx=播放"您好 xx桌的客人請取餐"*  
	uint8	ui8UseObstacleSensorProjectDistance;   //0 for sendor close, the other value for projection distance.
LAZY_HEADER_END(eARM_R2A_COMMAND)
#pragma pack(pop)

#pragma pack(push,PACK_SIZE)// push current alignment to stack,set alignment to n byte boundary
LAZY_HEADER_STAR(eARM_R2A_COUNT_TEST_REQUEST)
	uint32	ui32SendCount;
	int8	i81Start;//1,evert data add 1 for compare test.
	int16	i1610Start;//10
	int32	i32100Start;//100
LAZY_HEADER_END(eARM_R2A_COUNT_TEST_REQUEST)
//#pragma pack(pop)


#pragma pack(push,PACK_SIZE)// push current alignment to stack,set alignment to n byte boundary
LAZY_HEADER_STAR(eARM_A2R_COUNT_TEST_RESULT)
	uint32	ui32SendCount;
	int8	i81Start;//1,evert data add 1 for compare test.
	int16	i1610Start;//10
	int32	i32100Start;//100
LAZY_HEADER_END(eARM_A2R_COUNT_TEST_RESULT)
//#pragma pack(pop)



//int	SendDataTestCode(char*e_pBuffer, int e_iSizeToReceived)
//{
//	sStreamingData_eARM_A2R_HWARDWARE_INFO l_Data;
//	l_Data.i16Message;      
//	l_Data.i16PacketSize;
//	//l_Data.ui8MagicID;
//	l_Data.ui16LeftSpeed = 1;
//	l_Data.ui16LeftLoad = 2;
//	l_Data.ui16Obstacle = 3;
//	l_Data.ui16Power = 4;
//	l_Data.ui16RightSpeed = 5;
//	l_Data.ui16RightLoad = 6;
//	l_Data.ui16TagID = 7;
//
//	l_Data.i16CheckSum = BufferAndSizeGetCheckSum((char*)&l_Data, sizeof(sStreamingData_eARM_A2R_HWARDWARE_INFO));
//	char l_Garbage[3] = { 55,68,63 };
//	char l_Garbage2[3] = { 99,1,0 };
//	memcpy(e_pBuffer, l_Garbage, sizeof(l_Garbage));
//	memcpy(&e_pBuffer[3], &l_Data, sizeof(l_Data));
//	memcpy(&e_pBuffer[sizeof(l_Data) + sizeof(l_Garbage)], l_Garbage2, sizeof(l_Garbage2));
//	return sizeof(l_Data) + sizeof(l_Garbage) + sizeof(l_Garbage2);
//}
//
//inline void  ReceiveTestCode()
//{
//	sBufferAndSize l_sBufferAndSize;
//	BufferAndSizeInit(&l_sBufferAndSize);
//	char*l_pData = 0;
//	int	l_iOutSize = 0;
//	while (1)
//	{
//		char pBuffer[999];
//		//uart
//		int l_iSize = rec(pBuffer, 999);
//		if (l_iSize)
//		{
//			if (BufferAndSizeAddBuffer(&l_sBufferAndSize, pBuffer, l_iSize) != -1)
//			{
//				//do your things
//				int16 l_i16MessageID = -1;
//				l_pData = BufferAndSizeGetData(&l_sBufferAndSize, &l_iOutSize, &l_i16MessageID);
//				if (l_pData)
//				{
//					//do your things
//					if (l_i16MessageID == eARM_A2R_HWARDWARE_INFO)
//					{
//						sStreamingData_eARM_A2R_HWARDWARE_INFO*l_pFinalData = (sStreamingData_eARM_A2R_HWARDWARE_INFO*)l_pData;
//						l_pFinalData->ui16LeftLoad = 0;
//					}
//					//
//					free(l_pData);
//				}
//			}
//		}
//	}
//	BufferAndSizeFree(&l_sBufferAndSize);
//}


