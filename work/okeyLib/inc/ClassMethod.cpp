#include "PreCom.h"
#include "ClassMethod.h"
#include "TClass.h"

namespace okey
{

	TClassMethod::TClassMethod(TClass* pClass,TAnyTypeMethod* pFun):m_OwnerClass(pClass),m_pFun(pFun)
	{

	}


	TClassMethod::~TClassMethod()
	{

	}


	TClass* TClassMethod::GetOwnerClass()
	{
		return m_OwnerClass;
	}
}