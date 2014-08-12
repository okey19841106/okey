/********************************************************************
	created:	2014/08/10
	author:		okey
	
	purpose:	
*********************************************************************/


#ifndef __OKEY_CLASS_MEMBER_H__
#define __OKEY_CLASS_MEMBER_H__

#include "AnyTypeBase.h"

namespace okey
{
	class TClassMember
	{
	public:
		TClassMember();
		~TClassMember();
		inline uint32 GetOffset() const {return m_offset;}
		inline void SetOffset(const uint32& n){m_offset = n;}
		template<typename T>
		void SetValue(void* pClassObj, const T& val)
		{
			*((T*)(((char*)pClassObj)+m_offset)) = val;
		}
		template<typename T>
		const T& GetValue(void* pClassObj)
		{
			return (*((T*)(((char*)pClassObj) + m_offset)));
		}

		char* Read(void* pClassObj, char* pBuff)
		{
			return m_pType->Read(((char*)pClassObj) + m_offset,pBuff);
		}

		char* Write(void* pClassObj, char* pBuff)
		{
			return m_pType->Write(((char*)pClassObj) + m_offset,pBuff);
		}
	protected:
		TTypeBase* m_pType;
		uint32 m_offset;
	};

// 	template<class T>
// 	class TClassMember: public TAnyType<T>
// 	{
// 	public:
// 		TClassMember(){}
// 		~TClassMember(){}
// 
// 		inline int32 GetOffset()const{return m_offset;}
// 		inline void SetOffset(const uint32& n){m_offset = n;}
// 
// 		virtual void SetValue(void* pClassObj,const T& val)
// 		{
// 			*((T*)(((char*)pClassObj)+m_offset)) = val;
// 		}
// 
// 		virtual const T& GetValue(void* pClassObj)
// 		{
// 			return (*((T*)(((char*)pClassObj) + m_offset)));
// 		}
// 
// 		char* Read(void* pClassObj, char* pBuffer)
// 		{
// 			if (!pClassObj || !pBuffer)
// 			{
// 				return NULL;
// 			}
// 			TClass *pClass = T::GetStaticClass();
// 			if (!pClass)
// 			{
// 				//assert()
// 				return NULL;
// 			}
// 			return pClass->Read(((char*)pClassObj) + m_offset ,pBuffer);
// 		}
// 		char* Write(void* pClassObj, char* pBuffer)
// 		{
// 			if (!pClassObj || !pBuffer)
// 			{
// 				return NULL;
// 			}
// 			TClass* pClass = T::GetStaticClass();
// 			if (!pClass)
// 			{
// 				//assert()
// 				return NULL;
// 			}
// 			return pClass->Write(((char*)pClassObj) + m_offset,pBuffer);
// 		}
// 
// 	protected:
// 	
// 		uint32 m_offset;
// 	};
// 
// 
// 	template<>
// 	inline char* TClassMember<char>::Read(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(((char*)pClassObj) + m_offset , pBuffer, m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<char>::Write(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(pBuffer, ((char*)pClassObj) + m_offset , m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<uint8>::Read(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(((char*)pClassObj) + m_offset , pBuffer, m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<uint8>::Write(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(pBuffer, ((char*)pClassObj) + m_offset , m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<int8>::Read(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(((char*)pClassObj) + m_offset , pBuffer, m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<int8>::Write(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(pBuffer, ((char*)pClassObj) + m_offset , m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<uint16>::Read(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(((char*)pClassObj) + m_offset , pBuffer, m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<int16>::Write(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(pBuffer, ((char*)pClassObj) + m_offset , m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<uint32>::Read(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(((char*)pClassObj) + m_offset , pBuffer, m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<int32>::Write(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(pBuffer, ((char*)pClassObj) + m_offset , m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<uint64>::Read(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(((char*)pClassObj) + m_offset , pBuffer, m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<int64>::Write(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(pBuffer, ((char*)pClassObj) + m_offset , m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<f32>::Read(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(((char*)pClassObj) + m_offset , pBuffer, m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<f32>::Write(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(pBuffer, ((char*)pClassObj) + m_offset , m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<f64>::Read(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(((char*)pClassObj) + m_offset , pBuffer, m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<f64>::Write(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(pBuffer, ((char*)pClassObj) + m_offset , m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<bool>::Read(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(((char*)pClassObj) + m_offset , pBuffer, m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<>
// 	inline char* TClassMember<bool>::Write(void* pClassObj, char* pBuffer)
// 	{
// 		if (!pClassObj || !pBuffer)
// 		{
// 			return NULL;
// 		}
// 		memcpy(pBuffer, ((char*)pClassObj) + m_offset , m_size);
// 		return pBuffer + m_size;
// 	}
// 
// 	template<class T>
// 	class TClassMemberPtr:public TAnyTypePtr<T>
// 	{
// 	public:
// 		TClassMemberPtr(){}
// 		~TClassMemberPtr(){}
// 	};
	//template<typename Ret>
// 	class CMethodBase
// 	{
// 	public:
// 		const char* GetName(){return m_name.c_str();}
// 		void SetName(const char* name){m_name = name;}
// 
// 		const char* GetDes(){return m_des.c_str();}
// 		void SetDes(const char* des){m_des = des;}
// 		//void* GetMethodPtr(){return NULL;}
// 		//void SetMethodPtr(){}
// 	protected:
// 		//CallbackClassBase<Ret> *m_pfn;
// 		std::string m_name;
// 		std::string m_des;
// 	};

// 	class CAnyMethod: public CMethodBase
// 	{
// 	public:
// 		CallbackBase* GetMethod()const {return m_pfn;}
// 		void SetMethod(CallbackBase*pfn){m_pfn = pfn;}
// 	protected:
// 	private:
// 		CallbackBase* m_pfn;
// 	};
// 
// 	template<typename Ret>
// 	class CClassMethod: public CMethodBase
// 	{
// 	public:
// 		CallbackClassBase<Ret>* GetMethod()const {return m_pfn;}
// 		void SetMethod(CallbackClassBase<Ret>*pfn){m_pfn = pfn;}
// 	protected:
// 		CallbackClassBase<Ret>* m_pfn;
// 	private:
// 	};
// 
// 	class CClass
// 	{
// 		typedef std::map<UtilID, CTypeBase*> MemberMap;
// 		//typedef std::map<UtilID, CMethodBase*> MethodMap;
// 	public:
// 		CClass();
// 		~CClass();
// 		int32 GetMemberCount()const {return (int32)m_members.size();}
// 		//		int32 GetMethodCount()const {return m_methods.size();}
// 		const char* GetClassName()const {return m_classname.c_str();}
// 		void SetClassName(const char* name)
// 		{
// 			m_classname = name;
// 			uint32 cid = UtilID::StringToUtilID(m_classname.c_str(),(int32)m_classname.length());
// 			SetClassID(cid);
// 		}
// 		int32 GetClassID()const{return m_classID;}
// 		CClass* GetParent() const {return m_parent;}
// 		void SetParent(CClass* parent){m_parent = parent;}
// 		int32 GetClassSize()const {return m_classSize;}
// 		int32 GetClassSerSize()const {return m_classSerSize;}
// 		void AddMember(CTypeBase* member);
// 		//void AddMethod(CMethodBase* method);
// 		CTypeBase* GetMember(int32 index);
// 		//CMethodBase* GetMethod(int index);
// 		CTypeBase* GetMember(const char* name);
// 		//CMethodBase* GetMethod(const char* name);
// 		virtual char* Read(void* pClassObj,char* pBuffer,int32 flag);
// 		virtual char* Write(void* pClassObj,char* pBuffer,int32 flag);
// 		bool IsChild(uint32 classID);
// 		bool IsChild(const char* name);
// 		bool IsChild(CClass* pClass);
// 		uint32 GetID(){return m_classID;}
// 	protected:
// 		void SetClassID(const uint32& classid){m_classID = classid;}
// 		uint32 m_classID;
// 		int32 m_classSize;
// 		int32 m_classSerSize;
// 		CClass* m_parent;
// 		MemberMap m_members;
// 		//MethodMap m_methods;
// 		std::string m_classname;
// 
// 	};

