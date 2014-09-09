/********************************************************************
	created:	2014/09/09
	created:	17:28
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_OPERATOR_NEW_H__
#define __OKEY_OPERATOR_NEW_H__

#include "Types.h"
#include <new>
#include "DLAllocator.h"


namespace okey
{
	static Allocator* g_Allocator = NULL;
	std::new_handler SetNewHandler(std::new_handler pfnHandler)throw();
	std::new_handler GetNewHandler();
	void SetGlobleAllocator(Allocator* pAlloc);
	Allocator* GetGloableAllocator();
}

/////////////////////////////////////////////////////////////////////////////
//operator new and delete
/////////////////////////////////////////////////////////////////////////////


void* operator new(size_t nBytes);
void operator delete(void* ptr);
void* operator new[](size_t nBytes);
void operator delete[](void* ptr);


void* operator new(size_t nBytes, const std::nothrow_t&)throw();
void operator delete(void* ptr ,const std::nothrow_t&)throw();
void* operator new[](size_t nBytes,const std::nothrow_t&)throw();
void operator delete[](void* ptr,const std::nothrow_t&)throw();

#endif