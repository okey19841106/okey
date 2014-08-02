#ifndef __CLASS_H__
#define __CLASS_H__

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
		typedef FieldDescriptor* (*DescribeFieldsFunc)();
		typedef MethodDescriptor* (*DescribeMethodsFunc)();
		typedef void  (*DefaultConstructor)(void* ptr);
		typedef void* (*CreateInstanceFunc)();

		std::string getTypeName();

		/**
		 * Get next class. All classes in repository are linked in L1 list. 
		 * Repository <code>getFirstClass</code> method can be used to get reference to first class 
		 * descriptor in the list. And <code>getNext</code> method can be used to iterate through the      * list
		 * @return next class descriptor in the list or <code>NULL</code> if this class descriptor is the last
		 */
		ClassDescriptor* getNext() const{ return next;}
		std::map<std::string, FieldDescriptor*>& getFields() { return fields;}
		int32 getNumberOfFields() { return nFields;}
		std::string getName() { return name;}
		int  getSize() { return size;}

		/**
		 * Get class flags
		 * @return combination of <code>RTTIClassFlags</code> flags
		 */
		int  getFlags() { return flags;	}

		/**
		 * Createnew instance of the class
		 * @return newly created instance
		 */
		void* newInstance();
		std::map<std::string, ClassDescriptor*>& getBaseClasses() { return baseClasses;}
		int getNumberOfBaseClasses() {return nBaseClasses;}
		std::map<std::string, MethodDescriptor*>& getMethods() { return methods;}
		int getNumberOfMethods() { return nMethods;	}
		FieldDescriptor*  findField(const std::string& name);
		MethodDescriptor* findMethod(const std::string& name);

		ClassDescriptor(char const* name, int size, 
				DescribeFieldsFunc  describeFieldsFunc,
				DescribeMethodsFunc describeMethodsFunc, 
				CreateInstanceFunc  createInstanceFunc, 
				int flags); 
		ClassDescriptor(char const* name, int size, int flags);
		~ClassDescriptor();

	  protected:
		friend class RTTIRepository;
		friend class RTTIBfdRepository;

		ClassDescriptor*		next;
		ClassDescriptor*		collisionChain;

		MethodDescriptor*		methodList; //函数链表。。。
		std::map<std::string, MethodDescriptor*> methods;
		int                     nMethods;

		FieldDescriptor*		fieldList;//成员变量链表。。
		std::map<std::string, FieldDescriptor*> fields;
		int                     nFields;
		int                     flags;
		int                     size;
		bool                    initialized;
		std::string             name;
		unsigned                hashCode;
		int                     nBaseClasses;
		std::map<std::string, ClassDescriptor*> baseClasses;
		DefaultConstructor		defaultConstructor;
		CreateInstanceFunc		createInstanceFunc;
		void buildClassDescriptor();
	};

}

#endif
