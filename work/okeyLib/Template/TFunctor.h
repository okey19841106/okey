/********************************************************************
	created:	2015/07/31
	created:	15:50
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TEMPLATE_FUCTOR_H__
#define __TEMPLATE_FUCTOR_H__

#include "TNull.h"
#include "TypeTraits.h"
#include <memory>

namespace Template
{

	class EmptyType{};

	inline bool operator==(const EmptyType&, const EmptyType&){return true;}
	inline bool operator<(const EmptyType&, const EmptyType&){return false;}
	inline bool operator>(const EmptyType&, const EmptyType&){return false;}

	template<typename R>
	struct FunctorImplBase
	{
		typedef R ResultType;
		typedef FunctorImplBase<R> FunctorImplBaseType;
		typedef EmptyType Param0;
		typedef EmptyType Param1;
		typedef EmptyType Param2;
		typedef EmptyType Param3;
		typedef EmptyType Param4;
		typedef EmptyType Param5;
		typedef EmptyType Param6;
		typedef EmptyType Param7;
		typedef EmptyType Param8;
		typedef EmptyType Param9;
		typedef EmptyType Param10;
		typedef EmptyType Param11;
		typedef EmptyType Param12;
		typedef EmptyType Param13;
		typedef EmptyType Param14;
		virtual ~FunctorImplBase(){}
		virtual FunctorImplBase* DoClone() const = 0;
		template<typename T>
		static T* Clone(T* pObj)
		{
			if (!pObj)
			{
				return NULL;
			}
			T* pClone = static_cast<T*>(pObj->DoClone());
			//assert
			return pClone;
		}
		virtual bool operator==(const FunctorImplBase&) const = 0;
	};

#define TEMPLATE_DEFINE_CLONE_FUCTORIMPL(Cls)	\
	virtual Cls* DoClone() const{return new Cls(*this);}

	template<typename R, typename TL>
	class FunctorImpl;

	template<typename R>
	class FunctorImpl<R, NullType>: public FunctorImplBase<R>
	{
	public:
		typedef R ResultType;
		virtual R operator()() = 0;
	};

	template<typename R, typename P0>
	class FunctorImpl<R, TypeListType<P0> >: public FunctorImplBase<R >
	{
	public:
		typedef R ResultType;
		typedef typename TypeTraits<P0>::ParameterType Param0;
		virtual R operator()(Param0) = 0;
	};

	template<typename R, typename P0, typename P1>
	class FunctorImpl<R, TypeListType<P0, P1> >: public FunctorImplBase<R >
	{
	public:
		typedef R ResultType;
		typedef typename TypeTraits<P0>::ParameterType Param0;
		typedef typename TypeTraits<P1>::ParameterType Param1;
		virtual R operator()(Param0, Param1) = 0;
	};

	template<typename R, typename P0, typename P1, typename P2 >
	class FunctorImpl<R, TypeListType<P0, P1, P2> >: public FunctorImplBase<R >
	{
	public:
		typedef R ResultType;
		typedef typename TypeTraits<P0>::ParameterType Param0;
		typedef typename TypeTraits<P1>::ParameterType Param1;
		typedef typename TypeTraits<P2>::ParameterType Param2;
		virtual R operator()(Param0, Param1, Param2) = 0;
	};

	template<typename R, typename P0, typename P1, typename P2, typename P3 >
	class FunctorImpl<R, TypeListType<P0, P1, P2, P3> >: public FunctorImplBase<R >
	{
	public:
		typedef R ResultType;
		typedef typename TypeTraits<P0>::ParameterType Param0;
		typedef typename TypeTraits<P1>::ParameterType Param1;
		typedef typename TypeTraits<P2>::ParameterType Param2;
		typedef typename TypeTraits<P3>::ParameterType Param3;
		virtual R operator()(Param0, Param1, Param2, Param3) = 0;
	};
	
	//后续再加。。
	template<class ParentFunctor, typename Fun>
	class FunctorHandler: public ParentFunctor::Impl
	{
		typedef typename ParentFunctor::Impl Base;
	public:
		typedef typename Base::ResultType ResultType;
		typedef typename Base::Param0 Param0;
		typedef typename Base::Param1 Param1;
		typedef typename Base::Param2 Param2;
		typedef typename Base::Param3 Param3;
		typedef typename Base::Param4 Param4;
		typedef typename Base::Param5 Param5;
		typedef typename Base::Param6 Param6;
		typedef typename Base::Param7 Param7;
		typedef typename Base::Param8 Param8;
		typedef typename Base::Param9 Param9;
		typedef typename Base::Param10 Param10;
		typedef typename Base::Param11 Param11;
		typedef typename Base::Param12 Param12;
		typedef typename Base::Param13 Param13;
		typedef typename Base::Param14 Param14;

		FunctorHandler(const Fun& fun):_f(fun){}

		TEMPLATE_DEFINE_CLONE_FUCTORIMPL(FunctorHandler);

		bool operator==(const typename Base::FunctorImplBaseType& rhs) const
		{
			if (typeid(*this) != typeid(rhs))
			{
				return false;
			}
			const FunctorHandler& fh = static_cast<const FunctorHandler&>(rhs);
			return _f == fh._f;
		}
		ResultType operator()(){return _f();}
		ResultType operator()(Param0 p0){return _f(p0);}
		ResultType operator()(Param0 p0, Param1 p1){return _f(p0, p1);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2){return _f(p0, p1, p2);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2, Param3 p3){return _f(p0, p1, p2, p3);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4){return _f(p0, p1, p2, p3, p4);}
		//带添加。。
	private:
		Fun _f;
	};

	template<class ParentFunctor,typename PointObj, typename PointFun>
	class MemFunHandler: public ParentFunctor::Impl
	{
		typedef typename ParentFunctor::Impl Base;
	public:
		typedef typename Base::ResultType ResultType;
		typedef typename Base::Param0 Param0;
		typedef typename Base::Param1 Param1;
		typedef typename Base::Param2 Param2;
		typedef typename Base::Param3 Param3;
		typedef typename Base::Param4 Param4;
		typedef typename Base::Param5 Param5;
		typedef typename Base::Param6 Param6;
		typedef typename Base::Param7 Param7;
		typedef typename Base::Param8 Param8;
		typedef typename Base::Param9 Param9;
		typedef typename Base::Param10 Param10;
		typedef typename Base::Param11 Param11;
		typedef typename Base::Param12 Param12;
		typedef typename Base::Param13 Param13;
		typedef typename Base::Param14 Param14;

		MemFunHandler(const PointObj& pObj, PointFun pfun):_pObj(pObj),_f(fun){}

		TEMPLATE_DEFINE_CLONE_FUCTORIMPL(MemFunHandler);

		bool operator==(const typename Base::FunctorImplBaseType& rhs) const
		{
			if (typeid(*this) != typeid(rhs))
			{
				return false;
			}
			const MemFunHandler& fh = static_cast<const MemFunHandler&>(rhs);
			return _pObj==fh._pObj && _f == fh._f;
		}
		ResultType operator()(){return ((*_pObj).*_f)();}
		ResultType operator()(Param0 p0){return ((*_pObj).*_f)(p0);}
		ResultType operator()(Param0 p0, Param1 p1){return ((*_pObj).*_f)(p0, p1);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2){return ((*_pObj).*_f)(p0, p1, p2);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2, Param3 p3){return ((*_pObj).*_f)(p0, p1, p2, p3);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4){return ((*_pObj).*_f)(p0, p1, p2, p3, p4);}
		//带添加。。
	private:
		PointObj _pObj;
		PointFun _f;
	};

	template<typename R = void, class TL = NullType >
	class Functor
	{
	public:
		typedef FunctorImpl<R, TL > Impl;
		typedef R ResultType;
		typedef TL ParamList;
		typedef typename Impl::Param0 Param0;
		typedef typename Impl::Param1 Param1;
		typedef typename Impl::Param2 Param2;
		typedef typename Impl::Param3 Param3;
		typedef typename Impl::Param4 Param4;
		typedef typename Impl::Param5 Param5;
		typedef typename Impl::Param6 Param6;
		typedef typename Impl::Param7 Param7;
		typedef typename Impl::Param8 Param8;
		typedef typename Impl::Param9 Param9;
		typedef typename Impl::Param10 Param10;
		typedef typename Impl::Param11 Param11;
		typedef typename Impl::Param12 Param12;
		typedef typename Impl::Param13 Param13;
		typedef typename Impl::Param14 Param14;
		Functor():_spImpl(NULL){}
		Functor(const Functor& rhs):_spImpl(Impl::Clone(rhs._spImpl.get())){}
		Functor(std::auto_ptr<Impl> spImpl):_spImpl(spImpl){}
		template<typename Fun>
		Functor(Fun fun):_spImpl(new FunctorHandler<Functor, Fun>(fun)){}
		template<typename PtrObj, typename MemFun>
		Functor(const PtrObj& p, MemFun memfn):_spImpl(new MemFunHandler<Functor, PtrObj, MemFun>(p,memfn)){}
		typedef Impl* (std::auto_ptr<Impl>::*unspecified_bool_type)()const;
		operator unspecified_bool_type() const
		{
			return _spImpl.get() ? &std::auto_ptr<Impl>::get : NULL;
		}
		Functor& operator=(const Functor& rhs)
		{
			Functor copy(rhs);
			Impl* p = _spImpl.release();
			_spImpl.reset(copy._spImpl.release());
			copy._spImpl.reset(p);
			return *this;
		}
		bool empty()const{return _spImpl.get() == NULL;}
		void clear(){_spImpl.reset(NULL);}
		bool operator==(const Functor& rhs)const
		{
			if (_spImpl.get() == NULL && rhs._spImpl.get() == NULL)
			{
				return true;
			}
			if (_spImpl.get() != NULL && rhs._spImpl.get() != NULL)
			{
				return _spImpl.get() == rhs._spImpl.get();
			}
			else
				return false;
		}
		bool operator!=(const Functor& rhs) const
		{
			return !(*this == rhs);
		}
		ResultType operator()(){return (*_spImpl)();}
		ResultType operator()(Param0 p0){return (*_spImpl)(p0);}
		ResultType operator()(Param0 p0, Param1 p1){return (*_spImpl)(p0, p1);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2){return (*_spImpl)(p0, p1, p2);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2, Param3 p3){return (*_spImpl)(p0, p1, p2, p3);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4){return (*_spImpl)(p0, p1, p2, p3, p4);}
		//带添加。。
	private:
		std::auto_ptr<Impl> _spImpl;
	};

	template <typename Fctor>
	struct BinderFirstTraits;

	template<typename R, typename TL >
	struct BinderFirstTraits<Functor<R, TL > >
	{
		typedef Functor<R, TL > OriginalFunctor;
		typedef typename TypeOneEraser<TL, typename TypeGetter<0, TL>::HeadType>::ResultType ParamList;
		typedef typename TypeGetter<0, TL>::ResultType OriginalParam0;
		typedef Functor<R, ParamList > BoundFunctorType;
		typedef typename BoundFunctorType::Impl Impl;
	};

	template<typename T>
	struct BinderFirstBoundTypeStorage;

	template<typename T>
	struct BinderFirstBoundTypeStorage
	{
		typedef typename TypeTraits<T>::ParameterType RefOrValue;
	};

	template<typename R, typename TL >
	struct BinderFirstBoundTypeStorage<Functor<R, TL > >
	{
		typedef Functor<R, TL > OriginalFunctor;
		typedef const typename TypeTraits<OriginalFunctor>::ReferredType RefOrValue;
	};

	template<typename OriginalFunctor>
	class BinderFirst: public BinderFirstTraits<OriginalFunctor>::Impl
	{
		typedef typename BinderFirstTraits<OriginalFunctor>::Impl Base;
		typedef typename OriginalFunctor::ResultType ResultType;
		typedef typename OriginalFunctor::Param0 BoundType;
		typedef typename BinderFirstBoundTypeStorage<typename BinderFirstTraits<OriginalFunctor>::OriginalParam0 >::RefOrValue BoundTypeStorage;
		typedef typename OriginalFunctor::Param1 Param0;
		typedef typename OriginalFunctor::Param2 Param1;
		typedef typename OriginalFunctor::Param3 Param2;
		typedef typename OriginalFunctor::Param4 Param3;
		typedef typename OriginalFunctor::Param5 Param4;
		typedef typename OriginalFunctor::Param6 Param5;
		typedef typename OriginalFunctor::Param7 Param6;
		typedef typename OriginalFunctor::Param8 Param7;
		typedef typename OriginalFunctor::Param9 Param8;
		typedef typename OriginalFunctor::Param10 Param9;
		typedef typename OriginalFunctor::Param11 Param10;
		typedef typename OriginalFunctor::Param12 Param11;
		typedef typename OriginalFunctor::Param13 Param12;
		typedef typename OriginalFunctor::Param14 Param13;
		typedef typename EmptyType Param14;
	public:
		BinderFirst(const OriginalFunctor& fun, BoundType bound):_f(fun),_b(bound){}
		TEMPLATE_DEFINE_CLONE_FUCTORIMPL(MemFunHandler);
		bool operator == (const typename Base::FunctorImplBaseType& rhs) const
		{
			if (typeid(*this) != typeid(rhs))
			{
				return false;
			}
			return _f == ((static_cast<const BinderFirst&>(rhs))._f) && _b == ((static_cast<const BinderFirst&>(rhs))._b)
		}

		ResultType operator()(){return (_f)(_b);}
		ResultType operator()(Param0 p0){return  (_f)(_b,p0);}
		ResultType operator()(Param0 p0, Param1 p1){return (_f)(_b,p0, p1);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2){return (_f)(_b,p0, p1, p2);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2, Param3 p3){return (_f)(_b,p0, p1, p2, p3);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4){return (_f)(_b,p0, p1, p2, p3, p4);}
		//带添加。。
	private:
		OriginalFunctor _f;
		BoundTypeStorage _b;
	};

	template<typename Fctor>
	typename BinderFirstTraits<Fctor>::BoundFunctorType BindFirst(const Fctor& fun, typename Fctor::Param0 bound)
	{
		typedef typename BinderFirstTraits<Functor>::BoundFunctorType Outgoing;
		return Outgoing(std::auto_ptr<typename Outgoing::Impl>(new BinderFirst<Fctor>(fun,bound)));
	}

	template<typename Fun1, typename Fun2>
	class Chainer: public Fun2::Impl
	{
		typedef Fun2 Base;
	public:
		typedef typename Base::ResultType ResultType;
		typedef typename Base::Param0 Param0;
		typedef typename Base::Param1 Param1;
		typedef typename Base::Param2 Param2;
		typedef typename Base::Param3 Param3;
		typedef typename Base::Param4 Param4;
		typedef typename Base::Param5 Param5;
		typedef typename Base::Param6 Param6;
		typedef typename Base::Param7 Param7;
		typedef typename Base::Param8 Param8;
		typedef typename Base::Param9 Param9;
		typedef typename Base::Param10 Param10;
		typedef typename Base::Param11 Param11;
		typedef typename Base::Param12 Param12;
		typedef typename Base::Param13 Param13;
		typedef typename Base::Param14 Param14;
		Chainer(const Fun1& fun1, const Fun2& fun2):_f1(fun1),_f2(fun2){}
		TEMPLATE_DEFINE_CLONE_FUCTORIMPL(Chainer);
		bool operator==(const typename Base::Impl::FunctorImplBaseType& rhs)const
		{
			if (typeid(*this) != typeid(rhs))
			{
				return false;
			}
			return _f1 == ((static_cast<const Chainer&>(rhs))._f1) && _f2 == ((static_cast<const Chainer&>(rhs))._f2)
		}
		ResultType operator()(){return _f1(),_f2();}
		ResultType operator()(Param0 p0){return  _f1(p0),_f2(P0);}
		ResultType operator()(Param0 p0, Param1 p1){return _f1(p0, p1), _f2(p0, p1);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2){return _f1(p0, p1, p2), _f2(p0, p1, p2);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2, Param3 p3){return _f1(p0, p1, p2, p3), _f2(p0, p1, p2, p3);}
		ResultType operator()(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4){return _f1(p0, p1, p2, p3, p4),_f2(p0, p1, p2, p3, p4);}
	private:
		Fun1 _f1;
		Fun2 _f2;
	};

	template<typename Fun1, typename Fun2>
	Fun2 Chain(const Fun1& fun1, const Fun2& fun2)
	{
		return Fun2(std::auto_ptr<typename Fun2::Impl>(new Chainer<Fun1,Fun2>(fun1, fun2)));
	}
}


#endif