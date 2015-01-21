#include "PreCom.h"
#include "ThreadTarget.h"

namespace okey
{
	ThreadTarget::ThreadTarget(f fun):_f(fun)
	{

	}
	ThreadTarget::ThreadTarget(const ThreadTarget& te):_f(te._f)
	{

	}
	ThreadTarget& ThreadTarget::operator = (const ThreadTarget& te)
	{
		_f  = te._f;
		return *this;
	}

	ThreadTarget::~ThreadTarget()
	{

	}
}