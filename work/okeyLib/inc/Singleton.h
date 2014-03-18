/********************************************************************
	created:	2013/06/03
	created:	3-6-2013   22:33
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef OKEY_BASE_SINGLETON_H
#define OKEY_BASE_SINGLETON_H

#include "nocopyable.h"
#include "Types.h"


namespace okey
{
	class NoLock :private nocopyable
	{
	public:
		NoLock(){}
		~NoLock(){}

		void Lock(){}
		void UnLock(){}
	};


	template<typename T, typename Lock = NoLock>
	class Singleton : private nocopyable
	{
		static T* ms_Singleton; 
		static Lock m_lock;
	public:
		
		static T& GetSingleton()
		{
			return (*GetSingletonPtr());
		}
		static T* GetSingletonPtr()
		{
			if (ms_Singleton == NULL)
			{
				m_lock.Lock();
				if (ms_Singleton == NULL)
				{
					ms_Singleton = (T*)::malloc(sizeof(T));
					if (ms_Singleton)
					{
						new(ms_Singleton)T();
					}
				}
				m_lock.UnLock();
			}
			return ms_Singleton;
			
		}
	protected:
		Singleton()
		{

		}
		virtual ~Singleton()
		{

		}
	};
	template<typename T, typename Lock> Lock Singleton<T,Lock>::m_lock;
	template<typename T, typename Lock> T* Singleton<T,Lock>::ms_Singleton = NULL;
}
#endif

