/********************************************************************
	created:	2015/01/21
	created:	17:36
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TEMPLATE_ANY_H__
#define __TEMPLATE_ANY_H__

#include "Exception.h"
#include <typeinfo>
#include <algorithm>

namespace Template
{
	class AnyType
	{
	public:
		AnyType():_content(NULL)
		{

		}
		template<typename TypeValue>
		AnyType(const TypeValue& v):_content(new Holder<TypeValue>(v))
		{

		}
		~AnyType()
		{
			delete _content;
			_content = NULL;
		}
		AnyType(const AnyType& any):_content(any._content ? any._content->Clone() : NULL)
		{

		}
		AnyType& operator = (const AnyType& any)
		{
			AnyType(any).Swap(*this);
			return *this;
		}
		template<typename TypeValue>
		AnyType& operator= (const TypeValue& any)
		{
			AnyType(any).Swap(*this);
			return *this;
		}
		
		AnyType& Swap(AnyType& any)
		{
			std::swap(_content, any._content);
			return *this;
		}
		const std::type_info& GetType() const
		{
			return _content?_content->GetType():typeid(void);;
		}
		bool IsEmpty() const
		{
			return !_content;
		}
	private:
		class Placeholder
		{
		public:
			virtual ~Placeholder()
			{
			}

			virtual const std::type_info& GetType() const = 0;
			virtual Placeholder* Clone() const = 0;
		};

		template <typename ValueType>
		class Holder: public Placeholder
		{
		public: 
			Holder(const ValueType& value):
			  _held(value)
			  {
			  }
			  virtual const std::type_info& GetType() const
			  {
				  return typeid(ValueType);
			  }

			  virtual Placeholder* Clone() const
			  {
				  return new Holder(_held);
			  }
			  ValueType _held;
		};
	private:
		template <typename ValueType>
		friend ValueType* AnyCast(AnyType*);

		template <typename ValueType>
		friend ValueType* UnsafeAnyCast(AnyType*);
	private:
		Placeholder* _content;
	};


	template <typename ValueType>
	ValueType* AnyCast(AnyType* any)
	{
		return any && any->type() == typeid(ValueType)
			? &static_cast<AnyType::Holder<ValueType>*>(any->_content)->_held
			: NULL;
	}

	template <typename ValueType>
	ValueType* UnsafeAnyCast(AnyType* any)
	{
		 return &static_cast<AnyType::Holder<ValueType>*>(any->_content)->_held;
	}

	template <typename ValueType>
	const ValueType* AnyCast(const AnyType* any)
	{
		 return AnyCast<ValueType>(const_cast<AnyType*>(any));
	}

	template <typename ValueType>
	const ValueType* UnsafeAnyCast(const AnyType* any)
	{
		 return AnyCast<ValueType>(const_cast<AnyType*>(any));
	}

	template <typename ValueType>
	ValueType AnyCast(AnyType& any)
	{
		ValueType* result = AnyCast<ValueType>(&any);
		if (!result) throw BadCastException("Failed to convert between Any types");
		return *result;
	}

	template <typename ValueType>
	ValueType AnyCast(const AnyType& any)
	{
		ValueType* result = AnyCast<ValueType>(const_cast<AnyType*>(&any));
		if (!result) throw BadCastException("Failed to convert between const Any types");
		return *result;
	}


	template <typename ValueType>
	const ValueType& RefAnyCast(const AnyType & any)
	{
		ValueType* result = AnyCast<ValueType>(const_cast<AnyType*>(&any));
		if (!result) throw BadCastException("RefAnyCast: Failed to convert between const Any types");
		return *result;
	}


	template <typename ValueType>
	ValueType& RefAnyCast(AnyType& any)
	{
		ValueType* result = AnyCast<ValueType>(&any);
		if (!result) throw BadCastException("RefAnyCast: Failed to convert between Any types");
		return *result;
	}
}

#endif