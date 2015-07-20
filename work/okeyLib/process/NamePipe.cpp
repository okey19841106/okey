#include "PreCom.h"
#include "NamePipe.h"

namespace okey
{
	NamePipeServer::NamePipeServer():_handle(INVALID_HANDLE_VALUE)
	{

	}

	NamePipeServer::NamePipeServer(const std::string& name):_name(name),_handle(INVALID_HANDLE_VALUE)
	{
		Listen(_name);
	}

	NamePipeServer::~NamePipeServer()
	{
		Close();
	}

	bool NamePipeServer::Listen(const std::string& name)
	{
#ifdef _WINDOWS
		if(_handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(_handle);
		}
		_handle = CreateNamedPipe(name.c_str(), PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_BYTE | PIPE_NOWAIT,
			PIPE_UNLIMITED_INSTANCES,
			4096, 4096, 1000, 0);
		if(_handle == INVALID_HANDLE_VALUE)
			return false;
		_name = name;
		return true;
#else
		Close();
		struct sockaddr_un npaddr;
		npaddr.sun_family = AF_UNIX;
		strcpy(npaddr.sun_path, name);
		_handle = socket(PF_UNIX, SOCK_STREAM, 0);
		if (_handle == -1)
		{
			return false;
		}
		int ret = bind(_handle, (sockaddr*)&npaddr, sizeof(sockaddr_un));
		if (ret == -1)
		{
			::close(_handle);
			return false;
		}
		ret = listen(_handle, 128);
		if (ret == -1)
		{
			::close(_handle);
			return false;
		}
		_name = name;
#endif
	}

	void NamePipeServer::Close()
	{
#ifdef _WINDOWS
		if(_handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(_handle);
			_handle = INVALID_HANDLE_VALUE;
		}
#else
		if (_handle != INVALID_HANDLE_VALUE)
		{
			::close(_handle);
			unlink(_name.c_str());
		}
		_handle = INVALID_HANDLE_VALUE;
#endif
	}

	bool NamePipeServer::WaitClient(uint32 timeout)
	{
#ifdef _WINDOWS
		DWORD expire = GetTickCount() + timeout + 1;

		while(GetTickCount() < expire)
		{
			if(ConnectNamedPipe(_handle, NULL))
				return true;
			if(GetLastError() == ERROR_PIPE_CONNECTED)
				return true;
			else if(GetLastError() == ERROR_PIPE_LISTENING)
			{
				Sleep(1);
				continue;
			}
			else
			{
				return false;
			}
		}
		return false;
#else
		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(_handle, &rfds);
		struct timeval tv;
_select:
		int ret = select(_handle + 1, &rfds, 0 , 0, get_timeout(&tv, timeout, TIMEOUT_RELATIVE));
		if (ret == -1)
		{
			if (errno == EINTR)
			{
				goto _select;
			}
			return false;
		}
		return true;
#endif
	}

	Handle NamePipeServer::Accept()
	{
#ifdef _WINDOWS
		Handle client = _handle;
		_handle = CreateNamedPipe(_name.c_str(), PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_BYTE | PIPE_NOWAIT,
			PIPE_UNLIMITED_INSTANCES,
			4096, 4096, 1000, 0);
		DWORD state = PIPE_WAIT;
		SetNamedPipeHandleState(client, &state, NULL, NULL);
		return client;
#else 
		struct sockaddr_un npaddr;
		socklen_t addrlen = sizeof(sockaddr_un);

		Handle handle = ::accept(_handle, (sockaddr*)&npaddr, &addrlen);
		if(handle == -1)
			return INVALID_HANDLE_VALUE;
		return handle;
#endif
	}

	NamePipe::NamePipe():_handle(INVALID_HANDLE_VALUE)
	{

	}

	NamePipe::NamePipe(const std::string& name):_handle(INVALID_HANDLE_VALUE)
	{
		Connect(name);
	}

