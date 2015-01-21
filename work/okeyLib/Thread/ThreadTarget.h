/********************************************************************
	created:	2015/01/21
	created:	14:32
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __THREAD_TARGET_H__
#define __THREAD_TARGET_H__

#include "Runnable.h"

namespace okey
{
	class ThreadTarget: public Runnable
	{
	public:
		typedef void (*f)();
	public:
		ThreadTarget(f fun);
		ThreadTarget(const ThreadTarget& te);
		ThreadTarget& operator = (const ThreadTarget& te);
		~ThreadTarget();
		void Run();
	protected:
	private:
		f _f;
	};

	inline void ThreadTarget::Run()
	{
		_f();
	}
}
#endif