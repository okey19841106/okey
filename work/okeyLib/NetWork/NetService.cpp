#include "PreCom.h"
#include "NetService.h"
#include "Socket.h"
#include "Fuction.h"
#include "NetSession.h"
#include "NetThread.h"
#include "Thread/Runnable.h"
#include "Acceptor.h"
#include "IOCPNetSession.h"
#ifdef WINDOWS
#include "IOCPProactor.h"
#endif

namespace okey
{
	NetService::NetService(uint32 id, const NetServiceParam& param):m_ID(id),m_ConNum(0),m_State(e_Initial),m_Connections(1024)
	{
		m_Param = param;
#ifdef WINDOWS
		WSADATA wsaData;
		WORD wVersionRequested = MAKEWORD(2,2);
		WSAStartup(wVersionRequested, &wsaData);
		if (m_Param._bUseIOCP)
		{
			m_pEventActor = new IOCPProactor;
			m_pEventActor->Open(m_Param._maxConNum, m_Param._threadConnNum);
		}
		else
		{
			m_pConThread = new NetThread(m_Param._maxConNum);
		}
#else
		m_pConThread = new NetThread(m_Param._maxConNum);
#endif
	}
	NetService::~NetService()
	{
		if (m_pConThread)
		{
			delete m_pConThread;
			m_pConThread = NULL;
		}
		if (m_pConRunnable)
		{
			delete m_pConRunnable;
			m_pConRunnable = NULL;
		}
#ifdef WINDOWS
		WSACleanup();
#endif
	}
	bool NetService::StartUp()
	{
		if (m_State != e_Initial)
		{
			return false;
		}
		if (!m_Param._bUseIOCP)
		{
			StartThreads(m_Param._threadConnNum);
			m_pConRunnable = new RunnableAdapter<NetThread>(m_pConThread, &NetThread::HandleRun);
			m_pConThread->Start(*m_pConRunnable);
		}
		m_State = e_Running;
		//起线程。
		return true;
	}
	void NetService::ShutDown()
	{
		if (m_State != e_Running)
		{
			return;
		}
		m_State = e_Shutdown;
		if (!m_Param._bUseIOCP)
		{
			m_pConThread->Stop();
			m_pConThread->Join();
		}
		StopThreads();
		//全部停下。。。
	}
	bool NetService::OnConnect(SessionBase* pSession)
	{
		return true;
	}

	bool NetService::OnAccept(SessionBase* pSession)
	{
		return true;
	}

	bool NetService::OnDisconnect(SessionBase* pSession)
	{
		return true;
	}

	bool NetService::OnSend()
	{
		return true;
	}
	bool NetService::OnRecv()
	{
		return true;
	}
	void NetService::Run()
	{

	}
	SessionPtr NetService::Connect(const SocketAddr& addr)
	{
		if (m_State != e_Running)
		{
			return NULL;
		}
		Socket sock;
		if (!sock.Create())
		{
			return NULL;
		}
		if (!sock.Connect(addr))
		{
			return NULL;
		}
		if (!InitSocket(sock))
		{
			sock.Close();
			return NULL;
		}
		SessionBase* pSession = NULL;
		if (m_Param._bUseIOCP)
		{
			 pSession = new IOCPNetSession(this, m_pEventActor);
		}
		else
		{
			 pSession = new NetSession(this,m_pEventActor);
		}
		uint32 sessionid = m_Connections.insert(pSession);
		if (sessionid == 0)
		{
			sock.Close();
			return NULL;
		}
		pSession->Open(sock, SessionBase::e_Active, this);
		pSession->SetId(sessionid);
		if (m_ConnectCallBack)
		{
			(*m_ConnectCallBack)(pSession);
		}
		SessionPtr sPtr = pSession;
#ifdef WINDOWS
		if (m_Param._bUseIOCP)
		{
			m_pEventActor->RegisterHandler(pSession,Event_Handler::Event_IO);
		}
		else
		{
			ScheduleSession(sPtr);
		}
#else
		ScheduleSession(sPtr);
#endif
		return sPtr;
	}
	bool NetService::Accept(const SocketAddr& addr)
	{
		if (m_State != e_Running)
		{
			return false;
		}
		Socket sock;
		if (!sock.Create())
		{
			//create error
			return false;
		}
		if (!sock.Bind(addr))
		{
			return false;
		}
		if (!sock.Listen(m_Param.backlog))
		{
			return false;
		}
		if (m_Param._bUseIOCP)
		{
			if (!sock.SetNonBlocking(false))
			{
				return false;
			}
		}
		else
		{
			if (!sock.SetNonBlocking())
			{
				return false;
			}
		}
		sock.SetReuseAddr();
		//线程去注册监听器。。
		if (m_Param._bUseIOCP)
		{
			m_pEventActor->RegisterHandler(new IOCPAcceptor(sock, addr, this), Event_Handler::Event_Exception | Event_Handler::Event_In);
		}
		else
		{
			m_pConThread->RegisterHandler(new Acceptor(sock, addr, this), Event_Handler::Event_Exception | Event_Handler::Event_In);
		}
		return true;
	}
	
