#include "PreCom.h"
#include "RWLock.h"
#include "Exception.h"

namespace okey
{
	RWLock::RWLock()
	{
#ifdef WINDOWS
		_readers = 0;
		_writersWaiting = 0;
		_writers = 0;
		_mutex = CreateMutex(NULL, FALSE, NULL);
		if (_mutex == NULL)
			throw SystemException("cannot create reader/writer lock");

		_readEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
		if (_readEvent == NULL)
			throw SystemException("cannot create reader/writer lock");

		_writeEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
		if (_writeEvent == NULL)
			throw SystemException("cannot create reader/writer lock");
#else
		if (pthread_rwlock_init(&_rwl, NULL))
			throw SystemException("cannot create reader/writer lock");
#endif
	}

	RWLock::~RWLock()
	{
#ifdef WINDOWS
		CloseHandle(_mutex);
		CloseHandle(_readEvent);
		CloseHandle(_writeEvent);
#else
		pthread_rwlock_destroy(&_rwl);
#endif
	}

	void RWLock::ReadLock()
	{
#ifdef WINDOWS
		HANDLE h[2];
		h[0] = _mutex;
		h[1] = _readEvent;
		switch (WaitForMultipleObjects(2, h, TRUE, INFINITE))
		{
		case WAIT_OBJECT_0:
		case WAIT_OBJECT_0 + 1:
			++_readers;
			ResetEvent(_writeEvent);
			ReleaseMutex(_mutex);
			//poco_assert_dbg(_writers == 0);
			break;
		default:
			throw SystemException("cannot lock reader/writer lock");
		}
#else
		if (pthread_rwlock_rdlock(&_rwl)) 
			throw SystemException("cannot lock reader/writer lock");
#endif
		
	}

	bool RWLock::TryReadLock()
	{
#ifdef WINDOWS
		for (;;)
		{
			if (_writers != 0 || _writersWaiting != 0)
				return false;

			DWORD result = tryReadLockOnce();
			switch (result)
			{
			case WAIT_OBJECT_0:
			case WAIT_OBJECT_0 + 1:
				return true;
			case WAIT_TIMEOUT:
				continue; // try again
			default:
				throw SystemException("cannot lock reader/writer lock");
			}
		}
#else
		int rc = pthread_rwlock_tryrdlock(&_rwl);
		if (rc == 0)
			return true;
		else if (rc == EBUSY)
			return false;
		else
			throw SystemException("cannot lock reader/writer lock");
#endif
	}

	void RWLock::WriteLock()
	{
#ifdef WINDOWS
		addWriter();
		HANDLE h[2];
		h[0] = _mutex;
		h[1] = _writeEvent;
		switch (WaitForMultipleObjects(2, h, TRUE, INFINITE))
		{
		case WAIT_OBJECT_0:
		case WAIT_OBJECT_0 + 1:
			--_writersWaiting;
			++_readers;
			++_writers;
			ResetEvent(_readEvent);
			ResetEvent(_writeEvent);
			ReleaseMutex(_mutex);
			//poco_assert_dbg(_writers == 1);
			break;
		default:
			removeWriter();
			throw SystemException("cannot lock reader/writer lock");
		}
#else
		if (pthread_rwlock_wrlock(&_rwl)) 
			throw SystemException("cannot lock reader/writer lock");
#endif
	}

	bool RWLock::TryWriteLock()
	{
#ifdef WINDOWS
		addWriter();
		HANDLE h[2];
		h[0] = _mutex;
		h[1] = _writeEvent;
		switch (WaitForMultipleObjects(2, h, TRUE, 1))
		{
		case WAIT_OBJECT_0:
		case WAIT_OBJECT_0 + 1:
			--_writersWaiting;
			++_readers;
			++_writers;
			ResetEvent(_readEvent);
			ResetEvent(_writeEvent);
			ReleaseMutex(_mutex);
			//poco_assert_dbg(_writers == 1);
			return true;
		case WAIT_TIMEOUT:
			removeWriter();
			return false;
		default:
			removeWriter();
			throw SystemException("cannot lock reader/writer lock");
		}
#else
		int rc = pthread_rwlock_trywrlock(&_rwl);
		if (rc == 0)
			return true;
		else if (rc == EBUSY)
			return false;
		else
			throw SystemException("cannot lock reader/writer lock");
#endif
	}

	void RWLock::Unlock()
	{
#ifdef WINDOWS
		switch (WaitForSingleObject(_mutex, INFINITE))
		{
		case WAIT_OBJECT_0:
			_writers = 0;
			if (_writersWaiting == 0)
				SetEvent(_readEvent);
			if (--_readers == 0)
				SetEvent(_writeEvent);
			ReleaseMutex(_mutex);
			break;
		default:
			throw SystemException("cannot unlock reader/writer lock");
		}
#else
		if (pthread_rwlock_unlock(&_rwl))
			throw SystemException("cannot unlock mutex");
#endif
	}

#ifdef WINDOWS
	void RWLock::addWriter()
	{
		switch (WaitForSingleObject(_mutex, INFINITE))
		{
		case WAIT_OBJECT_0:
			if (++_writersWaiting == 1) 
				ResetEvent(_readEvent);
			ReleaseMutex(_mutex);
			break;
		default:
			throw SystemException("cannot lock reader/writer lock");
		}
	}
	void RWLock::removeWriter()
	{
		switch (WaitForSingleObject(_mutex, INFINITE))
		{
		case WAIT_OBJECT_0:
			if (--_writersWaiting == 0 && _writers == 0) 
				SetEvent(_readEvent);
			ReleaseMutex(_mutex);
			break;
		default:
			throw SystemException("cannot lock reader/writer lock");
		}
	}
	DWORD RWLock::tryReadLockOnce()
	{
		HANDLE h[2];
		h[0] = _mutex;
		h[1] = _readEvent;
		DWORD result = WaitForMultipleObjects(2, h, TRUE, 1); 
		switch (result)
		{
		case WAIT_OBJECT_0:
		case WAIT_OBJECT_0 + 1:
			++_readers;
			ResetEvent(_writeEvent);
			ReleaseMutex(_mutex);
			//poco_assert_dbg(_writers == 0);
			return result;
		case WAIT_TIMEOUT:
			return result;
		default:
			throw SystemException("cannot lock reader/writer lock");
		}
	}
#endif

}