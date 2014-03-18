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

#ifndef __LOGIC_GROUP_DEF_H__
#define __LOGIC_GROUP_DEF_H__

#include "Types.h"
#include "LogicConfig.h"
#include "AnyTypeBase.h"
#include "UtilID.h"
#include "LogicTreeBase.h"
#include <vector>

namespace okey
{
	struct LogicMember 
	{
		std::string name;
		std::string refname;
		std::string val;
		std::string defval;
		LogicMember& operator=(const LogicMember& lm)
		{
			name = lm.name;
			refname = lm.refname;
			defval = lm.defval;
			val = lm.val;
			return *this;
		}
		LogicMember()
		{
			name = "";
			refname = "";
			val = "";
			defval = "0";
		}
	};

	struct LogicNodeDef 
	{
		int32 nGroupID;
		int32 nType;
		int32 nParentID;
		int32 nInputCount;
		int32 nLogicID;
		CClass* pClass;
		LogicInputInfo m_InputInfo[MAX_LOGIC_IN_OUT_PUT];
		std::string name;
		std::vector<LogicMember> m_MemberList;
		LogicNodeDef()
		{
			nGroupID = -1;
			nType = -1;
			nParentID = -1;
			nInputCount = 0;
			nLogicID = -1;
			pClass = NULL;
			memset(m_InputInfo,-1, sizeof(LogicInputInfo)*MAX_LOGIC_IN_OUT_PUT );
		}
	};

	class LogicGroupDef
	{
		//变量名utilid,  groupid, 基本类型
		typedef std::map<UtilID, std::pair<int32, CTypeBase*> > LogicMemberMap;
	public:
		class LogicMemberCmp
		{
		public:
			LogicMemberCmp(){}
			~LogicMemberCmp(){}
			bool operator()(const LogicNodeDef& lnd1, const LogicNodeDef& lnd2)
			{
				return lnd1.nGroupID < lnd2.nGroupID;
			}
		protected:
		private:
		};
		LogicGroupDef():m_id(-1),m_classSize(0){}
		~LogicGroupDef(){}

		bool AddLogicNodeDef(LogicNodeDef& node);
		LogicTreeBase* Create();

		void SetMemberValue(const char* name, int32 val, LogicGroup* pGroup);
		void SetMemberValue(const char* name, float val, LogicGroup* pGroup);
		void SetMemberValue(const char* name, const char* val, LogicGroup* pGroup);

		int32 GetMemberValue(const char* name, int32 defval, LogicGroup* pGroup);
		float GetMemberValue(const char* name, float defval, LogicGroup* pGroup);
		char* GetMemberValue(const char* name, char* defval, LogicGroup* pGroup);
		int32 GetGroupID()const{return m_id;}
		int32 GetClassSize()const{return m_classSize;}
	protected:
	private:
		int32 m_id;
		int32 m_classSize;
		std::vector<LogicNodeDef> m_nodeList;
		std::string m_gourpName;
		LogicMemberMap m_logicMemberMap;
	};
}

#endif