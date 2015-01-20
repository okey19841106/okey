/********************************************************************
	created:	2015/01/20
	created:	17:11
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __NOTIFICATION_H__
#define __NOTIFICATION_H__

#include "CRefcounter.h"
#include "AutoPtr.h"

namespace okey
{
	class Notification: public CRefCounter
	{
	public:
		typedef AutoPtr<Notification> Ptr;
	public:
		Notification();
		std::string GetName() const;
	protected:
		virtual ~Notification(); //在堆上创建。 不能调用delete。。。 通过引用计数去删除。 不会调用这个。
	};
}

#endif