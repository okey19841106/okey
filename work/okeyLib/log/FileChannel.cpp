#include "PreCom.h"
#include "FileChannel.h"
#include "ArchiveStrategy.h"
#include "PurgeStrategy.h"
#include "RotateStrategy.h"
#include "LogFile.h"
#include "Message.h"
#include "Exception.h"
#include "StringHelper.h"
#include "AsciiCharacter.h"

namespace okey
{

	const std::string FileChannel::PROP_PATH         = "path";
	const std::string FileChannel::PROP_ROTATION     = "rotation";
	const std::string FileChannel::PROP_ARCHIVE      = "archive";
	const std::string FileChannel::PROP_TIMES        = "times";
	const std::string FileChannel::PROP_COMPRESS     = "compress";
	const std::string FileChannel::PROP_PURGEAGE     = "purgeAge";
	const std::string FileChannel::PROP_PURGECOUNT   = "purgeCount";
	const std::string FileChannel::PROP_FLUSH        = "flush";
	const std::string FileChannel::PROP_ROTATEONOPEN = "rotateOnOpen";

	FileChannel::FileChannel():_compress(false),_flush(true),_rotateOnOpen(false),
		_pFile(NULL),_pRotateStrategy(NULL),_pArchiveStrategy(new ArchiveByNumberStrategy),
		_pPurgeStrategy(NULL)
	{

	}

	FileChannel::FileChannel(const std::string& path):_path(path),_compress(false),_flush(true),_rotateOnOpen(false),
		_pFile(NULL),_pRotateStrategy(NULL),_pArchiveStrategy(new ArchiveByNumberStrategy),
		_pPurgeStrategy(NULL)
	{

	}

	FileChannel::~FileChannel()
	{
		Close();
		if (_pRotateStrategy)
		{
			delete _pRotateStrategy;
		}
		if (_pArchiveStrategy)
		{
			delete _pArchiveStrategy;
		}
		if (_pPurgeStrategy)
		{
			delete _pPurgeStrategy;
		}
	}
	void FileChannel::Open()
	{
		FastMutex::ScopedLock lock(_mutex);
		if (!_pFile)
		{
			_pFile = new LogFile(_path);
			if (_rotateOnOpen && _pFile->GetSize() > 0)
			{
				try
				{
					_pFile = _pArchiveStrategy->Archive(_pFile);
					purge();
				}
				catch(...)
				{
					_pFile = new LogFile(_path);
				}
			}
		}
		
	}

	void FileChannel::Close()
	{
		FastMutex::ScopedLock lock(_mutex);
		if (_pFile)
		{
			delete _pFile;
			_pFile = NULL;
		}
		
	}

	void FileChannel::Log(const Message& msg)
	{
		Open();
		FastMutex::ScopedLock lock(_mutex);
		if (_pRotateStrategy && _pArchiveStrategy && _pRotateStrategy->MustRotate(_pFile))
		{
			try
			{
				_pFile = _pArchiveStrategy->Archive(_pFile);
				purge();
			}
			catch(...)
			{
				_pFile = new LogFile(_path);
			}
			_pRotateStrategy->MustRotate(_pFile);
		}
		_pFile->WriteLog(msg.GetText(), _flush);
	}

	void FileChannel::SetProperty(const std::string& name, const std::string& value)
	{
		FastMutex::ScopedLock lock(_mutex);
		if (name == PROP_TIMES)
		{
			_times = value;
			if (!_rotation.empty())
			{
				setRotation(_rotation);
			}
			if (!_archive.empty())
			{
				setArchive(_archive);
			}
		}
		else if (name == PROP_PATH)
		{
			_path = value;
		}
		else if (name == PROP_ROTATION)
		{
			setRotation(value);
		}
		else if (name == PROP_ARCHIVE)
		{
			setArchive(value);
		}
		else if (name == PROP_COMPRESS)
		{
			setCompress(value);
		}
		else if (name == PROP_PURGEAGE)
		{
			setPurgeAge(value);
		}
		else if (name == PROP_PURGECOUNT)
		{
			setPurgeCount(value);
		}
		else if (name == PROP_FLUSH)
		{
			setFlush(value);
		}
		else if (name == PROP_ROTATEONOPEN)
		{
			setRotateOnOpen(value);
		}
		else
		{
			Channel::SetProperty(name,value);
		}
		
	}

	std::string FileChannel::GetProperty(const std::string& name) const
	{
		if (name == PROP_TIMES)
			return _times;
		else if (name == PROP_PATH)
			return _path;
		else if (name == PROP_ROTATION)
			return _rotation;
		else if (name == PROP_ARCHIVE)
			return _archive;
		else if (name == PROP_COMPRESS)
			return std::string(_compress ? "true" : "false");
		else if (name == PROP_PURGEAGE)
			return _purgeAge;
		else if (name == PROP_PURGECOUNT)
			return _purgeCount;
		else if (name == PROP_FLUSH)
			return std::string(_flush ? "true" : "false");
		else if (name == PROP_ROTATEONOPEN)
			return std::string(_rotateOnOpen ? "true" : "false");
		else
			return Channel::GetProperty(name);
	}

	TimeStamp FileChannel::CreationDate() const
	{
		if (_pFile)
		{
			return _pFile->CreationDate();
		}
		else
			return 0;
	}

	uint64 FileChannel::GetSize()
	{
		if (_pFile)
		{
			return _pFile->GetSize();
		}
		else
			return 0;
	}

	void FileChannel::setRotation(const std::string& rotation)
	{

	}

	void FileChannel::setArchive(const std::string& archive)
	{
		ArchiveStrategy* pStrategy = NULL;
		if (archive == "number")
		{
			pStrategy = new ArchiveByNumberStrategy;
		}
		else if (archive == "timestamp")
		{
			pStrategy = new ArchiveByTimeStampStrategy;
		}
		else
		{
			throw InvalidArgumentException("archive", archive);
		}
		if (_pArchiveStrategy)
		{
			delete _pArchiveStrategy;
		}
		pStrategy->SetCompress(_compress);
		_pArchiveStrategy = pStrategy;
		_archive = archive;
	}

	void FileChannel::setCompress(const std::string& compress)
	{
		_compress = icompare(compress, "true") == 0;
		if (_pArchiveStrategy)
		{
			_pArchiveStrategy->SetCompress(_compress);
		}
		
	}

	void FileChannel::setPurgeAge(const std::string& age)
	{

	}

	void FileChannel::setPurgeCount(const std::string& count)
	{
		std::string::const_iterator itr = count.begin();
		std::string::const_iterator end = count.end();
		int32 n = 0;
		while( itr != end && AsciiCharacter::IsSpace(*itr)) ++itr;
		while( itr != end && AsciiCharacter::IsDigit(*itr))
		{
			n *= 10;
			n += *itr++ - '0';
		}
		while( itr != end && AsciiCharacter::IsSpace(*itr))++itr;
		if (_pPurgeStrategy)
		{
			delete _pPurgeStrategy;
		}
		_pPurgeStrategy = new PurgeByCountStrategy(n);
		_purgeCount = count;
	}

	void FileChannel::setFlush(const std::string& flush)
	{
		_flush = icompare(flush, "true") == 0;
	}

	void FileChannel::setRotateOnOpen(const std::string& rotateOnOpen)
	{
		_rotateOnOpen = icompare(rotateOnOpen, "true") == 0;
	}

	void FileChannel::purge()
	{
		if (_pPurgeStrategy)
		{
			try
			{
				_pPurgeStrategy->Purge(_path);
			}
			catch(...)
			{

			}
		}
	}
}