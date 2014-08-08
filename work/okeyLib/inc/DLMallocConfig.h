/********************************************************************
	created:	2014/08/08
	created:	15:35
	filename: 	DLMallocConfig.h
	author:		
	
	purpose:	
*********************************************************************/
#ifndef _DL_MALLOC_CONFIG_H__
#define _DL_MALLOC_CONFIG_H__

#define USE_DL_PREFIX
#define MSPACES

#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG	1
#define FOOTERS	1
#else
#define INSECURE 1
#endif 

#define USE_LOCKS	1
//#define ABORT	throw std::runtime_error("dlmalloc abort");
//#define CORRUPTION_ERROR_ACTION(M) void fun(void*state)
//#define USAGE_ERROR_ACTION(M,p) void fun(void*state,void*pointer);
#endif