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
//  created:	2011-12-20 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////

#ifndef __LOGIC_MANAGER_H__
#define __LOGIC_MANAGER_H__

#include "Types.h"
#include "LogicConfig.h"
#include "DataBuffer.h"
#include "TList.h"
#include "BaseClass.h"
#include "AnyTypeBase.h"
#include "TManager.h"
#include "FactoryManager.h"

namespace okey
{
	class LogicTreeBase;
	class LogicGroupDef;

	class LogicManagerBase
	{
	public:
		LogicManagerBase();
		~LogicManagerBase();
		bool Load(const char* path);
		LogicTreeBase* MakeLogic(int32 id);
		bool FreeLogic(LogicTreeBase* pLogic, bool bDelete = true);
		void FreeMemory();
		LogicGroupDef* GetLogicGroupDefine(int32 id);
		void Clear();
	protected:
		TList<LogicTreeBase> m_logicList[MAX_LOGIC_LIST];
		LogicGroupDef* m_logicDefList[MAX_LOGIC_LIST];
	private:
	};

	class LogicDataManager: public DataManager
	{
	public:
		LogicDataManager(LogicManagerBase* mgr);
		~LogicDataManager();
		virtual bool Load(const char* sFile, CfgLoaderBase* pLoader);
		void Clear();
		bool InitLogic(LogicTreeBase* pLogic, int32 dataid);
	protected:
		LogicManagerBase* m_pManager;
	};

	class LogicManagerSingleton: public LogicManagerBase, public TManager<CClass>
	{
	public:
		void PrintClass();
		static LogicManagerSingleton& GetSingleton()
		{
			static LogicManagerSingleton m_instance;
			return m_instance;
		}
	protected:
	private:
		LogicManagerSingleton(){}
		~LogicManagerSingleton(){}
		LogicManagerSingleton(const LogicManagerSingleton&);
		LogicManagerSingleton& operator=(const LogicManagerSingleton&);
	};

	class LogicFactoryManager: public FactoryManagerArg0Base
	{
	public:
		static LogicFactoryManager& GetSingleton()
		{
			static LogicFactoryManager m_instance;
			return m_instance;
		}
	protected:
	private:
		LogicFactoryManager(){}
		~LogicFactoryManager(){}
		LogicFactoryManager(const LogicFactoryManager&);
		LogicFactoryManager& operator=(const LogicFactoryManager&);
	};

#define s_LogicFactoryManager LogicFactoryManager::GetSingleton()
#define s_ClassLogicManager LogicManagerSingleton::GetSingleton()


}


#endif