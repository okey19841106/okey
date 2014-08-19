#ifndef __MY_TEST_H__7866_
#define __MY_TEST_H__7866_


#include "TClassDefine.h"

using namespace okey;

class test
{
public:
	/*int64 b;*/
	int32 a;
	char str[10];
	f32* fptr;
	uint16 arr[15];
	void fun_1(int32 a)
	{
		printf("%d\n",a);
	}
	
	int32 fun_2(int32 a)
	{
		return a;
	}
	REG_CLASS_BEGIN_BASE(test);
	REG_CLASS_MEMBER(a,int32,0);
	REG_CLASS_MEMBER_STR(str,10,0);
	REG_CLASS_MEMBER_PTR(fptr,f32,0);
	REG_CLASS_MEMBER_ARRAY(arr,uint16,15,0);
	REG_CLASS_END(test);
// 	class mytest : public TClass
// 	{
// 	public:
// 		~mytest(){}
// 		mytest()
// 		{
// 			SetName("test");
// 			//AddBaseClass();
// 			//add register
// 			TAnyType<int32>* pMem_a = new TAnyType<int32>();
// 			pMem_a->SetName("a");
// 			//pMem_a->SetFlag();
// 			//pMem_a->SetDes("");
// 			TClassMember* pClassMember_a = new TClassMember(this,pMem_a);
// 			pClassMember_a->SetOffset(uint32(&((test*)0)->a));
// 			AddMember(pClassMember_a);
// 
// 			TClassMethod1<void, test,int32>* m_fuctor1_fun1 = new TClassMethod1<void, test,int32>(&test::fun_1);
// 			m_fuctor1_fun1->SetName("fun_1");
// 			TClassMethod* pClass_Mem_funtor_fun1 = new TClassMethod(this,m_fuctor1_fun1);
// 			AddMethod(pClass_Mem_funtor_fun1);
// 
// 			TClassMethod1<int32, test,int32>* m_fuctor1_fun2 = new TClassMethod1<int32, test,int32>(&test::fun_2);
// 			m_fuctor1_fun2->SetName("fun_2");
// 			TClassMethod* pClass_Mem_funtor_fun2 = new TClassMethod(this,m_fuctor1_fun2);
// 			AddMethod(pClass_Mem_funtor_fun2);
// 		}
// 	};
// 	static mytest _mytest;
// 	static TClass* GetClassStatic(){return (TClass*)&_mytest;}
// 	virtual char* Read(char* pBuffer){return _mytest.Read(this,pBuffer);}
// 	virtual char* Write(char* pBuffer){return _mytest.Write(this,pBuffer);}
	
};

DECLARE_CLASS(test);

class test_b
{
public:
	test t;
	REG_CLASS_BEGIN_BASE(test_b);

};

#endif