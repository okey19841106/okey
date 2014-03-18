#include "PreCom.h"
#include "Packet.h"

namespace okey
{

	char* PacketBase::ReadPacket(char* pBuffer)
	{
		if (!pBuffer)
		{
			return NULL;
		}
		char* tmp = pBuffer;
		m_packetid = *((uint32*)tmp);
		tmp += sizeof(uint32);
		m_sendType = *((uint8*)tmp);
		return tmp + sizeof(uint8);
	}
	char* PacketBase::WritePacket(char* pBuffer)
	{
		if (!pBuffer)
		{
			return NULL;
		}
		char* tmp = pBuffer;
		*((uint32*)tmp) = m_packetid;
		tmp += sizeof(uint32);
		*((uint8*)tmp) = m_sendType;
		return tmp + sizeof(uint8);
	}
}