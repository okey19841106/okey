/********************************************************************
	created:	2013/06/13
	created:	13-6-2013   0:32
	author:		okey
	
	purpose:	
*********************************************************************/


#ifndef __CFG_LOADER_ALL_H__
#define __CFG_LOADER_ALL_H__

#include "Types.h"
#include <vector>
#include <map>

namespace okey
{
	typedef std::vector<std::string> LabelVector;
	typedef std::vector<std::string> ValueVector;
	typedef std::vector<ValueVector> AllValue;
	typedef std::map<std::string, int32> StringMap;

	class FileBase;

	class CfgLoaderBase
	{
	public:
		CfgLoaderBase(FileBase* pFile):m_pFile(pFile){}
		~CfgLoaderBase(){}
		virtual bool Load(const char* pFileName){return false;}
		virtual bool GetLabel(LabelVector& vlist){return false;}
		virtual bool GetValueList(int32 index, ValueVector& vlist){return false;}
		virtual void Clear(){}
		virtual int32 GetColCount(){return 0;}
		virtual int32 GetLineCount(){return 0;}
		virtual int32 GetIndexByName(const std::string& name){return -1;}
	protected:
		FileBase* m_pFile;
	};

	class CfgLoaderStream: public CfgLoaderBase
	{
	public:
		CfgLoaderStream(FileBase* pFile);
		~CfgLoaderStream();
		virtual bool Load(const char* pFileName);
		virtual bool GetLabel(LabelVector& vlist);
		virtual bool GetValueList(int32 index, ValueVector& vlist);
		virtual void Clear();
		virtual int32 GetColCount(){return m_label.size();}
		virtual int32 GetLineCount(){return m_value.size();}
	protected:
	private:
		LabelVector m_label;
		AllValue m_value;
		StringMap m_StringMap;
	};
}


#endif