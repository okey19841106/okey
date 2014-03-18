/********************************************************************
	created:	2013/06/14
	created:	14-6-2013   16:14
	author:		okey
	
	purpose:	为了不同的文件读取。
*********************************************************************/

#ifndef __OKEY_FILE_BASE_H__
#define __OKEY_FILE_BASE_H__

#include "nocopyable.h"

namespace okey
{
	class FileBase : public nocopyable
	{
	public:
		FileBase():m_pFile(NULL){}
		virtual ~FileBase(){}
		virtual bool Open(const char* filename) = 0;
		virtual bool ReadLine(char* buffer, int32 len) = 0;
		virtual bool IsEnd() = 0;
		virtual bool Close() = 0;
// 		virtual bool OpenFromMemory(const char* pStart, const char* pEnd, const char* filename); //主要是为了加密与解密用的。
// 		virtual const char* GetLineFromMemory(char* pStringBuf, int32 nBufSize, const char* pMemory, const char* pDeadEnd);
	protected:
		FILE* m_pFile;
// 		char* m_pMem;
// 		char* m_startMem;
// 		char* m_pEndMem;
	};
}



#endif