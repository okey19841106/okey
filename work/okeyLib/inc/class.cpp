#include "PreCom.h"
#include "class.h"
#include <string.h>
#include <stdlib.h>
#include "type.h"
#include "field.h"
#include "method.h"

namespace okey
{



	FieldDescriptor* ClassDescriptor::findField(const std::string& name) 
	{ 
		std::map<std::string, FieldDescriptor*>::iterator itr = fieldList.find(name);
		if (itr != fieldList.end())
		{
			return itr->second;
		}
		return NULL;
	}


	ClassDescriptor::ClassDescriptor(char const* name, int size, 
		CreateInstanceFunc  createInstanceFunc,
		int flags) : AnyType(RTTI_STRUCT) 
	{
		this->name = name;
		this->size = size;
		this->defaultConstructor = NULL;
		this->createInstanceFunc = createInstanceFunc;
		this->flags = flags;
		
		//需要注册类到管理器里。
// 		RTTIRepository* repo = RTTIRepository::getInstance();
// 		repo->addClass(this);
	}

	void* ClassDescriptor::newInstance()
	{
		if (createInstanceFunc) 
		{ 
			return (*createInstanceFunc)();
		}
		else 
		{
			void* p = new char[size];	
			(*defaultConstructor)(p);
			return p;
		}
	}

	ClassDescriptor::ClassDescriptor(char const* name, int size, int flags) 
		: AnyType(RTTI_STRUCT) 
	{
		this->name = name;
		this->size = size;
		this->defaultConstructor = NULL;
		this->createInstanceFunc = NULL;
		this->flags = flags;
// 		this->fieldList = NULL;
// 		this->methodList = NULL;
		initialized = false;
	}

// 	void ClassDescriptor::buildClassDescriptor()
// 	{
// 		int i, n, nb;
// 		FieldDescriptor *fd;
// 		MethodDescriptor* md;
// 
// // 		for (fd = fieldList, n = 0, nb = 0; fd != NULL; fd = fd->next) 
// // 		{ 
// // 			n += 1;
// // 			fd->declaringClass = this;
// // 			if (fd->type != NULL && fd->type->tag == RTTI_DERIVED) 
// // 			{ 
// // 				nb += 1;
// // 			}
// // 		}
// 		nBaseClasses = nb;
// // 		baseClasses = new ClassDescriptor*[nb];    
// // 		fields = new FieldDescriptor*[n];
// 		
// 		for (fd = fieldList, n = 0, nb = 0; fd != NULL; fd = fd->next) 
// 		{ 
// 			++n;
// 			fieldList[fd->getName()] = fd;
// 			//fields[n++] = fd;
// 			if (fd->type != NULL && fd->type->tag == RTTI_DERIVED) 
// 			{ 
// 				++nb;
// 				baseClassList[fd->getName()] = ((DerivedType*)fd->type)->getBaseClass();
// 				//baseClasses[nb++] = ((DerivedType*)fd->type)->getBaseClass();
// 			}
// 		}
// 		nBaseClasses = nb;
// 		nFields = n;
// 		//qsort(fields, n, sizeof(FieldDescriptor*), cmpFields);
// // 		for (i = 0; i < n; i++) 
// // 		{ 
// // 			fields[i]->index = i;
// // 		}
// 
// // 		for (n = 0, md = methodList; md != NULL; md = md->next) { 
// // 			n += 1;
// // 		}
// //		nMethods = n;
// 		//methods = new MethodDescriptor*[n];
// 		for (n = 0, md = methodList; md != NULL; md = md->next) 
// 		{ 
// 			++n;
// 			methodList[md->getName()] = md;
// 			//methods[n++] = md;
// 		}
// 		nMethods = n;
// // 		qsort(methods, n, sizeof(MethodDescriptor*), cmpMethods);
// // 		for (i = 0; i < n; i++) 
// // 		{ 
// // 			methods[i]->index = i;
// // 		}
// 		initialized = true;
// 	}


	std::string ClassDescriptor::getTypeName()
	{
		return name;
	}

	MethodDescriptor* ClassDescriptor::findMethod(const std::string& name) 
	{ 
		std::map<std::string, MethodDescriptor*>::iterator itr = methodList.find(name);
		if (itr != methodList.end())
		{
			return itr->second;
		}
		return NULL;
	}



	ClassDescriptor::~ClassDescriptor()
	{
// 		delete[] baseClasses;
// 		delete[] methods;
// 		delete[] fields;
		std::map<std::string, MethodDescriptor*>::iterator itr_m = methodList.begin();
		for (;itr_m != methodList.end();++itr_m)
		{
			if (itr_m->second)
			{
				delete itr_m->second;
				itr_m->second = NULL;
			}
		}
		methodList.clear();
		std::map<std::string, FieldDescriptor*>::iterator itr_f = fieldList.begin();
		for (;itr_f != fieldList.end();++itr_f)
		{
			if (itr_f->second)
			{
				delete itr_f->second;
				itr_f->second = NULL;
			}
		}
		fieldList.clear();
		std::map<std::string, ClassDescriptor*>::iterator itr_c = baseClassList.begin();
		for (;itr_c != baseClassList.end();++itr_c)
		{
			if (itr_c->second)
			{
				delete itr_c->second;
				itr_c->second = NULL;
			}
		}
		baseClassList.clear();
	}

	bool ClassDescriptor::AddMethodDescriptor(const std::string& name, MethodDescriptor* pMethod)
	{
		std::map<std::string, MethodDescriptor*>::iterator itr = methodList.find(name);
		if (itr != methodList.end())
		{
			return false;
		}
		methodList[name] = pMethod;
		return true;
	}

	bool ClassDescriptor::AddFieldDescriptor(const std::string& name, FieldDescriptor* pField)
	{
		std::map<std::string, FieldDescriptor*>::iterator itr = fieldList.find(name);
		if (itr != fieldList.end())
		{
			return false;
		}
		fieldList[name] = pField;
		return true;
	}

	bool ClassDescriptor::AddBaseClassDescriptor(const std::string& name, ClassDescriptor* pClass)
	{
		std::map<std::string, ClassDescriptor*>::iterator itr = baseClassList.find(name);
		if (itr != baseClassList.end())
		{
			return false;
		}
		baseClassList[name] = pClass;
		return true;
	}
}

