#include "PreCom.h"
#include "PeerBase.h"
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
	PeerBase::PeerBase()
	{
		m_PeerPocPacket = NULL;
		m_NetManger = NULL;
		m_PeerIP = "127.0.0.1";
		m_PeerPort = 888;
	}
	PeerBase::~PeerBase()
	{
		if (m_PeerPocPacket)
		{
			delete m_NetManger;
		}
		if (m_NetManger)
		{
			delete m_NetManger;
		}
	}

	bool PeerBase::Init(int argc, char *argv[])
	{
		//可以初始化一些参数。。
		for (int i = 0; i < argc; ++i)
		{
			if (strcmp(argv[i], "-PeerIP") == 0)
			{
				m_PeerIP = argv[i+1];
			}
			else if (strcmp(argv[i], "-PeerPort") == 0)
			{
				m_PeerPort = (int)atoi(argv[i+1]);
			}
		}
		m_PeerPocPacket = new PacketProc();
		if (!m_PeerPocPacket)
		{
			return false;
		}
		CFunctionArg1Base<int32>* AFun = new CFunctionArg1<PeerBase,int32>(this, &PeerBase::OnPeerAccept);
		CFunctionArg1Base<int32>* CFun = new CFunctionArg1<PeerBase,int32>(this, &PeerBase::OnPeerConnect);
		CFunctionArg1Base<int32>* DFun = new CFunctionArg1<PeerBase,int32>(this, &PeerBase::OnPeerDisconnect);
		m_NetManger = new NetManager(2,4096,4096,4096,4096,AFun,CFun,DFun);
		if (!m_NetManger)
		{
			return false;
		}
		m_NetManger->SetPacketProcess(m_PeerPocPacket);
		m_NetManger->StartWorkThread();
		RegPktHandler();
		return true;
	}

	int32 PeerBase::PeerConnect(const char* ipaddress, int32 port)
	{
		if (!m_NetManger)
		{
			return -1;
		}
		SocketBase* pSocket = m_NetManger->Connect(ipaddress,port);
		if (!pSocket)
		{
			return -1;
		}
		return pSocket->GetID();
	}

	bool PeerBase::PeerAccept(const char* ipaddress, int32 port)
	{
		if (!m_NetManger)
		{
			return false;
		}
		return m_NetManger->Accept(ipaddress,port);
	}

	void PeerBase::PeerRun() //应该处理一些帧相关的东西哦。。
	{
// 		while (true)
// 		{
			DoPeerRun();
			int32 tTime = GTime::GetTimeMS();
			int32 tPeerNetThreadFrameTime = tTime - m_LastFrameTime;
			m_LastFrameTime = tTime;
			PeerProcPacket();
			if (m_PktSendList.GetPacketCount() <= 0)
			{
				//暂停一会哦。。。
			}
			int32 tSleeptime = 100 - tPeerNetThreadFrameTime;
			//Sleep(tSleeptime);
//		}
	}

	void PeerBase::DoPeerRun()
	{
		if (m_NetManger)
		{
			DoPeerSend();
			//m_NetManger->Run();
		}
	}

	void PeerBase::RegPktHandler()
	{
		if (!m_PeerPocPacket)
		{
			return;
		}
		REG_PACKET_IMPL_HANDLER(m_PeerPocPacket,PktTestHandler,PacketText,PacketBase,PeerBase);
		//m_PeerPocPacket->RegPacketHandler("PacketText",UtilID::StringToUtilID("PacketText",strlen("PacketText")),new CFunctionPacket<PeerBase,PacketText* , PacketBase* >(this,&PeerBase::PktTestHandler));
	}

	void PeerBase::DoPeerSend()
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

	bool PeerBase::PeerSend(int32 socketid, PacketBase* pkt)
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
	bool PeerBase::PeerProcPacket()
	{
		if (!m_PeerPocPacket)
		{
			return false;
		}
		PacketProc* pProc = (PacketProc*)m_PeerPocPacket;
		return pProc->DoProc();
	}

	bool PeerBase::PeerAccept()
	{
		if (!m_NetManger)
		{
			return false;
		}
		return m_NetManger->Accept(m_PeerIP.c_str(), m_PeerPort);
	}

	void PeerBase::PktTestHandler(PacketText* pkt)
	{
		if (!pkt)
		{
			return;
		}
		printf("%d\n",pkt->flag);

	}

	
}