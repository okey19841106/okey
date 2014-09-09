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
		TYPE_STR,
		TYPE_STRING,
	};

	class TTypeBase
	{
	public:
		TTypeBase();
		~TTypeBase();
		
		inline uint32 GetSize()const{return m_size;}
		inline void SetSize(const uint32& n){m_size = n;}

		inline bool CheckFlag(const uint32& flag){return m_flag&flag;}
		inline void SetFlag(const uint32& flag){m_flag = flag;}
		inline uint32 GetFlag()const{return m_flag;}
		inline uint32 AddFlag(const uint32& flag){return m_flag|flag;}

		virtual char* Read(void* pClassObj,char* pBuffer);
		virtual char* Write(void* pClassObj, char* pBuffer);

		const char* GetName(){return m_name.c_str();}
		void SetName(const char* name){m_name = name;}

		const char* GetDes(){return m_des.c_str();}
		void SetDes(const char* des){m_des = des;}
		virtual const char* GetTypeName()const{return NULL;}
		TypeTag GetType()const {return m_typeinfo;}
	protected:
		uint32 m_size;
		uint32 m_flag;
		std::string m_name;
		std::string m_des;
		TypeTag m_typeinfo;
	};


	template<typename T>
	class TAnyType:public TTypeBase
	{
	public:
		TAnyType()
		{
			m_typeinfo = TYPE_STRUCT;
			m_size = sizeof(T);
		} 
		~TAnyType(){}
		bool CheckType(const TypeTag& type)
		{
			return m_typeinfo == type;
		}
		//virtual TypeTag GetType()const{return m_typeinfo}
		/*virtual */const T& GetVal()const {return m_val;}
		/*virtual */void SetVal(const T& val){m_val = val;}

	protected:
		T m_val;
	};

	template<>
	inline TAnyType<char>::TAnyType()
	{
		m_typeinfo = TYPE_CHAR;
		m_size = sizeof(char);
	}


	template<>
	inline TAnyType<uint8>::TAnyType()
	{
		m_typeinfo = TYPE_UINT8;
		m_size = sizeof(uint8);
	}

	template<>
	inline TAnyType<int8>::TAnyType()
	{
		m_typeinfo = TYPE_INT8;
		m_size = sizeof(int8);
	}

	template<>
	inline TAnyType<int16>::TAnyType()
	{
		m_typeinfo = TYPE_INT16;
		m_size = sizeof(int16);
	}

	template<>
	inline TAnyType<uint16>::TAnyType()
	{
		m_typeinfo = TYPE_UINT16;
		m_size = sizeof(uint16);
	}

	template<>
	inline TAnyType<int32>::TAnyType()
	{
		m_typeinfo = TYPE_INT32;
		m_size = sizeof(int32);
	}
		
	template<>
	inline TAnyType<uint32>::TAnyType()
	{
		m_typeinfo = TYPE_UINT32;
		m_size = sizeof(uint32);
	}
		
	template<>
	inline TAnyType<int64>::TAnyType()
	{
		m_typeinfo = TYPE_INT64;
		m_size = sizeof(int64);
	}
			
	template<>
	inline TAnyType<uint64>::TAnyType()
	{
		m_typeinfo = TYPE_UINT64;
		m_size = sizeof(uint64);
	}
				
	template<>
	inline TAnyType<f32>::TAnyType()
	{
		m_typeinfo = TYPE_F32;
		m_size = sizeof(f32);
	}
		
	template<>
	inline TAnyType<f64>::TAnyType()
	{
		m_typeinfo = TYPE_F64;
		m_size = sizeof(f64);
	}
		
	template<>
	inline TAnyType<bool>::TAnyType()
	{
		m_typeinfo = TYPE_BOOL;
		m_size = sizeof(bool);
	}

	template<>
	class TAnyType<std::string>:public TTypeBase
	{
	public:
		TAnyType()
		{
			m_typeinfo = TYPE_STRING;
			m_size = sizeof(std::string);
		} 
		~TAnyType(){}
		bool CheckType(const TypeTag& type)
		{
			return m_typeinfo == type;
		}
		
		const std::string& GetVal()const {return m_val;}
		void SetVal(const std::string& val)
		{
			//m_size = val.length();
			m_val = val;
		}
		virtual char* Read(void* pClassObj,char* pBuffer)
		{
			if (!pClassObj || !pBuffer)
			{
				return NULL;
			}
			uint32 len = *((uint16*)pBuffer);
			char* tmpBuf = pBuffer + sizeof(uint16);
			*((std::string*)pClassObj) = std::string(tmpBuf,0,len);
			return tmpBuf + len;
			
		}
		virtual char* Write(void* pClassObj, char* pBuffer)
		{
			if (!pClassObj || !pBuffer)
			{
				return NULL;
			}
			uint16 size =(uint16)(*(std::string*)pClassObj).length();
			*(uint16*)pBuffer = size;
			char* tmpBuf = pBuffer + sizeof(uint16);
			memcpy(tmpBuf, (*(std::string*)pClassObj).c_str(),size);
			return tmpBuf + size;
		}
	protected:
		std::string m_val;
	};

	template<typename T>
	class TAnyTypePtr: public TTypeBase
	{
	public:
		TAnyTypePtr()
		{
			m_typeinfo = TYPE_PTR;
			m_size = sizeof(T*);
		}
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
		TAnyTypeArray(TTypeBase* pArray, uint32 count)
		{
			m_typeinfo = TYPE_ARRAY;
			m_pArray = pArray;
			nElem = count;
			m_size = pArray->GetSize()* count;
		}
		~TAnyTypeArray()
		{

		}

		inline int  GetArraySize() const{return nElem;}

		inline TTypeBase* GetElementType() const{return m_pArray;}
		virtual char* Read(void* pClassObj,char* pBuffer);
		virtual char* Write(void* pClassObj, char* pBuffer);
	protected:
		TTypeBase* m_pArray;
		uint32 nElem;
	};

	class TAnyTypeMethod: public TTypeBase
	{
	public:
		TAnyTypeMethod()
		{
			m_typeinfo = TYPE_METHOD;
			m_size = 0;
		}
		~TAnyTypeMethod(){}
		virtual void invoke(void* result, void* obj, void* parameters[]) = 0;
		uint32 GetParamCount(){return m_paramCount;}

	protected:
		uint32 m_paramCount;
		TTypeBase* m_RetType;
		TTypeBase** m_parameters;

	};

	class TAnyTypeStr: public TTypeBase
	{
	public:
		TAnyTypeStr(uint32 nCount);
		~TAnyTypeStr(){}
// 		const char* GetValue();
// 		void SetValue(const char* str);
		virtual char* Read(void* pClassObj,char* pBuffer);
		virtual char* Write(void* pClassObj, char* pBuffer);
	protected:

		uint32 m_CharSize;
	};
}




#endif