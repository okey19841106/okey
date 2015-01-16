
#include "PreCom.h"
#include "Types.h"
#include "AtomicCounter.h"

namespace okey
{
	AtomicCounter::AtomicCounter()
	{
		SetValue(1);
	}

	AtomicCounter::AtomicCounter(int32 InitialValue)
	{
		SetValue(InitialValue);
	}

	AtomicCounter::AtomicCounter(const AtomicCounter & other)
	{
		SetValue(other._value);
	}

	AtomicCounter& AtomicCounter::operator=(const AtomicCounter & other)
	{
		SetValue(other._value);
		return *this;
	}

	AtomicCounter& AtomicCounter::operator=(int32 value)
	{
		SetValue(value);
		return *this;
	}

	int32  AtomicCounter::operator++(int32)
	{
#ifdef WINDOWS
		int32 result = InterlockedDecrement(reinterpret_cast< volatile long* >(&_value));
		return ++result;
#else
		return (int32)__sync_fetch_and_add(&_value, -1);
#endif
	}

	int32  AtomicCounter::operator--(int32)
	{
#ifdef WINDOWS
		int32 result = InterlockedIncrement(reinterpret_cast< volatile long* >(&_value));
		return --result;
#else
		return (int32)__sync_fetch_and_add(&_value, 1);
#endif
	}

	
	AtomicCounter::operator int32() const
	{
		return _value;
	}
	bool  AtomicCounter::operator !() const
	{
		return _value == 0;
	}

	void AtomicCounter::SetValue(int32 v)
	{
#ifdef WINDOWS
		InterlockedExchange(reinterpret_cast< volatile LONG* >(&_value), long(v));
#else
#ifdef __GNUC__
		ret = __sync_val_compare_and_swap(&_value, _value, v);
#else
#error Your platform (architecture and compiler) is NOT supported. Arcemu requires little endian architecture, and at least GCC 4.1
#endif
#endif
	}

	int32 AtomicCounter::operator++()
	{
#ifdef WINDOWS
		return (int32)InterlockedIncrement(reinterpret_cast< volatile long* >(&_value));
#else
#ifdef __GNUC__
		return (int32)__sync_add_and_fetch(&_value, 1);
#else
#error Your platform (architecture and compiler) is NOT supported. Arcemu requires little endian architecture, and at least GCC 4.1
#endif
#endif
	}

	int32 AtomicCounter::operator--()
	{
#ifdef WINDOWS
		return (int32)InterlockedDecrement(reinterpret_cast< volatile long* >(&_value));
#else
#ifdef __GNUC__
		return (int32)__sync_add_and_fetch(&_value, -1);
#else
#error Your platform (architecture and compiler) is NOT supported. Arcemu requires little endian architecture, and at least GCC 4.1
#endif
#endif
	}

	
}