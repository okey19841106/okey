#include "PreCom.h"
#include "RotateStrategy.h"
#include "StringHelper.h"
#include "LogFile.h"

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
		if (DateTime().ToTime() >= _threshold.ToTime())
		{
			getNextRollover();
			return true;
		}
		return false;
	}

	void RotateAtTimeStrategy::getNextRollover()
	{
		uint32 nMinute = _threshold.minute();
		do
		{
			//_threshold.minute((nMinute++)% 60);
			_threshold = (_threshold.ToTime() + 60000);
		}
		while (!(_threshold.minute() == _minute &&
			(-1 == _hour || _threshold.hour() == _hour) && 
			(-1 == _day  || _threshold.week() == _day)));
		// round to :00.0 seconds
		_threshold = DateTime(_threshold.year(), _threshold.month(), _threshold.day(), _threshold.hour(), _threshold.minute());
		//_threshold.assign(_threshold.year(), _threshold.month(), _threshold.day(), _threshold.hour(), _threshold.minute());
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
		if (_lastRotate == 0 || pFile->GetSize() == 0)
		{
			if (pFile->GetSize() != 0)
			{
				_lastRotate = pFile->CreationDate();
			}
			else
			{
				_lastRotate = TimeStamp::CurrentTime();
			}
		}
		TimeStamp now;
		return _span <= now - _lastRotate;
	}

	RotateBySizeStrategy::RotateBySizeStrategy(uint64 size):_size(size)
	{

	}

	RotateBySizeStrategy::~RotateBySizeStrategy()
	{

	}

	bool RotateBySizeStrategy::MustRotate(LogFile* pFile)
	{
		return pFile->GetSize() >= _size;
	}
}