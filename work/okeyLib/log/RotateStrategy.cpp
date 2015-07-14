#include "PreCom.h"
#include "RotateStrategy.h"
#include "StringHelper.h"

namespace okey
{
	RotateStrategy::RotateStrategy()
	{

	}

	RotateStrategy::~RotateStrategy()
	{

	}
	
	RotateAtTimeStrategy::RotateAtTimeStrategy(const std::string& rtime):
		_day(-1), _hour(-1), _minute(0)
	{
		if (rtime.empty()) 
			throw InvalidArgumentException("Rotation time must be specified.");

		if ((rtime.find(',') != rtime.npos) && (rtime.find(':') == rtime.npos)) 
			throw InvalidArgumentException("Invalid rotation time specified.");

		StringTokenizer timestr(rtime, ",:", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
		int index = 0;

		switch (timestr.count())
		{
		case 3: // day,hh:mm
			{
				_day = StringHelper::ToValue<int32>(timestr[index]);
				_day = _day % 7;
				++index;
			}
		case 2: // hh:mm
			_hour = StringHelper::ToValue<int32>(timestr[index]);
			++index;
		case 1: // mm
			_minute =StringHelper::ToValue<int32>(timestr[index]);
			break;
		default:
			throw InvalidArgumentException("Invalid rotation time specified.");
		}
		getNextRollover();
	}

	RotateAtTimeStrategy::~RotateAtTimeStrategy()
	{

	}
	
	bool RotateAtTimeStrategy::MustRotate(LogFile* pFile)
	{
		if (DateTime() >= _threshold)
		{
			getNextRollover();
			return true;
		}
		return false;
	}

	void RotateAtTimeStrategy::getNextRollover()
	{
		TimeSpan tsp(0, 0, 1, 0, 1000); // 0,00:01:00.001
		do
		{
			_threshold += tsp;
		}
		while (!(_threshold.Minutes() == _minute &&
			(-1 == _hour || _threshold.Hours() == _hour) && 
			(-1 == _day  || _threshold.Days() == _day)));
		// round to :00.0 seconds
		_threshold.assign(_threshold.year(), _threshold.month(), _threshold.day(), _threshold.hour(), _threshold.minute());
	}

	const std::string RotateByIntervalStrategy::ROTATE_TEXT("# Log file created/rotated ");

	RotateByIntervalStrategy::RotateByIntervalStrategy(const TimeSpan& span)
	{

	}

	RotateByIntervalStrategy::~RotateByIntervalStrategy()
	{

	}

	bool RotateByIntervalStrategy::MustRotate(LogFile* pFile)
	{

	}

	RotateBySizeStrategy::RotateBySizeStrategy(uint64 size)
	{

	}

	RotateBySizeStrategy::~RotateBySizeStrategy()
	{

	}

	bool RotateBySizeStrategy::MustRotate(LogFile* pFile)
	{

	}
}