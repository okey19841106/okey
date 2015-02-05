/********************************************************************
	created:	2015/02/02
	created:	15:30
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __NET_SERVICE_H__
#define __NET_SERVICE_H__

#include "NetServiceBase.h"
#include "HashMap.h"
#include "Thread/Mutex.h"
#include "Thread/Thread.h"
#include "Thread/ThreadGroup.h"

namespace okey
{
	template<typename Arg>
	class CFunctionArg1Base;

	class NetService: public NetServiceBase, public ThreadGroup
	{
		typedef hash_map<uint32, SessionBase*> CONNECTION_MAP;
		
	public:
		NetService(uint32 id, const NetServiceParam& param);
		~NetService();
		virtual bool StartUp();
		virtual void ShutDown();
		virtual uint32 GetID() const{return m_ID;}
		virtual bool OnConnect(SessionBase* pSession);
		virtual bool OnAccept(SessionBase* pSession);
		virtual bool OnDisconnect(SessionBase* pSession);
		virtual bool OnSend();
		virtual bool OnRecv();
		virtual void Run();
		virtual SessionBase* Connect(const SocketAddr& addr);
		virtual bool Accept(const SocketAddr& addr);
		virtual SessionBase* GetSession(int32 id);
		virtual bool Disconnect(int32 scoketid);
		virtual void OnNewConnection(Socket& s, SessionBase::SessionType t);
		virtual SessionPtr Connect(uint32 id, const SocketAddr& addr);
		virtual void RecycleConnection(SessionBase* pSession);
	public:
		Thread* CreateThread();
		void DestroyThread(Thread* pThread);
	protected:
		bool InitSocket(Socket& sock);
		void ScheduleSession(SessionBase* pSession);
// 		void RegisterHandler(Event_Handler* pHandler, uint32 events);
// 		void HandlerRun();
	private:
		uint32 m_ID; //�������id
		volatile NetServiceState m_State;
		Thread* m_pThread; //���������ӵ��̡߳�
		uint32 m_ConNum;
		FastMutex m_ConMutex;
		CONNECTION_MAP m_Connections;
		
		CFunctionArg1Base<SessionBase*>* m_AcceptCallBack;
		CFunctionArg1Base<SessionBase*>* m_ConnectCallBack;
		CFunctionArg1Base<SessionBase*>* m_DisconnectCallBack;
	};
}

#endif