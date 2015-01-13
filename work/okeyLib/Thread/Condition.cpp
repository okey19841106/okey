#include "PreCom.h"
#include "Condition.h"
#include "Mutex.h"
#include "Event.h"
#include "Exception.h"

namespace okey{

	Condition::Condition()
	{

	}

	Condition::~Condition()
	{

	}

	void Condition::Wait(Mutex& mutex)
	{
		
		UnMutexGuard unlock(mutex, false);
		Event event;
		{
			MutexGuard lock(_mutex);
			mutex.UnLock();
			enqueue(event);
		}
		event.Wait();
	}

	void Condition::Wait(Mutex& mutex, uint32 milliseconds)
	{
		if (!TryWait(mutex,milliseconds))
		{
			throw TimeoutException("Condition is Time Out");
		}
	}

	bool Condition::TryWait(Mutex& mutex, uint32 milliseconds)
	{
		UnMutexGuard unlock(mutex, false);
		Event event;
		{
			MutexGuard lock(_mutex);
			mutex.UnLock();
			enqueue(event);
		}
		if (!event.TryWait(milliseconds))
		{
			MutexGuard lock(_mutex);
			dequeue(event);
			return false;
		}
		return true;
	}

	void Condition::Signal()
	{
		MutexGuard lock(_mutex);
		if (!_waitQueue.empty())
		{
			_waitQueue.front()->Set();
			dequeue();
		}
	}

	void Condition::Broascast()
	{
		MutexGuard lock(_mutex);
		for (WaitQueue::iterator it = _waitQueue.begin(); it != _waitQueue.end(); ++it)
		{
			(*it)->Set();
		}
		_waitQueue.clear();
	}

	void Condition::enqueue(Event& event)
	{
		_waitQueue.push_back(&event);
	}

	void Condition::dequeue()
	{
		_waitQueue.pop_front();
	}

	void Condition::dequeue(Event& event)
	{
		for (WaitQueue::iterator it = _waitQueue.begin(); it != _waitQueue.end(); ++it)
		{
			if (*it == &event)
			{
				_waitQueue.erase(it);
				break;
			}
		}
	}
}