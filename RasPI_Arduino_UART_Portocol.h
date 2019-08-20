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
	int		iExpcptionCode;//
	uint16	ui16TagID;
	char	i8Obstacle;
	char	i8MealSettle;
	char	i8Power;
	int16	i16LeftSpeed;//-100,100
	int16	i16RightSpeed;//-100,100
	uint16	ui16LeftDistabce;
	uint16	ui16RightDistabce;
	char	i8LeftMotorLoading;
	char	i8RightMotorLoading;
LAZY_HEADER_END(eARM_A2R_HWARDWARE_INFO)
#pragma pack()     /* cancel previous alignment to n byte boundary */ 


#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to n byte boundary */
LAZY_HEADER_STAR(eARM_R2A_COMMAND)
	int iDistance;
	int iAcceLeft;
	int iAcceRight;
	int iSpeedLeft;
	int iSpeedRight;
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