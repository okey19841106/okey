/********************************************************************
	created:	2015/07/24
	created:	15:54
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __DYNAMIC_ANY_H__
#define __DYNAMIC_ANY_H__


namespace okey
{
	class DynamicAny
	{
	public:
		DynamicAny();
		template<typename T>
		DynamicAny(const T& )
	};
}

#endif