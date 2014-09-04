
#include "PreCom.h"
#include "Types.h"
#include "AtomicCounter.h"

namespace okey
{
	

	uint32 AtomicCounter::operator++()
	{
		uint32 val = 0;

#ifdef WINDOWS
		val = InterlockedIncrement(reinterpret_cast< volatile LONG* >(&Value));
#else
#ifdef __GNUC__
		val = __sync_add_and_fetch(&Value, 1);
#else
#error Your platform (architecture and compiler) is NOT supported. Arcemu requires little endian architecture, and at least GCC 4.1
#endif
#endif

		return val;
	}

	uint32 AtomicCounter::operator--()
	{
		unsigned long val = 0;

#ifdef WINDOWS
		val = InterlockedDecrement(reinterpret_cast< volatile LONG* >(&Value));
#else
#ifdef __GNUC__
		val = __sync_add_and_fetch(&Value, -1);
#else
#error Your platform (architecture and compiler) is NOT supported. Arcemu requires little endian architecture, and at least GCC 4.1
#endif
#endif
		return val;
	}

	
}