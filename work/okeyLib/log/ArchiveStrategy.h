/********************************************************************
	created:	2015/07/10
	created:	16:42
	author:		okey
	
	purpose:	存档策略。 压缩日志用的。
*********************************************************************/
#ifndef _BASE_LOG_ARCHIVE_STRATEGY_H__
#define _BASE_LOG_ARCHIVE_STRATEGY_H__

#include <string>

namespace okey
{
	class LogFile;
	class ArchiveCompressor;


	class ArchiveStrategy
	{
	public:
		ArchiveStrategy();
		virtual ~ArchiveStrategy();
		//rename the given log file for archiving and creates and returns a new log file the given logfile object is deleted.
		virtual LogFile* Archive(LogFile* pFile) = 0; 
		void SetCompress(bool falg = true);
	protected:
		void MoveFile(const std::string& oldName, const std::string& newName);
		bool IsExists(const std::string& name);
	private:
		ArchiveStrategy(const ArchiveStrategy&);
		ArchiveStrategy& operator=(const ArchiveStrategy&);
		bool _compress;
		ArchiveCompressor* _pCompressor;
	};

	class ArchiveByNumberStrategy: public ArchiveStrategy
	{
	public:
		ArchiveByNumberStrategy();
		~ArchiveByNumberStrategy();
		LogFile* Archive(LogFile* pFile);
	};


	class ArchiveByTimeStampStrategy: public ArchiveStrategy
	{
	public:
		ArchiveByTimeStampStrategy();
		~ArchiveByTimeStampStrategy();

		LogFile* Archive(LogFile* pFile);
	private:
		void ArchiveByNumber(const std::string& basePath);
	};
}

#endif
