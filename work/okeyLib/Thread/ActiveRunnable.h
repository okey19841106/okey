/********************************************************************
	created:	2015/01/20
	created:	15:32
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __THREAD_ACTIVE_RUNNABLE_H__
#define __THREAD_ACTIVE_RUNNABLE_H__

#include "Runnable.h"
#include "CRefcounter.h"
#include "AutoPtr.h"
#include "ActiveResult.h"

namespace okey
{
	class ActiveRunnableBase: public Runnable , public CRefCounter
	{
	public:
		typedef AutoPtr<ActiveRunnableBase> Ptr;
	};

	template <class ResultType, class ArgType, class OwnerType>
	class ActiveRunnable : public ActiveRunnableBase
	{
	public:
		typedef ResultType (OwnerType::*Callback)(const ArgType&);
		typedef ActiveResult<ResultType> ActiveResultType;
	public:
		ActiveRunnable(OwnerType* pOwner, Callback method, const ArgType& arg, const ActiveResultType& result):
		  _pOwner(pOwner),_method(method),_arg(arg),_result(result)
		{

		}

		void Run()
		{
			ActiveRunnableBase::Ptr guard(this, false); // ensure automatic release when done
			try
			{
				_result.SetData(new ResultType((_pOwner->*_method)(_arg)));
			}
			catch (Exception& e)
			{
				_result.error(e);
			}
			catch (std::exception& e)
			{
				_result.error(e.what());
			}
			catch (...)
			{
				_result.error("unknown exception");
			}
			_result.Notify();
		}

	private:
		OwnerType* _pOwner;
		Callback   _method;
		ArgType    _arg;
		ActiveResultType _result;
	};

	template <class ResultType, class OwnerType>
	class ActiveRunnable<ResultType,void,OwnerType> : public ActiveRunnableBase
	{
	public:
		typedef ResultType (OwnerType::*Callback)();
		typedef ActiveResult<ResultType> ActiveResultType;
	public:
		ActiveRunnable(OwnerType* pOwner, Callback method, const ActiveResultType& result):
		  _pOwner(pOwner),_method(method),_result(result)
		  {

		  }

		  void Run()
		  {
			  ActiveRunnableBase::Ptr guard(this, false); // ensure automatic release when done
			  try
			  {
				  _result.SetData(new ResultType((_pOwner->*_method)()));
			  }
			  catch (Exception& e)
			  {
				  _result.error(e);
			  }
			  catch (std::exception& e)
			  {
				  _result.error(e.what());
			  }
			  catch (...)
			  {
				  _result.error("unknown exception");
			  }
			  _result.Notify();
		  }

	private:
		OwnerType* _pOwner;
		Callback   _method;
		ActiveResultType _result;
	};

	template<class ArgType, class OwnerType>
	class ActiveRunnable<void,ArgType,OwnerType> : public ActiveRunnableBase
	{
	public:
		typedef void (OwnerType::*Callback)(const ArgType&);
		typedef ActiveResult<void> ActiveResultType;
	public:
		ActiveRunnable(OwnerType* pOwner, Callback method, const ArgType& arg, const ActiveResultType& result):
		  _pOwner(pOwner),_method(method),_arg(arg),_result(result)
		  {

		  }

		  void Run()
		  {
			  ActiveRunnableBase::Ptr guard(this, false); // ensure automatic release when done
			  try
			  {
				  (_pOwner->*_method)(_arg);
			  }
			  catch (Exception& e)
			  {
				  _result.error(e);
			  }
			  catch (std::exception& e)
			  {
				  _result.error(e.what());
			  }
			  catch (...)
			  {
				  _result.error("unknown exception");
			  }
			  _result.Notify();
		  }

	private:
		OwnerType* _pOwner;
		Callback   _method;
		ArgType    _arg;
		ActiveResultType _result;
	};

	template<class OwnerType>
	class ActiveRunnable<void,void,OwnerType> : public ActiveRunnableBase
	{
	public:
		typedef void (OwnerType::*Callback)();
		typedef ActiveResult<void> ActiveResultType;
	public:
		ActiveRunnable(OwnerType* pOwner, Callback method, const ActiveResultType& result):
		  _pOwner(pOwner),_method(method),_result(result)
		  {

		  }

		  void Run()
		  {
			  ActiveRunnableBase::Ptr guard(this, false); // ensure automatic release when done
			  try
			  {
				(_pOwner->*_method)();
			  }
			  catch (Exception& e)
			  {
				  _result.error(e);
			  }
			  catch (std::exception& e)
			  {
				  _result.error(e.what());
			  }
			  catch (...)
			  {
				  _result.error("unknown exception");
			  }
			  _result.Notify();
		  }

	private:
		OwnerType* _pOwner;
		Callback   _method;
		ActiveResultType _result;
	};
}

#endif