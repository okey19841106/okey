/********************************************************************
	created:	2015/07/20
	created:	10:35
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __NAME_PIPE_H__
#define __NAME_PIPE_H__

#include "Types.h"
#include <string>

namespace okey
{
	class NamePipeServer
	{
		friend class NamePipe;
	public:
		NamePipeServer();
		NamePipeServer(const std::string& name) ;
		~NamePipeServer();
		bool Listen(const std::string& name) ;
		void Close();
		bool WaitClient(uint32 timeout);
		inline const std::string& path() const{ return _name; }
	  protected:
		Handle Accept();
	  private:
		NamePipeServer(const NamePipeServer&);
		NamePipeServer& operator=(const NamePipeServer&);
		Handle   _handle;
		std::string   _name;
	};

	class NamePipe
	{
	public:
		NamePipe();
		NamePipe(const std::string& name);
		NamePipe(NamePipeServer& srv);
		~NamePipe();
		bool Connect(const std::string& name);
		void Close();
		int32 Peek(char* buffer, uint32 count);
		inline bool isSeekable() const throw(){ return false; }
		int32 WriteBytes(const void* buffer, int length);
		int32 ReadBytes(void* buffer, int length);
	private:
		Handle _handle;
	};
}

#endif