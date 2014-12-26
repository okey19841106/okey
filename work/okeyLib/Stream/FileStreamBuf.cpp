#include "PreCom.h"
#include "FileStreamBuf.h"


namespace okey
{

	FileStreamBuf::FileStreamBuf():BufferedBidirectionalStreamBuf(BUFFER_SIZE, std::ios::in | std::ios::out),_pos(0)
	{

	}

	FileStreamBuf::~FileStreamBuf()
	{
		close();
	}

	void FileStreamBuf::open(const std::string& path, File::accessMode_t access, File::shareMode_t share = File::AllowNone, 
		File::openMode_t open = File::Normal, File::createMode_t create = File::OpenCreate)
	{
		resetBuffers();
		_file.Open(path,access,share,open,create);
	}

	bool FileStreamBuf::close()
	{
		bool success = true;
		if (_file.isFileOpen())
		{
			try
			{
				sync();
			}
			catch (...)
			{
				success = false;
			}
			_file.Close();
		}
		return success;
		
	}
	std::streampos FileStreamBuf::seekoff(std::streamoff off, std::ios::seekdir dir, std::ios::openmode mode )
	{
		if(!_file.isFileOpen())
			return -1;
		if (_file.GetShareMode() == File::AllowWrite || _file.GetShareMode() == File::AllowReadWrite)
		{
			sync();
		}
		std::streamoff adj;
		if (mode & std::ios::in)
			adj = static_cast<std::streamoff>(egptr() - gptr());
		else
			adj = 0;
		resetBuffers();
		File::posMode_t offset = File::posSet;
		if (dir == std::ios::cur)
		{
			offset = File::posCurrent;
			off -= adj;
		}
		else if (dir == std::ios::end)
		{
			offset = File::posEnd;
		}
		_pos = _file.SetPosition(off, offset);
		return _pos;
	}

	std::streampos FileStreamBuf::seekpos(std::streampos pos, std::ios::openmode mode)
	{
		if(!_file.isFileOpen())
			return -1;
		if (_file.GetShareMode() == File::AllowWrite || _file.GetShareMode() == File::AllowReadWrite)
		{
			sync();
		}
		resetBuffers();
		_pos = _file.SetPosition(pos, File::posSet);
		return _pos;
	}

	int FileStreamBuf::readFromDevice(char* buffer, std::streamsize length)
	{
		if ((!_file.isFileOpen()) || (_file.GetShareMode() == File::AllowWrite))
			return -1;
		if ( _file.GetShareMode() == File::AllowReadWrite)
		{
			sync();
		}
		uint32 bytesRead = _file.ReadBuffer(buffer,(uint32)length);
		_pos += bytesRead;
		return static_cast<int>(bytesRead);
	}

	int FileStreamBuf::writeToDevice(const char* buffer, std::streamsize length)
	{
		if ((!_file.isFileOpen()) || (_file.GetShareMode() == File::AllowRead))
			return -1;
		if (_file.GetOpenMode() == File::Append)
		{
			_pos = _file.SetPosition(0, File::posEnd);
		}
		uint32 bytesWritten = _file.WriteBufer(buffer,(uint32)length);
		_pos += bytesWritten;
		return static_cast<int>(bytesWritten);
	}
}