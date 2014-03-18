/********************************************************************
	created:	2014/03/10
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __OKEY_BASE_TYPES_H__
#define __OKEY_BASE_TYPES_H__

#ifdef WINDOWS
 #include <Windows.h>
 
// #include <winsock2.h>
#endif

#include <iostream>
#include <fstream>
#include <string>

#include <cstdlib>
#include <cstdio>

#include <cstdarg>

#include <cmath>
#include <cerrno>







#ifdef WINDOWS
// #include <WinSock2.h>
// #include <Windows.h>
#elif defined(LINUX)

typedef SOCKET int
#define INVALID_SOCKET -1
#endif

///
/// The most common stuffs.
///
namespace okey
{

#ifdef __GNUC__
	typedef long long int int64;
	typedef unsigned long long int uint64;
#endif

#ifdef WINDOWS
	typedef __int64 int64;
	typedef unsigned __int64 uint64;
#endif

	typedef signed int int32;
	typedef unsigned int uint32;
	typedef signed short  int16;
	typedef unsigned short uint16;
	typedef signed char int8;
	typedef unsigned char uint8;
	typedef unsigned long int ulong_type;
	typedef signed long int long_type;
	typedef float	f32;
	typedef double	f64;

	#ifndef TRUE
	#define TRUE 1
	#endif

	#ifndef FALSE
	#define FALSE 0
	#endif

#ifdef WINDOWS
	//#define snprintf _snprintf sn
	#define atoll(a) _atoi64(a)
	#define atoull(a) _strtoui64(a, NULL, 10)
	#define atoul(a) strtoul( a, NULL, 10)
#endif

#ifdef WINDOWS               
	typedef DWORD ThreadID;
	typedef DWORD ProcessID;
#else                      
	typedef pthread_t ThreadID;
	typedef pid_t	ProcessID:
#endif

	static inline int32 int32abs(const int32 value)
	{
		return (value ^ (value >> 31)) - (value >> 31);
	}

	// fast int abs and recast to unsigned
	static inline uint32 int32abs2uint32(const int32 value)
	{
		return (uint32)(value ^ (value >> 31)) - (value >> 31);
	}

	template<typename To, typename From>
	inline To implicit_cast(From const &f) {
	  return f;
	}

	inline uint32 now()
	{
	#ifdef WINDOWS
		return GetTickCount();
	#else
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	#endif
	}

	template<class T>
	void Delete(T t)
	{
		if (t)
		{
			delete t;
			t = 0;
		}
	}

	struct uint24
	{
		uint32 val;

		uint24() {}
		inline operator uint32() { return val; }
		inline operator uint32() const { return val; }

		inline uint24(const uint24& a) {val=a.val;}
		inline uint24 operator++() {++val; val&=0x00FFFFFF; return *this;}
		inline uint24 operator--() {--val; val&=0x00FFFFFF; return *this;}
		inline uint24 operator++(int) {uint24 temp(val); ++val; val&=0x00FFFFFF; return temp;}
		inline uint24 operator--(int) {uint24 temp(val); --val; val&=0x00FFFFFF; return temp;}
		inline uint24 operator&(const uint24& a) {return uint24(val&a.val);}
		inline uint24& operator=(const uint24& a) { val=a.val; return *this; }
		inline uint24& operator+=(const uint24& a) { val+=a.val; val&=0x00FFFFFF; return *this; }
		inline uint24& operator-=(const uint24& a) { val-=a.val; val&=0x00FFFFFF; return *this; }
		inline bool operator==( const uint24& right ) const {return val==right.val;}
		inline bool operator!=( const uint24& right ) const {return val!=right.val;}
		inline bool operator > ( const uint24& right ) const {return val>right.val;}
		inline bool operator < ( const uint24& right ) const {return val<right.val;}
		inline const uint24 operator+( const uint24 &other ) const { return uint24(val+other.val); }
		inline const uint24 operator-( const uint24 &other ) const { return uint24(val-other.val); }
		inline const uint24 operator/( const uint24 &other ) const { return uint24(val/other.val); }
		inline const uint24 operator*( const uint24 &other ) const { return uint24(val*other.val); }

		inline uint24(const uint32& a) {val=a; val&=0x00FFFFFF;}
		inline uint24 operator&(const uint32& a) {return uint24(val&a);}
		inline uint24& operator=(const uint32& a) { val=a; val&=0x00FFFFFF; return *this; }
		inline uint24& operator+=(const uint32& a) { val+=a; val&=0x00FFFFFF; return *this; }
		inline uint24& operator-=(const uint32& a) { val-=a; val&=0x00FFFFFF; return *this; }
		inline bool operator==( const uint32& right ) const {return val==(right&0x00FFFFFF);}
		inline bool operator!=( const uint32& right ) const {return val!=(right&0x00FFFFFF);}
		inline bool operator > ( const uint32& right ) const {return val>(right&0x00FFFFFF);}
		inline bool operator < ( const uint32& right ) const {return val<(right&0x00FFFFFF);}
		inline const uint24 operator+( const uint32 &other ) const { return uint24(val+other); }
		inline const uint24 operator-( const uint32 &other ) const { return uint24(val-other); }
		inline const uint24 operator/( const uint32 &other ) const { return uint24(val/other); }
		inline const uint24 operator*( const uint32 &other ) const { return uint24(val*other); }
	};

}

#endif
