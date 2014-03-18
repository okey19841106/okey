/********************************************************************
	created:	2013/06/12
	created:	12-6-2013   20:34
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __QUEUE_EX_H__
#define __QUEUE_EX_H__

#include "Types.h"
#include "Queue.h"
#include "Mutex.h"

namespace okey
{
	template<typename T, uint32 ELEMENTCOUNT>
	class QueueEx
	{
	public:
		QueueEx()
		{

		}
		~QueueEx()
		{

		}
		T* Pop()
		{
			MutexGuard(m_Mutex);
			if (m_Queue.Size() == 0)
			{
				return NULL;
			}
			return m_Queue.PopFront();
		}
		bool Push(T* pval)
		{
			MutexGuard(m_Mutex);
			if (m_Queue.Size() >= ELEMENTCOUNT)
			{
				return false;
			}
			return m_Queue.PushBack(pval);
		}
		int32 GetSize()
		{
			MutexGuard(m_Mutex);
			return m_Queue.Size();
		}
	private:
		Queue<T*, ELEMENTCOUNT> m_Queue;
		Mutex m_Mutex;
	};
}
#endif