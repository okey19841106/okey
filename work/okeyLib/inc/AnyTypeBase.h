/********************************************************************
	created:	2014/03/05
	author:		okey
	
	purpose:	
*********************************************************************/


#ifndef __OKEY_ANY_TYPE_BASE_
#define __OKEY_ANY_TYPE_BASE_

#ifdef WINDOWS
#pragma warning(disable: 4800)
#endif

#include "Types.h"
#include <string>
#include <map>
#include "Fuction.h"
#include "UtilID.h"

namespace okey
{

	enum MemberType
	{
		Type_Ser = 0x00000001<<0,
		Type_Print = 0x00000001<<1,
	};

	enum TypeTag 
	{ 
		TYPE_UNKNOWN, 
		TYPE_VOID, 
		TYPE_CHAR, 
		TYPE_UINT8, 
		TYPE_INT8, 
		TYPE_INT16, 
		TYPE_UINT16, 
		TYPE_INT32, 
		TYPE_UINT32, 
		TYPE_INT64, 
		TYPE_UINT64, 
		TYPE_F32, 
		TYPE_F64, 
		TYPE_BOOL, 
		TYPE_ARRAY, 
		TYPE_STRUCT, 
		TYPE_PTR,  
		TYPE_DERIVED,
		TYPE_METHOD, 
	};

	class TTypeBase
	{
	public:
		TTypeBase();
		~TTypeBase();
		
// 		inline void SetPtr(void* ptr){m_pPtr = ptr;}
// 		inline void* GetPtr()const{return m_pPtr;}
// 
// 		void* operator->(){return m_pPtr;}

		inline int32 GetSize()const{return m_size;}
		inline void SetSize(const int32& n){m_size = n;}

// 		inline int32 GetOffset()const{return m_offset;}
// 		inline void SetOffset(const int32&n){m_offset = n;}

		inline bool CheckFlag(const uint32& flag){return m_flag&flag;}
		inline void SetFlag(const uint32& flag){m_flag = flag;}
		inline uint32 GetFlag()const{return m_flag;}
		inline uint32 AddFlag(const uint32& flag){return m_flag|flag;}

// 		virtual char* Read(void* pClassObj,char* pBuffer) {};
// 		virtual char* Write(void* pClassObj, char* pBuffer){};

		const char* GetName(){return m_name.c_str();}
		void SetName(const char* name){m_name = name;}

		const char* GetDes(){return m_des.c_str();}
		void SetDes(const char* des){m_des = des;}
		virtual const char* GetTypeName()const{return NULL;}
	protected:
//		void* m_pPtr;
		int32 m_size;
//		int32 m_offset;
		uint32 m_flag;
		std::string m_name;
		std::string m_des;
		TypeTag m_typeifo;
	};


	template<typename T>
	class TAnyType:public TTypeBase
	{
	public:
		TAnyType():m_typeifo(TYPE_STRUCT),m_size(sizeof(T)){} //下边没定义的一律按照结构体算。
		~TAnyType(){}
		bool CheckType(const TypeTag& type)
		{
			return m_typeinfo == type;
		}
		virtual TypeTag GetTypeName()const{return m_typeinfo}
		virtual const T& GetVal()const {return m_val;}
		virtual void SetVal(const T& val){m_val = val;}

	protected:
		T m_val;
		
	};

	template<>
	inline TAnyType<char>::TAnyType():m_typeifo(TYPE_CHAR),m_size(sizeof(char))
	{
	}


	template<>
	inline TAnyType<uint8>::TAnyType():m_typeifo(TYPE_UINT8),m_size(sizeof(uint8))
	{
	}

	template<>
	inline TAnyType<int8>::TAnyType():m_typeifo(TYPE_INT8),m_size(sizeof(int8))
	{
	}

	template<>
	inline TAnyType<int16>::TAnyType():m_typeifo(TYPE_INT16),m_size(sizeof(int16))
	{
	}

	template<>
	inline TAnyType<uint16>::TAnyType():m_typeifo(TYPE_UINT16),m_size(sizeof(uint16))
	{
	}

	template<>
	inline TAnyType<int32>::TAnyType(): m_typeifo(TYPE_INT32),m_size(sizeof(int32))
	{
	}
		
	template<>
	inline TAnyType<uint32>::TAnyType(): m_typeifo(TYPE_UINT32),m_size(sizeof(uint32))
	{
	}
		
	template<>
	inline TAnyType<int64>::TAnyType(): m_typeifo(TYPE_INT64),m_size(sizeof(int64))
	{
	}
			
	template<>
	inline TAnyType<uint64>::TAnyType(): m_typeifo(TYPE_UINT64),m_size(sizeof(uint64))
	{
	}
				
	template<>
	inline TAnyType<f32>::TAnyType(): m_typeifo(TYPE_F32),m_size(sizeof(f32))
	{
	}
		
	template<>
	inline TAnyType<f64>::TAnyType(): m_typeifo(TYPE_F64),m_size(sizeof(f64))
	{
		
	template<>
	inline TAnyType<bool>::TAnyType():m_typeifo(TYPE_BOOL),m_size(sizeof(bool))
	{
	}


// 	template<>
// 	inline TAnyType<std::string>::TAnyType
// 	{
// 		assert(false);
// 	}

	template<typename T>
	class TAnyTypePtr: public TTypeBase
	{
	public:
		TAnyTypePtr():m_typeifo(TYPE_PTR),m_size(sizeof(T*))}{}
		~TAnyTypePtr(){}
		inline void SetPtr(T* ptr){m_ptr = ptr;}
		inline T* GetPtr()const{return m_ptr;}
		void* operator->(){return m_ptr;}
	protected:
		T* m_ptr;
	};

	class TAnyTypeArray: public TTypeBase
	{
	public:
		TAnyTypeArray(TTypeBase* pArray, int32 count)
		{
			m_typeifo = TYPE_ARRAY;
			m_pArray = pArray;
			nElem = count;
			m_size = pArray->GetSize()* count;
		}
		~TAnyTypeArray()
		{

		}

		inline int  GetArraySize() const{return nElem;}

		inline TTypeBase* GetElementType() const{return m_pArray;}
	protected:
		TTypeBase* m_pArray;
		int32 nElem;
	};

}




#endif