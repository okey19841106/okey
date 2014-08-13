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
	
	class TClassMember
	{
	public:
		TClassMember();
		~TClassMember();


		template<typename Rt>
		void invoke(Rt* result, void* obj)
		{
			//assert( m_pFun->GetParamCount() == 0);
			m_pFun->invoke((void*)result, obj, NULL);
		}

		template<typename Rt, typename P1>
		void invoke(Rt* result, void* obj, P1 p1)
		{
			//assert( m_pFun->GetParamCount() == 1);
			void* params[1];
			params[0] = &p1;
			m_pFun->invoke((void*)result,obj,params);
		}

	protected:
		TAnyTypeMethod* m_pFun;
	};


}


#endif