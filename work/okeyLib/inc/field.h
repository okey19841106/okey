/********************************************************************
	created:	2014/03/11
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __FIELD_H__
#define __FIELD_H__

#include <string.h>


namespace okey
{


	/**
	 * Field qualifying flags
	 */
	enum FieldFlags 
	{ 
		FLD_INSTANCE  = 0x0001, 
		FLD_STATIC    = 0x0002, 
		FLD_CONST     = 0x0004, 
		FLD_PUBLIC    = 0x0010, 
		FLD_PROTECTED = 0x0020, 
		FLD_PRIVATE   = 0x0040, 
		FLD_VIRTUAL   = 0x0100, // used for virtual base classes
		FLD_VOLATILE  = 0x0200, 
		FLD_TRANSIENT = 0x0400
	}; 


	/**
	 * Field descriptor
	 */
	class FieldDescriptor { 
	  public:
		
		inline std::string getName() const
		{ 
			return name;
		}

		void setValue(void* obj, void* buf) 
		{ 
			memcpy((char*)obj + offs, buf, size);
		}

		void getValue(void* obj, void* buf) 
		{ 
			memcpy(buf, (char*)obj + offs, size);
		}

		ClassDescriptor* getDeclaringClass() const { return declaringClass;}
		inline int getOffset()const { return offs;}
		inline int getSize() const{ return size;	}
		AnyType* getType() const{ return type;}
		int getFlags() const{ return flags;}
		FieldDescriptor(char const* name, int offs, int size, int flags, AnyType* type) 
		{ 
			this->name = name;
			this->offs = offs;
			this->size = size;
			this->type = type;
			this->flags = flags;
			next = NULL; 
			chain = &next;
		}

		/**
		 * Comma operator used to concatenate field descriptors in the list
		 * @param field descriptor tail conctateneted with this head field descriptor, <code>chain</code>
		 * component of which contains address of <code>next</code> field of last element of the list     
		 * @return head of the list
		 */
		FieldDescriptor& operator, (FieldDescriptor& field) 
		{
			*chain = &field;
			chain = &field.next;
			return *this;
		}

		/**
		 * Get index of the field in the array returned by <Code>RTTIClassDescriptor::getFields()</code> method
		 * @param index of the field descriptor in the array sorted by field name
		 */
		inline int getIndex() const{return index;}
    
		/**
		 * Destructor of field descriptor
		 */
		~FieldDescriptor()
		{ 
			type->destroy();
		}
	  protected:
		friend class AnyType;
		friend class ClassDescriptor;
		int         flags;
		int         index;
		AnyType*	type;
		int         offs;
		int         size;
		std::string name;
		ClassDescriptor*  declaringClass;
		FieldDescriptor*  next;
		FieldDescriptor** chain;
	};

}
#endif
