/********************************************************************
	created:	2015/01/22
	created:	11:20
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TEMPLATE_TYPE_LIST_H__
#define __TEMPLATE_TYPE_LIST_H__

#include "TMeta.h"

namespace Template
{
	struct NullTypeList
	{
		enum
		{
			length = 0
		};

		bool operator == (const NullTypeList&) const
		{
			return true;
		}

		bool operator != (const NullTypeList&) const
		{
			return false;
		}

		bool operator < (const NullTypeList&) const
		{
			return false;
		}
	};

	template<typename Head, typename Tail>
	struct TypeList  
	{
	
		typedef Head HeadType;
		typedef Tail TailType;
		typedef typename TypeWrapper<HeadType>::CONSTTYPE ConstHeadType;
		typedef typename TypeWrapper<TailType>::CONSTTYPE ConstTailType;

		enum
		{
			length = TailType::length+1
		};

		TypeList():_head(), _tail(){}
		TypeList(HeadType h, TailType t): _head(h), _tail(t){}
		TypeList(const TypeList& t):_head(t._head),_tail(t._tail){}
		TypeList& operator=(const TypeList& t)
		{
			if (&t != this)
			{
				TypeList tmp(t);
				Swap(tmp);
			}
			return *this;
		}
		void Swap(TypeList& t)
		{
			std::swap(_head, t._head);
			std::swap(_tail, t._tail);
		}
		bool operator == (const TypeList& t) const
		{
			return _head == t._head && _tail == t._tail;
		}

		bool operator !=(const TypeList& t) const
		{
			return !(*this == tl);
		}

		bool operator < (const TypeList& t) const
		{
			if (_head < t._head)
				return true;
			else if (_head == t._head)
				return _tail < t._tail;
			return false;
		}

		HeadType _head;
		TailType _tail;
	};

	template <typename T0  = NullTypeList, 
		typename T1  = NullTypeList, 
		typename T2  = NullTypeList,
		typename T3  = NullTypeList, 
		typename T4  = NullTypeList, 
		typename T5  = NullTypeList,
		typename T6  = NullTypeList, 
		typename T7  = NullTypeList, 
		typename T8  = NullTypeList,
		typename T9  = NullTypeList, 
		typename T10 = NullTypeList, 
		typename T11 = NullTypeList,
		typename T12 = NullTypeList, 
		typename T13 = NullTypeList, 
		typename T14 = NullTypeList,
		typename T15 = NullTypeList, 
		typename T16 = NullTypeList, 
		typename T17 = NullTypeList,
		typename T18 = NullTypeList,
		typename T19 = NullTypeList> 
	struct TypeListType
	{
	private:
		typedef typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType TailType;
	public:
		typedef TypeList<T0, TailType> ResultType; //结果。。 T0 就是HeadType
	};

	template<>
	struct TypeListType<>
	{
		typedef NullTypeList ResultType;
	};

	template <int n> 
	struct Getter //取第几个参数。。
	{
		template <class Ret, class Head, class Tail>
		inline static Ret& Get(TypeList<Head, Tail>& val)
		{
			return Getter<n-1>::template Get<Ret, typename Tail::HeadType, typename Tail::TailType>(val._tail);
		}

		template <class Ret, class Head, class Tail>
		inline static const Ret& Get(const TypeList<Head, Tail>& val)
		{
			return Getter<n-1>::template Get<Ret, typename Tail::HeadType, typename Tail::TailType>(val._tail);
		}
	};

	template <> 
	struct Getter<0>
	{
		template <class Ret, class Head, class Tail>
		inline static Ret& Get(TypeList<Head, Tail>& val)
		{
			return val._head;
		}

		template <class Ret, class Head, class Tail>
		inline static const Ret& Get(const TypeList<Head, Tail>& val)
		{
			return val._head;
		}
	};

	template <int N, typename Head> 
	struct TypeGetter;

	template <int N, typename Head, typename Tail>
	struct TypeGetter<N, TypeList<Head, Tail> >
	{
		typedef typename TypeGetter<N-1, Tail>::HeadType HeadType;
		typedef typename TypeWrapper<HeadType>::CONSTTYPE ConstHeadType;
	};

	template <typename Head, typename Tail>
	struct TypeGetter<0, TypeList<Head, Tail> >
	{
		typedef typename TypeList<Head, Tail>::HeadType HeadType;
		typedef typename TypeWrapper<HeadType>::CONSTTYPE ConstHeadType;
	};

	template <typename Head, typename T>//returns the first occurrence of the type T in Head
	struct TypeLocator;

	template <typename T>
	struct TypeLocator<NullTypeList, T>
	{
		enum
		{
			value = -1,
		};
	};

	template <typename T, typename Tail>
	struct TypeLocator<TypeList<T, Tail>, T>
	{
		enum 
		{ 
			value = 0 ,
		};
	};

	template <typename Head, typename Tail, typename T>
	struct TypeLocator<TypeList<Head, Tail>, T>
	{
	private:
		enum 
		{ 
			tmp = TypeLocator<Tail, T>::value ,
		};
	public:
		enum 
		{ 
			value = tmp == -1 ? -1 : 1 + tmp ,
		};
	};

	template <typename Head, typename T> 
	struct TypeAppender; /// TypeAppender appends T (type or a TypeList) to Head.

	template<>
	struct TypeAppender<NullTypeList, NullTypeList>
	{
		typedef NullTypeList ResultType;
	};

	template<typename T>
	struct TypeAppender<NullTypeList, T>
	{
		typedef TypeList<T, NullTypeList> ResultType;
	};

	template<typename Head, typename Tail>
	struct TypeAppender<NullTypeList, TypeList<Head, Tail> >
	{
		typedef TypeList<Head, Tail> ResultType;
	};

	template <typename Head, typename Tail, typename T>
	struct TypeAppender<TypeList<Head, Tail>, T>
	{
		typedef TypeList<Head, typename TypeAppender<Tail, T>::ResultType> ResultType;
	};

	template <typename Head, typename T> 
	struct TypeOneEraser;	/// TypeOneEraser erases the first occurence of the type T in Head.

	template <typename T>
	struct TypeOneEraser<NullTypeList, T>
	{
		typedef NullTypeList ResultType;
	};

	template <typename T, typename Tail>
	struct TypeOneEraser<TypeList<T, Tail>, T>
	{
		typedef Tail ResultType;
	};

	template <typename Head, typename Tail, typename T>
	struct TypeOneEraser<TypeList<Head, Tail>, T>
	{
		typedef TypeList <Head, typename TypeOneEraser<Tail, T>::ResultType> ResultType;
	};

	template <typename Head, typename T> 
	struct TypeAllEraser;	/// TypeAllEraser erases all the occurences of the type T in Head.

	template <typename T>
	struct TypeAllEraser<NullTypeList, T>
	{
		typedef NullTypeList ResultType;
	};

	template <typename T, typename Tail>
	struct TypeAllEraser<TypeList<T, Tail>, T>
	{
		typedef typename TypeAllEraser<Tail, T>::ResultType ResultType;
	};

	template <typename Head, typename Tail, typename T>
	struct TypeAllEraser<TypeList<Head, Tail>, T>
	{
		typedef TypeList <Head, typename TypeAllEraser<Tail, T>::ResultType> ResultType;
	};

	template <typename Head> 
	struct TypeDuplicateEraser;/// TypeDuplicateEraser erases all but the first occurence of the type T in Head.

	template<>
	struct TypeDuplicateEraser<NullTypeList>
	{
		typedef NullTypeList ResultType;
	};

	template <typename Head, typename Tail>
	struct TypeDuplicateEraser<TypeList<Head, Tail> >
	{
	private:
		typedef typename TypeDuplicateEraser<Tail>::ResultType L1;
		typedef typename TypeOneEraser<L1, Head>::ResultType L2;
	public:
		typedef TypeList<Head, L2> ResultType;
	};

	template <typename Head, typename T, typename R>
	struct TypeOneReplacer;	/// TypeOneReplacer replaces the first occurence 

	template <typename T, typename R>
	struct TypeOneReplacer<NullTypeList, T, R>
	{
		typedef NullTypeList ResultType;
	};


	template <typename T, typename Tail, typename R>
	struct TypeOneReplacer<TypeList<T, Tail>, T, R>
	{
		typedef TypeList<R, Tail> ResultType;
	};


	template <typename Head, typename Tail, typename T, typename R>
	struct TypeOneReplacer<TypeList<Head, Tail>, T, R>
	{
		typedef TypeList<Head, typename TypeOneReplacer<Tail, T, R>::ResultType> ResultType;
	};

	template <typename Head, typename T, typename R>
	struct TypeAllReplacer;	/// TypeAllReplacer replaces all the occurences 

	template <typename T, typename R>
	struct TypeAllReplacer<NullTypeList, T, R>
	{
		typedef NullTypeList ResultType;
	};


	template <typename T, typename Tail, typename R>
	struct TypeAllReplacer<TypeList<T, Tail>, T, R>
	{
		typedef TypeList<R, typename TypeAllReplacer<Tail, T, R>::ResultType> ResultType;
	};


	template <typename Head, typename Tail, typename T, typename R>
	struct TypeAllReplacer<TypeList<Head, Tail>, T, R>
	{
		typedef TypeList<Head, typename TypeAllReplacer<Tail, T, R>::ResultType> ResultType;
	};
}

#endif