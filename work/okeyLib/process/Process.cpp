#include "PreCom.h"
#include "Process.h"
#include "Exception.h"
#include "StringHelper.h"
#include "NameEvent.h"
#include "ProcessPipe.h"
#include "Environment.h"

namespace okey
{
	std::vector<char> getEnvironmentVariablesBuffer(const Process::Env& env)
	{   
		std::vector<char> envbuf;
		std::size_t pos = 0; 

		for (Process::Env::const_iterator it = env.begin(); it != env.end(); ++it)
		{
			std::size_t envlen = it->first.length() + it->second.length() + 1;

			envbuf.resize(pos + envlen + 1);
			std::copy(it->first.begin(), it->first.end(), &envbuf[pos]);
			pos += it->first.length();
			envbuf[pos] = '=';
			++pos;
			std::copy(it->second.begin(), it->second.end(), &envbuf[pos]);
			pos += it->second.length();

			envbuf[pos] = '\0';
			++pos;
		}

		envbuf.resize(pos + 1);
		envbuf[pos] = '\0';

		return envbuf;
	}

	void setEnvironmentVariables(const Process::Env& env)
	{
		for (Process::Env::const_iterator it = env.begin(); it != env.end(); ++it)
		{
			Environment::set(it->first, it->second);
		}
	}

	ProcessHandleImpl::~ProcessHandleImpl()
	{
#ifdef WINDOWS
		CloseHandle(_hProcess);
#else
#endif
	}

	ProcessID ProcessHandleImpl::GetID() const
	{
		return _pid;
	}

#ifdef WINDOWS
	ProcessHandleImpl::ProcessHandleImpl(HANDLE hp, ProcessID pid):_hProcess(hp), _pid(pid)
	{

	}

	HANDLE ProcessHandleImpl::GetProcess() const
	{
		return _hProcess;
	}
#else
	ProcessHandleImpl::ProcessHandleImpl(ProcessID pid):_pid(pid)
	{

	}
#endif

	int32 ProcessHandleImpl::Wait() const
	{
#ifdef WINDOWS
		DWORD rc = WaitForSingleObject(_hProcess, INFINITE);
		if (rc != WAIT_OBJECT_0)
			throw SystemException("Wait failed for process", StringHelper::ToString<uint32>(_pid));

		DWORD exitCode;
		if (GetExitCodeProcess(_hProcess, &exitCode) == 0)
			throw SystemException("Cannot get exit code for process", StringHelper::ToString<uint32>(_pid));
		return exitCode;
#else
		int status;
		int rc;
		do
		{
			rc = waitpid(_pid, &status, 0);
		}
		while (rc < 0 && errno == EINTR);
		if (rc != _pid)
			throw SystemException("Cannot wait for process", StringHelper::ToString<uint32>(_pid));
		return WEXITSTATUS(status);
#endif
		
	}

	ProcessHandle::ProcessHandle(const ProcessHandle& handle):
	_pImpl(handle._pImpl)
	{
		_pImpl->AddRef();
	}


	ProcessHandle::~ProcessHandle()
	{
		_pImpl->DecRef();
	}


	ProcessHandle::ProcessHandle(ProcessHandleImpl* pImpl):
	_pImpl(pImpl)
	{
		/*poco_check_ptr (_pImpl);*/
	}


	ProcessHandle& ProcessHandle::operator = (const ProcessHandle& handle)
	{
		if (&handle != this)
		{
			_pImpl->DecRef();
			_pImpl = handle._pImpl;
			_pImpl->AddRef();
		}
		return *this;
	}


	ProcessID ProcessHandle::GetID() const
	{
		return _pImpl->GetID();
	}


	int ProcessHandle::Wait() const
	{
		return _pImpl->Wait();
	}

	ProcessID Process::GetID()
	{
#ifdef WINDOWS
		return GetCurrentProcessId(); 
#else
		return getpid();
#endif
	}
	
	void Process::Times(long& userTime, long& kernelTime)
	{
#ifdef WINDOWS
		FILETIME ftCreation;
		FILETIME ftExit;
		FILETIME ftKernel;
		FILETIME ftUser;
		if (GetProcessTimes(GetCurrentProcess(), &ftCreation, &ftExit, &ftKernel, &ftUser) != 0)
		{
			ULARGE_INTEGER time;
			time.LowPart  = ftKernel.dwLowDateTime;
			time.HighPart = ftKernel.dwHighDateTime;
			kernelTime    = long(time.QuadPart/10000000L);
			time.LowPart  = ftUser.dwLowDateTime;
			time.HighPart = ftUser.dwHighDateTime;
			userTime      = long(time.QuadPart/10000000L);
		}
		else
		{
			userTime = kernelTime = -1;
		}
#else
		struct rusage usage;
		getrusage(RUSAGE_SELF, &usage);
		userTime   = usage.ru_utime.tv_sec;
		kernelTime = usage.ru_stime.tv_sec;
#endif
	}
	
