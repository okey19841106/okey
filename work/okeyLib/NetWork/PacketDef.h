#ifndef __PACKET_DEF__H__
#define __PACKET_DEF__H__

#include "Types.h"
#include "NetPacket.h"

namespace okey
{

	PACKET(PacketText, PacketBase)
	int32 flag;
	START_ADD_PACKET_MEMBER(PacketText)
	ADD_PACKET_MEMBER(PacketText,flag,int32,test)
	PACKET_END(PacketText)


	
}



#endif