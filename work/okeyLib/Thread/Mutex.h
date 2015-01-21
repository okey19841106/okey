/********************************************************************
	created:	2014/09/09
	created:	10:28
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef OKEY_BASE_MUTEX_H
#define OKEY_BASE_MUTEX_H

#ifdef  WINDOWS
	//#include <windows.h>

#else
#include <pthread.h>
#endif

#include "nocopyable.h"
#include "Types.h"



namespace okey
{

	template<typename M>
	class ScopedLock
	{
	public:
		ScopedLock(M& m):_m(m){_m.Lock();}
		~ScopedLock(){_m.UnLock();}
	private:
		M& _m;
	private:
		ScopedLock();
		ScopedLock(const ScopedLock&);
		ScopedLock& operator = (const ScopedLock&);
	};

	template<typename M>
	class ScopedLockWithUnlock
	{
	public:
		ScopedLockWithUnlock(M& m):_m(&m){_m->Lock();}
		~ScopedLockWithUnlock(){UnLock();}
		void UnLock()
		{
			if (_m)
			{
				_m->UnLock();
				_m = NULL;
			}
		}
	private:
		ScopedLockWithUnlock();
		ScopedLockWithUnlock(const ScopedLockWithUnlock&);
		ScopedLockWithUnlock& operator = (const ScopedLockWithUnlock&);
	private:
		M* _m;
	};

	template<typename M>
	class ScopedUnLock
	{
	public:
		ScopedUnLock(M& m, bool unlockNow = true):_m(m), _bUnLock(unlockNow)
		{
			if (_bUnLock)
			{
				_m->Lock();
			}
		}
		~ScopedUnLock()
		{
			_m->Lock();
		}
	private:
		ScopedUnLock();
		ScopedUnLock(const ScopedUnLock&);
		ScopedUnLock& operator = (const ScopedUnLock&);
	private:
		bool _bUnLock;
		M& _m;
	};

	class Mutex : private nocopyable
	{
	public:
		typedef ScopedLock<Mutex> ScopedLock;
		typedef ScopedLockWithUnlock<Mutex> ScopedLockWithUnlock;
		typedef ScopedUnLock<Mutex> ScopedUnLock;
	public:
		Mutex();
#ifdef LINUX
		Mutex(bool fast);
#endif
		~Mutex();
		void Lock();
		void UnLock();
		bool TryLock();
	private:
#ifdef WINDOWS
		CRITICAL_SECTION _mutex;
#else
		pthread_mutex_t _mutex;
#endif
	};


#ifdef WINDOWS
	typedef Mutex FastMutex;
#else
	class FastMutex : public Mutex
	{
	public:
		typedef ScopedLock<FastMutex> ScopedLock;
		typedef ScopedLockWithUnlock<FastMutex> ScopedLockWithUnlock;
		typedef ScopedUnLock<FastMutex> ScopedUnLock;
	public:
		FastMutex():Mutex(true){}
		~FastMutex(){}
	};
#endif

	class NullLock: public nocopyable
	{
	public:
		NullLock(){}
		~NullLock(){}
		void Lock(){}
		void UnLock(){}
		bool TryLock(){return true;}
	};

}

// Prevent misuse like:
// MutexLockGuard(mutex_);
// A tempory object doesn't hold the lock for long!

#endif  // MUDUO_BASE_MUTEX_H
