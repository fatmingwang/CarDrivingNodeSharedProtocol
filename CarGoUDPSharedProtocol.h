#pragma once

#include "SharedProtocolCommonDefine.h"
#define	UDP_PORT	22667
enum eUDP_MessageList
{
	eUDPML_C2S_REQUIRE_IMAGE = 200000,
	eUDPML_S2C_IMAGE_PACKET_START,
	eUDPML_S2C_IMAGE_PACKET,
	eUDPML_MAX
};

enum eCompressMethod
{
	eCM_JPG = 0,
	eCM_PNG,
	eCM_MAX,
};

LAZY_MESSAGE_HEADER_STAR(eUDPML_C2S_REQUIRE_IMAGE)
LAZY_MESSAGE_HEADER_END(eUDPML_C2S_REQUIRE_IMAGE)


LAZY_MESSAGE_HEADER_STAR(eUDPML_S2C_IMAGE_PACKET_START)
	int		iCompressMethod;
	int32	i32ImageSize;
	int32	i32PacketCount;
	int32	i32EachPacketDataSize;
	int		iImageWidth;
	int		iImageHeight;
	int		iNumChannel;
LAZY_MESSAGE_HEADER_END(eUDPML_S2C_IMAGE_PACKET_START)


#define PIXELS_PACK_SIZE 4096 //udp pack size; note that OSX limits < 8100 bytes

LAZY_MESSAGE_HEADER_STAR(eUDPML_S2C_IMAGE_PACKET)
	int		iPacketIndex;
	char	PixelData[PIXELS_PACK_SIZE];
	int		iPixelDataLen;
LAZY_MESSAGE_HEADER_END(eUDPML_S2C_IMAGE_PACKET)
