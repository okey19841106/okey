/********************************************************************
	created:	2015/01/14
	created:	16:32
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_PIPE_H__
#define __OKEY_PIPE_H__

#include "CRefcounter.h"

namespace okey
{
	class ProcessPipe : public CRefCounter
	{
	public:
		ProcessPipe();
		~ProcessPipe();
		int WriteBytes(const void* buffer, int length);	/// Sends the contents of the given buffer through
		int ReadBytes(void* buffer, int length);/// Receives data from the pipe and stores it
		Handle ReadHandle() const{return _readfd;}
		Handle WriteHandle() const{return _writefd;}
		void CloseRead();
		void CloseWrite();
	private:
		Handle _readfd;
		Handle _writefd;
	};

	class Pipe
	{
		enum CloseMode /// used by close()
		{
			CLOSE_READ  = 0x01, /// Close reading end of pipe.
			CLOSE_WRITE = 0x02, /// Close writing end of pipe.
			CLOSE_BOTH  = 0x03  /// Close both ends of pipe.
		};
	public:
		Pipe();
		~Pipe();
		Pipe(const Pipe& p);
		Pipe& operator=(const Pipe& p);
		int WriteBytes(const void* buffer, int length){ return _pipe->WriteBytes(buffer,length);}
		int ReadBytes(void* buffer, int length){return _pipe->ReadBytes(buffer,length);}
		Handle ReadHandle() const{return _pipe->ReadHandle();}
		Handle WriteHandle() const{return _pipe->WriteHandle();}
		void Close(CloseMode mode = CLOSE_BOTH);
	private:
		ProcessPipe* _pipe;
	};

}

#endif