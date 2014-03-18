#include "PoolAllocator.h"

namespace okey
{
	template<typename T>
	PoolAllocator<T>::PoolAllocator()
	{
		m_freecount = 0;
		m_count = 0;
		m_memusage = 0;
		m_objsize = 0;
		m_cellsize = sizeof(sMemoryCell);
		m_phead = NULL;
	}

	template<typename T>
	PoolAllocator<T>::PoolAllocator(int32 size)
	{
		m_cellsize = size + sizeof(sMemoryCell);
		m_freecount = 0;
		m_count = 0;
		m_memusage = 0;
		m_objsize = size;
		m_phead = NULL;
	}


	template<typename T>
	PoolAllocator<T>::~PoolAllocator()
	{

	}
	template<typename T>
	void* PoolAllocator<T>::DLMalloc(int32 size)
	{
		if (size > m_objsize)
		{
			return NULL;
		}
		return PopMemory();
	}
	template<typename T>
	void PoolAllocator<T>::DLFree(void* ptr)
	{
		if (!ptr)
		{
			return;
		}
		PushMemory(ptr);
	}
	template<typename T>
	void PoolAllocator<T>::SetMemoryInfo(const MemoryHead& info)
	{
		m_info.AllocInfo = info.AllocInfo;
		m_info.MemInfo = m_cellsize;
	}
	template<typename T>
	bool PoolAllocator<T>::Init(int32 size)
	{
		m_cellsize = size + sizeof(sMemoryCell);
		m_objsize = size;
		m_info.MemInfo = m_cellsize;
		m_info.AllocInfo = 0;
		return true;
	}
	template<typename T>
	void PoolAllocator<T>::CollectMemory()
	{
		m_mutex.Lock();
		while (m_phead)
		{
			//char* ptr = (char*)m_phead;
			sMemoryCell* realptr = m_phead;
			if (realptr->m_info.MemInfo & 0x80000000)
			{
				return;
			}
			m_phead = m_phead->m_pnext;
			::free((void*)realptr);
			m_memusage -= m_cellsize;
			--m_count;
			--m_freecount;
		}
		m_mutex.UnLock();
	}
	template<typename T>
	bool PoolAllocator<T>::IsValidMemory(void* ptr)
	{
		if (!ptr)
		{
			return false;
		}
		sMemoryCell* pCell = (sMemoryCell*)( (char*)ptr - sizeof(sMemoryCell) );
		return ((pCell->m_info.MemInfo & 0x80000000) && 
			(pCell->m_info.AllocInfo == m_info.AllocInfo) && 
			((pCell->m_info.MemInfo << 2) == (pCell->m_info.MemInfo << 2)));
	}
	template<typename T>
	int32 PoolAllocator<T>::GetAllocInfo(void* ptr)
	{
		if (!ptr)
		{
			return -1;
		}
		sMemoryCell* realptr = (sMemoryCell*)( (char*)ptr - sizeof(sMemoryCell) );
		return realptr->m_info.AllocInfo;
	}
	template<typename T>
	int64 PoolAllocator<T>::GetMemroyUsage()
	{
		return m_memusage;
	}
	template<typename T>
	void* PoolAllocator<T>::PopMemory()
	{
		m_mutex.Lock();
		char* res = NULL;
		if (NULL == m_phead)
		{
			res = (char*)::malloc(m_cellsize);
			if (!res)
			{
				return NULL;
			}
			((sMemoryCell*)res)->m_info = m_info;
			((sMemoryCell*)res)->m_info.MemInfo |= 0x80000000;
			res = res + sizeof(sMemoryCell);
			m_memusage += m_cellsize;
			++m_count;
		}
		else
		{
			res = (char*)m_phead;
			((sMemoryCell*)res)->m_info = m_info;
			((sMemoryCell*)res)->m_info.MemInfo |= 0x80000000;
			res = res + sizeof(sMemoryCell);
			m_phead = m_phead->m_pnext;
			--m_freecount;
		}
		m_mutex.UnLock();
		return (void*)res;
	}
	template<typename T>
	void PoolAllocator<T>::PushMemory(void* ptr)
	{
		m_mutex.Lock();
		if (!ptr)
		{
			return;
		}
		sMemoryCell* pCell = (sMemoryCell*)( (char*)ptr - sizeof(sMemoryCell) );
		if (pCell->m_info.AllocInfo != m_info.AllocInfo)
		{
			printf("error in PushMemory! %d, %d", pCell->m_info.AllocInfo, m_info.AllocInfo);
			::free((void*)pCell);
			return;
		}
		pCell->m_info.MemInfo &= 0x7fffffff;
		pCell->m_pnext = m_phead;
		m_phead = pCell;
		++m_freecount;
		m_mutex.UnLock();
	}
}
