/********************************************************************
	created:	2014/08/21
	created:	15:07
	author:		
	
	purpose:	
*********************************************************************/

#ifndef __POOL__ALLOCATOR_H__
#define __POOL__ALLOCATOR_H__

#include "Types.h"
#include "Allocator.h"
#include "Thread/Mutex.h"

namespace okey
{
	struct sMemoryCell 
	{
		sMemoryCell* m_pnext;
		MemoryHead m_info;
		sMemoryCell()
		{
			m_pnext = NULL;
		}
	};


	class PoolAllocator: public Allocator
	{
	public:
		PoolAllocator();
		PoolAllocator(int32 size);
		~PoolAllocator();
		virtual void* Malloc(int32 size);
		virtual void Free(void* ptr);
		virtual void SetMemoryInfo(const MemoryHead& info);
		virtual bool Init(int32 size);
		virtual void CollectMemory();
		virtual bool IsValidMemory(void* ptr);
		virtual int32 GetAllocInfo(void* ptr);
		virtual int64 GetMemroyUsage();
		virtual int32 GetType(){return MEMORY_POOL;}
		virtual MemoryHead GetMemoryHead()
		{
			return m_info;
		}
	protected:
		virtual void* PopMemory();
		virtual void PushMemory(void* ptr);
	protected:
		uint32 m_freecount;
		uint32 m_count;
		uint64 m_memusage;
		int32 m_objsize;
		int32 m_cellsize;
		MemoryHead m_info;
		sMemoryCell* m_phead; //¿ÕÏÐÄÚ´æÍ·Ö¸Õë
	private:
	};

	class PoolAllocatorLock: public PoolAllocator
	{
	public:
		PoolAllocatorLock();
		~PoolAllocatorLock();
		PoolAllocatorLock(int32 size);
	
		virtual void CollectMemory();
		virtual int64 GetMemroyUsage();
		virtual bool IsValidMemory(void* ptr);
		virtual int32 GetAllocInfo(void* ptr);
	protected:
		virtual void* PopMemory();
		virtual void PushMemory(void* ptr);

	protected:
		Mutex m_Mutex;
	};


}







#endif