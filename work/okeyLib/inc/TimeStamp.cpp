#include "PreCom.h"
#include "TimeStamp.h"


namespace okey
{
	TimeStamp::TimeStamp()
	{
		_milliSec = CurrentTime()._milliSec;
	}

	TimeStamp::TimeStamp(int64 t)
	{
		_milliSec = t;
	}

	TimeStamp::TimeStamp(const TimeStamp& t)
	{
		_milliSec = t._milliSec;
	}

	TimeStamp::~TimeStamp()
	{

	}

	TimeStamp TimeStamp::CurrentTime()
	{
#ifdef WINDOWS
		ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
		epoch.LowPart  = 0xD53E8000;
		epoch.HighPart = 0x019DB1DE;
		FILETIME ft;
		GetSystemTimeAsFileTime(&ft);
		ULARGE_INTEGER ts;
		ts.LowPart  = ft.dwLowDateTime;
		ts.HighPart = ft.dwHighDateTime;
		ts.QuadPart -= epoch.QuadPart;
		return (ts.QuadPart/10000);
#else
		struct timeval tv;
		if (gettimeofday(&tv, NULL))
			throw SystemException("cannot get time of day");
		return ((int64)tv.tv_sec)*1000 + ((int64)tv.tv_usec)/1000;
#endif
	}
}