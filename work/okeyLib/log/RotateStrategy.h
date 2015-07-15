/********************************************************************
	created:	2015/07/14
	created:	16:48
	author:		okey
	
	purpose:	Ìæ»»²ßÂÔ
*********************************************************************/
#ifndef __LOG_ROTATE_STRATEGY_H__
#define __LOG_ROTATE_STRATEGY_H__

#include <string>
#include "TimeStamp.h"
#include "TimeSpan.h"
#include "DateTime.h"

namespace okey
{
	class LogFile;

	class RotateStrategy
	{
	public:
		RotateStrategy();
		virtual ~RotateStrategy();
		virtual bool MustRotate(LogFile* pFile) = 0;
	private:
		RotateStrategy(const RotateStrategy&);
		RotateStrategy& operator = (const RotateStrategy&);
	};

	class RotateAtTimeStrategy: public RotateStrategy
	{
	public:
		RotateAtTimeStrategy(const std::string& rtime);
		virtual ~RotateAtTimeStrategy();
		bool MustRotate(LogFile* pFile);
	protected:
		void getNextRollover();
		DateTime  _threshold;
		int _day; //ÖÜ¼¸¡£¡£
		int _hour;
		int _minute;

	};

	class RotateByIntervalStrategy: public RotateStrategy
	{
	public:
		RotateByIntervalStrategy(const TimeSpan& span);
		~RotateByIntervalStrategy();
		bool MustRotate(LogFile* pFile);

	private:
		TimeSpan _span;
		TimeStamp _lastRotate;
		static const std::string ROTATE_TEXT;
	};

	class RotateBySizeStrategy: public RotateStrategy
	{
	public:
		RotateBySizeStrategy(uint64 size);
		~RotateBySizeStrategy();
		bool MustRotate(LogFile* pFile);

	private:
		uint64 _size;
	};
}

#endif