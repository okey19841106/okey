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

namespace okey
{
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

		virtual void* GetHandle();
		virtual void SetHandle(const void* pHandle);
		virtual void HandleInput();
		virtual void HandleOutput();
		virtual void HandleException();
		virtual void HandleTick(const TimeStamp& now);
		virtual void HandleClose();
	private:
		Socket m_Socket;
		NetServiceBase* m_pNetService;
		uint32 m_ID;
		volatile SessionState m_State;
		SessionType m_Type;
		FastMutex	m_ReadMutex;
		FastMutex	m_WriteMutex;

	};
}

#endif