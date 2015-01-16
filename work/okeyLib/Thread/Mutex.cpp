#include "PreCom.h"
#include "Mutex.h"
#include "Exception.h"

namespace okey
{
	Mutex::Mutex()
	{
#ifdef WINDOWS
		InitializeCriticalSectionAndSpinCount(&_mutex, 4000);
#else
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE); //可重入锁。
		if (pthread_mutex_init(&_mutex, &attr))
		{
			pthread_mutexattr_destroy(&attr);
			throw SystemException("cannot create mutex");
		}
		pthread_mutexattr_destroy(&attr);
#endif
	}
#ifdef LINUX
	Mutex::Mutex(bool fast)
	{
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, fast ?PTHREAD_MUTEX_NORMAL:PTHREAD_MUTEX_RECURSIVE); //可重入锁。或者是不可重入锁。
		if (pthread_mutex_init(&_mutex, &attr))
		{
			pthread_mutexattr_destroy(&attr);
			throw SystemException("cannot create mutex");
		}
		pthread_mutexattr_destroy(&attr);
	}
#endif

	Mutex::~Mutex()
	{
#ifdef WINDOWS
		DeleteCriticalSection(&_mutex);
#else
		pthread_mutex_destroy(&_mutex);
#endif
	}
	void Mutex::Lock()
	{
#ifdef WINDOWS
		try
		{
			EnterCriticalSection(&_mutex);
		}
		catch (...)
		{
			throw SystemException("cannot lock mutex");
		}
#else
		if (pthread_mutex_lock(&_mutex)) 
			throw SystemException("cannot lock mutex");
#endif
	}
	void Mutex::UnLock()
	{
#ifdef WINDOWS
		try
		{
			LeaveCriticalSection(&_mutex);
		}
		catch (...)
		{
		}
		throw SystemException("cannot unlock mutex");
#else
		if (pthread_mutex_unlock(&_mutex)) 
			throw SystemException("cannot unlock mutex");
#endif
	}
	bool Mutex::TryLock()
	{
#ifdef WINDOWS
		try
		{
			return TryEnterCriticalSection(&_mutex) != 0;
		}
		catch (...)
		{
		}
		throw SystemException("cannot lock mutex");
#else
		int rc = pthread_mutex_trylock(&_mutex);
		if (rc == 0)
			return true;
		else if (rc == EBUSY)
			return false;
		else
			throw SystemException("cannot lock mutex");
#endif
	}

}
