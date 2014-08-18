#ifndef __MY_TEST_H__7866_
#define __MY_TEST_H__7866_


#include "TClass.h"
#include "ClassMember.h"
#include "ClassFunctor.h"

using namespace okey;

class test
{
public:
	/*int64 b;*/
	int32 a;
	void fun_1(int32 a)
	{
		printf("%d\n",a);
	}
	
	class mytest : public TClass
	{
	public:
		~mytest(){}
		mytest()
		{
			SetName("test");
			//AddBaseClass();
			//add register
			TAnyType<int32>* pMem_a = new TAnyType<int32>();
			pMem_a->SetName("a");
			//pMem_a->SetFlag();
			//pMem_a->SetDes("");
			TClassMember* pClassMember_a = new TClassMember(this,pMem_a);
			pClassMember_a->SetOffset(uint32(&((test*)0)->a));
			AddMember(pClassMember_a);

			TClassMethod1<void, test,int32>* m_fuctor1_fun1 = new TClassMethod1<void, test,int32>(&test::fun_1);
			TClassMethod* pClass_Mem_funtor_fun1 = new TClassMethod(this,m_fuctor1_fun1);
			AddMethod(pClass_Mem_funtor_fun1);
		}
	};
	static mytest _mytest;
	static TClass* GetClassStatic(){return (TClass*)&_mytest;}
	virtual char* Read(char* pBuffer){return _mytest.Read(this,pBuffer);}
	virtual char* Write(char* pBuffer){return _mytest.Write(this,pBuffer);}
	
};

test::mytest test::_mytest;

#endif