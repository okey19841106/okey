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

#ifndef ATOMICFLOAT_HPP__
#define ATOMICFLOAT_HPP__

#include "AtomicULong.h"

namespace okey
{
	
	class AtomicFloat
	{
		public:
			AtomicFloat() : Value(0) {}

			AtomicFloat(float InitialValue)
			{
				unsigned long iv = *(reinterpret_cast< unsigned long* >(&InitialValue));
				Value.SetVal(iv);
			}
			float SetVal(float NewValue);
			float GetVal();

		private:
			// Disabled copy constructor
			AtomicFloat(const AtomicFloat & other) {}

			// Disabled assignment operator
			AtomicFloat operator=(const AtomicFloat & other) { return *this; }

			AtomicUInt Value;
	};
}


#endif
