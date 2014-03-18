#include <iostream>
#include <string>
#include "Types.h"
#include "NetWork/PeerBase.h"
#include "NetWork/PacketDef.h"
#include "Param/ParamDefManager.h"
#include "File/cfgloader.h"
#include "File/NormalFile.h"
#include "Param/ParamDataManager.h"
#include "Param/ParamPool.h"

int main(int argc , char *argv[])
{
 	std::string ip = "127.0.0.1";
 	int port = 888;
 	int isListen = FALSE;
 	for (int i = 0; i < argc; ++i)
 	{
 		if (strcmp(argv[i], "-ip") == 0)
 		{
 			ip = argv[i+1];
 		}
 		else if (strcmp(argv[i], "port") == 0)
 		{
 			port = (int)atoi(argv[i+1]);
 		}
 		else if (strcmp(argv[i], "starttype") == 0)
 		{
 			isListen = atoi(argv[i+1]);
 		}
 	}
 	okey::PeerBase* pPeer = new okey::PeerBase;
 	if (!pPeer)
 	{
 		return 0;
 	}
 	pPeer->Init(argc,argv);
 	if (isListen)
 	{
 		std::cout<<"start listen...."<<std::endl;
 		pPeer->PeerAccept(ip.c_str(),port);
 	}
 	else
 	{
 		std::cout<<"start connecting...."<<std::endl;
 		pPeer->PeerConnect(ip.c_str(),port);
 		okey::PacketText pkt;
 		pkt.flag = 1;
 		pPeer->PeerSend(0,&pkt);
 	}
 	pPeer->PeerRun();
 	std::cout<<"test ok!"<<std::endl;
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
	return 0;
}