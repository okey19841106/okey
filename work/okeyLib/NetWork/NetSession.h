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

namespace okey
{
#ifdef WINDOWS

	class CompleteOperator: public OVERLAPPED
	{
	public:
		enum CompleteOperatorEvent
		{
			IOCP_IVALID = -1,
			IOCP_EVENT_READ_COMPLETE = 0,
			IOCP_EVENT_WRITE_END = 1,
			IOCP_EVENT_EXCEPT = 2,
		};
	public:
		CompleteOperator()
		{
			hEvent = 0;
			Internal = 0;
			InternalHigh = 0;
			Offset = 0;
			OffsetHigh = 0;
			nMask = IOCP_IVALID;
		}
		~CompleteOperator();
		uint32 GetBytesTransferred(){return static_cast<uint32>( InternalHigh );}
		CompleteOperatorEvent nMask;
	};
#endif

	class Event_Actor;
	class NetServiceBase;

	class NetSession : public SessionBase
	{
	public:
		NetSession();
		virtual ~NetSession();
		virtual SessionState GetState() const{return m_State;}
		virtual SessionType GetType() const{return m_Type;}
		virtual uint32 GetID() const{return m_ID;}
		virtual void SetId(uint32 id){m_ID = id;}
		virtual void Disconnect();
		virtual SocketAddr GetPeerAddr() const;
		virtual SocketAddr GetHostAddr() const;
		virtual void Open(SOCKET s, SessionType type, NetServiceBase* pNet);
		virtual void Close();
		virtual bool SendPacket(void* packet);
		virtual void* RecvPacket();
		virtual int32 SendData(const char* buff, int32 len);
		virtual int32 RecvData(char* buff, int32 len);
		virtual void OnRecv();
		virtual void OnTick(const TimeStamp& curtime);
		virtual void OnConnect();
		virtual void OnSend();
		virtual void SetEventActor(Event_Actor* pActor);
		virtual void* GetHandle(){return (void*)this;}
		virtual void SetHandle(const void* pHandle){}
		virtual void HandleInput();
		virtual void HandleOutput();
		virtual void HandleException();
		virtual void HandleTick(const TimeStamp& now);
		virtual void HandleClose();
#ifdef WINDOWS
		void PostReadEvent();
		void PostWriteEvent();
		void HandlerComplete(CompleteOperator* p);
	private:
		void HandleReadComplete(CompleteOperator* p);
		void HandleWriteComplete(CompleteOperator* p);
#endif
	private:
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
#ifdef WINDOWS
		WSABUF m_SendWSABuf;
		WSABUF m_RecvWSABuf;
		CompleteOperator m_SendOverLapped;
		CompleteOperator m_RecvOverLapped;
		bool m_bSend;
#endif
	};
}

#endif