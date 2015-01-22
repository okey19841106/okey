/********************************************************************
	created:	2015/01/22
	created:	10:41
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TEMPLATE_VOID_H__
#define __TEMPLATE_VOID_H__

namespace Template
{
	class Void
	{
	public:
		Void(){}
		~Void(){}
		Void(const Void& v){}
		~Void(){}
		Void& operator = (const Void& v){return *this;}
		bool operator ==(const Void& v) const{return true;}
		bool operator !=(const Void& v) const{return false;}
	};
}

#endif