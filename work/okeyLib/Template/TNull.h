/********************************************************************
	created:	2015/01/21
	created:	19:17
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TEMPLATE_NULL_H__
#define __TEMPLATE_NULL_H__

namespace Template
{
	class NullType {};

	template<typename C>
	class Nullable
	{
	public:
		Nullable():_isNull(true){}
		Nullable(const C& v):_value(_value),_isNull(false){}
		Nullable(const Nullable& n):_value(n._value),_isNull(n._isNull){}
		~Nullable(){}
		void Swap(Nullable& n)
		{
			std::swap(_value, n._value);
			std::swap(_isNull, n._isNull);
		}
		Nullable& operator = (const C& value)
		{
			_value  = value;
			_isNull = false;
			return *this;
		}

		Nullable& operator = (const Nullable& other)
		{
			Nullable tmp(other);
			swap(tmp);
			return *this;
		}

		bool isNull(){return _isNull;}
		const C& GetValue() const
		{
			if (!_isNull)
				return _value;
			else
				throw NullValueException();
		}

		const C& GetValue(const C& deflt) const
		{
			return _isNull ? deflt : _value;
		}

		void Clear()
		{
			_isNull = true;
		}
	private:
		C _value;
		bool _isNull;

	};

	template<typename C>
	inline void Swap(Nullable<C>& n1, Nullable<C>& n2)
	{
		n1.swap(n2);
	}
}

#endif