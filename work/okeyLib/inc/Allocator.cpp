#include "PreCom.h"
#include "Allocator.h"

#ifdef WINDOWS
#pragma warning(disable: 4800)
#endif

namespace okey
{
	namespace MemoryCheck
	{
		bool IsValidMemory(void* ptr)
		{
			if (!ptr)
			{
				return false;
			}
			MemoryHead* pHead =  (MemoryHead*)((char*)ptr - sizeof(MemoryHead));
			return (pHead->MemInfo & 0x80000000);
		}
		int32 GetAllocInfo(void* ptr)
		{
			if (!ptr)
			{
				return false;
			}
			MemoryHead* pHead =  (MemoryHead*)((char*)ptr - sizeof(MemoryHead));
			return pHead->AllocInfo;
		}

		int32 GetMemSize(void* ptr)
		{
			if (!ptr)
			{
				return false;
			}
			MemoryHead* pHead =  (MemoryHead*)((char*)ptr - sizeof(MemoryHead));
			return (pHead->MemInfo<<2);
		}
	}
}