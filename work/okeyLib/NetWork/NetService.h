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

namespace okey
{
	class NetService: public NetServiceBase
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
		virtual bool Run();
		virtual SessionBase* Connect(const SocketAddr& addr);
		virtual bool BindAddress(const SocketAddr& addr);
		virtual bool Accept(const char* ip, int32 port);
		virtual SessionBase* GetSession(int32 id);
		virtual bool Disconnect(int32 scoketid);
		virtual void OnNewConnection(Socket& s, SessionBase::SessionType t);
		virtual SessionPtr Connect(uint32 id, const SocketAddr& addr);
		virtual void RecycleConnection(SessionBase* pSession);
	protected:
		bool InitSocket(Socket& sock);
	private:
		uint32 m_ID; //网络服务id
		volatile NetServiceState m_State;
		Thread* m_pThread; //负责处理链接的线程。
		uint32 m_ConNum;
		FastMutex m_lock;
		CONNECTION_MAP m_Connections;
	};
}

#endif