/********************************************************************
	created:	2014/08/12
	created:	16:32
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef _OKEY_CLASS_METHOD_H_
#define _OKEY_CLASS_METHOD_H_

#include "AnyTypeBase.h"

namespace okey
{
	class TClass;
	class TClassMethod
	{
	public:
		TClassMethod(TClass* pClass,TAnyTypeMethod* pFun);
		~TClassMethod();

		void invoke(void* result, void* obj, void* params[])
		{
			m_pFun->invoke(result,obj,params);
		}
		TClass* GetOwnerClass();

		std::string GetMethodName(){return m_pFun->GetName();}
	protected:
		TAnyTypeMethod* m_pFun;
		TClass* m_OwnerClass;
	};

}


#endif