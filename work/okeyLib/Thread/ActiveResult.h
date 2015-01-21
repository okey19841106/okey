/********************************************************************
	created:	2015/01/20
	created:	15:39
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __THREAD_ACTIVE_RESULT_H__
#define __THREAD_ACTIVE_RESULT_H__

#include "CRefcounter.h"
#include "Exception.h"
#include "Event.h"

namespace okey
{
	template <class ResultType>
	class ActiveResultHolder: public CRefCounter
	{
	public:
		ActiveResultHolder():_pData(NULL),_pExc(NULL),_event(false)
		{

		}
		ResultType& GetData(){return *_pData;}
		void SetData(ResultType* pData)
		{
			delete _pData;
			_pData = pData;
		}
		void Wait()
		{
			_event.Wait();
		}
		void Wait(uint32 milliseconds)
		{
			_event.Wait(milliseconds);
		}
		bool TryWait(uint32 milliseconds)
		{
			_event.TryWait(milliseconds);
		}
		void Notify()
		{
			_event.Set();
		}
		bool IsFailed() const{return _pExc != 0;}
		std::string GetError() const
		{
			if (_pExc)
				return _pExc->message();
			else
				return std::string();
		}
		Exception* GetException() const{return _pExc;}
		void SetError(const Exception& exc)
		{
			delete _pExc;
			_pExc = exc.clone();
		}
		void SetError(const std::string& msg)
		{
			delete _pExc;
			_pExc = new UnhandledException(msg);
		}
	protected:
		~ActiveResultHolder()
		{
			delete _pData;
			delete _pExc;
		}
	private:
		ResultType* _pData;
		Exception*  _pExc;
		Event       _event;
	};

	template<>
	class ActiveResultHolder<void>: public CRefCounter
	{
	public:
		ActiveResultHolder():_pExc(NULL),_event(false)
		{

		}
		void Wait()
		{
			_event.Wait();
		}
		void Wait(uint32 milliseconds)
		{
			_event.Wait(milliseconds);
		}
		bool TryWait(uint32 milliseconds)
		{
			_event.TryWait(milliseconds);
		}
		void Notify()
		{
			_event.Set();
		}
		bool IsFailed() const{return _pExc != 0;}
		std::string GetError() const
		{
			if (_pExc)
				return _pExc->message();
			else
				return std::string();
		}
		Exception* GetException() const{return _pExc;}
		void SetError(const Exception& exc)
		{
			delete _pExc;
			_pExc = exc.clone();
		}
		void SetError(const std::string& msg)
		{
			delete _pExc;
			_pExc = new UnhandledException(msg);
		}
	protected:
		~ActiveResultHolder() //在堆上创建对象。 不能delete。。
		{
			delete _pExc;
		}
	private:
		Exception*  _pExc;
		Event       _event;
	};

	template<typename ResultType>
	class ActiveResult
	{
	public:
		typedef ActiveResultHolder<ResultType> ActiveResultHolderType;
	public:
		ActiveResult(ActiveResultHolderType* pHolder):_pHolder(pHolder)
		{

		}
		ActiveResult(const ActiveResult& r)
		{
			_pHolder = r._pHolder;
			_pHolder->AddRef();
		}
		ActiveResult& operator=(const ActiveResult& r)
		{
			ActiveResult tmp(r);
			Swap(tmp);
			return *this;
		}

		~ActiveResult()
		{
			_pHolder->DecRef();
		}

		void Swap(ActiveResult& r)
		{
			std::swap(_pHolder, r._pHolder);
		}

		ResultType& GetData() const
		{
			return _pHolder->_pData;
		}

		ResultType& GetData()
		{
			return _pHolder->_pData;
		}
		void SetData(ResultType* pData)
		{
			_pHolder->SetData(pData);
		}
		void Wait()
		{
			_pHolder->Wait();
		}
		void Wait(uint32 milliseconds)
		{
			_pHolder->Wait(milliseconds);
		}
		bool TryWait(uint32 milliseconds)
		{
			_pHolder->TryWait(milliseconds);
		}
		void Notify()
		{
			_pHolder->Notify();
		}
		bool IsFailed() const
		{
			return _pHolder->IsFailed();
		}
		std::string GetError() const
		{
			return _pHolder->GetError();
		}
		Exception* GetException() const
		{
			return _pHolder->GetException();
		}
		void SetError(const Exception& exc)
		{
			_pHolder->SetError(exc);
		}
		void SetError(const std::string& msg)
		{
			_pHolder->SetError(msg);
		}
		bool Isvailable() const			/// Returns true if a result is available.
		{
			return _pHolder->TryWait(0);
		}
	private:
		ActiveResult();
	private:
		ActiveResultHolderType* _pHolder;
	};

	template<>
	class ActiveResult<void>
	{
	public:
		typedef ActiveResultHolder<void> ActiveResultHolderType;
	public:
		ActiveResult(ActiveResultHolderType* pHolder):_pHolder(pHolder)
		{

		}
		ActiveResult(const ActiveResult& r)
		{
			_pHolder = r._pHolder;
			_pHolder->AddRef();
		}
		ActiveResult& operator=(const ActiveResult& r)
		{
			ActiveResult tmp(r);
			Swap(tmp);
			return *this;
		}

		~ActiveResult()
		{
			_pHolder->DecRef();
		}

		void Swap(ActiveResult& r)
		{
			std::swap(_pHolder, r._pHolder);
		}
		void Wait()
		{
			_pHolder->Wait();
		}
		void Wait(uint32 milliseconds)
		{
			_pHolder->Wait(milliseconds);
		}
		bool TryWait(uint32 milliseconds)
		{
			_pHolder->TryWait(milliseconds);
		}
		void Notify()
		{
			_pHolder->Notify();
		}
		bool IsFailed() const
		{
			return _pHolder->IsFailed();
		}
		std::string GetError() const
		{
			return _pHolder->GetError();
		}
		Exception* GetException() const
		{
			return _pHolder->GetException();
		}
		void SetError(const Exception& exc)
		{
			_pHolder->SetError(exc);
		}
		void SetError(const std::string& msg)
		{
			_pHolder->SetError(msg);
		}
		bool Isvailable() const			/// Returns true if a result is available.
		{
			return _pHolder->TryWait(0);
		}
	private:
		ActiveResult();
	private:
		ActiveResultHolderType* _pHolder;
	};
}

#endif