/********************************************************************
	created:	2013/06/22
	created:	22-6-2013   23:32
	author:		okey
	
	purpose:	
*********************************************************************/
#include "PreCom.h"
#include "GateServer.h"


int main(int argc , char *argv[])
{
	okey::GateServer::GetSingleton().Init(argc,argv);
	okey::GateServer::GetSingleton().Start();
	return 0;
}