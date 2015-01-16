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

	ThreadLocalStorage& ThreadLocalStorage::Current()
	{
		Thread* pThread = Thread::Current();
		if (pThread)
		{
			return pThread->GetTLS();
		}
		else
		{
			return *sh.get();
		}
	}

	void ThreadLocalStorage::Clear()
	{
		Thread* pThread = Thread::Current();
		if (pThread)
			pThread->ClearTLS();
	}
}