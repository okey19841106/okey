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

#ifndef __LOGIC_OUT_H__
#define __LOGIC_OUT_H__

#include "Types.h"
#include "LogicConfig.h"

namespace okey
{

	class LogicTreeBase;

	class LogicOutput
	{
	public:
		LogicOutput();
		~LogicOutput();
		inline void SetType(int32 p){m_type = p;}
		inline int32 GetType()const{return m_type;}
		inline int32 GetSize()const{return m_size;}
		inline void SetSize(const int32& n){m_size = n;}
		inline int32 GetOffset()const{return m_offset;}
		inline void SetOffset(const int32&n){m_offset = n;}
		inline int32 GetIndex()const{return m_index;}
		inline void SetIndex(int32 i){m_index = i;}
		int32 GetValue(LogicTreeBase* pLogic, int32 dev) {return 0;}
		float GetValue(LogicTreeBase* pLogic, float dev) {return 0.0;}
		char* GetValue(LogicTreeBase* pLogic, char* dev) {return NULL;}
		void* GetValue(LogicTreeBase* pLogic, void* dev) {return NULL;}
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
	class TLogicOutput : public LogicOutput
	{
		TLogicOutput()
		{
			m_size = sizeof(T);
		}
		T GetValue(LogicTreeBase* pLogic, int32 dev)
		{
			if (!pLogic)
			{
				return dev;
			}
			return *((T*)((char*)pLogic + m_offset));
		}
	};

	class LogicOutput_Int: public LogicOutput
	{
	public:
		LogicOutput_Int()
		{
			m_size = sizeof(int32);
			SetType(Logic_Type_Int);
		}
		~LogicOutput_Int()
		{

		}
		int32 GetValue(LogicTreeBase* pLogic, int32 dev);
	};

	class LogicOutput_Float: public LogicOutput
	{
	public:
		LogicOutput_Float()
		{
			m_size = sizeof(float);
			SetType(Logic_Type_Float);
		}
		~LogicOutput_Float()
		{

		}
		float GetValue(LogicTreeBase* pLogic, float dev);
	};

	class LogicOutput_Char: public LogicOutput
	{
	public:
		LogicOutput_Char(int32 size)
		{
			m_size = size;
			SetType(Logic_Type_Char);
		}
		~LogicOutput_Char()
		{

		}
		char* GetValue(LogicTreeBase* pLogic, char* dev);
	};

	class LogicOutput_Ptr: public LogicOutput
	{
	public:
		LogicOutput_Ptr()
		{
			m_size = sizeof(void*);
			SetType(Logic_Type_Ptr);
		}
		~LogicOutput_Ptr()
		{

		}
		void* GetValue(LogicTreeBase* pLogic, void* dev);
	};

	class LogicOutputManager
	{
	public:
		LogicOutputManager();
		~LogicOutputManager();
		LogicOutput* GetOutput(int32 index);
		int32 GetOutputCount(){return m_outputCount;}
		void Clear();
		bool AddOutput(LogicOutput* pOut);
		int32 GetValue(int32 index,LogicTreeBase* pLogic, int32 dev);
		float GetValue(int32 index,LogicTreeBase* pLogic, float dev); 
		char* GetValue(int32 index,LogicTreeBase* pLogic, char* dev); 
		void* GetValue(int32 index,LogicTreeBase* pLogic, void* dev); 
	private:
		LogicOutput *m_outputList[MAX_LOGIC_IN_OUT_PUT];
		int32 m_outputCount;
	};


}


#endif