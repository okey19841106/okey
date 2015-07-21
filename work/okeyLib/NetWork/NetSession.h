/********************************************************************
	created:	2015/01/29
	created:	16:00
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __NET_SESSION_H__
#define __NET_SESSION_H__

#include "SessionBase.h"
#include "Socket.h"
#include "Thread/Mutex.h"
#include "CircularBuffer.h"
#ifdef WINDOWS
#include "CompleteOperation.h"
#endif

namespace okey
{
	class Event_Actor;
	class NetServiceBase;

	class NetSession : public SessionBase
	{
	public:
		NetSession(NetServiceBase* pNetService, Event_Actor* pActor);
		virtual ~NetSession();
		virtual SessionState GetState() const{return m_State;}
		virtual SessionType GetType() const{return m_Type;}
		virtual uint32 GetID() const{return m_ID;}
		virtual void SetId(uint32 id){m_ID = id;}
		virtual void Disconnect();
		virtual SocketAddr GetPeerAddr() const;
		virtual SocketAddr GetHostAddr() const;
		virtual void Open(Socket& s, SessionType type, NetServiceBase* pNet);
		virtual void Close();
		virtual bool SendPacket(void* packet);
		virtual void* RecvPacket();
		virtual int32 SendData(const char* buff, int32 len);
		virtual int32 RecvData(char* buff, int32 len);
		virtual SOCKET GetSocket() {return m_Socket.GetSocket();}
		virtual void OnRecv();
		virtual void OnTick(const TimeStamp& curtime);
		virtual void OnConnect();
		virtual void OnSend();
		virtual void SetEventActor(Event_Actor* pActor);
		virtual EVENT_HANDLE GetHandle(){return (EVENT_HANDLE)m_Socket.GetSocket();}
		virtual void SetHandle(const void* pHandle){}


		virtual void HandleInput();
		virtual void HandleOutput();
		virtual void HandleException();
		virtual void HandleClose();
		virtual void HandleTick(const TimeStamp& now);
	protected:
		Socket m_Socket;
		NetServiceBase* m_pNetService;
		Event_Actor* m_pActor;
		uint32 m_ID;
		volatile SessionState m_State;
		SessionType m_Type;
		FastMutex	m_RecvMutex;
		FastMutex	m_SendMutex;
		CircularBuffer m_SendBuffer;
		CircularBuffer m_RecvBuffer;
		const static int32 RECV_BLOCK_SIZE;
	};
}

#endif