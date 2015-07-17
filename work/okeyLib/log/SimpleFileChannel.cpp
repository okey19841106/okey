#include "PreCom.h"
#include "SimpleFileChannel.h"
#include "LogFile.h"
#include "File/FileInfo.h"
#include "Message.h"
#include "AsciiCharacter.h"
#include "StringHelper.h"

namespace okey
{
	SimpleFileChannel::SimpleFileChannel():_limit(0),_flush(true),_pFile(NULL)
	{

	}

	SimpleFileChannel::SimpleFileChannel(const std::string& path):_path(path),
		_secondaryPath(path + ".0"),_limit(0),_flush(true),_pFile(NULL)
	{

	}

	void SimpleFileChannel::Open()
	{
		FastMutex::ScopedLock lock(_mutex);
		if (!_pFile)
		{
			FileInfo primary(_path);
			FileInfo secondary(_secondaryPath);
			TimeStamp pt = primary.IsExisted() ? primary.GetModityTime() : 0;
			TimeStamp st = secondary.IsExisted() ? secondary.GetModityTime() : 0;
			std::string path;
			if (pt >= st)
				path = _path;
			else
				path = _secondaryPath;
			_pFile = new LogFile(path);
		}
	}

	void SimpleFileChannel::Close()
	{
		FastMutex::ScopedLock lock(_mutex);
		delete _pFile;
		_pFile = NULL;
	}

	void SimpleFileChannel::Log(const Message& msg)
	{
		Open();
		FastMutex::ScopedLock lock(_mutex);
		if (_limit > 0 && _pFile->GetSize() >= _limit)
		{
			rotate();
		}
		_pFile->WriteLog(msg.GetText(), _flush);
	}

	void SimpleFileChannel::SetProperty(const std::string& name, const std::string& value)
	{
		FastMutex::ScopedLock lock(_mutex);
		if (name == PROP_PATH)
		{
			_path = value;
			if (_secondaryPath.empty())
				_secondaryPath = _path + ".0";
		}
		else if (name == PROP_SECONDARYPATH)
			_secondaryPath = value;
		else if (name == PROP_ROTATION)
			setRotation(value);
		else if (name == PROP_FLUSH)
			setFlush(value);
		else
			Channel::SetProperty(name, value);
	}

	std::string SimpleFileChannel::GetProperty(const std::string& name) const
	{
		if (name == PROP_PATH)
			return _path;
		else if (name == PROP_SECONDARYPATH)
			return _secondaryPath;
		else if (name == PROP_ROTATION)
			return _rotation;
		else if (name == PROP_FLUSH)
			return std::string(_flush ? "true" : "false");
		else
			return Channel::GetProperty(name);
	}

	TimeStamp SimpleFileChannel::GetCreationDate() const
	{
		if (_pFile)
			return _pFile->CreationDate();
		else
			return 0;
	}

	uint64 SimpleFileChannel::GetSize() const
	{
		if (_pFile)
			return _pFile->GetSize();
		else
			return 0;
	}

	const std::string& SimpleFileChannel::GetPath() const
	{
		return _path;
	}

	const std::string& SimpleFileChannel::GetSecondaryPath() const
	{
		return _secondaryPath;
	}

	SimpleFileChannel::~SimpleFileChannel()
	{
		Close();
	}

	void SimpleFileChannel::setRotation(const std::string& rotation)
	{
		std::string::const_iterator it  = rotation.begin();
		std::string::const_iterator end = rotation.end();
		uint64 n = 0;
		while (it != end && AsciiCharacter::IsSpace(*it)) ++it;
		while (it != end && AsciiCharacter::IsDigit(*it)) { n *= 10; n += *it++ - '0'; }
		while (it != end && AsciiCharacter::IsSpace(*it)) ++it;
		std::string unit;
		while (it != end && AsciiCharacter::IsAlpha(*it)) unit += *it++;
		if (unit == "K")
			_limit = n*1024;
		else if (unit == "M")
			_limit = n*1024*1024;
		else if (unit.empty())
			_limit = n;
		else if (unit == "never")
			_limit = 0;
		else
			throw InvalidArgumentException("rotation", rotation);
		_rotation = rotation;
	}

	void SimpleFileChannel::setFlush(const std::string& flush)
	{
		_flush = icompare(flush, "true") == 0;
	}

	void SimpleFileChannel::rotate()
	{
		std::string newPath;
		if (_pFile->GetPath() == _path)
			newPath = _secondaryPath;
		else
			newPath = _path;
		FileInfo f(newPath);
		if (f.IsExisted())
		{
			try
			{
				f.Remove();
			}
			catch (...)
			{
			}
		}
		delete _pFile;
		_pFile = new LogFile(newPath);
	}
}