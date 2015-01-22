#include "PreCom.h"
#include "PriorityNotificationQueue.h"
#include "NotificationCenter.h"

namespace okey
{
	PriorityNotificationQueue::PriorityNotificationQueue()
	{

	}
	PriorityNotificationQueue::~PriorityNotificationQueue()
	{
		Clear();
	}
	void PriorityNotificationQueue::EnqueueNotification(Notification::Ptr pNotification , int32 priority)
	{
		FastMutex::ScopedLock lock(_mutex);
		if (_waitQueue.empty())
		{
			_nfQueue.insert(NfQueue::value_type(priority, pNotification));
		}
		else
		{
			WaitInfo* pWI = _waitQueue.front();
			_waitQueue.pop_front();
			pWI->pNf = pNotification;
			pWI->nfAvailable.Set();
		}	
	}
	
	Notification* PriorityNotificationQueue::DequeueNotification()
	{
		FastMutex::ScopedLock lock(_mutex);
		return dequeueOne().AddRef();
	}
	Notification* PriorityNotificationQueue::WaitDequeueNotification()
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
	Notification* PriorityNotificationQueue::WaitDequeueNotification(uint32 milliseconds)
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
	void PriorityNotificationQueue::Dispatch(NotificationCenter& notificationCenter)
	{
		FastMutex::ScopedLock lock(_mutex);
		Notification::Ptr pNf = dequeueOne();
		while (pNf)
		{
			notificationCenter.PostNotification(pNf);
			pNf = dequeueOne();
		}
	}
	void PriorityNotificationQueue::WakeUpAll()
	{
		FastMutex::ScopedLock lock(_mutex);
		for (WaitQueue::iterator it = _waitQueue.begin(); it != _waitQueue.end(); ++it)
		{
			(*it)->nfAvailable.Set();
		}
		_waitQueue.clear();
	}

	bool PriorityNotificationQueue::Empty() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return _nfQueue.empty();
	}

	int32 PriorityNotificationQueue::GetSize() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return (int32)_nfQueue.size();
	}

	void PriorityNotificationQueue::Clear()
	{
		FastMutex::ScopedLock lock(_mutex);
		_nfQueue.clear();	
	}

	bool PriorityNotificationQueue::HasIdleThreads() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return !_waitQueue.empty();
	}

	Notification::Ptr PriorityNotificationQueue::dequeueOne()
	{
		Notification::Ptr pNf;
		NfQueue::iterator it = _nfQueue.begin();
		if (it != _nfQueue.end())
		{
			pNf = it->second;
			_nfQueue.erase(it);
		}
		return pNf;
	}

	PriorityNotificationQueue& PriorityNotificationQueue::DefaultQueue()
	{
		static PriorityNotificationQueue s;
		return s;
	}

}