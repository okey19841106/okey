/********************************************************************
	created:	2014/09/10
	created:	15:34
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_FILE_STREAM_H___
#define __OKEY_FILE_STREAM_H___

#include "File.h"
#include <iosfwd>
#include <iostream>

namespace okey
{

	class FileStream : public File, public std::streambuf, public std::iostream
	{
	public:
		FileStream();
		~FileStream();
		FileStream(const std::string& path, accessMode_t access, shareMode_t share = AllowNone, openMode_t open = Normal,
			createMode_t create = OpenCreate);

		FileStream(const FileStream& fs);

		explicit FileStream(const File& f);

		void Close()
		{
			Commit();
			File::Close();
		}

		void Commit()
		{
			sync();
			File::SyncFile();
		}

		FileStream& operator=(const FileStream& fs)
		{
			sync(); 
			flush();
			File::operator=(fs);
			return *this;
		}
	protected:
		int sync();

	protected:
		int uflow();
		int underflow();
		int overflow(int c);

	private:
		void allocate(uint32 size);
		uint32		 m_bufsize;
		char*        m_gbuf;
		char*        m_pbuf;

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