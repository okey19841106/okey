/********************************************************************
	created:	2013/06/18
	created:	18-6-2013   23:48
	author:		okey
	
	purpose:	
*********************************************************************/


#ifndef __PARAM_BASE_H__
#define __PARAM_BASE_H__

#include "Types.h"
#include "AnyTypeBase.h"

namespace okey
{
	
	class ParamBase
	{
	public:
		ParamBase(){
			m_id = 0;
			m_index = 0;
			m_flag = 0;
		//	m_timegate = 0;
		}
		virtual ~ParamBase(){}
		virtual int32 GetOffset()const = 0;
		virtual void SetOffset(int32 offset) = 0;
		virtual const char* GetName() = 0;
		virtual void SetName(const char* s) = 0;
		virtual bool TypeCheck(const std::type_info& type) = 0;
		uint32 GetID()const {return m_id;}
		void SetID(uint32 pid){m_id = pid;}
		void SetFlag(uint32 flag){m_flag = flag;}
		bool CheckFlag(uint32 flag){return m_flag&flag;}
		virtual char* ParamRead(char* pParamBuff, char* pbuff) = 0;
		virtual char* ParamWirte(char* pParamBuff, char* pbuff) = 0;
		virtual int32 GetParamSize() = 0;
		virtual void SetParamSize(int32 size) = 0;
		uint32 GetIndex(){return m_index;}
		void SetIndex(uint32 i){m_index = i; }
	protected:
		uint32 m_id;
		uint32 m_index;
		uint32 m_flag;
		/*int32 m_timegate;*/
	private:
	};


	template<typename T>
	class Param: public ParamBase,public CClassMember<T>
	{
	public:
		Param(){
//			m_timegateoffset = -1;
		}
		virtual ~Param(){};
		void SetValue(void* pClassObj,T& val)
		{
			if (!CClassMember<T>::CheckType(typeid(T)))
			{
				return;
			}
			if (val > m_max)
			{
				val = m_max;
			}
			else if (val < m_min)
			{
				val = m_min;
			}
			CClassMember<T>::SetValue(pClassObj,val);
		}

		char* ParamRead(char* pParamBuff, char* pbuff)
		{
			if (!pParamBuff || !pbuff)
			{
				return NULL;
			}
			return CClassMember<T>::Read(pParamBuff,pbuff);
		}
		char* ParamWirte(char* pParamBuff, char* pbuff)
		{
			if (!pParamBuff || !pbuff)
			{
				return NULL;
			}
			return CClassMember<T>::Write(pParamBuff,pbuff);
		}
		virtual int32 GetOffset()const
		{
			return CClassMember<T>::GetOffset();
		}
		virtual void SetOffset(int32 offset)
		{
			CClassMember<T>::SetOffset(offset);
		}
		virtual bool TypeCheck(const std::type_info& type)
		{
			return CClassMember<T>::CheckType(type);
		}
		virtual const char* GetName()
		{
			return CClassMember<T>::GetName();
		}
		virtual void SetName(const char* s)
		{
			CClassMember<T>::SetName(s);
		}
		virtual int32 GetParamSize()
		{
			return CClassMember<T>::GetSize();
		}
		virtual void SetParamSize(int32 size)
		{
			CClassMember<T>::SetSize(size);
		}
		void SetMaxValue(const T& tMax){m_max = tMax;}
		void SetMinValue(const T& tMin){m_min = tMin;}
	protected:
		T m_max;
		T m_min;
	private:
	};

	template<typename T>
	class ParamClass: public ParamBase, CClassMember_Class<T>
	{
	public:
		ParamClass()
		{
			/*m_timegateoffset = -1;*/
		}
		virtual ~ParamClass(){};

