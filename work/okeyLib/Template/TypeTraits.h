/********************************************************************
	created:	2015/07/31
	created:	15:31
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TEMPLATE_TYPE_TRAITS_H__
#define __TEMPLATE_TYPE_TRAITS_H__

#include "TVoid.h"
#include "TTypeList.h"

namespace Template
{
	template<typename T>
	struct IsSignedInt
	{
		enum{VALUE = 0};
	};

	template<typename T>
	struct IsUnsignedInt
	{
		enum{VALUE = 0};
	};

	template<typename T>
	struct IsFloat
	{
		enum{VALUE = 0};
	};

	template<typename T>
	struct GetPointer
	{
		typedef T* Result;
	};

	template<typename T>
	struct GetPointer<T&>
	{
		typedef T* Result;
	};

	template<typename T>
	struct GetReference
	{
		typedef T& Result;
	};

	template<typename T>
	struct GetReference<T&>
	{
		typedef T& Result;
	};

	template<>
	struct GetReference<void>
	{
		typedef Void Result;
	};

	template<typename T>
	struct GetParamerterType
	{
		typedef const T& Result;
	};

	template<typename T>
	struct GetParamerterType<T&>
	{
		typedef T& Result;
	};

	template<>
	struct GetParamerterType<void>
	{
		typedef Void Result;
	};

	template<typename T>
	struct IsFunctionPointer
	{
		enum{VALUE=0};
	};

	template<typename T>
	struct IsFunctionPointer<T(*)()>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0>
	struct IsFunctionPointer<T(*)(P0)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1>
	struct IsFunctionPointer<T(*)(P0, P1)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2>
	struct IsFunctionPointer<T(*)(P0, P1, P2)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18, P19)>
	{
		enum{VALUE=1};
	};

	template<typename T>
	struct IsFunctionPointer<T(*)(...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0>
	struct IsFunctionPointer<T(*)(P0,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1>
	struct IsFunctionPointer<T(*)(P0, P1,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2>
	struct IsFunctionPointer<T(*)(P0, P1, P2,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19>
	struct IsFunctionPointer<T(*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18, P19,...)>
	{
		enum{VALUE=1};
	};

	template<typename T>
	struct IsMemberFunctionPointer
	{
		enum{VALUE=0};
	};

	template<typename T, typename S>
	struct IsMemberFunctionPointer<T(S::*)()>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0>
	struct IsMemberFunctionPointer<T(S::*)(P0)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18, P19)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S>
	struct IsMemberFunctionPointer<T(S::*)(...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0>
	struct IsMemberFunctionPointer<T(S::*)(P0,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18, P19,...)>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S>
	struct IsMemberFunctionPointer<T(S::*)()const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0>
	struct IsMemberFunctionPointer<T(S::*)(P0)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18, P19)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S>
	struct IsMemberFunctionPointer<T(S::*)(...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0>
	struct IsMemberFunctionPointer<T(S::*)(P0,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18, P19,...)const>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S>
	struct IsMemberFunctionPointer<T(S::*)()volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0>
	struct IsMemberFunctionPointer<T(S::*)(P0)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18, P19)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S>
	struct IsMemberFunctionPointer<T(S::*)(...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0>
	struct IsMemberFunctionPointer<T(S::*)(P0,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18, P19,...)volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S>
	struct IsMemberFunctionPointer<T(S::*)()const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0>
	struct IsMemberFunctionPointer<T(S::*)(P0)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18, P19)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S>
	struct IsMemberFunctionPointer<T(S::*)(...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0>
	struct IsMemberFunctionPointer<T(S::*)(P0,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18,...)const volatile>
	{
		enum{VALUE=1};
	};

	template<typename T, typename S, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5,
		typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12,
		typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19>
	struct IsMemberFunctionPointer<T(S::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15,
		P16, P17, P18, P19,...)const volatile>
	{
		enum{VALUE=1};
	};


	template<bool flag, typename T, typename U>
	struct TSelect
	{
		typedef T Result;
	};

	template<typename T, typename U>
	struct TSelect<false, T, U>
	{
		typename U Result;
	};

	typedef TypeListType<unsigned char, unsigned short int, unsigned int, unsigned long int, unsigned long long>::ResultType StdUnsignedInts;
	typedef TypeListType<signed char, short, int, long, long long>::ResultType StdSignedInts;
	typedef TypeListType<bool, char>::ResultType StdOtherInts;
	typedef TypeListType<float, double, long double>::ResultType StdFloats;

	template<typename T>
	class TypeTraits
	{
	private:
		template<typename U> struct ReferenceTraits{enum{result=false};typedef U ReferredType;};
		template<typename U> struct ReferenceTraits<U&>{enum{result=true};typedef U ReferredType;};
		template<typename U> struct PointerTaits{enum{result=false};typedef Void PointeeType;};
		template<typename U> struct PointerTaits<U*>{enum{result=true};typedef U PointeeType;};
		template<typename U> struct PointerTaits<U*&>{enum{result=true};typedef U PointeeType;};
		template<typename U> struct PtoMTraits{enum{result=false};};//point to member
		template<typename U, typename V> struct PtoMTraits<U V::*>{enum{result = true};};
		template<typename U, typename V> struct PtoMTraits<U V::*&>{enum{result = true};};
		template<typename U> struct FunctionTraits{enum{result=IsFunctionPointer<U>::VALUE};};
		template<typename U> struct PtoMFunctionTraits{enum{result=IsMemberFunctionPointer<U>::VALUE};};
		template<typename U> struct UnConst{enum{isConst=0};typedef U Result;};
		template<typename U> struct UnConst<const U>{enum{isConst=1};typedef U Result;};
		template<typename U> struct UnConst<const U&>{enum{isConst=1};typedef U& Result;};
		template<typename U> struct UnVolatile{enum{isVolatile=0};typedef U Result;};
		template<typename U> struct UnVolatile<volatile U>{enum{isVolatile=1};typedef U Result;};
		template<typename U> struct UnVolatile<volatile U&>{enum{isVolatile=1};typedef U& Result;};
	public:
		typedef typename UnConst<T>::Result NonConstType; //去const修饰
		typedef typename UnVolatile<T>::Result NonVolatileType;//去volatile修饰
		typedef typename UnVolatile<typename UnConst<T>::Result >::Result UnqualifiedType; //不要任何修饰变量
		typedef typename PointerTaits<UnqualifiedType>::PointeeType PointeeType; //去修饰指针类型
		typedef typename ReferenceTraits<T>::ReferredType ReferredType; //引用类型
		enum{isConst=UnConst<T>::isConst};
		enum{isVolatile=UnVolatile<T>::isVolatile};
		enum{isReference=ReferenceTraits<T>::result};
		enum{isFunction=FunctionTraits<typename GetPointer<T>::Result >::result};
		enum{isFunctionPointer=FunctionTraits<typename ReferenceTraits<UnqualifiedType>::ReferredType >::result};
		enum{isMemberFunctionPointer=PtoMFunctionTraits<typename ReferenceTraits<UnqualifiedType>::ReferredType >::result};
		enum{isMemberPointer=PtoMTraits<typename ReferenceTraits<UnqualifiedType>::ReferredType>::result||isMemberFunctionPointer};
		enum{isPointer=PointerTaits<typename ReferenceTraits<UnqualifiedType>::ReferredType>::result || isFunctionPointer};
		enum{isStdUnsignedInt=TypeLocator<StdUnsignedInts, UnqualifiedType>::value >= 0 || TypeLocator<StdUnsignedInts, typename ReferenceTraits<UnqualifiedType>::ReferredType>::value >= 0 };
		enum{isStdSignedInt=TypeLocator<StdSignedInts, UnqualifiedType>::value >= 0 || TypeLocator<StdSignedInts, typename ReferenceTraits<UnqualifiedType>::ReferredType>::value >= 0 };
		enum{isStdIntergral=isStdSignedInt||isStdUnsignedInt||TypeLocator<StdOtherInts, UnqualifiedType>::value >= 0 || TypeLocator<StdOtherInts, typename ReferenceTraits<UnqualifiedType>::ReferredType>::value >= 0};//整数
		enum{isStdFloat=TypeLocator<StdFloats, UnqualifiedType>::value >= 0 || TypeLocator<StdFloats, typename ReferenceTraits<UnqualifiedType>::ReferredType>::value >= 0};
		enum{isStdArith=isStdIntergral||isStdFloat};

		typedef typename TSelect<isStdArith || isPointer || isMemberPointer, T, typename GetParamerterType<T>::Result>::Result ParameterType;

	};
}

#endif