	ProcessHandle Process::Launch(const std::string& command, const Args& args)
	{
		std::string initialDirectory;
		Env env;
		return ProcessHandle(Launch(command, args, initialDirectory, 0, 0, 0, env));
	}
	
	ProcessHandle Process::Launch(const std::string& command, const Args& args, const std::string& initialDirectory)
	{
		Env env;
		return ProcessHandle(Launch(command, args, initialDirectory, 0, 0, 0, env));
	}
	
	ProcessHandle Process::Launch(const std::string& command, const Args& args, Pipe* inPipe,	Pipe* outPipe, Pipe* errPipe)
	{
		std::string initialDirectory;
		Env env;
		return ProcessHandle(Launch(command, args, initialDirectory, inPipe, outPipe, errPipe, env));
	}
	
	ProcessHandle Process::Launch(const std::string& command, const Args& args, const std::string& initialDirectory, Pipe* inPipe, Pipe* outPipe, Pipe* errPipe)
	{
		Env env;
		return ProcessHandle(Launch(command, args, initialDirectory, inPipe, outPipe, errPipe, env));
	}
	
	ProcessHandle Process::Launch(const std::string& command, const Args& args, Pipe* inPipe, Pipe* outPipe, Pipe* errPipe, const Env& env)
	{
		std::string initialDirectory;
		return ProcessHandle(Launch(command, args, initialDirectory, inPipe, outPipe, errPipe, env));
	}
	
	ProcessHandle Process::Launch(const std::string& command, const Args& args, const std::string& initialDirectory, Pipe* inPipe, Pipe* outPipe, Pipe* errPipe, const Env& env)
	{
#ifdef WINDOWS
		std::string commandLine = command;
		for (Args::const_iterator it = args.begin(); it != args.end(); ++it)
		{
			commandLine.append(" ");
			commandLine.append(*it);
		}		

		STARTUPINFOA startupInfo;
		GetStartupInfoA(&startupInfo); // take defaults from current process
		startupInfo.cb          = sizeof(STARTUPINFOA);
		startupInfo.lpReserved  = NULL;
		startupInfo.lpDesktop   = NULL;
		startupInfo.lpTitle     = NULL;
		startupInfo.dwFlags     = STARTF_FORCEOFFFEEDBACK;
		startupInfo.cbReserved2 = 0;
		startupInfo.lpReserved2 = NULL;

		HANDLE hProc = GetCurrentProcess();
		bool mustInheritHandles = false;
		if (inPipe)
		{
			DuplicateHandle(hProc, inPipe->ReadHandle(), hProc, &startupInfo.hStdInput, 0, TRUE, DUPLICATE_SAME_ACCESS);
			mustInheritHandles = true;
			inPipe->Close(Pipe::CLOSE_READ);
		}
		else if (GetStdHandle(STD_INPUT_HANDLE))
		{
			DuplicateHandle(hProc, GetStdHandle(STD_INPUT_HANDLE), hProc, &startupInfo.hStdInput, 0, TRUE, DUPLICATE_SAME_ACCESS);
			mustInheritHandles = true;
		}
		else 
		{
			startupInfo.hStdInput = 0;
		}
		// outPipe may be the same as errPipe, so we duplicate first and close later.
		if (outPipe)
		{
			DuplicateHandle(hProc, outPipe->WriteHandle(), hProc, &startupInfo.hStdOutput, 0, TRUE, DUPLICATE_SAME_ACCESS);
			mustInheritHandles = true;
		}
		else if (GetStdHandle(STD_OUTPUT_HANDLE))
		{
			DuplicateHandle(hProc, GetStdHandle(STD_OUTPUT_HANDLE), hProc, &startupInfo.hStdOutput, 0, TRUE, DUPLICATE_SAME_ACCESS);
			mustInheritHandles = true;
		}
		else 
		{
			startupInfo.hStdOutput = 0;
		}
		if (errPipe)
		{
			DuplicateHandle(hProc, errPipe->WriteHandle(), hProc, &startupInfo.hStdError, 0, TRUE, DUPLICATE_SAME_ACCESS);
			mustInheritHandles = true;
		}
		else if (GetStdHandle(STD_ERROR_HANDLE))
		{
			DuplicateHandle(hProc, GetStdHandle(STD_ERROR_HANDLE), hProc, &startupInfo.hStdError, 0, TRUE, DUPLICATE_SAME_ACCESS);
			mustInheritHandles = true;
		}
		else
		{
			startupInfo.hStdError = 0;
		}
		if (outPipe) 
			outPipe->Close(Pipe::CLOSE_WRITE);
		if (errPipe)
			errPipe->Close(Pipe::CLOSE_WRITE);

		if (mustInheritHandles)
		{
			startupInfo.dwFlags |= STARTF_USESTDHANDLES;
		}

		const char* workingDirectory = initialDirectory.empty() ? 0 : initialDirectory.c_str();

		const char* pEnv = 0;
		std::vector<char> envChars;
		if (!env.empty())
		{
			envChars = getEnvironmentVariablesBuffer(env);
			pEnv = &envChars[0];
		}

		PROCESS_INFORMATION processInfo;
		DWORD creationFlags = GetConsoleWindow() ? 0 : CREATE_NO_WINDOW;
		BOOL rc = CreateProcess(
			NULL, 
			const_cast<char*>(commandLine.c_str()), 
			NULL, // processAttributes
			NULL, // threadAttributes
			mustInheritHandles,
			creationFlags,
			(LPVOID) pEnv, 
			workingDirectory, 
			&startupInfo, 
			&processInfo
			);
		if (startupInfo.hStdInput) 
			CloseHandle(startupInfo.hStdInput); //前边已经复制了。这里要减掉应用计数
		if (startupInfo.hStdOutput) 
			CloseHandle(startupInfo.hStdOutput);
		if (startupInfo.hStdError) 
			CloseHandle(startupInfo.hStdError);
		if (rc)
		{
			CloseHandle(processInfo.hThread);//显示关闭线程句柄。引用计数减掉1
			return new ProcessHandleImpl(processInfo.hProcess, processInfo.dwProcessId);
		}
		else 
			throw SystemException("Cannot launch process", command);
#else
		int pid = fork();
		if (pid < 0)
		{
			throw SystemException("Cannot fork process for", command);		
		}
		else if (pid == 0)
		{
			if (!initialDirectory.empty())
			{
				if (chdir(initialDirectory.c_str()) != 0)
				{
					_exit(72);
				}
			}

			setEnvironmentVariables(env);

			// setup redirection
			if (inPipe)
			{
				dup2(inPipe->ReadHandle(), STDIN_FILENO); //放到标准输入中。
				inPipe->Close(Pipe::CLOSE_BOTH);
			}
			// outPipe and errPipe may be the same, so we dup first and close later
			if (outPipe) 
				dup2(outPipe->WriteHandle(), STDOUT_FILENO);
			if (errPipe) 
				dup2(errPipe->WriteHandle(), STDERR_FILENO);
			if (outPipe) 
				outPipe->Close(Pipe::CLOSE_BOTH);
			if (errPipe) 
				errPipe->Close(Pipe::CLOSE_BOTH);
			// close all open file descriptors other than stdin, stdout, stderr
			for (int i = 3; i < getdtablesize(); ++i)
				close(i);

			char** argv = new char*[args.size() + 2];
			int i = 0;
			argv[i++] = const_cast<char*>(command.c_str());
			for (ArgsImpl::const_iterator it = args.begin(); it != args.end(); ++it) 
				argv[i++] = const_cast<char*>(it->c_str());
			argv[i] = NULL;
			execvp(command.c_str(), argv);
			_exit(72);
		}

		if (inPipe)  
			inPipe->Close(Pipe::CLOSE_READ);
		if (outPipe) 
			outPipe->Close(Pipe::CLOSE_WRITE);
		if (errPipe) 
			errPipe->Close(Pipe::CLOSE_WRITE);
		return 
			new ProcessHandleImpl(pid);
#endif
	}

