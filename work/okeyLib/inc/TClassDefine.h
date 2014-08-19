/********************************************************************
	created:	2014/08/19
	created:	15:23
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_T_CLASS_H__
#define __OKEY_T_CLASS_H__

#include "AnyTypeBase.h"
#include "ClassMember.h"
#include "ClassMethod.h"
#include "ClassFunctor.h"
#include "TClass.h"

namespace okey
{

#define REG_CLASS_BEGIN_BASE(classname) \
public:\
	class _my_ref_##classname : public TClass{\
	public:\
		~_my_ref_##classname(){}\
		_my_ref_##classname(){\
		SetName(#classname);
		//AddClass...
#define REG_CLASS_BEGIN(classname,baseclass) \
	public:\
	class _my_ref_##classname : public TClass{\
	public:\
	~_my_ref_##classname(){}\
	_my_ref_##classname(){\
	SetName(#classname);	\
	AddBaseClass(baseclass::GetStaticClass());
	//AddClass...

#define REG_CLASS_END(classname)	\
	}};	\
	static _my_ref_##classname m_Class_##classname;\
public:\
	static TClass* GetStaticClass(){return (TClass*)&m_Class_##classname; }	\
	virtual TClass* GetClass(){return (TClass*)&m_Class_##classname;}\
	virtual char* Read(char* pBuffer){return m_Class_##classname.Read(this,pBuffer);}\
	virtual char* Write(char* pBuffer){return m_Class_##classname.Write(this,pBuffer);}

#define  DECLARE_CLASS(classname)	\
	classname::_my_ref_##classname classname::m_Class_##classname;

#define REG_CLASS_MEMBER(classname,member,type,flag) \
	TAnyType<type>* pMem_##member = new TAnyType<type>(); \
	pMem_##member->SetName(#member);	\
	pMem_##member->SetFlag(flag);	\
	TClassMember* pClassMember_##member = new TClassMember(this,pMem_##member);	\
	pClassMember_##member->SetOffset(uint32(&((classname*)0)->member));	\
	AddMember(pClassMember_##member);

#define REG_CLASS_MEMBER_STR(classname,member,size,flag)	\
	TAnyTypeStr* pMem_##member = new TAnyTypeStr(size);	\
	pMem_##member->SetName(#member);	\
	pMem_##member->SetFlag(flag);	\
	TClassMember* pClassMember_##member = new TClassMember(this,pMem_##member);	\
	pClassMember_##member->SetOffset(uint32(&((classname*)0)->member));	\
	AddMember(pClassMember_##member);

#define REG_CLASS_MEMBER_ARRAY(classname,member,type,size,flag)	\
	TAnyType<type>* pType_##member = new TAnyType<type>();\
	TAnyTypeArray* pMem_##member = new TAnyTypeArray(pType_##member, size);\
	pMem_##member->SetName(#member);	\
	pMem_##member->SetFlag(flag);	\
	TClassMember* pClassMember_##member = new TClassMember(this,pMem_##member);	\
	pClassMember_##member->SetOffset(uint32(&((classname*)0)->member));	\
	AddMember(pClassMember_##member);

#define REG_CLASS_MEMBER_PTR(classname,member,type,flag)	\
	TAnyTypePtr<type>* pMem_##member = new TAnyTypePtr<type>();\
	pMem_##member->SetName(#member);	\
	pMem_##member->SetFlag(flag);	\
	TClassMember* pClassMember_##member = new TClassMember(this,pMem_##member);	\
	pClassMember_##member->SetOffset(uint32(&((classname*)0)->member));	\
	AddMember(pClassMember_##member);

#define REG_CLASS_MEMBER_CLASS(bclassname,member,classname,flag) \
	classname::_my_ref_##classname *pMem_##member = new classname::_my_ref_##classname();\
	pMem_##member->SetName(#member);	\
	pMem_##member->SetFlag(flag);	\
	TClassMember* pClassMember_##member = new TClassMember(this,pMem_##member);	\
	pClassMember_##member->SetOffset(uint32(&((bclassname*)0)->member));	\
	AddMember(pClassMember_##member);

#define REG_CLASS_METHOD(classname,method)	\
	TAnyTypeMethod* pMethod_##method = MethodTypeOf(&classname::method);	\
	pMethod_##method->SetName(#method);	\
	TClassMethod* pClass_Memthod_##method = new TClassMethod(this,pMethod_##method);	\
	AddMethod(pClass_Memthod_##method);
}


#endif