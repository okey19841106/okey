/********************************************************************
	created:	2015/01/20
	created:	17:03
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __THREAD_ACTIVE_STARTER_H__
#define __THREAD_ACTIVE_STARTER_H__

#include "ThreadPool.h"
#include "ActiveRunnable.h"

namespace okey
{
	template<typename OwnerType>
	class ActiveStarter
	{
	public:
		static void Start(OwnerType* pOwner, ActiveRunnableBase::Ptr pRunnable)
		{
			ThreadPool::defaultPool().Start(*pRunnable);
			pRunnable->AddRef(); // The runnable will release itself.
		}
	};
}

#endif