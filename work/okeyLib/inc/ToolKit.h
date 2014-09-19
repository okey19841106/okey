/********************************************************************
	created:	2014/09/19
	created:	11:20
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef _TOOL_KIT_HELPER_H__
#define _TOOL_KIT_HELPER_H__

namespace okey
{
	class ToolKit
	{
	public:

		static void BytesToHex(uchar* buf, uint32 len, uchar* hex);
		static void HexToBytes(uchar* hex, uint32 len, uchar* buf);

		static void AtExit(void (*fuction)(void));
	};
}



#endif