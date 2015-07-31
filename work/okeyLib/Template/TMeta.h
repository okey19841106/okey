/********************************************************************
	created:	2015/01/22
	created:	11:23
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TEMPLATE_META_H__
#define __TEMPLATE_META_H__

#include "TVoid.h"
#include "TTypeList.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4180)
#endif

namespace Template
{
	template <typename T>
	struct IsReference
	{
		enum {VALUE = 0};
	};
	template <typename T>
	struct IsReference<T&>
	{
		enum {VALUE = 1};
	};
	template <typename T>
	struct IsReference<const T&>
	{
		enum {VALUE = 1};
	};
	template <typename T>
	struct IsConst
	{
		enum {VALUE = 0};
	};
	template <typename T>
	struct IsConst<const T&>
	{
		enum {VALUE = 1};
	};
	template <typename T>
	struct IsConst<const T>
	{
		enum {VALUE = 1};
	};

	template <typename T>
	struct TypeWrapper
	{
		typedef T TYPE;
		typedef const T CONSTTYPE;
		typedef T& REFTYPE;
		typedef const T& CONSTREFTYPE;
	};

	template <typename T>
	struct TypeWrapper<T&>
	{
		typedef T TYPE;
		typedef const T CONSTTYPE;
		typedef T& REFTYPE;
		typedef const T& CONSTREFTYPE;
	};

	template <typename T>
	struct TypeWrapper<const T>
	{
		typedef T TYPE;
		typedef const T CONSTTYPE;
		typedef T& REFTYPE;
		typedef const T& CONSTREFTYPE;
	};

	template <typename T>
	struct TypeWrapper<const T&>
	{
		typedef T TYPE;
		typedef const T CONSTTYPE;
		typedef T& REFTYPE;
		typedef const T& CONSTREFTYPE;
	};
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif