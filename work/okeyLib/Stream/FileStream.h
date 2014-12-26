/********************************************************************
	created:	2014/12/25
	created:	15:06
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __FILE_STREAM_H__
#define __FILE_STREAM_H__

#include <istream>
#include <ostream>
#include "FileStreamBuf.h"


namespace okey
{
	class FileStreamBuf;

	class FileIOS: public virtual std::ios
	{
	public:
		FileIOS();
		~FileIOS();
		void open(const std::string& path, File::accessMode_t access, File::shareMode_t share = File::AllowNone, 
			File::openMode_t open = File::Normal, File::createMode_t create = File::OpenCreate);
		void close();
		FileStreamBuf* rdbuf();
	protected:
		FileStreamBuf _buf;
		std::ios::openmode _defauleMode;
	};

	class FileInputStream: public FileIOS, public std::istream
	{
	public:
		FileInputStream();
		FileInputStream(const std::string& path, File::shareMode_t share = File::AllowNone, 
			File::openMode_t open = File::Normal, File::createMode_t create = File::OpenCreate);
		~FileInputStream();
	};

	class FileOutputStream: public FileIOS, public std::ostream
	{
	public:
		FileOutputStream();
		FileOutputStream(const std::string& path, File::shareMode_t share = File::AllowNone, 
			File::openMode_t open = File::Normal, File::createMode_t create = File::OpenCreate);
		~FileOutputStream();
	};

	class FileStream: public FileIOS, public std::iostream
	{
	public:
		FileStream();
		FileStream(const std::string& path, File::shareMode_t share = File::AllowNone, 
			File::openMode_t open = File::Normal, File::createMode_t create = File::OpenCreate);
		~FileStream();
	};

	inline std::ostream& pendl(std::ostream& os)
	{
#ifdef WINDOWS
		os << "\r\n";
#else
		os << "\n";
#endif
		os << std::flush;
		return os;
	}
}

#endif