#include "PreCom.h"
#include "AnyTypeBase.h"


namespace okey
{

	CTypeBase::CTypeBase()
	{
		m_pPtr = NULL;
		m_size = 0;
		m_offset = 0;
		m_flag = 0;
	}
	CTypeBase::~CTypeBase()
	{

	}

	char* CTypeBase::Read(void* pClassObj,char* pBuffer)
	{
		if (!m_pPtr || !pBuffer)
		{
			return NULL;
		}
		memcpy(m_pPtr, pBuffer, m_size);
		return pBuffer + m_size;
	}

	char* CTypeBase::Write(void* pClassObj, char* pBuffer)
	{
		if (!m_pPtr || !pBuffer)
		{
			return NULL;
		}
		memcpy(pBuffer, m_pPtr, m_size);
		return pBuffer + m_size;
	}

	CClass::CClass()
	{
		m_classID = 0;
		m_classSize = 0;
		m_classSerSize = 0;
		m_parent = NULL;
	}
	CClass::~CClass()
	{

	}

	void CClass::AddMember(CTypeBase* member)
	{
		if (!member)
		{
			return;
		}
		MemberMap::iterator itr = m_members.find(member->GetName());
		if (itr != m_members.end())
		{
			return;
		}
		m_members[member->GetName()] = member;
		m_classSize += member->GetSize();
		if (member->CheckFlag(1))
		{
			m_classSerSize += member->GetSize();
		}
	}

	//void CClass::AddMethod(CMethodBase* method)
	//{
	//	if (!method)
	//	{
	//		return;
	//	}
	//	m_methods[method->GetName()] = method;
	//}

	CTypeBase* CClass::GetMember(int32 index)
	{
		MemberMap::iterator itr = m_members.begin();
		if (itr == m_members.end())
		{
			return NULL;
		}
		std::advance(itr, index);
		return itr->second;
	}

	//CMethodBase* CClass::GetMethod(int index)
	//{
	//	MethodMap::iterator itr = m_methods.begin();
	//	if (itr == m_methods.end())
	//	{
	//		return NULL;
	//	}
	//	std::advance(itr, index);
	//	return itr->second;
	//}
	CTypeBase* CClass::GetMember(const char* name)
	{
		MemberMap::iterator itr = m_members.find(name);
		if (itr == m_members.end())
		{
			return NULL;
		}
		return itr->second;
	}

	//CMethodBase* CClass::GetMethod(const char* name)
	//{
	//	MethodMap::iterator itr = m_methods.find(name);
	//	if (itr == m_methods.end())
	//	{
	//		return NULL;
	//	}
	//	return itr->second;
	//}

	char* CClass::Read(void* pClassObj,char* pBuffer,int32 flag)
	{
		if (!pClassObj || !pBuffer)
		{
			return NULL;
		}
		MemberMap::iterator itr = m_members.begin();
		for(;itr != m_members.end(); ++itr)
		{
			//if (itr->second->CheckFlag(1))
			{
				m_classSerSize += itr->second->GetSize();
				pBuffer = itr->second->Read(pClassObj, pBuffer);
			}
			m_classSize += itr->second->GetSize();
		}
		return pBuffer;
	}

	char* CClass::Write(void* pClassObj,char* pBuffer,int32 flag)
	{
		if (!pClassObj || !pBuffer)
		{
			return NULL;
		}
		MemberMap::iterator itr = m_members.begin();
		for(;itr != m_members.end(); ++itr)
		{
			//if (itr->second->CheckFlag(1))
			{
				//m_classSerSize += m_size;
				pBuffer = itr->second->Write(pClassObj, pBuffer);
			}
			//m_classSize += m_size;
		}
		return pBuffer;
	}

	bool CClass::IsChild(uint32 classID)
	{
		CClass *pClass = m_parent;
		while (pClass)
		{
			if (pClass->GetClassID() == classID)
			{
				return true;
			}
			pClass = pClass->GetParent();
		}
		return false;
		
	}

	bool CClass::IsChild(const char* name)
	{
		CClass *pClass = m_parent;
		while (pClass)
		{
			if (strcmp(pClass->GetClassName() ,name) == 0)
			{
				return true;
			}
			pClass = pClass->GetParent();
		}
		return false;
	}

	bool CClass::IsChild(CClass* pClass)
	{
		CClass *ppClass = m_parent;
		while (pClass)
		{
			if (pClass->GetClassID() == ppClass->GetClassID())
			{
				return true;
			}
			pClass = pClass->GetParent();
		}
		return false;
	}




}




