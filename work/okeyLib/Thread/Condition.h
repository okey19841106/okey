/********************************************************************
	created:	2014/09/09
	created:	10:28
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef OKEY_BASE_CONDITION_H
#define OKEY_BASE_CONDITION_H

#include "Types.h"
#include "nocopyable.h"
#ifdef WINDOWS
	//#include <windows.h>
#else
	#include <pthread.h>
#endif



namespace okey
{
	class Mutex;

	class Condition : private nocopyable
	{
	 public:
	  Condition();
	  ~Condition();
	  void wait(Mutex& mutex);
	  void signal();
	  void broadcast();

	 private:
	  
	#ifdef WINDOWS
	  HANDLE m_EventOne; 
	  HANDLE m_EventAll; 
	#else
	  pthread_cond_t pcond_;
	#endif
	  
	};

}
#endif  // MUDUO_BASE_CONDITION_H
