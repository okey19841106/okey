/********************************************************************
	created:	2014/09/20
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __FILE_INI_H__
#define __FILE_INI_H__

#include <map>
#include "VectorString.h"

namespace okey
{
	class FileINI
	{
		typedef std::map<std::string, std::string>  ValueList;
		typedef std::map<std::string, ValueList> SectionList;
	public:
		FileINI();
		FileINI(const std::string& filename);
		~FileINI();
		
		bool Open(const std::string& filename);

	protected:
		bool Parse(BinString& buf);
		std::string GetLine(BinString& buf); //输入输出都有。。
		bool isComment(const std::string& line);
		bool isOffsetEnd();
		bool isSection(const std::string& line);
	private:
		std::string m_Filename;
		uint32 m_Filelen;
		char* m_strData;



	};
}


#endif