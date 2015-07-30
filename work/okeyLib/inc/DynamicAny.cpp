#include "PreCom.h"
#include "DynamicAny.h"

namespace okey
{
	DynamicAny::DynamicAny(): _pHolder(NULL)
	{
	}


	DynamicAny::DynamicAny(const char* pVal):_pHolder(new DynamicAnyHolder<std::string>(pVal))
	{
	}

	DynamicAny::DynamicAny(const DynamicAny& other):_pHolder(NULL)
	{
		if (other._pHolder)
			_pHolder = other._pHolder->Clone();
	}

	DynamicAny::~DynamicAny()
	{
		delete _pHolder;
	}

	DynamicAny& DynamicAny::operator = (const DynamicAny& other)
	{
		DynamicAny tmp(other);
		Swap(tmp);
		return *this;
	}


	const DynamicAny DynamicAny::operator + (const DynamicAny& other) const
	{
		if (IsInteger())
		{
			if(IsSigned())
				return add<int64>(other);
			else
				return add<uint64>(other);
		}
		else if (IsNumeric())
			return add<f64>(other);
		else if (IsString())
			return add<std::string>(other);
		else
			throw InvalidArgumentException("Invalid operation for this data type.");
	}


	DynamicAny& DynamicAny::operator += (const DynamicAny& other)
	{
		if (IsInteger())
		{
			if(IsSigned())
				return *this = add<int64>(other);
			else
				return *this = add<uint64>(other);
		}
		else if (IsNumeric())
			return *this = add<f64>(other);
		else if (IsString())
			return *this = add<std::string>(other);
		else
			throw InvalidArgumentException("Invalid operation for this data type.");
	}


	const DynamicAny DynamicAny::operator - (const DynamicAny& other) const
	{
		if (IsInteger())
		{
			if(IsSigned())
				return sub<int64>(other);
			else
				return sub<uint64>(other);
		}
		else if (IsNumeric())
			return sub<f64>(other);
		else
			throw InvalidArgumentException("Invalid operation for this data type.");
	}


	DynamicAny& DynamicAny::operator -= (const DynamicAny& other)
	{
		if (IsInteger())
		{
			if(IsSigned())
				return *this = sub<int64>(other);
			else
				return *this = sub<uint64>(other);
		}
		else if (IsNumeric())
			return *this = sub<f64>(other);
		else
			throw InvalidArgumentException("Invalid operation for this data type.");
	}


	const DynamicAny DynamicAny::operator * (const DynamicAny& other) const
	{
		if (IsInteger())
		{
			if(IsSigned())
				return mul<int64>(other);
			else
				return mul<uint64>(other);
		}
		else if (IsNumeric())
			return mul<f64>(other);
		else
			throw InvalidArgumentException("Invalid operation for this data type.");
	}


	DynamicAny& DynamicAny::operator *= (const DynamicAny& other)
	{
		if (IsInteger())
		{
			if(IsSigned())
				return *this = mul<int64>(other);
			else
				return *this = mul<uint64>(other);
		}
		else if (IsNumeric())
			return *this = mul<f64>(other);
		else
			throw InvalidArgumentException("Invalid operation for this data type.");
	}


	const DynamicAny DynamicAny::operator / (const DynamicAny& other) const
	{
		if (IsInteger())
		{
			if(IsSigned())
				return div<int64>(other);
			else
				return div<uint64>(other);
		}
		else if (IsNumeric())
			return div<f64>(other);
		else
			throw InvalidArgumentException("Invalid operation for this data type.");
	}


	DynamicAny& DynamicAny::operator /= (const DynamicAny& other)
	{
		if (IsInteger())
		{
			if(IsSigned())
				return *this = div<int64>(other);
			else
				return *this = div<uint64>(other);
		}
		else if (IsNumeric())
			return *this = div<f64>(other);
		else
			throw InvalidArgumentException("Invalid operation for this data type.");
	}


	DynamicAny& DynamicAny::operator ++ ()
	{
		if (!IsInteger())
			throw InvalidArgumentException("Invalid operation for this data type.");
		return *this = *this + 1;
	}

	const DynamicAny DynamicAny::operator ++ (int)
	{
		if (!IsInteger())
			throw InvalidArgumentException("Invalid operation for this data type.");
		DynamicAny tmp(*this);
		*this += 1;
		return tmp;
	}

	DynamicAny& DynamicAny::operator -- ()
	{
		if (!IsInteger())
			throw InvalidArgumentException("Invalid operation for this data type.");

		return *this = *this - 1;
	}

	const DynamicAny DynamicAny::operator -- (int)
	{
		if (!IsInteger())
			throw InvalidArgumentException("Invalid operation for this data type.");
		DynamicAny tmp(*this);
		*this -= 1;
		return tmp;
	}


	bool DynamicAny::operator == (const DynamicAny& other) const
	{
		if (IsEmpty() || other.IsEmpty()) return false;
		return Convert<std::string>() == other.Convert<std::string>();
	}


	bool DynamicAny::operator == (const char* other) const
	{
		if (IsEmpty()) return false;
		return Convert<std::string>() == other;
	}

	bool DynamicAny::operator != (const DynamicAny& other) const
	{
		if (IsEmpty() && other.IsEmpty()) return false;
		else if (IsEmpty() || other.IsEmpty()) return true;

		return Convert<std::string>() != other.Convert<std::string>();
	}


	bool DynamicAny::operator != (const char* other) const
	{
		if (IsEmpty()) return true;
		return Convert<std::string>() != other;
	}


	bool DynamicAny::operator < (const DynamicAny& other) const
	{
		if (IsEmpty() || other.IsEmpty()) return false;
		return Convert<std::string>() < other.Convert<std::string>();
	}


	bool DynamicAny::operator <= (const DynamicAny& other) const
	{
		if (IsEmpty() || other.IsEmpty()) return false;
		return Convert<std::string>() <= other.Convert<std::string>();
	}


	bool DynamicAny::operator > (const DynamicAny& other) const
	{
		if (IsEmpty() || other.IsEmpty()) return false;
		return Convert<std::string>() > other.Convert<std::string>();
	}


	bool DynamicAny::operator >= (const DynamicAny& other) const
	{
		if (IsEmpty() || other.IsEmpty()) return false;
		return Convert<std::string>() >= other.Convert<std::string>();
	}


	bool DynamicAny::operator || (const DynamicAny& other) const
	{
		if (IsEmpty() || other.IsEmpty()) return false;
		return Convert<bool>() || other.Convert<bool>();
	}


	bool DynamicAny::operator && (const DynamicAny& other) const
	{
		if (IsEmpty() || other.IsEmpty()) return false;
		return Convert<bool>() && other.Convert<bool>();
	}


	void DynamicAny::Empty()
	{
		delete _pHolder;
		_pHolder = NULL;
	}
}