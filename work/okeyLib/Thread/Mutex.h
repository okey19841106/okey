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

	class Mutex : private nocopyable
	{
	public:
	  Mutex()
	  {
#ifdef WINDOWS
		InitializeCriticalSection( &mutex_ );
#else
		pthread_mutex_init(&mutex_, NULL);
#endif
	  }

	  ~Mutex()
	  {
#ifdef WINDOWS
		DeleteCriticalSection( &mutex_ );
#else
		pthread_mutex_destroy(&mutex_);
#endif
	  }

	  void Lock()
	  {
#ifdef WINDOWS
		EnterCriticalSection( &mutex_ );
#else
		pthread_mutex_lock(&mutex_);
#endif
	  }

	  void UnLock()
	  {
#ifdef WINDOWS
		 LeaveCriticalSection( &mutex_ );
#else
		pthread_mutex_unlock(&mutex_);
#endif
	  }

#ifdef WINDOWS
	  CRITICAL_SECTION*
#else
	   pthread_mutex_t* 
#endif
	  getPthreadMutex() /* non-const */
	  {
		return &mutex_;
	  }


	   bool TryLock()
	   {
#ifndef WINDOWS
		   return (pthread_mutex_trylock(&mutex_) == 0);
#else
		   return (TryEnterCriticalSection(&mutex_) == TRUE ? true : false);
#endif
	   }
	   

	 private:
#ifdef WINDOWS
	CRITICAL_SECTION mutex_;
#else
	 pthread_mutex_t mutex_;
#endif
	};

	class MutexGuard:private nocopyable
	{
	public:
		explicit MutexGuard(Mutex& pMutex );
		~MutexGuard();

	public:
		void Lock();
		void UnLock();

	private:
		Mutex& m_pMutex;
		bool m_Owner;
	};

	inline	MutexGuard::MutexGuard( Mutex& pMutex )
		: m_pMutex( pMutex ), m_Owner(false)
	{
		Lock();
	}

	inline	MutexGuard::~MutexGuard()
	{
		UnLock();
	}

	inline	void MutexGuard::Lock()
	{
		m_pMutex.Lock();
		m_Owner = true;
	}

	inline	void MutexGuard::UnLock()
	{
		if( m_Owner )
		{
			m_Owner = false;
			m_pMutex.UnLock();
		}
	}

	class UnMutexGuard:private nocopyable
	{
	public:
		explicit UnMutexGuard(Mutex& pMutex , bool bunlock = true);
		~UnMutexGuard();

	public:
		void Lock();
		void UnLock();

	private:
		Mutex& m_pMutex;
		bool m_Owner;
	};

	inline	UnMutexGuard::UnMutexGuard( Mutex& pMutex , bool bunlock)
		: m_pMutex( pMutex ), m_Owner(bunlock)
	{
		UnLock();
	}

	inline	UnMutexGuard::~UnMutexGuard()
	{
		Lock();
	}

	inline	void UnMutexGuard::Lock()
	{
		m_pMutex.Lock();
		m_Owner = true;
	}

	inline	void UnMutexGuard::UnLock()
	{
		if( m_Owner )
		{
			m_Owner = false;
			m_pMutex.UnLock();
		}
	}
}

// Prevent misuse like:
// MutexLockGuard(mutex_);
// A tempory object doesn't hold the lock for long!

#endif  // MUDUO_BASE_MUTEX_H
