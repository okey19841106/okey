#include "PreCom.h"
#include "FileStream.h"


namespace okey
{
	FileIOS::FileIOS()
	{

	}

	FileIOS::~FileIOS()
	{

	}

	void FileIOS::open(const std::string& path, File::accessMode_t access, File::shareMode_t share, 
		File::openMode_t open, File::createMode_t create)
	{
		clear();
		_buf.open(path, access,share,open,create);
	}

	void FileIOS::close()
	{
		if (!_buf.close())
		{
			setstate(ios_base::badbit);
		}
	}

	FileStreamBuf* FileIOS::rdbuf()
	{
		return &_buf;
	}

	FileInputStream::FileInputStream():std::istream(&_buf)
	{

	}

	FileInputStream::FileInputStream(const std::string& path, File::shareMode_t share, 
		File::openMode_t open, File::createMode_t create ): std::istream(&_buf)
	{
		FileIOS::open(path, File::acRead,share, open, create);
	}

	FileInputStream::~FileInputStream()
	{

	}

	FileOutputStream::FileOutputStream():std::ostream(&_buf)
	{

	}

	FileOutputStream::FileOutputStream(const std::string& path, File::shareMode_t share, 
		File::openMode_t open, File::createMode_t create ): std::ostream(&_buf)
	{
		FileIOS::open(path, File::acWrite,share, open, create);
	}

	FileOutputStream::~FileOutputStream()
	{

	}

	FileStream::FileStream():std::iostream(&_buf)
	{

	}

	FileStream::FileStream(const std::string& path, File::shareMode_t share, 
		File::openMode_t open, File::createMode_t create ): std::iostream(&_buf)
	{
		FileIOS::open(path, File::acReadWrite,share, open, create);
	}

	FileStream::~FileStream()
	{

	}
}