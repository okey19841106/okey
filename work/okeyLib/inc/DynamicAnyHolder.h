/********************************************************************
	created:	2015/07/24
	created:	15:54
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __DYNAMIC_ANY_HOLDER_H__
#define __DYNAMIC_ANY_HOLDER_H__

#include "Types.h"
#include <typeinfo>
#include "DateTime.h"
#include "TimeStamp.h"
#include "Exception.h"
#include "StringHelper.h"
#undef min
#undef max
#include <limits>

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
			if ((sizeof(T) < sizeof(F)) &&	
				(from > static_cast<F>(std::numeric_limits<T>::max())))
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
	class DynamicAnyHolder<int8> : public DynamicAnyHolderBase
	{
	public:
		DynamicAnyHolder(int8 val):_val(val){}
		~DynamicAnyHolder(){}
		const std::type_info& GetType() const
		{
			return typeid(int8);
		}

		bool IsInteger() const
		{
			return std::numeric_limits<int8>::is_integer;
		}

		bool IsSigned() const
		{
			return std::numeric_limits<int8>::is_signed;
		}

		bool IsNumeric() const
		{
			return std::numeric_limits<int8>::is_specialized;
		}

		bool IsString() const
		{
			return false;
		}

		bool IsArray() const
		{
			throw false;
		}

		DynamicAnyHolderBase* Clone() const
		{
			return new DynamicAnyHolder<int8>(_val);
		}

		void Convert(int8& val) const
		{
			val = _val;
		}

		void Convert(int16& val) const
		{
			val = _val;
		}

		void Convert(int32& val) const
		{
			val = _val;
		}

		void Convert(int64& val) const
		{
			val = _val;
		}

		void Convert(uint8& val) const
		{
			convertSignedToUnsigned(_val,val);
		}

		void Convert(uint16& val) const
		{
			convertSignedToUnsigned(_val,val);
		}

		void Convert(uint32& val) const
		{
			convertSignedToUnsigned(_val,val);
		}

		void Convert(uint64& val) const
		{
			convertSignedToUnsigned(_val,val);
		}

		void Convert(bool& val) const
		{
			val = (_val != 0);
		}

		void Convert(f32& val) const
		{
			val = static_cast<f32>(_val);
		}

		void Convert(f64& val) const
		{
			val = static_cast<f64>(_val);
		}

		void Convert(char& val) const
		{
			val = static_cast<char>(_val);
		}

		void Convert(std::string& val) const
		{
			val = StringHelper::ToString(_val);
		}

		void Convert(DateTime& val) const
		{
			throw BadCastException("int8 -> DateTime");
		}

		void Convert(TimeStamp& val) const
		{
			throw BadCastException("int8 -> TimeStamp");
		}
		
		const int8& GetValue() {return _val;}
	private:
		int8 _val;
	};

	template<>
	class DynamicAnyHolder<std::string> : public DynamicAnyHolderBase
	{
	public:
		DynamicAnyHolder(const std::string& val):_val(val){}
		DynamicAnyHolder(const char* pVal):_val(pVal){}
		~DynamicAnyHolder(){}
		const std::type_info& GetType() const
		{
			return typeid(std::string);
		}

		bool IsInteger() const
		{
			return false;
		}

		bool IsSigned() const
		{
			return false;
		}

		bool IsNumeric() const
		{
			return false;
		}

		bool IsString() const
		{
			return true;
		}

		bool IsArray() const
		{
			throw false;
		}

		DynamicAnyHolderBase* Clone() const
		{
			return new DynamicAnyHolder(_val);
		}

		void Convert(int8& val) const
		{
			int32 v = StringHelper::ToValue<int32>(_val);
			convertToSmaller(v, val);
		}

		void Convert(int16& val) const
		{
			int32 v = StringHelper::ToValue<int32>(_val);
			convertToSmaller(v, val);
		}

		void Convert(int32& val) const
		{
			val = StringHelper::ToValue<int32>(_val);
		}

		void Convert(int64& val) const
		{
			val = StringHelper::ToValue<int64>(_val);
		}

		void Convert(uint8& val) const
		{
			uint32 v = StringHelper::ToValue<uint32>(_val);
			convertToSmallerUnsigned(v,val);
		}

		void Convert(uint16& val) const
		{
			uint32 v = StringHelper::ToValue<uint32>(_val);
			convertToSmallerUnsigned(v,val);
		}

		void Convert(uint32& val) const
		{
			val = StringHelper::ToValue<uint32>(_val);
		}

		void Convert(uint64& val) const
		{
			val = StringHelper::ToValue<uint64>(_val);
		}

		void Convert(bool& val) const
		{
			static const std::string VAL_FALSE("false");
			static const std::string VAL_INTFALSE("0");

			if (_val == VAL_INTFALSE || (icompare(_val, VAL_FALSE) == 0))
				val = false;
			else
				val = true;
		}

		void Convert(f32& val) const
		{
			f64 v = StringHelper::ToValue<f64>(_val);
			convertToSmaller(v, val);
		}

		void Convert(f64& val) const
		{
			val = StringHelper::ToValue<f64>(_val);
		}

		void Convert(char& val) const
		{
			if (_val.empty())
				val = '\0';
			else
				val = _val[0];
		}

		void Convert(std::string& val) const
		{
			val = _val;
		}

		void Convert(DateTime& val) const
		{
			val.fromString(_val);
		}

		void Convert(TimeStamp& val) const
		{
			DateTime d = DateTime(val);
			d.fromString(_val);
			val = d.ToTime();
		}

		const std::string& GetValue() {return _val;}
	private:
		std::string _val;
	};

	template<>
	class DynamicAnyHolder<int64> : public DynamicAnyHolderBase
	{
	public:
		DynamicAnyHolder(int64 val):_val(val){}
		~DynamicAnyHolder(){}
		const std::type_info& GetType() const
		{
			return typeid(int64);
		}

		bool IsInteger() const
		{
			return std::numeric_limits<int64>::is_integer;
		}

		bool IsSigned() const
		{
			return std::numeric_limits<int64>::is_signed;
		}

		bool IsNumeric() const
		{
			return std::numeric_limits<int64>::is_specialized;
		}

		bool IsString() const
		{
			return false;
		}

		bool IsArray() const
		{
			throw false;
		}

		DynamicAnyHolderBase* Clone() const
		{
			return new DynamicAnyHolder<int64>(_val);
		}

		void Convert(int8& val) const
		{
			convertToSmaller(_val,val);
		}

		void Convert(int16& val) const
		{
			convertToSmaller(_val,val);
		}

		void Convert(int32& val) const
		{
			convertToSmaller(_val,val);
		}

		void Convert(int64& val) const
		{
			val = _val;
		}

		void Convert(uint8& val) const
		{
			convertSignedToUnsigned(_val,val);
		}

		void Convert(uint16& val) const
		{
			convertSignedToUnsigned(_val,val);
		}

		void Convert(uint32& val) const
		{
			convertSignedToUnsigned(_val,val);
		}

		void Convert(uint64& val) const
		{
			convertSignedToUnsigned(_val,val);
		}

		void Convert(bool& val) const
		{
			val = (_val != 0);
		}

		void Convert(f32& val) const
		{
			val = static_cast<f32>(_val);
		}

		void Convert(f64& val) const
		{
			val = static_cast<f64>(_val);
		}

		void Convert(char& val) const
		{
			uint8 tmp;
			Convert(tmp);
			val = static_cast<char>(tmp);
		}

		void Convert(std::string& val) const
		{
			val = StringHelper::ToString(_val);
		}

		void Convert(DateTime& val) const
		{
			TimeStamp n = TimeStamp(_val);
			val.Update(n);
		}

		void Convert(TimeStamp& val) const
		{
			val = TimeStamp(_val);
		}

		const int64& GetValue() {return _val;}
	private:
		int64 _val;
	};

	template<>
	class DynamicAnyHolder<uint64> : public DynamicAnyHolderBase
	{
	public:
		DynamicAnyHolder(uint64 val):_val(val){}
		~DynamicAnyHolder(){}
		const std::type_info& GetType() const
		{
			return typeid(uint64);
		}

		bool IsInteger() const
		{
			return std::numeric_limits<uint64>::is_integer;
		}

		bool IsSigned() const
		{
			return std::numeric_limits<uint64>::is_signed;
		}

		bool IsNumeric() const
		{
			return std::numeric_limits<uint64>::is_specialized;
		}

		bool IsString() const
		{
			return false;
		}

		bool IsArray() const
		{
			throw false;
		}

		DynamicAnyHolderBase* Clone() const
		{
			return new DynamicAnyHolder<uint64>(_val);
		}

		void Convert(int8& val) const
		{
			convertUnsignedToSigned(_val,val);
		}

		void Convert(int16& val) const
		{
			convertUnsignedToSigned(_val,val);
		}

		void Convert(int32& val) const
		{
			convertUnsignedToSigned(_val,val);
		}

		void Convert(int64& val) const
		{
			convertUnsignedToSigned(_val,val);
		}

		void Convert(uint8& val) const
		{
			convertToSmallerUnsigned(_val,val);
		}

		void Convert(uint16& val) const
		{
			convertToSmallerUnsigned(_val,val);
		}

		void Convert(uint32& val) const
		{
			convertToSmallerUnsigned(_val,val);
		}

		void Convert(uint64& val) const
		{
			val = _val;
		}

		void Convert(bool& val) const
		{
			val = (_val != 0);
		}

		void Convert(f32& val) const
		{
			val = static_cast<f32>(_val);
		}

		void Convert(f64& val) const
		{
			val = static_cast<f64>(_val);
		}

		void Convert(char& val) const
		{
			uint8 tmp;
			Convert(tmp);
			val = static_cast<char>(tmp);
		}

		void Convert(std::string& val) const
		{
			val = StringHelper::ToString(_val);
		}

		void Convert(DateTime& val) const
		{
			int64 t;
			convertUnsignedToSigned(_val,t);
			TimeStamp n = TimeStamp(t);
			val.Update(n);
		}

		void Convert(TimeStamp& val) const
		{
			int64 t;
			convertUnsignedToSigned(_val,t);
			val = TimeStamp(t);
		}

		const uint64& GetValue() {return _val;}
	private:
		uint64 _val;
	};

	template<>
	class DynamicAnyHolder<f64> : public DynamicAnyHolderBase
	{
	public:
		DynamicAnyHolder(f64 val):_val(val){}
		~DynamicAnyHolder(){}
		const std::type_info& GetType() const
		{
			return typeid(f64);
		}

		bool IsInteger() const
		{
			return std::numeric_limits<f64>::is_integer;
		}

		bool IsSigned() const
		{
			return std::numeric_limits<f64>::is_signed;
		}

		bool IsNumeric() const
		{
			return std::numeric_limits<f64>::is_specialized;
		}

		bool IsString() const
		{
			return false;
		}

		bool IsArray() const
		{
			throw false;
		}

		DynamicAnyHolderBase* Clone() const
		{
			return new DynamicAnyHolder<f64>(_val);
		}

		void Convert(int8& val) const
		{
			convertToSmaller(_val,val);
		}

		void Convert(int16& val) const
		{
			convertToSmaller(_val,val);
		}

		void Convert(int32& val) const
		{
			convertToSmaller(_val,val);
		}

		void Convert(int64& val) const
		{
			convertToSmaller(_val,val);
		}

		void Convert(uint8& val) const
		{
			convertSignedFloatToUnsigned(_val,val);
		}

		void Convert(uint16& val) const
		{
			convertSignedFloatToUnsigned(_val,val);
		}

		void Convert(uint32& val) const
		{
			convertSignedFloatToUnsigned(_val,val);
		}

		void Convert(uint64& val) const
		{
			convertSignedFloatToUnsigned(_val,val);
		}

		void Convert(bool& val) const
		{
			val = !(_val <= std::numeric_limits<f64>::min() && 
				_val >= -1 * std::numeric_limits<f64>::min());
		}

		void Convert(f32& val) const
		{
			f64 fMin = -1 * std::numeric_limits<f32>::max();
			f64 fMax = std::numeric_limits<f32>::max();

			if (_val < fMin) throw RangeException("Value too small.");
			if (_val > fMax) throw RangeException("Value too large.");

			val = static_cast<f32>(_val);
		}

		void Convert(f64& val) const
		{
			val = _val;
		}

		void Convert(char& val) const
		{
			uint8 tmp;
			Convert(tmp);
			val = static_cast<char>(tmp);
		}

		void Convert(std::string& val) const
		{
			val = StringHelper::ToString(_val);
		}

		void Convert(DateTime& val) const
		{
			throw BadCastException("f64 -> DateTime");
		}

		void Convert(TimeStamp& val) const
		{
			throw BadCastException("f64 -> TimeStamp");
		}

		const f64& GetValue() {return _val;}
	private:
		f64 _val;
	};

	template<>
	class DynamicAnyHolder<int32> : public DynamicAnyHolderBase
	{
	public:
		DynamicAnyHolder(int32 val):_val(val){}
		~DynamicAnyHolder(){}
		const std::type_info& GetType() const
		{
			return typeid(int32);
		}

		bool IsInteger() const
		{
			return std::numeric_limits<int32>::is_integer;
		}

		bool IsSigned() const
		{
			return std::numeric_limits<int32>::is_signed;
		}

		bool IsNumeric() const
		{
			return std::numeric_limits<int32>::is_specialized;
		}

		bool IsString() const
		{
			return false;
		}

		bool IsArray() const
		{
			throw false;
		}

		DynamicAnyHolderBase* Clone() const
		{
			return new DynamicAnyHolder<int32>(_val);
		}

		void Convert(int8& val) const
		{
			convertToSmaller(_val,val);
		}

		void Convert(int16& val) const
		{
			convertToSmaller(_val,val);
		}

		void Convert(int32& val) const
		{
			val = _val;
		}

		void Convert(int64& val) const
		{
			val = _val;
		}

		void Convert(uint8& val) const
		{
			convertSignedToUnsigned(_val,val);
		}

		void Convert(uint16& val) const
		{
			convertSignedToUnsigned(_val,val);
		}

		void Convert(uint32& val) const
		{
			convertSignedToUnsigned(_val,val);
		}

		void Convert(uint64& val) const
		{
			convertSignedToUnsigned(_val,val);
		}

		void Convert(bool& val) const
		{
			val = (_val != 0);
		}

		void Convert(f32& val) const
		{
			val = static_cast<f32>(_val);
		}

		void Convert(f64& val) const
		{
			val = static_cast<f64>(_val);
		}

		void Convert(char& val) const
		{
			uint8 tmp;
			Convert(tmp);
			val = static_cast<char>(tmp);
		}

		void Convert(std::string& val) const
		{
			val = StringHelper::ToString(_val);
		}

		void Convert(DateTime& val) const
		{
			throw BadCastException("int32 -> DateTime");
		}

		void Convert(TimeStamp& val) const
		{
			throw BadCastException("int32 -> TimeStamp");
		}

		const int32& GetValue() {return _val;}
	private:
		int32 _val;
	};

	//后边的等实现时再添加。
}

#endif