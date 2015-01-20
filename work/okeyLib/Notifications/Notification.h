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
		virtual ~Notification(); //�ڶ��ϴ����� ���ܵ���delete������ ͨ�����ü���ȥɾ���� ������������
	};
}

#endif