#include "PreCom.h"
#include "SocketNotification.h"

namespace okey
{
	SocketNotification::SocketNotification(SocketReactor* pReactor):
			_pReacotr(pReactor)
	{

	}

	SocketNotification::~SocketNotification()
	{

	}

	void SocketNotification::SetSocket(const Socket& socket)
	{
		_socket.Shift(socket);
	}
	ReadableNotification::ReadableNotification(SocketReactor* pReactor): 
	SocketNotification(pReactor)
	{
	}


	ReadableNotification::~ReadableNotification()
	{
	}


	WritableNotification::WritableNotification(SocketReactor* pReactor): 
	SocketNotification(pReactor)
	{
	}


	WritableNotification::~WritableNotification()
	{
	}


	ErrorNotification::ErrorNotification(SocketReactor* pReactor): 
	SocketNotification(pReactor)
	{
	}


	ErrorNotification::~ErrorNotification()
	{
	}


	TimeoutNotification::TimeoutNotification(SocketReactor* pReactor): 
	SocketNotification(pReactor)
	{
	}


	TimeoutNotification::~TimeoutNotification()
	{
	}


	IdleNotification::IdleNotification(SocketReactor* pReactor): 
	SocketNotification(pReactor)
	{
	}


	IdleNotification::~IdleNotification()
	{
	}


	ShutdownNotification::ShutdownNotification(SocketReactor* pReactor): 
	SocketNotification(pReactor)
	{
	}


	ShutdownNotification::~ShutdownNotification()
	{
	}
}