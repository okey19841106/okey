/********************************************************************
	created:	2013/06/03
	created:	3-6-2013   22:33
	author:		okey
	
	purpose:	单件实例一律都用new和delete 
*********************************************************************/

#ifndef OKEY_BASE_SINGLETON_H
#define OKEY_BASE_SINGLETON_H

#include "nocopyable.h"
#include "Types.h"
#include "ToolKit.h"

namespace okey
{

#define initialiseSingleton(type)	\
	template<>	type* Singleton< type >::ms_Singleton = NULL;

#define initialiseTemplateSingleton(temp, type)	\
	template<> temp< type >* Singleton< temp< type > >::ms_Singleton = NULL;

#define createFileSingleton(type)	\
	initialiseSingleton(type)	\
	type the##type;

	template<typename T>
	class Singleton : private nocopyable
	{
		static T* ms_Singleton; 
	public:
		Singleton()
		{
			assert(this->ms_Singleton == NULL);
			this->ms_Singleton = static_cast<T*>(this);
			ToolKit::AtExit(DestroySingleton);
		}

		~Singleton()
		{
			this->ms_Singleton = NULL;
		}
		static T& GetSingleton()
		{
			assert(ms_Singleton);
			return *ms_Singleton;
		}
		static T* GetSingletonPtr()
		{
			return ms_Singleton;
		}

		static void DestroySingleton()
		{
			if (ms_Singleton)
			{
				delete ms_Singleton;
			}
		}
	private:
		Singleton(const Singleton&);
		Singleton& operator=(const Singleton&);
	};
	
	template<typename T> T* Singleton<T>::ms_Singleton = NULL;
}
#endif

