#include "PreCom.h"
#include "MemoryPool.h"

namespace okey
{
	MemoryPool::MemoryPool(std::size_t blockSize, int32 preAlloc , int32 maxAlloc):
		_blockSize(blockSize),_maxAlloc(maxAlloc),_allocated(preAlloc)
	{
		//assert (maxalloc == 0 || maxalloc >= prealloc)
		//assert (prealloc>=0 && maxlloc >=0)
		int32 r = BLOCK_RESERVER;
		if (preAlloc > r)
		{
			r = preAlloc;
		}
		if (maxAlloc > 0 && maxAlloc < r)
		{
			r = maxAlloc;
		}
		_blocks.reserve(r);
		for(int32 i = 0; i < preAlloc; ++i)
		{
			_blocks.push_back(new char[_blockSize]);
		}
	}

	MemoryPool::~MemoryPool()
	{
		for(BlockVec::iterator itr = _blocks.begin(); itr != _blocks.end(); ++itr)
		{
			delete []*itr;
		}
	}

	void* MemoryPool::Get()
	{
		FastMutex::ScopedLock lock(_mutex);
		if (_blocks.empty())
		{
			if (_maxAlloc == 0 || _allocated < _maxAlloc)
			{
				++_allocated;
				return new char[_blockSize];
			}
			else
				throw OutOfMemoryException("MemoryPool exhausted!");
		}
		else
		{
			char* ptr = _blocks.back();
			_blocks.pop_back();
			return ptr;
		}
	}

	void MemoryPool::Release(void* ptr)
	{
		FastMutex::ScopedLock lock(_mutex);
		_blocks.push_back(reinterpret_cast<char*>(ptr));
	}
}