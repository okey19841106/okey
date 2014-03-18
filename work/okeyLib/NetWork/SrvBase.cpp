#include "PreCom.h"
#include "SrvBase.h"
#include "NetManager.h"
#include "Packet.h"
#include "PacketProcess.h"
#include "Thread/Thread.h"
#include "PacketFactory.h"
#include "PacketDef.h"
#include "TimeManager.h"
#include "SocketBase.h"

namespace okey
{
	SrvBase::SrvBase()
	{
		m_SrvPocPacket = NULL;
		m_NetManger = NULL;
		m_SrvIP = "127.0.0.1";
		m_SrvPort = 888;
	}
	SrvBase::~SrvBase()
	{
		if (m_SrvPocPacket)
		{
			delete m_NetManger;
		}
		if (m_NetManger)
		{
			delete m_NetManger;
		}
	}

	bool SrvBase::Init(int argc, char *argv[])
	{
		//可以初始化一些参数。。
		m_SrvPocPacket = new PacketProc();
		if (!m_SrvPocPacket)
		{
			return false;
		}
		CFunctionArg1Base<int32>* AFun = new CFunctionArg1<SrvBase,int32>(this, &SrvBase::OnSrvAccept);
		CFunctionArg1Base<int32>* CFun = new CFunctionArg1<SrvBase,int32>(this, &SrvBase::OnSrvConnect);
		CFunctionArg1Base<int32>* DFun = new CFunctionArg1<SrvBase,int32>(this, &SrvBase::OnSrvDisconnect);
		m_NetManger = new NetManager(2,4096,4096,4096,4096,AFun,CFun,DFun);
		if (!m_NetManger)
		{
			return false;
		}
		m_NetManger->SetPacketProcess(m_SrvPocPacket);
		m_NetManger->StartWorkThread();
		RegPktHandler();
		return true;
	}

	bool SrvBase::SrvConnect(const char* ipaddress, int32 port)
	{
		if (!m_NetManger)
		{
			return false;
		}
		return m_NetManger->Connect(ipaddress,port);
	}

	bool SrvBase::SrvAccecpt(const char* ipaddress, int32 port)
	{
		if (!m_NetManger)
		{
			return false;
		}
		return m_NetManger->Accept(ipaddress,port);
	}

	void SrvBase::SrvRun() //应该处理一些帧相关的东西哦。。
	{
		while (true)
		{
			DoSrvRun();
			int32 tTime = GTime::GetTimeMS();
			int32 tSrvNetThreadFrameTime = tTime - m_LastFrameTime;
			m_LastFrameTime = tTime;
			SrvProcPacket();
			if (m_PktSendList.GetPacketCount() <= 0)
			{
				//暂停一会哦。。。
			}
			int32 tSleeptime = 100 - tSrvNetThreadFrameTime;
			//Sleep(tSleeptime);
		}
	}

	void SrvBase::DoSrvRun()
	{
		if (m_NetManger)
		{
			DoSrvSend();
			//m_NetManger->Run();
		}
	}

	void SrvBase::RegPktHandler()
	{
		if (!m_SrvPocPacket)
		{
			return;
		}
		//REG_PACKET_IMPL_HANDLER(m_SrvPocPacket,PktTestHandler,PacketText,PacketBase,SrvBase);
		//m_SrvPocPacket->RegPacketHandler("PacketText",UtilID::StringToUtilID("PacketText",strlen("PacketText")),new CFunctionPacket<SrvBase,PacketText* , PacketBase* >(this,&SrvBase::PktTestHandler));
	}

	void SrvBase::DoSrvSend()
	{
		int32 realSndCount = 0;
		int32 curSndCount = 0;
		int32 dropCount = 0;
		PacketBase* pkt = m_PktSendList.Pop_Head();
		while (pkt)
		{
			SocketBase* s = m_NetManger->GetSocket(pkt->GetSocketID());
			if (s)
			{
				++curSndCount;
				if (!s->SendPacket(pkt))
				{
					if (!pkt->m_isDrop)
					{
						m_PktFailedList.Push_Back(pkt);
						pkt = m_PktSendList.Pop_Head();
						continue;
					}
					++dropCount;
				}
				++realSndCount;
				s_PacketFactory.DestroyPacket(pkt);
			}
			if (curSndCount >= 50)
			{
				break;
			}
			pkt = m_PktSendList.Pop_Head();
		}
		{
			PacketBase* failpkt = m_PktFailedList.Pop_Back();
			while (failpkt)
			{
				m_PktSendList.Push_Back(failpkt);
				failpkt = m_PktFailedList.Pop_Back();
			}
		}


	}

	bool SrvBase::SrvSend(int32 socketid, PacketBase* pkt)
	{
		if (socketid < 0 || !pkt)
		{
			return false;
		}
		PacketBase* tmppkt = (PacketBase*)s_PacketFactory.CreatePacket(pkt->GetPacketID());
		if (!tmppkt)
		{
			return false;
		}
		char buffer[MAX_PACKET_SIZE];
		pkt->WritePacket(buffer);
		tmppkt->ReadPacket(buffer);
		tmppkt->SetSocketID(socketid);
		tmppkt->m_isDrop = tmppkt->m_isDrop;
		return m_PktSendList.Push_Back(tmppkt);
	}
	bool SrvBase::SrvProcPacket()
	{
		if (!m_SrvPocPacket)
		{
			return false;
		}
		PacketProc* pProc = (PacketProc*)m_SrvPocPacket;
		return pProc->DoProc();
	}

	bool SrvBase::SrvAccept()
	{
		if (!m_NetManger)
		{
			return false;
		}
		return m_NetManger->Accept(m_SrvIP.c_str(), m_SrvPort);
	}

// 	void SrvBase::PktTestHandler(PacketText* pkt)
// 	{
// 		if (!pkt)
// 		{
// 			return;
// 		}
// 		printf("%d\n",pkt->flag);
// 
// 	}
}