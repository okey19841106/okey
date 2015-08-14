#include <iostream>
#include <string>
#include "test.h"
#include "VectorString.h"
#include "Stream/FileStream.h"
#include "AssocVector.h"
#include "File/FileIni.h"
#include "StringHelper.h"
//#include "log/LogChannel.h"
#include "File/FileInfo.h"
#include "Template/Tuple.h"
#include "Notifications/NotificationQueue.h"
#include "Notifications/NotificationCenter.h"
#include "Notifications/Observer.h"
#include "NetWork/NetService.h"
#include "log/Logger.h"
#include "log/FileChannel.h"
#include "Template/TFunctoion.h"
#include "Stream/ByteBuf.h"
#include "ReflectEnum.h"

using namespace okey;
using namespace Template;
// void MyTest();
// void MyTest2();
void TestFileLog();
static void TestFuction();
void TestByte();



int main(int argc , char *argv[])
{

	//TestByte();
	 printf("%s is %d.", GET_ENUM_STRING(WeekDay,Monday).c_str(), GET_ENUM_VALUE(WeekDay,"Monday"));
	 return 0;
}



// class QTestNotification: public Notification
// {
// public:
// 	QTestNotification(const std::string& r):_data(r)
// 	{
// 
// 	}
// 	void handle1(Notification* a)
// 	{
// 		AutoPtr<Notification> nf = a;	
// 	}
// 	std::string _data;
// };
// 
// void MyTest()
// {
// 	NotificationQueue queue;
// 	Notification* pNf = queue.DequeueNotification();
// 	queue.EnqueueNotification(new Notification);
// 	pNf = queue.DequeueNotification();
// 	pNf->DecRef();
// 
// 	queue.EnqueueNotification(new QTestNotification("first"));
// 	queue.EnqueueNotification(new QTestNotification("second"));
// 	QTestNotification* pTNf = dynamic_cast<QTestNotification*>(queue.DequeueNotification());
// 	
// 	pTNf->DecRef();
// 	pTNf = dynamic_cast<QTestNotification*>(queue.DequeueNotification());
// 	pTNf->DecRef();
// 	pNf = queue.DequeueNotification();
// }
// 
// void MyTest2()
// {
// 	NotificationCenter nc;
// 	QTestNotification test1("ok");
// 	nc.AddObserver(Observer<QTestNotification, Notification>(&test1, &QTestNotification::handle1));
// 	nc.PostNotification(new Notification);
// 	nc.RemoveObserver(Observer<QTestNotification, Notification>(&test1, &QTestNotification::handle1));
// }

void TestFileLog()
{
	std::string name = "testlog";
	try
	{
		AutoPtr<FileChannel> pChannel = new FileChannel(name);
		pChannel->SetProperty(FileChannel::PROP_ROTATION, "2 K");
		pChannel->SetProperty(FileChannel::PROP_ARCHIVE, "number");
		pChannel->SetProperty(FileChannel::PROP_COMPRESS, "true");
		pChannel->Open();
		//Message msg("source", "This is a log file entry", Message::PRIO_INFORMATION);
		for (int i = 0; i < 200; ++i)
		{
			//pChannel->LogInstance( Message::PRIO_INFORMATION, "This is a log file entry");
		}
		Sleep(3000);
	}
	catch (...)
	{
		//remove(name);
		throw;
	}
	//remove(name);
	Sleep(4000);
}

static void test_static() { std::cout<<"test static!"<<std::endl;}

Function<void()> static_func(test_static);

static void TestFuction()
{
	static_func();
}

void TestByte()
{
	ByteBuf buf;
	for (int i = 0; i < 10; ++i)
	{
		buf<<i+50;
		buf<<(f32)(0.2+i);
	}
	buf<<"oke";
	buf.hexlike();
}