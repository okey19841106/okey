#include "PreCom.h"
#include "FactoryManager.h"
#include "Factory.h"
#include <map>

namespace okey
{
	void FactoryManagerArg0Base::CollectMemory()
	{
		std::map<UtilID,CFactoryArg0_Base*>::iterator itr = m_Tmap.begin();
		for (;itr!=m_Tmap.end();++itr)
		{
			itr->second->CollectMemory();
		}
	}

	int64 FactoryManagerArg0Base::GetUsageMemory()
	{
		int64 usagememory = 0;
		std::map<UtilID,CFactoryArg0_Base*>::iterator itr = m_Tmap.begin();
		for (;itr!=m_Tmap.end();++itr)
		{
			usagememory += itr->second->GetUsageMemory();
		}
		return usagememory;
	}

	void* FactoryManagerArg0Base::CreateObj(const char* name)
	{
		CFactoryArg0_Base* ptr = GetObj(name);
		if (!ptr)
		{
			return NULL;
		}
		return (void*)ptr->CreateObject();
	}

	void FactoryManagerArg0Base::FreeObj(const char* name, void* ptr)
	{
		CFactoryArg0_Base* pfac = GetObj(name);
		if (!pfac)
		{
			return;
		}
		pfac->FreeObject(ptr);
	}
}