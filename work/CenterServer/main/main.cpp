/********************************************************************
	created:	2013/06/22
	created:	22-6-2013   23:32
	author:		okey
	
	purpose:	
*********************************************************************/
#include "PreCom.h"
#include "CenterServer.h"


int main(int argc , char *argv[])
{
	okey::CenterServer::GetSingleton().Init(argc,argv);
	okey::CenterServer::GetSingleton().Start();
	return 0;
}