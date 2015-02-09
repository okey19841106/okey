/********************************************************************
	created:	2015/01/28
	created:	17:21
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __SOCKET_ACCEPTOR_H__
#define __SOCKET_ACCEPTOR_H__

#include "Events/EventHandler.h"
#include "Socket.h"
#include "SocketAddr.h"

namespace okey
{
#define ADDRLEN	(sizeof(SOCKADDR_IN) + 16)

	class NetServiceBase;
	class Acceptor : public Event_Handler
	{
	public:
		Acceptor(Socket& socket, const SocketAddr& addr, NetServiceBase* p);
		~Acceptor();

		virtual void* GetHandle(){return (void*)this;}
		virtual void SetHandle(const void* pHandle){}
		virtual void HandleInput();
		virtual void HandleOutput();
		virtual void HandleException();
		virtual void HandleClose();
		virtual void HandleInput(void* pParam);
#ifdef WINDOWS
		void PostAccept();
#endif
	private:
		Socket m_Socket;
		SocketAddr m_Addr;
		NetServiceBase* m_pNetService;
#ifdef WINDOWS
		char m_RecvBuf[ADDRLEN + ADDRLEN];
		CompleteOperator m_AccepterCom;
#endif
	};
}

#endif