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

#ifndef ATOMICCOUNTER_HPP_
#define ATOMICCOUNTER_HPP_

#include "Types.h"
#include "AtomicULong.h"

namespace okey
{
	
	//////////////////////////////////////////////////////////
	//class AtomicCounter
	//  Derives from AtomicULong.
	//  Implements atomic incrementation and decrementation
	//
	//////////////////////////////////////////////////////////
	class AtomicCounter : public AtomicUInt
	{
		public:
			AtomicCounter() { Value = 0; }
			AtomicCounter(uint32 InitialValue) { Value = InitialValue; }


			//////////////////////////////////////////////////////////
			//unsigned long operator++()
			// lockless threadsafe prefix increment operator
			//
			// Parameters
			//  None
			//
			// Return values
			//  Returns the incremented value
			/////////////////////////////////////////////////////////
			uint32 operator++();



			/////////////////////////////////////////////////////////
			//unsigned long operator--()
			// lockless threadsafe prefix decrement operator
			//
			// Parameters
			//  None
			//
			// Return values
			//  Returns the decremented value
			////////////////////////////////////////////////////////
			uint32 operator--();



		private:
			// Disabled copy constructor
			AtomicCounter(const AtomicCounter & other) {}

			// Disabled assignment operator
			AtomicCounter operator=(const AtomicCounter & other) { return *this; }
	};
	
}

#endif
