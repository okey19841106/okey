/********************************************************************
	created:	2015/07/07
	created:	11:24
	author:		okey
	
	purpose:    Ê±¼ä¿ç¶È	
*********************************************************************/
#ifndef __OKEY_TIME_SPAN_H__
#define __OKEY_TIME_SPAN_H__

#include "Types.h"

namespace okey
{

	class TimeSpan
	{
	public:
		TimeSpan();
		explicit TimeSpan(int64 microseconds);
		TimeSpan(int32 seconds, int32 microseconds);
		TimeSpan(int32 days, int32 hours, int32 minutes, int32 seconds, int32 microseconds);
		TimeSpan(const TimeSpan& timespan);
		~TimeSpan();

		TimeSpan& operator = (const TimeSpan& timespan);
		TimeSpan& operator = (int64 microseconds);
		TimeSpan& Assign(int32 days, int32 hours, int32 minutes, int32 seconds, int32 microseconds);
		TimeSpan& Assign(int32 seconds, int32 microseconds);
		void Swap(TimeSpan& timespan);

		inline bool operator == (const TimeSpan& ts) const{ return _span == ts._span;}
		inline bool operator != (const TimeSpan& ts) const{ return _span != ts._span;}
		inline bool operator >  (const TimeSpan& ts) const{return _span > ts._span;}
		inline bool operator >= (const TimeSpan& ts) const{return _span >= ts._span;}
		inline bool operator <  (const TimeSpan& ts) const{return _span < ts._span;}
		inline bool operator <= (const TimeSpan& ts) const{return _span <= ts._span;}

		inline bool operator == (int64 microseconds) const{return _span == microseconds;}
		inline bool operator != (int64 microseconds) const{return _span != microseconds;}
		inline bool operator >  (int64 microseconds) const{return _span > microseconds;}
		inline bool operator >= (int64 microseconds) const{return _span >= microseconds;}
		inline bool operator <  (int64 microseconds) const{return _span < microseconds;}
		inline bool operator <= (int64 microseconds) const{return _span <= microseconds;}

		TimeSpan operator + (const TimeSpan& d) const;
		TimeSpan operator - (const TimeSpan& d) const;
		TimeSpan& operator += (const TimeSpan& d);
		TimeSpan& operator -= (const TimeSpan& d);

		TimeSpan operator + (int64 microseconds) const;
		TimeSpan operator - (int64 microseconds) const;
		TimeSpan& operator += (int64 microseconds);
		TimeSpan& operator -= (int64 microseconds);
		
		inline int32 Days() const{return int32(_span/DAYS);}
		/// Returns the number of days.
		inline int32 Hours() const{ return int32((_span/HOURS) % 24);}
		/// Returns the number of hours (0 to 23).
		inline int32 TotalHours() const{return int32(_span/HOURS);}
		/// Returns the total number of hours.
		inline int32 Minutes() const{ return int32((_span/MINUTES)%60);}
		/// Returns the number of minutes (0 to 59).
		inline int32 TotalMinutes() const{return int32(_span/MINUTES);}
		/// Returns the total number of minutes.
		inline int32 Seconds() const{return int32((_span/SECONDS)%60);}
		/// Returns the number of seconds (0 to 59).
		inline int32 TotalSeconds() const{return int32(_span/SECONDS);}
		/// Returns the total number of seconds.
		inline int32 Milliseconds() const{return int32((_span/MILLISECONDS)%1000);}
		/// Returns the number of milliseconds (0 to 999).
		inline int64 TotalMilliseconds() const{return _span/MILLISECONDS;}
		/// Returns the total number of milliseconds.
		inline int32 Microseconds() const{ return int32(_span % 1000);;}
		/// Returns the fractions of a millisecond in microseconds (0 to 999).
		inline int32 Useconds() const{return int32(_span % 1000000);}
		/// Returns the fractions of a second in microseconds (0 to 999999).
		inline int64 totalMicroseconds() const{return _span;}

		static const int64 MILLISECONDS; /// The number of microseconds in a millisecond.
		static const int64 SECONDS;      /// The number of microseconds in a second.
		static const int64 MINUTES;      /// The number of microseconds in a minute.
		static const int64 HOURS;        /// The number of microseconds in a hour.
		static const int64 DAYS;         /// The number of microseconds in a day.

	private:
		int64 _span;
	};

	inline void Swap(TimeSpan& s1, TimeSpan& s2)
	{
		s1.Swap(s2);
	}
}

#endif
