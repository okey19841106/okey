/********************************************************************
	created:	2015/01/18
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __THREAD_RUNNABLE_H__
#define __THREAD_RUNNABLE_H__

namespace okey
{
	class Runnable
	{
		public:	
			Runnable(){}
			virtual ~Runnable(){}
			virtual void Run() = 0;
			
	};

	template<typename C>
	class RunnableAdapter : public Runnable
	{
		typedef void (C::*_f)();
	public:
		RunnableAdapter(C& object, _f method):_c(&object),f(method)
		{

		}
		RunnableAdapter(C* object, _f method):_c(object),f(method)
		{

		}
		RunnableAdapter(const RunnableAdapter& r):_c(r._c), f(r.f)
		{

		}
		RunnableAdapter& operator = (const RunnableAdapter& r)
		{
			_c = r._c;
			f  = r.f;
			return *this;
		}
		~RunnableAdapter()
		{

		}
		void Run()
		{
			(_c->*f)();
		}
	private:
		RunnableAdapter();
		C* _c;
		_f f;
	};
}

#endif