#include "PreCom.h"
#include "ByteBuf.h"


namespace okey
{
	ByteBuf::ByteBuf():_rpos(0),_wpos(0)
	{
		_storage.reserve(DEFAULT_SIZE);
	}

	ByteBuf::ByteBuf(size_t res):_rpos(0),_wpos(0)
	{
		_storage.reserve(res);
	}
	ByteBuf::ByteBuf(const ByteBuf& buf):_rpos(buf._rpos), _wpos(buf._wpos),_storage(buf._storage)
	{

	}

	ByteBuf::~ByteBuf()
	{

	}

	void ByteBuf::clear()
	{
		_storage.clear();
		_rpos = _wpos = 0;
	}
	
	void ByteBuf::read(uint8* dest, size_t len)
	{
		if (_rpos + len <= size())
		{
			memcpy(dest, &_storage[_rpos], len);
		}
		else
		{
			//assert()
			memset(dest, 0, len);
		}
		_rpos += len;
	}

	void ByteBuf::resize(size_t newsize)
	{
		_storage.reserve(newsize);
		_rpos = 0;
		_wpos = size();
	}
	void ByteBuf::reserve(size_t ressize)
	{
		if (ressize > size())
		{
			_storage.reserve(ressize);
		}
	}
	void ByteBuf::append(const uint8* src, size_t cnt)
	{
		if (!cnt)
		{
			//assert
			return;
		}
		if (_storage.size() < _wpos + cnt)
		{
			_storage.resize(_wpos + cnt);
		}
		memcpy(&_storage[_wpos], src, cnt);
		_wpos += cnt;
	}
	void ByteBuf::put(size_t pos, const uint8* src, size_t cnt)
	{
		//assert
		memcpy(&_storage[_wpos], src, cnt);
	}

	void ByteBuf::hexlike()
	{
		uint32 j = 1, k = 1;
		uint32 finish = 0;
		printf("STORAGE_SIZE: %u\n", (uint32)size());
		for (uint32 i = 0; i < size(); ++i)
		{
			if ((i == j * 8) && (i != k * 16))
			{
				if (read<uint8>(i) < 0x0f)
				{
					printf("| 0%X ", read<uint8>(i));
				}
				else
				{
					printf("| %X ", read<uint8>(i));
				}
				++j;
			}
			else if ( i == (k* 16))
			{
				//rpos(rpos() - 16);
				printf(" | ");
				for (int32 x = 0; x <16; ++x)
				{
					printf("%c", read<uint8>(i - 16 +x));
				}
				if (read<uint8>(i) < 0x0f)
				{
					printf("\n0%X ", read<uint8>(i));
				}
				else
				{
					printf("\n%X ", read<uint8>(i));
				}
				++k,++j;
			}
			else
			{
				if (read<uint8>(i) < 0x0f)
				{
					printf("0%X ", read<uint8>(i));
				}
				else
				{
					printf("%X ", read<uint8>(i));
				}
			}
			++finish;
		}
		int32 t = finish % 16;
		int32 s = ( finish /16 )*16;
		if (t != 0)
		{
			printf(" | ");
			for (int32 i = 0; i < t; ++i)
			{
				printf("%c", read<uint8>(s + i));
			}
		}
		printf("\n");
	}
}