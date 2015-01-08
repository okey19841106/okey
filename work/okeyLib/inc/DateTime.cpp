#include "PreCom.h"
#include "DateTime.h"
#include <sstream>

namespace okey
{
	DateTime::DateTime()
	{
		Update(TimeStamp::CurrentTime());
	}
	DateTime::DateTime(const DateTime& d)
	{
		_dateTime.tm_year = d._dateTime.tm_year;
		_dateTime.tm_mon = d._dateTime.tm_mon;
		_dateTime.tm_mday = d._dateTime.tm_mday;
		_dateTime.tm_hour = d._dateTime.tm_hour;
		_dateTime.tm_min = d._dateTime.tm_min;
		_dateTime.tm_sec = d._dateTime.tm_sec;
		m_MilliSec = d.m_MilliSec;
	}
	DateTime::DateTime(const TimeStamp& t)
	{
		Update(t);
	}

	void DateTime::Update(const TimeStamp& time)
	{
		class TZSetHellper
		{
		public:
			TZSetHellper()
			{
#ifdef WINDOWS
				_tzset();
#else
				tzset();
#endif
			}
		};
		static TZSetHellper helper;
		m_MilliSec = (uint32)(time.MilliSecond() % 1000);
		time_t tv = (time_t)(time.MilliSecond() / 1000);
#ifdef WINDOWS
		localtime_s(&_dateTime,&tv);
#else
		localtime_r(&tv, &_dateTime);
#endif
	}

	DateTime::DateTime(uint32 year, uint32 month, uint32 day, uint32 hour, uint32 minute , uint32 second , uint32 millisecond )
	{
		_dateTime.tm_year = year;
		_dateTime.tm_mon = month;
		_dateTime.tm_mday = day;
		_dateTime.tm_hour = hour;
		_dateTime.tm_min = minute;
		_dateTime.tm_sec = second;
		m_MilliSec = millisecond;
	}
	DateTime::~DateTime()
	{

	}

	TimeStamp DateTime::ToTime()
	{
		time_t tv = ::mktime(&_dateTime);
		return TimeStamp(((int64)tv*1000) + m_MilliSec);
	}

	std::string DateTime::toString(const DateTime& d)
	{
		std::stringstream str;
		str<<d.year()<<"-"<<d.month()<<"-"<<d.day()<<" "<<d.hour()<<":"<<d.minute()<<":"<<d.second()<<":"<<d.millisecond();
		return str.str();
	}

	DateTime DateTime::fromString(const std::string& str)
	{
		int32 year, moth, day, hour, mi, se, ss;
		tsscanf(str.c_str() , "%d-%d-%d %d:%d:%d:%d", &year, &moth, &day, &hour, &mi, &se, &ss);
		DateTime d;
		d.year(year);
		d.month(moth);
		d.day(day);
		d.hour(hour);
		d.minute(mi);
		d.second(se);
		d.millisecond(ss);
		return d;
	}
}