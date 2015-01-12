#include "PreCom.h"
#include "Types.h"
#include "AtomicBoolean.h"

namespace okey
{

	bool AtomicBoolean::SetVal(bool val)
	{
		unsigned long oldval = 0;

		if(val)
			oldval = Value.SetVal(1);
		else
			oldval = Value.SetVal(0);

		return (oldval & 1);
	}
}