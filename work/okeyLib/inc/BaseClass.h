#ifndef __MARC_H__H__
#define __MARC_H__H__


#include "Types.h"
#include "AnyTypeBase.h"
#include "ClassManager.h"
#include "Factory.h"

namespace okey
{
	#define Reg_Base_Class_Begin(Class)\
		public:\
		class Manager##Class : public CClass{\
		public:  \
		~Manager##Class(){}\
		Manager##Class(){\
		SetClassName(#Class);\
		s_ClassManager.AddObj(this);

	#define Reg_Class_Begin(Class , pClass)\
		public:\
		class Manager##Class : public CClass{\
		public: \
		~Manager##Class(){}\
		Manager##Class(){\
		SetClassName(#Class);\
		SetParent(s_ClassManager.GetObj(#pClass));\
		s_ClassManager.AddObj(this);

	#define Add_Class_Member(Class,member,type,flag,des)\
		CClassMember<type>* tb_##member = new CClassMember<type>();\
		tb_##member->SetOffset(    static_cast<int32>(reinterpret_cast<int64>((&((Class*)(0))->member)) ) );\
		tb_##member->SetName(#member);\
		tb_##member->SetFlag(flag);\
		tb_##member->SetDes(#des);\
		AddMember(tb_##member);

	#define Reg_Base_Class_End(Class)\
		}};\
		static Manager##Class m_static##Class;\
		CClass* GetClassStatic(){return &m_static##Class;}\
		Manager##Class& Get##Class##Manager(){return m_static##Class;}\
		char* Read(char* pBuffer,uint32 flag){\
		return m_static##Class.Read(this,pBuffer,flag);}\
		char* Write(char* pBuffer, uint32 flag){\
		return m_static##Class.Write(this,pBuffer,flag);}

	#define Reg_Class_End(Class,pClass)\
		}};\
		static Manager##Class m_static##Class;\
		CClass* GetClassStatic(){return &m_static##Class;}\
		Manager##Class& Get##Class##Manager(){return m_static##Class;}\
		char* Read(char* pBuffer,uint32 flag){\
		pClass::Read(pBuffer,flag);\
		return m_static##Class.Read(this,pBuffer,flag);}\
		char* Write(char* pBuffer, uint32 flag){\
		pClass::Write(pBuffer,flag);\
		return m_static##Class.Write(this,pBuffer,flag);}


	#define Reg_Class_Initial(Class)\
		Class::Manager##Class  Class::m_static##Class;


	#define Reg_Factory0_Begin(Class,Alloc)\
		public:\
		class Class##Factory : public CFactoryArg0<Class>{\
		public:  \
		~Class##Factory(){}\
		Class##Factory():CFactoryArg0<Class>(Alloc){\
		SetObjName(#Class);\
		s_FactoryManager.AddObj(this);}

	#define Reg_Factory0_Initial(Class)\
		Class::Class##Factory Class::m_factory##Class;

	#define DECLARE_FACTORY_ARG0(classObj, classid, Alloc, manager) \
		private:\
	class CClassFactory_##classObj: public CFactoryArg0<classObj>{\
		public:\
		CClassFactory_##classObj():CFactoryArg0<classObj>(Alloc){\
		SetID(classid);\
		SetObjName(#classObj);\
		manager.AddObj(this);}\
		~CClassFactory_##classObj(){}\
		};\
		static CClassFactory_##classObj m_static##classObj##factory;

	#define FINISH_FACTORY_ARG0(classObj)\
	classObj::CClassFactory_##classObj classObj::m_static##classObj##factory;

#define Reg_Base_Class_BeginEx(Class, classMgr)\
		public:\
	class Manager##Class : public CClass{\
	public:  \
	~Manager##Class(){}\
	Manager##Class(){\
	SetClassName(#Class);\
	classMgr.AddObj(this);

#define Reg_Class_BeginEx(Class , pClass, classMgr)\
	public:\
	class Manager##Class : public CClass{\
	public: \
	~Manager##Class(){}\
	Manager##Class(){\
	SetClassName(#Class);\
	SetParent(s_ClassManager.GetObj(#pClass));\
	classMgr.AddObj(this);

#define Add_Class_Member_Char(Class,member,size,flag,des)\
	CClassMember_String* tb = new CClassMember_String(size);\
	tb->SetOffset(    static_cast<int32>(reinterpret_cast<int64>((&((Class*)(0))->member)) ) );\
	tb->SetName(#member);\
	tb->SetFlag(flag);\
	tb->SetDes(#des);\
	AddMember(tb);
}
#endif