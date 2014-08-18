/********************************************************************
	created:	2014/08/18
	created:	11:04
	author:		
	
	purpose:	
*********************************************************************/
#ifndef __CLASS_METHOD_FUNCTOR_H__
#define __CLASS_METHOD_FUNCTOR_H__


#include "ClassMethod.h"


namespace okey
{
	template<typename Rt, typename Obj>
	class TClassMethod0: public TAnyTypeMethod
	{
		typedef Rt (Obj::*fun)();
	public:
		TClassMethod0(fun f):m_pf(f){}
		~TClassMethod0();

		void invoke(void* result, void* obj, void* parameters[])
		{
			*(Rt*)result = (((Obj*)obj)->*m_pf)();

		}
	protected:
		fun m_pf;
	};

	template<typename Obj>
	class TClassMethod0<void, Obj>: public TAnyTypeMethod
	{
		typedef void (Obj::*fun)();
	public:
		TClassMethod0(fun f):m_pf(f){}
		~TClassMethod0();

		void invoke(void* result, void* obj, void* parameters[])
		{
			(((Obj*)obj)->*m_pf)();

		}
	protected:
		fun m_pf;
	};

	template<typename Rt, typename Obj, typename P1>
	class TClassMethod1: public TAnyTypeMethod
	{
		typedef Rt (Obj::*fun)(P1);
	public:
		TClassMethod1(fun f):m_pf(f){}
		~TClassMethod1();

		void invoke(void* result, void* obj, void* parameters[])
		{
			*(Rt*)result = (((Obj*)obj)->*m_pf)(*(P1*)parameters[0]);
		}
	protected:
		fun m_pf;
	};

	template<typename Obj,typename P1>
	class TClassMethod1<void,Obj,P1>: public TAnyTypeMethod
	{
		typedef void (Obj::*fun)(P1);
	public:
		TClassMethod1(fun f):m_pf(f){}
		~TClassMethod1();

		void invoke(void* result, void* obj, void* parameters[])
		{
			(((Obj*)obj)->*m_pf)(*(P1*)parameters[0]);

		}
	protected:
		fun m_pf;
	};
}


#endif