#include "PreCom.h"
#include "SocketNotifier.h"
#include "Socket.h"
#include "SocketReactor.h"
#include "SocketNotification.h"

namespace okey
{
	SocketNotifier::SocketNotifier(const Socket& socket)
	{
		_socket.Shift(socket);
	}

	void SocketNotifier::AddObserver(SocketReactor* pReator, const AbstractObserver& observer)
	{
		_nc.AddObserver(observer);
		if (observer.Accepts(pReator->_pReadableNotification))
		{
			_events.insert(pReator->_pReadableNotification.get());
		}
		else if (observer.Accepts(pReator->_pWritableNotification))
		{
			_events.insert(pReator->_pWritableNotification.get());
		}
		else if (observer.Accepts(pReator->_pErrorNotification))
		{
			_events.insert(pReator->_pErrorNotification.get());
		}
		else if (observer.Accepts(pReator->_pTimeoutNotification))
		{
			_events.insert(pReator->_pTimeoutNotification.get());
		}
	}

	void SocketNotifier::RemoveObserver(SocketReactor* pReator, const AbstractObserver& observer)
	{
		_nc.RemoveObserver(observer);
		EventSet::iterator itr = _events.end();
		if (observer.Accepts(pReator->_pReadableNotification))
		{
			_events.find(pReator->_pReadableNotification.get());
		}
		else if (observer.Accepts(pReator->_pWritableNotification))
		{
			_events.find(pReator->_pWritableNotification.get());
		}
		else if (observer.Accepts(pReator->_pErrorNotification))
		{
			_events.find(pReator->_pErrorNotification.get());
		}
		else if (observer.Accepts(pReator->_pTimeoutNotification))
		{
			_events.find(pReator->_pTimeoutNotification.get());
		}
		if (itr != _events.end())
		{
			_events.erase(itr);
		}
	}

	namespace 
	{
		static Socket nullSocket;
	}

	void SocketNotifier::Dispatch(SocketNotification* pNotification)
	{
		pNotification->SetSocket(_socket);
		pNotification->AddRef();
		try
		{
			_nc.PostNotification(pNotification);
		}
		catch (...)
		{
			pNotification->SetSocket(nullSocket);
			throw;
		}
		pNotification->SetSocket(nullSocket);
	}
}