	template<typename T>
	class CClassMember_Class:public TAnyType<T>
	{
	public:
		CClassMember_Class(){}
		~CClassMember_Class(){}

		virtual void SetValue(void* pClassObj,const T& val)
		{
			*((T*)(((char*)pClassObj)+m_offset)) = val;
		}

		virtual const T& GetValue(void* pClassObj)
		{
			return (*((T*)(((char*)pClassObj) + m_offset)));
		}

		char* Read(void* pClassObj, char* pBuffer)
		{
			if (!pClassObj || !pBuffer)
			{
				return NULL;
			}
			CClass* pClass = T::GetClassStatic();
			if (pClass)
			{
				return pClass->Read(((char*)pClassObj) + m_offset ,pBuffer);
			}
			memcpy(((char*)pClassObj) + m_offset , pBuffer, m_size);
			return pBuffer + m_size;
		}
		char* Write(void* pClassObj, char* pBuffer)
		{
			if (!pClassObj || !pBuffer)
			{
				return NULL;
			}
			CClass* pClass = T::GetClassStatic(pBuffer, );
			if (pClass)
			{
				return pClass->Write(pBuffer, ((char*)pClassObj) + m_offset);
			}
			memcpy(pBuffer, ((char*)pClassObj) + m_offset , m_size);
			return pBuffer + m_size;
		}
	protected:
	private:

	};
	class CClassMember_String:public CTypeBase
	{
	public:
		CClassMember_String()
		{
			m_stringsize = 0;
			m_size = sizeof(m_stringsize);

		}
		CClassMember_String(uint8 size)
		{
			m_stringsize = size;
			m_size = m_stringsize + sizeof(m_stringsize);
		}
		~CClassMember_String()
		{

		}
		virtual const char* GetTypeName()const
		{
			return "String";
		}

