#ifndef CREFCOUNTER_HPP
#define CREFCOUNTER_HPP

#include "Thread/AtomicCounter.h"

namespace okey
{
	class CRefCounter
	{

		public:
			CRefCounter() { Counter.SetValue(1); }
			virtual ~CRefCounter() {}
			void AddRef() { ++Counter; }
			void DecRef()
			{
				if(--Counter == 0)
					delete this;
			}
		private:
			AtomicCounter Counter;

	};
	
}

#endif
