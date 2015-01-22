/********************************************************************
	created:	2015/01/22
	created:	15:41
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TEMPLATE_TUPLE_IMPL_H__
#define __TEMPLATE_TUPLE_IMPL_H__

#include "TTypeList.h"

namespace Template
{

	template <OKEY_TUPLE_TEMPLATE_PARAMS>
#ifdef OKEY_TUPLE_BASE
	struct Tuple
#else
	struct Tuple<OKEY_TUPLE_TEMLPATE,NullTypeList>
#endif
	
	{
		typedef typename TypeListType<OKEY_TUPLE_TEMLPATE>::ResultType Type;
		enum TupleLengthType
		{
			length = Type::length
		};
		Tuple():_data()
		{
		}
		Tuple(OKEY_TUPLE_TEMPLATE_ARGS):_data(OKEY_TUPLE_TEMPLATE_INIT){}
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