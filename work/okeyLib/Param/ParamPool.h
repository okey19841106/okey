/********************************************************************
	created:	2013/06/12
	created:	12-6-2013   20:17
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __PARAM_POOL_H__
#define __PARAM_POOL_H__

#include "Types.h"
#include "Fuction.h"
#include "ParamBase.h"
#include "ParamDef.h"


namespace okey
{

	class ParamPool;
	typedef CFunctionArg2Base<ParamPool*, int32> ParamFun;

#define PARAM_COUNT_IN_POOL 256
#define PARAM_COUNT_IN_BLOCK	(sizeof(uint32)*8)

#define PARAM_BLOCK_SIZE\
	(PARAM_COUNT_IN_POOL/PARAM_COUNT_IN_BLOCK)


	class ParamPool
	{
	public:
		struct ParamStreamInfo 
		{
			uint32 BlockFlag;
			uint8 BlockIndex;
			static uint32 size(){return sizeof(uint32) + sizeof(uint8);}
		};

		ParamPool();
		ParamPool(ParamDef* pDef);
		~ParamPool();
		void SetParamDef(ParamDef* pDef);
		ParamDef* GetParamDef()const {return m_paramDef;}
		void SetOwner(void* pOwner){m_owner = pOwner;}
		void* GetOwner()const{return m_owner;}
		void SetPreParamFun(ParamFun* fun){PreParamCallFun = fun;}
		void SetPostParamFun(ParamFun* fun){PostParamCallFun = fun;}
		int32 GetParamBufferSize()const {return m_ParamBuffersize;}
		
		bool DirtyCheck();
		bool ClearDirty();
		bool ParamDirtyCheck(int32 index);
		void ClearParamDirty(int32 index);
		void SetParamDirty(int32 index);
		void UpdateTimeGate(int32 delta);
		template<typename T>
		void SetValue(int32 index, const T& val, bool bDirty = true)
		{
			if (!m_paramDef)
			{
				return;
			}
			Param<T>* pParam = (Param<T>*)m_paramDef->GetParam(index);
			if (!pParam)
			{
				return;
			}
			if (PreParamCallFun)
			{
				(*PreParamCallFun)(this, val);
			}
			pParam->SetVal(m_ParamBuffer,(T)val);
			if (PostParamCallFun)
			{
				(*PostParamCallFun)(this, val);
			}
			if (/*pParam->CheckFlag() &&*/ bDirty)
			{
				SetParamDirty(index);
			}
		}
		void SetStringValue(int32 index, const char* val, bool bDirty = true)
		{
			if (!m_paramDef)
			{
				return;
			}
			ParamStr* pParam = (ParamStr*)m_paramDef->GetParam(index);
			if (!pParam)
			{
				return;
			}
			pParam->SetValueString(m_ParamBuffer,val);
			if (/*pParam->CheckFlag() &&*/ bDirty)
			{
				SetParamDirty(index);
			}
		}
		void SetStringValue(const char* name, const char* val, bool bDirty = true)
		{
			if (!m_paramDef)
			{
				return;
			}
			ParamStr* pParam = (ParamStr*)m_paramDef->GetParam(name);
			if (!pParam)
			{
				return;
			}
			
			pParam->SetValueString(m_ParamBuffer,val);
			
			if (/*pParam->CheckFlag() &&*/ bDirty)
			{
				SetParamDirty(pParam->GetIndex());
			}
		}
		template<typename T>
		void SetValue(const char* name, T& val, bool bDirty = true)
		{
			if (!m_paramDef)
			{
				return;
			}
			Param<T>* pParam = (Param<T>*)m_paramDef->GetParam(name);
			if (!pParam)
			{
				return;
			}
			if (PreParamCallFun)
			{
				(*PreParamCallFun)(this, pParam->GetIndex());
			}
			pParam->SetValue(m_ParamBuffer,val);
			if (PostParamCallFun)
			{
				(*PostParamCallFun)(this, pParam->GetIndex());
			}
			if (/*pParam->CheckFlag() &&*/ bDirty)
			{
				SetParamDirty(pParam->GetIndex());
			}
		}

		template<typename T>
		T GetVal(int32 index, const T& defVal)
		{
			if (!m_paramDef)
			{
				return defVal;
			}
			Param<T>* pParam = (Param<T>*)m_paramDef->GetParam(index);
			if (!pParam)
			{
				return defVal;
			}
			return pParam->GetVal(m_ParamBuffer);
		}
		const char* GetStringVal(int32 index, const char* defVal)
		{
			if (!m_paramDef)
			{
				return defVal;
			}
			ParamStr* pParam = (ParamStr*)m_paramDef->GetParam(index);
			if (!pParam)
			{
				return defVal;
			}
			return pParam->GetValueString(m_ParamBuffer);
		}
		const char* GetStringVal(const char* name, const char* defVal)
		{
			if (!m_paramDef)
			{
				return defVal;
			}
			ParamStr* pParam = (ParamStr*)m_paramDef->GetParam(name);
			if (!pParam)
			{
				return defVal;
			}
			return pParam->GetValueString(m_ParamBuffer);
		}
		template<typename T>
		T GetVal(const char* name, const T& defVal)
		{
			if (!m_paramDef)
			{
				return defVal;
			}
			Param<T>* pParam = (Param<T>*)m_paramDef->GetParam(name);
			if (!pParam)
			{
				return defVal;
			}
			return pParam->GetVal(m_ParamBuffer);
		}

		char* Data2Buffer(char* pBuffer);
		char* Buffer2Data(char* pBuffer);

		bool AllocParamBuffer();
		void FreeParamBuffer();

		char* GetParamBuffer()const {return m_ParamBuffer;}
		void SetParamBuffer(char* pBuffer);

		int32 GetDataID()const {return m_InitDataID;}
		void SetDataID(const int32& tid ){m_InitDataID = tid;}

		bool Read(char* pBuffer, bool bDirty = false);
		bool Write(char* pBuffer, int32& nBufSize, int32& nStartPos, uint32 nFlag=0xffffffff, bool bAll = false, bool bClearDirty = false);

		void PrintTheParam();
	protected:
		uint32 DirtyCheck(int32 index);
      	void ClearDirty(int32 index);
		int32 m_InitDataID;
		int32 m_ParamBuffersize;
		char* m_ParamBuffer;
		void* m_owner;
		ParamDef* m_paramDef;
		int32 m_ParamBlockCount;
		uint32 m_ParamBlock[PARAM_BLOCK_SIZE];
		ParamFun* PreParamCallFun;
		ParamFun* PostParamCallFun;
		bool m_bUserBuffer;

	};



}

#endif