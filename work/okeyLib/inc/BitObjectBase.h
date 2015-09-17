/********************************************************************
	created:	2013/06/12
	created:	12-6-2013   20:32
	author:		okey
	
	purpose:	
*********************************************************************/


#ifndef __BIT_OBJECT_H__
#define __BIT_OBJECT_H__

#include "Types.h"

namespace okey
{

	class BitObjectBase
	{
		BitObjectBase():_bitList(NULL), _count(0), _blocks(0)
		{

		}
		~BitObjectBase()
		{
			if (_bitList)
			{
				delete []_bitList;
			}
		}

		bool CheckBit(int32 nBit)
		{
			if (nBit < 0 || nBit > MAX_BIT_SIZE)
			{
				return false;
			}
			int32 dindex = nBit/BIT_SIZE;
			int32 bitindex = nBit%BIT_SIZE;
			return m_BitList[dindex] & (0x00000001 << bitindex)?true:false;
		}

		bool SetBit(int32 nBit)
		{
			if (nBit < 0 || nBit > _count)
			{
				return false;
			}
			((uint8*)_bitList)[nBit >> 3] |= 1 << (nBit & 0x7);
// 			int32 dindex = nBit/BIT_SIZE;
// 			int32 bitindex = nBit%BIT_SIZE;
// 			m_BitList[dindex] |= (0x00000001 << bitindex);
			return true;
		}

		bool ClearBit(int32 nBit)
		{
			if (nBit < 0 || nBit > _count)
			{
				return false;
			}
			((uint8*)_bitList)[nBit >> 3] |= (0xff ^ 1 << (nBit & 0x7));
// 			int32 dindex = nBit/BIT_SIZE;
// 			int32 bitindex = nBit%BIT_SIZE;
// 			m_BitList[dindex] &= ~(0x00000001 << bitindex);
			return true;
		}

		void SetCount(uint32 nCount)
		{
			if (_bitList)
			{
				delete []_bitList;
				_bitList = NULL;
			}
			_count = nCount;
			_blocks = _count >> 5;
			if (_count & 31)
			{
				++_blocks;
			}
			_bitList = new uint32[_blocks];
			memset(_bitList, 0, _blocks* sizeof(uint32));
		}

		void ClearAllBit()
		{
			if (_bitList)
			{
				memset(_bitList,0,_blocks << 2);
			}
		}

		inline uint32 GetBlockCount() const{return _blocks;}
		inline uint32 GetLength() const{return _blocks * sizeof(uint32);}
		inline uint32 GetCount() const {return _count;}
		inline const uint8* GetBit() const{return (uint8*)_bitList;}

		BitObjectBase& operator=(const BitObjectBase& b)
		{
			SetCount(b._count);
			memcpy(_bitList, b._bitList, _blocks << 2);
			return *this;
		}

		void operator &=(const BitObjectBase& b)
		{
			//assert b._count <= _count;
			for(uint32 i = 0; i < _blocks; ++i)
			{
				_bitList[i] &= b._bitList[i];
			}
		}

		void operator |= (const BitObjectBase& b)
		{
			//assert b._count <= _count;
			for(uint32 i = 0; i < _blocks; ++i)
			{
				_bitList[i] |= b._bitList[i];
			}
		}

		BitObjectBase operator& (const BitObjectBase& b) const
		{
			//assert b._count <= _count;
			BitObjectBase n;
			n = *this;
			n &= b;
			return n;
		}

		BitObjectBase operator| (const BitObjectBase& b) const
		{
			//assert b._count <= _count;
			BitObjectBase n;
			n = *this;
			n |= b;
			return n;
		}
	protected:
		uint32* _bitList;
		uint32 _count;
		uint32 _blocks;
		//uint32 m_BitList[BIT_LIST_SIZE];
	};
}

#endif