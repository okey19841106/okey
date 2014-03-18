//////////////////////////////////////////////////////////////
//  created:	2011-11-28 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////

#ifndef __PACKET_PROCESS_H__
#define __PACKET_PROCESS_H__

#include "Types.h"
#include "BaseProcess.h"
#include "PacketFunction.h"
#include "Packet.h"
#include "PacketList.h"
#include <map>
#include "Singleton.h"

namespace okey
{
#define REG_PACKET_IMPL_HANDLER(proc,funname,packet,basepacket,classObj)\
	proc->RegPacketHandler(#packet,UtilID::StringToUtilID(#packet,(uint32)strlen(#packet)),new CFunctionPacket<classObj,packet*, basepacket* >(this,&classObj::funname));\
	packet tmp_##packet;

	class PacketProcess
	{
		typedef std::map<uint32, ProcessBase<CFunctionArg1Base<PacketBase*>, PacketBase* >* > FunMap;
	public:
		PacketProcess();
		~PacketProcess();
		virtual bool ProcessPacket(PacketBase* pkt);
		virtual void RegPacketHandler(const char* name, uint32 packetid, CFunctionArg1Base<PacketBase*>* Fun);
		virtual void RemovePacketHandler(uint32 packetid, CFunctionArg1Base<PacketBase*>* Fun);
		virtual void RegDefaultHandler(CFunctionArg1Base<PacketBase*>* DefFun);
	private:
		FunMap m_Funmap;
		ProcessBase<CFunctionArg1Base<PacketBase*>, PacketBase* >* m_DefFun;
	};

	class PacketProcessEx
	{
		typedef std::map<uint32, CFunctionArg1Base<PacketBase*>* > FunMap;
	public:
		PacketProcessEx();
		~PacketProcessEx();
		virtual bool ProcessPacket(PacketBase* pkt);
		virtual void RegPacketHandler(const char* name, uint32 packetid, CFunctionArg1Base<PacketBase*>* Fun);
		virtual void RemovePacketHandler(uint32 packetid, CFunctionArg1Base<PacketBase*>* Fun);
		virtual void RegDefaultHandler(CFunctionArg1Base<PacketBase*>* DefFun);
	private:
		FunMap m_Funmap;
		CFunctionArg1Base<PacketBase*>* m_DefFun;
	};

	class PacketProc: public PacketProcessEx
	{
	public:
		PacketProc();
		~PacketProc();
		bool PushPacket(PacketBase* pkt);
		virtual bool ProcessPacket(PacketBase* pkt);
		bool DoProc();
		int32 GetPacketCount();
		//PacketProcess* GetPacketProcess(){return this;}
	protected:
	private:
		Mutex	m_Mutex;
		PacketList m_PktList;
	};

	class GPacketProcess: public PacketProcessEx, public Singleton<GPacketProcess>
	{
	public:
		GPacketProcess(){}
		~GPacketProcess(){}
	};

	#define s_PacketProcess GPacketProcess::GetSingleton()
}


#endif