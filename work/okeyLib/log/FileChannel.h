/********************************************************************
	created:	2015/07/14
	created:	15:58
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __LOG_FILE_CHANNEL_H__
#define __LOG_FILE_CHANNEL_H__

#include "Channel.h"
#include "TimeStamp.h"
#include "Thread/Mutex.h"

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
		FileChannel(const std::string& path);
		virtual void Open();
		virtual void Close();
		virtual void Log(const Message& msg) = 0;
		void SetProperty(const std::string& name, const std::string& value);
		std::string GetProperty(const std::string& name) const;
		TimeStamp CreationDate() const;
		uint64 GetSize();
		inline const std::string& GetPath() const{return _path;}

		static const std::string PROP_PATH;
		static const std::string PROP_ROTATION;
		static const std::string PROP_ARCHIVE;
		static const std::string PROP_TIMES;
		static const std::string PROP_COMPRESS;
		static const std::string PROP_PURGEAGE;
		static const std::string PROP_PURGECOUNT;
		static const std::string PROP_FLUSH;
		static const std::string PROP_ROTATEONOPEN;
	protected:
		~FileChannel();
		void setRotation(const std::string& rotation);
		void setArchive(const std::string& archive);
		void setCompress(const std::string& compress);
		void setPurgeAge(const std::string& age);
		void setPurgeCount(const std::string& count);
		void setFlush(const std::string& flush);
		void setRotateOnOpen(const std::string& rotateOnOpen);
		void purge();
	private:
		std::string _path;
		std::string _times;
		std::string _rotation;
		std::string _archive;
		bool	_compress;
		std::string _purgeAge;
		std::string _purgeCount;
		bool _flush;
		bool _rotateOnOpen;
		LogFile* _pFile;
		RotateStrategy* _pRotateStrategy;
		ArchiveStrategy* _pArchiveStrategy;
		PurgeStrategy* _pPurgeStrategy;
		FastMutex _mutex;
	};
}

#endif