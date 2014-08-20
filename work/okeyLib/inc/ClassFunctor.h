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
		TClassMethod0(fun f):m_pf(f)
		{
			m_paramCount = 0;
		}
		~TClassMethod0();

		void invoke(void* result, void* obj, void* parameters[])
		{
			*(Rt*)result = (((Obj*)obj)->*m_pf)();
		}

		Rt operator()(Obj* obj)
		{
			return (obj->*m_pf)();
		}
	protected:
		fun m_pf;
	};

	template<typename Obj>
	class TClassMethod0<void, Obj>: public TAnyTypeMethod
	{
		typedef void (Obj::*fun)();
	public:
		TClassMethod0(fun f):m_pf(f)
		{
			m_paramCount = 0;
		}
		~TClassMethod0();

		void invoke(void* result, void* obj, void* parameters[])
		{
			(((Obj*)obj)->*m_pf)();

		}

		void operator()(Obj* obj)
		{
			(obj->*m_pf)();
		}
	protected:
		fun m_pf;
	};

	template<typename Rt, typename Obj, typename P1>
	class TClassMethod1: public TAnyTypeMethod
	{
		typedef Rt (Obj::*fun)(P1);
	public:
		TClassMethod1(fun f):m_pf(f){
			m_paramCount = 1;
		}
		~TClassMethod1();

		void invoke(void* result, void* obj, void* parameters[])
		{
			*(Rt*)result = (((Obj*)obj)->*m_pf)(*(P1*)parameters[0]);
		}

		Rt operator()(Obj* obj,P1 param1)
		{
			return (obj->*m_pf)(param1);
		}
	protected:
		fun m_pf;
	};

	template<typename Obj,typename P1>
	class TClassMethod1<void,Obj,P1>: public TAnyTypeMethod
	{
		typedef void (Obj::*fun)(P1);
	public:
		TClassMethod1(fun f):m_pf(f){
			m_paramCount = 1;
		}
		~TClassMethod1();

		void invoke(void* result, void* obj, void* parameters[])
		{
			(((Obj*)obj)->*m_pf)(*(P1*)parameters[0]);

		}

		void operator()(Obj* obj,P1 param1)
		{
			(obj->*m_pf)(param1);
		}
	protected:
		fun m_pf;
	};

	template<typename Rt, typename Obj, typename P1, typename P2>
	class TClassMethod2: public TAnyTypeMethod
	{
		typedef Rt (Obj::*fun)(P1, P2);
	public:
		TClassMethod2(fun f):m_pf(f){
			m_paramCount = 2;
		}
		~TClassMethod2();

		void invoke(void* result, void* obj, void* parameters[])
		{
			*(Rt*)result = (((Obj*)obj)->*m_pf)(*(P1*)parameters[0], *(P2*)parameters[1]);
		}

		Rt operator()(Obj* obj,P1 param1, P2 param2)
		{
			return (obj->*m_pf)(param1, param2);
		}
	protected:
		fun m_pf;
	};

	template<typename Obj,typename P1, typename P2>
	class TClassMethod2<void,Obj,P1,P2>: public TAnyTypeMethod
	{
		typedef void (Obj::*fun)(P1, P2);
	public:
		TClassMethod2(fun f):m_pf(f){
			m_paramCount = 2;
		}
		~TClassMethod2();

		void invoke(void* result, void* obj, void* parameters[])
		{
			(((Obj*)obj)->*m_pf)(*(P1*)parameters[0], *(P2*)parameters[1]);

		}

		void operator()(Obj* obj,P1 param1, P2 param2)
		{
			(obj->*m_pf)(param1, param2);
		}
	protected:
		fun m_pf;
	};


	template<typename Rt, typename Obj, typename P1, typename P2, typename P3>
	class TClassMethod3: public TAnyTypeMethod
	{
		typedef Rt (Obj::*fun)(P1, P2,P3);
	public:
		TClassMethod3(fun f):m_pf(f){
			m_paramCount = 3;
		}
		~TClassMethod3();

		void invoke(void* result, void* obj, void* parameters[])
		{
			*(Rt*)result = (((Obj*)obj)->*m_pf)(*(P1*)parameters[0], *(P2*)parameters[1], *(P3*)parameters[2]);
		}

		Rt operator()(Obj* obj,P1 param1, P2 param2,P3 param3)
		{
			return (obj->*m_pf)(param1, param2, param3);
		}
	protected:
		fun m_pf;
	};

	template<typename Obj,typename P1, typename P2, typename P3>
	class TClassMethod3<void,Obj,P1,P2,P3>: public TAnyTypeMethod
	{
		typedef void (Obj::*fun)(P1, P2,P3);
	public:
		TClassMethod3(fun f):m_pf(f){}
		~TClassMethod3();

		void invoke(void* result, void* obj, void* parameters[])
		{
			(((Obj*)obj)->*m_pf)(*(P1*)parameters[0], *(P2*)parameters[1], *(P3*)parameters[2]);

		}

		void operator()(Obj* obj,P1 param1, P2 param2, P3 param3)
		{
			(obj->*m_pf)(param1, param2, param3);
		}
	protected:
		fun m_pf;
	};









	template<typename RT, typename Obj>
	inline TAnyTypeMethod* MethodTypeOf( RT (Obj::*Method) () ) {
		return new TClassMethod0<RT, Obj>(Method);
	}

	template<typename RT, typename Obj, typename P1>
	inline TAnyTypeMethod* MethodTypeOf( RT (Obj::*Method) (P1) ) {
		return new TClassMethod1< RT,  Obj, P1>(Method);
	}

	template<typename RT, typename Obj, typename P1, typename P2>
	inline TAnyTypeMethod* MethodTypeOf( RT (Obj::*Method) (P1,P2) ) {
		return new TClassMethod2< RT,  Obj, P1, P2>(Method);
	}

	template<typename RT, typename Obj, typename P1, typename P2, typename P3>
	inline TAnyTypeMethod* MethodTypeOf( RT (Obj::*Method) (P1,P2,P3) ) {
		return new TClassMethod3< RT, Obj, P1, P2,P3>(Method);
	}
}


#endif