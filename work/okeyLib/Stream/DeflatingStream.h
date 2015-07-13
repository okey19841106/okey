/********************************************************************
	created:	2015/07/13
	created:	19:18
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __DEFLATING_STREAM_H__
#define __DEFLATING_STREAM_H__

#include "BufferedStreamBuf.h"
#include "zlib/zlib.h"

namespace okey
{
	class DeflatingStreamBuf : public BufferdStreamBuf
	{
	public:
		enum StreamType
		{
			STREAM_ZLIB, /// Create a zlib header, use Adler-32 checksum.
			STREAM_GZIP  /// Create a gzip header, use CRC-32 checksum.
		};

		DeflatingStreamBuf(std::istream& istr, StreamType type, int level);	/// Creates a DeflatingStreamBuf for compressing data read from the given input stream.
		DeflatingStreamBuf(std::istream& istr, int windowBits, int level);/// Creates a DeflatingStreamBuf for compressing data read from the given input stream.
		DeflatingStreamBuf(std::ostream& ostr, StreamType type, int level);	/// Creates a DeflatingStreamBuf for compressing data passed through and forwarding it to the given output stream.
		DeflatingStreamBuf(std::ostream& ostr, int windowBits, int level);
		~DeflatingStreamBuf();
		int close();/// Finishes up the stream.  Must be called when deflating to an output stream.
	protected:
		int32 readFromDevice(char* buffer, std::streamsize length);
		int32 writeToDevice(const char* buffer, std::streamsize length);
		virtual int sync();

	private:
		enum 
		{
			STREAM_BUFFER_SIZE  = 1024,
			DEFLATE_BUFFER_SIZE = 32768
		};

		std::istream* _pIstr;
		std::ostream* _pOstr;
		char*    _buffer;
		z_stream _zstr;
		bool     _eof;
	};

	class DeflatingIOS: public virtual std::ios
	{
	public:
		DeflatingIOS(std::istream& istr, DeflatingStreamBuf::StreamType type = DeflatingStreamBuf::STREAM_ZLIB, int level = Z_DEFAULT_COMPRESSION);
		DeflatingIOS(std::istream& istr, int windowBits, int level);
		DeflatingIOS(std::ostream& ostr, DeflatingStreamBuf::StreamType type = DeflatingStreamBuf::STREAM_ZLIB, int level = Z_DEFAULT_COMPRESSION);	
		DeflatingIOS(std::ostream& ostr, int windowBits, int level);
		~DeflatingIOS();
		DeflatingStreamBuf* rdbuf();/// Returns a pointer to the underlying stream buffer.
	protected:
		DeflatingStreamBuf _buf;
	};

	class DeflatingOutputStream: public DeflatingIOS
	{
	public:
		DeflatingOutputStream(std::ostream& ostr, DeflatingStreamBuf::StreamType type = DeflatingStreamBuf::STREAM_ZLIB, int level = Z_DEFAULT_COMPRESSION);
		DeflatingOutputStream(std::ostream& ostr, int windowBits, int level);
		~DeflatingOutputStream();
		int close();
	protected:
		virtual int sync();
	};

	class DeflatingInputStream: public DeflatingIOS
	{
	public:
		DeflatingInputStream(std::istream& istr, DeflatingStreamBuf::StreamType type = DeflatingStreamBuf::STREAM_ZLIB, int level = Z_DEFAULT_COMPRESSION);
		DeflatingInputStream(std::istream& istr, int windowBits, int level);
		~DeflatingInputStream();
	};
}

#endif