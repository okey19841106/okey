#ifndef ATOMICBOOLEAN_HPP__
#define ATOMICBOOLEAN_HPP__

#include "AtomicULong.h"

namespace okey
{


	class AtomicBoolean
	{

		public:
			AtomicBoolean() : Value(0) {}

			AtomicBoolean(bool val)
			{
				if(val)
					Value.SetVal(1);
				else
					Value.SetVal(0);
			}

			bool SetVal(bool val);

			bool GetVal()
			{
				unsigned long val = 0;

				val = Value.GetVal();

				return (val & 1);
			}

		private:
			// Disabled copy constructor
			AtomicBoolean(const AtomicBoolean & other) {}

			// Disabled assignment operator
			AtomicBoolean operator=(const AtomicBoolean & other) { return *this; }

			AtomicUInt Value;
	};
	
}

#endif
