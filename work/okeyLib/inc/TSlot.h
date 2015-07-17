/********************************************************************
	created:	2015/07/17
	created:	16:02
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TEMPLATE_SLOT_H__
#define __TEMPLATE_SLOT_H__

namespace okey
{
	template <typename R>
	class Slot0 {
	public:
		Slot0() {}
		virtual ~Slot0() {}
		virtual R Proxy() = 0;
		virtual Slot0* Clone() const = 0;
	};

	template <class RetType>
	class FuncSlot0: public Slot0<RetType> 
	{
	public:
		typedef RetType (*Callback)();

		FuncSlot0(Callback cb): _callback(cb) {}
		~FuncSlot0() {}
		RetType Proxy(){ return _callback(); }
		Slot0<RetType>* Clone() const{ return new FuncSlot0(*this); }
		bool operator==(const FuncSlot0& slot) const{ return (_callback == slot._callback); }
	private:
		Callback _callback;
	};

	template<>
	class FuncSlot0<void>: public Slot0<void>
	{
	public:
		typedef void (*Callback)();

		FuncSlot0(Callback cb): _callback(cb) {}
		~FuncSlot0() {}
		void Proxy(){ return _callback(); }
		Slot0<void>* Clone() const{ return new FuncSlot0(*this); }
		bool operator==(const FuncSlot0& slot) const{ return (_callback == slot._callback); }
	private:
		Callback _callback;
	};

	template <typename R>
	FuncSlot0<R> f_slot(R (*func)(void)){ return FuncSlot0<R>(func); }

	template <typename RetType, typename ObjType>
	class MethodSlot0: public Slot0<RetType> 
	{
	public:
		typedef RetType (ObjType::*Callback)();
		MethodSlot0(ObjType* obj, Callback cb): _object(obj), _callback(cb) {}
		~MethodSlot0() {}
		RetType Proxy(){ return (_object->*_callback)(); }
		Slot0<RetType>* Clone() const{ return new MethodSlot0(*this); }
		bool operator==(const MethodSlot0& slot) const{ return (_object == slot._object && _callback == slot._callback); }
	private:
		ObjType* _object;
		Callback _callback;
	};

	template<typename ObjType>
	MethodSlot0<void, ObjType>: public Slot0<void>
	{
	public:
		typedef void (ObjType::*Callback)();
		MethodSlot0(ObjType* obj, Callback cb): _object(obj), _callback(cb) {}
		~MethodSlot0() {}
		void Proxy(){ return (_object->*_callback)(); }
		Slot0<RetType>* Clone() const{ return new MethodSlot0(*this); }
		bool operator==(const MethodSlot0& slot) const{ return (_object == slot._object && _callback == slot._callback); }
	private:
		ObjType* _object;
		Callback _callback;
	};

	template <class R, class O>
	MethodSlot0<R,O> f_slot(O* obj, R (O::*func)(void)){ return MethodSlot0<R,O>(obj, func); }

	template <typename R, typename P1>
	class Slot1 {
	public:
		Slot1() {}
		virtual ~Slot1() {}
		virtual R Proxy(P1 p1) = 0;
		virtual Slot1* Clone() const = 0;
	};

	template <typename RetType, typename P1>
	class FuncSlot1: public Slot0<RetType,P1> 
	{
	public:
		typedef RetType (*Callback)(P1);

		FuncSlot1(Callback cb): _callback(cb) {}
		~FuncSlot1() {}
		RetType Proxy(P1 p1){ return _callback(p1); }
		Slot1<RetType,P1>* Clone() const{ return new FuncSlot1(*this); }
		bool operator==(const FuncSlot1& slot) const{ return (_callback == slot._callback); }
	private:
		Callback _callback;
	};

	template<typename P1>
	class FuncSlot1<void,P1>: public Slot1<void, P1>
	{
	public:
		typedef void (*Callback)(P1);

		FuncSlot1(Callback cb): _callback(cb) {}
		~FuncSlot1() {}
		void Proxy(P1 p1){ return _callback(p1); }
		Slot1<void,P1>* Clone() const{ return new FuncSlot1(*this); }
		bool operator==(const FuncSlot1& slot) const{ return (_callback == slot._callback); }
	private:
		Callback _callback;
	};

	template <typename R, typename P1>
	FuncSlot1<R,P1> f_slot(R (*func)(P1)){ return FuncSlot1<R, P1>(func); }

	template <typename RetType, typename ObjType, typename P1>
	class MethodSlot1: public Slot1<RetType,P1> 
	{
	public:
		typedef RetType (ObjType::*Callback)(P1);
		MethodSlot1(ObjType* obj, Callback cb): _object(obj), _callback(cb) {}
		~MethodSlot1() {}
		RetType Proxy(P1 p1){ return (_object->*_callback)(p1); }
		Slot1<RetType,P1>* Clone() const{ return new MethodSlot1(*this); }
		bool operator==(const MethodSlot1& slot) const{ return (_object == slot._object && _callback == slot._callback); }
	private:
		ObjType* _object;
		Callback _callback;
	};

	template<typename ObjType, typename P1>
	MethodSlot1<void, ObjType, P1>: public Slot1<void, P1>
	{
	public:
		typedef void (ObjType::*Callback)(P1);
		MethodSlot1(ObjType* obj, Callback cb): _object(obj), _callback(cb) {}
		~MethodSlot1() {}
		void Proxy(P1 p1){ return (_object->*_callback)(p1); }
		Slot1<RetType, P1>* Clone() const{ return new MethodSlot1(*this); }
		bool operator==(const MethodSlot1& slot) const{ return (_object == slot._object && _callback == slot._callback); }
	private:
		ObjType* _object;
		Callback _callback;
	};

	template <class R, class O, class P1>
	MethodSlot1<R,O,P1> f_slot(O* obj, R (O::*func)(P1)){ return MethodSlot1<R,O,P1>(obj, func); }


}

#endif