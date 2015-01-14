/********************************************************************
	created:	2015/01/14
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __OKEY_PROCESS_H__
#define __OKEY_PROCESS_H__


namespace okey
{
	class ProcessHandleImpl;

	class ProcessHandle
	{
	public:
		ProcessHandle(const ProcessHandle& handle);
		~ProcessHandle();
		ProcessHandle& operator=(const ProcessHandle& handle);
		ProcessID GetID()const;
		int Wait() const;
	protected:
		ProcessHandle(ProcessHandleImpl* pImpl);
	private:
		ProcessHandle();
		ProcessHandleImpl* _pImpl;
		friend class Process;
	};

	class Process
	{

	};
}

#endif