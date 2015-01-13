/********************************************************************
	created:	2014/09/09
	created:	10:28
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef OKEY_BASE_CONDITION_H
#define OKEY_BASE_CONDITION_H


#include <deque>

namespace okey
{
	class Mutex;
	class Event;

	class Condition
	{
	public:
		Condition();
		~Condition();
		void Wait(Mutex& mutex);
		void Wait(Mutex& mutex, uint32 milliseconds);
		bool TryWait(Mutex& mutex, uint32 milliseconds);
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
		Mutex _mutex;
		WaitQueue _waitQueue;
	};
}
#endif  // MUDUO_BASE_CONDITION_H
