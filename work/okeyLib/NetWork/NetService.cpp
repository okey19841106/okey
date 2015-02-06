#include "PreCom.h"
#include "NetService.h"
#include "Socket.h"
#include "Fuction.h"
#include "NetSession.h"
#include "NetThread.h"
#include "Thread/Runnable.h"
#include "Acceptor.h"
#ifdef WINDOWS
#include "IOCPProactor.h"
#endif

namespace okey
{
	NetService::NetService(uint32 id, const NetServiceParam& param):m_ID(id),m_ConNum(0),m_State(e_Initial)
	{
		m_Param = param;
#ifdef WINDOWS
		m_pEventActor = new IOCPProactor;
		m_pEventActor->Open(m_Param._maxConNum, m_Param._threadConnNum);
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
	}
	bool NetService::StartUp()
	{
		if (m_State != e_Initial)
		{
			return false;
		}
		StartThreads(m_Param._threadConnNum);
#ifdef WINDOWS
#else
		m_pConRunnable = new RunnableAdapter<NetThread>(m_pConThread, &NetThread::HandleRun);
		m_pConThread->Start(*m_pConRunnable);
#endif
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
#ifdef WINDOWS
#else
		m_pConThread->Stop();
		m_pConThread->Join();
#endif
		StopThreads();
		//全部停下。。。
	}
	bool NetService::OnConnect(SessionBase* pSession)
	{

	}

	bool NetService::OnAccept(SessionBase* pSession)
	{

	}

	bool NetService::OnDisconnect(SessionBase* pSession)
	{

	}

	bool NetService::OnSend()
	{

	}
	bool NetService::OnRecv()
	{

	}
	void NetService::Run()
	{

	}
	SessionBase* NetService::Connect(const SocketAddr& addr)
	{

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
		if (!sock.SetNonBlocking())
		{
			return false;
		}
		sock.SetReuseAddr();
		//线程去注册监听器。。
#ifdef WINDOWS
		
#else
		m_pConThread->RegisterHandler(new Acceptor(sock, addr, this), Event_Handler::Event_Exception | Event_Handler::Event_In);
#endif
		return true;
	}
	
	SessionBase* NetService::GetSession(int32 id)
	{
		CONNECTION_MAP::iterator itr = m_Connections.find(id);
		if (itr != m_Connections.end())
		{
			return itr->second;
		}
		return NULL;
	}
	bool NetService::Disconnect(int32 scoketid)
	{
		SessionBase* pSession = GetSession(scoketid);
		RecycleConnection(pSession);
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
		{
			FastMutex::ScopedLock lock(m_ConMutex);
			if (m_ConNum >= m_Param._maxConNum)
			{
				s.Close();
				return;
			}
			++m_ConNum;
		}
		SessionBase* pSession = new NetSession;
		SOCKET sock = s.GetSocket();
		pSession->Open(sock, t, this);
		ScheduleSession(pSession);
	}
	SessionPtr NetService::Connect(uint32 id, const SocketAddr& addr)
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
		SessionBase* pSession = new NetSession;
		SOCKET s = sock.GetSocket();
		pSession->Open(s, SessionBase::e_Active, this);
		if (m_ConnectCallBack)
		{
			(*m_ConnectCallBack)(pSession);
		}
		SessionPtr sPtr = pSession;
#ifdef WINDOWS

#else
		ScheduleSession(sPtr);
#endif
		return sPtr;
	}
	void NetService::RecycleConnection(SessionBase* pSession)
	{
		bool bVerified = false;
		{
			FastMutex::ScopedLock lock(m_ConMutex);
			if (m_ConNum > 0)
			{
				--m_ConNum;
			}
			CONNECTION_MAP::iterator itr = m_Connections.find(pSession->GetID());
			if (itr != m_Connections.end())
			{
				m_Connections.erase(itr);
				bVerified = true;
			}
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
		Thread* pThread = new NetThread(m_Param._maxConNum);
		Runnable* pRun = new RunnableAdapter<NetThread>((NetThread*)pThread, &NetThread::HandleRun);
		return std::pair<Thread*, Runnable*>(pThread, pRun);
	}

	void NetService::DestroyThread(std::pair<Thread*, Runnable*> threadinfo)
	{
		delete threadinfo.first;
		delete threadinfo.second;
	}


}