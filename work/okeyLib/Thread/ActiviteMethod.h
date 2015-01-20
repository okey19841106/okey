/********************************************************************
	created:	2015/01/20
	created:	15:57
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __THREAD_ACTIVITE_METHOD_H__
#define __THREAD_ACTIVITE_METHOD_H__

#include "ActiveResult.h"
#include "ActiveRunnable.h"

namespace okey
{
	template <class ResultType, class ArgType, class OwnerType, class StarterType = ActiveStarter<OwnerType> >
	class ActiveMethod
	{
	public:
		typedef ResultType (OwnerType::*Callback)(const ArgType&);
		typedef ActiveResult<ResultType> ActiveResultType;
		typedef ActiveRunnable<ResultType, ArgType, OwnerType> ActiveRunnableType;
	public:
		ActiveMethod(OwnerType* pOwner, Callback method):_pOwner(pOwner),_method(method)
		{

		}
		ActiveMethod(const ActiveMethod& r):_pOwner(r.pOwner),_method(r.method)
		{

		}
		ActiveMethod& operator=(const ActiveMethod& r)
		{
			ActiveMethod tmp(r);
			Swap(r);
			return *this;
		}
		~ActiveMethod()
		{

		}
		ActiveResultType operator () (const ArgType& arg)
		{
			ActiveResultType result(new ActiveResultHolder<ResultType>());
			ActiveRunnableBase::Ptr pRunnable(new ActiveRunnableType(_pOwner, _method, arg, result));
			StarterType::Start(_pOwner, pRunnable);
			return result;
		}

		void Swap(ActiveMethod& r)
		{
			std::swap(_pOwner, r._pOwner);
			std::swap(_method, r._method);
		}
	private:
		ActiveMethod();
	private:
		OwnerType* _pOwner;
		Callback   _method;
	};

	template <class ResultType, class OwnerType, class StarterType>
	class ActiveMethod <ResultType, void, OwnerType, StarterType>
	{
		typedef ResultType (OwnerType::*Callback)();
		typedef ActiveResult<ResultType> ActiveResultType;
		typedef ActiveRunnable<ResultType, void, OwnerType> ActiveRunnableType;
	public:
		ActiveMethod(OwnerType* pOwner, Callback method):_pOwner(pOwner),_method(method)
		{

		}
		ActiveMethod(const ActiveMethod& r):_pOwner(r.pOwner),_method(r.method)
		{

		}
		ActiveMethod& operator=(const ActiveMethod& r)
		{
			ActiveMethod tmp(r);
			Swap(r);
			return *this;
		}
		~ActiveMethod()
		{

		}
		ActiveResultType operator()(void)
		{
			ActiveResultType result(new ActiveResultHolder<ResultType>());
			ActiveRunnableBase::Ptr pRunnable(new ActiveRunnableType(_pOwner, _method, result));
			StarterType::Start(_pOwner, pRunnable);
			return result;
		}
		void Swap(ActiveMethod& r)
		{
			std::swap(_pOwner, r._pOwner);
			std::swap(_method, r._method);
		}
	private:
		ActiveMethod();
	private:
		OwnerType* _pOwner;
		Callback   _method;
	};


}

#endif