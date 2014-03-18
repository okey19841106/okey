//////////////////////////////////////////////////////////////
//                      .----.
//                   _.'__    `.
//             .--(#)(##)---/#\
//           .' @            /###\
//           :         ,       #####
//            `-..__.-' _.-  \###/ 
//                   `;_:         `"'
//                 .'"""""`.
//                /,         ,\
//               //           \\
//               `-._______.-'
//                ___`. | .'___
//             (______|______)
//
//  created:	2011-9-3 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////


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
			return (FunClass->*f_)();
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
			return (FunClass->*f_)(ar);
		}
	protected:
	private:
		T* FunClass;
		void (T::*f_)(Arg);
	};
    template<class T, typename Arg>
	class CFunctionArg0With1Arg:public CFunctionArg0Base
	{
	public:
		CFunctionArg0With1Arg(CFunctionArg1Base<Arg>* pf1, Arg ta):m_pf1(pf1),m_ta(m_ta){}
		~CFunctionArg0With1Arg(){}
		virtual void operator()()
		{
			return (*m_pf1)(m_ta);
		}
	protected:
	private:
		CFunctionArg1Base<Arg>* m_pf1;
		Arg m_ta;
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
			return (FunClass->*f_)(ar1, ar2);
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
			return (FunClass->*f_)(ar1, ar2, ar3);
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
			return (FunClass->*f_)(ar1, ar2, ar3, ar4);
		}
	protected:
	private:
		T* FunClass;
		void (T::*f_)(Arg1,Arg2,Arg3,Arg4);
	};

	class CallbackBase
	{
	public:
		virtual void execute() = 0;
		virtual void operator()(){};
		virtual ~CallbackBase() {};
	};

	class CallBackFunctionP0 : public CallbackBase
	{
		typedef void(*cbfunction)();
		cbfunction cb;
	public:
		CallBackFunctionP0(cbfunction fn) : cb(fn) {}
		void operator()() { return (cb)(); }
		void execute() { return operator()(); }
	};

	template<typename P1>
	class CallBackFunctionP1 : public CallbackBase
	{
		typedef void(*cbfunction)(P1);
		cbfunction cb;
		P1 _p1;
	public:
		CallBackFunctionP1(cbfunction fn, P1 p1)
		{
			cb = fn;
			_p1 = p1;
		}
		void operator()() { return (cb)(_p1); }
		void execute() { return operator()(); }
	};

	template<typename P1, typename P2>
	class CallBackFunctionP2 : public CallbackBase
	{
		typedef void(*cbfunction)(P1, P2);
		cbfunction cb;
		P1 _p1;
		P2 _p2;
	public:
		CallBackFunctionP2(cbfunction fn, P1 p1, P2 p2) : cb(fn), _p1(p1), _p2(p2) {}
		void operator()() { return (cb)(_p1, _p2); }
		void execute() { return operator()(); }
	};
	template<typename P1, typename P2, typename P3>
	class CallBackFunctionP3 : public CallbackBase
	{
		typedef void(*cbfunction)(P1, P2, P3);
		cbfunction cb;
		P1 _p1;
		P2 _p2;
		P3 _p3;
	public:
		CallBackFunctionP3(cbfunction fn, P1 p1, P2 p2, P3 p3) : cb(fn), _p1(p1), _p2(p2), _p3(p3) {};
		void operator()() { return (cb)(_p1, _p2, _p3); }
		void execute() { return operator()(); }
	};
	template<typename P1, typename P2, typename P3, typename P4>
	class CallBackFunctionP4 : public CallbackBase
	{
		typedef void(*cbfunction)(P1, P2, P3, P4);
		cbfunction cb;
		P1 _p1;
		P2 _p2;
		P3 _p3;
		P4 _p4;
	public:
		CallBackFunctionP4(cbfunction fn, P1 p1, P2 p2, P3 p3, P4 p4) : cb(fn), _p1(p1), _p2(p2), _p3(p3), _p4(p4) {};
		void operator()() { return (cb)(_p1, _p2, _p3, _p4); }
		void execute() { return operator()(); }
	};

	template<typename Ret>
	class CallbackClassBase
	{
	public:
		virtual Ret execute() = 0;
		virtual Ret operator()(){};
		virtual ~CallbackClassBase(){};
	};
	
	template<class T,typename Ret>
	class CallBackClassFunctionP0 : public CallbackClassBase<Ret>
	{
		typedef Ret(T::*cbfunction)();
		cbfunction cb;
		T* m_pclass;
	public:
		CallBackClassFunctionP0(T* pclass, cbfunction fn):m_pclass(pclass),cb(fn){}
		~CallBackClassFunctionP0(){}
		 Ret operator()(){
			return (m_pclass->*cb)();
		}
		Ret execute() { return operator()(); }
	
		
	};

	template<class T,typename Ret, typename P1>
	class CallBackClassFunctionP1 : public CallbackClassBase<Ret>
	{
		typedef Ret(T::*cbfunction)(P1);
		cbfunction cb;
		P1 _p1;
		T* m_pclass;
	public:
		CallBackClassFunctionP1(T* pclass, cbfunction fn, P1 p1):m_pclass(pclass),cb(fn),_p1(p1)
		{
		}
		~CallBackClassFunctionP1(){}
		Ret operator()() { return (m_pclass->*cb)(_p1); }
		Ret execute() { return operator()(); }
	};

	template<class T,typename Ret, typename P1, typename P2>
	class CallBackClassFunctionP2 : public CallbackClassBase<Ret>
	{
		typedef Ret(T::*cbfunction)(P1, P2);
		cbfunction cb;
		P1 _p1;
		P2 _p2;
		T* m_pclass;
	public:
		CallBackClassFunctionP2(T* pclass, cbfunction fn, P1 p1, P2 p2) :m_pclass(pclass), cb(fn), _p1(p1), _p2(p2) {}
		Ret operator()() { return (m_pclass->*cb)(_p1, _p2); }
		Ret execute() { return operator()(); }
	};
	template<class T,typename Ret, typename P1, typename P2, typename P3>
	class CallBackClassFunctionP3 : public CallbackClassBase<Ret>
	{
		typedef Ret(T::*cbfunction)(P1, P2, P3);
		cbfunction cb;
		P1 _p1;
		P2 _p2;
		P3 _p3;
		T* m_pclass;
	public:
		CallBackClassFunctionP3(T* pclass, cbfunction fn, P1 p1, P2 p2, P3 p3) :m_pclass(pclass), cb(fn), _p1(p1), _p2(p2), _p3(p3) {};
		Ret operator()() { return (m_pclass->*cb)(_p1, _p2, _p3); }
		Ret execute() { return operator()(); }
	};
	template<class T,typename Ret, typename P1, typename P2, typename P3, typename P4>
	class CallBackClassFunctionP4 : public CallbackClassBase<Ret>
	{
		typedef Ret(T::*cbfunction)(P1, P2, P3, P4);
		cbfunction cb;
		P1 _p1;
		P2 _p2;
		P3 _p3;
		P4 _p4;
		T* m_pclass;
	public:
		CallBackClassFunctionP4(T* pclass, cbfunction fn, P1 p1, P2 p2, P3 p3, P4 p4) :m_pclass(pclass), cb(fn), _p1(p1), _p2(p2), _p3(p3), _p4(p4) {};
		Ret operator()() { return (m_pclass->*cb)(_p1, _p2, _p3, _p4); }
		Ret execute() { return operator()(); }
	};

}
#endif