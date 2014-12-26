/********************************************************************
	created:	2014/12/24
	created:	16:09
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __FILE_STREAM_BUF_H__
#define __FILE_STREAM_BUF_H__

#include <istream>
#include <ostream>
#include "BufferedBidirectionalStreamBuf.h"
#include "File/File.h"

namespace okey
{
	class FileStreamBuf: public BufferedBidirectionalStreamBuf
	{
	public:
		FileStreamBuf();
		~FileStreamBuf();

		void open(const std::string& path, File::accessMode_t access, File::shareMode_t share, 
			File::openMode_t open, File::createMode_t create);
		bool close();
		std::streampos seekoff(std::streamoff off, std::ios::seekdir dir, std::ios::openmode mode = std::ios::in | std::ios::out);
		std::streampos seekpos(std::streampos pos, std::ios::openmode mode = std::ios::in | std::ios::out);
	protected:
		enum
		{
			BUFFER_SIZE = 4096
		};

		int readFromDevice(char* buffer, std::streamsize length);
		int writeToDevice(const char* buffer, std::streamsize length);
	private:
		File _file;
		std::streamoff _pos;
	};
	
}

#endif