/********************************************************************
	created:	2014/08/22
	created:	16:37
	author:		
	
	purpose:	
*********************************************************************/


#ifndef OKEY_BASE_FUCTION_H
#define OKEY_BASE_FUCTION_H

namespace okey
{
	class CFunctionArg0Base
	{
	public:
		CFunctionArg0Base(){}
		~CFunctionArg0Base(){}
		virtual void operator()() = 0;
	};

	


	template<class T>
	class CFunctionArg0: public CFunctionArg0Base
	{
	public:
		CFunctionArg0(T* pclass, void (T::*pf)()):FunClass(pclass),f_(pf){}
		~CFunctionArg0(){}
		void operator()(){
			(FunClass->*f_)();
		}
	private:
		T* FunClass;
		void (T::*f_)();

	};
	
	template<typename Arg>
	class CFunctionArg1Base
	{
	public:
		CFunctionArg1Base(){}
		~CFunctionArg1Base(){}
		virtual void operator()(Arg) = 0;
	};

	



	template<class T, typename Arg>
	class CFunctionArg1: public CFunctionArg1Base<Arg>
	{
	public:
		CFunctionArg1(T*pclass, void(T::*pf)(Arg)):FunClass(pclass),f_(pf){}
		~CFunctionArg1(){}
		virtual void operator()(Arg ar)
		{
			(FunClass->*f_)(ar);
		}
	protected:
	private:
		T* FunClass;
		void (T::*f_)(Arg);
	};
  

	template<typename Arg1, typename Arg2>
	class CFunctionArg2Base
	{
	public:
		CFunctionArg2Base(){}
		~CFunctionArg2Base(){}
		virtual void operator()(Arg1, Arg2) = 0;
	};

	template<class T, typename Arg1, typename Arg2>
	class CFunctionArg2: public CFunctionArg2Base<Arg1, Arg2>
	{
	public:
		CFunctionArg2(T*pclass, void(T::*pf)(Arg1, Arg2)):FunClass(pclass),f_(pf){}
		~CFunctionArg2(){}
		virtual void operator()(Arg1 ar1, Arg2 ar2)
		{
			(FunClass->*f_)(ar1, ar2);
		}
	protected:
	private:
		T* FunClass;
		void (T::*f_)(Arg1,Arg2);
	};

	template<typename Arg1, typename Arg2, typename Arg3>
	class CFunctionArg3Base
	{
	public:
		CFunctionArg3Base(){}
		~CFunctionArg3Base(){}
		virtual void operator()(Arg1, Arg2,Arg3) = 0;
	};

	

	template<class T, typename Arg1, typename Arg2, typename Arg3>
	class CFunctionArg3: public CFunctionArg3Base<Arg1, Arg2, Arg3>
	{
	public:
		CFunctionArg3(T*pclass, void(T::*pf)(Arg1,Arg2, Arg3)):FunClass(pclass),f_(pf){}
		~CFunctionArg3(){}
		virtual void operator()(Arg1 ar1, Arg2 ar2, Arg3 ar3)
		{
			(FunClass->*f_)(ar1, ar2, ar3);
		}
	protected:
	private:
		T* FunClass;
		void (T::*f_)(Arg1,Arg2,Arg3);
	};

	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4>
	class CFunctionArg4Base
	{
	public:
		CFunctionArg4Base(){}
		~CFunctionArg4Base(){}
		virtual void operator()(Arg1, Arg2,Arg3,Arg4) = 0;
	};



	template<class T, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
	class CFunctionArg4: public CFunctionArg4Base<Arg1, Arg2, Arg3, Arg4>
	{
	public:
		CFunctionArg4(T*pclass, void(T::*pf)(Arg1,Arg2, Arg3, Arg4)):FunClass(pclass),f_(pf){}
		~CFunctionArg4(){}
		virtual void operator()(Arg1 ar1, Arg2 ar2, Arg3 ar3, Arg4 ar4)
		{
			(FunClass->*f_)(ar1, ar2, ar3, ar4);
		}
	protected:
	private:
		T* FunClass;
		void (T::*f_)(Arg1,Arg2,Arg3,Arg4);
	};


}
#endif