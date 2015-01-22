#include "PreCom.h"
#include "TimedNotificationQueue.h"

namespace okey
{
	TimedNotificationQueue::TimedNotificationQueue()
	{
	}


	TimedNotificationQueue::~TimedNotificationQueue()
	{
		Clear();
	}


	void TimedNotificationQueue::EnqueueNotification(Notification::Ptr pNotification, TimeStamp timestamp)
	{

		FastMutex::ScopedLock lock(_mutex);
		_nfQueue.insert(NfQueue::value_type(timestamp, pNotification));
		_nfAvailable.Set();
	}


	Notification* TimedNotificationQueue::DequeueNotification()
	{
		FastMutex::ScopedLock lock(_mutex);

		NfQueue::iterator it = _nfQueue.begin();
		if (it != _nfQueue.end())
		{
			int64 sleep = -it->first.elapsed();
			if (sleep <= 0)
			{
				Notification::Ptr pNf = it->second;
				_nfQueue.erase(it);
				return pNf.AddRef();
			}
		}
		return 0;
	}


	Notification* TimedNotificationQueue::WaitDequeueNotification()
	{
		for (;;)
		{
			_mutex.Lock();
			NfQueue::iterator it = _nfQueue.begin();
			if (it != _nfQueue.end())
			{
				_mutex.UnLock();
				int64 sleep = -it->first.elapsed();
				if (sleep <= 0)
				{
					return dequeueOne(it).AddRef();
				}
				else if (!wait(sleep))
				{
					return dequeueOne(it).AddRef();
				}
				else continue;
			}
			else
			{
				_mutex.UnLock();
			}
			_nfAvailable.Wait();
		}
	}


	Notification* TimedNotificationQueue::WaitDequeueNotification(uint32 milliseconds)
	{
		while (milliseconds >= 0)
		{
			_mutex.Lock();
			NfQueue::iterator it = _nfQueue.begin();
			if (it != _nfQueue.end())
			{
				_mutex.UnLock();
				TimeStamp now;
				int64 sleep = it->first - now;
				if (sleep <= 0)
				{
					return dequeueOne(it).AddRef();
				}
				else if (sleep <= int64(milliseconds))
				{
					if (!wait(sleep))
					{
						return dequeueOne(it).AddRef();
					}
					else 
					{
						milliseconds -= static_cast<uint32>((now.elapsed() + 999));
						continue;
					}
				}
			}
			else
			{
				_mutex.UnLock();
			}
			if (milliseconds > 0)
			{
				TimeStamp now;
				_nfAvailable.TryWait(milliseconds);
				milliseconds -= static_cast<uint32>((now.elapsed() + 999));
			}
			else return 0;
		}
		return 0;
	}


	bool TimedNotificationQueue::wait(uint32 interval)
	{
		const int64 MAX_SLEEP = 8*60*60*(int64(1000000)); // sleep at most 8 hours at a time
		while (interval > 0)
		{
			TimeStamp now;
			int64 sleep = interval <= MAX_SLEEP ? interval : MAX_SLEEP;
			if (_nfAvailable.TryWait(static_cast<uint32>((sleep + 999))))
				return true;
			interval -= (uint32)now.elapsed();
		}
		return false;
	}


	bool TimedNotificationQueue::Empty() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return _nfQueue.empty();
	}


	int TimedNotificationQueue::GetSize() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return static_cast<int>(_nfQueue.size());
	}


	void TimedNotificationQueue::Clear()
	{
		FastMutex::ScopedLock lock(_mutex);
		_nfQueue.clear();	
	}


	Notification::Ptr TimedNotificationQueue::dequeueOne(NfQueue::iterator& it)
	{
		FastMutex::ScopedLock lock(_mutex);
		Notification::Ptr pNf = it->second;
		_nfQueue.erase(it);
		return pNf;
	}
}