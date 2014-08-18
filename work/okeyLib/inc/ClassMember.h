/********************************************************************
	created:	2014/08/10
	author:		okey
	
	purpose:	
*********************************************************************/


#ifndef __OKEY_CLASS_MEMBER_H__
#define __OKEY_CLASS_MEMBER_H__


namespace okey
{
	class TTypeBase;
	class TClass;

	class TClassMember
	{
	public:
		TClassMember(TClass* pClass, TTypeBase* pType);
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

		char* Read(void* pClassObj, char* pBuff);
// 		{
// 			return m_pType->Read(((char*)pClassObj) + m_offset,pBuff);
// 		}

		char* Write(void* pClassObj, char* pBuff);
// 		{
// 			return m_pType->Write(((char*)pClassObj) + m_offset,pBuff);
// 		}

		TClass* GetOwnerClass();
		std::string GetMemberName();
	protected:
		uint32 m_offset;
		TTypeBase* m_pType;
		TClass* m_OwnerClass;
	};

}

#endif