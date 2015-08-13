/********************************************************************
	created:	2015/08/13
	created:	15:37
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_DEFINE_ENUM_H__
#define __BASE_DEFINE_ENUM_H__


#undef ENUM_LIST

#undef ENUM_NAME
#define ENUM_NAME(...)  __VA_ARGS__

#undef ENUM_VALUE
#define ENUM_VALUE(val) = val

#define ENUM_COTENTS(...)  __VA_ARGS__

#define DEFINE_ENUM(name)  enum name { ENUM_COTENTS(ENUM_LIST) };

#endif