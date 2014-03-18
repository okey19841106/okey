#include "PreCom.h"
#include "DLAllocator.h"
#include "DLMalloc.h"

namespace okey
{
	void* DLAllocator::DLMalloc(int32 size)
	{
		int32 realsize = sizeof(m_Info) + size;
		void* presult = dlmalloc(realsize);
		if (!presult)
		{
			return NULL;
		}
		*((MemoryHead*)presult) = m_Info;
		((MemoryHead*)presult)->MemInfo = realsize;
		((MemoryHead*)presult)->MemInfo |= 0x80000000;
		return (char*)presult + sizeof(m_Info);

	}
	void DLAllocator::DLFree(void* ptr)
	{
		if (!ptr)
		{
			return;
		}
		char* realptr = (char*)ptr - sizeof(m_Info);
		MemoryHead* pHead =(MemoryHead*)realptr;
		pHead->MemInfo &= 0x7fffffff;
		dlfree((void*)realptr);
	}
	void DLAllocator::SetMemoryInfo(const MemoryHead& info)
	{
		m_Info.AllocInfo = info.AllocInfo;
		m_Info.MemInfo = m_size;
	}
	bool DLAllocator::Init(int32 size)
	{
		m_size = size + sizeof(MemoryHead);
		m_Info.MemInfo = m_size;
		return true;
	}
	void DLAllocator::CollectMemory()
	{
		dlmalloc_trim(0);
	}
	bool DLAllocator::IsValidMemory(void* ptr)
	{
		if (!ptr)
		{
			return false;
		}
		MemoryHead* pHead =  (MemoryHead*)((char*)ptr - sizeof(m_Info));
		return ((pHead->MemInfo & 0x80000000) && 
			(pHead->AllocInfo == m_Info.AllocInfo) && 
			((pHead->MemInfo << 2) == (m_Info.MemInfo << 2)));

	}
	int32 DLAllocator::GetAllocInfo(void* ptr)
	{
		if (!ptr)
		{
			return -1;
		}
		MemoryHead* pHead =  (MemoryHead*)((char*)ptr - sizeof(m_Info));
		return pHead->AllocInfo;
	}
	int64 DLAllocator::GetMemroyUsage()
	{
		return (int64)dlmalloc_footprint();
	}
}