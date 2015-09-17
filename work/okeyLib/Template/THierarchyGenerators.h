/********************************************************************
	created:	2015/08/03
	created:	16:10
	author:		okey
	
	purpose:	·Ö²ãÓÃµÄ¡£¡£
*********************************************************************/
#ifndef __TEMPLATE_HIERARCHY_GENERATORS_H__
#define __TEMPLATE_HIERARCHY_GENERATORS_H__


namespace Template
{
	template<typename , typename>
	struct ScatterHierarchyTag;


	template<typename TL, template<typename> class Unit>
	class GenScatterHierarchy;

	template<typename T1, typename T2, template<typename> class Uint>
	class GenScatterHierarchy<TypeList<T1, T2>, Unit> : public GenScatterHierarchy<ScatterHierarchyTag<T1, T2>, Unit>,
		public GenScatterHierarchy<T2, Unit>
	{
	public:
		typedef TypeList<T1, T2> TList;
		typedef GenScatterHierarchy<ScatterHierarchyTag<T1, T2>, Unit> LeftBase;
		typedef GenScatterHierarchy<T2, Unit> RightBase;
		template <typename T> struct Rebind
		{
			typedef Unit<T> Result;
		};
	};

	template<typename T1, typename T2, template<typename> class Uint>
	class GenScatterHierarchy<TypeList<T1, T2>, Unit> : public GenScatterHierarchy<ScatterHierarchyTag<T1, T2>, Unit>,
		public GenScatterHierarchy<T1, Unit>
	{
	};

	template<typename AtomicType, template<typename> class Unit>
	class GenScatterHierarchy: public Unit<AtomicType>
	{
	public:
		typedef Unit<AtomicType> LeftBase;
		template <typename T> struct Rebind
		{
			typedef Unit<T> Result;
		};
	};

	template<typename T, typename H>
	typename H::template Rebind<T>::ResultCodes& Field(H& obj)
	{
		return obj;
	}

	template<typename T, typename H>
	const typename H::template Rebind<T>::ResultCodes& Field(H& obj)
	{
		return obj;
	}

	template<typename T>
	struct TupleUnit
	{
		T _value;
		operator T&(){return _value;}
		operator const T&() const{return _value;}
	};

	template<typename TL>
	struct TTuple: public GenScatterHierarchy<TL, TupleUnit>
	{
	};

	template<typename H, unsigned int i>
	struct FieldHelper;

	template<typename H>
	struct FieldHelper<H, 0>
	{
		typedef typename H::TList::HeadType ElementType;
		typedef typename H::template Rebind<ElementType>::ResultCodes UnitType;

		enum
		{
			isTuple ,
			isConst = TypeTraits<H>::isConst;
		};

		typedef const typename H::LeftBase ConstLeftBase;
		typedef typename TSelect<isConst, ConstLeftBase, typename H::LeftBase>::Result LeftBase;
		typedef typename TSelect<isTuple, ElementType, UnitType>::Result UnqualifiedResultType;
		typedef typename TSelect<isConst, const UnqualifiedResultType, UnqualifiedResultType>::Result ResultType;
		static ResultType& Do(H& obj)
		{
			LeftBase& leftBase = obj;
			return leftBase;
		}
	};

	template<typename H, unsigned int i>
	struct FieldHelper
	{
		typedef typename TypeGetter<i, typename H::TList> ElementType;
		typedef typename H::template Rebind<ElementType>::ResultCodes UnitType;

		enum
		{
			isTuple ,
			IsConst = TypeTraits<H>::isConst;
		};

		typedef const typename H::RightBase ConstRightBase;
		typedef typename TSelect<isConst, ConstLeftBase, typename H::LeftBase>::Result RightBase;
		typedef typename TSelect<isTuple, ElementType, UnitType>::Result UnqualifiedResultType;
		typedef typename TSelect<isConst, const UnqualifiedResultType, UnqualifiedResultType>::Result ResultType;
		static ResultType& Do(H& obj)
		{
			LeftBase& leftBase = obj;
			return FieldHelper<RightBase , i - 1>::Do(obj);
		}
	};

	template<int i, class H>
	typename FieldHelper<H, i>::ResultType& Field(H& obj)
	{
		return FieldHelper<H, i - 1>::Do(obj);
	}

	template<typename TL, template<typename AtomicType, typename Base> class Unit, typename Root = EmptyType>
	class GenLinerHierarchy;

	template<typename T1, typename T2, template<typename , typename > class Unit, typename Root>
	class GenLinerHierarchy: public Unit< T1, GenLinerHierarchy<T2, Unit, Root> >
	{
	};

	template<typename T, template<typename , typename > class Unit, typename Root>
	class GenLinerHierarchy<TypeList<T, NullType>, Unit, Root >: public Unit< T1, GenLinerHierarchy<T, Root> >
	{
	};

	template<template<typename , typename > class Unit, typename Root>
	class GenLinerHierarchy<NullType, Unit, Root >: public Root
	{
	};
}

#endif