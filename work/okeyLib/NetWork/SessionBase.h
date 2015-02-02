/********************************************************************
	created:	2015/01/28
	created:	17:54
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __SOCKET_SESSION_BASE_H__
#define __SOCKET_SESSION_BASE_H__

#include "Events/EventHandler.h"
#include "CRefcounter.h"
#include "SocketAddr.h"
#include "AutoPtr.h"

namespace okey
{
	class NetServiceBase;
	class Event_Actor;

	class SessionBase : public Event_Handler, public CRefCounter
	{
	public:
		enum SessionState
		{
			e_Connected,
			e_DisConnected,
		};
		enum SessionType
		{
			e_Active,
			e_Passive,
		};
	public:
		SessionBase(){}
		virtual ~SessionBase(){}
		virtual SessionState GetState() const = 0;
		virtual SessionType GetType() const = 0;
		virtual uint32 GetID() const = 0;
		virtual void SetId(uint32 id) = 0;
		virtual void Disconnect() = 0;
		virtual SocketAddr GetPeerAddr() const = 0;
		virtual SocketAddr GetHostAddr() const = 0;
		virtual void Open(SOCKET s, SessionType type, NetServiceBase* pNet) = 0;
		virtual void Close() = 0;
		virtual bool SendPacket(void* packet) = 0;
		virtual void* RecvPacket() = 0;
		virtual int32 SendData(const char* buff, int32 len) = 0;
		virtual int32 RecvData(char* buff, int32 len) = 0;
		virtual SOCKET GetSocket() = 0;
		virtual void SetEventActor(Event_Actor* pActor) = 0;
	private:
	};

	typedef AutoPtr<SessionBase> SessionPtr;
}

#endif