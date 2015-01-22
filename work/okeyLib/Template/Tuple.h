/********************************************************************
	created:	2015/01/22
	created:	15:57
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TEMPLATE_TUPLE_H__
#define __TEMPLATE_TUPLE_H__

namespace Template
{

//20 param.
#define OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1 = NullTypeList,	\
	typename T2 = NullTypeList,	\
	typename T3 = NullTypeList,	\
	typename T4 = NullTypeList,	\
	typename T5 = NullTypeList,	\
	typename T6 = NullTypeList,	\
	typename T7 = NullTypeList,	\
	typename T8 = NullTypeList,	\
	typename T9 = NullTypeList,	\
	typename T10 = NullTypeList,	\
	typename T11 = NullTypeList,	\
	typename T12 = NullTypeList,	\
	typename T13 = NullTypeList,	\
	typename T14 = NullTypeList,	\
	typename T15 = NullTypeList,	\
	typename T16 = NullTypeList,	\
	typename T17 = NullTypeList,	\
	typename T18 = NullTypeList,	\
	typename T19 = NullTypeList
#define OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19
#define OKEY_TUPLE_TEMPLATE_ARGS \
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T6>::CONSTTYPE& t6 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T7>::CONSTTYPE& t7 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T8>::CONSTTYPE& t8 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T9>::CONSTTYPE& t9 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T10>::CONSTTYPE& t10 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T11>::CONSTTYPE& t11 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T12>::CONSTTYPE& t12 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T13>::CONSTTYPE& t13 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T14>::CONSTTYPE& t14 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T15>::CONSTTYPE& t15 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T16>::CONSTTYPE& t16 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T17>::CONSTTYPE& t17 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T18>::CONSTTYPE& t18 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T19>::CONSTTYPE& t19 = typename TypeWrapper<T>::TYPE()
#define OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType	\
	(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType	\
	(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType	\
	(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType	\
	(t6, typename TypeListType<T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType	\
	(t7, typename TypeListType<T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType	\
	(t8, typename TypeListType<T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType	\
	(t9, typename TypeListType<T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType	\
	(t10, typename TypeListType<T11,T12,T13,T14,T15,T16,T17,T18,T19>::ResultType	\
	(t11, typename TypeListType<T12,T13,T14,T15,T16,T17,T18,T19>::ResultType	\
	(t12, typename TypeListType<T13,T14,T15,T16,T17,T18,T19>::ResultType	\
	(t13, typename TypeListType<T14,T15,T16,T17,T18,T19>::ResultType	\
	(t14, typename TypeListType<T15,T16,T17,T18,T19>::ResultType	\
	(t15, typename TypeListType<T16,T17,T18,T19>::ResultType	\
	(t16, typename TypeListType<T17,T18,T19>::ResultType	\
	(t17, typename TypeListType<T18,T19>::ResultType	\
	(t18, typename TypeListType<T19>::ResultType	\
	(t19, NullTypeList())))))))))))))))))))
#define OKEY_TUPLE_BASE
#include "TupleImpl.h"
#undef OKEY_TUPLE_BASE
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	

	//19  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4,	\
	typename T5,	\
	typename T6,	\
	typename T7,	\
	typename T8,	\
	typename T9,	\
	typename T10,	\
	typename T11,	\
	typename T12,	\
	typename T13,	\
	typename T14,	\
	typename T15,	\
	typename T16,	\
	typename T17,	\
	typename T18
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T6>::CONSTTYPE& t6 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T7>::CONSTTYPE& t7 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T8>::CONSTTYPE& t8 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T9>::CONSTTYPE& t9 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T10>::CONSTTYPE& t10 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T11>::CONSTTYPE& t11 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T12>::CONSTTYPE& t12 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T13>::CONSTTYPE& t13 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T14>::CONSTTYPE& t14 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T15>::CONSTTYPE& t15 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T16>::CONSTTYPE& t16 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T17>::CONSTTYPE& t17 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T18>::CONSTTYPE& t18 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType	\
	(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType	\
	(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType	\
	(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType	\
	(t6, typename TypeListType<T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType	\
	(t7, typename TypeListType<T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType	\
	(t8, typename TypeListType<T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType	\
	(t9, typename TypeListType<T10,T11,T12,T13,T14,T15,T16,T17,T18>::ResultType	\
	(t10, typename TypeListType<T11,T12,T13,T14,T15,T16,T17,T18>::ResultType	\
	(t11, typename TypeListType<T12,T13,T14,T15,T16,T17,T18>::ResultType	\
	(t12, typename TypeListType<T13,T14,T15,T16,T17,T18>::ResultType	\
	(t13, typename TypeListType<T14,T15,T16,T17,T18>::ResultType	\
	(t14, typename TypeListType<T15,T16,T17,T18>::ResultType	\
	(t15, typename TypeListType<T16,T17,T18>::ResultType	\
	(t16, typename TypeListType<T17,T18>::ResultType	\
	(t17, typename TypeListType<T18>::ResultType	\
	(t18, NullTypeList()))))))))))))))))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//18  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4,	\
	typename T5,	\
	typename T6,	\
	typename T7,	\
	typename T8,	\
	typename T9,	\
	typename T10,	\
	typename T11,	\
	typename T12,	\
	typename T13,	\
	typename T14,	\
	typename T15,	\
	typename T16,	\
	typename T17
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T6>::CONSTTYPE& t6 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T7>::CONSTTYPE& t7 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T8>::CONSTTYPE& t8 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T9>::CONSTTYPE& t9 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T10>::CONSTTYPE& t10 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T11>::CONSTTYPE& t11 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T12>::CONSTTYPE& t12 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T13>::CONSTTYPE& t13 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T14>::CONSTTYPE& t14 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T15>::CONSTTYPE& t15 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T16>::CONSTTYPE& t16 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T17>::CONSTTYPE& t17 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType	\
	(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType	\
	(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType	\
	(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType	\
	(t6, typename TypeListType<T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType	\
	(t7, typename TypeListType<T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType	\
	(t8, typename TypeListType<T9,T10,T11,T12,T13,T14,T15,T16,T17>::ResultType	\
	(t9, typename TypeListType<T10,T11,T12,T13,T14,T15,T16,T17>::ResultType	\
	(t10, typename TypeListType<T11,T12,T13,T14,T15,T16,T17>::ResultType	\
	(t11, typename TypeListType<T12,T13,T14,T15,T16,T17>::ResultType	\
	(t12, typename TypeListType<T13,T14,T15,T16,T17>::ResultType	\
	(t13, typename TypeListType<T14,T15,T16,T17>::ResultType	\
	(t14, typename TypeListType<T15,T16,T17>::ResultType	\
	(t15, typename TypeListType<T16,T17>::ResultType	\
	(t16, typename TypeListType<T17>::ResultType	\
	(t17, NullTypeList())))))))))))))))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//17  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4,	\
	typename T5,	\
	typename T6,	\
	typename T7,	\
	typename T8,	\
	typename T9,	\
	typename T10,	\
	typename T11,	\
	typename T12,	\
	typename T13,	\
	typename T14,	\
	typename T15,	\
	typename T16
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T6>::CONSTTYPE& t6 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T7>::CONSTTYPE& t7 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T8>::CONSTTYPE& t8 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T9>::CONSTTYPE& t9 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T10>::CONSTTYPE& t10 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T11>::CONSTTYPE& t11 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T12>::CONSTTYPE& t12 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T13>::CONSTTYPE& t13 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T14>::CONSTTYPE& t14 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T15>::CONSTTYPE& t15 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T16>::CONSTTYPE& t16 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType	\
	(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType	\
	(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType	\
	(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType	\
	(t6, typename TypeListType<T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType	\
	(t7, typename TypeListType<T8,T9,T10,T11,T12,T13,T14,T15,T16>::ResultType	\
	(t8, typename TypeListType<T9,T10,T11,T12,T13,T14,T15,T16>::ResultType	\
	(t9, typename TypeListType<T10,T11,T12,T13,T14,T15,T16>::ResultType	\
	(t10, typename TypeListType<T11,T12,T13,T14,T15,T16>::ResultType	\
	(t11, typename TypeListType<T12,T13,T14,T15,T16>::ResultType	\
	(t12, typename TypeListType<T13,T14,T15,T16>::ResultType	\
	(t13, typename TypeListType<T14,T15,T16>::ResultType	\
	(t14, typename TypeListType<T15,T16>::ResultType	\
	(t15, typename TypeListType<T16>::ResultType	\
	(t16, NullTypeList()))))))))))))))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//16  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4,	\
	typename T5,	\
	typename T6,	\
	typename T7,	\
	typename T8,	\
	typename T9,	\
	typename T10,	\
	typename T11,	\
	typename T12,	\
	typename T13,	\
	typename T14,	\
	typename T15
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T6>::CONSTTYPE& t6 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T7>::CONSTTYPE& t7 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T8>::CONSTTYPE& t8 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T9>::CONSTTYPE& t9 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T10>::CONSTTYPE& t10 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T11>::CONSTTYPE& t11 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T12>::CONSTTYPE& t12 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T13>::CONSTTYPE& t13 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T14>::CONSTTYPE& t14 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T15>::CONSTTYPE& t15 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType	\
	(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType	\
	(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType	\
	(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType	\
	(t6, typename TypeListType<T7,T8,T9,T10,T11,T12,T13,T14,T15>::ResultType	\
	(t7, typename TypeListType<T8,T9,T10,T11,T12,T13,T14,T15>::ResultType	\
	(t8, typename TypeListType<T9,T10,T11,T12,T13,T14,T15>::ResultType	\
	(t9, typename TypeListType<T10,T11,T12,T13,T14,T15>::ResultType	\
	(t10, typename TypeListType<T11,T12,T13,T14,T15>::ResultType	\
	(t11, typename TypeListType<T12,T13,T14,T15>::ResultType	\
	(t12, typename TypeListType<T13,T14,T15>::ResultType	\
	(t13, typename TypeListType<T14,T15>::ResultType	\
	(t14, typename TypeListType<T15>::ResultType	\
	(t15, NullTypeList())))))))))))))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//15  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4,	\
	typename T5,	\
	typename T6,	\
	typename T7,	\
	typename T8,	\
	typename T9,	\
	typename T10,	\
	typename T11,	\
	typename T12,	\
	typename T13,	\
	typename T14
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T6>::CONSTTYPE& t6 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T7>::CONSTTYPE& t7 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T8>::CONSTTYPE& t8 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T9>::CONSTTYPE& t9 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T10>::CONSTTYPE& t10 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T11>::CONSTTYPE& t11 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T12>::CONSTTYPE& t12 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T13>::CONSTTYPE& t13 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T14>::CONSTTYPE& t14 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>::ResultType	\
	(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>::ResultType	\
	(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>::ResultType	\
	(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12,T13,T14>::ResultType	\
	(t6, typename TypeListType<T7,T8,T9,T10,T11,T12,T13,T14>::ResultType	\
	(t7, typename TypeListType<T8,T9,T10,T11,T12,T13,T14>::ResultType	\
	(t8, typename TypeListType<T9,T10,T11,T12,T13,T14>::ResultType	\
	(t9, typename TypeListType<T10,T11,T12,T13,T14>::ResultType	\
	(t10, typename TypeListType<T11,T12,T13,T14>::ResultType	\
	(t11, typename TypeListType<T12,T13,T14>::ResultType	\
	(t12, typename TypeListType<T13,T14>::ResultType	\
	(t13, typename TypeListType<T14>::ResultType	\
	(t14, NullTypeList()))))))))))))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//14  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4,	\
	typename T5,	\
	typename T6,	\
	typename T7,	\
	typename T8,	\
	typename T9,	\
	typename T10,	\
	typename T11,	\
	typename T12,	\
	typename T13
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T6>::CONSTTYPE& t6 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T7>::CONSTTYPE& t7 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T8>::CONSTTYPE& t8 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T9>::CONSTTYPE& t9 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T10>::CONSTTYPE& t10 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T11>::CONSTTYPE& t11 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T12>::CONSTTYPE& t12 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T13>::CONSTTYPE& t13 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>::ResultType	\
	(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>::ResultType	\
	(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12,T13>::ResultType	\
	(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12,T13>::ResultType	\
	(t6, typename TypeListType<T7,T8,T9,T10,T11,T12,T13>::ResultType	\
	(t7, typename TypeListType<T8,T9,T10,T11,T12,T13>::ResultType	\
	(t8, typename TypeListType<T9,T10,T11,T12,T13>::ResultType	\
	(t9, typename TypeListType<T10,T11,T12,T13>::ResultType	\
	(t10, typename TypeListType<T11,T12,T13>::ResultType	\
	(t11, typename TypeListType<T12,T13>::ResultType	\
	(t12, typename TypeListType<T13>::ResultType	\
	(t13, NullTypeList())))))))))))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//13  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4,	\
	typename T5,	\
	typename T6,	\
	typename T7,	\
	typename T8,	\
	typename T9,	\
	typename T10,	\
	typename T11,	\
	typename T12
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T6>::CONSTTYPE& t6 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T7>::CONSTTYPE& t7 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T8>::CONSTTYPE& t8 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T9>::CONSTTYPE& t9 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T10>::CONSTTYPE& t10 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T11>::CONSTTYPE& t11 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T12>::CONSTTYPE& t12 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>::ResultType	\
	(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11,T12>::ResultType	\
	(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11,T12>::ResultType	\
	(t5, typename TypeListType<T6,T7,T8,T9,T10,T11,T12>::ResultType	\
	(t6, typename TypeListType<T7,T8,T9,T10,T11,T12>::ResultType	\
	(t7, typename TypeListType<T8,T9,T10,T11,T12>::ResultType	\
	(t8, typename TypeListType<T9,T10,T11,T12>::ResultType	\
	(t9, typename TypeListType<T10,T11,T12>::ResultType	\
	(t10, typename TypeListType<T11,T12>::ResultType	\
	(t11, typename TypeListType<T12>::ResultType	\
	(t12, NullTypeList()))))))))))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//12  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4,	\
	typename T5,	\
	typename T6,	\
	typename T7,	\
	typename T8,	\
	typename T9,	\
	typename T10,	\
	typename T11
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T6>::CONSTTYPE& t6 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T7>::CONSTTYPE& t7 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T8>::CONSTTYPE& t8 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T9>::CONSTTYPE& t9 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T10>::CONSTTYPE& t10 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T11>::CONSTTYPE& t11 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10,T11>::ResultType	\
	(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10,T11>::ResultType	\
	(t4, typename TypeListType<T5,T6,T7,T8,T9,T10,T11>::ResultType	\
	(t5, typename TypeListType<T6,T7,T8,T9,T10,T11>::ResultType	\
	(t6, typename TypeListType<T7,T8,T9,T10,T11>::ResultType	\
	(t7, typename TypeListType<T8,T9,T10,T11>::ResultType	\
	(t8, typename TypeListType<T9,T10,T11>::ResultType	\
	(t9, typename TypeListType<T10,T11>::ResultType	\
	(t10, typename TypeListType<T11>::ResultType	\
	(t11, NullTypeList())))))))))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//11  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4,	\
	typename T5,	\
	typename T6,	\
	typename T7,	\
	typename T8,	\
	typename T9,	\
	typename T10
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T6>::CONSTTYPE& t6 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T7>::CONSTTYPE& t7 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T8>::CONSTTYPE& t8 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T9>::CONSTTYPE& t9 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T10>::CONSTTYPE& t10 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9,T10>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9,T10>::ResultType	\
	(t3, typename TypeListType<T4,T5,T6,T7,T8,T9,T10>::ResultType	\
	(t4, typename TypeListType<T5,T6,T7,T8,T9,T10>::ResultType	\
	(t5, typename TypeListType<T6,T7,T8,T9,T10>::ResultType	\
	(t6, typename TypeListType<T7,T8,T9,T10>::ResultType	\
	(t7, typename TypeListType<T8,T9,T10>::ResultType	\
	(t8, typename TypeListType<T9,T10>::ResultType	\
	(t9, typename TypeListType<T10>::ResultType	\
	(t10, NullTypeList()))))))))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//10  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4,	\
	typename T5,	\
	typename T6,	\
	typename T7,	\
	typename T8,	\
	typename T9
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5,T6,T7,T8,T9
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T6>::CONSTTYPE& t6 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T7>::CONSTTYPE& t7 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T8>::CONSTTYPE& t8 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T9>::CONSTTYPE& t9 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8,T9>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8,T9>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5,T6,T7,T8,T9>::ResultType	\
	(t3, typename TypeListType<T4,T5,T6,T7,T8,T9>::ResultType	\
	(t4, typename TypeListType<T5,T6,T7,T8,T9>::ResultType	\
	(t5, typename TypeListType<T6,T7,T8,T9>::ResultType	\
	(t6, typename TypeListType<T7,T8,T9>::ResultType	\
	(t7, typename TypeListType<T8,T9>::ResultType	\
	(t8, typename TypeListType<T9>::ResultType	\
	(t9, NullTypeList())))))))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//9  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4,	\
	typename T5,	\
	typename T6,	\
	typename T7,	\
	typename T8
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5,T6,T7,T8
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T6>::CONSTTYPE& t6 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T7>::CONSTTYPE& t7 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T8>::CONSTTYPE& t8 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7,T8>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5,T6,T7,T8>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5,T6,T7,T8>::ResultType	\
	(t3, typename TypeListType<T4,T5,T6,T7,T8>::ResultType	\
	(t4, typename TypeListType<T5,T6,T7,T8>::ResultType	\
	(t5, typename TypeListType<T6,T7,T8>::ResultType	\
	(t6, typename TypeListType<T7,T8>::ResultType	\
	(t7, typename TypeListType<T8>::ResultType	\
	(t8, NullTypeList()))))))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//8  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4,	\
	typename T5,	\
	typename T6,	\
	typename T7
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5,T6,T7
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T6>::CONSTTYPE& t6 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T7>::CONSTTYPE& t7 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5,T6,T7>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5,T6,T7>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5,T6,T7>::ResultType	\
	(t3, typename TypeListType<T4,T5,T6,T7>::ResultType	\
	(t4, typename TypeListType<T5,T6,T7>::ResultType	\
	(t5, typename TypeListType<T6,T7>::ResultType	\
	(t6, typename TypeListType<T7>::ResultType	\
	(t7, NullTypeList())))))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//7  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4,	\
	typename T5,	\
	typename T6
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5,T6
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T6>::CONSTTYPE& t6 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5,T6>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5,T6>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5,T6>::ResultType	\
	(t3, typename TypeListType<T4,T5,T6>::ResultType	\
	(t4, typename TypeListType<T5,T6>::ResultType	\
	(t5, typename TypeListType<T6>::ResultType	\
	(t6, NullTypeList()))))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//6  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4,	\
	typename T5
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4,T5
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T5>::CONSTTYPE& t5 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4,T5>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4,T5>::ResultType	\
	(t2, typename TypeListType<T3,T4,T5>::ResultType	\
	(t3, typename TypeListType<T4,T5>::ResultType	\
	(t4, typename TypeListType<T5>::ResultType	\
	(t5, NullTypeList())))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//5  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3,	\
	typename T4
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3,T4
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T4>::CONSTTYPE& t4 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3,T4>::ResultType	\
	(t1, typename TypeListType<T2,T3,T4>::ResultType	\
	(t2, typename TypeListType<T3,T4>::ResultType	\
	(t3, typename TypeListType<T4>::ResultType	\
	(t4, NullTypeList()))))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//4  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2,	\
	typename T3
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2,T3
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T3>::CONSTTYPE& t3 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2,T3>::ResultType	\
	(t1, typename TypeListType<T2,T3>::ResultType	\
	(t2, typename TypeListType<T3>::ResultType	\
	(t3, NullTypeList())))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//3  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1,	\
	typename T2
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1,T2
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T2>::CONSTTYPE& t2 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1,T2>::ResultType	\
	(t1, typename TypeListType<T2>::ResultType	\
	(t2, NullTypeList()))
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//2  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0,	\
	typename T1
#define	OKEY_TUPLE_TEMLPATE	\
	T0,T1
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE(),\
	typename TypeWrapper<T1>::CONSTTYPE& t1 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	(t0, typename TypeListType<T1>::ResultType	\
	(t1, NullTypeList())
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT

	//1  param
#define	OKEY_TUPLE_TEMPLATE_PARAMS	\
	typename T0
#define	OKEY_TUPLE_TEMLPATE	\
	T0
#define	OKEY_TUPLE_TEMPLATE_ARGS	\
	typename TypeWrapper<T0>::CONSTTYPE& t0 = typename TypeWrapper<T>::TYPE()
#define	OKEY_TUPLE_TEMPLATE_INIT	\
	t0, NullTypeList()
#include "TupleImpl.h"
#undef  OKEY_TUPLE_TEMPLATE_PARAMS
#undef OKEY_TUPLE_TEMLPATE
#undef OKEY_TUPLE_TEMPLATE_ARGS
#undef OKEY_TUPLE_TEMPLATE_INIT



}

#endif