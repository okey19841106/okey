#include "PreCom.h"
#include "PoolAllocator.h"

namespace okey
{
	
	PoolAllocator::PoolAllocator()
	{
		m_freecount = 0;
		m_count = 0;
		m_memusage = 0;
		m_objsize = 0;
		m_cellsize = sizeof(sMemoryCell);
		m_info.AllocInfo = 0;
		m_info.MemInfo = m_cellsize;
		m_phead = NULL;
	}

	
	PoolAllocator::PoolAllocator(int32 size)
	{
		m_cellsize = size + sizeof(sMemoryCell);
		m_freecount = 0;
		m_count = 0;
		m_memusage = 0;
		m_objsize = size;
		m_phead = NULL;
		m_info.MemInfo = m_cellsize;
		m_info.AllocInfo = 0;
	}


	
	PoolAllocator::~PoolAllocator()
	{

	}
	
	void* PoolAllocator::Malloc(int32 size)
	{
		if (size > m_objsize)
		{
			return NULL;
		}
		return PopMemory();
	}
	
	void PoolAllocator::Free(void* ptr)
	{
		if (!ptr)
		{
			return;
		}
		PushMemory(ptr);
	}
	
	void PoolAllocator::SetMemoryInfo(const MemoryHead& info)
	{
		m_info.AllocInfo = info.AllocInfo;
		m_info.MemInfo = m_cellsize;
	}
	
	bool PoolAllocator::Init(int32 size)
	{
		m_cellsize = size + sizeof(sMemoryCell);
		m_objsize = size;
		m_info.MemInfo = m_cellsize;
		m_info.AllocInfo = 0;
		return true;
	}
	
	void PoolAllocator::CollectMemory()
	{
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
	}
	
	bool PoolAllocator::IsValidMemory(void* ptr)
	{
		if (!ptr)
		{
			return false;
		}
		sMemoryCell* pCell = (sMemoryCell*)( (char*)ptr - sizeof(MemoryHead) );
		return ((pCell->m_info.MemInfo & 0x80000000) && 
			(pCell->m_info.AllocInfo == m_info.AllocInfo) && 
			((pCell->m_info.MemInfo << 2) == (pCell->m_info.MemInfo << 2)));
	}
	
	int32 PoolAllocator::GetAllocInfo(void* ptr)
	{
		if (!ptr)
		{
			return -1;
		}
		sMemoryCell* realptr = (sMemoryCell*)( (char*)ptr - sizeof(MemoryHead) );
		return realptr->m_info.AllocInfo;
	}
	
	int64 PoolAllocator::GetMemroyUsage()
	{
		return m_memusage;
	}
	
	void* PoolAllocator::PopMemory()
	{
		char* res = NULL;
		if (NULL == m_phead)
		{
			res = (char*)::malloc(m_cellsize);
			if (!res)
			{
				return NULL;
			}
			*((MemoryHead*)res) = m_info;
			((MemoryHead*)res)->MemInfo |= 0x80000000;
			res = res + sizeof(MemoryHead);
			m_memusage += m_cellsize;
			++m_count;
		}
		else
		{
			res = (char*)m_phead;
			*((MemoryHead*)res) = m_info;
			((MemoryHead*)res)->MemInfo |= 0x80000000;
			res = res + sizeof(MemoryHead);
			m_phead = m_phead->m_pnext;
			--m_freecount;
		}
		return (void*)res;
	}
	
	void PoolAllocator::PushMemory(void* ptr)
	{

		if (!ptr)
		{
			return;
		}
		sMemoryCell* pCell = (sMemoryCell*)( (char*)ptr - sizeof(MemoryHead) );
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

	}

	PoolAllocatorLock::PoolAllocatorLock()
	{

	}

	PoolAllocatorLock::~PoolAllocatorLock()
	{

	}

	PoolAllocatorLock::PoolAllocatorLock(int32 size): PoolAllocator(size)
	{

	}

	void* PoolAllocatorLock::PopMemory()
	{
		
		MutexGuard guard(m_Mutex);
		char* res = NULL;
		if (NULL == m_phead)
		{
			res = (char*)::malloc(m_cellsize);
			if (!res)
			{
				return NULL;
			}
			*((MemoryHead*)res) = m_info;
			((MemoryHead*)res)->MemInfo |= 0x80000000;
			res = res + sizeof(MemoryHead);
			m_memusage += m_cellsize;
			++m_count;
		}
		else
		{
			res = (char*)m_phead;
			*((MemoryHead*)res) = m_info;
			((MemoryHead*)res)->MemInfo |= 0x80000000;
			res = res + sizeof(MemoryHead);
			m_phead = m_phead->m_pnext;
			--m_freecount;
		}
		return (void*)res;

	}
	void PoolAllocatorLock::PushMemory(void* ptr)
	{
		
		if (!ptr)
		{
			return;
		}
		MutexGuard guard(m_Mutex);
		sMemoryCell* pCell = (sMemoryCell*)( (char*)ptr - sizeof(MemoryHead) );
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
	}
	void PoolAllocatorLock::CollectMemory()
	{
		MutexGuard guard(m_Mutex);
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
	}
	int64 PoolAllocatorLock::GetMemroyUsage()
	{
		MutexGuard guard(m_Mutex);
		return m_memusage;
	}
	bool PoolAllocatorLock::IsValidMemory(void* ptr)
	{
		if (!ptr)
		{
			return false;
		}
		MutexGuard guard(m_Mutex);
		
		sMemoryCell* pCell = (sMemoryCell*)( (char*)ptr - sizeof(MemoryHead) );
		return ((pCell->m_info.MemInfo & 0x80000000) && 
			(pCell->m_info.AllocInfo == m_info.AllocInfo) && 
			((pCell->m_info.MemInfo << 2) == (pCell->m_info.MemInfo << 2)));
	}

	int32 PoolAllocatorLock::GetAllocInfo(void* ptr)
	{
		if (!ptr)
		{
			return -1;
		}
		MutexGuard guard(m_Mutex);
		sMemoryCell* realptr = (sMemoryCell*)( (char*)ptr - sizeof(MemoryHead) );
		return realptr->m_info.AllocInfo;
	}
}
