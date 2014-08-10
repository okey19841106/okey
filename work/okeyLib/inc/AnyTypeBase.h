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

	class CTypeBase
	{
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
	public:
		CTypeBase();
		~CTypeBase();
		
		inline void SetPtr(void* ptr){m_pPtr = ptr;}
		inline void* GetPtr()const{return m_pPtr;}

		void* operator->(){return m_pPtr;}

		inline int32 GetSize()const{return m_size;}
		inline void SetSize(const int32& n){m_size = n;}

// 		inline int32 GetOffset()const{return m_offset;}
// 		inline void SetOffset(const int32&n){m_offset = n;}

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
	protected:
		void* m_pPtr;
		int32 m_size;
//		int32 m_offset;
		uint32 m_flag;
		std::string m_name;
		std::string m_des;
	};






	template<typename T>
	class CAnyType:public CTypeBase
	{
	public:
		CAnyType():m_typeinfo(typeid(T))
		{
			SetSize(sizeof(T));
		}
		~CAnyType(){}
		bool CheckType(const std::type_info& type)
		{
			return m_typeinfo == type;
		}
		virtual const char* GetTypeName()const{return m_typeinfo.name();}
		virtual const T& GetVal()const {return m_val;}
		virtual void SetVal(const T& val){m_val = val;}


	protected:
		T m_val;
		const std::type_info& m_typeinfo;
	};

	class CAnyTypePtr: public CTypeBase
	{
	public:
		CAnyTypePtr()
	};


}




#endif