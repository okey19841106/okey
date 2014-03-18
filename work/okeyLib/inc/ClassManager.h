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
//  created:	2011-11-7 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////

#ifndef __CLASS_MANAGER_H__
#define __CLASS_MANAGER_H__

#include "Types.h"
#include <vector>
#include "TManager.h"

namespace okey
{

	class CClass;

	/*class ClassManager
	{
	
		ClassManager(){}
		~ClassManager(){}
		ClassManager(const ClassManager&);
		ClassManager& operator=(const ClassManager&);
	public:
		int32 GetClassCount(){return m_classlist.size();}
		CClass* GetClass(uint32 classID);
		CClass* GetClass(const char* name);
		void AddClass(CClass* pClass)
		{
			m_classlist.push_back(pClass);
		}
		void PrintClass();
		static ClassManager& GetSingleton()
		{
			static ClassManager m_instance;
			return m_instance;
		}
	protected:
	private:
		std::vector<CClass*> m_classlist;
	};*/

	class ClassManager: public TManager<CClass>
	{
	public:
		void PrintClass();
		static ClassManager& GetSingleton()
		{
			static ClassManager m_instance;
			return m_instance;
		}
	protected:
	private:
		ClassManager(){}
		~ClassManager(){}
		ClassManager(const ClassManager&);
		ClassManager& operator=(const ClassManager&);
	};

#define s_ClassManager ClassManager::GetSingleton()


}






#endif 