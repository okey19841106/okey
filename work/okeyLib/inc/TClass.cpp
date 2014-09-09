#include "PreCom.h"
#include "TClass.h"
#include "ClassMember.h"
#include "ClassMethod.h"
#include <algorithm>
#include "TClassManager.h"

namespace okey
{
	namespace myprivate
	{
		struct MethodComparer: public std::binary_function<TClassMethod*, std::string, bool>
		{
			bool operator()(TClassMethod* p,const std::string& name) const {return p->GetMethodName() == name;}
		};

		struct MemberComparer: public std::binary_function<TClassMember*, std::string, bool>
		{
			bool operator()(TClassMember* p,const std::string& name) const {return p->GetMemberName() == name;}
		};

		struct BaseClassComparer: public std::binary_function<TClass*, std::string, bool>
		{
			bool operator()(TClass* p,const std::string& name) const {return p->GetName() == name;}
		};
	}
	char* TClass::Read(void* pClassObj,char* pBuffer)
	{
		std::list<TClass*>::iterator itr = m_BaseClsList.begin();
		for (; itr!= m_BaseClsList.end(); ++itr)
		{
			pBuffer = (*itr)->Read(pClassObj,pBuffer);
		}
		std::list<TClassMember*>::iterator itr_m = m_MemList.begin();
		for (; itr_m != m_MemList.end(); ++itr_m)
		{
			pBuffer = (*itr_m)->Read(pClassObj,pBuffer);
		}
		return pBuffer;
	}

	char* TClass::Write(void* pClassObj, char* pBuffer)
	{
		std::list<TClass*>::iterator itr = m_BaseClsList.begin();
		for (; itr!= m_BaseClsList.end(); ++itr)
		{
			pBuffer = (*itr)->Write(pClassObj,pBuffer);
		}
		std::list<TClassMember*>::iterator itr_m = m_MemList.begin();
		for (; itr_m != m_MemList.end(); ++itr_m)
		{
			pBuffer = (*itr_m)->Write(pClassObj,pBuffer);
		}
		return pBuffer;
	}

	void TClass::AddMethod(TClassMethod* pMethod)
	{

		m_MtdList.push_back(pMethod);
	}

	void TClass::AddMember(TClassMember* pField)
	{
		m_MemList.push_back(pField);
	}

	void TClass::AddBaseClass(TClass* pClass)
	{
		m_BaseClsList.push_back(pClass);
	}


	TClass* TClass::GetBaseClass(const std::string& name)
	{
		std::list<TClass*>::iterator itr_n = std::find_if(m_BaseClsList.begin(), m_BaseClsList.end(), std::bind2nd(myprivate::BaseClassComparer(),name));
		if (itr_n != m_BaseClsList.end())
		{
			return  *itr_n;
		}
		else
		{
			std::list<TClass*>::iterator itr_b = m_BaseClsList.begin();
			for (; itr_b!=m_BaseClsList.end();++itr_b)
			{
				TClass* pClass = (*itr_b)->GetBaseClass(name);
				if (pClass)
				{
					return pClass;
				}
			}
		}
		return NULL;
	}

	TClassMember* TClass::GetClassMember(const std::string& name)
	{
		std::list<TClassMember*>::iterator itr_n = std::find_if(m_MemList.begin(), m_MemList.end(), std::bind2nd(myprivate::MemberComparer(),name));
		if (itr_n != m_MemList.end())
		{
			return  *itr_n;
		}
		else
		{
			std::list<TClass*>::iterator itr_b = m_BaseClsList.begin();
			for (; itr_b!=m_BaseClsList.end();++itr_b)
			{
				TClassMember* pMember = (*itr_b)->GetClassMember(name);
				if (pMember)
				{
					return pMember;
				}
			}
		}
		return NULL;
	}

	TClassMethod* TClass::GetClassMethod(const std::string& name)
	{
		std::list<TClassMethod*>::iterator itr_n = std::find_if(m_MtdList.begin(), m_MtdList.end(), std::bind2nd(myprivate::MethodComparer(),name));
		if (itr_n != m_MtdList.end())
		{
			return  *itr_n;
		}
		else
		{
			std::list<TClass*>::iterator itr_b = m_BaseClsList.begin();
			for (; itr_b!=m_BaseClsList.end();++itr_b)
			{
				TClassMethod* pMethod = (*itr_b)->GetClassMethod(name);
				if (pMethod)
				{
					return pMethod;
				}
			}
		}
		return NULL;
	}

	TClass::TClass()
	{
		m_typeinfo = TYPE_STRUCT;
	}

	TClass::~TClass()
	{

	}

	uint32 TClass::GetClassCount()
	{
		return GetTClassManager().GetClassCount();
	}

	void TClass::AddClass(TClass* pClass)
	{
		GetTClassManager().AddClass(pClass);
	}

	TClass* TClass::GetClass(const std::string& name)
	{
		return GetTClassManager().GetClass(name);
	}

	
}