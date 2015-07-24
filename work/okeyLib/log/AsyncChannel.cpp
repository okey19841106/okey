#include "PreCom.h"
#include "AsyncChannel.h"
#include "LoggingRegistry.h"

namespace okey
{

	class LogNotification: public Notification
	{
	public:
		LogNotification(int32 pro, const std::string& sz):_pro(pro),_sz(sz)
		{
		}
		~LogNotification()
		{
		}

		std::string _sz;
		int32 _pro;
	};

	AsyncChannel::AsyncChannel(Channel* pChannel, Thread::Priority prio):_pChannel(pChannel), 
		_thread("AsyncChannel")
	{
		if (_pChannel) 
			_pChannel->AddRef();
		_thread.SetPriority(prio);
	}

	void AsyncChannel::SetChannel(Channel* pChannel)
	{
		FastMutex::ScopedLock lock(_channelMutex);
		if (_pChannel) 
			_pChannel->DecRef();
		_pChannel = pChannel;
		if (_pChannel) 
			_pChannel->AddRef();
	}

	Channel* AsyncChannel::GetChannel() const
	{
		return _pChannel;
	}

	void AsyncChannel::Open()
	{
		FastMutex::ScopedLock lock(_threadMutex);

		if (!_thread.IsRunning())
			_thread.Start(*this);
	}

	void AsyncChannel::Close()
	{
		if (_thread.IsRunning())
		{
			while (!_queue.Empty()) 
				Thread::Sleep(100);
			do 
			{
				_queue.WakeUpAll(); 
			}
			while (!_thread.TryJoin(100));
		}
	}

	void AsyncChannel::SetProperty(const std::string& name, const std::string& value)
	{
		if (name == "channel")
			SetChannel(LoggingRegistry::GetDefaultRegistry().GetChannelForName(value));
		else if (name == "priority")
			setPriority(value);
		else
			Channel::SetProperty(name, value);
	}

	AsyncChannel::~AsyncChannel()
	{
		Close();
		if (_pChannel) 
			_pChannel->DecRef();
	}
	void AsyncChannel::Run()
	{
		AutoPtr<Notification> nf = _queue.WaitDequeueNotification();
		while (nf)
		{
			LogNotification* pNf = dynamic_cast<LogNotification*>(nf.get());
			{
				FastMutex::ScopedLock lock(_channelMutex);

				if (pNf && _pChannel) 
					_pChannel->Log(pNf->_pro, pNf->_sz.c_str());
			}
			nf = _queue.WaitDequeueNotification();
		}
	}

	void AsyncChannel::setPriority(const std::string& value)
	{
		Thread::Priority prio = Thread::PRIO_NORMAL;

		if (value == "lowest")
			prio = Thread::PRIO_LOWEST;
		else if (value == "low")
			prio = Thread::PRIO_LOW;
		else if (value == "normal")
			prio = Thread::PRIO_NORMAL;
		else if (value == "high")
			prio = Thread::PRIO_HIGH;
		else if (value == "highest")
			prio = Thread::PRIO_HIGHEST;
		else
			throw InvalidArgumentException("thread priority", value);
		_thread.SetPriority(prio);
	}

	void AsyncChannel::logInstance(int32 pro, const char* msg)
	{
		Open();
		_queue.EnqueueNotification(new LogNotification(pro, msg));
	}
}