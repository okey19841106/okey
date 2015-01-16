
#ifndef ATOMICCOUNTER_HPP_
#define ATOMICCOUNTER_HPP_

#include "Types.h"

namespace okey
{
	
	
	class AtomicCounter 
	{
	public:
		AtomicCounter();
		explicit AtomicCounter(int32 InitialValue);
		AtomicCounter(const AtomicCounter & other);
		AtomicCounter& operator=(const AtomicCounter & other);
		AtomicCounter& operator=(int32 value);
		int32 operator++();
		int32 operator--();
		int32 operator++(int32);
		int32 operator--(int32);
		int32 GetValue()const {return _value;}
		operator int32() const;
		bool operator !() const;
		void SetValue(int32 v);
	private:
		volatile int32 _value;

	};
	
}

#endif
