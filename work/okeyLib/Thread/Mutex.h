//////////////////////////////////////////////////////////////
//                      .----.
//                   _.'__    `.
//             .--(#)(##)---/#\
//           .' @            /###\
//           :         ,       #####
//            `-..__.-' _.-  \###/ 
//                   `;_:         `"'
//                 .'"""""`.
//                /,         ,\
//               //           \\
//               `-._______.-'
//                ___`. | .'___
//             (______|______)
//
//  created:	2011-9-1 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////

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
		  // use critical sections in windows; much faster
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

	   /*
	   bool TryLock()
	   	   {
	   #ifndef WINDOWS
	   		   return (pthread_mutex_trylock(&mutex_) == 0);
	   #else
	   		   return (TryEnterCriticalSection(&mutex_) == TRUE ? true : false);
	   #endif
	   	   }*/
	   

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

	inline
		MutexGuard::MutexGuard( Mutex& pMutex )
		: m_pMutex( pMutex ), m_Owner(false)
	{
		Lock();
	}

	inline
	MutexGuard::~MutexGuard()
	{
		UnLock();
	}

	inline
	void MutexGuard::Lock()
	{
		m_pMutex.Lock();
		m_Owner = true;
	}

	inline
	void MutexGuard::UnLock()
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
