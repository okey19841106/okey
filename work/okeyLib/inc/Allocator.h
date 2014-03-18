/********************************************************************
	created:	2014/03/05
	author:		okey
	
	purpose:	
*********************************************************************/


#ifndef __I_ALLOCAL_H___
#define __I_ALLOCAL_H___

#include "Types.h"

namespace okey
{
	enum MemoryType
	{
		MEMORY_BASE = 0,
		MEMORY_DL,
		MEMORY_POOL,
	};

	struct MemoryHead 
	{
		int32 MemInfo;
		int32 AllocInfo;
		bool operator == (MemoryHead& mh)
		{
			return ((MemInfo == mh.MemInfo) && (AllocInfo == mh.AllocInfo));
		}
		bool operator != (MemoryHead& mh)
		{
			return ((MemInfo!=mh.MemInfo) || (AllocInfo != mh.AllocInfo));
		}
		MemoryHead& operator = (MemoryHead& mh)
		{
			MemInfo = mh.MemInfo;
			AllocInfo = mh.AllocInfo;
			return *this;
		}
		MemoryHead()
		{
			MemInfo = 0;
			AllocInfo = 0;
		}
	};

	namespace MemoryCheck
	{
		bool IsValidMemory(void* ptr);
		int32 GetAllocInfo(void* ptr);
		int32 GetMemSize(void* ptr);
	}


	class Allocator
	{
	public:
		Allocator(){}
		~Allocator(){}
		virtual void* DLMalloc(int32 size) = 0;
		virtual void DLFree(void* ptr) = 0;
		virtual void SetMemoryInfo(const MemoryHead& info) = 0;
		virtual bool Init(int32 size){return false;}
		virtual void CollectMemory(){}
		virtual bool IsValidMemory(void* ptr) = 0;
		virtual int32 GetAllocInfo(void* ptr) = 0;
		virtual int64 GetMemroyUsage() = 0;
		virtual int32 GetType(){return MEMORY_BASE;}
		virtual MemoryHead GetMemoryHead() = 0;
	protected:
	private:
	};
}



#endif