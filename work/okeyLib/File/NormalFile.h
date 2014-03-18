/********************************************************************
	created:	2013/06/16
	created:	16-6-2013   16:03
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __OKEY_NORMAL_FILE_H__
#define __OKEY_NORMAL_FILE_H__

#include "FileBase.h"

namespace okey
{
	

	class NormalFile: public FileBase
	{
	public:
		NormalFile();
		~NormalFile();
		virtual bool Open(const char* filename);
		virtual bool ReadLine(char* buffer, int32 len);
		virtual bool IsEnd();
		virtual bool Close();
// 	protected:
// 		bool isFirst;
	};
}


#endif