/********************************************************************
	created:	2014/09/09
	created:	10:28
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef OKEY_BASE_CONDITION_H
#define OKEY_BASE_CONDITION_H


#include <deque>
#include "Mutex.h"

namespace okey
{

	class Event;

	class Condition
	{
	public:
		Condition();
		~Condition();
		template<typename M>
		void Wait(M& mutex)
		{
			ScopedUnLock<M> unlock(mutex, false);
			Event event;
			{
				FastMutex::ScopedLock lock(_mutex);
				mutex.UnLock();
				enqueue(event);
			}
			event.Wait();
		}
		template<typename M>
		void Wait(M& mutex, uint32 milliseconds)
		{
			if (!TryWait(mutex,milliseconds))
			{
				throw TimeoutException("Condition is Time Out");
			}
		}
		template<typename M>
		bool TryWait(M& mutex, uint32 milliseconds)
		{
			ScopedUnLock<M> unlock(mutex, false);
			Event event;
			{
				FastMutex::ScopedLock lock(_mutex);
				mutex.UnLock();
				enqueue(event);
			}
			if (!event.TryWait(milliseconds))
			{
				FastMutex::ScopedLock lock(_mutex);
				dequeue(event);
				return false;
			}
			return true;
		}

		void Signal();
		void Broascast();
	protected:
		void enqueue(Event& event);
		void dequeue();
		void dequeue(Event& event);
	private:
		Condition(const Condition&);
		Condition& operator = (const Condition&);
		typedef std::deque<Event*> WaitQueue;
		FastMutex _mutex;
		WaitQueue _waitQueue;
	};
}
#endif  // MUDUO_BASE_CONDITION_H
