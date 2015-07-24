/********************************************************************
	created:	2015/07/24
	created:	15:54
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __DYNAMIC_ANY_HOLDER_H__
#define __DYNAMIC_ANY_HOLDER_H__

#include "Types.h"
#include <limits>
#include <typeinfo>
#include "DateTime.h"
#include "TimeStamp.h"
#include "Exception.h"

namespace okey
{
	class DynamicAnyHolderBase
	{
	public:
		
		DynamicAnyHolderBase();
		virtual ~DynamicAnyHolderBase();
		virtual DynamicAnyHolderBase* Clone() const = 0;
		virtual const std::type_info& GetType() const = 0;
		virtual void Convert(int8& val) const = 0;
		virtual void Convert(int16& val) const = 0;
		virtual void Convert(int32& val) const = 0;
		virtual void Convert(int64& val) const = 0;
		virtual void Convert(uint8& val) const = 0;
		virtual void Convert(uint16& val) const = 0;
		virtual void Convert(uint32& val) const = 0;
		virtual void Convert(uint64& val) const = 0;
		virtual void Convert(bool& val) const = 0;
		virtual void Convert(f32& val) const = 0;
		virtual void Convert(f64& val) const = 0;
		virtual void Convert(char& val) const = 0;
		virtual void Convert(std::string& val) const = 0;
		virtual void Convert(DateTime& val) const = 0;
		virtual void Convert(TimeStamp& val) const = 0;

		virtual bool IsArray() const = 0;
		virtual bool IsInteger() const = 0;
		virtual bool IsSigned() const = 0;
		virtual bool IsNumeric() const = 0;
		virtual bool IsString() const = 0;

	protected:
		template <typename F, typename T>
		void convertToSmaller(const F& from, T& to) const
		{
			my_static_assert(std::numeric_limits<F>::is_specialized); //测试目标类型是不是在numeric_limits .模板类中有特殊定义
			my_static_assert(std::numeric_limits<T>::is_specialized);
			my_static_assert(std::numeric_limits<T>::is_signed);
			my_static_assert(std::numeric_limits<F>::is_signed);
			if (std::numeric_limits<F>::is_integer)
			{
				checkUpperLimit(from,to);
				checkLowerLimit(from,to);
			}
			else
			{
				checkUpperLimitFloat(from, to);
				checkLowerLimitFloat(from, to);
			}
			to = static_cast<T>(from);
		}
		template <typename F, typename T>
		void convertToSmallerUnsigned(const F& from, T& to) const
		{
			my_static_assert(std::numeric_limits<F>::is_specialized); 
			my_static_assert(std::numeric_limits<T>::is_specialized);
			my_static_assert(!std::numeric_limits<T>::is_signed);
			my_static_assert(!std::numeric_limits<F>::is_signed);
			checkUpperLimit(from, to);
			to = static_cast<T>(from);
		}

		template<typename F, typename T>
		void convertSignedToUnsigned(const F& from, T& to) const
		{
			my_static_assert(std::numeric_limits<F>::is_specialized); 
			my_static_assert(std::numeric_limits<T>::is_specialized);
			my_static_assert(std::numeric_limits<F>::is_signed);
			my_static_assert(!std::numeric_limits<T>::is_signed);
			if (from < 0 )
			{
				throw RangeException("Value too small.");
			}
			checkUpperLimit(from, to);
			to = static_cast<T>(from);
		}

		template <typename F, typename T>
		void convertSignedFloatToUnsigned(const F& from, T& to) const
		{
			my_static_assert(std::numeric_limits<F>::is_specialized); 
			my_static_assert(std::numeric_limits<T>::is_specialized);
			my_static_assert(!std::numeric_limits<F>::is_integer);
			my_static_assert(std::numeric_limits<T>::is_integer);
			my_static_assert(!std::numeric_limits<T>::is_signed);
			if (from < 0 )
			{
				throw RangeException("Value too small.");
			}
			checkUpperLimit(from, to);
			to = static_cast<T>(from);
		}

		template <typename F, typename T>
		void convertUnsignedToSigned(const F& from, T& to) const
		{
			my_static_assert (std::numeric_limits<F>::is_specialized);
			my_static_assert (std::numeric_limits<T>::is_specialized);
			my_static_assert (!std::numeric_limits<F>::is_signed);
			my_static_assert (std::numeric_limits<T>::is_signed);
			checkUpperLimit(from, to); 
			to = static_cast<T>(from);
		}
	private:
		template<typename F, typename T>
		void checkUpperLimit(const F& from, T&) const
		{
			if (( sizeof(T) < sizeof(F) ) && 
				(from > static_cast<F>(std::numeric_limits<F>::max())))
			{
				throw RangeException("Value too large.");
			}
			else 
			{
				if(static_cast<T>(from) > std::numeric_limits<T>::max())
				{
					throw RangeException("Value too large.");
				}
			}
		}
		template <typename F, typename T>
		void checkUpperLimitFloat(const F& from, T&) const
		{
			if (from > std::numeric_limits<T>::max())
				throw RangeException("Value too large.");
		}

		template <typename F, typename T>
		void checkLowerLimitFloat(const F& from, T&) const
		{
			if (from < -std::numeric_limits<T>::max())
				throw RangeException("Value too small.");
		}

		template <typename F, typename T>
		void checkLowerLimit(const F& from, T&) const
		{
			if (from < std::numeric_limits<T>::min()) 
				throw RangeException("Value too small.");
		}
	};

	template<typename T>
	class DynamicAnyHolder : public DynamicAnyHolderBase
	{
	public:
		DynamicAnyHolder(){}
		~DynamicAnyHolder(){}

		const std::type_info& GetType() const
		{
			return typeid(T);
		}

		bool IsInteger() const
		{
			return std::numeric_limits<T>::is_integer;
		}

		bool IsSigned() const
		{
			return std::numeric_limits<T>::is_signed;
		}

		bool IsNumeric() const
		{
			return std::numeric_limits<T>::is_specialized;
		}

		bool IsString() const
		{
			return type() == typeid(std::string);
		}

		bool IsArray() const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		DynamicAnyHolderBase* Clone() const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(int8& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(int16& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(int32& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(int64& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(uint8& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(uint16& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(uint32& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(uint64& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(bool& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(f32& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(f64& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(char& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(std::string& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(DateTime& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}

		void Convert(TimeStamp& val) const
		{
			throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
		}
	};

	template<>
	DynamicAnyHolder<int8> : public DynamicAnyHolderBase
	{
	public:
	private:
		int8 _val;
	}

}

#endif