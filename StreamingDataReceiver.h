//#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef int8
#define int8 char
#endif

#ifndef int16
#define int16 short
#endif

#ifndef uint8
#define uint8 unsigned char
#endif
#ifndef uint16
#define uint16 unsigned short
#endif

#ifndef int32
#define int32 long
#endif

#ifndef uint32
#define uint32 unsigned long
#endif

#define		LAZY_HEADER_STAR(ID)			struct sStreamingData_##ID{int8 i8MagicID[MAGIC_ID_COUNT]; int16	i16PacketSize; uint16	i16CheckSum; int16 i16Message;


#ifdef RPI
#define		LAZY_HEADER_END(ID)				sStreamingData_##ID(){ memset(this,0,sizeof(sStreamingData_##ID));ASSIGN_MAGIC_ID(i8MagicID);i16PacketSize = sizeof(sStreamingData_##ID); i16CheckSum = 0;i16Message = ID;} };
#else
#define    LAZY_HEADER_END(ID)      };                            \
void Init_sStreamingData_##ID(sStreamingData_##ID*e_pInData)      \
{                                                                 \
  memset(e_pInData,0,sizeof(sStreamingData_##ID));                \
  ASSIGN_MAGIC_ID(e_pInData->i8MagicID);                          \
  e_pInData->i16PacketSize = sizeof(sStreamingData_##ID);         \
  e_pInData->i16CheckSum = 0;                                     \
  e_pInData->i16Message = ID;                                    \
}
#endif


#define		MAGIC_ID_COUNT					4
#define		MAGIC_ID_SIZE					(sizeof(int8)*MAGIC_ID_COUNT)
#define		PACKET_SIZE_SIZE				sizeof(int16)
#define		CHECK_SUM_SIZE					sizeof(uint16)
#define		MESSAGE_ID_SIZE					sizeof(int16)
#define		HEADER_SIZE						(MAGIC_ID_SIZE+PACKET_SIZE_SIZE+CHECK_SUM_SIZE+MESSAGE_ID_SIZE)

#define		MAGIC_ID_INDEX					0
#define		PACKET_SIZE_INDEX				MAGIC_ID_SIZE
#define		CHECK_SUM_INDEX					(PACKET_SIZE_INDEX+PACKET_SIZE_SIZE)
#define		MESSAGE_ID_INDEX				(CHECK_SUM_INDEX+sizeof(uint16))



const static int8	g_i8StreamingDataMagicID[MAGIC_ID_COUNT] = { 55,68,63,80 };
#define		ASSIGN_MAGIC_ID(Data)			memcpy(Data, g_i8StreamingDataMagicID,MAGIC_ID_SIZE);


inline int BufferAndSizeGetCheckSum(char*e_pData,int e_iSize)
{
	int l_iCheckSum = 0;
	for (int i = 0; i < e_iSize; ++i)
	{
		l_iCheckSum += e_pData[i];
	}
	return l_iCheckSum;
}
#define	NUM_MAGIC_ID_MATCHED	10
typedef struct sBufferAndSize sBufferAndSize;
struct sBufferAndSize
{
	char*	pBuffer;
	int		iSize;
};

inline void	BufferAndSizeInit(sBufferAndSize*e_pStreamingDataReceiver){e_pStreamingDataReceiver->pBuffer = 0; e_pStreamingDataReceiver->iSize = 0;}
inline void	BufferAndSizeFree(sBufferAndSize*e_pStreamingDataReceiver)
{
	if (e_pStreamingDataReceiver->pBuffer)
	{
		free(e_pStreamingDataReceiver->pBuffer);
		e_pStreamingDataReceiver->pBuffer = 0;
	}
	e_pStreamingDataReceiver->iSize = 0; 
}
inline void	BufferAndSizeRemoveBuffer(sBufferAndSize*e_pStreamingDataReceiver,int e_iSize)
{
	char*l_pNewBuffer = 0;
	int l_iNewSize = e_pStreamingDataReceiver->iSize-e_iSize;
	if (l_iNewSize == 0)
	{
		BufferAndSizeFree(e_pStreamingDataReceiver);
		return;
	}
	l_pNewBuffer = (char*)malloc(l_iNewSize);
	memcpy(l_pNewBuffer, &e_pStreamingDataReceiver->pBuffer[e_iSize], l_iNewSize);
	BufferAndSizeFree(e_pStreamingDataReceiver);
	e_pStreamingDataReceiver->pBuffer = l_pNewBuffer;
	e_pStreamingDataReceiver->iSize = l_iNewSize;
}
inline int		BufferAndSizeAddBuffer(sBufferAndSize*e_pStreamingDataReceiver, char*e_pNewBuffer, int e_iSize)
{
	if (e_iSize < 1)
		return -1;
	int l_iNewSize = e_iSize + e_pStreamingDataReceiver->iSize;
	char*l_pNewBuffer = 0;
	//old data over 4k???remove old data
	if (l_iNewSize > 4096)
	{
		printf("buffer over 4096 bytes");
		BufferAndSizeFree(e_pStreamingDataReceiver);
		return -1;
	}
	//malloc old and new buffer size
	l_pNewBuffer = (char*)malloc(l_iNewSize);
	//copy old
	if (e_pStreamingDataReceiver->iSize > 0)
		memcpy(l_pNewBuffer, e_pStreamingDataReceiver->pBuffer, e_pStreamingDataReceiver->iSize);
	//copy new
	memcpy(&l_pNewBuffer[e_pStreamingDataReceiver->iSize], e_pNewBuffer, e_iSize);
	//free old
	BufferAndSizeFree(e_pStreamingDataReceiver);
	//assign to new
	e_pStreamingDataReceiver->pBuffer = l_pNewBuffer;
	e_pStreamingDataReceiver->iSize = l_iNewSize;
	return 1;
}
inline int		BufferAndSizeGetMatchedMagicID(sBufferAndSize*e_pStreamingDataReceiver, int*e_piMatchedIndex, int*e_piNumMatched)
{
	int		l_iBufferSize = e_pStreamingDataReceiver->iSize - MAGIC_ID_COUNT;
	int		l_iFori = 0;
	*e_piNumMatched = 0;
	if (e_pStreamingDataReceiver->iSize < MESSAGE_ID_INDEX)
		return 0;
	for (; l_iFori < l_iBufferSize; ++l_iFori)
	{
		if (e_pStreamingDataReceiver->pBuffer[l_iFori    ] == g_i8StreamingDataMagicID[0] &&
			e_pStreamingDataReceiver->pBuffer[l_iFori + 1] == g_i8StreamingDataMagicID[1] &&
			e_pStreamingDataReceiver->pBuffer[l_iFori + 2] == g_i8StreamingDataMagicID[2] &&
			e_pStreamingDataReceiver->pBuffer[l_iFori + 3] == g_i8StreamingDataMagicID[3])
		{
			if (*e_piNumMatched >= NUM_MAGIC_ID_MATCHED)
				return *e_piNumMatched;
			e_piMatchedIndex[*e_piNumMatched] = l_iFori;
			++*e_piNumMatched;
		}
	}
	return *e_piNumMatched;
}

inline char*	BufferAndSizeGetData(sBufferAndSize*e_pStreamingDataReceiver, int*e_piSize,int16*e_pi16MessageID)
{
	char*	l_pOutData = 0;
	int		l_iMatchIndex[NUM_MAGIC_ID_MATCHED];
	int		l_iCheckSumIndex = -1;
	int		l_iPacketSizeIndex = -1;
	uint16	l_iu16PacketSize = -1;
	int		l_iFori = 0;
	int		l_iNumMatch = 0;
	int		l_iBufferEndIndex = -1;
	uint16	l_ui16CheckSum = -1;
	uint16*	l_pui16OriginalCheckSumValue = 0;
	int		l_iMessageIDIndex = MESSAGE_ID_INDEX;
	if(!BufferAndSizeGetMatchedMagicID(e_pStreamingDataReceiver,l_iMatchIndex,&l_iNumMatch))
		return 0;
	for (; l_iFori < l_iNumMatch; ++l_iFori)
	{
		l_iPacketSizeIndex = l_iMatchIndex[l_iFori] + PACKET_SIZE_INDEX;
		l_iBufferEndIndex = l_iMatchIndex[l_iFori] +*(uint16*)&e_pStreamingDataReceiver->pBuffer[l_iPacketSizeIndex];
		if (l_iBufferEndIndex > e_pStreamingDataReceiver->iSize)
		{
			continue;
		}
		l_iCheckSumIndex = l_iMatchIndex[l_iFori] + CHECK_SUM_INDEX;
		l_iu16PacketSize = *(uint16*)&e_pStreamingDataReceiver->pBuffer[l_iPacketSizeIndex];
		l_ui16CheckSum = *(uint16*)&e_pStreamingDataReceiver->pBuffer[l_iCheckSumIndex];
		l_pui16OriginalCheckSumValue = (uint16*)&e_pStreamingDataReceiver->pBuffer[l_iCheckSumIndex];
		*l_pui16OriginalCheckSumValue = 0;
		if (l_ui16CheckSum != BufferAndSizeGetCheckSum(&e_pStreamingDataReceiver->pBuffer[l_iMatchIndex[l_iFori]], l_iu16PacketSize))
		{
			printf("check sum not matched!");
			continue;
		}
		l_pOutData = (char*)malloc(l_iu16PacketSize);
		memcpy(l_pOutData, &e_pStreamingDataReceiver->pBuffer[l_iMatchIndex[l_iFori]], l_iu16PacketSize);
		BufferAndSizeRemoveBuffer(e_pStreamingDataReceiver, l_iBufferEndIndex);
		*e_pi16MessageID = *(int16*)&l_pOutData[l_iMessageIDIndex];
		*e_piSize = l_iu16PacketSize;
		return l_pOutData;
	}
	return 0;
}