	SessionBase* NetService::GetSession(int32 id)
	{
// 		CONNECTION_MAP::iterator itr = m_Connections.find(id);
// 		if (itr != m_Connections.end())
// 		{
// 			return itr->second;
// 		}
// 		return NULL;
		return m_Connections.get_index(id);
	}
	bool NetService::Disconnect(int32 scoketid)
	{
		SessionBase* pSession = GetSession(scoketid);
		pSession->Disconnect();
		return true;
	}

	void NetService::OnNewConnection(Socket& s, SessionBase::SessionType t)
	{
		SocketAddr addr;
		s.GetPeerAddr(addr);
		if (m_State != e_Running)
		{
			s.Close();
			return;
		}
		if (!InitSocket(s))
		{
			s.Close();
			return;
		}
		SessionBase* pSession = NULL;
		{
			FastMutex::ScopedLock lock(m_ConMutex);
			if (m_ConNum >= m_Param._maxConNum)
			{
				s.Close();
				return;
			}
			if (m_Param._bUseIOCP)
			{
				pSession = new IOCPNetSession(this,m_pEventActor);
			}
			else
			{
				pSession = new NetSession(this,m_pEventActor);
			}
			uint32 sessionid = m_Connections.insert(pSession);
			if (sessionid == 0)
			{
				s.Close();
				delete pSession;
				pSession = NULL;
				return;
			}
			++m_ConNum;
		}
	
		pSession->Open(s, t, this);
#ifdef WINDOWS
		if (m_Param._bUseIOCP)
		{
			m_pEventActor->RegisterHandler(pSession,Event_Handler::Event_IO);
		}
		else
		{
			ScheduleSession(pSession);
		}
#else
		ScheduleSession(pSession);
#endif
		
	}
// 	SessionPtr NetService::Connect(uint32 id, const SocketAddr& addr)
// 	{
// 		
// 	}
	void NetService::RecycleConnection(SessionBase* pSession)
	{
		bool bVerified = false;
		{
			FastMutex::ScopedLock lock(m_ConMutex);
			if (m_ConNum > 0)
			{
				--m_ConNum;
			}
// 			CONNECTION_MAP::iterator itr = m_Connections.find(pSession->GetID());
// 			if (itr != m_Connections.end())
// 			{
// 				m_Connections.erase(itr);
// 				bVerified = true;
// 			}
			m_Connections.erase(pSession->GetID());
			bVerified = true;
		}
		if (m_DisconnectCallBack && bVerified)
		{
			(*m_DisconnectCallBack)(pSession);
			//通知。。。。
		}
		pSession->Close();
		pSession->DecRef();
	}

	void NetService::ScheduleSession(SessionBase* pSession)
	{
		NetThread* thread = (NetThread*)GetMiniLoadThread();
		thread->RegisterHandler(pSession, Event_Handler::Event_In | Event_Handler::Event_Exception);
	}

	std::pair<Thread*, Runnable*> NetService::CreateThread()
	{
		NetThread* pThread = new NetThread(m_Param._maxConNum);
		Runnable* pRun = new RunnableAdapter<NetThread>((NetThread*)pThread, &NetThread::HandleRun);
		return std::pair<Thread*, Runnable*>(pThread, pRun);
	}

	void NetService::DestroyThread(std::pair<Thread*, Runnable*> threadinfo)
	{
		delete threadinfo.first;
		delete threadinfo.second;
	}

	bool NetService::InitSocket(Socket& sock)
	{
		if (m_Param._bUseIOCP)
		{
			if (!sock.SetNonBlocking(false))
			{
				return false;
			}
		}
		else
		{
			if (!sock.SetNonBlocking())
			{
				return false;
			}
		}
		sock.SetSendBufSize(m_Param._sysSendBuff);
		sock.SetRecvBufSize(m_Param._sysRecvBuff);
		sock.SetNonDelay();
		return true;
	}
}