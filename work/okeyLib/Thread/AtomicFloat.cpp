#include "PreCom.h"
#include "Types.h"
#include "AtomicFloat.h"

namespace okey
{
	float AtomicFloat::SetVal(float NewValue)
	{
		unsigned long iv = 0;
		float ret = 0.0f;

		iv = *(reinterpret_cast< unsigned long* >(&NewValue));
		ret = *(reinterpret_cast< float* >(Value.SetVal(iv)));

		return ret;
	}


	float AtomicFloat::GetVal()
	{
		float val = 0.0f;

		val = *(reinterpret_cast< float* >(Value.GetVal()));

		return val;
	}
	
}