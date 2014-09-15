/********************************************************************
	created:	2013/06/16
	created:	16-6-2013   16:03
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __OKEY_NORMAL_FILE_H__
#define __OKEY_NORMAL_FILE_H__

#include "FileBase.h"

namespace okey
{
	

	class FFile: public FileBase
	{
	public:
		FFile(const std::string& name);
		FFile();
		~FFile();
		virtual bool isFileOpen();
		virtual void SetPosition(int64 lPos, int32 nType);
		virtual int64 GetPosition()const;
		virtual bool Open(accessMode_t am, shareMode_t sm, openMode_t om, createMode_t cm);
		virtual bool Open(const std::string& filename, accessMode_t am, shareMode_t sm, openMode_t om, createMode_t cm);
		virtual bool ReadLine(char* buffer, int32 len);
		virtual bool ReadBuffer(void* pBuffer, uint32 nBufferSize);
		virtual bool WriteBufer(const void* pBuffer, uint32 nBuffersize);
		virtual void TruncateFile(int64 length){}
	protected:
		FILE* m_pFile;
	};
}


#endif