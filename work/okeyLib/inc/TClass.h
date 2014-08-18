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

// 		TClassMember* findMember(const std::string& name);
// 		TClassMethod* findMethod(const std::string& name);

		void AddMethod(TClassMethod* pMethod);
		void AddMember(TClassMember* pField);
		void AddBaseClass(TClass* pClass);


		std::list<TClass*>& GetBaseClassList(){return m_BaseClsList;}
		std::list<TClassMember*>& GetClassMemberList(){return m_MemList;}
		std::list<TClassMethod*>& GetClassMethodList(){return m_MtdList;}



		TClass* GetBaseClass(const std::string& name);
		TClassMember* GetClassMember(const std::string& name);
		TClassMethod* GetClassMethod(const std::string& name);


	public:
// 		template<typename Rt, typename Obj>
// 		void Invoke(Rt* result, const std::string& name,Obj* obj)
// 		{
// 			TClassMethod* pMethod = GetClassMethod(name);
// 			//assert("pMethod");
// 			pMethod->invoke(result,obj,NULL);
// 		}

		template<typename Obj>
		void Invoke(const std::string& name,Obj* obj)
		{
			TClassMethod* pMethod = GetClassMethod(name);
			//assert("pMethod");
			pMethod->invoke(NULL,obj,NULL);
		}

// 		template<typename Rt, typename Obj, typename P1>
// 		void Invoke(Rt* result, const std::string& name,Obj* obj, P1 param1)
// 		{
// 
// 			TClassMethod* pMethod = GetClassMethod(name);
// 			//assert("pMethod");
// 			void* Param[1];
// 			Param[0] = &param1;
// 			pMethod->invoke(result,obj,Param);
// 		}

		template<typename Rt, typename Obj, typename P1>
		Rt Invoke( const std::string& name,Obj* obj, P1 param1)
		{
		 
		 	TClassMethod* pMethod = GetClassMethod(name);
		 	//assert("pMethod");
		 	void* Param[1];
		 	Param[0] = &param1;
			Rt res;
		 	pMethod->invoke(&res,obj,Param);
			return res;
		}


		template<typename Obj, typename P1>
		void Invoke(const std::string& name,Obj* obj, P1 param1)
		{

			TClassMethod* pMethod = GetClassMethod(name);
			//assert("pMethod");
			void* Param[1];
			Param[0] = &param1;
			pMethod->invoke(NULL,obj,Param);
		}
	protected:



	protected:
		std::string m_Namespace;
		std::list<TClass*> m_BaseClsList;
		std::list<TClassMember*> m_MemList;
		std::list<TClassMethod*> m_MtdList;
	};

// 	template<typename Obj>
// 	inline void TClass::Invoke<void, Obj>(const std::string& name,Obj* obj)
// 	{
// 		TClassMethod* pMethod = findMethod(name);
// 		//assert("pMethod");
// 		pMethod->invoke(NULL,obj,NULL);
// 	}
// 
// 	template<typename Obj, typename P1>
// 	inline void TClass::Invoke<void,Obj,P1>(const std::string& name,Obj* obj, P1 param1)
// 	{
// 
// 		TClassMethod* pMethod = findMethod(name);
// 		//assert("pMethod");
// 		void* Param[1];
// 		Param[0] = &param1;
// 		pMethod->invoke(NULL,obj,Param);
// 	}
}
#endif