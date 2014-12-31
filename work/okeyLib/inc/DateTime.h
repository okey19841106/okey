/********************************************************************
	created:	2014/12/30
	created:	16:04
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __DATE_TIME_H__
#define __DATE_TIME_H__

#include "TimeStamp.h"
#include <time.h>

namespace okey
{
	class DateTime
	{
	public:
		enum Months
		{
			JANUARY = 1,
			FEBRUARY,
			MARCH,
			APRIL,
			MAY,
			JUNE,
			JULY,
			AUGUST,
			SEPTEMBER,
			OCTOBER,
			NOVEMBER,
			DECEMBER
		};

		enum DaysOfWeek
		{
			SUNDAY = 0,
			MONDAY,
			TUESDAY,
			WEDNESDAY,
			THURSDAY,
			FRIDAY,
			SATURDAY
		};
		DateTime();
		DateTime(const DateTime& d);
		explicit DateTime(const TimeStamp& t);
		DateTime(uint32 year, uint32 month, uint32 day, uint32 hour = 0, uint32 minute = 0, uint32 second = 0, uint32 millisecond = 0);
		~DateTime();
		DateTime& operator = (const DateTime& dateTime)
		{
			if (&dateTime != this)
			{
				_dateTime.tm_year = dateTime._dateTime.tm_year;
				_dateTime.tm_mon = dateTime._dateTime.tm_mon;
				_dateTime.tm_mday = dateTime._dateTime.tm_mday;
				_dateTime.tm_hour = dateTime._dateTime.tm_hour;
				_dateTime.tm_min = dateTime._dateTime.tm_min;
				_dateTime.tm_sec = dateTime._dateTime.tm_sec;
				m_MilliSec = dateTime.m_MilliSec;
			}
			return *this;
		}
		DateTime& operator = (const TimeStamp& timestamp)
		{
			DateTime dt(timestamp);
			return operator=(dt);
		}
		void Update(const TimeStamp& time);
		TimeStamp ToTime();
		uint32 day() const{return _dateTime.tm_mday;}
		void day(const uint32& d){_dateTime.tm_mday = d;}
		uint32 yearday()const{return _dateTime.tm_yday;}
		void yearday(const uint32& d){_dateTime.tm_yday = d;}
		uint32 month()const{return _dateTime.tm_mon + 1;}
		void month(const uint32& m){_dateTime.tm_mon = m - 1;}
		uint32 year()const{return _dateTime.tm_year + 1900;}
		void year(const uint32& y){_dateTime.tm_year = y - 1900;}
		uint32 hour()const{return _dateTime.tm_hour;}
		void hour(const uint32& h){_dateTime.tm_hour = h;}
		uint32 minute()const {return _dateTime.tm_min;}
		void minute(const uint32& m){_dateTime.tm_min = m;}
		uint32 second()const{return _dateTime.tm_sec;}
		void second(const uint32& s){_dateTime.tm_sec = s;}
		uint32 millisecond()const{return m_MilliSec;}
		void millisecond(const uint32& m){m_MilliSec = m;}
		uint32 week()const{return _dateTime.tm_wday;}
		void week(const uint32& w){_dateTime.tm_wday = w;}

		static bool isSameYear(const TimeStamp& t1, const TimeStamp& t2);
		static bool isSameMonth(const TimeStamp& t1, const TimeStamp& t2);
		static bool isSameDay(const TimeStamp& t1, const TimeStamp& t2);
		static bool isSameWeek(const TimeStamp& t1, const TimeStamp& t2);
	private:
		struct tm _dateTime;
		uint32 m_MilliSec;
	};
}

#endif