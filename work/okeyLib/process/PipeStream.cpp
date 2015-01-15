#include "PreCom.h"
#include "PipeStream.h"


namespace okey
{
	PipeStreamBuf::PipeStreamBuf(const Pipe& pipe, openmode mode):BufferdStreamBuf(STREAM_BUFFER_SIZE,mode),_pipe(pipe)
	{

	}
	
	PipeStreamBuf::~PipeStreamBuf()
	{
		close();
	}

	void PipeStreamBuf::close()
	{
		_pipe.Close(Pipe::CLOSE_BOTH);
	}

	int PipeStreamBuf::readFromDevice(char* buffer, std::streamsize length)
	{
		_pipe.ReadBytes(buffer, (int)length);
	}

	int PipeStreamBuf::writeToDevice(const char* buffer, std::streamsize length)
	{
		_pipe.WriteBytes(buffer, (int)length);
	}

	PipeIOS::PipeIOS(const Pipe& pipe, openmode mode):_buf(pipe,mode)
	{

	}

	PipeIOS::~PipeIOS()
	{
		try
		{
			_buf.sync();
		}
		catch (...)
		{
		}
	}
	PipeStreamBuf* PipeIOS::rdbuf()
	{
		return &_buf;
	}
	
	void PipeIOS::close()
	{
		_buf.sync();
		_buf.close();
	}

	PipeOutputStream::PipeOutputStream(const Pipe& pipe):PipeIOS(pipe, std::ios::out), std::ostream(&_buf)
	{
	}


	PipeOutputStream::~PipeOutputStream()
	{
	}

	PipeInputStream::PipeInputStream(const Pipe& pipe):PipeIOS(pipe, std::ios::in),	std::istream(&_buf)
	{
	}


	PipeInputStream::~PipeInputStream()
	{
	}
}