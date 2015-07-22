#include "PreCom.h"
#include "PurgeStrategy.h"


namespace okey
{
	PurgeStrategy::PurgeStrategy()
	{

	}

	PurgeStrategy::~PurgeStrategy()
	{

	}

	void PurgeStrategy::GetList(const std::string& path, std::vector<FileInfo>& files)
	{
		std::string baseName = FileInfo::GetFileName(path);
		baseName.append(".");
		OkeyFile::Iterator it(path);
		OkeyFile::Iterator end;
		while(it != end)
		{
			if ( it.name().compare(0, baseName.size(), baseName) == 0)
			{
				files.push_back(*it);
			}
			++it;
		}
	}

	PurgeByAgeStrategy::PurgeByAgeStrategy(const TimeSpan& age):_age(age)
	{

	}

	PurgeByAgeStrategy::~PurgeByAgeStrategy()
	{

	}

	void PurgeByAgeStrategy::Purge(const std::string& path)
	{
		std::vector<FileInfo> files;
		GetList(path, files);
		for (std::vector<FileInfo>::iterator it = files.begin(); it != files.end(); ++it)
		{
			if (it->GetModityTime().ToTime().isElapsed(_age.totalMicroseconds()))
			{
				it->Remove();
			}
		}
	}

	PurgeByCountStrategy::PurgeByCountStrategy(int32 count):_count(count)
	{

	}

	PurgeByCountStrategy::~PurgeByCountStrategy()
	{

	}

	void PurgeByCountStrategy::Purge(const std::string& path)
	{
		std::vector<FileInfo> files;
		GetList(path, files);
		while (files.size() > _count)
		{
			std::vector<FileInfo>::iterator it = files.begin();
			std::vector<FileInfo>::iterator purgeIt = it;
			TimeStamp purgeTS = purgeIt->GetModityTime().ToTime();
			++it;
			while (it != files.end())
			{
				TimeStamp md(it->GetModityTime().ToTime());
				if (md <= purgeTS)
				{
					purgeTS = md;
					purgeIt = it;
				}
				++it;
			}
			purgeIt->Remove();
			files.erase(purgeIt);
		}
	}
}