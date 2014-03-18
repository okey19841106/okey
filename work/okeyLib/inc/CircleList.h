/********************************************************************
	created:	2013/05/26
	created:	26-5-2013   20:13
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CIRCLE_LIST_H__
#define __CIRCLE_LIST_H__

#include "Types.h"

namespace okey
{
	template<typename T, int32 ELEMENTCOUNT>
	class CircleList
	{
		T m_element[ELEMENTCOUNT];
		T m_defval;
		uint32 m_count;
		int32 m_pos;
	public:
		CircleList()
		{
			m_defval = 0;
			Init();
		}

		CircleList(const T& del)
		{
			m_defval = del;
			Init();
		}

		bool Add(int32 i, const T& val)
		{
			if (i > ELEMENTCOUNT || i < 0)
			{
				return false;
			}
			if (m_element[i] == m_defval)
			{
				++m_count;
			}
			m_element[i] = val;
			return true;
		}

		bool Remove(int32 i)
		{
			if (i > ELEMENTCOUNT || i < 0 || m_count <= 0)
			{
				return false;
			}
			m_element[i] = m_defval;
			--m_count;
			return true;
		}
		
		T Get(int32 i)
		{
			if (i > ELEMENTCOUNT || i < 0 || m_count <= 0)
			{
				return m_defval;
			}
			return m_element[i];
		}

		uint32 GetCount(){return m_count;}

		int32 Add(const T& val)
		{
			if (m_count >= ELEMENTCOUNT)
			{
				return -1;
			}
			while (true)
			{
				if (m_element[m_pos] != m_defval)
				{
					++m_pos;
					if (m_pos == ELEMENTCOUNT)
					{
						m_pos = 0;
					}
				}
				int32 pos = m_pos;
				m_element[m_pos] = val;
				++m_pos;
				++m_count;
				return pos;
			}
		}
		void Init()
		{
			for (int32 i = 0; i< ELEMENTCOUNT; ++i)
			{
				m_element[i] = m_defval;
			}
			m_pos = 0;
		}
		bool IsFull(){return m_count == ELEMENTCOUNT;}
	};

}


#endif