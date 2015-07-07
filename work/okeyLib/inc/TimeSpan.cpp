#include "PreCom.h"
#include "TimeSpan.h"


namespace okey
{
	const int64 TimeSpan::MILLISECONDS = 1000; 
	const int64 TimeSpan::SECONDS =  1000 * TimeSpan::MILLISECONDS;     
	const int64 TimeSpan::MINUTES = 60 * TimeSpan::SECONDS;    
	const int64 TimeSpan::HOURS = 60 * TimeSpan::MINUTES;     
	const int64 TimeSpan::DAYS = 24 * TimeSpan::HOURS;  

	TimeSpan::TimeSpan():_span(0){}

	TimeSpan::TimeSpan(int64 microseconds):_span(microseconds){}

	TimeSpan::TimeSpan(int32 seconds, int32 microseconds):_span(int64(seconds)*SECONDS + microseconds){}

	TimeSpan::TimeSpan(int32 days, int32 hours, int32 minutes, int32 seconds, int32 microseconds):
	_span(int64(days)*DAYS + int64(hours)*HOURS + int64(minutes)*MINUTES + int64(seconds)*SECONDS + microseconds)
	{

	}

	TimeSpan::TimeSpan(const TimeSpan& timespan):_span(timespan._span){	}

	TimeSpan::~TimeSpan(){}

	TimeSpan& TimeSpan::operator = (const TimeSpan& timespan)
	{
		_span = timespan._span;
		return *this;
	}

	TimeSpan& TimeSpan::operator = (int64 microseconds)
	{
		_span = microseconds;
		return *this;
	}

	TimeSpan& TimeSpan::Assign(int32 days, int32 hours, int32 minutes, int32 seconds, int32 microseconds)
	{
		_span = int64(days)*DAYS + int64(hours)*HOURS + int64(minutes)*MINUTES + int64(seconds)*SECONDS + microseconds;
		return *this;
	}

	TimeSpan& TimeSpan::Assign(int32 seconds, int32 microseconds)
	{
		_span = int64(seconds)*SECONDS + microseconds;
		return *this;
	}

	void TimeSpan::Swap(TimeSpan& timespan)
	{
		std::swap(_span, timespan._span);
	}

	TimeSpan TimeSpan::operator + (const TimeSpan& d) const
	{
		return TimeSpan(_span + d._span);
	}

	TimeSpan TimeSpan::operator - (const TimeSpan& d) const
	{
		return TimeSpan(_span - d._span);
	}

	TimeSpan& TimeSpan::operator += (const TimeSpan& d)
	{
		_span += d._span;
		return *this;
	}

	TimeSpan& TimeSpan::operator -= (const TimeSpan& d)
	{
		_span -= d._span;
		return *this;
	}

	TimeSpan TimeSpan::operator + (int64 microseconds) const
	{
		return TimeSpan(_span + microseconds);
	}

	TimeSpan TimeSpan::operator - (int64 microseconds) const
	{
		return TimeSpan(_span - microseconds);
	}

	TimeSpan& TimeSpan::operator += (int64 microseconds)
	{
		_span += microseconds;
		return *this;
	}

	TimeSpan& TimeSpan::operator -= (int64 microseconds)
	{
		_span -= microseconds;
		return *this;
	}
}