/********************************************************************
	created:	2015/08/13
	created:	15:37
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef DECLARE_ENUM
#define DECLARE_ENUM(T) enum T
#endif

#ifndef REG_ENUM
#define REG_ENUM(eval) eval,
#endif

#ifndef REG_ENUM_ID
#define REG_ENUM_ID(eval, ID) eval=ID,
#endif

////////////////////////////////////////////////////////////////////////////////////////////////
//所有的可以映射的枚举定义都在这里定义好
///////////////////////////////////////////////////////////////////////////////////////////////

DECLARE_ENUM(WeekDay)
{
	REG_ENUM_ID(Sunday,10)
	REG_ENUM_ID(Monday,Sunday+1)
	REG_ENUM_ID(Tuesday,123)
	REG_ENUM_ID(Wednesday,10)
	REG_ENUM_ID(Thursday,7)
	REG_ENUM_ID(Friday,8)
	REG_ENUM_ID(Saturday,12)
};


