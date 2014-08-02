#include "PreCom.h"
#include <string.h>
#include <stdlib.h>
#include "reflect.h"

namespace okey
{



	FieldDescriptor* ClassDescriptor::findField(const std::string& name) 
	{ 
		std::map<std::string, FieldDescriptor*>::iterator itr = fields.find(name);
		if (itr != fields.end())
		{
			return itr->second;
		}
		return NULL;
	}

// 	static int cmpFields(const void* p, const void* q) { 
// 		return strcmp((*(RTTIFieldDescriptor**)p)->getName(), (*(RTTIFieldDescriptor**)q)->getName());
// 	} 
// 
// 	static int cmpMethods(const void* p, const void* q) { 
// 		return strcmp((*(RTTIMethodDescriptor**)p)->getName(), (*(RTTIMethodDescriptor**)q)->getName());
// 	} 


	ClassDescriptor::ClassDescriptor(char const* name, int size, 
		DescribeFieldsFunc  describeFieldsFunc,
		DescribeMethodsFunc describeMethodsFunc, 
		CreateInstanceFunc  createInstanceFunc,
		int flags) : AnyType(RTTI_STRUCT) 
	{
		this->name = name;
		this->size = size;
		this->defaultConstructor = NULL;
		this->createInstanceFunc = createInstanceFunc;
		this->flags = flags;
		fieldList = (*describeFieldsFunc)();
		methodList = (*describeMethodsFunc)();
		buildClassDescriptor();
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
		this->fieldList = NULL;
		this->methodList = NULL;
		initialized = false;
	}

	void ClassDescriptor::buildClassDescriptor()
	{
		int i, n, nb;
		FieldDescriptor *fd;
		MethodDescriptor* md;

// 		for (fd = fieldList, n = 0, nb = 0; fd != NULL; fd = fd->next) 
// 		{ 
// 			n += 1;
// 			fd->declaringClass = this;
// 			if (fd->type != NULL && fd->type->tag == RTTI_DERIVED) 
// 			{ 
// 				nb += 1;
// 			}
// 		}
		nBaseClasses = nb;
// 		baseClasses = new ClassDescriptor*[nb];    
// 		fields = new FieldDescriptor*[n];
		
		for (fd = fieldList, n = 0, nb = 0; fd != NULL; fd = fd->next) 
		{ 
			++n;
			fields[fd->getName()] = fd;
			//fields[n++] = fd;
			if (fd->type != NULL && fd->type->tag == RTTI_DERIVED) 
			{ 
				++nb;
				baseClasses[fd->getName()] = ((DerivedType*)fd->type)->getBaseClass();
				//baseClasses[nb++] = ((DerivedType*)fd->type)->getBaseClass();
			}
		}
		nBaseClasses = nb;
		nFields = n;
		//qsort(fields, n, sizeof(FieldDescriptor*), cmpFields);
// 		for (i = 0; i < n; i++) 
// 		{ 
// 			fields[i]->index = i;
// 		}

// 		for (n = 0, md = methodList; md != NULL; md = md->next) { 
// 			n += 1;
// 		}
//		nMethods = n;
		//methods = new MethodDescriptor*[n];
		for (n = 0, md = methodList; md != NULL; md = md->next) 
		{ 
			++n;
			methods[md->getName()] = md;
			//methods[n++] = md;
		}
		nMethods = n;
// 		qsort(methods, n, sizeof(MethodDescriptor*), cmpMethods);
// 		for (i = 0; i < n; i++) 
// 		{ 
// 			methods[i]->index = i;
// 		}
		initialized = true;
	}


	std::string ClassDescriptor::getTypeName()
	{
		return name;
	}

	MethodDescriptor* ClassDescriptor::findMethod(const std::string& name) 
	{ 
// 		int l = 0, r = nMethods;
// 		while (l < r) { 
// 			int i = (l + r) >> 1;
// 			if (strcmp(name, methods[i]->name) > 0) { 
// 				l = i+1;
// 			} else { 
// 				r = i;
// 			}
// 		}
// 		if (r < nMethods && strcmp(methods[r]->name, name) == 0) { 
// 			return methods[r];
// 		}
		std::map<std::string, MethodDescriptor*>::iterator itr = methods.find(name);
		if (itr != methods.end())
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
	}

}

