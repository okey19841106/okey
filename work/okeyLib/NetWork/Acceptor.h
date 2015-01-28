/********************************************************************
	created:	2015/01/28
	created:	17:21
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __SOCKET_ACCEPTOR_H__
#define __SOCKET_ACCEPTOR_H__


namespace okey
{
	class NetServiceImpl;
	class Acceptor : public Event_Handler
	{
	public:
		Acceptor(Socket& socket, const SocketAddr& addr, NetServiceImpl* p);
		~Acceptor();

		virtual void* GetHandle();
		virtual void SetHandle(const void* pHandle){}
		virtual void HandleInput();
		virtual void HandleOutput();
		virtual void HandleException();
		virtual void HandleClose();

	private:
		Socket m_Socket;
		SocketAddr m_Addr;
		NetServiceImpl* m_pNetService;
	};
}

#endif