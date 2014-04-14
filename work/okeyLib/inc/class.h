/********************************************************************
	created:	2014/04/12
	author:		okey
	
	purpose:	把他当成容器，或者可以在代码里初始化他，这是肯定的。
*********************************************************************/

#ifndef __RTTI_CLASS_H__
#define __RTTI_CLASS_H__

#include <stddef.h>
#include <stdio.h>
#include <map>
#include "type.h"

namespace okey
{


	/**
	 * Class description flags
	 */
	enum ClassFlags 
	{ 
		CLS_ABSTRACT  = 0x0001,
		CLS_INTERNAL  = 0x0002,
		CLS_TRANSIENT = 0x0004
	};
    

	/**
	 * Class descriptor
	 */
	class  ClassDescriptor : public AnyType { 
	public:
		typedef void  (*DefaultConstructor)(void* ptr);
		typedef void* (*CreateInstanceFunc)();
		std::string getTypeName();
		int32 getNumberOfFields() { return fieldList.size();}
		std::string getName() { return name;}
		int  getSize() { return size;}
		int  getFlags() { return flags;	}
		void* newInstance();
		int getNumberOfBaseClasses() {return baseClassList.size();}
		int getNumberOfMethods() { return methodList.size();	}
		FieldDescriptor*  findField(const std::string& name);
		MethodDescriptor* findMethod(const std::string& name);
 		ClassDescriptor(char const* name, int size, 
				CreateInstanceFunc  createInstanceFunc, 
 				int flags); 
		ClassDescriptor(char const* name, int size, int flags);
		~ClassDescriptor();

		bool AddMethodDescriptor(const std::string& name, MethodDescriptor* pMethod);
		bool AddFieldDescriptor(const std::string& name, FieldDescriptor* pField);
		bool AddBaseClassDescriptor(const std::string& name, ClassDescriptor* pClass);
	  protected:
		std::map<std::string, MethodDescriptor*> methodList;
		std::map<std::string, FieldDescriptor*> fieldList;
		int                     flags;
		int                     size;
		bool                    initialized;
		std::string             name;
		std::map<std::string, ClassDescriptor*> baseClassList;
		DefaultConstructor		defaultConstructor;
		CreateInstanceFunc		createInstanceFunc;
		void buildClassDescriptor();
	};

}

#endif
