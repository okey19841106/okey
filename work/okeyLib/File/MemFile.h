/********************************************************************
	created:	2013/06/16
	created:	16-6-2013   0:14
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __OKEY_MEM_FILE_H__
#define __OKEY_MEM_FILE_H__

#include "FileBase.h"

namespace okey
{
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4>
	class CFunctionArg4Base;

	class MemFile: public FileBase
	{
	public:
		MemFile();
		~MemFile();
		void SetDeCodeFun(CFunctionArg4Base<const char*, int32, const char*, int32&>* pfun){m_DeCodeFun = pfun;}
		virtual bool Open(const char* filename);
		virtual bool ReadLine(char* buffer, int32 len);
		virtual bool IsEnd();
		virtual bool Close();
		const char* GetNextLine(char* pStringBuf, int32 nBufSize, const char* pMemory);
	protected:
		char* m_pMem;
		char* m_startMem;
		char* m_pEndMem;
		CFunctionArg4Base<const char*, int32, const char*, int32&>* m_DeCodeFun; //source, source len, dest, dest len
	};
}



#endif