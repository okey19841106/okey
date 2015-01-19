/********************************************************************
	created:	2015/01/18
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_RW_LOCK_H__
#define __OKEY_RW_LOCK_H__

#include "Types.h"

namespace okey
{
	class ScopedRWLock;
	class ScopedReadRWLock;
	class ScopedWriteRWLock;

	class RWLock
	{
	public:
		typedef ScopedRWLock ScopedLock;
		typedef ScopedReadRWLock ScopedReadLock;
		typedef ScopedWriteRWLock ScopedWriteLock;
	public:
		RWLock();
		~RWLock();
		void ReadLock();
		bool TryReadLock();
		void WriteLock();
		bool TryWriteLock();
		void Unlock();
	private:
		RWLock(const RWLock&);
		RWLock& operator = (const RWLock&);
	private:
#ifdef WINDOWS
		void addWriter();
		void removeWriter();
		DWORD tryReadLockOnce();

		HANDLE   _mutex; //互斥锁和读写时间控制。
		HANDLE   _readEvent;
		HANDLE   _writeEvent;
		unsigned _readers;
		unsigned _writersWaiting;
		unsigned _writers;
#else
		pthread_rwlock_t _rwl;
#endif
	};
}

#endif