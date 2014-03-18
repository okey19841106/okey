/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2008-2011 <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef ATOMICULONG_HPP_
#define ATOMICULONG_HPP_

#include "Types.h"

namespace okey
{
	

	/////////////////////////////////////////////////
	//class AtomicULong
	//  Stores an unsigned long atomically.
	//  Base class for all Arcemu atomics.
	//
	////////////////////////////////////////////////
	class AtomicUInt
	{
		public:
			AtomicUInt() { Value = 0; }

			AtomicUInt(uint32 InitialValue) { Value = InitialValue; }

			////////////////////////////////////////////////////////////
			//unsigned long SetVal( unsigned long NewValue )
			// lockless threadsafe set operation on the contained value
			//
			// Parameters
			//  unsigned long val  -  value to be set
			//
			// Return values
			//  Returns the initial value contained
			///////////////////////////////////////////////////////////
			uint32 SetVal(uint32 NewValue);


			///////////////////////////////////////////////////////////
			//unsigned long GetVal()
			// non-threadsafe get operation on the contained value
			//
			// Parameters
			//  None
			//
			// Return values
			//  Returns the value contained
			//////////////////////////////////////////////////////////
			uint32 GetVal() { return Value; }


		private:
			// Disabled copy constructor
			AtomicUInt(const AtomicUInt & other) {}

			// Disabled assignment operator
			AtomicUInt operator=(AtomicUInt & other) { return *this; }


		protected:

#ifdef WINDOWS
			__declspec(align(4))  volatile uint32 Value;
#else
			volatile unsigned long Value;
#endif
	};
	
}

#endif
