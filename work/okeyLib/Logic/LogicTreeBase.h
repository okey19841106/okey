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
//  created:	2011-12-15 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////


#ifndef __LOGIC_TREE_BASE_H__
#define __LOGIC_TREE_BASE_H__

#include "Types.h"
#include "LogicConfig.h"
#include "TreeNodeBase.h"

namespace okey
{

	class LogicGroup;
	template<typename T> class TList;
	class LogicInput;
	class LogicOutput;
	class LogicInputManager;
	class LogicOutputManager;
	

	struct LogicInputInfo 
	{
		int16 LogicIndex;
		int16 OutputIndex;
		LogicInputInfo()
		{
			LogicIndex = -1;
			OutputIndex = -1;
		}
	};

	class LogicTreeBase: public TreeNodeBase
	{
		friend class TList< LogicTreeBase >;
	public:
		LogicTreeBase();
		~LogicTreeBase();
		virtual bool Init(){return false;}
		virtual void PrevProcess(){}
		virtual bool Process(){return false;}//为false，下次还会执行之。。。
		virtual void PostProcess(){}
		virtual void PrevProcessChild(){}
		virtual void PostProcessChild(){}
		virtual LogicInputManager* GetInputManager(){return NULL;}
		virtual LogicOutputManager* GetOutputManager(){return NULL;}
		virtual void OnReset();
		virtual char* Buffer2Data(char* pBuffer, int32 flag);
		virtual char* Data2Buffer(char* pBuffer, int32 flag);
		virtual void OnBuffer2Data(){}
		virtual void OnData2Buffer(){}

		void DoProcess();
		bool AddChildLogic(LogicTreeBase* pLogic);
		bool RemoveChildLogic(LogicTreeBase* pLogic);
		bool ProcessSelf();
		bool ProcessChild();
		void Reset(bool bActive = true);
		void ResetChild(bool bActive = true);
		void Active(bool bActive = true){m_bActive = bActive;}
		void ChildFirst(){m_bChildFirst = true;}
		void BrotherFirst(){m_bChildFirst = false;}
		bool IsFinish();
		bool IsSelfFinish(){return m_bselfFinish;}
		bool IsChildFinish(){return m_bChildFinish;}
		void FinishSelf(bool f = true){m_bselfFinish = f;}
		void FinishChild(bool f = true){m_bChildFinish = f;}
		void SetFinish();

		virtual void ReActive();
		virtual void UpdateInput(){}
		virtual int32 GetOutputInt(int32 i){return 0;}
		virtual float GetOutputFloat(int32 i){return 0.0;}
		virtual char* GetOutputChar(int32 i){return NULL;}
		virtual void* GetOutputPtr(int32 i){return NULL;}
		virtual LogicInput* GetInput(int32 i){return NULL;}
		virtual LogicOutput* GetOutput(int32 i){return NULL;}
		void SetLogicGroup(LogicGroup* pLogicGroup){m_pOwnerGroup = pLogicGroup;}
		LogicGroup* GetLogicGroup()const{return m_pOwnerGroup;}
		void SetGroupIndex(int32 i){m_GroupIndex = i;}
		int32 GetGroupIndex()const{return m_GroupIndex;}
		void SetLogicID(int32 i){m_LogicID = i;}
		int32 GetLogicID()const {return m_LogicID;}
		bool LinkInput(int32 i, int32 outLogicIndex, int32 inputIndex);
		void Free();
		bool TerminataLogic();
		LogicInputInfo m_InputInfo[MAX_LOGIC_IN_OUT_PUT];
	protected:
		bool m_bActive;
		bool m_bChildFirst;
		bool m_bselfFinish;
		bool m_bChildFinish;
		LogicGroup* m_pOwnerGroup;
		int32 m_GroupIndex;
		int32 m_LogicID;
		LogicTreeBase* m_prev;
		LogicTreeBase* m_next;
		TList<LogicTreeBase>* m_plist;
		
	private:
	};
}



#endif