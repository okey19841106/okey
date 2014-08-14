#include "PreCom.h"
#include "ClassMethod.h"
#include "TClass.h"

namespace okey
{

	TClassMethod::TClassMethod()
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