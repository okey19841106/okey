//////////////////////////////////////////////////////////////
//                    .----.
//                 _.'__    `.
//             .--(#)(##)---/#\
//           .' @          /###\
//           :       ,     #####
//            `-..__.-' _.-\###/ 
//                   `;_:   `"'
//                 .'"""""`.
//                /,        ,\
//               //          \\
//               `-._______.-'
//              ___`. | .'___
//             (______|______)
//
//  created:	2011-11-16 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////

#ifndef __PACKET_H__
#define __PACKET_H__

#ifdef WINDOWS
#pragma warning(disable: 4800)
#endif

#include "Types.h"
#include <string>
#include "UtilID.h"
/*#include "FactoryManager.h"*/
#include "PoolAllocator.h"

namespace okey
{


#define MAX_PACKET_SIZE 256

	class PacketBase
	{
	/*Reg_Base_Packet_Begin(PacketBase,g_PoolPacketAllocator);
	Add_Packet_Member(PacketBase,m_packetlen,uint32,1,packet_id);
	Add_Packet_Member(PacketBase,m_packetid,uint32,1,packet_id);
	Reg_Base_Packet_End(PacketBase);*/
	public:
		PacketBase()
		{
			m_packetid = 0;
			m_Socketid = -1;
			m_next = NULL;
			m_prev = NULL;
			m_sendType = 0;
			m_isDrop = false;
		}
		~PacketBase()
		{

		}
		void SetPacketID(uint32 id){m_packetid = id;}
		uint32 GetPacketID()const{return m_packetid;}
		void SetSocketID(int32 id){m_Socketid = id;}
		int32 GetSocketID()const{return m_Socketid;}
		void SetSendType(uint8 tp){m_sendType = tp;}
		uint8 GetSendType()const{return m_sendType;}
		bool CheckType(uint8 tp){return m_sendType& tp;}
		virtual int32 GetPakcetSize(){return sizeof(m_packetid) + sizeof(m_Socketid) + sizeof(m_sendType);}
		PacketBase* m_next;
		PacketBase* m_prev;
		virtual char* ReadPacket(char* pBuffer);
		virtual char* WritePacket(char* pBuffer);
		bool m_isDrop;
	protected:
		uint32 m_packetid;
	    int32 m_Socketid;
	    uint8 m_sendType;
		
	private:
		
	};
	/*IMPL_PACKET(Packet);*/
	
	template<uint32 PACKET_SIZE>
	class PacketBaseEx :public PacketBase
	{
	public:
		PacketBaseEx()
		{
			memset(m_buffer, 0 , PACKET_SIZE);
			m_buffersize = 0;
		}
		~PacketBaseEx(){}

		virtual char* ReadPacket(char* pBuffer)
		{
			if (!pBuffer)
			{
				return NULL;
			}
			char* tmp = PacketBase::ReadPacket(pBuffer);
			m_buffersize = *((uint16*)tmp);
			if (m_buffersize > PACKET_SIZE)
			{
				return NULL;
			}
			tmp + = sizeof(uint16);
			memcpy(m_buffer, tmp , m_buffersize);
			return tmp + m_buffersize;
		}
		virtual char* WritePacket(char* pBuffer)
		{
			if (!pBuffer)
			{
				return NULL;
			}
			m_buffersize = strlen(pBuffer);
			if (m_buffersize > PACKET_SIZE)
			{
				return NULL;
			}
			char* tmp = PacketBase::WritePacket(pBuffer);
			*((uint16*)tmp) = m_buffersize;
			
			tmp + = sizeof(uint16);
			memcpy(tmp , m_buffer,  m_buffersize);
			return tmp + m_buffersize;
		}

		uint16 ReadBuffer(char* buff, uint16 size)
		{
			if (!buff)
			{
				return;
			}
			memcpy(buff, m_buffer, size);
			return m_buffersize;
		}

		uint16 WriteBuffer(char* buff)
		{
			if (!buff)
			{
				return;
			}
			m_buffersize = (strlen(buff)>PACKET_SIZE)? PACKET_SIZE : strlen(buff);
			memcpy(m_buffer, buff, m_buffersize);
			return m_buffersize;
		}
	private:
		char m_buffer[PACKET_SIZE];
		uint16 m_buffersize;
	};
	
//	#define s_PacketFactoryManager FactoryManagerArg0::GetSingleton()
}



#endif

