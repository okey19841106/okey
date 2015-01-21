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
	class Any
	{
	public:
		Any():_content(NULL)
		{

		}
		template<typename TypeValue>
		Any(const TypeValue& v):_content(new Holder<TypeValue>(v))
		{

		}
		~Any()
		{
			delete _content;
			_content = NULL;
		}
		Any(const Any& any):_content(any._content ? any._content->Clone() : NULL)
		{

		}
		Any& operator = (const Any& any)
		{
			Any(any).Swap(*this);
			return *this;
		}
		template<typename TypeValue>
		Any& operator= (const TypeValue& any)
		{
			Any(any).Swap(*this);
			return *this;
		}
		
		Any& Swap(Any& any)
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
		friend ValueType* AnyCast(Any*);

		template <typename ValueType>
		friend ValueType* UnsafeAnyCast(Any*);
	private:
		Placeholder* _content;
	};


	template <typename ValueType>
	ValueType* AnyCast(Any* any)
	{
		return any && any->type() == typeid(ValueType)
			? &static_cast<Any::Holder<ValueType>*>(any->_content)->_held
			: NULL;
	}

	template <typename ValueType>
	ValueType* UnsafeAnyCast(Any* any)
	{
		 return &static_cast<Any::Holder<ValueType>*>(any->_content)->_held;
	}

	template <typename ValueType>
	const ValueType* AnyCast(const Any* any)
	{
		 return AnyCast<ValueType>(const_cast<Any*>(any));
	}

	template <typename ValueType>
	const ValueType* UnsafeAnyCast(const Any* any)
	{
		 return AnyCast<ValueType>(const_cast<Any*>(any));
	}

	template <typename ValueType>
	ValueType AnyCast(Any& any)
	{
		ValueType* result = AnyCast<ValueType>(&any);
		if (!result) throw BadCastException("Failed to convert between Any types");
		return *result;
	}

	template <typename ValueType>
	ValueType AnyCast(const Any& any)
	{
		ValueType* result = AnyCast<ValueType>(const_cast<Any*>(&any));
		if (!result) throw BadCastException("Failed to convert between const Any types");
		return *result;
	}


	template <typename ValueType>
	const ValueType& RefAnyCast(const Any & any)
	{
		ValueType* result = AnyCast<ValueType>(const_cast<Any*>(&any));
		if (!result) throw BadCastException("RefAnyCast: Failed to convert between const Any types");
		return *result;
	}


	template <typename ValueType>
	ValueType& RefAnyCast(Any& any)
	{
		ValueType* result = AnyCast<ValueType>(&any);
		if (!result) throw BadCastException("RefAnyCast: Failed to convert between Any types");
		return *result;
	}
}

#endif