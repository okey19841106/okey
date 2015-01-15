/********************************************************************
	created:	2015/01/15
	created:	16:32
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef _OKEY_PIPE_STREAM_H__
#define _OKEY_PIPE_STREAM_H__

#include "Stream/BufferedStreamBuf.h"
#include "ProcessPipe.h"
#include <istream>
#include <ostream>

namespace okey
{

	class PipeStreamBuf : public BufferdStreamBuf
	{

	public:
		PipeStreamBuf(const Pipe& pipe, openmode mode);
		~PipeStreamBuf();
		void close();
	protected:
		int readFromDevice(char* buffer, std::streamsize length);
		int writeToDevice(const char* buffer, std::streamsize length);
	private:
		enum
		{
			STREAM_BUFFER_SIZE = 1024,
		};
		Pipe _pipe;
	};

	class  PipeIOS: public virtual std::ios
	{
	public:
		PipeIOS(const Pipe& pipe, openmode mode);
		~PipeIOS();
		PipeStreamBuf* rdbuf();
		/// Returns a pointer to the internal PipeStreamBuf.
		void close();
		/// Flushes the stream and closes the pipe.

	protected:
		PipeStreamBuf _buf;
	};

	class  PipeOutputStream: public PipeIOS, public std::ostream
	{
	public:
		PipeOutputStream(const Pipe& pipe);
		~PipeOutputStream();
	};

	class  PipeInputStream: public PipeIOS, public std::istream
	{
	public:
		PipeInputStream(const Pipe& pipe);
		~PipeInputStream();
	};

}

#endif