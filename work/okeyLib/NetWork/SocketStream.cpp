#include "PreCom.h"
#include "SocketStream.h"


namespace okey
{
	SocketStreamBuf::SocketStreamBuf(Socket& s):BufferedBidirectionalStreamBuf(STREAM_BUFFER_SIZE, std::ios::in | std::ios::out)
	{
		_socket.Shift(s);
	}

	SocketStreamBuf::~SocketStreamBuf()
	{
		_socket.Close();
	}

	int SocketStreamBuf::readFromDevice(char* buffer, std::streamsize length)
	{
		return _socket.Recv(buffer,(int32)length);//这有问题， 大小的
	}

	int SocketStreamBuf::writeToDevice(const char* buffer, std::streamsize length)
	{
		return _socket.Send(buffer,(int32)length);
	}

	SocketIOS::SocketIOS(Socket& socket):_buf(socket)
	{

	}

	SocketIOS::~SocketIOS()
	{
		try
		{
			_buf.sync();
		}
		catch (...)
		{
		}
	}
	
	void SocketIOS::close()
	{
		_buf.sync();
		_buf.GetSocket()->Close();
	}

	Socket* SocketIOS::socket()
	{
		return _buf.GetSocket();
	}

	SocketOutputStream::SocketOutputStream(Socket& socket):SocketIOS(socket),	std::ostream(&_buf)
	{
	}

	SocketOutputStream::~SocketOutputStream()
	{
	}

	SocketInputStream::SocketInputStream(Socket& socket):SocketIOS(socket),std::istream(&_buf)
	{
	}

	SocketInputStream::~SocketInputStream()
	{
	}

	SocketStream::SocketStream(Socket& socket):SocketIOS(socket),	std::iostream(&_buf)
	{
	}

	SocketStream::~SocketStream()
	{
	}

}