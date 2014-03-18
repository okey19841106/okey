/// \file GetTime.h
/// \brief Returns the value from QueryPerformanceCounter.  This is the function RakNet uses to represent time. This time won't match the time returned by GetTimeCount(). See http://www.jenkinssoftware.com/forum/index.php?topic=2798.0
///
/// This file is part of RakNet Copyright 2003 Jenkins Software LLC
///
/// Usage of RakNet is subject to the appropriate license agreement.


#ifndef __OKEY_TIME_H_
#define __OKEY_TIME_H_

#include "Types.h"

namespace okey
{
	class GTime{
	public:
	/// Same as GetTimeMS
	/// Holds the time in either a 32 or 64 bit variable, depending on __GET_TIME_64BIT
		static uint32 GetTime( void );

	/// Return the time as 32 bit
	/// \note The maximum delta between returned calls is 1 second - however, RakNet calls this constantly anyway. See NormalizeTime() in the cpp.
		static uint32 GetTimeMS( void );
	
	/// Return the time as 64 bit
	/// \note The maximum delta between returned calls is 1 second - however, RakNet calls this constantly anyway. See NormalizeTime() in the cpp.
		static uint64 GetTimeUS( void );

	protected:
		static bool initialized;
	};
}

#endif
