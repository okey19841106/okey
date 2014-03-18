#include "PreCom.h"
#include "PacketFactory.h"
#include "PacketProcess.h"

namespace okey
{

	PacketProcess::PacketProcess():m_DefFun(NULL)
	{

	}

	PacketProcess::~PacketProcess()
	{
		if (m_DefFun)
		{
			delete m_DefFun;
		}
	}
	bool PacketProcess::ProcessPacket(PacketBase* pkt)
	{
		if (!pkt)
		{
			return false;
		}
		uint32 tid = pkt->GetPacketID();
		FunMap::iterator itr = m_Funmap.find(tid);
		if (itr != m_Funmap.end())
		{
			itr->second->Process(pkt);
			return true;
		}
		else
		{
			if (m_DefFun)
			{
				m_DefFun->Process(pkt);
				return true;
			}
			return false;
		}

	}
	void PacketProcess::RegPacketHandler(const char* name, 
		uint32 packetid, CFunctionArg1Base<PacketBase*>* Fun)
	{
		if (!name || !Fun)
		{
			return;
		}
		ProcessBase<CFunctionArg1Base<PacketBase*>, PacketBase* >* pProc = NULL;
		FunMap::iterator itr = m_Funmap.find(packetid);
		if (itr == m_Funmap.end())
		{
			pProc = new ProcessBase<CFunctionArg1Base<PacketBase*>, PacketBase* >();
			m_Funmap[packetid] = pProc;
		}
		else
		{
			pProc = itr->second;
		}
		pProc->RegFunction(name,Fun);

	}
	void PacketProcess::RemovePacketHandler(uint32 packetid, CFunctionArg1Base<PacketBase*>* Fun)
	{
		if (!Fun)
		{
			return;
		}
		FunMap::iterator itr = m_Funmap.find(packetid);
		if (itr != m_Funmap.end())
		{
			itr->second->RemoveFunction(Fun);
		}

	}
	void PacketProcess::RegDefaultHandler(CFunctionArg1Base<PacketBase*>* DefFun)
	{
		if (!DefFun)
		{
			return;
		}
		if (m_DefFun)
		{
			delete m_DefFun;
			m_DefFun = NULL;
		}
		m_DefFun = new ProcessBase<CFunctionArg1Base<PacketBase*>, PacketBase* >();
		if (!m_DefFun)
		{
			return;
		}
		m_DefFun->RegFunction("DefaultFunction",DefFun);
	}
	
	PacketProcessEx::PacketProcessEx():m_DefFun(NULL)
	{

	}

	PacketProcessEx::~PacketProcessEx()
	{
		if (m_DefFun)
		{
			delete m_DefFun;
		}
	}

	bool PacketProcessEx::ProcessPacket(PacketBase* pkt)
	{
		if (!pkt)
		{
			return false;
		}
		uint32 tid = pkt->GetPacketID();
		FunMap::iterator itr = m_Funmap.find(tid);
		if (itr != m_Funmap.end())
		{
			CFunctionArg1Base<PacketBase*>* fun = itr->second;
			(*fun)(pkt);
			return true;
		}
		else
		{
			if (m_DefFun)
			{
				(*m_DefFun)(pkt);
				return true;
			}
			return false;
		}

	}
	void PacketProcessEx::RegPacketHandler(const char* name, 
		uint32 packetid, CFunctionArg1Base<PacketBase*>* Fun)
	{
		if (!name || !Fun)
		{
			return;
		}
		FunMap::iterator itr = m_Funmap.find(packetid);
		m_Funmap[packetid] = Fun;
		

	}
	void PacketProcessEx::RemovePacketHandler(uint32 packetid, CFunctionArg1Base<PacketBase*>* Fun)
	{
		if (!Fun)
		{
			return;
		}
		FunMap::iterator itr = m_Funmap.find(packetid);
		if (itr != m_Funmap.end())
		{
			m_Funmap.erase(itr);
		}

	}
	void PacketProcessEx::RegDefaultHandler(CFunctionArg1Base<PacketBase*>* DefFun)
	{
		if (!DefFun)
		{
			return;
		}
		if (m_DefFun)
		{
			delete m_DefFun;
			m_DefFun = NULL;
		}
		m_DefFun = DefFun;
	}
	PacketProc::PacketProc()
	{

	}

	PacketProc::~PacketProc()
	{

	}

	bool PacketProc::PushPacket(PacketBase* pkt)
	{
		MutexGuard tmpMutex(m_Mutex);
		return m_PktList.Push_Back(pkt);
	}

	bool PacketProc::ProcessPacket(PacketBase* pkt)
	{
		MutexGuard tmpMutex(m_Mutex);
		return m_PktList.Push_Back(pkt);
	}

	bool PacketProc::DoProc()
	{
		MutexGuard tmpMutex(m_Mutex);
		PacketBase* pkt = m_PktList.Pop_Head();
		int32 procount = 0;
		while (pkt)
		{
			PacketProcessEx::ProcessPacket(pkt);
			s_PacketFactory.DestroyPacket(pkt);
			++procount;
			if (procount >= 50) //每个Tick处理包的最多数量
			{
				break;
			}
			pkt = m_PktList.Pop_Head();
		}
		return true;
	}

	int32 PacketProc::GetPacketCount()
	{
		return m_PktList.GetPacketCount();
	}
}