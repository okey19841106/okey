/********************************************************************
	created:	2013/06/13
	created:	13-6-2013   22:22
	author:		okey
	
	purpose:	file reader
*********************************************************************/
#ifndef __OKEY_TABLE_LOADER_H__
#define __OKEY_TABLE_LOADER_H__

#include <string>


namespace okey
{
	class FileBase;
	class TableLoader
	{
	public:
		TableLoader();
		~TableLoader();

		bool Load(std::string filename);
		Char* GetLineBuffer(int32 nLineNum);
		template<typename T>
		T GetValue(std::string name, int32 nLineNum,T defValue);
		std::string GetValueString(std::string name, int32 nLineNum);
	protected:

	};
}


#endif