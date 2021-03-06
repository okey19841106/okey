/********************************************************************
	created:	2014/09/22
	created:	18:02
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __PACKET_FUNTION_H__
#define __PACKET_FUNTION_H__

#include "Types.h"
#include "Fuction.h"

namespace okey
{
	template<typename ClassObj, typename SubPacket, typename BasePacket>
	class CFunctionPacket: public CFunctionArg1Base<BasePacket>
	{
		typedef void (ClassObj::*f_)(SubPacket);
	public:
		CFunctionPacket(ClassObj*pclass, f_ pf):FunClass(pclass),fun(pf){}
		~CFunctionPacket(){}
		virtual void operator()(BasePacket pPacket)
		{
			SubPacket subPacket = (SubPacket)pPacket;
			if (subPacket)
			{
				(FunClass->*fun)(subPacket);
			}
		}
	protected:
	private:
		ClassObj* FunClass;
		f_ fun;
	};
}

#endif