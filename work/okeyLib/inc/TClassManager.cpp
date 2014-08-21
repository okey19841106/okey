#include "PreCom.h"
#include "TClassManager.h"
#include "TClass.h"


namespace okey
{
	TClassManager& GetTClassManager()
	{
		static TClassManager ins;
		return ins;
	}

	TClassManager::TClassManager()
	{

	}

	TClassManager::~TClassManager()
	{

	}


	void TClassManager::AddClass(TClass* pClass)
	{
		std::map<std::string,TClass*>::iterator itr = m_classList.find(pClass->GetName());
		if (itr != m_classList.end())
		{
			m_classList[pClass->GetName()] = pClass;
		}
	}

	TClass* TClassManager::GetClass(const std::string& name)
	{
		std::map<std::string, TClass*>::iterator itr = m_classList.find(name);
		if (itr != m_classList.end())
		{
			return itr->second;
		}
		return NULL;
	}

	uint32 TClassManager::GetClassCount() const
	{
		return (uint32)m_classList.size();
	}
}