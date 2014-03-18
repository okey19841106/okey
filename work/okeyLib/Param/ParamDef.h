/********************************************************************
	created:	2013/06/12
	created:	12-6-2013   20:19
	author:		okey
	
	purpose:	
*********************************************************************/


#ifndef __PARAM_DEF_H__
#define __PARAM_DEF_H__

#include "Types.h"
#include <string>
#include <map>
#include "CircleList.h"
#include "UtilID.h"


namespace okey
{
	class ParamBase;
	class Allocator;

	class ParamDef
	{
		typedef std::map<UtilID, ParamBase*> ParamMap;
		typedef CircleList<ParamBase*,512> ParamList;
	public:
		ParamDef();
		~ParamDef(){}
		bool AddParam(ParamBase* pParam);
		ParamBase* GetParam(int32 index);
		ParamBase* GetParam(const char* name);
		const char* GetName()const {return m_name.c_str();}
		void SetName(const char* name){m_name = name;}
		uint32 GetID()const {return m_cid;}
		void SetID(uint32 pid){m_cid = pid;}
//	int32 GetIndex()const {return m_index;}
// 		void SetIndex(int32 pid){m_index = pid;}
		int32 GetSize()const {return m_poolsize;}
		void SetSize(int32 psize){m_poolsize = psize;}
		int32 GetMaxParamIndex()const {return m_maxindex;}
		int32 GetParamCount()const {return m_count;}
		bool SetBufferAlloc(Allocator* pAlloc);
		Allocator* GetBufferAlloc()const{return m_palloc;}
		char* MakeBuffer();
		void FreeBuffer(char* ptr);

	protected:
		int32 m_poolsize;
//		int32 m_index;
		uint32 m_cid;
		int32 m_maxindex;
		int32 m_count;
		std::string m_name;
		Allocator* m_palloc;
		ParamMap m_pmap;
		ParamList m_plist;
	private:
	};
}

#endif