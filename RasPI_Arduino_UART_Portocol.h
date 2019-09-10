#pragma once

#include "StreamingDataReceiver.h"

enum eArduinoRasPIMessage
{
	eARM_A2R_HWARDWARE_INFO = 0,
	eARM_R2A_COMMAND,
	eARM_A2R_MAX
};

#define	MOTOR_OVER_HEAT	1<<1
#define	EXP_1			2<<1
#define	EXP_2			3<<1
//make sure
#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to n byte boundary */
LAZY_HEADER_STAR(eARM_A2R_HWARDWARE_INFO)
	uint16		ui16ExpcptionCode;  //   異常代碼 0=正常  1=馬達異常 2=避障感測器觸發  
	uint32	ui32TagID;      //目前最新讀到的TAG ID  範圍0000000~FFFFFFF  
  uint16  ui16RfidReadStatus; //rfid的當次迴圈的讀取狀態 1=有讀取 0=沒讀取
//	uint16	i8Obstacle;   //合併到異常代碼中  
	uint16	ui16MealSettle;   //餐盤感測器狀態   00=沒有   01=第一節車有 10=第二節車有  11=兩節車都有     
	uint16	ui16Power;        //電池電量   0~100(%)
	int16	  i16LeftSpeed;//讀取左馬達速度 +/- 0~100(%)    
	int16	  i16RightSpeed;//讀取右馬達速度 +/- 0~100(%)  
	uint32	ui32LeftDistabce;   //讀取左馬達轉動距離 範圍0~2147483648(單位mm) 
	uint32	ui32RightDistabce;  //讀取右馬達轉動距離 範圍0~2147483648(單位mm) 
	uint16	ui16LeftMotorLoading;   //讀取左馬達負載量 範圍0~100(%) 
	uint16	ui16RightMotorLoading;  //讀取右馬達負載量 範圍0~100(%) 
	uint16	ui16ReceivedMessageCount;//回傳arduino收到正確封包的次數
LAZY_HEADER_END(eARM_A2R_HWARDWARE_INFO)
#pragma pack()     /* cancel previous alignment to n byte boundary */ 


#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to n byte boundary */
LAZY_HEADER_STAR(eARM_R2A_COMMAND)
	uint32 ui32DistanceLeft;  //設定左馬達轉動距離 範圍0~2147483648(單位mm) 
	uint32 ui32DistanceRight; //設定右馬達轉動距離 範圍0~2147483648(單位mm)
  uint16 ui16AcceLeft;     //設定左馬達加速度 範圍0~300(%)
	uint16 ui16AcceRight;    //設定右馬達加速度 範圍0~300(%)
	int16  i16SpeedLeft;    //設定左馬達速度  範圍+/- 0~100(%)
	int16  i16SpeedRight;   //設定右馬達速度  範圍+/- 0~100(%)
	uint16 ui16voice;        //設定語音模組  0=停止 1=撥放  *之後預定修改成播放"xx桌的客人請取餐",請送出xx*  
	uint32 ui32TagID;   //設定目標TAG ID  範圍0000000~FFFFFFF  
LAZY_HEADER_END(eARM_R2A_COMMAND)
#pragma pack()     /* cancel previous alignment to n byte boundary */ 





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
