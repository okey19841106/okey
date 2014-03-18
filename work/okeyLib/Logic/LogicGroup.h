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
//  created:	2011-12-19 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////

#ifndef __LOGIC_GROUP_H__
#define __LOGIC_GROUP_H__

#include "Types.h"
#include "LogicConfig.h"

namespace okey
{
	class LogicTreeBase;
	class LogicGroupDef;

	class LogicGroup
	{
	public:
		LogicGroup();
		~LogicGroup();
		void Reset(){m_bTerminate = false;}
		int32 GetClassSize()const{return m_classSize;}
		void SetClassSize(int32 n){m_classSize = n;}
		bool IsTerminate()const{return m_bTerminate;}
		void Terminate(){m_bTerminate = true;}
		void SetLogicGroupDef(LogicGroupDef* pDef);
		LogicGroupDef* GetLogicGroupDef()const{return m_pDef;}
		bool AddLogic(LogicTreeBase* pLogic);
		LogicTreeBase* GetLogic(int32 id){return m_logicList[id];}
	protected:
	private:
		int32 m_classSize;
		LogicTreeBase* m_logicList[MAX_LOGIC_LIST];
		LogicGroupDef* m_pDef;
		bool m_bTerminate;
	};
}


#endif