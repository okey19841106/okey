/********************************************************************
	created:	2013/05/26
	created:	26-5-2013   19:18
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef _OKEY_SOCKET_OPS_H__
#define _OKEY_SOCKET_OPS_H__



#ifdef WINDOWS

#elif defined(LINUX)

#endif
#include "PreCom.h"


namespace okey
{


	namespace SocketOps
	{
		// Create file descriptor for socket i/o operations.
		SOCKET CreateTCPFileDescriptor();

		// Disable blocking send/recv calls.
		bool Nonblocking(SOCKET fd);

		// Enable blocking send/recv calls.
		bool Blocking(SOCKET fd);

		// Disable nagle buffering algorithm
		bool DisableBuffering(SOCKET fd);

		// Enables nagle buffering algorithm
		bool EnableBuffering(SOCKET fd);

		// Set internal buffer size to socket.
		bool SetRecvBufferSize(SOCKET fd, uint32 size);

		// Set internal buffer size to socket.
		bool SetSendBufferSize(SOCKET fd, uint32 size);

		// Set timeout, in seconds
		bool SetTimeout(SOCKET fd, uint32 timeout);

		// Closes socket completely.
		void CloseSocket(SOCKET fd);

		// Sets SO_REUSEADDR
		void ReuseAddr(SOCKET fd);

		int32 GetLastError();
	};

}

#endif

