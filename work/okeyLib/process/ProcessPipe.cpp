#include "PreCom.h"
#include "ProcessPipe.h"
#include "Exception.h"

namespace okey
{
	ProcessPipe::ProcessPipe()
	{
#ifdef WINDOWS
		SECURITY_ATTRIBUTES attr;
		attr.nLength              = sizeof(attr);
		attr.lpSecurityDescriptor = NULL;
		attr.bInheritHandle       = FALSE;

		if (!CreatePipe(&_readfd, &_writefd, &attr, 0))
			throw CreateFileException("anonymous pipe");
#else
		int fds[2];
		int rc = pipe(fds);
		if (rc == 0)
		{
			_readfd  = fds[0];
			_writefd = fds[1];
		}
		else 
			throw CreateFileException("anonymous pipe");
#endif
	}

	ProcessPipe::~ProcessPipe()
	{
		CloseRead();
		CloseWrite();
	}

	int ProcessPipe::WriteBytes(const void* buffer, int length)
	{
		//assert _writefd...
#ifdef WINDOWS
		DWORD bytesWritten = 0;
		if (!WriteFile(_writefd, buffer, length, &bytesWritten, NULL))
			throw WriteFileException("anonymous pipe");
		return bytesWritten;
#else
		int n;
		do
		{
			n = write(_writefd, buffer, length);
		}
		while (n < 0 && errno == EINTR);
		if (n >= 0)
			return n;
		else
			throw WriteFileException("anonymous pipe");
#endif
	}
	int ProcessPipe::ReadBytes(void* buffer, int length)
	{
		//assert _readfd
#ifdef WINDOWS
		DWORD bytesRead = 0;
		BOOL ok = ReadFile(_readfd, buffer, length, &bytesRead, NULL);
		if (ok || GetLastError() == ERROR_BROKEN_PIPE)
			return bytesRead;
		else
			throw ReadFileException("anonymous pipe");
#else
		int n;
		do
		{
			n = read(_readfd, buffer, length);
		}
		while (n < 0 && errno == EINTR);
		if (n >= 0)
			return n;
		else
			throw ReadFileException("anonymous pipe");
#endif
	}


	void ProcessPipe::CloseRead()
	{
#ifdef WINDOWS
		if (_readfd != INVALID_HANDLE_VALUE)
		{
			CloseHandle(_readfd);
			_readfd = INVALID_HANDLE_VALUE;
		}
#else
		if (_readfd != -1)
		{
			close(_readfd);
			_readfd = -1;
		}
#endif
	}

	void ProcessPipe::CloseWrite()
	{
#ifdef WINDOWS
		if (_writefd != INVALID_HANDLE_VALUE)
		{
			CloseHandle(_writefd);
			_writefd = INVALID_HANDLE_VALUE;
		}
#else
		if (_writefd != -1)
		{
			close(_writefd);
			_writefd = -1;
		}
#endif
	}

	Pipe::Pipe():_pipe(new ProcessPipe)
	{

	}

	Pipe::~Pipe()
	{
		_pipe->DecRef();
	}

	Pipe::Pipe(const Pipe& p):_pipe(p._pipe)
	{
		_pipe->AddRef();
	}

	Pipe& Pipe::operator=(const Pipe& p)
	{
		if (this != &p)
		{
			_pipe->DecRef();
			_pipe = p._pipe;
			_pipe->AddRef();
		}
		return *this;
	}

	void Pipe::Close(CloseMode mode)
	{
		switch (mode)
		{
		case CLOSE_READ:
			_pipe->CloseRead();
			break;
		case CLOSE_WRITE:
			_pipe->CloseWrite();
			break;
		default:
			_pipe->CloseRead();
			_pipe->CloseWrite();
			break;
		}
	}
}