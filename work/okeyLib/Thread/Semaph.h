/********************************************************************
	created:	2014/09/09
	created:	10:27
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef SEMAPH_H
#define SEMAPH_H

#ifdef WINDOWS
//#include <Windows.h>
#else
#include <semaphore.h>
#endif

#include "Types.h"
#include "nocopyable.h"

namespace okey
{

	class Semaph:private nocopyable
	{
	public:
		Semaph();
		~Semaph();


	public:
		void Post();
		void Wait();
		int32 TryWait();

	private:
#ifdef WINDOWS
		HANDLE m_Sem;
#else
		sem_t* m_pSem;
#endif

	};

	extern Semaph* g_pMsgQueueSemaph;
#ifdef LINUX
	extern Semaph* g_pAsyncOperationQueueSemaph;
#endif

} //namespace okey

#endif //SEMAPH_H