	int32 Process::Wait(const ProcessHandle& handle)
	{
		handle.Wait();
	}
	void Process::Kill(const ProcessHandle& handle)
	{
		if (!handle._pImpl)
		{
			throw NotFoundException(" no Process Handle");
		}
		
#ifdef WINDOWS
		HANDLE h = handle._pImpl->GetProcess();
		if (TerminateProcess(h, 0) == 0)
		{
			CloseHandle(h);
			throw SystemException("cannot kill process");
		}
		CloseHandle(h);
#else
		Kill(handle.GetID());
#endif
	}

	void Process::Kill(ProcessID pid)
	{
#ifdef WINDOWS
		HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
		if (hProc)
		{
			if (TerminateProcess(hProc, 0) == 0)
			{
				CloseHandle(hProc);
				throw SystemException("cannot kill process");
			}
			CloseHandle(hProc);
		}
		else
		{
			switch (GetLastError())
			{
			case ERROR_ACCESS_DENIED:
				throw NoPermissionException("cannot kill process");
			case ERROR_NOT_FOUND: 
				throw NotFoundException("cannot kill process");
			default:
				throw SystemException("cannot kill process");
			}
		}
#else
		if (kill(pid, SIGKILL) != 0)
		{
			switch (errno)
			{
			case ESRCH:
				throw NotFoundException("cannot kill process");
			case EPERM:
				throw NoPermissionException("cannot kill process");
			default:
				throw SystemException("cannot kill process");
			}
		}
#endif
	}

	void Process::RequestTermination(ProcessID pid)
	{
#ifdef WINDOWS
		std::string evName("OKEYTRM");
		evName += TO_HEX_STRING_INT(pid,8);
		NamedEvent event(evName);
		event.Set();
#else
		if (kill(pid, SIGINT) != 0)
		{
			switch (errno)
			{
			case ESRCH:
				throw NotFoundException("cannot terminate process");
			case EPERM:
				throw NoPermissionException("cannot terminate process");
			default:
				throw SystemException("cannot terminate process");
			}
		}
#endif
	}
}