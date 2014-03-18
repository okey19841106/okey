/********************************************************************
	created:	2014/03/12
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __METHOD_H__
#define __METHOD_H__


namespace okey
{


	/**
	 * Method qualifying flags
	 */
	enum MethodFlags { 
		MTH_INSTANCE  = FLD_INSTANCE, 
		MTH_STATIC    = FLD_STATIC, 
		MTH_CONST     = FLD_CONST, 
		MTH_PUBLIC    = FLD_PUBLIC, 
		MTH_PROTECTED = FLD_PROTECTED, 
		MTH_PRIVATE   = FLD_PRIVATE, 
		MTH_VIRTUAL   = FLD_VIRTUAL, 
		MTH_CONSTRUCTOR = 0x0200, 
		MTH_ABSTRACT    = 0x0400 
	}; 


	/**
	 * Method descriptor
	 */
	class MethodDescriptor 
	{ 
	public:
		/**
		 * Get method's name
		 */
		inline std::string getName() const{ return name;}
    
		/**
		 * Gte type of the method
		 * @return method type
		 */
		inline MethodType* getType() const{ return type;}
    
		/**
		 * Get flags associated with the method
		 * @return combination of <code>RTTIMethodFlags>/code> flags
		 */
		inline int getFlags() const{ return flags;	}


		/**
		 * Print to the buffer forward declaration of the method, ifor example:
		 * <PRE>
		 *      void SomeClass::foo(char* name);
		 * </PRE>
		 * @param buf buffer to which method declaration will be printed
		 */
		std::string getMethodDeclaration() {return type->getMethodDeclaration(name);}

		/**
		 * Invoke method
		 * @param result pointer to the location where method result will be stored. 
		 * @param obj target object (ignired for static methods)
		 * @param parameters array of pointer to the parameter values
		 */
		void invoke(void* result, void* obj, void* parameters[]) 
		{ 
			type->invoke(result, obj, parameters);
		}

		/**
		 * Get class to which the method belongs
		 * @return descriptor of the class containing this method
		 */
		ClassDescriptor* getDeclaringClass() const {return type->getClass();}

		/**
		 * Method descriptor constructor
		 * @param name name of the method
		 * @param flags method qualifiers
		 * @param type method type
		 */
		MethodDescriptor(char const* name, int flags, MethodType* type) 
		{ 
			this->name = name;
			this->flags = flags;
			this->type = type;
			type->isStatic = (flags & MTH_STATIC) != 0; 
			next = NULL; 
			chain = &next;
		}

		/**
		 * Comma operator used to concatenate metod descriptors in the list
		 * @param  method descriptor tail conctateneted with this head method descriptor, <code>chain</code>
		 * component of which contains address of <code>next</code> field of last element of the list     
		 * @return head of the list
		 */
		MethodDescriptor& operator, (MethodDescriptor& method) 
		{
			*chain = &method;
			chain = &method.next;
			return *this;
		}
    
		/**
		 * Destructor of method descriptor
		 */
		~MethodDescriptor() 
		{ 
			type->destroy();
		}

		/**
		 * Get index of the metod in the array returned by <Code>RTTIClassDescriptor::getMethods()</code> method
		 * @param index of method descriptor in the array sorted by method name
		 */
		int getIndex() const {return index;}

	  protected:
		friend class AnyType;
		friend class ClassDescriptor;
		/*friend class RTTIBfdRepository;*/
	

		int             flags;
		int             index;
		MethodType*		type;
		std::string     name;

		MethodDescriptor*  next;
		MethodDescriptor** chain;
	};

}

#endif
