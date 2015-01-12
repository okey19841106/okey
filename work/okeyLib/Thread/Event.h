/********************************************************************
	created:	2015/01/12
	created:	16:56
	author:		okey
	
	purpose:	Event ... signal
*********************************************************************/
#ifndef _OKEY_EVENT_H__
#define _OKEY_EVENT_H__


namespace okey
{
	class Event 
	{
	public:
		Event(bool autoReset = true);
		~Event();

		void Set();	/// Signals the event.
		void Wait();/// Waits for the event to become signalled.

		bool Wait(long milliseconds);/// Waits for the event to become signalled.
		bool TryWait(long milliseconds);/// Waits for the event to become signalled.

		void Reset();/// Resets the event to unsignalled state.

	private:
		Event(const Event&);
		Event& operator = (const Event&);
#ifdef WINDOWS
		HANDLE _event;
#else
		bool            _auto;
		volatile bool   _state;
		pthread_mutex_t _mutex;
		pthread_cond_t  _cond;
#endif
	};
}

#endif