#include "PreCom.h"
#include "PacketFactory.h"
#include "Packet.h"

namespace okey
{
	void* PacketFactory::CreatePacket(const char* name)
	{
		CFactoryArg0_Base* pfac = GetObj(name);
		if (!pfac)
		{
			return NULL;
		}
		return pfac->CreateObject();
	}
	void* PacketFactory::CreatePacket(uint32 packetid)
	{
		CFactoryArg0_Base* pfac = GetObj(packetid);
		if (!pfac)
		{
			return NULL;
		}
		return pfac->CreateObject();
	}
	bool PacketFactory::DestroyPacket(PacketBase* pkt)
	{
		CFactoryArg0_Base* pfac = GetObj(pkt->GetPacketID());
		if (!pfac)
		{
			return false;
		}
		pfac->FreeObject((void*)pkt);
		return true;
	}
}
