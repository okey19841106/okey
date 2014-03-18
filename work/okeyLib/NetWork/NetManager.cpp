#include "PreCom.h"
#include "NetManager.h"
#include "Packet.h"
#include "PacketProcess.h"
#include "log/Logger.h"
#include "HelperFunction.h"
#include "SocketOps.h"
#include "SocketBase.h"
#include "MySocket.h"
#include "Thread/Thread.h"
#include "CompleteOperation.h"
#ifdef WINDOWS
#include "IOCPReactor.h"
#endif



namespace okey
{
	NetManager::NetManager(int32 numThread,int32 skRcv,int32 stRcv,int32 skSnd, int32 stSnd,
		CFunctionArg1Base<int32>* AptFun,CFunctionArg1Base<int32>* conFun,
		CFunctionArg1Base<int32>* DisFun):m_numThread(numThread),m_socketRcvSize(skRcv),
		m_streamRcvSize(stRcv),m_socketSndSize(skSnd),
		m_streamSndSize(stSnd),m_AptFun(AptFun),m_ConFun(conFun),m_DisFun(DisFun),m_pktProc(NULL),m_isThreadExit(false)
	{
#ifdef WINDOWS
		//initialize Winsock
		WSADATA wsaData;
		if ( NO_ERROR != WSAStartup( MAKEWORD(2,2), &wsaData ) )
		{
			LOG_ERROR( logger, __FUNCTION__ << " failed WSAStartup(), " << FormatErrorMessage( WSAGetLastError() ) );
			return;
		}
		m_pReactor = new IOCPReactor(4);
#endif
		m_pReactor->Open(4,0);
		m_pListenSocket = NULL;
		m_aptThread = NULL;//œ»–¥À¿
	}

	NetManager::~NetManager()
	{
		if (m_AptFun)
		{
			delete m_AptFun;
		}
		if (m_ConFun)
		{
			delete m_ConFun;
		}
		if (m_DisFun)
		{
			delete m_DisFun;
		}
		m_isThreadExit = true;
		Sleep(1000);
#ifdef WINDOWS
		if( NO_ERROR != WSACleanup() )
		{
			LOG_ERROR( logger, __FUNCTION__ << " failed WSACleanup(), " << FormatErrorMessage( WSAGetLastError() ) );
		}
#endif
		if (m_pListenSocket)
		{
			delete m_pListenSocket;
			m_pListenSocket = NULL;
		}
	}

	bool NetManager::OnConnect(SocketBase* pSocket)
	{
		if (!pSocket)
		{
			return false;
		}
		MutexGuard tmpMutex(m_Mutex);
		MySocket* pMySocket = (MySocket*)pSocket;
		if (!pMySocket)
		{
			return false;
		}
		NetEventHandler* pHandler = (NetEventHandler*)pMySocket;
		if (!pHandler)
		{
			return false;
		}
		//add sock to epoll set
		if(!m_pReactor->RegisterHandler(pHandler,NetEvent_IO))
		{
			LOG_ERROR( logger, __FUNCTION__ << " failed to register Session , id:" << pSocket->GetID() );
			return false;
		}
		int32 sid = m_SocketList.Add(pSocket);
		pSocket->SetID(sid);
		if (m_ConFun)
		{
			(*m_ConFun)(pSocket->GetID());
		}
#ifdef WINDOWS
		return	pMySocket->PostRecvOperation();
#endif
	}

	bool NetManager::OnAccept(SocketBase* pSocket)
	{
		if (!pSocket)
		{
			return false;
		}
		MutexGuard tmpMutex(m_Mutex);
		MySocket* pMySocket = (MySocket*)pSocket;
		if (!pMySocket)
		{
			return false;
		}
		NetEventHandler* pHandler = (NetEventHandler*)pMySocket;
		if (!pHandler)
		{
			return false;
		}
		//add sock to epoll set
		if(!m_pReactor->RegisterHandler(pHandler,NetEvent_IO))
		{
			LOG_ERROR( logger, __FUNCTION__ << " failed to register Session, id:" << pSocket->GetID() );
			return false;
		}
		
		int32 sid = m_SocketList.Add(pSocket);
		pSocket->SetID(sid);
		if (m_AptFun)
		{
			(*m_AptFun)(pSocket->GetID());
		}
#ifdef WINDOWS
		return	pMySocket->PostRecvOperation();
#endif
	}

