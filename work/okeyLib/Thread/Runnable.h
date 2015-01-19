/********************************************************************
	created:	2015/01/18
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __THREAD_RUNNABLE_H__
#define __THREAD_RUNNABLE_H__

namespace okey
{
	class Runnable
	{
		public:	
			Runnable(){}
			virtual ~Runnable(){}
			virtual void run() = 0;
			
	};
}

#endif