/********************************************************************
	created:	2015/08/20
	created:	16:09
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_TEMPLATE_ARRAY_H__
#define __BASE_TEMPLATE_ARRAY_H__


namespace okey
{
	template<typename T>
	class Array
	{
	public:
		Array():_data(NULL),_len(0),_cap(0){}
		explicit Array(int32 size):_data(NULL),_len(0),_cap(0)
		{
			SetSize(size);
		}
		~Array()
		{
			delete[] _data;
		}

		void Add(const T& a)
		{
			if (_len + 1 > _cap)
			{
				SetCapacity(_len + 1);
			}
			_data[_len++] = a;
		}

		void SetSize(int32 s)
		{
			if (s > _cap)
			{
				SetCapacity(s);
			}
			_len = s;
		}
		T& operator[](int32 i)
		{
			//assert
			return _data[i];
		}
		T* Begin(){return _data;}
		T* End(){return _data + _len;}
		int32 GetSize() const {return _len;}
		const T& operator[](int32 i) const
		{
			//assert
			return _data[i];
		}
		const T* Begin()const {return _data;}
		const T* End()const {return _data + _len;}
	private:
		T* _data;
		int32 _len;
		int32 _cap;
		void SetCapacity(int32 s)
		{
			++s;
			if (s < 8)
			{
				s = 8;
			}
			else if (s < _cap * 2)
			{
				s = _cap*2;
			}
			_cap = s;
			T* data = new T[s];
			for (int32 i = 0; i < _len; ++i)
			{
				data[i] = _data[i];
			}
			delete []_data;
			_data = data;
		}
	};
}

#endif