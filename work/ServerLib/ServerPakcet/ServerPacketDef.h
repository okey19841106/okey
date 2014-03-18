/********************************************************************
	created:	2013/06/24
	created:	24-6-2013   22:47
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __SERVER_PACKET_DEF__H__
#define __SERVER_PACKET_DEF__H__

#include "Types.h"
#include "NetWork/NetPacket.h"

namespace okey
{
	

	PACKET(PacketConnect, PacketBase)
	int32 nID;
	int32 nServerType;
	char nIp[16];
	int16 nPort;
	START_ADD_PACKET_MEMBER(PacketConnect)
	ADD_PACKET_MEMBER(PacketConnect,nID,int32,test)
	ADD_PACKET_MEMBER(PacketConnect,nServerType,int32,test)
	ADD_PACKET_MEMBER_STR(PacketConnect,nIp,16,test)
	ADD_PACKET_MEMBER(PacketConnect,nPort,int16,test)
	PACKET_END(PacketConnect)

	PACKET(PacketServerID, PacketBase)
	int32 nGroupID;
	int32 nServerID;
	START_ADD_PACKET_MEMBER(PacketServerID)
	ADD_PACKET_MEMBER(PacketServerID,nGroupID,int32,test)
	ADD_PACKET_MEMBER(PacketServerID,nServerID,int32,test)
	PACKET_END(PacketServerID)

	PACKET(PacketServerInfo, PacketBase)
	int32 nServerType;
	int32 nServerID;
	char nIp[16];
	int16 nPort;
	START_ADD_PACKET_MEMBER(PacketServerInfo)
	ADD_PACKET_MEMBER(PacketServerInfo,nServerType,int32,test)
	ADD_PACKET_MEMBER(PacketServerInfo,nServerID,int32,test)
	ADD_PACKET_MEMBER_STR(PacketServerInfo,nIp,16,test)
	ADD_PACKET_MEMBER(PacketServerInfo,nPort,int16,test)
	PACKET_END(PacketServerInfo)
}

#endif