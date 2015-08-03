/********************************************************************
	created:	2015/08/03
	created:	10:56
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TEMPLATE_FUCTION_H__
#define __TEMPLATE_FUCTION_H__

#include "TFunctor.h"

namespace Template
{
	template<class R = void()>
	struct Function;

	template<class R>
	struct Function<R()> : public Functor<R>
	{
		typedef Functor<R> FBase;

		Function() : FBase() {}

		Function(const Function& func) : FBase()
		{
			if( !func.empty())
				FBase::operator=(func);
		}

		// test on emptiness
		template<class R2>
		Function(Function<R2()> func) : FBase()
		{
			if(!func.empty())
				FBase::operator=(func);
		}

		// clear  by '= 0'
		Function(const int i) : FBase()
		{
			if(i==0)
				FBase::clear();
			else
				throw std::runtime_error("Function(const int i): i!=0");
		}

		template<class Func>
		Function(Func func) : FBase(func) {}

		template<class Host, class Func>
		Function(const Host& host, const Func& func) : FBase(host,func) {}

	};

#define TEMPLATE_FUNCTION_BODY	\
	Function() : FBase() {}                     \
	\
	Function(const Function& func) : FBase()    \
	{                                           \
	if( !func.empty())                      \
	FBase::operator=(func);             \
	}                                           \
	\
	Function(const int i) : FBase()             \
	{                                           \
	if(i==0)                                \
	FBase::clear();                     \
			else                                    \
			throw std::runtime_error(           \
			"Function(const int i): i!=0");   \
	}                                           \
	\
	template<class Func>                        \
	Function(Func func) : FBase(func) {}        \
	\
	template<class Host, class Func>            \
	Function(const Host& host, const Func& func): FBase(host,func) {}

#define  TEMPLATE_FUNCTION_R2_CTOR_BODY	\
	: FBase()	\
	{	\
		if (!func.empty())	\
			FBase::operator=(func);	\
	}
	
	template<>
	struct Function<>: public Functor<>
	{
		typedef Functor<> FBase;
		template<typename R2>
		Function(Function<R2()> func)
			TEMPLATE_FUNCTION_R2_CTOR_BODY
		TEMPLATE_FUNCTION_BODY
	};

	template<typename R, typename P0>
	struct Function<R(P0)>: public Functor<R, TypeListType<P0> >
	{
		typedef Functor<R, TypeListType<P0> > FBase;
		template<typename R2, typename Q0>
		Function(Function<R2(Q0)> func)
			TEMPLATE_FUNCTION_R2_CTOR_BODY
		TEMPLATE_FUNCTION_BODY
	};

	template<typename R, typename P0, typename P1>
	struct Function<R(P0, P1)>: public Functor<R, TypeListType<P0, P1> >
	{
		typedef Functor<R, TypeListType<P0, P1> > FBase;
		template<typename R2, typename Q0, typename Q1>
		Function(Function<R2(Q0, Q1)> func)
			TEMPLATE_FUNCTION_R2_CTOR_BODY
		TEMPLATE_FUNCTION_BODY
	};

	template<typename R, typename P0, typename P1, typename P2>
	struct Function<R(P0, P1, P2)>: public Functor<R, TypeListType<P0, P1, P2> >
	{
		typedef Functor<R, TypeListType<P0, P1, P2> > FBase;
		template<typename R2, typename Q0, typename Q1, typename Q2>
		Function(Function<R2(Q0, Q1, Q2)> func)
			TEMPLATE_FUNCTION_R2_CTOR_BODY
			TEMPLATE_FUNCTION_BODY
	};

	template<typename R, typename P0, typename P1, typename P2, typename P3>
	struct Function<R(P0, P1, P2, P3)>: public Functor<R, TypeListType<P0, P1, P2, P3> >
	{
		typedef Functor<R, TypeListType<P0, P1, P2, P3> > FBase;
		template<typename R2, typename Q0, typename Q1, typename Q2, typename Q3>
		Function(Function<R2(Q0, Q1, Q2, Q3)> func)
			TEMPLATE_FUNCTION_R2_CTOR_BODY
		TEMPLATE_FUNCTION_BODY
	};

	template<typename R, typename P0, typename P1, typename P2, typename P3, typename P4>
	struct Function<R(P0, P1, P2, P3, P4)>: public Functor<R, TypeListType<P0, P1, P2, P3, P4> >
	{
		typedef Functor<R, TypeListType<P0, P1, P2, P3, P4> > FBase;
		template<typename R2, typename Q0, typename Q1, typename Q2, typename Q3, typename Q4>
		Function(Function<R2(Q0, Q1, Q2, Q3, Q4)> func)
			TEMPLATE_FUNCTION_R2_CTOR_BODY
		TEMPLATE_FUNCTION_BODY
	};
}

#endif