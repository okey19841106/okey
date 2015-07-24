/********************************************************************
	created:	2015/07/14
	created:	15:09
	author:		okey
	
	purpose:	
*********************************************************************/
#include "PreCom.h"
#include "ConsoleChannel.h"
#include "StringHelper.h"

namespace okey
{
	FastMutex ConsoleChannel::_mutex;

	ConsoleChannel::ConsoleChannel():_str(std::clog)
	{

	}

	ConsoleChannel::ConsoleChannel(std::ostream& str):_str(str)
	{

	}

	void ConsoleChannel::logInstance(int32 pro, const char* msg)
	{
		FastMutex::ScopedLock lock(_mutex);
		_str<< msg << std::endl;
	}

	ConsoleChannel::~ConsoleChannel()
	{

	}


	FastMutex ColorConsoleChannel::_mutex;
	const std::string ColorConsoleChannel::CSI("\033[");

	ColorConsoleChannel::ColorConsoleChannel():
		_str(std::clog),_enableColors(true)
	{
		initColors();
	}
	ColorConsoleChannel::ColorConsoleChannel(std::ostream& str):
		_str(str),_enableColors(true)
	{
		initColors();
	}

	void ColorConsoleChannel::logInstance(int32 pro, const char* msg)
	{
		FastMutex::ScopedLock lock(_mutex);
		if (_enableColors)
		{
			if (pro < 0 || pro > Channel::PRIO_TRACE )
			{
				pro = 0;
			}
			int color = _colors[pro];
			if (color & 0x100)
			{
				_str << CSI << "1m";
			}
			color &= 0xff;
			_str << CSI << color << "m";
		}
		_str << msg;
		if (_enableColors)
		{
			_str << CSI << "0m";
		}
		_str << std::endl;
	}

	void ColorConsoleChannel::SetProperty(const std::string& name, const std::string& value)
	{
		if (name == "enableColors")
		{
			_enableColors = icompare(value, "true") == 0;
		}
		else if (name == "traceColor")
		{
			_colors[Channel::PRIO_TRACE] = parseColor(value);
		}
		else if (name == "debugColor")
		{
			_colors[Channel::PRIO_DEBUG] = parseColor(value);
		}
		else if (name == "informationColor")
		{
			_colors[Channel::PRIO_INFORMATION] = parseColor(value);
		}
		else if (name == "noticeColor")
		{
			_colors[Channel::PRIO_NOTICE] = parseColor(value);
		}
		else if (name == "warningColor")
		{
			_colors[Channel::PRIO_WARNING] = parseColor(value);
		}
		else if (name == "errorColor")
		{
			_colors[Channel::PRIO_ERROR] = parseColor(value);
		}
		else if (name == "criticalColor")
		{
			_colors[Channel::PRIO_CRITICAL] = parseColor(value);
		}
		else if (name == "fatalColor")
		{
			_colors[Channel::PRIO_FATAL] = parseColor(value);
		}
		else
		{
			Channel::SetProperty(name, value);
		}
	}

	std::string ColorConsoleChannel::GetProperty(const std::string& name) const
	{
		if (name == "enableColors")
		{
			return _enableColors ? "true" : "false";
		}
		else if (name == "traceColor")
		{
			return formatColor(_colors[Channel::PRIO_TRACE]);
		}
		else if (name == "debugColor")
		{
			return formatColor(_colors[Channel::PRIO_DEBUG]);
		}
		else if (name == "informationColor")
		{
			return formatColor(_colors[Channel::PRIO_INFORMATION]);
		}
		else if (name == "noticeColor")
		{
			return formatColor(_colors[Channel::PRIO_NOTICE]);
		}
		else if (name == "warningColor")
		{
			return formatColor(_colors[Channel::PRIO_WARNING]);
		}
		else if (name == "errorColor")
		{
			return formatColor(_colors[Channel::PRIO_ERROR]);
		}
		else if (name == "criticalColor")
		{
			return formatColor(_colors[Channel::PRIO_CRITICAL]);
		}
		else if (name == "fatalColor")
		{
			return formatColor(_colors[Channel::PRIO_FATAL]);
		}
		else
		{
			return Channel::GetProperty(name);
		}
	}

	ColorConsoleChannel::~ColorConsoleChannel()
	{

	}

	ColorConsoleChannel::Color ColorConsoleChannel::parseColor(const std::string& color) const
	{
		if (icompare(color, "default") == 0)
			return CC_DEFAULT;
		else if (icompare(color, "black") == 0)
			return CC_BLACK;
		else if (icompare(color, "red") == 0)
			return CC_RED;
		else if (icompare(color, "green") == 0)
			return CC_GREEN;
		else if (icompare(color, "brown") == 0)
			return CC_BROWN;
		else if (icompare(color, "blue") == 0)
			return CC_BLUE;
		else if (icompare(color, "magenta") == 0)
			return CC_MAGENTA;
		else if (icompare(color, "cyan") == 0)
			return CC_CYAN;
		else if (icompare(color, "gray") == 0)
			return CC_GRAY;
		else if (icompare(color, "darkGray") == 0)
			return CC_DARKGRAY;
		else if (icompare(color, "lightRed") == 0)
			return CC_LIGHTRED;
		else if (icompare(color, "lightGreen") == 0)
			return CC_LIGHTGREEN;
		else if (icompare(color, "yellow") == 0)
			return CC_YELLOW;
		else if (icompare(color, "lightBlue") == 0)
			return CC_LIGHTBLUE;
		else if (icompare(color, "lightMagenta") == 0)
			return CC_LIGHTMAGENTA;
		else if (icompare(color, "lightCyan") == 0)
			return CC_LIGHTCYAN;
		else if (icompare(color, "white") == 0)
			return CC_WHITE;
		else throw InvalidArgumentException("Invalid color value", color);
	}

	std::string ColorConsoleChannel::formatColor(Color color) const
	{
		switch (color)
		{
		case CC_DEFAULT:      return "default";
		case CC_BLACK:        return "black";
		case CC_RED:          return "red";
		case CC_GREEN:        return "green";
		case CC_BROWN:        return "brown";
		case CC_BLUE:         return "blue";
		case CC_MAGENTA:      return "magenta";
		case CC_CYAN:         return "cyan";
		case CC_GRAY:         return "gray";
		case CC_DARKGRAY:     return "darkGray";
		case CC_LIGHTRED:     return "lightRed";
		case CC_LIGHTGREEN:   return "lightGreen";
		case CC_YELLOW:       return "yellow";
		case CC_LIGHTBLUE:    return "lightBlue";
		case CC_LIGHTMAGENTA: return "lightMagenta";
		case CC_LIGHTCYAN:    return "lightCyan";
		case CC_WHITE:        return "white";
		default:              return "invalid";
		}
	}

	void ColorConsoleChannel::initColors()
	{
		_colors[0] = CC_DEFAULT; // unused
		_colors[Channel::PRIO_FATAL]       = CC_LIGHTRED;
		_colors[Channel::PRIO_CRITICAL]    = CC_LIGHTRED;
		_colors[Channel::PRIO_ERROR]       = CC_LIGHTRED;
		_colors[Channel::PRIO_WARNING]     = CC_YELLOW;
		_colors[Channel::PRIO_NOTICE]      = CC_DEFAULT;
		_colors[Channel::PRIO_INFORMATION] = CC_DEFAULT;
		_colors[Channel::PRIO_DEBUG]       = CC_GRAY;
		_colors[Channel::PRIO_TRACE]       = CC_GRAY;
	}
}