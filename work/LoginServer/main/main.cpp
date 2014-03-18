/********************************************************************
	created:	2013/06/22
	created:	22-6-2013   23:32
	author:		okey
	
	purpose:	
*********************************************************************/
#include "PreCom.h"
#include "LoginServer.h"


int main(int argc , char *argv[])
{
	okey::LoginServer::GetSingleton().Init(argc,argv);
	okey::LoginServer::GetSingleton().Start();
	return 0;
}