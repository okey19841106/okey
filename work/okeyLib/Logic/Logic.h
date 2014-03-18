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
//  created:	2012-2-22 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////


#ifndef __LOGIC_MARCO_H__
#define __LOGIC_MARCO_H__

#include "BaseClass.h"
#include "Logic/LogicTreeBase.h"
#include "Logic/LogicFactory.h"
#include "Logic/LogicInput.h"
#include "Logic/LogicOutput.h"
#include "Logic/LogicManager.h"

namespace okey
{

#define Logic_Factory(classObj)\
	DECLARE_FACTORY_ARG0(classObj, (uint32)UtilID::StringToUtilID(#classObj,strlen(#classObj)), new PoolAllocator<NoLock>(sizeof(classObj)), s_LogicFactoryManager)

#define Logic_Ref_Base(classObj)\
	Logic_Factory(classObj)\
	Reg_Base_Class_BeginEx(classObj,s_ClassLogicManager)

#define Logic_Ref(classObj, classBase)\
	Logic_Factory(classObj)\
	Reg_Class_BeginEx(classObj,classBase,s_ClassLogicManager)

#define Add_Logic_Member(class,member,type,flag,des)\
	Add_Class_Member(class,member,type,flag,des)

#define Logic_Base_Ref_End(classObj)\
	Reg_Base_Class_End(classObj)

#define Logic_Ref_End(classObj,baseclass)\
	Reg_Class_End(classObj,baseclass)

#define Behavior_IO_Begin(classObj)\
public:\
	void UpdateInput(){m_InputManager##classObj.Update((LogicTreeBase*)this);}\
	int32 GetOutputInt(int32 index){return m_OutPutManager##classObj.GetValue(index,(LogicTreeBase*)this,0);}\
	float GetOutputFloat(int32 index){return m_OutPutManager##classObj.GetValue(index,(LogicTreeBase*)this,(float)0.0);}\
	char* GetOutputChar(int32 index){return m_OutPutManager##classObj.GetValue(index,(LogicTreeBase*)this,(char*)NULL);}\
	void* GetOutputPtr(int32 index){return m_OutPutManager##classObj.GetValue(index,(LogicTreeBase*)this,(void*)NULL);}\
	LogicInput* GetInput(int32 index){return m_InputManager##classObj.GetInput(index);}\
	LogicOutput* GetOutput(int32 index){return m_OutPutManager##classObj.GetOutput(index);}\
	LogicInputManager* GetInputManager(){return &m_InputManager##classObj;}\
	LogicOutputManager* GetOutputManager(){return &m_OutPutManager##classObj;}\
protected:\
	static LogicInputManager m_InputManager##classObj;\
	static LogicOutputManager m_OutPutManager##classObj;\
	class cInputOutDeclare_##classObj{\
	public:\
	~cInputOutDeclare_##classObj(){}\
	cInputOutDeclare_##classObj(){\
	m_InputManager##classObj.Clear();\
	m_OutPutManager##classObj.Clear();
	
#define Behavior_IO_End(classObj)\
	}};static cInputOutDeclare_##classObj cInOutPutObj_##classObj;

#define Behavior_IO(classObj)\
	LogicInputManager classObj::m_InputManager##classObj;\
	LogicOutputManager classObj::m_OutPutManager##classObj;\
	classObj::cInputOutDeclare_##classObj classObj::cInOutPutObj_##classObj;

#define Logic_IMPL(classObj)\
	FINISH_FACTORY_ARG0(classObj);\
	Reg_Class_Initial(classObj);\
	Behavior_IO(classObj);

#define Reg_Input(classObj,member,type,des)\
	TLogicInput<type>* pInt_##member = new TLogicInput<type>();\
	pInt_##member->SetSize(sizeof(member));\
	pInt_##member->SetOffset(static_cast<int32>(reinterpret_cast<int64>((&((classObj*)(0))->member))));\
	pInt_##member->SetName(#member);\
	pInt_##member->SetDes(#des);\
	m_InputManager##classObj.AddInput(pInt_##member);

#define Reg_Input_Int(classObj,member,type,des)\
	LogicInput_Int *pInt_##member_##int = new LogicInput_Int();\
	pInt_##member_##int->SetOffset(static_cast<int32>(reinterpret_cast<int64>((&((classObj*)(0))->member))));\
	pInt_##member_##int->SetName(#member);\
	pInt_##member_##int->SetDes(#des);\
	m_InputManager##classObj.AddInput(pInt_##member_##int);

#define Reg_Input_Float(classObj,member,type,des)\
	LogicInput_Float *pInt_##member_##float = new LogicInput_Float();\
	pInt_##member_##float->SetOffset(static_cast<int32>(reinterpret_cast<int64>((&((classObj*)(0))->member))));\
	pInt_##member_##float->SetName(#member);\
	pInt_##member_##float->SetDes(#des);\
	m_InputManager##classObj.AddInput(pInt_##member_##float);

#define Reg_Input_Char(classObj,member,size,des)\
	LogicInput_Char *pInt_##member_##char = new LogicInput_Char(size);\
	pInt_##member_##char->SetOffset(static_cast<int32>(reinterpret_cast<int64>((&((classObj*)(0))->member))));\
	pInt_##member_##char->SetName(#member);\
	pInt_##member_##char->SetDes(#des);\
	m_InputManager##classObj.AddInput(pInt_##member_##char);

#define Reg_Input_Ptr(classObj,member,type,des)\
	LogicInput_Ptr *pInt_##member_##ptr = new LogicInput_Ptr();\
	pInt_##member_##ptr->SetOffset(static_cast<int32>(reinterpret_cast<int64>((&((classObj*)(0))->member))));\
	pInt_##member_##ptr->SetName(#member);\
	pInt_##member_##ptr->SetDes(#des);\
	m_InputManager##classObj.AddInput(pInt_##member_##ptr);

#define Reg_Output(classObj,member,type,des)\
	LogicOutput<type>* pInt_##member = new LogicOutput<type>();\
	pOut_##member->SetSize(sizeof(member));\
	pOut_##member->SetOffset(static_cast<int32>(reinterpret_cast<int64>((&((classObj*)(0))->member))));\
	pOut_##member->SetName(#member);\
	pOut_##member->SetDes(#des);\
	m_OutPutManager##classObj.AddOutput(pInt_##member);

#define Reg_Output_Int(classObj,member,type,des)\
	LogicOutput_Int *pOut_##member_##int = new LogicOutput_Int();\
	pOut_##member_##int->SetOffset(static_cast<int32>(reinterpret_cast<int64>((&((classObj*)(0))->member))));\
	pOut_##member_##int->SetName(#member);\
	pOut_##member_##int->SetDes(#des);\
	m_OutPutManager##classObj.AddOutput(pOut_##member_##int);

#define Reg_Output_Float(classObj,member,type,des)\
	LogicOutput_Float *pOut_##member_##float = new LogicOutput_Float();\
	pOut_##member_##float->SetOffset(static_cast<int32>(reinterpret_cast<int64>((&((classObj*)(0))->member))));\
	pOut_##member_##float->SetName(#member);\
	pOut_##member_##float->SetDes(#des);\
	m_OutPutManager##classObj.AddOutput(pOut_##member_##float);

#define Reg_Output_Char(classObj,member,size,des)\
	LogicOutput_Char *pOut_##member_##char = new LogicOutput_Char(size);\
	pOut_##member_##char->SetOffset(static_cast<int32>(reinterpret_cast<int64>((&((classObj*)(0))->member))));\
	pOut_##member_##char->SetName(#member);\
	pOut_##member_##char->SetDes(#des);\
	m_OutPutManager##classObj.AddOutput(pOut_##member_##char);

#define Reg_Output_Ptr(classObj,member,type,des)\
	LogicOutput_Ptr *pOut_##member_##ptr = new LogicOutput_Ptr();\
	pOut_##member_##ptr->SetOffset(static_cast<int32>(reinterpret_cast<int64>((&((classObj*)(0))->member))));\
	pOut_##member_##ptr->SetName(#member);\
	pOut_##member_##ptr->SetDes(#des);\
	m_OutPutManager##classObj.AddOutput(pOut_##member_##ptr);


}

#endif