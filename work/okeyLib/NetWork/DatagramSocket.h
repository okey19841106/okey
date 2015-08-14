/********************************************************************
	created:	2015/07/30
	created:	14:37
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __DATA_GRAM_SOCKET_H__
#define __DATA_GRAM_SOCKET_H__


namespace okey
{
	class DatagramSocket
	{
	public:
		DatagramSocket();
		explicit DatagramSocket(SOCKET s);
		~DatagramSocket();


	};
}

#endif