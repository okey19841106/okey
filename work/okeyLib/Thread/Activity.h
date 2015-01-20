/********************************************************************
	created:	2015/01/20
	created:	15:19
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __THREAD_ACTIVITY_H__
#define __THREAD_ACTIVITY_H__

#include "Runnable.h"
#include "ThreadPool.h"

namespace okey
{
	template<typename C>
	class Activity: public Runnable
	{
		typedef RunnableAdapter<C> RunnableAdapterType;
		typedef typename RunnableAdapterType::_f Callback;
	public:
		Activity(C* pOwner, Callback method):
		  _pOwner(pOwner),
			_runnable(pOwner,method),
			_stopped(true),
			_running(false),
			_done(false)
		{

		}
		virtual ~Activity()
		{
			Stop();
			Wait();
		}

		void Start()
		{
			FastMutex::ScopedLock lock(_mutex);
			if (!_running)
			{
				_done.Reset();
				_stopped = false;
				_running = true;
				try
				{
					ThreadPool::defaultPool().Start(*this);
				}
				catch (...)
				{
					_running = false;
					throw;
				}
			}
		}

		void Stop()
		{
			FastMutex::ScopedLock lock(_mutex);
			_stopped = true;
		}

		void Wait()
		{
			if (_running)
			{
				_done.Wait();
			}
		}

		void Wait(uint32 milliseconds)
		{
			if (_running)
			{
				_done.Wait(milliseconds);
			}
		}

		bool IsStopped() const{ return _stopped;}
		bool IsRunning() const{ return _running;}
	protected:
		void Run()
		{
			try
			{
				_runnable.Run();
			}
			catch (...)
			{
				_running = false;
				_done.Set();
				throw;
			}
			_running = false;
			_done.Set();
		}
	private:
		Activity();
		Activity(const Activity&);
		Activity& operator = (const Activity&);
	private:
		C*                  _pOwner;
		RunnableAdapterType _runnable;
		volatile bool       _stopped;
		volatile bool       _running;
		Event               _done;
		FastMutex           _mutex;
	};
}


#endif