	bool NetManager::OnDisconnect(SocketBase* pSocket)
	{
		if (!pSocket)
		{
			return false;
		}
		//pSocket->Disconnect();
		delete pSocket;
		pSocket = NULL;
		return true;
	}

	bool NetManager::OnSend()
	{
		return true;
	}

	bool NetManager::OnRecv()
	{
		return true;
	}

	bool NetManager::Run()
	{
		//delete list...
		ProcessDelSockets();
		return true;
	}

	void NetManager::ThreadRun()
	{
		while(!m_isThreadExit)
		{
			m_pReactor->HandleEvent(INFINITE);
		}
	}

	SocketBase* NetManager::Connect(const char* ip,int32 port)
	{
		MySocket* pSocket = new MySocket(this, m_streamSndSize,m_streamRcvSize,m_socketRcvSize,m_socketSndSize);
		if (!pSocket)
		{
			return NULL;
		}
		if (!pSocket->Connect(ip,port))
		{
			return NULL;
		}
		//notify connect
		pSocket->SetReactor(m_pReactor);
		OnConnect(pSocket);
		return pSocket;

	}

	bool NetManager::Accept(const char* ip, int32 port)
	{
		if (m_pListenSocket)
		{
			return false;
		}
		m_pListenSocket = new MySocket(this, 4096, 4096);
		if(!m_pListenSocket->Listen(ip,port))
		{
			delete m_pListenSocket;
			m_pListenSocket = NULL;
			return false;
		}
		m_aptThread = new Thread(new CFunctionArg0<NetManager>(this,&NetManager::RunAccept), "accept thread");
		if (!m_aptThread)
		{
			return false;
		}
		m_aptThread->start();
		return true;
	}

	SocketBase* NetManager::GetSocket(int32 socketid)
	{
		return m_SocketList.Get(socketid);
	}

	bool NetManager::Disconnect(int32 socketid)
	{
		MutexGuard tmpMutex(m_Mutex);
		SocketBase* pSocket = GetSocket(socketid);
		if (!pSocket)
		{
			return false;
		}
		//OnDisconnect(pSocket);
		if (m_DisFun)
		{
			(*m_DisFun)(pSocket->GetID());
		}
		m_SocketList.Remove(pSocket->GetID());
		MutexGuard tMutex(m_DelMutex);
		m_DelList.Add(pSocket);
		return true;
	}


	void NetManager::RunAccept()
	{
		while (!m_isThreadExit)
		{
			MySocket* pSocket = (MySocket*) m_pListenSocket->Accept(m_streamSndSize, m_streamRcvSize,m_socketRcvSize,m_socketSndSize);
			if (pSocket)
			{
				OnAccept(pSocket);
			}

		}
	}

	bool NetManager::ProcessPacket(PacketBase* pkt)
	{
		return m_pktProc->ProcessPacket(pkt);
	}

	void NetManager::StartWorkThread()
	{
		for( int32 i = 0; i < m_numThread; ++i )
		{
		 	char tname[64] = {0};
		 	sprintf_s(tname,"Peer Net Thread:%d",i);
		 	m_Threads.push_back(new Thread(new CFunctionArg0<NetManager>(this,&NetManager::ThreadRun), tname) );
		}
		std::vector<Thread*>::iterator it = m_Threads.begin();
		std::vector<Thread*>::iterator end = m_Threads.end();
		for( ; end != it; ++it )
		{
		 	(*it)->start();
		}
	}

	 void NetManager::StopWorkThread()
	 {
		if (!m_pReactor)
		{
			return;
		}
		m_pReactor->Close();
	 }
	 void NetManager::ProcessDelSockets()
	 {
		 MutexGuard tMutex(m_DelMutex);
		 for (int32 i = 0;  m_DelList.GetCount(); ++i )
		 {
			 SocketBase* pSocket = m_DelList.Get(i);
			 if (!pSocket)
			 {
				 continue;
			 }
			 m_DelList.Remove(i);
			 OnDisconnect(pSocket);
		 }
	 }
}