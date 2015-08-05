/********************************************************************
	created:	2015/08/05
	created:	10:40
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __STREAM_BYTE_BUF_H__
#define __STREAM_BYTE_BUF_H__

/*#include "VectorString.h"*/
#include "Types.h"
#include <vector>
#include <string>

namespace okey
{



	class ByteBuf
	{
	public:
		const static size_t DEFAULT_SIZE = 0x1000;

		ByteBuf();
		ByteBuf(size_t res);
		ByteBuf(const ByteBuf& buf);
		virtual ~ByteBuf();
		void clear();

		template<typename T>
		void append(T value)
		{
			append((uint8*)&value, sizeof(value));
		}
		template<typename T>
		void append(size_t pos, T value)
		{
			put(pos, (uint8*)&value, sizeof(value));
		}

		ByteBuf& operator<<(bool value)
		{
			append<char>((char)value);
			return *this;
		}

		ByteBuf& operator<<(uint8 value)
		{
			append<uint8>(value);
			return *this;
		}

		ByteBuf& operator<<(uint16 value)
		{
			append<uint16>(value);
			return *this;
		}

		ByteBuf& operator<<(uint32 value)
		{
			append<uint32>(value);
			return *this;
		}

		ByteBuf& operator<<(uint64 value)
		{
			append<uint64>(value);
			return *this;
		}
		ByteBuf& operator<<(int8 value)
		{
			append<int8>(value);
			return *this;
		}
		ByteBuf& operator<<(int16 value)
		{
			append<int16>(value);
			return *this;
		}
		ByteBuf& operator<<(int32 value)
		{
			append<int32>(value);
			return *this;
		}
		ByteBuf& operator<<(int64 value)
		{
			append<int64>(value);
			return *this;
		}
		ByteBuf& operator<<(f32 value)
		{
			append<f32>(value);
			return *this;
		}
		ByteBuf& operator<<(f64 value)
		{
			append<f64>(value);
			return *this;
		}
		ByteBuf& operator<<(const char* value)
		{
			append((uint8*)value, strlen(value));
			append((uint8)0);
			return *this;
		}
		ByteBuf& operator<<(const std::string& value)
		{
			append((uint8*)value.c_str(), value.length());
			append((uint8)0);
			return *this;
		}

		ByteBuf& operator>>(bool& value)
		{
			value = read<char>() > 0 ? true: false;
			return *this;
		}

		ByteBuf& operator>>(uint8& value)
		{
			value = read<uint8>();
			return *this;
		}

		ByteBuf& operator>>(uint16& value)
		{
			value = read<uint16>();
			return *this;
		}

		ByteBuf& operator>>(uint32& value)
		{
			value = read<uint32>();
			return *this;
		}

		ByteBuf& operator>>(uint64& value)
		{
			value = read<uint64>();
			return *this;
		}
		ByteBuf& operator>>(int8& value)
		{
			value = read<int8>();
			return *this;
		}
		ByteBuf& operator>>(int16& value)
		{
			value = read<int16>();
			return *this;
		}
		ByteBuf& operator>>(int32& value)
		{
			value = read<int32>();
			return *this;
		}
		ByteBuf& operator>>(int64& value)
		{
			value = read<int64>();
			return *this;
		}
		ByteBuf& operator>>(f32& value)
		{
			value = read<f32>();
			return *this;
		}
		ByteBuf& operator>>(f64& value)
		{
			value = read<f64>();
			return *this;
		}
		
		ByteBuf& operator>>(std::string& value)
		{
			value.clear();
			while(true)
			{
				char c = read<char>();
				if (c == 0)
				{
					break;
				}
				value += c;
			}
			return *this;
		}

		uint8 operator[](size_t pos)
		{
			return read<uint8>(pos);
		}
		inline size_t rpos()const {return _rpos;}
		inline size_t rpos(size_t r)
		{
			_rpos = r;
			return _rpos;
		}
		inline size_t wpos()const {return _wpos;}
		inline size_t wpos(size_t w)
		{
			_wpos = w;
			return _wpos;
		}

		template<typename T>
		T read()
		{
			T r = read<T>(_rpos);
			_rpos += sizeof(T);
			return r;
		}
		template<typename T>
		T read(size_t pos) const
		{
			if (pos + sizeof(T) > size())
			{
				//assert
				return (T)0;
			}
			else
			{
				return *((T*)&_storage[pos]);
			}
		}
		void append(const std::string& str)
		{
			append((uint8*)str.c_str(), str.size() + 1);
		}
		void append(const char* src, size_t cnt)
		{
			append((const uint8*)src, cnt);
		}
		void append(const ByteBuf& buffer)
		{
			if (buffer.size() > 0)
			{
				append(buffer.contents(), buffer.size());
			}
		}
// 		void append(const BinString& s)
// 		{
// 			if (s.size() > 0)
// 			{
// 				append((uint8*)(&(*s.begin())), s.size());
// 			}
// 		}
		void reverse()
		{
			std::reverse(_storage.begin(), _storage.end());
		}
		inline const uint8* contents() const{return &_storage[0];}
		inline size_t size() const{return _storage.size();}
		void read(uint8* dest, size_t len);
		void resize(size_t newsize);
		void reserve(size_t ressize);
		void append(const uint8* src, size_t cnt);
		void put(size_t pos, const uint8* src, size_t cnt);
		void hexlike();
	protected:
		size_t _rpos, _wpos;
		std::vector<uint8> _storage;
	};
}

#endif