#include "PreCom.h"
#include "ArchiveStrategy.h"
#include "LogFile.h"
#include "StringHelper.h"
#include "DateTime.h"
#include "File/FileInfo.h"
#include "Thread/ActiveDispatcher.h"
#include "Thread/ActiviteMethod.h"
#include "Stream/DeflatingStream.h"
#include "Stream/StreamCopier.h"

namespace okey
{
	class ArchiveCompressor: public ActiveDispatcher
	{
	public:
		ArchiveCompressor():
		  compress(this, &ArchiveCompressor::compressImpl)
		  {
		  }

		  ~ArchiveCompressor()
		  {
		  }

		  ActiveMethod<void, std::string, ArchiveCompressor, ActiveStarter<ActiveDispatcher> > compress;

	protected:
		void compressImpl(const std::string& path)
		{
			std::string gzPath(path);
			gzPath.append(".gz");
			FileInputStream istr(path, File::AllowRead);
			if (!istr.good()) 
				throw OpenFileException(path);
			FileOutputStream ostr(gzPath, File::AllowWrite);
			if (ostr.good())
			{
				DeflatingOutputStream deflater(ostr, DeflatingStreamBuf::STREAM_GZIP);
				StreamCopier::CopyStream(istr, deflater);
				deflater.close();
				ostr.close();
				istr.close();
				FileInfo f(path);
				f.Remove();
			}
			else 
				throw CreateFileException(gzPath);
			
		}
	};

	ArchiveStrategy::ArchiveStrategy():_compress(false),_pCompressor(NULL)
	{

	}

	ArchiveStrategy::~ArchiveStrategy()
	{
		if (_pCompressor)
		{
			delete _pCompressor;
			_pCompressor = NULL;
		}
	}

	void ArchiveStrategy::MoveFile(const std::string& oldName, const std::string& newName)
	{
		bool compressed = false;
		FileInfo f(oldName);
		if (!f.IsExisted())
		{
			f = oldName + ".gz";
			compressed = true;
		}
		std::string mvPath(newName);
		if (_compress || compressed)
			mvPath.append(".gz");
		if (!_compress || compressed)
		{
			f.RenameTo(mvPath);
		}
		else
		{
			f.RenameTo(newName);
			if (!_pCompressor) _pCompressor = new ArchiveCompressor;
			_pCompressor->compress(newName);
		}
	}

	bool ArchiveStrategy::IsExists(const std::string& name)
	{
		FileInfo f(name);
		if (f.IsExisted())
		{
			return true;
		}
		else if (_compress)
		{
			std::string gzName(name);
			gzName.append(".gz");
			FileInfo gzf(gzName);
			return gzf.IsExisted();
		}
		else return false;
	}

	ArchiveByNumberStrategy::ArchiveByNumberStrategy()
	{

	}

	ArchiveByNumberStrategy::~ArchiveByNumberStrategy()
	{

	}

	LogFile* ArchiveByNumberStrategy::Archive(LogFile* pFile)
	{
		std::string basePath = pFile->GetPath();
		delete pFile;
		int n = -1;
		std::string path;
		do
		{
			path = basePath;
			path.append(".");
			std::string ret = StringHelper::ToString(++n);
			path += ret;
		}
		while (IsExists(path));
		while (n >= 0)
		{
			std::string oldPath = basePath;
			if (n > 0)
			{
				oldPath.append(".");
				std::string ret = StringHelper::ToString(n - 1);
				oldPath += ret;
			}
			std::string newPath = basePath;
			newPath.append(".");
			std::string rr = StringHelper::ToString(n);
			newPath += rr;
			MoveFile(oldPath, newPath);
			--n;
		}
		return new LogFile(basePath);
	}

	ArchiveByTimeStampStrategy::ArchiveByTimeStampStrategy()
	{

	}

	ArchiveByTimeStampStrategy::~ArchiveByTimeStampStrategy()
	{

	}

	LogFile* ArchiveByTimeStampStrategy::Archive(LogFile* pFile)
	{
		std::string path = pFile->GetPath();
		delete pFile;
		std::string archPath = path;
		archPath.append(".");
		char Buff[64] = {0};
		DateTime now;
		tsnprintf(Buff,64,"%2d%2d%2d%2d%2d%2d%2d",now.year(),now.month(),now.day(),now.hour(),
			now.second(),now.millisecond());
		archPath += Buff;
		if (IsExists(archPath))
			ArchiveByNumber(archPath);
		else 
			MoveFile(path, archPath);
		return new LogFile(path);
	}

	void ArchiveByTimeStampStrategy::ArchiveByNumber(const std::string& basePath)
	{
		int32 n = -1;
		std::string path;
		do 
		{
		 	path = basePath;
		 	path.append(".");
		 	std::string se = StringHelper::ToString(++n);
		 	path += se;
		 				
		} while (IsExists(path));
		 			
		while(n >= 0)
		{
		 	std::string oldPath = basePath;
		 	if (n > 0)
		 	{
		 		oldPath.append(".");
		 		std::string se = StringHelper::ToString(n - 1);
		 		oldPath += se;
		 	}
		 	std::string newPath = basePath;
		 	newPath.append(".");
		 	std::string sen = StringHelper::ToString(n );
		 	newPath += sen;
		 	MoveFile(oldPath, newPath);
		 	--n;
		}
	}
}