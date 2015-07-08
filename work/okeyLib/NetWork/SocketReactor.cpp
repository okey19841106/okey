#include "PreCom.h"
#include "SocketReactor.h"
#include "SocketNotifier.h"
#include "SocketNotification.h"

namespace okey
{
	SocketReactor::SocketReactor():_stop(false),_timeout(DEFAULT_TIMEOUT)
	{

	}

	SocketReactor::SocketReactor(const TimeSpan& timeout):_stop(false), _timeout(timeout)
	{

	}

	SocketReactor::~SocketReactor()
	{

	}

	void SocketReactor::Init()
	{
		_pReadableNotification = new ReadableNotification(this);
		_pWritableNotification = new WritableNotification(this);
		_pErrorNotification = new ErrorNotification(this);
		_pTimeoutNotification = new TimeoutNotification(this);
		_pIdleNotification = new IdleNotification(this);
		_pShutdownNotification = new ShutdownNotification(this);
	}

	void SocketReactor::Run()
	{
		std::vector<Socket> readable;
		std::vector<Socket> writable;
		std::vector<Socket> except;
		while(!_stop)
		{
			try
			{
				readable.clear();
				writable.clear();
				except.clear();
				int32 nSocket = 0;
				{
					FastMutex::ScopedLock lock(_mutex);
					for(EventHandlerMap::iterator itr = _handlers.begin(); itr != _handlers.end(); ++itr)
					{
						if (itr->second->Accepts(_pReadableNotification))
						{
							readable.push_back(itr->first);
							nSocket++;
						}
						if (itr->second->Accepts(_pWritableNotification))
						{
							readable.push_back(itr->first);
							nSocket++;
						}
						if (itr->second->Accepts(_pErrorNotification))
						{
							readable.push_back(itr->first);
							nSocket++;
						}
					}
				}
				if (nSocket == 0)
				{
					OnIdle();
				}
				else if (Select(readable, writable, except, _timeout))
				{
					OnBusy();
					for (std::vector<Socket>::iterator it_r = readable.begin(); it_r != readable.end(); ++it_r)
					{
						Dispatch(*it_r, _pReadableNotification);
					}
					for (std::vector<Socket>::iterator it_w = writable.begin(); it_w != readable.end(); ++it_w)
					{
						Dispatch(*it_w, _pWritableNotification);
					}
					for (std::vector<Socket>::iterator it_e = except.begin(); it_e != except.end(); ++it_e)
					{
						Dispatch(*it_e, _pErrorNotification);
					}
				}

			}
			catch(Exception& exc)
			{
				ErrorHandler::handle(exc);
			}
			catch(std::exception& exc)
			{
				ErrorHandler::handle(exc);
			}
			catch(...)
			{
				ErrorHandler::handle();
			}
		}
		OnShutdown();
	}

	void SocketReactor::Stop()
	{
		_stop = true;
	}

	void SocketReactor::SetTimeout(const TimeSpan& timeout)
	{
		_timeout = timeout;
	}

	const TimeSpan& SocketReactor::GetTimeout() const
	{
		return _timeout;
	}

	void SocketReactor::AddEventHandler(const Socket& socket, const AbstractObserver& observer)
	{
		NotifierPtr pNotifier;
		{
			FastMutex::ScopedLock lock(_mutex);
			EventHandlerMap::iterator itr = _handlers.find(socket);
			if (itr == _handlers.end())
			{
				pNotifier = new SocketNotifier(socket);
				_handlers[socket] = pNotifier;
			}
			else
				pNotifier = itr->second;
		}
		pNotifier->AddObserver(this,observer);
	}

	void SocketReactor::RemoveEventHandler(const Socket& socket, const AbstractObserver& observer)
	{
		NotifierPtr pNotifier;
		{
			FastMutex::ScopedLock lock(_mutex);
			EventHandlerMap::iterator itr = _handlers.find(socket);
			if (itr != _handlers.end())
			{
				pNotifier = itr->second;
				if (pNotifier->CountObservers())
				{
					_handlers.erase(itr);
				}
			}
		}
		if (pNotifier)
		{
			pNotifier->RemoveObserver(this, observer);
		}
	}

	void SocketReactor::OnTimeout()
	{
		Dispatch(_pTimeoutNotification);
	}

	void SocketReactor::OnIdle()
	{
		Dispatch(_pIdleNotification);
	}

	void SocketReactor::OnShutdown()
	{
		Dispatch(_pShutdownNotification);
	}

	void SocketReactor::OnBusy()
	{

	}

	void SocketReactor::Dispatch(const Socket& socket, SocketNotification* pNotification)
	{
		NotifierPtr pNotifier;
		{
			FastMutex::ScopedLock lock(_mutex);
			EventHandlerMap::iterator itr = _handlers.find(socket);
			if (itr != _handlers.end())
			{
				pNotifier = itr->second;
			}
			else
				return;
		}
		Dispatch(pNotifier,pNotification);
	}

	void SocketReactor::Dispatch(SocketNotification* pNotification)
	{
		std::vector<NotifierPtr> delegates;
		delegates.reserve(_handlers.size());
		{
			FastMutex::ScopedLock lock(_mutex);
			for (EventHandlerMap::iterator it = _handlers.begin(); it != _handlers.end(); ++it)
				delegates.push_back(it->second);
		}
		for (std::vector<NotifierPtr>::iterator it = delegates.begin(); it != delegates.end(); ++it)
		{
			Dispatch(*it, pNotification);
		}
	}

	void SocketReactor::Dispatch(NotifierPtr& pNotifer, SocketNotification* pNotification)
	{
		try
		{
			pNotifer->Dispatch(pNotification);
		}
		catch (Exception& exc)
		{
			ErrorHandler::handle(exc);
		}
		catch (std::exception& exc)
		{
			ErrorHandler::handle(exc);
		}
		catch (...)
		{
			ErrorHandler::handle();
		}
	}
}