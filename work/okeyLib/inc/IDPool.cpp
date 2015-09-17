#include "PreCom.h"
#include "IDPool.h"
#include <algorithm>

namespace okey
{
// 	IDPool::IDPool(uint32 maxvalue, const std::string& des):m_uMax(maxvalue),m_szDes(des),m_uCur(0)
// 	{
// 
// 	}
// 	IDPool::~IDPool()
// 	{
// 
// 	}
// 	bool IDPool::AllocID(uint32& allocid)
// 	{
// 		if (m_FreeIDs.empty())
// 		{
// 			if (m_uCur == m_uMax)
// 			{
// 				//满了。 申请不到。。
// 				return false;
// 			}
// 			allocid=m_uCur++;
// 			//assert(m_uMax != 0)
// 		}
// 		else
// 		{
// 			allocid = m_FreeIDs[0];
// 			m_FreeIDs.pop_front();
// 		}
// 		return true;
// 	}
// 	void IDPool::FreeID(uint32 allocid)
// 	{
// 		std::deque<uint32>::iterator itr = std::find(m_FreeIDs.begin(), m_FreeIDs.end(), allocid);
// 		if (itr != m_FreeIDs.end())
// 		{
// 			//重复释放。。
// 			return;
// 		}
// 		m_FreeIDs.push_back(allocid);
// 	}
}