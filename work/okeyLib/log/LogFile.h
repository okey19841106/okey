/********************************************************************
	created:	2015/07/13
	created:	14:40
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_LOG_FILE_H__
#define __BASE_LOG_FILE_H__

#include "TimeStamp.h"
#include "Stream/FileStream.h"

namespace okey
{

	class LogFile
	{
	public:
		LogFile(const std::string& path);
		~LogFile();
		void WriteLog(const std::string& text, bool flush = true);
		inline uint64 GetSize() const{ return (uint64)_str.tellp();}
		inline TimeStamp CreationDate() const{ return _creationDate;}
		inline const std::string& GetPath() const{return _path;}
	private:
		std::string _path;
		mutable FileOutputStream _str;
		TimeStamp _creationDate;
	};

}

#endif