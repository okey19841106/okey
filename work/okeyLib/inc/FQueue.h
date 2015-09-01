/********************************************************************
	created:	2015/09/01
	created:	16:42
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_FQUEUE_H__
#define __BASE_FQUEUE_H__

namespace okey
{
	template<typename T>
	class FQueue
	{
	public:
		FQueue():_first(NULL),_next(NULL),_size(0){}
		~FQueue(){}

		uint32 GetSize()
		{
			FastMutex::ScopedLock lock(_mutex);
			return _size;
		}

		void Push(const T& item)
		{
			h* p = new h;
			p->_value = item;
			p->_next = NULL;
			FastMutex::ScopedLock lock(_mutex);
			if (_last != NULL)
			{
				_last->_next = p;
				_last = p;
				++_size;
			}
			else
			{
				_last = _first = p;
				_size = 1;
			}
		}

		bool Pop(T& ret)
		{
			h* tmp = NULL;
			{
				FastMutex::ScopedLock lock(_mutex);
				if (_size == 0)
				{
					return false;
				}
				tmp = _first;
				if (tmp == NULL)
				{
					return false;
				}
				if (--_size)
				{
					_first = _first->_next;
				}
				else
				{
					_first = _last = NULL;
				}
			}
			ret = tmp->_value;
			delete tmp;
			return true;
		}

		bool IsEmpty()
		{
			return GetSize() == 0;
		}
	private:
		struct h
		{
			T _value;
			h* _next;
		};
		h* _first;
		h* _last;
		volatile uint32 _size;
		FastMutex _mutex;
	};
}


#endif