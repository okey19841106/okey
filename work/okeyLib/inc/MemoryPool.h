/********************************************************************
	created:	2015/07/10
	created:	11:12
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_MEMORY_POOL_H___
#define __BASE_MEMORY_POOL_H___

#include "Thread/Mutex.h"
#include <vector>

namespace okey
{
	class MemoryPool
	{
	public:
		MemoryPool(std::size_t blockSize, int32 preAlloc =0 , int32 maxAlloc = 0);
		~MemoryPool();
		void* Get();
		void Release(void* ptr);
		inline std::size_t GetBlockSize() const{return _blockSize;}
		inline int32 GetAllocated() const{return _allocated;}
		inline int32 GetAvailable()const{return (int32)_blocks.size();}
	private:
		MemoryPool();
		MemoryPool(const MemoryPool&);
		MemoryPool& operator=(const MemoryPool&);
	private:
		enum{BLOCK_RESERVER = 128};
		typedef std::vector<char*> BlockVec;
		std::size_t _blockSize;
		int32 _maxAlloc;
		int32 _allocated;
		BlockVec _blocks;
		FastMutex _mutex;
	};
}


#endif