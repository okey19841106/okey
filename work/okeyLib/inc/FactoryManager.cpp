#include "PreCom.h"
#include "FactoryManager.h"
#include "Factory.h"
#include "UtilID.h"


namespace okey
{
	hash_map<uint32, std::string> FactoryManager_Arg0::m_UtilList;

	FactoryManager_Arg0& GetTClassManager()
	{
		static FactoryManager_Arg0 ist;
		return ist;
	}

	void FactoryManager_Arg0::CollectMemory()
	{
		hash_map<uint32,CFactoryArg0_Base*>::iterator itr = m_FactoryList.begin();
		for (;itr != m_FactoryList.end();++itr)
		{
			itr->second->CollectMemory();
		}
	}

	int64 FactoryManager_Arg0::GetUsageMemory()
	{
		int64 usagememory = 0;
		hash_map<uint32,CFactoryArg0_Base*>::iterator itr = m_FactoryList.begin();
		for (;itr!=m_FactoryList.end();++itr)
		{
			usagememory += itr->second->GetUsageMemory();
		}
		return usagememory;
	}

	void* FactoryManager_Arg0::CreateObj(const char* name)
	{
		hash_map<uint32,CFactoryArg0_Base*>::iterator itr = m_FactoryList.find(UtilID::StringToUtilID(name,strlen(name)));
		if (itr == m_FactoryList.end())
		{
			//assert();
			return NULL;
		}
		return (void*)itr->second->CreateObject();
	}

	void FactoryManager_Arg0::FreeObj(void* ptr)
	{
		//assert(ptr)
		uint32 info = ((MemoryHead*)((char*)ptr-sizeof(MemoryHead)))->AllocInfo;
		CFactoryArg0_Base* pfac = m_FactoryList[info];
		if (!pfac)
		{
			//assert(false);
			return;
		}
		pfac->FreeObject(ptr);
	}

	void* FactoryManager_Arg0::CreateObj(uint32 classID)
	{
		hash_map<uint32,CFactoryArg0_Base*>::iterator itr = m_FactoryList.find(classID);
		if (itr == m_FactoryList.end())
		{
			//assert();
			return NULL;
		}
		return (void*)itr->second->CreateObject();
	}

	void FactoryManager_Arg0::AddFactory(CFactoryArg0_Base* pFun)
	{
		//assert(pFun);
		uint32 uid = UtilID::StringToUtilID(pFun->GetObjName(),strlen(pFun->GetObjName()));
		if(m_UtilList.find(uid) != m_UtilList.end())
		{
			//assert(false);
		}
		m_FactoryList[uid] = pFun;
		m_UtilList[uid] = pFun->GetObjName();
	}
}