#ifndef __UTIL_ID__
#define __UTIL_ID__

#ifdef WINDOWS
#pragma  warning(disable: 4522)
#endif
#include "Types.h"

namespace okey
{
	uint32 crc32(const unsigned char* s, uint32 len);

	class UtilID
	{
	public:
		UtilID():m_utilid(0){}
		UtilID(uint32 id):m_utilid(id){}
		UtilID(const char* s)
		{
			m_utilid = StringToUtilID(s, (uint32)strlen(s));
		}
		UtilID(const UtilID& uid);
		bool operator<(UtilID& uid);
		bool operator<(const UtilID&uid)const;
		bool operator>(const UtilID& uid)const;
		bool operator>(UtilID& uid);
		bool operator==(const UtilID& uid)const;
		bool operator==(UtilID& uid);
		UtilID& operator = (const UtilID& uid);
		UtilID& operator = (UtilID& uid);
		UtilID& operator = (uint32 uid);
		UtilID& operator = (char* s);
		UtilID& operator = (const char* s);
		uint32 GetUint32(){return m_utilid;}
		~UtilID()
		{

		}
		static uint32 StringToUtilID(const char* s, uint32 len);
	private:
		uint32 m_utilid;
	};
}




#endif