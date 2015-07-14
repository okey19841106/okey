/********************************************************************
	created:	2015/07/14
	created:	15:58
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __LOG_FILE_CHANNEL_H__
#define __LOG_FILE_CHANNEL_H__

namespace okey
{
	class LogFile;
	class RotateStrategy;
	class ArchiveStrategy;
	class PurgeStrategy;

	class FileChannel: public Channel
	{
	public:
		FileChannel();
	protected:
		~FileChannel();
	};
}

#endif