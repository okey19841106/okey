/********************************************************************
	created:	2015/07/24
	created:	15:23
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_DEBUGGER_H__
#define __BASE_DEBUGGER_H__

#include <string>

namespace okey
{
	class Debugger
	{
	public:
		static bool IsAvailable();
		static void Message(const std::string& msg);
		static void Message(const std::string& msg, const char* file, int32 line);
		static void Enter();
		static void Enter(const std::string& msg);
		static void Enter(const std::string& msg, const char* file, int32 line);
		static void Enter(const char* file, int32 line);
	};
}

#endif