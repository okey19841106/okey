/********************************************************************
	created:	2015/07/24
	created:	15:54
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __DYNAMIC_ANY_H__
#define __DYNAMIC_ANY_H__

#include "DynamicAnyHolder.h"

namespace okey
{
	class DynamicAny
	{
	public:
		DynamicAny();
		template<typename T>
		DynamicAny(const T& val):_pHolder(new DynamicAnyHolder<T>(val)){}
		DynamicAny(const char* pVal);
		
		DynamicAny(const DynamicAny& other);
		~DynamicAny();
		inline void Swap(DynamicAny& other)
		{
			std::swap(_pHolder, other._pHolder);
		}
		template<typename T>
		void Convert(T& val) const
		{
			if (!_pHolder)
			{
				return;
			}
			_pHolder->Convert(val);
		}

		template<typename T>
		T Convert() const
		{
			if (!_pHolder)
			{
				throw InvalidAccessException("can not convert empty value");
			}
			T result;
			_pHolder->Convert(result);
			return result;
		}

		template<typename T>
		operator T() const
		{
			if (!_pHolder)
			{
				throw InvalidAccessException("can not convert empty value");
			}
			if (typeid(T) == _pHolder->GetType())
			{
				return Extract<T>();
			}
			else
			{
				T result;
				_pHolder->Convert(result);
				return result;
			}
			
		}

		template<typename T>
		const T& Extract() const
		{
			if (_pHolder && _pHolder->GetType() == typeid(T))
			{
				DynamicAnyHolder<T>* pHolder = static_cast<DynamicAnyHolder<T>*>(_pHolder);
				return pHolder->GetValue();
			}
			else if ()
			{
				throw InvalidAccessException("Can not extract empty value.");
			}
			else
			{
				throw BadCastException("error");
			}
		}

		template<typename T>
		DynamicAny& operator=(const T& other)
		{
			DynamicAny tmp(other);
			Swap(tmp);
			return *this;
		}

		inline bool operator!() const
		{
			return !Convert<bool>();
		}
		DynamicAny& operator=(const DynamicAny& other);
		template<typename T>
		const DynamicAny operator + (const T& other) const
		{
			return Convert<T>() + other;
		}
		const DynamicAny operator + (const DynamicAny& other) const;
		inline const DynamicAny operator + (const char* other) const
		{
			return Convert<std::string>() + other;
		}
		DynamicAny& operator ++();
		const DynamicAny operator ++(int);
		DynamicAny& operator --();
		const DynamicAny operator --(int);
		template<typename T>
		DynamicAny& operator +=(const T& other)
		{
			return *this = Convert<T>() + other;
		}
		DynamicAny& operator += (const DynamicAny& other);
		inline DynamicAny& operator += (const char* other)
		{
			return *this = Convert<std::string>() + other;
		}
		template<typename T>
		const DynamicAny operator -(const T& other) const
		{
			return Convert<T>() - other;
		}
		const DynamicAny operator - (const DynamicAny& other) const;
		template<typename T>
		DynamicAny& operator -= (const T& other)
		{
			return *this = Convert<T>() - other;
		}
		DynamicAny& operator -=(const DynamicAny& other);
		template <typename T> 
		const DynamicAny operator * (const T& other) const
		{
			return Convert<T>() * other;
		}
		const DynamicAny operator * (const DynamicAny& other) const;
		template <typename T> 
		DynamicAny& operator *= (const T& other)
		{
			return *this = Convert<T>() * other;
		}
		DynamicAny& operator *= (const DynamicAny& other);
		template <typename T> 
		const DynamicAny operator / (const T& other) const
		{
			return convert<T>() / other;
		}
		const DynamicAny operator / (const DynamicAny& other) const;
		template <typename T> 
		DynamicAny& operator /= (const T& other)
		{
			return *this = convert<T>() / other;
		}
		DynamicAny& operator /= (const DynamicAny& other);
		template <typename T> 
		bool operator == (const T& other) const
		{
			if (IsEmpty()) return false;
			return Convert<T>() == other;
		}
		bool operator == (const char* other) const;
		bool operator == (const DynamicAny& other) const;
		template <typename T> 
		bool operator != (const T& other) const
		{
			if (IsEmpty()) return true;
			return Convert<T>() != other;
		}
		bool operator != (const DynamicAny& other) const;
		bool operator != (const char* other) const;
		template <typename T> 
		bool operator < (const T& other) const
		{
			if (IsEmpty()) return false;
			return Convert<T>() < other;
		}
		bool operator < (const DynamicAny& other) const;
		template <typename T> 
		bool operator <= (const T& other) const
		{
			if (IsEmpty()) return false;
			return convert<T>() <= other;
		}
		bool operator <= (const DynamicAny& other) const;
		template <typename T> 
		bool operator > (const T& other) const
		{
			if (IsEmpty()) return false;
			return Convert<T>() > other;
		}
		bool operator > (const DynamicAny& other) const;
		template <typename T> 
		bool operator >= (const T& other) const
		{
			if (IsEmpty()) return false;
			return Convert<T>() >= other;
		}
		bool operator >= (const DynamicAny& other) const;
		template <typename T>
		bool operator || (const T& other) const
		{
			if (IsEmpty()) return false;
			return convert<bool>() || other;
		}
		bool operator || (const DynamicAny& other) const;
		template <typename T>
		bool operator && (const T& other) const
		{
			if (IsEmpty()) return false;
			return Convert<bool>() && other;
		}
		bool operator&& (const DynamicAny& other) const;
		bool IsArray() const;
		template<typename T>
		DynamicAny& operator[](T n)
		{
			return holderImpl<std::vector<DynamicAny>,InvalidAccessException>("Not an array.")->operator[](n);
		}
		template<typename T>
		const DynamicAny& operator[](T n) const
		{
			return const_cast<const DynamicAny&>(holderImpl<std::vector<DynamicAny>,InvalidAccessException>("Not an array.")->operator[](n));
		}
		inline const std::type_info& GetType() const
		{
			return _pHolder ? _pHolder->GetType(): typeid(void);
		}
		void Empty();
		inline bool IsEmpty() const
		{
			return _pHolder == NULL;
		}
		inline bool IsInteger() const
		{
			return _pHolder ? _pHolder->IsInteger(): false;
		}
		bool IsSigned() const
		{
			return _pHolder ? _pHolder->IsSigned(): false;
		}
		bool IsNumeric() const
		{
			return _pHolder ? _pHolder->IsNumeric(): false;
		}
		bool IsString() const
		{
			return _pHolder ? _pHolder->IsString(): false;
		}
	private:
		template<typename T>
		T add(const DynamicAny& other) const
		{
			return Convert<T>() + other.Convert<T>();
		}

		template<typename T>
		T sub(const DynamicAny& other) const
		{
			return Convert<T>() - other.Convert<T>();
		}

		template<typename T>
		T mul(const DynamicAny& other) const
		{
			return Convert<T>() * other.Convert<T>();
		}

		template<typename T>
		T div(const DynamicAny& other) const
		{
			return Convert<T>() / other.Convert<T>();
		}

		template<typename T, typename E>
		DynamicAnyHolder<T>* holderImpl(const std::string errorMessage = "") const
		{
			if (_pHolder && _pHolder->GetType() == typeid(T))
			{
				return static_cast<DynamicAnyHolder<T>* >(_pHolder);
			}
			else if (!_pHolder)
			{
				throw InvalidAccessException("Can not access empty value.");
			}
			else
				throw E(errorMessage);
		}

		DynamicAnyHolderBase* _pHolder;
	};

	inline const DynamicAny operator + (const char* other,const DynamicAny& da)
	{
		std::string tmp = other;
		return tmp + da.Convert<std::string>();
	}

	inline char operator + (const char& other, const DynamicAny& da)
	{
		return other + da.Convert<char>();
	}

	inline char operator - (const char& other, const DynamicAny& da)
	{
		return other - da.Convert<char>();
	}


	inline char operator * (const char& other, const DynamicAny& da)
	{
		return other * da.Convert<char>();
	}


	inline char operator / (const char& other, const DynamicAny& da)
	{
		return other / da.Convert<char>();
	}


	inline char operator += (char& other, const DynamicAny& da)
	{
		return other += da.Convert<char>();
	}


	inline char operator -= (char& other, const DynamicAny& da)
	{
		return other -= da.Convert<char>();
	}


	inline char operator *= (char& other, const DynamicAny& da)
	{
		return other *= da.Convert<char>();
	}


	inline char operator /= (char& other, const DynamicAny& da)
	{
		return other /= da.Convert<char>();
	}


	inline bool operator == (const char& other, const DynamicAny& da)
	{
		if (da.IsEmpty()) return false;
		return other == da.Convert<char>();
	}


	inline bool operator != (const char& other, const DynamicAny& da)
	{
		if (da.IsEmpty()) return true;
		return other != da.Convert<char>();
	}


	inline bool operator < (const char& other, const DynamicAny& da)
	{
		if (da.IsEmpty()) return false;
		return other < da.Convert<char>();
	}


	inline bool operator <= (const char& other, const DynamicAny& da)
	{
		if (da.IsEmpty()) return false;
		return other <= da.Convert<char>();
	}


	inline bool operator > (const char& other, const DynamicAny& da)
	{
		if (da.IsEmpty())return false;
		return other > da.Convert<char>();
	}


	inline bool operator >= (const char& other, const DynamicAny& da)
	{
		if (da.IsEmpty())return false;
		return other >= da.Convert<char>();
	}

	//各种类型的待添加。bool, int8 uint8 ........
}

#endif