/********************************************************************
	created:	2014/12/30
	created:	14:08
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TIME_STAMP_H__
#define __TIME_STAMP_H__

#include "Types.h"

namespace okey
{

	class TimeStamp
	{
	public:
		TimeStamp();
		TimeStamp(int64 t);
		TimeStamp(const TimeStamp& t);
		~TimeStamp();

		TimeStamp& operator = (const TimeStamp& other);
		TimeStamp& operator = (int64 tv);

		bool operator == (const TimeStamp& ts) const
		{
			return _milliSec == ts._milliSec;
		}
		bool operator != (const TimeStamp& ts) const
		{
			return _milliSec != ts._milliSec;
		}
		bool operator >  (const TimeStamp& ts) const
		{
			return _milliSec > ts._milliSec;
		}
		bool operator >= (const TimeStamp& ts) const
		{
			return _milliSec >= ts._milliSec;
		}
		bool operator <  (const TimeStamp& ts) const
		{
			return _milliSec < ts._milliSec;
		}
		bool operator <= (const TimeStamp& ts) const
		{
			return _milliSec <= ts._milliSec;
		}

		TimeStamp  operator +  (int64 d) const
		{
			return TimeStamp(_milliSec + d);
		}
		TimeStamp  operator -  (int64 d) const
		{
			return TimeStamp(_milliSec - d);
		}
		int64 operator - (const TimeStamp& ts) const
		{
			return _milliSec - ts._milliSec;
		}
		TimeStamp& operator += (int64 d)
		{
			_milliSec += d;
			return *this;
		}
		TimeStamp& operator -= (int64 d)
		{
			_milliSec -= d;
			return *this;
		}
		int64 elapsed() const
		{
			TimeStamp now;
			return now - *this;
		}

		static TimeStamp CurrentTime();

		int64 MilliSecond() const
		{
			return _milliSec;
		}
		uint32 Second() const
		{
			return (uint32)(_milliSec / 1000);
		}
	private:
		int64 _milliSec;
	};

}

#endif