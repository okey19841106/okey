/********************************************************************
	created:	2015/08/17
	created:	16:18
	author:		okey
	
	purpose:	只用TCP的，UDP以后再加吧。
*********************************************************************/
#ifndef __NETWORK_SOCKET_STREAM_H__
#define __NETWORK_SOCKET_STREAM_H__

#include "Socket.h"
#include "Stream/BufferedBidirectionalStreamBuf.h"

namespace okey
{



	class SocketStreamBuf: public BufferedBidirectionalStreamBuf
	{
	public:
		SocketStreamBuf(Socket& s);//移交管理权
		~SocketStreamBuf();
		Socket* GetSocket() {return &_socket;}
	protected:
		int readFromDevice(char* buffer, std::streamsize length);
		int writeToDevice(const char* buffer, std::streamsize length);

		enum 
		{
			STREAM_BUFFER_SIZE = 1024
		};
		Socket _socket;
	};

	class SocketIOS: public virtual std::ios
	{
	public:
		SocketIOS(Socket& socket);
		~SocketIOS();
		inline SocketStreamBuf* rdbuf(){return &_buf;}
		void close();
		Socket* socket();
	protected:
		SocketStreamBuf _buf;
	};

	class SocketOutputStream: public SocketIOS, public std::ostream
	{
	public:
		explicit SocketOutputStream(Socket& socket);
		~SocketOutputStream();
	};


	class SocketInputStream: public SocketIOS, public std::istream
	{
	public:
		explicit SocketInputStream(Socket& socket);
		~SocketInputStream();
	};


	class SocketStream: public SocketIOS, public std::iostream
	{
	public:
		explicit SocketStream(Socket& socket);
		~SocketStream();
	};
}

#endif