	NamePipe::NamePipe(NamePipeServer& srv)
	{
		Handle handle = srv.Accept();
#ifdef _WINDOWS
		BOOL ret = DuplicateHandle(GetCurrentProcess(), handle,
			GetCurrentProcess(), &_handle,
			DUPLICATE_SAME_ACCESS, TRUE, 0);
#else
		m_handle = dup(handle);
#endif
	}
	
	NamePipe::~NamePipe()
	{
		Close();
	}
	bool NamePipe::Connect(const std::string& name)
	{
#ifdef _WINDOWS
		Handle handle;
		while(true)
		{
			handle = CreateFile(name.c_str(), GENERIC_READ | GENERIC_WRITE,
				0, NULL, OPEN_EXISTING, 0, NULL);

			if(handle == INVALID_HANDLE_VALUE)
			{
				if(GetLastError() == ERROR_PIPE_BUSY)
				{
					if(!WaitNamedPipe(name.c_str(), NMPWAIT_WAIT_FOREVER))
						return false;
					continue;
				}
				return false;
			}
			else
				break;
		}
		_handle = handle;
#else
		if(_handle != INVALID_HANDLE_VALUE)
			Close();

		struct sockaddr_un npaddr;
		npaddr.sun_family = AF_UNIX;
		strcpy(npaddr.sun_path, name);
		Handle handle = socket(PF_UNIX, SOCK_STREAM, 0);
		if(handle == -1)
			return false;
		int ret = ::connect(handle, (sockaddr*)&npaddr, sizeof(sockaddr_un));
		if(ret == -1)
		{
			::close(handle);
			return false;
		}
		setHandle(handle);
		return true;
#endif
	}

	void NamePipe::Close()
	{
#ifdef _WINDOWS
		if(_handle != INVALID_HANDLE_VALUE)
		{
			DWORD flags;
			GetNamedPipeInfo(_handle, &flags, NULL, NULL, NULL);
			if(flags & PIPE_SERVER_END)
				DisconnectNamedPipe(_handle);
			CloseHandle(_handle);
			_handle = INVALID_HANDLE_VALUE;
		}
#else
		if(_handle != INVALID_HANDLE_VALUE)
		{
			::shutdown(handle(), 2);
			close(_handle);
			_handle = INVALID_HANDLE_VALUE;
		}
#endif
	}

	int32 NamePipe::Peek(char* buffer, uint32 count)
	{
#ifdef _WINDOWS
		DWORD bytesRead, bytesAvail, bytesLeft;
		if(PeekNamedPipe(_handle, (void*)buffer, count, &bytesRead, &bytesAvail, &bytesLeft))
			return bytesRead;
		return -1;
#else
		int ret;
_recv:
		ret = recv(_handle, (void*)buffer, count, MSG_PEEK);
		if(ret != -1)
			return ret;
		if(errno == EINTR)
			goto _recv;
		return -1;
#endif
	}

	int32 NamePipe::WriteBytes(const void* buffer, int length)
	{
#ifdef _WINDOWS
		DWORD written = 0;

		if(!WriteFile(_handle, (void*)buffer, length, &written, NULL))
			return -1;
		return written;
#else
_write:
		ssize_t ret = ::write(_handle, buffer, length);
		if(ret != -1)
			return ret;
		if(errno == EAGAIN)
			return 0;
		else if(errno == EINTR)
			goto _write;
		return -1;
#endif
	}

	int32 NamePipe::ReadBytes(void* buffer, int length)
	{
#ifdef _WINDOWS
		DWORD read;
		if(!ReadFile(_handle, (void*)buffer, length, &read, NULL))
			return -1;
		return read;
#else
_read:
		ssize_t ret = ::read(m_handle, buffer, length);
		if(ret != -1)
			return ret;
		if(errno == EAGAIN)
			return 0;
		else if(errno == EINTR)
			goto _read;
		return -1;
#endif
	}
}