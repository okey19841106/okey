#include "PreCom.h"
#include "Timer.h"
#include "ThreadPool.h"
#include "ErrorHandler.h"

namespace okey
{
	Timer::Timer(uint32 startInterval, uint32 periodicInterval):
	_startInterval(startInterval), _periodicInterval(periodicInterval),
		_skipped(0),_pCallback(NULL)
	{

	}
	Timer::~Timer()
	{
		Stop();
	}
	void Timer::Start(const AbstractTimerCallback& method)
	{
		Start(method, Thread::PRIO_NORMAL, ThreadPool::defaultPool());

	}
	void Timer::Start(const AbstractTimerCallback& method, Thread::Priority priority)
	{
		Start(method, priority, ThreadPool::defaultPool());
	}
	void Timer::Start(const AbstractTimerCallback& method, ThreadPool& threadPool)
	{
		Start(method, Thread::PRIO_NORMAL, threadPool);
	}
	void Timer::Start(const AbstractTimerCallback& method, Thread::Priority priority, ThreadPool& threadPool)
	{
		TimeStamp nextInvocation;
		nextInvocation += static_cast<int64>(_startInterval);
		FastMutex::ScopedLock lock(_mutex);	
		_nextInvocation = nextInvocation;
		_pCallback = method.Clone();
		_wakeUp.Reset();
		threadPool.StartWithPriority(priority, *this);
	}
	void Timer::Stop()
	{
		FastMutex::ScopedLock lock(_mutex);
		if (_pCallback)
		{
			_periodicInterval = 0;
			_mutex.UnLock();
			_wakeUp.Set();
			_done.Wait(); // warning: deadlock if called from timer callback
			_mutex.Lock();
			delete _pCallback;
			_pCallback = 0;
		}
	}

	void Timer::ReStart()
	{
		FastMutex::ScopedLock lock(_mutex);
		if (_pCallback)
		{
			_wakeUp.Set();
		}
	}

	void Timer::ReStart(uint32 milliseconds)//输入0的时候会推出这个线程。
	{
		FastMutex::ScopedLock lock(_mutex);
		if (_pCallback)
		{
			_periodicInterval = milliseconds;
			_wakeUp.Set();
		}
	}

	uint32 Timer::GetStartInterval() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return _startInterval;
	}

	void Timer::SetStartInterval(uint32 milliseconds)
	{
		FastMutex::ScopedLock lock(_mutex);
		_startInterval = milliseconds;
	}

	uint32 Timer::GetPeriodicInterval() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return _periodicInterval;
	}

	void Timer::SetPeriodicInterval(uint32 milliseconds)
	{
		FastMutex::ScopedLock lock(_mutex);
		_periodicInterval = milliseconds;
	}

	uint32 Timer::Skipped() const
	{
		return _skipped;
	}

	void Timer::Run()
	{
		TimeStamp now;
		uint32 interval(0);
		do
		{
			int32 sleep(0);
			do
			{
				now = TimeStamp::CurrentTime();
				sleep = static_cast<int32>((_nextInvocation - now));
				if (sleep < 0)
				{
					if (interval == 0) //超时。。
					{
						sleep = 0;
						break;
					}
					_nextInvocation += static_cast<int64>(interval);
					++_skipped;
				}
			}
			while (sleep < 0);

			if (_wakeUp.TryWait(sleep)) //stop会在这里。restart.
			{
				FastMutex::ScopedLock lock(_mutex);
				_nextInvocation = TimeStamp::CurrentTime();
				interval = _periodicInterval;
			}
			else
			{
				try
				{
					_pCallback->Invoke(*this);
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
				interval = _periodicInterval;
			}
			_nextInvocation += static_cast<int64>(interval);
			_skipped = 0;
		}
		while (interval > 0);
		_done.Set();
	}

	AbstractTimerCallback::AbstractTimerCallback()
	{

	}
	AbstractTimerCallback::AbstractTimerCallback(const AbstractTimerCallback& callback)
	{

	}
	AbstractTimerCallback::~AbstractTimerCallback()
	{

	}
	AbstractTimerCallback& AbstractTimerCallback::operator = (const AbstractTimerCallback& callback)
	{
		return *this;
	}
}