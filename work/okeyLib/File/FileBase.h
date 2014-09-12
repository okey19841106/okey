/********************************************************************
	created:	2013/06/14
	created:	14-6-2013   16:14
	author:		okey
	
	purpose:	为了不同的文件读取。
*********************************************************************/

#ifndef __OKEY_FILE_BASE_H__
#define __OKEY_FILE_BASE_H__

#include "nocopyable.h"
#include <string>

namespace okey
{
	class FileBase : public nocopyable
	{
	
	public:
		static bool IsFileExist(const std::string& filename);
	public:
		FileBase(const std::string& filename): m_FileName(filename){}
		FileBase():m_pFile(NULL){}
		virtual ~FileBase(){}
		
		std::string GetFileName() const {return m_FileName;}
		void SetFileName(const std::string& name){m_FileName = name;}
		bool isFileExist() const{ return IsFileExist(m_FileName);}
		bool isFileOpen() const {return m_pFile == NULL;}
		
		// SEEK_SET, SEEK_CUR, SEEK_END
		void SetPosition(int64 lPos, int32 nType = SEEK_SET) { fseek(m_pFile, lPos, nType); }
		int64 GetPosition() const { return (int64)ftell(m_pFile); }
		
	public:
		virtual bool Open(){return false;}
		virtual bool Open(const std::string& filename){return false;}
		virtual bool ReadLine(char* buffer, int32 len){return false;}
		virtual bool IsEnd() { return feof(m_pFile);}
		virtual bool Close();
		virtual bool ReadBuffer(void* pBuffer, uint32 nBufferSize){ return false;}
		virtual bool WriteBufer(const void* pBuffer, uint32 nBuffersize){ return false;}
		
	public:
		template<typename T> 
		bool Read(T& data)
		{
			return ReadBuffer((void*)&data, sizeof(T));
		}

		template<typename T>
		bool Write(const T& data)
		{
			return WriteBufer((void*)&data, sizeof(T));
		}
	protected:
		std::string m_FileName;
		FILE* m_pFile;
	};

}



#endif