/********************************************************************
	created:	2015/07/08
	created:	14:45
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __SOCKET_NOTIFIER_H__
#define __SOCKET_NOTIFIER_H__

#include "CRefcounter.h"
#include <set>
#include "Notifications/NotificationCenter.h"

namespace okey
{
	class Socket;
	class SocketReactor;
	class SocketNotification;

	class SocketNotifier: public CRefCounter
	{
	public:
		explicit SocketNotifier(const Socket& socket);
		void AddObserver(SocketReactor* pReator, const AbstractObserver& observer);
		void RemoveObserver(SocketReactor* pReator, const AbstractObserver& observer);
		bool Accepts(SocketNotification* pNotification);
		void Dispatch(SocketNotification* pNotification);
		bool HasObservers()const;
		int32 CountObservers() const;
	protected:
		~SocketNotifier();
	private:
		typedef std::multiset<SocketNotification*> EventSet;
		EventSet _events;
		NotificationCenter _nc;
		Socket _socket;
	};

	inline bool SocketNotifier::Accepts(SocketNotification* pNotification)
	{
		return _events.find(pNotification) != _events.end();
	}

	inline bool SocketNotifier::HasObservers() const
	{
		return _nc.HasObservers();
	}

	inline int32 SocketNotifier::CountObservers() const
	{
		return _nc.CountObservers();
	}
}


#endif