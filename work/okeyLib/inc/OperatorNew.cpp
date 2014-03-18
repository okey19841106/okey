#include "PreCom.h"
#include "OperatorNew.h"
#include <cassert>

namespace okey
{
	std::new_handler SetNewHandler(std::new_handler pfnHandler)
	{
		return std::set_new_handler(pfnHandler);
	}
	std::new_handler GetNewHandler()
	{
		std::new_handler pfnHandler = std::set_new_handler(0);
		std::set_new_handler(pfnHandler);
		return pfnHandler;
	}
	void SetGlobleAllocator(Allocator* pAlloc)
	{
		g_Allocator = pAlloc;
	}
	Allocator* GetGloableAllocator()
	{
		return g_Allocator;
	}
}

void* operator new(size_t nBytes)
{
	for (;;)
	{
		try
		{
#if USE_SYSTEM_NEW
			return ::malloc(nBytes);
#else
			if (!okey::g_Allocator)
			{
				printf("there is no g_Allocator, now start it.....\n");
				okey::g_Allocator = (okey::Allocator*)::malloc(sizeof(okey::DLAllocator));
				if (okey::g_Allocator)
				{
					new(okey::g_Allocator)okey::DLAllocator();
					okey::MemoryHead mh;
					mh.AllocInfo = 1;
					okey::g_Allocator->SetMemoryInfo(mh);
				}
				else
					throw;
			}
			return okey::g_Allocator->DLMalloc(nBytes);
#endif
		}
		catch(std::bad_alloc&)
		{
			std::new_handler pfnHandler = okey::GetNewHandler();
			if (!pfnHandler)
			{
				throw;
			}
			(*pfnHandler)();
		}
	}

}
void operator delete(void* ptr)
{
#if USE_SYSTEM_NEW
	::free(ptr);
#else
	if (!okey::g_Allocator)
	{
		printf("no Globle Allocator, how did you get it\t");
		return;
	}
	okey::g_Allocator->DLFree(ptr);
#endif
}
void* operator new[](size_t nBytes)
{
	return operator new(nBytes);
}
void operator delete[](void* ptr)
{
	operator delete(ptr);
}


void* operator new(size_t nBytes, const std::nothrow_t&)
{
	assert(false);
	return NULL;
}
void operator delete(void* ptr ,const std::nothrow_t&)
{
	assert(false);
	//return NULL;
}
void* operator new[](size_t nBytes,const std::nothrow_t&)throw()
{
	assert(false);
	return NULL;
}
void operator delete[](void* ptr,const std::nothrow_t&)throw()
{
	assert(false);
	//return NULL;
}