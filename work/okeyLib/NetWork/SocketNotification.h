/********************************************************************
	created:	2015/07/08
	created:	14:44
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __SOCKET_NOTIFITION_H__
#define __SOCKET_NOTIFITION_H__

#include "Notifications/Notification.h"
#include "Socket.h"

namespace okey
{
	class SocketReactor;

	class SocketNotification: public Notification
	{
	public:
		explicit SocketNotification(SocketReactor* pReactor);
		~SocketNotification();
		SocketReactor& Source(){return *_pReacotr;}
		Socket& GetSocket(){return _socket;}
	private:
		void SetSocket(const Socket& socket);
		SocketReactor* _pReacotr;
		Socket _socket;
		friend class SocketNotifier;
	};

	class ReadableNotification: public SocketNotification
	{
	public:
		ReadableNotification(SocketReactor* pReactor);
		~ReadableNotification();
	};

	class WritableNotification: public SocketNotification
	{
	public:
		WritableNotification(SocketReactor* pReactor);
		~WritableNotification();
	};

	class ErrorNotification: public SocketNotification
	{
	public:
		ErrorNotification(SocketReactor* pReactor);
		~ErrorNotification();
	};

	class TimeoutNotification: public SocketNotification
	{
	public:
		TimeoutNotification(SocketReactor* pReactor);
		~TimeoutNotification();
	};

	class IdleNotification: public SocketNotification
	{
	public:
		IdleNotification(SocketReactor* pReactor);
		~IdleNotification();
	};

	class ShutdownNotification: public SocketNotification
	{
	public:
		ShutdownNotification(SocketReactor* pReactor);
		~ShutdownNotification();
	};
}

#endif