		char* ParamRead(char* pParamBuff, char* pbuff)
		{
			if (!pParamBuff || !pbuff)
			{
				return NULL;
			}
			return CClassMember_Class<T>::Read(pParamBuff,pbuff);
		}
		char* ParamWirte(char* pParamBuff, char* pbuff)
		{
			if (!pParamBuff || !pbuff)
			{
				return NULL;
			}
			return CClassMember_Class<T>::Write(pParamBuff,pbuff);
		}
		virtual int32 GetOffset()const
		{
			return CClassMember_Class<T>::GetOffset();
		}
		virtual void SetOffset(int32 offset)
		{
			CClassMember_Class<T>::SetOffset(offset);
// 			if (IsTimeGateParam())
// 			{
// 				m_timegateoffset = offset + CClassMember_Class<T>::GetSize();
// 			}
		}
		virtual bool TypeCheck(const std::type_info& type)
		{
			return CClassMember_Class<T>::CheckType(type);
		}
		virtual const char* GetName()
		{
			return CClassMember_Class<T>::GetName();
		}
		virtual void SetName(const char* s)
		{
			CClassMember_Class<T>::SetName(s);
		}
		virtual int32 GetParamSize()
		{
			return CClassMember_Class<T>::GetSize();
		}
		virtual void SetParamSize(int32 size)
		{
			CClassMember_Class<T>::SetSize(size);
		}
	private:
	};

	
	class ParamStr: public ParamBase, CClassMember_String
	{
	public:
		ParamStr(){
			/*m_timegateoffset = -1;*/
		}
		ParamStr(uint8 nSize):CClassMember_String(nSize){}
		virtual ~ParamStr(){};
		void SetValueString(void* pClassObj,const char* val)
		{
			CClassMember_String::SetValue(pClassObj,val);
		}

		const char* GetValueString(void* pClassObj)
		{
			return CClassMember_String::GetValue(pClassObj);
		}

		char* ParamRead(char* pParamBuff, char* pbuff)
		{
			if (!pParamBuff || !pbuff)
			{
				return NULL;
			}
			return CClassMember_String::Read(pParamBuff,pbuff);
		}
		char* ParamWirte(char* pParamBuff, char* pbuff)
		{
			if (!pParamBuff || !pbuff)
			{
				return NULL;
			}
			return CClassMember_String::Write(pParamBuff,pbuff);
		}
		virtual int32 GetOffset()const
		{
			return CClassMember_String::GetOffset();
		}
		virtual void SetOffset(int32 offset)
		{
			CClassMember_String::SetOffset(offset);
// 			if (IsTimeGateParam())
// 			{
// 				m_timegateoffset = offset + CClassMember_String::GetSize();
// 			}
		}
		virtual bool TypeCheck(const std::type_info& type)
		{
			return CClassMember_String::CheckType(type);
		}
		virtual const char* GetName()
		{
			return CClassMember_String::GetName();
		}
		virtual void SetName(const char* s)
		{
			CClassMember_String::SetName(s);
		}
		virtual int32 GetParamSize()
		{
			return CClassMember_String::GetSize();
		}
		virtual void SetParamSize(int32 size)
		{
			CClassMember_String::SetSize(size);
		}
// 		virtual bool CheckTimeGate(char* pParamBuff)
// 		{
// 			if (!pParamBuff || -1 == m_timegateoffset)
// 			{
// 				return true;
// 			}
// 			int32* pCurTime = (int32*)(pParamBuff + m_timegateoffset);
// 			if ((*pCurTime) >= m_timegate)
// 			{
// 				return true;
// 			}
// 			return false;
// 		}
// 		virtual void UpdateTimeGate(char* pParamBuff, int32 deltaTime)
// 		{
// 			if (!pParamBuff || -1 == m_timegateoffset)
// 			{
// 				return;
// 			}
// 			int32* pCurTime = (int32*)(pParamBuff + m_timegateoffset);
// 			(*pCurTime) += deltaTime;
// 		}
// 		virtual void ResetTimeGate(char* pParamBuff)
// 		{
// 			if (!pParamBuff || -1 == m_timegateoffset)
// 			{
// 				return;
// 			}
// 			int32* pCurTime = (int32*)(pParamBuff + m_timegateoffset);
// 			(*pCurTime) += 0;
// 		}
	protected:
		/*int32 m_timegateoffset;*/
	private:
	};




}



#endif