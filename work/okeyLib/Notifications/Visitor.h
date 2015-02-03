/********************************************************************
	created:	2015/02/03
	created:	16:11
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_VISITOR_H__
#define __OKEY_VISITOR_H__

#include "Template/TTypeList.h"

namespace okey
{
	class BaseVisitor
	{
	public:
		virtual ~BaseVisitor(){}
	};

	template<typename T, typename R = void, bool ConstVisit = false>
	class Visitor;


	template<typename T, typename R>
	class Visitor<T, R, false>
	{
	public:
		typedef R ReturnType;
		typedef T ParamType;
		virtual ~Visitor(){}
		virtual ReturnType Visit(ParamType&) = 0;
	};

	template<typename T, typename R>
	class Visitor<T, R, true>
	{
	public:
		typedef R ReturnType;
		typedef const T ParamType;
		virtual ~Visitor(){}
		virtual ReturnType Visit(ParamType&) = 0;
	};

	template<typename Head, typename Tail, typename R>
	class Visitor<Template::TypeList<Head, Tail>, R, false >: public Visitor<Head, R, false>, public Visitor<Tail, R, false>
	{
	public:
		typedef R ReturnType;
	};

	template<typename Head, typename R>
	class Visitor<Template::TypeList<Head, Template::NullTypeList> , R, false>: public Visitor<Head, R, false>
	{
	public:
		typedef R ReturnType;
		using Visitor<Head, R, false>::Visit;
	};

	template<typename Head, typename Tail, typename R>
	class Visitor<Template::TypeList<Head, Tail>, R, true >: public Visitor<Head, R, true>, public Visitor<Tail, R, true>
	{
	public:
		typedef R ReturnType;
	};

	template<typename Head, typename R>
	class Visitor<Template::TypeList<Head, Template::NullTypeList> , R, true>: public Visitor<Head, R, true>
	{
	public:
		typedef R ReturnType;
		using Visitor<Head, R, false>::Visit;
	};

	template<typename TList, typename R = void>
	class BaseVisitorImpl;

	template<typename Head, class Tail, typename R>
	class BaseVisitorImpl<Template::TypeList<Head, Tail>, R>: public Visitor<Head, R>, public BaseVisitorImpl<Tail, R>
	{
	public:
		virtual R Visit(Head&){return R();}//用Typelist来观察一堆的东西。只需重载关注的就行了。
	};

	template<typename Head, typename R>
	class BaseVisitorImpl<Template::TypeList<Head, Template::NullTypeList> , R>: public Visitor<Head, R>
	{
	public:
		virtual R Visit(Head&){return R();}
	};

	template<typename R, typename Visited>
	struct DefaultCatchAll
	{
		static R OnUnknowVisitor(Visited&, BaseVisitor&){return R(); }
	};

	template<typename R = void, template<typename, typename>class CatchAll = DefaultCatchAll, bool ConstVisitable = false>
	class BaseVisitable;

	template<typename R, template<typename, typename>class CatchAll>
	class BaseVisitable//重载这个。去接受访问着。
	{
	public:
		typedef R ReturnType;
		virtual ~BaseVisitable(){}
		virtual ReturnType Accept(BaseVisitor&) = 0;
	protected:
		template<typename T>
		static ReturnType AcceptImpl(T& visited, BaseVisitor& guest)
		{
			if (Visitor<T, R>* p= dynamic_cast<Visitor<T, R>*>(guest))
			{
				return p->Visit(visited);
			}
			return CatchAll<R, T>::OnUnknowVisitor(const_cast<T&>(visited), guest);
		}
	};

	template<typename R, typename TList>
	class CyclicVisitor: public Visitor<TList, R>
	{
	public:
		typedef R ReturnType;
		template<typename Visited>
		ReturnType GenericVisit(Visited& host)
		{
			Visitor<Visited, ReturnType>& subObj = *this;
			return subObj.Visit(host);
		}
	};

#define DEFINE_VISITABLE()\
	virtual ReturnType Accept(BaseVisitor& guest)\
	{return AcceptImpl(*this, guest);}

#define DEFINE_CONST_VISITABLE()\
	virtual ReturnType Accept(BaseVisitor& guest)\
	{return AcceptImpl(*this, guest);}

#define DEFINE_CYCLIC_VISITABLE(SomeVisitor)\
	virtual SomeVisitor::ReturnType Accept(SomeVisitor& guest)\
	{return guest.GenericVisit(guest);}
}

#endif