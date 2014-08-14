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
		TClass();
		~TClass();

		virtual char* Read(void* pClassObj,char* pBuffer);
		virtual char* Write(void* pClassObj, char* pBuffer);

		TClassMember* findMember(const std::string& name);
		TClassMethod* findMethod(const std::string& name);

		void AddMethod(TClassMethod* pMethod);
		void AddMember(TClassMember* pField);
		void AddBaseClass(TClass* pClass);


		std::list<TClass*>& GetBaseClassList(){return m_BaseClsList;}
		std::list<TClassMember*>& GetClassMemberList(){return m_MemList;}
		std::list<TClassMethod*>& GetClassMethodList(){return m_MtdList;}



		TClass* GetBaseClass(const std::string& name);
		TClassMember* GetClassMember(const std::string& name);
		TClassMethod* GetClassMethod(const std::string& name);
	protected:



	protected:
		std::string m_Namespace;
		std::list<TClass*> m_BaseClsList;
		std::list<TClassMember*> m_MemList;
		std::list<TClassMethod*> m_MtdList;
	};
}
#endif