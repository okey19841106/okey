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

	void Condition::Signal()
	{
		FastMutex::ScopedLock lock(_mutex);
		if (!_waitQueue.empty())
		{
			_waitQueue.front()->Set();
			dequeue();
		}
	}

	void Condition::Broascast()
	{
		FastMutex::ScopedLock lock(_mutex);
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