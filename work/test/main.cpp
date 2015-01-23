#include <iostream>
#include <string>
#include "test.h"
#include "VectorString.h"
#include "Stream/FileStream.h"
#include "AssocVector.h"
#include "File/FileIni.h"
#include "StringHelper.h"
#include "log/LogChannel.h"
#include "File/FileInfo.h"
#include "Template/Tuple.h"
#include "Notifications/NotificationQueue.h"
#include "Notifications/NotificationCenter.h"
#include "Notifications/Observer.h"
using namespace okey;

void MyTest();
void MyTest2();
int main(int argc , char *argv[])
{
	MyTest2();
	return 0;

}



class QTestNotification: public Notification
{
public:
	QTestNotification(const std::string& r):_data(r)
	{

	}
	void handle1(Notification* a)
	{
		AutoPtr<Notification> nf = a;	
	}
	std::string _data;
};

void MyTest()
{
	NotificationQueue queue;
	Notification* pNf = queue.DequeueNotification();
	queue.EnqueueNotification(new Notification);
	pNf = queue.DequeueNotification();
	pNf->DecRef();

	queue.EnqueueNotification(new QTestNotification("first"));
	queue.EnqueueNotification(new QTestNotification("second"));
	QTestNotification* pTNf = dynamic_cast<QTestNotification*>(queue.DequeueNotification());
	
	pTNf->DecRef();
	pTNf = dynamic_cast<QTestNotification*>(queue.DequeueNotification());
	pTNf->DecRef();
	pNf = queue.DequeueNotification();
}

void MyTest2()
{
	NotificationCenter nc;
	QTestNotification test1("ok");
	nc.AddObserver(Observer<QTestNotification, Notification>(&test1, &QTestNotification::handle1));
	nc.PostNotification(new Notification);
	nc.RemoveObserver(Observer<QTestNotification, Notification>(&test1, &QTestNotification::handle1));
}