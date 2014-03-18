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

#ifndef __LOGIC_INPUT_H__
#define __LOGIC_INPUT_H__

#include "Types.h"
#include "LogicConfig.h"

namespace okey
{

	class LogicTreeBase;

	class LogicInput
	{
	public:
		LogicInput();
		~LogicInput();
		virtual bool Update(LogicTreeBase* pInlogic, LogicTreeBase* pOutLogic, 
			int32 nLinkedOutIndex) = 0;
		inline void SetType(int32 p){m_type = p;}
		inline int32 GetType()const{return m_type;}
		inline int32 GetSize()const{return m_size;}
		inline void SetSize(const int32& n){m_size = n;}
		inline int32 GetOffset()const{return m_offset;}
		inline void SetOffset(const int32&n){m_offset = n;}
		inline int32 GetIndex()const{return m_index;}
		inline void SetIndex(int32 i){m_index = i;}
		inline void SetName(const char* name){m_name = name;}
		inline const char* GetName(){return m_name.c_str();}
		inline void SetDes(const char* des){m_des = des;}
		inline const char* GetDes(){return m_des.c_str();}
	protected:
		int32 m_type;
		int32 m_index;
		int32 m_offset;
		int32 m_size;
		std::string m_name;
		std::string m_des;
	};

	template<typename T>
	class TLogicInput: public LogicInput
	{
	public:
		TLogicInput()
		{
			m_size = sizeof(T);	
		}
		~TLogicInput()
		{

		}
		bool Update(LogicTreeBase* pInlogic, LogicTreeBase* pOutLogic, 
			int32 nLinkedOutIndex)
		{
			if (!pInlogic || !pOutLogic || nLinkedOutIndex > MAX_LOGIC_IN_OUT_PUT ||
				nLinkedOutIndex < 0)
			{
				return false;
			}
			LogicOutput* pOutput = pOutLogic->GetOutput(nLinkedOutIndex);
			if (!pOutput)
			{
				return false;
			}
			int32 tsize = (m_size < pOutput->GetSize())?m_size:pOutput->GetSize();
			memcpy((char*)pInlogic + m_offset, (char*)pOutLogic + pOutput->GetOffset(), tsize);
		}
	protected:
	private:
	};

	class LogicInput_Int: public LogicInput
	{
	public:
		LogicInput_Int()
		{
			m_size = sizeof(int32);
			SetType(Logic_Type_Int);
		}
		~LogicInput_Int()
		{

		}
		bool Update(LogicTreeBase* pInlogic, LogicTreeBase* pOutLogic, 
			int32 nLinkedOutIndex);
	};

	class LogicInput_Float: public LogicInput
	{
	public:
		LogicInput_Float()
		{
			m_size = sizeof(float);
			SetType(Logic_Type_Float);
		}
		~LogicInput_Float()
		{

		}
		bool Update(LogicTreeBase* pInlogic, LogicTreeBase* pOutLogic, 
			int32 nLinkedOutIndex);
	};

	class LogicInput_Char: public LogicInput
	{
	public:
		LogicInput_Char()
		{
			m_size = 0;
			SetType(Logic_Type_Char);
		}
		LogicInput_Char(int32 size)
		{
			m_size = size;
			SetType(Logic_Type_Char);
		}
		~LogicInput_Char()
		{

		}
		bool Update(LogicTreeBase* pInlogic, LogicTreeBase* pOutLogic, 
			int32 nLinkedOutIndex);
	};

	class LogicInput_Ptr: public LogicInput
	{
	public:
		LogicInput_Ptr()
		{
			m_size = sizeof(void*);
			SetType(Logic_Type_Ptr);
		}
		~LogicInput_Ptr()
		{

		}
		bool Update(LogicTreeBase* pInlogic, LogicTreeBase* pOutLogic, 
			int32 nLinkedOutIndex);
	};

	class LogicInputManager
	{
	public:
		LogicInputManager();
		~LogicInputManager();
		LogicInput* GetInput(int32 index);
		int32 GetInputCount(){return m_inputCount;}
		bool Update(LogicTreeBase* pLogic);
		void Clear();
		bool AddInput(LogicInput* pInput);
	private:
		LogicInput* m_inputList[MAX_LOGIC_IN_OUT_PUT];
		int32 m_inputCount;
	};


}


#endif