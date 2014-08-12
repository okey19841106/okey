/********************************************************************
	created:	2014/08/12
	created:	16:47
	filename: 	
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_TCLASS_H__
#define __OKEY_TCLASS_H__


namespace okey
{
	class TClass :public TTypeBase //类也是一个种类型。
	{
	public:
		TClass():m_typeinfo(TYPE_STRUCT){}
		~TClass();

		virtual char* Read(void* pClassObj,char* pBuffer);
		virtual char* Write(void* pClassObj, char* pBuffer);



	};
}
#endif