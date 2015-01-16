/********************************************************************
	created:	2014/12/15
	created:	17:34
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BUFFERED_STREAM_BUFF_H__
#define __BUFFERED_STREAM_BUFF_H__

#include "BufferAlloctor.h"
#include <streambuf>
#include <iosfwd>
#include <ios>

namespace okey
{
	template <typename ch, typename tr, typename ba = TBuffAlloctor<ch> >
	class TBuffedStreamBuf: public std::basic_streambuf<ch, tr>
	{
	protected:
		typedef std::basic_streambuf<ch, tr> Base;
		typedef std::basic_ios<ch, tr> IOS;
		typedef ch char_type;
		typedef tr char_traits;
		typedef ba Allocator;
		typedef typename Base::int_type int_type;
		typedef typename Base::pos_type pos_type;
		typedef typename Base::off_type off_type;
		typedef typename IOS::openmode openmode;
	public:
		TBuffedStreamBuf(std::streamsize bufferSize, openmode mode):
		_bufsize(bufferSize),_mode(mode),_pBuffer(Allocator::allocate(_bufsize))
		{
			this->setg(_pBuffer + 4, _pBuffer + 4, _pBuffer + 4); //读
			this->setp(_pBuffer, _pBuffer + (_bufsize - 1));//写
		}

		~TBuffedStreamBuf()
		{
			Allocator::deallocate(_pBuffer, _bufsize);
		}

		virtual int_type overflow(int_type c)
		{
			if (!(_mode & IOS::out))
			{
				return char_traits::eof();
			}
			if ( c != char_traits::eof())
			{
				*this->pptr() = char_traits::to_char_type(c);//写指针
				this->pbump(1);
			}
			if (flushBuffer() == std::streamsize(-1))
			{
				return char_traits::eof();
			}
			return c;
		}

		virtual int_type underflow()
		{
			if (!(_mode & IOS::in))
			{
				return char_traits::eof();
			}
			if (this->gptr() && (this->gptr() < this->egptr())) //读指针
			{
				return char_traits::to_int_type(*this->gptr());
			}
			int32 putback = int32(this->gptr() - this->eback());//开始指针
			if (putback > 4)
			{
				putback = 4;
			}
			char_traits::move(_pBuffer + (4 - putback), this->gptr() - putback, putback);
			int32 n = readFromDevice(_pBuffer + 4, _bufsize - 4);
			if (n <= 0)
			{
				return char_traits::eof();
			}
			this->setg(_pBuffer + (4 - putback), _pBuffer + 4, _pBuffer + 4 + n);
			return char_traits::to_int_type(*this->gptr());
		}

		virtual int sync()
		{
			if (this->pptr() && this->pptr() > this->pbase())
			{
				if (flushBuffer() == -1)
				{
					return -1;
				}
			}
			return 0;
		}
	protected:
		void setMode(openmode mode){_mode = mode;}
		openmode getMode()const{return _mode;}
	private:
		virtual int32 readFromDevice(char_type* buffer, std::streamsize length)
		{
			return 0;
		}
		virtual int32 writeToDevice(const char_type* buffer, std::streamsize length)
		{
			return 0;
		}

		int32 flushBuffer()
		{
			int32 n = int32(this->pptr() - this->pbase());
			if (writeToDevice(this->pbase(), n))
			{
				this->pbump(-n);
				return n;
			}
			return -1;
		}
	private:
		std::streamsize _bufsize;
		char_type*	_pBuffer;
		openmode	_mode;
	private:
		TBuffedStreamBuf(const TBuffedStreamBuf&);
		TBuffedStreamBuf& operator=(const TBuffedStreamBuf&);
	};

	typedef TBuffedStreamBuf<char, std::char_traits<char> > BufferdStreamBuf;
}


#endif