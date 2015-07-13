#include "PreCom.h"
#include "File/File.h"
#include "File/FileInfo.h"
#include "LogFile.h"

namespace okey
{
	LogFile::LogFile(const std::string& path):
		_path(path),_str(path,File::AllowReadWrite,File::Append)
	{
		if (GetSize() == 0)
			_creationDate = FileInfo(path).GetModityTime().ToTime();
		else
			_creationDate = FileInfo(path).GetCreateTime().ToTime();
	}

	LogFile::~LogFile()
	{

	}

	void LogFile::WriteLog(const std::string& text, bool flush)
	{
		_str << text;
		if (flush) 
			_str << std::endl;
		else
			_str << "\n";
		if (!_str.good()) 
			throw WriteFileException(_path);
	}
}

