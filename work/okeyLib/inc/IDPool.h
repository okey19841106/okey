/********************************************************************
	created:	2015/03/10
	created:	15:24
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __ID_POOL_H__
#define __ID_POOL_H__


#include <deque>
#include "HashMap.h"


namespace okey
{
	class IDPool
	{
	public:
		IDPool(uint32 maxvalue, const std::string& des = "");
		~IDPool();
		bool AllocID(uint32& allocid);
		void FreeID(uint32 allocid);
	private:
		std::string m_szDes;
		uint32 m_uMax;
		uint32 m_uCur;
		std::deque<uint32> m_FreeIDs;
	};

	template<typename Value, int32 MAX_VALUE = 1024>
	class IDMap
	{
	public:
		typedef hash_map<uint32, Value> MapType;
		typedef typename MapType::iterator iterator;
		typedef typename MapType::const_iterator const_iterator;
		typedef typename MapType::reference reference;
		typedef typename MapType::const_reference const_reference;
	public:
		IDMap(const std::string& des = ""):m_IDPool(MAX_VALUE, des){}
		~IDMap(){}

		iterator begin()
		{
			return m_IDMap.begin();
		}
		iterator end()
		{
			return m_IDMap.end();
		}
		iterator find(const uint32& id)
		{
			return m_IDMap.find(id);
		}

		const_iterator find(const uint32& id) const
		{
			return m_IDMap.find(id);
		}

		void erase(const_iterator itr)
		{
			m_IDPool.FreeID(itr->first);
			m_IDMap.erase(itr);
		}

		bool insert(const Value& v, uint32& key)
		{
			if (m_IDPool.AllocID(key))
			{
				m_IDMap.insert(std::make_pair<uint32, Value>(key, v));
				return true;
			}
			return false;
		}

		void erase(uint32 id)
		{
			iterator itr = m_IDMap.find(id);
			if (itr != m_IDMap.end())
			{
				erase(itr);
			}
		}
	private:
		MapType m_IDMap;
		IDPool m_IDPool;
	};
}


#endif