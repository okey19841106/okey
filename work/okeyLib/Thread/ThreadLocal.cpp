#include "PreCom.h"
#include "ThreadLocal.h"
#include "Thread.h"

namespace okey
{
	ThreadLocalStorage::ThreadLocalStorage()
	{

	}

	ThreadLocalStorage::~ThreadLocalStorage()
	{
		for (TLSMap::iterator it = _map.begin(); it != _map.end(); ++it)
		{
			delete it->second;	
		}
	}

	TLSAbstractSlot*& ThreadLocalStorage::Get(const void* key)
	{
		TLSMap::iterator it = _map.find(key);
		if (it == _map.end())
			return _map.insert(TLSMap::value_type(key, reinterpret_cast<TLSAbstractSlot*>(0))).first->second;
		else
			return it->second;
	}

	namespace
	{
		ThreadLocalStorage& GetGlobleTLS()
		{
			static ThreadLocalStorage st;
			return st;
		}
	}

	ThreadLocalStorage& ThreadLocalStorage::Current()
	{
		Thread* pThread = Thread::Current();
		if (pThread)
		{
			return pThread->GetTLS();
		}
		else
		{
			return GetGlobleTLS();//主线程的。
		}
	}

	void ThreadLocalStorage::Clear() //主线程TLS不会被销毁。
	{
		Thread* pThread = Thread::Current();
		if (pThread)
			pThread->ClearTLS();
	}
}