#include "PreCom.h"
#include "ClassMember.h"
#include "AnyTypeBase.h"
#include "TClass.h"

namespace okey
{
	TClassMember::TClassMember(TClass* pClass, TTypeBase* pType):m_OwnerClass(pClass),m_pType(pType)
	{
		
	}

	TClassMember::~TClassMember()
	{

	}

	TClass* TClassMember::GetOwnerClass()
	{
		return m_OwnerClass;
	}

	char* TClassMember::Read(void* pClassObj, char* pBuff)
	{
		return m_pType->Read(((char*)pClassObj) + m_offset,pBuff);
	}

	char* TClassMember::Write(void* pClassObj, char* pBuff)
	{
		return m_pType->Write(((char*)pClassObj) + m_offset,pBuff);
	}

	std::string TClassMember::GetMemberName(){return m_pType->GetName();}
}