/********************************************************************
	created:	2014/08/12
	created:	16:47
	filename: 	
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_TCLASS_H__
#define __OKEY_TCLASS_H__

#include "AnyTypeBase.h"
#include <list>

namespace okey
{
	class TClassMember;
	class TClassMethod;

	class TClass :public TTypeBase //类也是一个种类型。
	{
	public:
		TClass():m_typeinfo(TYPE_STRUCT){}
		~TClass();

		virtual char* Read(void* pClassObj,char* pBuffer);
		virtual char* Write(void* pClassObj, char* pBuffer);

		TClassMember* findMember(const std::string& name);
		TClassMethod* findMethod(const std::string& name);

		bool AddMethod(const std::string& name, TClassMember* pMethod);
		bool AddMember(const std::string& name, TClassMethod* pField);
		bool AddBaseClass(const std::string& name, TClass* pClass);
	protected:
		std::list<TClass*> m_BaseClsList;
		std::list<TClassMember*> m_ClsList;
		std::list<TClassMethod*> m_MtdList;
	};
}
#endif