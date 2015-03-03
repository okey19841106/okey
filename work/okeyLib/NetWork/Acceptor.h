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
#ifdef WINDOWS
#include <MSWSock.h>
#include "CompleteOperation.h"
#endif

namespace okey
{

#ifdef WINDOWS
	class AcceptCompleteOperator :  public CompleteOperator 
	{
	public:
		AcceptCompleteOperator(){}
		~AcceptCompleteOperator(){}
	public:
		Socket m_AcceptSocket;
	};

// 	class IOPCAcceptFun
// 	{
// 	public:
// 		IOPCAcceptFun(Socket s);
// 		void AcceptEx();
// 		void GetAcceptExSockaddrs();
// 	private:
// 		static LPFN_ACCEPTEX m_fnAcceptEx;
// 		static LPFN_GETACCEPTEXSOCKADDRS m_fnGetAcceptExSockaddrs;
// 	};
#endif
	
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
		AcceptCompleteOperator m_AccepterCom;
		static LPFN_ACCEPTEX m_fnAcceptEx;
#endif
	};
}

#endif