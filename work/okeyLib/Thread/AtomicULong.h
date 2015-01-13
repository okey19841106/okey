

#ifndef ATOMICULONG_HPP_
#define ATOMICULONG_HPP_

#include "Types.h"

namespace okey
{
	
	class AtomicUInt
	{
		public:
			AtomicUInt() { Value = 0; }

			AtomicUInt(uint32 InitialValue) { Value = InitialValue; }
			uint32 SetVal(uint32 NewValue);
			uint32 GetVal() { return Value; }
		private:
			AtomicUInt(const AtomicUInt & other) {}
			AtomicUInt operator=(AtomicUInt & other) { return *this; }
		protected:

#ifdef WINDOWS
			__declspec(align(4))  volatile uint32 Value;
#else
			volatile unsigned uint32 Value;
#endif
	};
	
}

#endif
