// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

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
