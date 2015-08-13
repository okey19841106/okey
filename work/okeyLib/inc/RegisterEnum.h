/********************************************************************
	created:	2015/08/13
	created:	15:39
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_REGISTER_ENUM_H__
#define __BASE_REGISTER_ENUM_H__

#include "ReflectEnum.h"

#undef ENUM_VALUE
#define ENUM_VALUE(val)

#define REGISTER_ENUM(name)  REFLECT_ENUM(name, ENUM_LIST )



#endif