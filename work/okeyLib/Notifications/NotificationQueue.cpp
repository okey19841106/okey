#include "PreCom.h"
#include "NotificationQueue.h"
#include "NotificationCenter.h"

namespace okey
{
	NotificationQueue::NotificationQueue()
	{

	}
	NotificationQueue::~NotificationQueue()
	{
		Clear();
	}
	void NotificationQueue::EnqueueNotification(Notification::Ptr pNotification)
	{
		FastMutex::ScopedLock lock(_mutex);
		if (_waitQueue.empty())
		{
			_nfQueue.push_back(pNotification);
		}
		else
		{
			WaitInfo* pWI = _waitQueue.front();
			_waitQueue.pop_front();
			pWI->pNf = pNotification;
			pWI->nfAvailable.Set();
		}	
	}
	void NotificationQueue::EnqueueUrgentNotification(Notification::Ptr pNotification)
	{
		FastMutex::ScopedLock lock(_mutex);
		if (_waitQueue.empty())
		{
			_nfQueue.push_back(pNotification);
		}
		else
		{
			WaitInfo* pWI = _waitQueue.front();
			_waitQueue.pop_front();
			pWI->pNf = pNotification;
			pWI->nfAvailable.Set();
		}	
	}
	Notification* NotificationQueue::DequeueNotification()
	{
		FastMutex::ScopedLock lock(_mutex);
		return dequeueOne().AddRef();
	}
	Notification* NotificationQueue::WaitDequeueNotification()
	{
		Notification::Ptr pNf;
		WaitInfo* pWI = NULL;
		{
			FastMutex::ScopedLock lock(_mutex);
			pNf = dequeueOne();
			if (pNf) 
				return pNf.AddRef();
			pWI = new WaitInfo;
			_waitQueue.push_back(pWI);
		}
		pWI->nfAvailable.Wait();
		pNf = pWI->pNf;
		delete pWI;
		return pNf.AddRef();
	}
	Notification* NotificationQueue::WaitDequeueNotification(long milliseconds)
	{
		Notification::Ptr pNf;
		WaitInfo* pWI = 0;
		{
			FastMutex::ScopedLock lock(_mutex);
			pNf = dequeueOne();
			if (pNf) 
				return pNf.AddRef();
			pWI = new WaitInfo;
			_waitQueue.push_back(pWI);
		}
		if (pWI->nfAvailable.TryWait(milliseconds))
		{
			pNf = pWI->pNf;
		}
		else
		{
			FastMutex::ScopedLock lock(_mutex);
			pNf = pWI->pNf;
			for (WaitQueue::iterator it = _waitQueue.begin(); it != _waitQueue.end(); ++it)
			{
				if (*it == pWI)
				{
					_waitQueue.erase(it);
					break;
				}
			}
		}
		delete pWI;
		return pNf.AddRef();
	}
	void NotificationQueue::Dispatch(NotificationCenter& notificationCenter)
	{
		FastMutex::ScopedLock lock(_mutex);
		Notification::Ptr pNf = dequeueOne();
		while (pNf)
		{
			notificationCenter.PostNotification(pNf);
			pNf = dequeueOne();
		}
	}
	void NotificationQueue::WakeUpAll()
	{
		FastMutex::ScopedLock lock(_mutex);
		for (WaitQueue::iterator it = _waitQueue.begin(); it != _waitQueue.end(); ++it)
		{
			(*it)->nfAvailable.Set();
		}
		_waitQueue.clear();
	}

	bool NotificationQueue::Empty() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return _nfQueue.empty();
	}

	int32 NotificationQueue::GetSize() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return (int32)_nfQueue.size();
	}

	void NotificationQueue::Clear()
	{
		FastMutex::ScopedLock lock(_mutex);
		_nfQueue.clear();	
	}

	bool NotificationQueue::HasIdleThreads() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return !_waitQueue.empty();
	}

	Notification::Ptr NotificationQueue::dequeueOne()
	{
		Notification::Ptr pNf;
		if (!_nfQueue.empty())
		{
			pNf = _nfQueue.front();
			_nfQueue.pop_front();
		}
		return pNf;
	}

	NotificationQueue& NotificationQueue::DefaultQueue()
	{
		static NotificationQueue s;
		return s;
	}

}