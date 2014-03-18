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

#define MAX_BIT_SIZE	128
#define BIT_SIZE	32
#define BIT_LIST_SIZE	(MAX_BIT_SIZE/BIT_SIZE)
	class BitObjectBase
	{
		BitObjectBase()
		{
			ClearAllBit();
		}
		~BitObjectBase(){}

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
			if (nBit < 0 || nBit > MAX_BIT_SIZE)
			{
				return false;
			}
			int32 dindex = nBit/BIT_SIZE;
			int32 bitindex = nBit%BIT_SIZE;
			m_BitList[dindex] |= (0x00000001 << bitindex);
			return true;
		}

		bool ClearBit(int32 nBit)
		{
			if (nBit < 0 || nBit > MAX_BIT_SIZE)
			{
				return false;
			}
			int32 dindex = nBit/BIT_SIZE;
			int32 bitindex = nBit%BIT_SIZE;
			m_BitList[dindex] &= ~(0x00000001 << bitindex);
			return true;
		}

		void ClearAllBit()
		{
			memset(m_BitList,0,MAX_BIT_SIZE);
		}

	protected:
		uint32 m_BitList[BIT_LIST_SIZE];
	};
}

#endif