
#ifndef ATOMICCOUNTER_HPP_
#define ATOMICCOUNTER_HPP_

#include "Types.h"
#include "AtomicULong.h"

namespace okey
{
	
	
	class AtomicCounter : public AtomicUInt
	{
		public:
			AtomicCounter() { Value = 0; }
			AtomicCounter(uint32 InitialValue) { Value = InitialValue; }


			
			uint32 operator++();



			uint32 operator--();



		private:
			// Disabled copy constructor
			AtomicCounter(const AtomicCounter & other) {}

			// Disabled assignment operator
			AtomicCounter operator=(const AtomicCounter & other) { return *this; }
	};
	
}

#endif