		bool CheckType(const std::type_info& type)
		{
			return typeid(char*) == type;
		}

		virtual void SetValue(void* pClassObj,const char* val)
		{
			int32 slen = (int32)strlen(val);
			slen = (slen>(m_stringsize-1))?(m_stringsize-1):slen;
			memset(((char*)pClassObj)+m_offset,0,m_stringsize);
			memcpy(((char*)pClassObj)+m_offset,val,slen);
		}

		virtual const char* GetValue(void* pClassObj)
		{
			return (((char*)pClassObj) + m_offset);
		}

		char* Write(void* pClassObj, char* pBuffer)
		{
			if (!pClassObj || !pBuffer)
			{
				return NULL;
			}
			*((uint8*)pBuffer) = m_stringsize - 1;
			char* tmpBuffer = pBuffer + sizeof(uint8);
			memset(tmpBuffer,0,m_stringsize);
			memcpy(tmpBuffer,((char*)pClassObj)+m_offset,m_stringsize);
			return tmpBuffer + m_stringsize;
		}
		char* Read(void* pClassObj, char* pBuffer)
		{
			if (!pClassObj || !pBuffer)
			{
				return NULL;
			}
			int32 rlen = *((uint8*)pBuffer);
			char* tmpBuffer = pBuffer + sizeof(uint8);
			int32 tlen = (rlen>(m_stringsize-1))?(m_stringsize - 1):rlen;
			memset(((char*)pClassObj)+m_offset,0,m_stringsize);
			memcpy(((char*)pClassObj)+m_offset,tmpBuffer,tlen);
			return tmpBuffer + m_stringsize;
		}
	protected:
		uint8 m_stringsize;
	private:

	};
}

#endif