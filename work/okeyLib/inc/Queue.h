/********************************************************************
	created:	2013/06/12
	created:	12-6-2013   20:33
	author:		okey
	
	purpose:	
*********************************************************************/


#ifndef ___QUEUE_H___
#define ___QUEUE_H___

#include <stdlib.h>
#include "Types.h"

namespace okey
{
/**
 * our own Queue
 * a rotate queue
 */
	template<typename T, uint32 ELEMENTCOUNT>
	class Queue
	{
		T m_List[ELEMENTCOUNT];
		uint32 m_Size;
		uint32 m_Front;
		uint32 m_Back;
	public:
		/**
		 * rotate queue constructor
		 * @param size the max count of the elements in the queue
		 */
		Queue():m_Size(0),m_Front(0), m_Back(0)
		{
			memset(m_List, 0, sizeof(m_List));
		}
		~Queue(){}

	public:
		uint32 Size()
		{
			return m_Size;
		}
		bool PushBack( const T& element )
		{
			if( m_Size == ELEMENTCOUNT )
			{
				return false;
			}
			m_List[m_Back] = element;
			//	m_Back = (m_Back+1) % m_Capacity;
			m_Back = (m_Back+1) % static_cast<int32>( ELEMENTCOUNT );

			++m_Size;
			return true;
		}
		void PopFront()
		{
			if( 0 == Size() )
			{
				return;
			}

			m_Front = (m_Front+1) % ELEMENTCOUNT;
			if( m_Front == m_Back )
			{
				m_Front = m_Back = 0;
			}

			--m_Size;
		}
		bool Front( T& element )
		{
			if( 0 == Size() )
			{
				return false;
			}

			element = m_List[m_Front];

			return true;
		}
	
};

}
#endif //QUEUE_H
