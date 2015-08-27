#ifndef _SERVER_CONFIG_H__
#define _SERVER_CONFIG_H__




#if defined(WIN64) || defined(_WIN64)
#define _OS_WIN64_ 1
#define _OS_STRING_ "win64"
#elif defined(__WIN32__) || defined(_WIN32) || defined(__CYGWIN32__)||defined(__MINGW32__)
#define _OS_WIN32_ 1
#define _OS_STRING_ "win32"
#endif

#if defined(_OS_WIN32_) || defined(_OS_WIN64_)
#define _OS_WINDOWS_ 1
#endif

#if defined(__LINUX__)||defined(__linux__)
#define _OS_LINUX_ 1
#define _OS_STRING_ "linux"
#endif

#if defined(i386) || defined(__i386__) || defined(__x86__) || defined(_OS_WINDOWS_) \
	defined(__ia64__)|| defined(__amd64__)||defined(__x86_64__)
#define _ENDIAN_LITTLE_ 1
#endif

#ifndef _OS_STRING_
#define _OS_STRING_ "unknown"
#endif

#define USE_SYSTEM_NEW 0
#define THREAD_STACK_SIZE 0

#endif