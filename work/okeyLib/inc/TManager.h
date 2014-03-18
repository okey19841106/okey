//////////////////////////////////////////////////////////////
//                    .----.
//                 _.'__    `.
//             .--(#)(##)---/#\
//           .' @          /###\
//           :       ,     #####
//            `-..__.-' _.-\###/ 
//                   `;_:   `"'
//                 .'"""""`.
//                /,        ,\
//               //          \\
//               `-._______.-'
//              ___`. | .'___
//             (______|______)
//
//  created:	2011-11-14 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////


#ifndef __T_MANAGER_H__
#define __T_MANAGER_H__

#include "Types.h"
#include <map>
#include <string>
#include "UtilID.h"

namespace okey
{
	template<typename T>
	class TManager
	{
	public:
		virtual int32 GetCount()
		{
			return (int32)m_Tmap.size();
		}
		virtual T* GetObj(const char* name)
		{
			std::map<UtilID,T*>::iterator itr = m_Tmap.find(name);
			if (itr == m_Tmap.end())
			{
				return NULL;
			}
			return itr->second;
		}
		virtual T* GetObj(uint32 objid)
		{
			std::map<UtilID,T*>::iterator itr = m_Tmap.find(objid);
			if (itr == m_Tmap.end())
			{
				return NULL;
			}
			return itr->second;
		}
		virtual bool AddObj(T* obj)
		{
			if (!obj)
			{
				return false;
			}
			m_Tmap[obj->GetID()] = obj;
			return true;
		}
	protected:
		std::map<UtilID,T*> m_Tmap;
	private:
		
	};
}


#endif