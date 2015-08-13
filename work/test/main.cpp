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
using namespace okey;
using namespace Template;
// void MyTest();
// void MyTest2();
void TestFileLog();
static void TestFuction();
void TestByte();

#include "DefineEnum.h"
#define ENUM_LIST                                   \
	ENUM_NAME(Sunday     ENUM_VALUE(10)),       \
	ENUM_NAME(Monday     ENUM_VALUE(Sunday+1)),     \
	ENUM_NAME(Tuesday    ENUM_VALUE(123)),      \
	ENUM_NAME(Wednesday  ENUM_VALUE(10)) ,      \
	ENUM_NAME(Thursday   ENUM_VALUE(7)),        \
	ENUM_NAME(Friday     ENUM_VALUE(8)),        \
	ENUM_NAME(Saturday   ENUM_VALUE(12))
DEFINE_ENUM(WeekDay);

#include "RegisterEnum.h"
REGISTER_ENUM(WeekDay);

#include "DefineEnum.h"
#define ENUM_LIST                                   \
	ENUM_NAME(one     ENUM_VALUE(10)),       \
	ENUM_NAME(two     ENUM_VALUE(Sunday+1)),     \
	ENUM_NAME(three    ENUM_VALUE(123)),      
DEFINE_ENUM(Years);

#include "RegisterEnum.h"
REGISTER_ENUM(Years);

int main(int argc , char *argv[])
{

	//TestByte();
	 printf("%s is %d.", EnumHelper<WeekDay>::ToString(Monday), Monday);
	  printf("%s is %d.", EnumHelper<Years>::ToString(one), one);
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