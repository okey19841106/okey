/********************************************************************
	created:	2014/03/10
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef _OKEY_RTTI_TYPE_H__
#define _OKEY_RTTI_TYPE_H__

#include <string>
#include <vector>

namespace okey
{


	class ClassDescriptor;
	class FieldDescriptor;

	/**
	 * Class representing type
	 */
	class  AnyType 
	{ 
	public:
		/**
		 * Get type tag
		 * @return one of <code>TypeTag</code> enumaration constants
		 */     
		inline int  getTag() const
		{ 
			return tag;
		}

		/**
		 * Get name of the type as it is written in C, for example (</code>char*, int[10]</code>)
		 * @param buf buffer to which type name will be printed
		 */    
		virtual std::string getTypeName();

		static AnyType voidType;
		static AnyType charType;
		static AnyType uint8Type;
		static AnyType int8Type;
		static AnyType int16Type;
		static AnyType uint16Type;
		static AnyType int32Type;
		static AnyType uint32Type;
		static AnyType int64Type;
		static AnyType uint64Type;
		static AnyType f32Type;
		static AnyType f64Type;
		static AnyType boolType;
		static AnyType unknownType;

		enum TypeTag 
		{ 
			RTTI_UNKNOWN, 
			RTTI_VOID, 
			RTTI_CHAR, 
			RTTI_UINT8, 
			RTTI_INT8, 
			RTTI_INT16, 
			RTTI_UINT16, 
			RTTI_INT32, 
			RTTI_UINT32, 
			RTTI_INT64, 
			RTTI_UINT64, 
			RTTI_F32, 
			RTTI_F64, 
			RTTI_BOOL, 
			RTTI_ARRAY, 
			RTTI_STRUCT, 
			RTTI_PTR,  
			RTTI_DERIVED,
			RTTI_METHOD, 
		};
    
		/**
		 * Checks whether it is built-in type
		 */
		inline bool isBuiltin() 
		{ 
			return tag <= RTTI_BOOL;
		}
    
		/**
		 * Checks whether it is integer of floating point type
		 */
		inline bool isScalar() 
		{ 
			return tag > RTTI_VOID && tag <= RTTI_BOOL;
		} 
	
		/**
		 * Checks whether it is array type
		 */
		inline bool isArray() 
		{ 
			return tag == RTTI_ARRAY;
		}

		/**
		 * Checks whether it is pointer type
		 */
		inline bool isPointer()
		{ 
			return tag == RTTI_PTR;
		}

		/**
		 * Checks whether it is  class or struct type
		 */
		inline bool isClass() 
		{ 
			return tag == RTTI_STRUCT;
		}

		/**
		 * Checks whether type represents inhertited base class
		 */
		inline bool isBaseClass() 
		{ 
			return tag == RTTI_DERIVED;
		}
    
		/**
		 * Type descructor
		 */
		~AnyType();

	  protected:
		friend class ClassDescriptor;
		friend class FieldDescriptor;
		friend class MethodDescriptor;

		int   tag;

		void destroy() 
		{
			if (!isBuiltin()) 
			{ 
				delete this;
			}
		}

		AnyType(int tag) 
		{ 
			this->tag = tag;
		}
	};
 

	/**
	 * Pointer type
	 */
	class  PtrType : public AnyType 
	{     
	public:
		PtrType(AnyType* ptrType) : AnyType(RTTI_PTR) 
		{
			this->ptrType = ptrType;
		}
		std::string getTypeName();

		PtrType* GetPtrType()const{return ptrType;}
	  protected:
		AnyType* ptrType;
	};

	/**
	 * Array type
	 */
	class  ArrayType : public AnyType {     
	  public:
		ArrayType(AnyType* elemType, int32 nElems) : AnyType(RTTI_ARRAY) 
		{
			this->elemType = elemType;
			this->nElems = nElems;
		}
		std::string getTypeName();

		inline int  getArraySize() const{return nElems;}

		inline AnyType* getElementType() const{return elemType;}

	  protected:
		AnyType*  elemType;
		int32       nElems;
	};

	/**
	 * Type for base class 
	 */
	class  DerivedType : public AnyType {     
	  public:
		DerivedType(ClassDescriptor* baseClass) : AnyType(RTTI_DERIVED) 
		{
			this->baseClass = baseClass;
		}
    
		ClassDescriptor* getBaseClass() 
		{ 
			return baseClass;
		}

		std::string getTypeName();

	  protected:
		ClassDescriptor* baseClass;
	};

	/**
	 * Method type
	 */
	class  MethodType : public AnyType { 
	  public:
		std::string getTypeName();
    
		std::string getMethodDeclaration( const std::string& name);

		virtual void invoke(void* result, void* obj, std::vector<void*>& param) = 0;

		inline ClassDescriptor* getClass() const
		{ 
			return methodClass;
		}

		inline AnyType* getReturnType() const
		{ 
			return returnType;
		}

		const std::vector<AnyType*>& getParameterTypes() const
		{ 
			return paramTypes;
		}

		inline int32 getNumberOfParameters() const
		{ 
			return nParams;
		}

		MethodType() : AnyType(RTTI_METHOD) {}
		~MethodType()
		{ 
			//delete[] paramTypes;

		}
	  protected:
		friend class MethodDescriptor;
		//friend class RTTIBfdRepository;

		AnyType*  returnType;
		int        nParams;
		std::vector<AnyType*> paramTypes;
		//AnyType** paramTypes;
		ClassDescriptor* methodClass;
		bool       isStatic;
	};
	
}
#endif

