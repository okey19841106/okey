#include "PreCom.h"
#include "Semaphore.h"
#include "Exception.h"

#ifdef WINDOWS
#include <limits>
#endif


namespace okey
{

	Semaphore::Semaphore(int n)
	{
#ifdef WINDOWS
		_sema = CreateSemaphore(NULL, n, n, NULL);
		if (!_sema)
		{
			throw SystemException("cannot create semaphore");
		}
#else
		_n = n;
		_max = n;
		if (pthread_mutex_init(&_mutex, NULL))
			throw SystemException("cannot create semaphore (mutex)");
		if (pthread_cond_init(&_cond, NULL))
			throw SystemException("cannot create semaphore (condition)");
#endif
	}

	Semaphore::Semaphore(int n, int max)
	{
		//poco_assert (n >= 0 && max > 0 && n <= max);
#ifdef WINDOWS
		_sema = CreateSemaphore(NULL, n, max, NULL);
		if (!_sema)
		{
			throw SystemException("cannot create semaphore");
		}
#else
		_n = n;
		_max = max;
		if (pthread_mutex_init(&_mutex, NULL))
			throw SystemException("cannot create semaphore (mutex)");
		if (pthread_cond_init(&_cond, NULL))
			throw SystemException("cannot create semaphore (condition)");
#endif
		
	}
	Semaphore::~Semaphore()
	{
#ifdef WINDOWS
		CloseHandle(_sema);
#else
		pthread_cond_destroy(&_cond);
		pthread_mutex_destroy(&_mutex);
#endif
	}

	void Semaphore::Set()
	{
#ifdef WINDOWS
		if (!ReleaseSemaphore(_sema, 1, NULL))
		{
			throw SystemException("cannot signal semaphore");
		}
#else
		if (pthread_mutex_lock(&_mutex))	
			throw SystemException("cannot signal semaphore (lock)");
		if (_n < _max)
		{
			++_n;
		}
		else
		{
			pthread_mutex_unlock(&_mutex);
			throw SystemException("cannot signal semaphore: count would exceed maximum");
		}	
		if (pthread_cond_signal(&_cond))
		{
			pthread_mutex_unlock(&_mutex);
			throw SystemException("cannot signal semaphore");
		}
		pthread_mutex_unlock(&_mutex);
#endif
	}

	void Semaphore::Wait()
	{
#ifdef WINDOWS
		switch (WaitForSingleObject(_sema, INFINITE))
		{
		case WAIT_OBJECT_0:
			return;
		default:
			throw SystemException("wait for semaphore failed");
		}
#else
		if (pthread_mutex_lock(&_mutex))
			throw SystemException("wait for semaphore failed (lock)"); 
		while (_n < 1) 
		{
			if (pthread_cond_wait(&_cond, &_mutex))//在里边会有解锁
			{
				pthread_mutex_unlock(&_mutex);
				throw SystemException("wait for semaphore failed");
			}
		}
		--_n;
		pthread_mutex_unlock(&_mutex);
#endif
	}

	bool Semaphore::Wait(uint32 milliseconds)
	{
#ifdef WINDOWS
		switch (WaitForSingleObject(_sema, milliseconds+1))
		{
		case WAIT_TIMEOUT:
			return false;
		case WAIT_OBJECT_0:
			return true;
		default:
			throw SystemException("wait for semaphore failed");	
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
			throw SystemException("wait for semaphore failed (lock)"); 
		while (_n < 1) 
		{
			if ((rc = pthread_cond_timedwait(&_cond, &_mutex, &abstime)))
			{
				if (rc == ETIMEDOUT) break;
				pthread_mutex_unlock(&_mutex);
				throw SystemException("cannot wait for semaphore");
			}
		}
		if (rc == 0) --_n;
		pthread_mutex_unlock(&_mutex);
		return rc == 0;
#endif
	}

	bool Semaphore::TryWait(uint32 milliseconds)
	{
		return Wait(milliseconds);
	}
	

}
