/********************************************************************
	created:	2013/06/12
	created:	12-6-2013   20:35
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "Types.h"
#include <string>
#include "UtilID.h"
#include "Allocator.h"

namespace okey
{

	class CFactoryArg0_Base
	{
	public:
		CFactoryArg0_Base(){}
		virtual ~CFactoryArg0_Base(){}
		virtual void* CreateObject() {return NULL;}
		virtual void SetObjName(const std::string name)
		{
			objname = name;
		}
		const char* GetObjName(){return objname.c_str();}
		uint32 GetID(){return objid;}
		void SetID(uint32 pid){objid = pid;}
		virtual void CollectMemory() = 0;
		virtual int64 GetUsageMemory() = 0;
		virtual int32 ClassSize() = 0;
		virtual Allocator* GetAllocator(){return NULL;}
		virtual void FreeObject(void *ptr)=0;
		//virtual void Init() = 0;
		//virtual void SetAllocator(Allocator* alloc)=0;
	protected:
		std::string objname;
		uint32	objid;
	private:
	};

	template<typename T>
	class CFactoryArg0 : public CFactoryArg0_Base
	{
	public:
		CFactoryArg0(Allocator* alloc)
		{
			m_Alloc = alloc;
			m_Alloc->Init(sizeof(T));
		}
		virtual void SetObjName(const std::string name)
		{
			CFactoryArg0_Base::SetObjName(name);
			MemoryHead mh;
			mh.AllocInfo = UtilID::StringToUtilID(name.c_str(),(uint32)name.length());
			m_Alloc->SetMemoryInfo(mh);
		}
		virtual ~CFactoryArg0()
		{
			if(m_Alloc)
				delete m_Alloc; //还没有想好在哪里析构。
		}
		virtual void* CreateObject()
		{
			T* p = (T*)m_Alloc->Malloc(sizeof(T));
			if(p)
			{
				::new(p)T();
				return (void*)p;
			}
			return NULL;
		}
		virtual void CollectMemory()
		{
			m_Alloc->CollectMemory();
		}
		virtual int32 ClassSize()
		{
			return m_Alloc->GetMemoryHead().MemInfo;
		}
		virtual int64 GetUsageMemory()
		{
			return m_Alloc->GetMemroyUsage();
		}
		virtual Allocator* GetAllocator()
		{
			return m_Alloc;
		}
		virtual void FreeObject(void *ptr)
		{
			if(ptr && m_Alloc /*&& 另一个检查的东西*/)
			{
				((T*)ptr)->~T();
				m_Alloc->Free(ptr);
			}
		}
	protected:
		Allocator *m_Alloc;
	};
	
	template<typename Type>
	class CFactoryArg1_Base
	{
	public:
		CFactoryArg1_Base(){}
		virtual ~CFactoryArg1_Base(){}
		virtual void* CreateObject(Type) {return NULL;}
		virtual void SetObjName(const std::string name)
		{
			objname = name;
		}
		const char* GetObjName(){return objname.c_str();}
		uint32 GetID(){return objid;}
		void SetID(uint32 pid){objid = pid;}
		virtual void CollectMemory() = 0;
		virtual int64 GetUsageMemory() = 0;
		virtual int32 ClassSize() = 0;
		virtual Allocator* GetAllocator(){return NULL;}
		virtual void FreeObject(void *ptr)=0;
		virtual void Init() = 0;
		//virtual void SetAllocator(Allocator* alloc)=0;
	protected:
		std::string objname;
		uint32	objid;
	private:
	};

	template<typename T, typename Type>
	class CFactoryArg1 : public CFactoryArg1_Base<Type>
	{
	public:
		CFactoryArg1(Allocator* alloc)
		{
			m_Alloc = alloc;
			m_Alloc->Init(sizeof(T));
		}
		virtual void SetObjName(const std::string name)
		{
			CFactoryArg0_Base::SetObjName(name);
			MemoryHead mh;
			mh.AllocInfo = UtilID::StringToUtilID(name.c_str(),name.length());
			m_Alloc->SetMemoryInfo(mh);
		}
		virtual ~CFactoryArg1()
		{
			/*if(m_Alloc)
			delete m_Alloc;*/ //还没有想好在哪里析构。
		}
		virtual void* CreateObject(Type ty)
		{
			T* p = (T*)m_Alloc->Malloc(sizeof(T));
			if(p)
			{
				::new(p)T(ty);
				return (void*)p;
			}
			return NULL;
		}
		virtual void CollectMemory()
		{
			m_Alloc->CollectMemory();
		}
		virtual int32 ClassSize()
		{
			return m_Alloc->GetMemoryHead().MemInfo;
		}
		virtual int64 GetUsageMemory()
		{
			return m_Alloc->GetMemroyUsage();
		}
		virtual Allocator* GetAllocator()
		{
			return m_Alloc;
		}
		virtual void FreeObject(void *ptr)
		{
			if(ptr && m_Alloc /*&& 另一个检查的东西*/)
			{
				((T*)ptr)->~T();
				m_Alloc->Free(ptr);
			}
		}
	protected:
		Allocator *m_Alloc;
	};

}

#endif
