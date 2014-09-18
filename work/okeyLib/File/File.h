/********************************************************************
	created:	2013/06/14
	created:	14-6-2013   16:14
	author:		okey
	
	purpose:	使用底层函数。 文件大小不能超过4G
*********************************************************************/

#ifndef __OKEY_FILE_BASE_H__
#define __OKEY_FILE_BASE_H__

#include "nocopyable.h"
#include <string>


namespace okey
{

	class FileInfo;

	class File
	{
	public:
		enum accessMode_t {
		  acRead,     /*!< Open file for reading */
		  acWrite,    /*!< Open file for writing */
		  acReadWrite /*!< Open file for reading and writing */
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

		 enum posMode_t {
			 posSet,     /*!< Absolute positioning */
			 posCurrent, /*!< Relative from current position */
			 posEnd      /*!< Relative from the end */
		 };

	public:
		static bool IsFileExist(const std::string& filename);
		static void UnLink(const std::string& filename);
		static File CreateTmpFile(const std::string& pername);
		static bool GetFileInfo(const std::string& filename, FileInfo* pFileInfo);
		static void HandleFileError(const std::string filename);
		static void HandleFileError(const std::string filename, int32 err);
	public:
		File(const std::string& filename, accessMode_t access, openMode_t open = Normal,
			createMode_t create = OpenCreate, shareMode_t share = AllowNone);
		File();
		File(const File& f);
		virtual ~File();
	public:
		std::string GetFileName() const {return m_FileName;}
		void SetFileName(const std::string& name){m_FileName = name;}
		bool isFileExist() const{ return IsFileExist(m_FileName);}
	public:
		bool isFileOpen(){ return bool(m_Handle != INVALID_HANDLE_VALUE);}
		int32 SetPosition(int32 lPos, posMode_t pmod);
		int32 GetPosition();
		void Open(const std::string& filename, accessMode_t am, shareMode_t sm = AllowNone, openMode_t om = Normal, createMode_t cm = OpenCreate);
		void Close();
		uint32 ReadBuffer(char* pBuffer, uint32 nBufferSize);
		uint32 WriteBufer(const char* pBuffer, uint32 nBuffersize);
		void TruncateFile(uint32 length);
		bool ReOpen();
		uint32 PeekFile(char* pBuff, uint32 len);
		uint32 GetFileSize();
		void SyncFile();

	protected:
		void setHandle(IOType handle){m_Handle = handle;}
	protected:
		IOType m_Handle;
		std::string m_FileName;
		accessMode_t  m_accessMode;
		openMode_t    m_openMode;
		createMode_t  m_createMode;
		shareMode_t   m_shareMode;
	};

}



#endif