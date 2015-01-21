/********************************************************************
	created:	2015/01/21
	created:	15:12
	author:		okey
	
	purpose:	¶¨Ê±Æ÷¡£
*********************************************************************/
#ifndef __THREAD_TIMER_H__
#define __THREAD_TIMER_H__

#include "Runnable.h"
#include "TimeStamp.h"
#include "Event.h"
#include "Mutex.h"
#include "Thread.h"

namespace okey
{
	class AbstractTimerCallback;
	class ThreadPool;

	class Timer : public Runnable
	{
	public:
		Timer(uint32 startInterval = 0, uint32 periodicInterval = 0);
		virtual ~Timer();
		void Start(const AbstractTimerCallback& method);		/// Starts the timer.
		void Start(const AbstractTimerCallback& method, Thread::Priority priority);		/// Starts the timer in a thread with the given priority.
		void Start(const AbstractTimerCallback& method, ThreadPool& threadPool); /// Starts the timer.
		void Start(const AbstractTimerCallback& method, Thread::Priority priority, ThreadPool& threadPool); /// Starts the timer in a thread with the given priority.
		void Stop();		/// Stops the timer.
		void ReStart();		/// Restarts the periodic interval. 
		void ReStart(uint32 milliseconds);		/// Sets a new periodic interval and restarts the timer.
		uint32 GetStartInterval() const;		/// Returns the start interval.
		void SetStartInterval(uint32 milliseconds);		/// Sets the start interval. 
		uint32 GetPeriodicInterval() const;		/// Returns the periodic interval.
		void SetPeriodicInterval(uint32 milliseconds);		/// Sets the periodic interval. 
		uint32 Skipped() const;
	protected:
		void Run();
	private:
		Timer(const Timer&);
		Timer& operator = (const Timer&);
	private:
		volatile uint32 _startInterval;
		volatile uint32 _periodicInterval;
		Event         _wakeUp;
		Event         _done;
		uint32        _skipped;
		AbstractTimerCallback* _pCallback;
		TimeStamp              _nextInvocation;
		mutable FastMutex      _mutex;

	};

	class AbstractTimerCallback
	{
	public:
		AbstractTimerCallback();
		AbstractTimerCallback(const AbstractTimerCallback& callback);
		virtual ~AbstractTimerCallback();
		AbstractTimerCallback& operator = (const AbstractTimerCallback& callback);
		virtual void Invoke(Timer& timer) const = 0;
		virtual AbstractTimerCallback* Clone() const = 0;
	};

	template <typename C>
	class TimerCallback: public AbstractTimerCallback
	{
	public:
		typedef void (C::*Callback)(Timer&);
	public:
		TimerCallback(C* obj, Callback method):_obj(obj),_callback(method)
		{

		}
		TimerCallback(const TimerCallback& callback): _obj(callback.obj), _callback(callback.method)
		{
		}
		TimerCallback& operator = (const TimerCallback& callback)
		{
			if (&callback != this)
			{
				_obj = callback._obj;
				_callback  = callback._callback;
			}
			return *this;
		}
		virtual ~TimerCallback()
		{

		}
		virtual void Invoke(Timer& timer) const
		{
			(_obj->*Callback)(timer);
		}
		virtual AbstractTimerCallback* Clone() const
		{
			return return new TimerCallback(*this);
		}
	private:
		C* _obj;
		Callback _callback;
		

	};
}

#endif