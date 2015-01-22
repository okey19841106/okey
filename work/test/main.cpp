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

int main(int argc , char *argv[])
{
//  	std::string ip = "127.0.0.1";
//  	int port = 888;
//  	int isListen = FALSE;
//  	for (int i = 0; i < argc; ++i)
//  	{
//  		if (strcmp(argv[i], "-ip") == 0)
//  		{
//  			ip = argv[i+1];
//  		}
//  		else if (strcmp(argv[i], "port") == 0)
//  		{
//  			port = (int)atoi(argv[i+1]);
//  		}
//  		else if (strcmp(argv[i], "starttype") == 0)
//  		{
//  			isListen = atoi(argv[i+1]);
//  		}
//  	}
//  	okey::PeerBase* pPeer = new okey::PeerBase;
//  	if (!pPeer)
//  	{
//  		return 0;
//  	}
//  	pPeer->Init(argc,argv);
//  	if (isListen)
//  	{
//  		std::cout<<"start listen...."<<std::endl;
//  		pPeer->PeerAccept(ip.c_str(),port);
//  	}
//  	else
//  	{
//  		std::cout<<"start connecting...."<<std::endl;
//  		pPeer->PeerConnect(ip.c_str(),port);
//  		okey::PacketText pkt;
//  		pkt.flag = 1;
//  		pPeer->PeerSend(0,&pkt);
//  	}
//  	pPeer->PeerRun();
// 	std::cout<<"test ok!"<<std::endl;
// 	okey::ParamDefManager::GetSingleton().Load("../Data/Param/ParamDefine.xml");
// 	okey::ParamDataManager tParamData(okey::ParamDefManager::GetSingletonPtr());
// 	okey::NormalFile tFile;
// 	okey::CfgLoaderStream cfg(&tFile);
// 	tParamData.Load("../Data/Param/", &cfg);
// 	okey::ParamPool tPool;
// 	okey::ParamDef* pDef = okey::ParamDefManager::GetSingleton().GetParamDef(0);
// 	if (!pDef)
// 	{
// 		return 0;
// 	}
// 	tPool.SetParamDef(pDef);
// 	tPool.AllocParamBuffer();
// 	tParamData.InitParamPool(&tPool,0);
// 	tPool.PrintTheParam();
// 	char buff[512] = {0};
// 	int tSize = 512;
// 	int tStart = 0;
// 	tPool.Write(buff,tSize,tStart,1,true);
// 
// 	okey::ParamPool tPool2;
// 	tPool2.SetParamDef(pDef);
// 	tPool2.AllocParamBuffer();
// 	tPool2.Read(buff);
// 	tPool2.PrintTheParam();
//	test_c t;
	/*t.a = 1;*/
//	strcpy(t.str,"ok");
// 	for (int32 i = 0; i< 15; ++i)
// 	{
// 		t.arr[i] = i;
// 	}
// 	f32 b = 0.5;
// 	t.fptr = &b;
// 	t.t_c = 'b';
// 	SET_TCLASS_VALUE(t,a,(int32)1);
// 	SET_TCLASS_VALUE(t,sz,std::string("ok"));
// 	t.GetClass()->SetMemberValue("a",&t,(int32)1);
// 	t.GetClass()->SetMemberValue("sz",&t,std::string("ok"));
//	int32 rt = t.GetClass()->GetMemberValue<int32>("a",&t);
// 	int32 rt = GET_TCLASS_VALUE(t,a,int32);
// 	char buff[128] = {0};
// 	t.Write(buff);
// 	test_c t2;
// 	t2.Read(buff);
// 	t2.GetClass()->Invoke("fun_1",&t,(int32)5);
// 	int32 ret;
// 	t2.GetClass()->Invoke(&ret,"fun_2",&t, (int32)5);
// 	TClassMethod* pfun = t.GetClass()->GetClassMethod("fun_1");
// 	pfun->invoke(NULL,&t,(int32)5);
// 	test_b tb;
// 	tb.k = 8;
// 	tb.t = t;
// 	tb.f = 8.9;
// 	char buff2[256] = {0};
// 	tb.Write(buff2);
// 
// 	test_b tb2;
// 	tb2.Read(buff2);
// 	int* a =new int;
// 	TClass::GetClassCount();
//	test_c t_c;
	
// 	okey::BinString t; 
// 
// 	char buf[12] = "ok!!!!!";
// 	t.append(buf, buf + strlen(buf));
// 	std::cout<<t.c_str();
// 	char buf2[13] = "no";
// 	t.append(buf2, buf2 + strlen(buf2));
// 	std::cout<<t.c_str();
// 	okey::BinString t2(buf, 12);
	//using namespace okey;
	//FileStream test("2.txt");
	//std::string sz;
	////test<<1<<pendl;
	//while (!test.eof())
	//{
	//	std::getline(test,sz);
	//	std::cout<<sz<<std::endl;
	//}
	//std::getline(test,sz);

// 	AssocVector<std::string ,int> v;
// 	v["ok"] = 1;
// 	v["no"] = 2;
// 	v.insert(std::make_pair("1",5));
// 
// 	AssocVector<std::string ,int>::iterator itr = v.find("no");
// 	if (itr != v.end())
// 	{
// 		std::cout<<itr->first<<itr->second<<std::endl;
// 	}
	//char buff[] = " a b c d e f     ";
	//FileINI file("1.txt");
	////StringHelper::Trim(buff);
	//std::string ret;
	//file.GetValue("DefaultValue","Dlls",ret);
	//int32 u;
	//file.GetValue("DefaultValue","a",u);
	//file.SetValue("my","8",(int32)8);
	//file.Write();
// 	BinString bs;
// 	file.FillAllBuffer(bs);
// 	std::cout<<bs.c_str()<<bs.size();
// 	LogChannel<1024> channel;
// 	channel.Init("the log");
// 	channel.Log("ok", strlen("ok"), false);
// 	channel.Log("not ok",strlen("not ok"),false);
// 	return 0;
	//FileInfo ftest("../temp");
// 	ftest.SetModityTime(DateTime());
// 	std::cout<<		ftest.IsExisted()<<
// 	ftest.CanRead()<<
// 	ftest.CanWrite()<<
// 	ftest.CanExecute()<<
// 	ftest.IsFile()<<
// 	ftest.IsLink()<<
// 	ftest.IsDirectory()<<
// 	ftest.IsDevice()<<
// 	ftest.IsHidden()<<
// 	DateTime::toString(ftest.GetCreateTime())<<
// 	DateTime::toString(ftest.GetModityTime())<<std::endl;
	//std::cout<<ftest.GetSize();
	//ftest.CopyTo("../");
	//ftest.Remove(true);
// 	std::vector<std::string> v;
// 	FileInfo::ListRoots(v);
// 	std::cout<<FileInfo::GetAbsDir("temp")<<std::endl
// 	<<FileInfo::GetExtension("temp")<<std::endl
// 	<<FileInfo::GetFileName("temp")<<std::endl;
	//return 0;
	int a = 3;
	float b = 4.0;
	Template::Tuple<int, float> Vale(a,b);
	if (a == Vale.Get<0>())
	{
		std::cout<<"1111111"<<std::endl;
	}
	else
	{
		std::cout<<"1111111"<<std::endl;
	}
	//std::cout<< Vale.Get<0>() <<std::endl;
	return 0;


}