/********************************************************************
	created:	2014/08/21
	created:	15:06
	author:		
	
	purpose:	
*********************************************************************/

#ifndef __DL_ALLOCATOR_H__
#define __DL_ALLOCATOR_H__

#include "Types.h"
#include "Allocator.h"

namespace okey
{
	class DLAllocator: public Allocator
	{
	public:
		DLAllocator(){}
		~DLAllocator(){}
		virtual void* Malloc(int32 size);
		virtual void Free(void* ptr);
		virtual void SetMemoryInfo(const MemoryHead& info);
		virtual bool Init(int32 size);
		virtual void CollectMemory();
		virtual bool IsValidMemory(void* ptr);
		virtual int32 GetAllocInfo(void* ptr);
		virtual int64 GetMemroyUsage();
		virtual int32 GetType(){return MEMORY_DL;}
		virtual MemoryHead GetMemoryHead()
		{
			return m_Info;
		}
	protected:
		int32 m_size;
		MemoryHead m_Info;
	private:
	};
}


#endif