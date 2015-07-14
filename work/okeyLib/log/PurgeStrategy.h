/********************************************************************
	created:	2015/07/14
	created:	16:14
	author:		okey
	
	purpose:	清除策略
*********************************************************************/
#ifndef __LOG_PURGE_STRATEGY_H__
#define __LOG_PURGE_STRATEGY_H__

#include <string>
#include <vector>
#include "File/FileInfo.h"
#include "TimeSpan.h"

namespace okey
{
	class PurgeStrategy
	{
	public:
		PurgeStrategy();
		virtual ~PurgeStrategy();
		virtual void Purge(const std::string& path) = 0; //清除日志备份文件
	protected:
		void GetList(const std::string& path, std::vector<FileInfo>& files);
	private:
		PurgeStrategy(const PurgeStrategy&);
		PurgeStrategy& operator = (const PurgeStrategy&);
	};

	class PurgeByAgeStrategy: public PurgeStrategy
	{
	public:
		PurgeByAgeStrategy(const TimeSpan& age);
		~PurgeByAgeStrategy();
		void Purge(const std::string& path);
	private:
		TimeSpan _age;
	};


	class PurgeByCountStrategy: public PurgeStrategy
	{
	public:
		PurgeByCountStrategy(int32 count);
		~PurgeByCountStrategy();
		void Purge(const std::string& path);
	private:
		int32 _count;
	};
}

#endif