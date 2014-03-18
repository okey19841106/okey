/********************************************************************
	created:	2013/06/12
	created:	12-6-2013   20:35
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __HASH_LIST_H__
#define __HASH_LIST_H__

#include "Types.h"

namespace okey
{
	template<typename T, int32 TABLECOUNT, int32 ELEMENTCOUNT>
	class HashList
	{
		CircleList<T, ELEMENTCOUNT> m_ListTable[TABLECOUNT];
		int32 m_HashKey;
		int32 m_Count;
		T m_DefVal;
	public:
		HashList():m_HashKey(0),m_Count(0)
		{
			if (ELEMENTCOUNT >= 65535)
			{
				assert(false);
			}
		}
		~HashList()
		{

		}

		void Init(T def)
		{
			m_DefVal = def;
			for(int32 i = 0; i < TABLECOUNT; ++ i)
				m_ListTable[i].Init(def);
		}

		int32 Add(const T& Val)
		{
			int32 curkey = m_HashKey;
			while (m_ListTable[m_HashKey].IsFull())
			{
				++m_HashKey;
				if (curkey == m_HashKey)
				{
					return -1;
				}
				if (m_HashKey >= TABLECOUNT)
				{
					m_HashKey = 0;
				}
			}
			int32 tableIndex = m_ListTable[m_HashKey].Add(Val);
			curkey = m_HashKey;
			if (tableIndex == -1)
			{
				return -1;
			}
			++m_HashKey;
			++m_Count;
			if (m_HashKey >= TABLECOUNT)
			{
				m_HashKey = 0;
			}
			curkey = curkey << 16;
			return curkey + tableIndex;
		}

		bool Add(int32 index, const T& val)
		{
			int32 key = -1;
			int32 id = -1;
			id = index & 0x0000ffff;
			key = index >> 16;
			if (key < 0 || key > TABLECOUNT)
			{
				return false;
			}
			if (!m_ListTable[key].Add(id,val))
			{
				return false;
			}
			return true;
		}

		int32 AddByKey(int32 hashkey, const T& val)
		{
			if (hashkey < 0 || hashkey > TABLECOUNT)
			{
				return -1;
			}
			int32 tableIndex = m_ListTable[hashkey].Add(val);
			if (tableIndex)
			{
				++m_Count;
			}
			hashkey = hashkey << 16;
			return hashkey + tableIndex;
		}

		bool Remove(int32 index)
		{
			int32 key = -1;
			int32 id = -1;
			id = index & 0x0000ffff;
			key = index >> 16;
			if (key < 0 || key > TABLECOUNT)
			{
				return false;
			}
			if (!m_ListTable[key].Remove(id,val))
			{
				return false;	
			}
			--m_Count;
			return true;
		}

		inline T Get(int32 index)
		{
			int32 key = -1;
			int32 id = -1;
			id = index & 0x0000ffff;
			key = index >> 16;
			if (key < 0 || key > TABLECOUNT)
			{
				return m_DefVal;
			}
			return m_ListTable[key].Get(id);
		}

		int32 GetCount(){return m_Count;}

	};
}


#endif