/********************************************************************
	created:	2015/07/17
	created:	14:22
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __SIMPLE_FILE_CHANNEL_H__
#define __SIMPLE_FILE_CHANNEL_H__

#include "Channel.h"
#include "TimeStamp.h"
#include "Thread/Mutex.h"

namespace okey
{
	class LogFile;

	class SimpleFileChannel: public Channel
	{
	public:
		SimpleFileChannel();
		SimpleFileChannel(const std::string& path);
		virtual void Open();
		virtual void Close();
		virtual void Log(const Message& msg);
		void SetProperty(const std::string& name, const std::string& value);
		std::string GetProperty(const std::string& name) const;
		TimeStamp GetCreationDate() const;
		uint64 GetSize() const;
		const std::string& GetPath() const;
		const std::string& GetSecondaryPath() const;

		static const std::string PROP_PATH;
		static const std::string PROP_SECONDARYPATH;
		static const std::string PROP_ROTATION;
		static const std::string PROP_FLUSH;
	protected:
		~SimpleFileChannel();
		void setRotation(const std::string& rotation);
		void setFlush(const std::string& flush);
		void rotate();
	private:
		std::string      _path;
		std::string      _secondaryPath;
		std::string      _rotation;
		uint64           _limit;
		bool             _flush;
		LogFile*         _pFile;
		FastMutex        _mutex;
	};
}

#endif