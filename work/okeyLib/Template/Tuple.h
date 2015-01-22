#ifndef __TEMPLATE_TUPLE_H__
#define __TEMPLATE_TUPLE_H__

#include "TTypeList.h"


namespace Template {


#if defined(_MSC_VER) 
#define TYPEWRAPPER_DEFAULTVALUE(T) TypeWrapper<T>::TYPE()
#else
#define TYPEWRAPPER_DEFAULTVALUE(T) typename TypeWrapper<T>::TYPE()
#endif


	template <class T0,
	class T1 = NullTypeList,
	class T2 = NullTypeList,
	class T3 = NullTypeList,
	class T4 = NullTypeList,
	class T5 = NullTypeList,
	class T6 = NullTypeList,
	class T7 = NullTypeList,
	class T8 = NullTypeList,
	class T9 = NullTypeList,
	class T10 = NullTypeList,
	class T11 = NullTypeList,
	class T12 = NullTypeList,
	class T13 = NullTypeList,
	class T14 = NullTypeList,
	class T15 = NullTypeList,
	class T16 = NullTypeList,
	class T17 = NullTypeList,
	class T18 = NullTypeList,
	class T19 = NullTypeList>
	struct Tuple
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0,
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5),
			typename TypeWrapper<T6>::CONSTTYPE& t6 = TYPEWRAPPER_DEFAULTVALUE(T6),
			typename TypeWrapper<T7>::CONSTTYPE& t7 = TYPEWRAPPER_DEFAULTVALUE(T7),
			typename TypeWrapper<T8>::CONSTTYPE& t8 = TYPEWRAPPER_DEFAULTVALUE(T8),
			typename TypeWrapper<T9>::CONSTTYPE& t9 = TYPEWRAPPER_DEFAULTVALUE(T9),
			typename TypeWrapper<T10>::CONSTTYPE& t10 = TYPEWRAPPER_DEFAULTVALUE(T10),
			typename TypeWrapper<T11>::CONSTTYPE& t11 = TYPEWRAPPER_DEFAULTVALUE(T11),
			typename TypeWrapper<T12>::CONSTTYPE& t12 = TYPEWRAPPER_DEFAULTVALUE(T12),
			typename TypeWrapper<T13>::CONSTTYPE& t13 = TYPEWRAPPER_DEFAULTVALUE(T13),
			typename TypeWrapper<T14>::CONSTTYPE& t14 = TYPEWRAPPER_DEFAULTVALUE(T14),
			typename TypeWrapper<T15>::CONSTTYPE& t15 = TYPEWRAPPER_DEFAULTVALUE(T15),
			typename TypeWrapper<T16>::CONSTTYPE& t16 = TYPEWRAPPER_DEFAULTVALUE(T16),
			typename TypeWrapper<T17>::CONSTTYPE& t17 = TYPEWRAPPER_DEFAULTVALUE(T17),
			typename TypeWrapper<T18>::CONSTTYPE& t18 = TYPEWRAPPER_DEFAULTVALUE(T18),
			typename TypeWrapper<T19>::CONSTTYPE& t19 = TYPEWRAPPER_DEFAULTVALUE(T19)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType
			(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType
			(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType
			(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType
			(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType
			(t6, typename TypeListType<T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType
			(t7, typename TypeListType<T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType
			(t8, typename TypeListType<T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType
			(t9, typename TypeListType<T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType
			(t10, typename TypeListType<T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType
			(t11, typename TypeListType<T12,T13,T14,T15,T16,T17,T18,T19>::ResultType
			(t12, typename TypeListType<T13,T14,T15,T16,T17,T18,T19>::ResultType
			(t13, typename TypeListType<T14,T15,T16,T17,T18,T19>::ResultType
			(t14, typename TypeListType<T15,T16,T17,T18,T19>::ResultType
			(t15, typename TypeListType<T16,T17,T18,T19>::ResultType
			(t16, typename TypeListType<T17,T18,T19>::ResultType
			(t17, typename TypeListType<T18,T19>::ResultType
			(t18, typename TypeListType<T19>::ResultType
			(t19, NullTypeList()))))))))))))))))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4,
	class T5,
	class T6,
	class T7,
	class T8,
	class T9,
	class T10,
	class T11,
	class T12,
	class T13,
	class T14,
	class T15,
	class T16,
	class T17,
	class T18>
	struct Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5),
			typename TypeWrapper<T6>::CONSTTYPE& t6 = TYPEWRAPPER_DEFAULTVALUE(T6),
			typename TypeWrapper<T7>::CONSTTYPE& t7 = TYPEWRAPPER_DEFAULTVALUE(T7),
			typename TypeWrapper<T8>::CONSTTYPE& t8 = TYPEWRAPPER_DEFAULTVALUE(T8),
			typename TypeWrapper<T9>::CONSTTYPE& t9 = TYPEWRAPPER_DEFAULTVALUE(T9),
			typename TypeWrapper<T10>::CONSTTYPE& t10 = TYPEWRAPPER_DEFAULTVALUE(T10),
			typename TypeWrapper<T11>::CONSTTYPE& t11 = TYPEWRAPPER_DEFAULTVALUE(T11),
			typename TypeWrapper<T12>::CONSTTYPE& t12 = TYPEWRAPPER_DEFAULTVALUE(T12),
			typename TypeWrapper<T13>::CONSTTYPE& t13 = TYPEWRAPPER_DEFAULTVALUE(T13),
			typename TypeWrapper<T14>::CONSTTYPE& t14 = TYPEWRAPPER_DEFAULTVALUE(T14),
			typename TypeWrapper<T15>::CONSTTYPE& t15 = TYPEWRAPPER_DEFAULTVALUE(T15),
			typename TypeWrapper<T16>::CONSTTYPE& t16 = TYPEWRAPPER_DEFAULTVALUE(T16),
			typename TypeWrapper<T17>::CONSTTYPE& t17 = TYPEWRAPPER_DEFAULTVALUE(T17),
			typename TypeWrapper<T18>::CONSTTYPE& t18 = TYPEWRAPPER_DEFAULTVALUE(T18)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType
			(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType
			(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType
			(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType
			(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType
			(t6, typename TypeListType<T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType
			(t7, typename TypeListType<T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType
			(t8, typename TypeListType<T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType
			(t9, typename TypeListType<T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType
			(t10, typename TypeListType<T11,T12,T13,T14,T15,T16,T17,T18>::ResultType
			(t11, typename TypeListType<T12,T13,T14,T15,T16,T17,T18>::ResultType
			(t12, typename TypeListType<T13,T14,T15,T16,T17,T18>::ResultType
			(t13, typename TypeListType<T14,T15,T16,T17,T18>::ResultType
			(t14, typename TypeListType<T15,T16,T17,T18>::ResultType
			(t15, typename TypeListType<T16,T17,T18>::ResultType
			(t16, typename TypeListType<T17,T18>::ResultType
			(t17, typename TypeListType<T18>::ResultType
			(t18, NullTypeList())))))))))))))))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4,
	class T5,
	class T6,
	class T7,
	class T8,
	class T9,
	class T10,
	class T11,
	class T12,
	class T13,
	class T14,
	class T15,
	class T16,
	class T17>
	struct Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5),
			typename TypeWrapper<T6>::CONSTTYPE& t6 = TYPEWRAPPER_DEFAULTVALUE(T6),
			typename TypeWrapper<T7>::CONSTTYPE& t7 = TYPEWRAPPER_DEFAULTVALUE(T7),
			typename TypeWrapper<T8>::CONSTTYPE& t8 = TYPEWRAPPER_DEFAULTVALUE(T8),
			typename TypeWrapper<T9>::CONSTTYPE& t9 = TYPEWRAPPER_DEFAULTVALUE(T9),
			typename TypeWrapper<T10>::CONSTTYPE& t10 = TYPEWRAPPER_DEFAULTVALUE(T10),
			typename TypeWrapper<T11>::CONSTTYPE& t11 = TYPEWRAPPER_DEFAULTVALUE(T11),
			typename TypeWrapper<T12>::CONSTTYPE& t12 = TYPEWRAPPER_DEFAULTVALUE(T12),
			typename TypeWrapper<T13>::CONSTTYPE& t13 = TYPEWRAPPER_DEFAULTVALUE(T13),
			typename TypeWrapper<T14>::CONSTTYPE& t14 = TYPEWRAPPER_DEFAULTVALUE(T14),
			typename TypeWrapper<T15>::CONSTTYPE& t15 = TYPEWRAPPER_DEFAULTVALUE(T15),
			typename TypeWrapper<T16>::CONSTTYPE& t16 = TYPEWRAPPER_DEFAULTVALUE(T16),
			typename TypeWrapper<T17>::CONSTTYPE& t17 = TYPEWRAPPER_DEFAULTVALUE(T17)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType
			(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType
			(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType
			(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType
			(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType
			(t6, typename TypeListType<T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType
			(t7, typename TypeListType<T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType
			(t8, typename TypeListType<T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType
			(t9, typename TypeListType<T10,T11,T12,T13,T14,T15,T16,T17>::ResultType
			(t10, typename TypeListType<T11,T12,T13,T14,T15,T16,T17>::ResultType
			(t11, typename TypeListType<T12,T13,T14,T15,T16,T17>::ResultType
			(t12, typename TypeListType<T13,T14,T15,T16,T17>::ResultType
			(t13, typename TypeListType<T14,T15,T16,T17>::ResultType
			(t14, typename TypeListType<T15,T16,T17>::ResultType
			(t15, typename TypeListType<T16,T17>::ResultType
			(t16, typename TypeListType<T17>::ResultType
			(t17, NullTypeList()))))))))))))))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4,
	class T5,
	class T6,
	class T7,
	class T8,
	class T9,
	class T10,
	class T11,
	class T12,
	class T13,
	class T14,
	class T15,
	class T16>
	struct Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5),
			typename TypeWrapper<T6>::CONSTTYPE& t6 = TYPEWRAPPER_DEFAULTVALUE(T6),
			typename TypeWrapper<T7>::CONSTTYPE& t7 = TYPEWRAPPER_DEFAULTVALUE(T7),
			typename TypeWrapper<T8>::CONSTTYPE& t8 = TYPEWRAPPER_DEFAULTVALUE(T8),
			typename TypeWrapper<T9>::CONSTTYPE& t9 = TYPEWRAPPER_DEFAULTVALUE(T9),
			typename TypeWrapper<T10>::CONSTTYPE& t10 = TYPEWRAPPER_DEFAULTVALUE(T10),
			typename TypeWrapper<T11>::CONSTTYPE& t11 = TYPEWRAPPER_DEFAULTVALUE(T11),
			typename TypeWrapper<T12>::CONSTTYPE& t12 = TYPEWRAPPER_DEFAULTVALUE(T12),
			typename TypeWrapper<T13>::CONSTTYPE& t13 = TYPEWRAPPER_DEFAULTVALUE(T13),
			typename TypeWrapper<T14>::CONSTTYPE& t14 = TYPEWRAPPER_DEFAULTVALUE(T14),
			typename TypeWrapper<T15>::CONSTTYPE& t15 = TYPEWRAPPER_DEFAULTVALUE(T15),
			typename TypeWrapper<T16>::CONSTTYPE& t16 = TYPEWRAPPER_DEFAULTVALUE(T16)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType
			(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType
			(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType
			(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType
			(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType
			(t6, typename TypeListType<T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType
			(t7, typename TypeListType<T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType
			(t8, typename TypeListType<T9,T10,T11,T12,T13,T14,T15,T16>::ResultType
			(t9, typename TypeListType<T10,T11,T12,T13,T14,T15,T16>::ResultType
			(t10, typename TypeListType<T11,T12,T13,T14,T15,T16>::ResultType
			(t11, typename TypeListType<T12,T13,T14,T15,T16>::ResultType
			(t12, typename TypeListType<T13,T14,T15,T16>::ResultType
			(t13, typename TypeListType<T14,T15,T16>::ResultType
			(t14, typename TypeListType<T15,T16>::ResultType
			(t15, typename TypeListType<T16>::ResultType
			(t16, NullTypeList())))))))))))))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4,
	class T5,
	class T6,
	class T7,
	class T8,
	class T9,
	class T10,
	class T11,
	class T12,
	class T13,
	class T14,
	class T15>
	struct Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5),
			typename TypeWrapper<T6>::CONSTTYPE& t6 = TYPEWRAPPER_DEFAULTVALUE(T6),
			typename TypeWrapper<T7>::CONSTTYPE& t7 = TYPEWRAPPER_DEFAULTVALUE(T7),
			typename TypeWrapper<T8>::CONSTTYPE& t8 = TYPEWRAPPER_DEFAULTVALUE(T8),
			typename TypeWrapper<T9>::CONSTTYPE& t9 = TYPEWRAPPER_DEFAULTVALUE(T9),
			typename TypeWrapper<T10>::CONSTTYPE& t10 = TYPEWRAPPER_DEFAULTVALUE(T10),
			typename TypeWrapper<T11>::CONSTTYPE& t11 = TYPEWRAPPER_DEFAULTVALUE(T11),
			typename TypeWrapper<T12>::CONSTTYPE& t12 = TYPEWRAPPER_DEFAULTVALUE(T12),
			typename TypeWrapper<T13>::CONSTTYPE& t13 = TYPEWRAPPER_DEFAULTVALUE(T13),
			typename TypeWrapper<T14>::CONSTTYPE& t14 = TYPEWRAPPER_DEFAULTVALUE(T14),
			typename TypeWrapper<T15>::CONSTTYPE& t15 = TYPEWRAPPER_DEFAULTVALUE(T15)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType
			(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType
			(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType
			(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType
			(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType
			(t6, typename TypeListType<T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType
			(t7, typename TypeListType<T8,T9,T10,T11,T12,T13,T14,T15>::ResultType
			(t8, typename TypeListType<T9,T10,T11,T12,T13,T14,T15>::ResultType
			(t9, typename TypeListType<T10,T11,T12,T13,T14,T15>::ResultType
			(t10, typename TypeListType<T11,T12,T13,T14,T15>::ResultType
			(t11, typename TypeListType<T12,T13,T14,T15>::ResultType
			(t12, typename TypeListType<T13,T14,T15>::ResultType
			(t13, typename TypeListType<T14,T15>::ResultType
			(t14, typename TypeListType<T15>::ResultType
			(t15, NullTypeList()))))))))))))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4,
	class T5,
	class T6,
	class T7,
	class T8,
	class T9,
	class T10,
	class T11,
	class T12,
	class T13,
	class T14>
	struct Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5),
			typename TypeWrapper<T6>::CONSTTYPE& t6 = TYPEWRAPPER_DEFAULTVALUE(T6),
			typename TypeWrapper<T7>::CONSTTYPE& t7 = TYPEWRAPPER_DEFAULTVALUE(T7),
			typename TypeWrapper<T8>::CONSTTYPE& t8 = TYPEWRAPPER_DEFAULTVALUE(T8),
			typename TypeWrapper<T9>::CONSTTYPE& t9 = TYPEWRAPPER_DEFAULTVALUE(T9),
			typename TypeWrapper<T10>::CONSTTYPE& t10 = TYPEWRAPPER_DEFAULTVALUE(T10),
			typename TypeWrapper<T11>::CONSTTYPE& t11 = TYPEWRAPPER_DEFAULTVALUE(T11),
			typename TypeWrapper<T12>::CONSTTYPE& t12 = TYPEWRAPPER_DEFAULTVALUE(T12),
			typename TypeWrapper<T13>::CONSTTYPE& t13 = TYPEWRAPPER_DEFAULTVALUE(T13),
			typename TypeWrapper<T14>::CONSTTYPE& t14 = TYPEWRAPPER_DEFAULTVALUE(T14)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>::ResultType
			(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>::ResultType
			(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>::ResultType
			(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>::ResultType
			(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12,T13,T14>::ResultType
			(t6, typename TypeListType<T7,T8,T9,T10,T11,T12,T13,T14>::ResultType
			(t7, typename TypeListType<T8,T9,T10,T11,T12,T13,T14>::ResultType
			(t8, typename TypeListType<T9,T10,T11,T12,T13,T14>::ResultType
			(t9, typename TypeListType<T10,T11,T12,T13,T14>::ResultType
			(t10, typename TypeListType<T11,T12,T13,T14>::ResultType
			(t11, typename TypeListType<T12,T13,T14>::ResultType
			(t12, typename TypeListType<T13,T14>::ResultType
			(t13, typename TypeListType<T14>::ResultType
			(t14, NullTypeList())))))))))))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4,
	class T5,
	class T6,
	class T7,
	class T8,
	class T9,
	class T10,
	class T11,
	class T12,
	class T13>
	struct Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5),
			typename TypeWrapper<T6>::CONSTTYPE& t6 = TYPEWRAPPER_DEFAULTVALUE(T6),
			typename TypeWrapper<T7>::CONSTTYPE& t7 = TYPEWRAPPER_DEFAULTVALUE(T7),
			typename TypeWrapper<T8>::CONSTTYPE& t8 = TYPEWRAPPER_DEFAULTVALUE(T8),
			typename TypeWrapper<T9>::CONSTTYPE& t9 = TYPEWRAPPER_DEFAULTVALUE(T9),
			typename TypeWrapper<T10>::CONSTTYPE& t10 = TYPEWRAPPER_DEFAULTVALUE(T10),
			typename TypeWrapper<T11>::CONSTTYPE& t11 = TYPEWRAPPER_DEFAULTVALUE(T11),
			typename TypeWrapper<T12>::CONSTTYPE& t12 = TYPEWRAPPER_DEFAULTVALUE(T12),
			typename TypeWrapper<T13>::CONSTTYPE& t13 = TYPEWRAPPER_DEFAULTVALUE(T13)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>::ResultType
			(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>::ResultType
			(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>::ResultType
			(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12,T13>::ResultType
			(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12,T13>::ResultType
			(t6, typename TypeListType<T7,T8,T9,T10,T11,T12,T13>::ResultType
			(t7, typename TypeListType<T8,T9,T10,T11,T12,T13>::ResultType
			(t8, typename TypeListType<T9,T10,T11,T12,T13>::ResultType
			(t9, typename TypeListType<T10,T11,T12,T13>::ResultType
			(t10, typename TypeListType<T11,T12,T13>::ResultType
			(t11, typename TypeListType<T12,T13>::ResultType
			(t12, typename TypeListType<T13>::ResultType
			(t13, NullTypeList()))))))))))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4,
	class T5,
	class T6,
	class T7,
	class T8,
	class T9,
	class T10,
	class T11,
	class T12>
	struct Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12, NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5),
			typename TypeWrapper<T6>::CONSTTYPE& t6 = TYPEWRAPPER_DEFAULTVALUE(T6),
			typename TypeWrapper<T7>::CONSTTYPE& t7 = TYPEWRAPPER_DEFAULTVALUE(T7),
			typename TypeWrapper<T8>::CONSTTYPE& t8 = TYPEWRAPPER_DEFAULTVALUE(T8),
			typename TypeWrapper<T9>::CONSTTYPE& t9 = TYPEWRAPPER_DEFAULTVALUE(T9),
			typename TypeWrapper<T10>::CONSTTYPE& t10 = TYPEWRAPPER_DEFAULTVALUE(T10),
			typename TypeWrapper<T11>::CONSTTYPE& t11 = TYPEWRAPPER_DEFAULTVALUE(T11),
			typename TypeWrapper<T12>::CONSTTYPE& t12 = TYPEWRAPPER_DEFAULTVALUE(T12)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>::ResultType
			(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>::ResultType
			(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12>::ResultType
			(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12>::ResultType
			(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12>::ResultType
			(t6, typename TypeListType<T7,T8,T9,T10,T11,T12>::ResultType
			(t7, typename TypeListType<T8,T9,T10,T11,T12>::ResultType
			(t8, typename TypeListType<T9,T10,T11,T12>::ResultType
			(t9, typename TypeListType<T10,T11,T12>::ResultType
			(t10, typename TypeListType<T11,T12>::ResultType
			(t11, typename TypeListType<T12>::ResultType
			(t12, NullTypeList())))))))))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4,
	class T5,
	class T6,
	class T7,
	class T8,
	class T9,
	class T10,
	class T11>
	struct Tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5),
			typename TypeWrapper<T6>::CONSTTYPE& t6 = TYPEWRAPPER_DEFAULTVALUE(T6),
			typename TypeWrapper<T7>::CONSTTYPE& t7 = TYPEWRAPPER_DEFAULTVALUE(T7),
			typename TypeWrapper<T8>::CONSTTYPE& t8 = TYPEWRAPPER_DEFAULTVALUE(T8),
			typename TypeWrapper<T9>::CONSTTYPE& t9 = TYPEWRAPPER_DEFAULTVALUE(T9),
			typename TypeWrapper<T10>::CONSTTYPE& t10 = TYPEWRAPPER_DEFAULTVALUE(T10),
			typename TypeWrapper<T11>::CONSTTYPE& t11 = TYPEWRAPPER_DEFAULTVALUE(T11)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>::ResultType
			(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11>::ResultType
			(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11>::ResultType
			(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11>::ResultType
			(t5, typename TypeListType<T6,T7,T8,T9,T10,T11>::ResultType
			(t6, typename TypeListType<T7,T8,T9,T10,T11>::ResultType
			(t7, typename TypeListType<T8,T9,T10,T11>::ResultType
			(t8, typename TypeListType<T9,T10,T11>::ResultType
			(t9, typename TypeListType<T10,T11>::ResultType
			(t10, typename TypeListType<T11>::ResultType
			(t11, NullTypeList()))))))))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4,
	class T5,
	class T6,
	class T7,
	class T8,
	class T9,
	class T10>
	struct Tuple<T0, T1,T2,T3,T4,T5,T6,T7,T8,T9,T10, NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5),
			typename TypeWrapper<T6>::CONSTTYPE& t6 = TYPEWRAPPER_DEFAULTVALUE(T6),
			typename TypeWrapper<T7>::CONSTTYPE& t7 = TYPEWRAPPER_DEFAULTVALUE(T7),
			typename TypeWrapper<T8>::CONSTTYPE& t8 = TYPEWRAPPER_DEFAULTVALUE(T8),
			typename TypeWrapper<T9>::CONSTTYPE& t9 = TYPEWRAPPER_DEFAULTVALUE(T9),
			typename TypeWrapper<T10>::CONSTTYPE& t10 = TYPEWRAPPER_DEFAULTVALUE(T10)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10>::ResultType
			(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10>::ResultType
			(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10>::ResultType
			(t4, typename TypeListType<T5,T6,T7,T8,T9,T10>::ResultType
			(t5, typename TypeListType<T6,T7,T8,T9,T10>::ResultType
			(t6, typename TypeListType<T7,T8,T9,T10>::ResultType
			(t7, typename TypeListType<T8,T9,T10>::ResultType
			(t8, typename TypeListType<T9,T10>::ResultType
			(t9, typename TypeListType<T10>::ResultType
			(t10, NullTypeList())))))))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4,
	class T5,
	class T6,
	class T7,
	class T8,
	class T9>
	struct Tuple<T0, T1,T2,T3,T4,T5,T6,T7,T8,T9, NullTypeList>
	{
		typedef typename TypeListType<T0, T1,T2,T3,T4,T5,T6,T7,T8,T9>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5),
			typename TypeWrapper<T6>::CONSTTYPE& t6 = TYPEWRAPPER_DEFAULTVALUE(T6),
			typename TypeWrapper<T7>::CONSTTYPE& t7 = TYPEWRAPPER_DEFAULTVALUE(T7),
			typename TypeWrapper<T8>::CONSTTYPE& t8 = TYPEWRAPPER_DEFAULTVALUE(T8),
			typename TypeWrapper<T9>::CONSTTYPE& t9 = TYPEWRAPPER_DEFAULTVALUE(T9)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9>::ResultType
			(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9>::ResultType
			(t3, typename TypeListType<T4,T5,T6,T7,T8,T9>::ResultType
			(t4, typename TypeListType<T5,T6,T7,T8,T9>::ResultType
			(t5, typename TypeListType<T6,T7,T8,T9>::ResultType
			(t6, typename TypeListType<T7,T8,T9>::ResultType
			(t7, typename TypeListType<T8,T9>::ResultType
			(t8, typename TypeListType<T9>::ResultType
			(t9, NullTypeList()))))))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4,
	class T5,
	class T6,
	class T7,
	class T8>
	struct Tuple<T0, T1,T2,T3,T4,T5,T6,T7,T8, NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4,T5,T6,T7,T8>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5),
			typename TypeWrapper<T6>::CONSTTYPE& t6 = TYPEWRAPPER_DEFAULTVALUE(T6),
			typename TypeWrapper<T7>::CONSTTYPE& t7 = TYPEWRAPPER_DEFAULTVALUE(T7),
			typename TypeWrapper<T8>::CONSTTYPE& t8 = TYPEWRAPPER_DEFAULTVALUE(T8)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8>::ResultType
			(t2, typename TypeListType<T3,T4,T5,T6,T7,T8>::ResultType
			(t3, typename TypeListType<T4,T5,T6,T7,T8>::ResultType
			(t4, typename TypeListType<T5,T6,T7,T8>::ResultType
			(t5, typename TypeListType<T6,T7,T8>::ResultType
			(t6, typename TypeListType<T7,T8>::ResultType
			(t7, typename TypeListType<T8>::ResultType
			(t8, NullTypeList())))))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4,
	class T5,
	class T6,
	class T7>
	struct Tuple<T0, T1,T2,T3,T4,T5,T6,T7, NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4,T5,T6,T7>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5),
			typename TypeWrapper<T6>::CONSTTYPE& t6 = TYPEWRAPPER_DEFAULTVALUE(T6),
			typename TypeWrapper<T7>::CONSTTYPE& t7 = TYPEWRAPPER_DEFAULTVALUE(T7)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5,T6,T7>::ResultType
			(t2, typename TypeListType<T3,T4,T5,T6,T7>::ResultType
			(t3, typename TypeListType<T4,T5,T6,T7>::ResultType
			(t4, typename TypeListType<T5,T6,T7>::ResultType
			(t5, typename TypeListType<T6,T7>::ResultType
			(t6, typename TypeListType<T7>::ResultType
			(t7, NullTypeList()))))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4,
	class T5,
	class T6>
	struct Tuple<T0, T1,T2,T3,T4,T5,T6, NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4,T5,T6>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5),
			typename TypeWrapper<T6>::CONSTTYPE& t6 = TYPEWRAPPER_DEFAULTVALUE(T6)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5,T6>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5,T6>::ResultType
			(t2, typename TypeListType<T3,T4,T5,T6>::ResultType
			(t3, typename TypeListType<T4,T5,T6>::ResultType
			(t4, typename TypeListType<T5,T6>::ResultType
			(t5, typename TypeListType<T6>::ResultType
			(t6, NullTypeList())))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4,
	class T5>
	struct Tuple<T0, T1,T2,T3,T4,T5, NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4,T5>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4),
			typename TypeWrapper<T5>::CONSTTYPE& t5 = TYPEWRAPPER_DEFAULTVALUE(T5)):
		_data(t0, typename TypeListType<T1,T2,T3,T4,T5>::ResultType
			(t1, typename TypeListType<T2,T3,T4,T5>::ResultType
			(t2, typename TypeListType<T3,T4,T5>::ResultType
			(t3, typename TypeListType<T4,T5>::ResultType
			(t4, typename TypeListType<T5>::ResultType
			(t5, NullTypeList()))))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3,
	class T4>
	struct Tuple<T0, T1,T2,T3,T4, NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3,T4>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3),
			typename TypeWrapper<T4>::CONSTTYPE& t4 = TYPEWRAPPER_DEFAULTVALUE(T4)):
		_data(t0, typename TypeListType<T1,T2,T3,T4>::ResultType
			(t1, typename TypeListType<T2,T3,T4>::ResultType
			(t2, typename TypeListType<T3,T4>::ResultType
			(t3, typename TypeListType<T4>::ResultType
			(t4, NullTypeList())))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2,
	class T3>
	struct Tuple<T0, T1,T2,T3, NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2,T3>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2),
			typename TypeWrapper<T3>::CONSTTYPE& t3 = TYPEWRAPPER_DEFAULTVALUE(T3)):
		_data(t0, typename TypeListType<T1,T2,T3>::ResultType
			(t1, typename TypeListType<T2,T3>::ResultType
			(t2, typename TypeListType<T3>::ResultType
			(t3, NullTypeList()))))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1,
	class T2>
	struct Tuple<T0, T1,T2, NullTypeList>
	{
		typedef typename TypeListType<T0,T1,T2>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1),
			typename TypeWrapper<T2>::CONSTTYPE& t2 = TYPEWRAPPER_DEFAULTVALUE(T2)):
		_data(t0, typename TypeListType<T1,T2>::ResultType
			(t1, typename TypeListType<T2>::ResultType
			(t2, NullTypeList())))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0,
	class T1>
	struct Tuple<T0, T1, NullTypeList>
	{
		typedef typename TypeListType<T0,T1>::ResultType Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
			typename TypeWrapper<T1>::CONSTTYPE& t1 = TYPEWRAPPER_DEFAULTVALUE(T1)):
		_data(t0, typename TypeListType<T1>::ResultType(t1, NullTypeList()))
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


	template <class T0>
	struct Tuple<T0, NullTypeList>
	{
		typedef TypeList<T0, NullTypeList> Type;

		enum TupleLengthType
		{
			length = Type::length
		};

		Tuple():_data()
		{
		}

		Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0):
		_data(t0, NullTypeList())
		{
		}

		template <int N>
		typename TypeGetter<N, Type>::ConstHeadType& Get() const
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		typename TypeGetter<N, Type>::HeadType& Get()
		{
			return Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
		}

		template <int N>
		void Set(typename TypeGetter<N, Type>::ConstHeadType& val)
		{
			Getter<N>::template Get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
		}

		bool operator == (const Tuple& other) const
		{
			return _data == other._data;
		}

		bool operator != (const Tuple& other) const
		{
			return !(_data == other._data);
		}

		bool operator < (const Tuple& other) const
		{
			return _data < other._data;
		}

	private:
		Type _data;
	};


} 


#endif
