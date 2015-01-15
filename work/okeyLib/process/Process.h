/********************************************************************
	created:	2015/01/14
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __OKEY_PROCESS_H__
#define __OKEY_PROCESS_H__

#include "Types.h"
#include <vector>
#include <map>
#include "CRefcounter.h"

namespace okey
{
	class Pipe;

	class ProcessHandleImpl: public CRefCounter
	{
	public:
		~ProcessHandleImpl();
		ProcessID GetID() const;
#ifdef WINDOWS
		ProcessHandleImpl(HANDLE hp, ProcessID pid);
		HANDLE GetProcess() const;
#else
		ProcessHandleImpl(ProcessID pid);
#endif
		int32 Wait() const;
	private:
#ifdef WINDOWS
		HANDLE _hProcess;
#endif
		ProcessID _pid;
	private:
		ProcessHandleImpl(const ProcessHandleImpl&);
		ProcessHandleImpl& operator = (const ProcessHandleImpl&);
	};

	class ProcessHandle
	{
	public:
		ProcessHandle(const ProcessHandle& handle);
		~ProcessHandle();
		ProcessHandle& operator=(const ProcessHandle& handle);
		ProcessID GetID()const;
		int32 Wait() const;
	protected:
		ProcessHandle(ProcessHandleImpl* pImpl);
	private:
		ProcessHandle();
		ProcessHandleImpl* _pImpl;
		friend class Process;
	};

	class Process
	{
	public:
		typedef std::vector<std::string> Args;
		typedef std::map<std::string, std::string> Env;
	public:
		/// Returns the process ID of the current process.
		static ProcessID GetID();
		/// Returns the number of seconds spent by the
		static void Times(long& userTime, long& kernelTime);
		/// Creates a new process for the given command and returns
		static ProcessHandle Launch(const std::string& command, const Args& args);
		/// Creates a new process for the given command and returns	
		static ProcessHandle Launch(const std::string& command, const Args& args, const std::string& initialDirectory);
		/// Creates a new process for the given command and returns
		static ProcessHandle Launch(const std::string& command, const Args& args, Pipe* inPipe,	Pipe* outPipe, Pipe* errPipe);
		/// Creates a new process for the given command and returns
		static ProcessHandle Launch(const std::string& command, const Args& args, const std::string& initialDirectory, Pipe* inPipe, Pipe* outPipe, Pipe* errPipe);
		/// Creates a new process for the given command and returns
		static ProcessHandle Launch(const std::string& command, const Args& args, Pipe* inPipe, Pipe* outPipe, Pipe* errPipe, const Env& env);
		/// Creates a new process for the given command and returns
		static ProcessHandle Launch(const std::string& command, const Args& args, const std::string& initialDirectory, Pipe* inPipe, Pipe* outPipe, Pipe* errPipe, const Env& env);
		static int32 Wait(const ProcessHandle& handle);		/// Waits for the process specified by handle to terminate
		static void Kill(const ProcessHandle& handle);		/// Kills the process specified by handle.
		static void Kill(ProcessID pid);		/// Kills the process with the given pid.
		static void RequestTermination(ProcessID pid);	/// Requests termination of the process with the give PID.
	};
}

#endif