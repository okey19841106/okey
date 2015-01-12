#include "PreCom.h"
#include "Event.h"
#include "Exception.h"

namespace okey
{
	Event::Event(bool autoReset)
	{
#ifdef WINDOWS
		_event = CreateEvent(NULL, autoReset ? FALSE : TRUE, FALSE, NULL);
		if (!_event)
			throw SystemException("cannot create event");
#else
		if (pthread_mutex_init(&_mutex, NULL))
			throw SystemException("cannot create event (mutex)");
		if (pthread_cond_init(&_cond, NULL))
			throw SystemException("cannot create event (condition)");
#endif
	}
	Event::~Event()
	{
#ifdef WINDOWS
		CloseHandle(_event);
#else
		pthread_cond_destroy(&_cond);
		pthread_mutex_destroy(&_mutex);
#endif
	}

	void Event::Set()
	{
#ifdef WINDOWS
		if (!SetEvent(_event))
		{
			throw SystemException("cannot signal event");
		}
#else
		if (pthread_mutex_lock(&_mutex))	
			throw SystemException("cannot signal event (lock)");
		_state = true;
		if (pthread_cond_broadcast(&_cond))
		{
			pthread_mutex_unlock(&_mutex);
			throw SystemException("cannot signal event");
		}
		pthread_mutex_unlock(&_mutex);
#endif
	}
	void Event::Wait()
	{
#ifdef WINDOWS
		switch (WaitForSingleObject(_event, INFINITE))
		{
		case WAIT_OBJECT_0:
			return;
		default:
			throw SystemException("wait for event failed");
		}
#else
		if (pthread_mutex_lock(&_mutex))
			throw SystemException("wait for event failed (lock)"); 
		while (!_state) 
		{
			if (pthread_cond_wait(&_cond, &_mutex))
			{
				pthread_mutex_unlock(&_mutex);
				throw SystemException("wait for event failed");
			}
		}
		if (_auto)
			_state = false;
		pthread_mutex_unlock(&_mutex);
#endif
	}

	bool Event::Wait(long milliseconds)
	{
#ifdef WINDOWS
		switch (WaitForSingleObject(_event, milliseconds + 1))
		{
		case WAIT_TIMEOUT:
			return false;
		case WAIT_OBJECT_0:
			return true;
		default:
			throw SystemException("wait for event failed");		
		}
#else
		struct timeval tv;
		gettimeofday(&tv, NULL);
		abstime.tv_sec  = tv.tv_sec + milliseconds / 1000;
		abstime.tv_nsec = tv.tv_usec*1000 + (milliseconds % 1000)*1000000;
		if (abstime.tv_nsec >= 1000000000)
		{
			abstime.tv_nsec -= 1000000000;
			abstime.tv_sec++;
		}
		if (pthread_mutex_lock(&_mutex) != 0)
			throw SystemException("wait for event failed (lock)"); 
		while (!_state) 
		{
			if ((rc = pthread_cond_timedwait(&_cond, &_mutex, &abstime)))
			{
				if (rc == ETIMEDOUT) break;
				pthread_mutex_unlock(&_mutex);
				throw SystemException("cannot wait for event");
			}
		}
		if (rc == 0 && _auto) _state = false;
		pthread_mutex_unlock(&_mutex);
		return rc == 0;
#endif
	}

	bool Event::TryWait(long milliseconds)
	{
		return Wait(milliseconds);
	}

	void Event::Reset()
	{
#ifdef WINDOWS
		if (!ResetEvent(_event))
		{
			throw SystemException("cannot reset event");
		}
#else
		if (pthread_mutex_lock(&_mutex))	
			throw SystemException("cannot reset event");
		_state = false;
		pthread_mutex_unlock(&_mutex);
#endif
	}
}