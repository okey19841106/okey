/********************************************************************
	created:	2015/07/14
	created:	14:47
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __LOG_CONSOLE_CHANNEL_H__
#define __LOG_CONSOLE_CHANNEL_H__

#include "Channel.h"
#include <ostream>
#include "Thread/Mutex.h"

namespace okey
{
	class ConsoleChannel: public Channel
	{
	public:
		ConsoleChannel();
		ConsoleChannel(std::ostream& str);
		void Log(const Message& msg);
	protected:
		~ConsoleChannel();
	private:
		std::ostream& _str;
		static FastMutex _mutex;
	};

	class ColorConsoleChannel: public Channel
	{
	public:
		ColorConsoleChannel();
		ColorConsoleChannel(std::ostream& str);
		void Log(const Message& msg);
		void SetProperty(const std::string& name, const std::string& value);
		std::string GetProperty(const std::string& name) const;
	protected:
		enum Color
		{
			CC_DEFAULT      = 0x0027,
			CC_BLACK        = 0x001e,
			CC_RED          = 0x001f,
			CC_GREEN        = 0x0020,
			CC_BROWN        = 0x0021,
			CC_BLUE         = 0x0022,
			CC_MAGENTA      = 0x0023,
			CC_CYAN         = 0x0024,
			CC_GRAY         = 0x0025,
			CC_DARKGRAY     = 0x011e,
			CC_LIGHTRED     = 0x011f,
			CC_LIGHTGREEN   = 0x0120,
			CC_YELLOW       = 0x0121,
			CC_LIGHTBLUE    = 0x0122,
			CC_LIGHTMAGENTA = 0x0123,
			CC_LIGHTCYAN    = 0x0124,
			CC_WHITE        = 0x0125
		};

		~ColorConsoleChannel();
		Color parseColor(const std::string& color) const;
		std::string formatColor(Color color) const;
		void initColors();
	private:
		std::ostream& _str;
		bool _enableColors;
		Color _colors[9];
		static FastMutex _mutex;
		static const std::string CSI;
	};
}

#endif