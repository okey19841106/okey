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
		enum accessMode_t {
		  Read,     /*!< Open file for reading */
		  Write,    /*!< Open file for writing */
		  ReadWrite /*!< Open file for reading and writing */
		};
    
		enum shareMode_t {
		  AllowNone,      /*!< Do'nt allow sharing */
		  AllowRead,      /*!< Allow open for reading */
		  AllowWrite,     /*!< Allow open for writing */
		  AllowReadWrite  /*!< Allow open for read & write */
		};
    
		 enum openMode_t {
		  Normal,   /*!< Normal open - the file pointer is placed at the
						 beginning of the file */
		  Append,   /*!< Open for appending - the file pointer is placed
						 past the end of the file */
		  Truncate  /*!< Truncate the file and place the file
						 pointer at the beginning */
		};

		 enum createMode_t {
			 OpenCreate,   /*!< Open file create if not existent */
			 OpenExisting, /*!< Open existing file, fail if not existent*/
			 CreateFail    /*!< Create and open file, fail if already existent */
		 };

		 enum seekMode_t {
			 seekSet,     /*!< Absolute positioning */
			 seekCurrent, /*!< Relative from current position */
			 seekEnd      /*!< Relative from the end */
		 };

	public:
		static bool IsFileExist(const std::string& filename);
	public:
		FileBase(const std::string& filename): m_FileName(filename){}
		FileBase(){}
		virtual ~FileBase(){}
		
		std::string GetFileName() const {return m_FileName;}
		void SetFileName(const std::string& name){m_FileName = name;}
		bool isFileExist() const{ return IsFileExist(m_FileName);}
//		bool isFileOpen() const {return m_pFile == NULL;}
		
		// SEEK_SET, SEEK_CUR, SEEK_END
// 		void SetPosition(int64 lPos, int32 nType = SEEK_SET) { fseek(m_pFile, lPos, nType); }
// 		int64 GetPosition() const { return (int64)ftell(m_pFile); }
		
	public:
		virtual bool isFileOpen() { return false;}
		virtual void SetPosition(int64 lPos, int32 nType){};
		virtual int64 GetPosition()const {return -1;} 
		virtual bool Open(accessMode_t am, shareMode_t sm, openMode_t om, createMode_t cm){return false;}
		virtual bool Open(const std::string& filename, accessMode_t am, shareMode_t sm, openMode_t om, createMode_t cm){return false;}
		virtual bool ReadLine(char* buffer, int32 len){return false;}
		virtual bool IsEnd() { return false;}
		virtual bool Close();
		virtual bool ReadBuffer(void* pBuffer, uint32 nBufferSize){ return false;}
		virtual bool WriteBufer(const void* pBuffer, uint32 nBuffersize){ return false;}
		virtual void TruncateFile(int64 length){}
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
	//	FILE* m_pFile;
	};

}



#endif