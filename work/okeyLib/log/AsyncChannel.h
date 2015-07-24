/********************************************************************
	created:	2015/07/23
	created:	16:51
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __LOG_ASYNC_CHANNEL_H__
#define __LOG_ASYNC_CHANNEL_H__

#include "Channel.h"
#include "Thread/Runnable.h"
#include "Thread/Thread.h"
#include "Thread/Mutex.h"
#include "Notifications/NotificationQueue.h"

namespace okey
{
	class AsyncChannel: public Channel, public Runnable
	{
	public:
		AsyncChannel(Channel* pChannel = 0, Thread::Priority prio = Thread::PRIO_NORMAL);
		void SetChannel(Channel* pChannel);
		Channel* GetChannel() const;
		void Open();
		void Close();
		void SetProperty(const std::string& name, const std::string& value);
	protected:
		~AsyncChannel();
		void Run();
		void setPriority(const std::string& value);
		void logInstance(int32 pro, const char* msg);
	private:
		Channel*  _pChannel;
		Thread    _thread;
		FastMutex _threadMutex;
		FastMutex _channelMutex;
		NotificationQueue _queue;
	};
}

#endif