/********************************************************************
	created:	2014/09/09
	created:	10:27
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef _OKEY_SEMAPHORE_H_
#define _OKEY_SEMAPHORE_H_


#include "Types.h"


namespace okey
{
	class Semaphore
	{
	public:
		Semaphore(int n);
		Semaphore(int n, int max);
		~Semaphore();
		void Set();	/// Increments the semaphore's value by one and
		void Wait();/// Waits for the semaphore to become signalled.
		bool Wait(uint32 milliseconds);/// Waits for the semaphore to become signalled.
		bool TryWait(uint32 milliseconds);/// Waits for the semaphore to become signalled.
	private:
		Semaphore();
		Semaphore(const Semaphore&);
		Semaphore& operator = (const Semaphore&);
	private:
#ifdef WINDOWS
		HANDLE _sema;
#else
		volatile int    _n;
		int             _max;
		pthread_mutex_t _mutex;
		pthread_cond_t  _cond;
#endif
		
	};
	

} //namespace okey

#endif //SEMAPH_H
