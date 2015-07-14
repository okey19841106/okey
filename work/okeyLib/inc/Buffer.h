/********************************************************************
	created:	2015/07/14
	created:	14:32
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_BUFFER_H__
#define __BASE_BUFFER_H__


namespace okey
{
	template<typename T>
	class Buffer
	{
	public:
		Buffer(uint32 size):_size(size),_ptr(new T[size]){}
		~Buffer()
		{
			if (_ptr)
			{
				delete []_ptr;
				_ptr = NULL;
			}
		}
		void Resize(uint32 newSize, bool preserveContent = true)
		{
			T* ptr = new T[newSize];
			if (preserveContent)
			{
				uint32 n = newSize > _size ? _size : newSize;
				std::memcpy(ptr, _ptr, n*sizeof(T));
			}
			delete [] _ptr;
			_ptr  = ptr;
			_size = newSize;
		}

		inline uint32 GetSize()const{return _size;}
		T* GetBegin(){return _ptr;}
		T* GetEnd(){return _ptr + _size;}
		const T* GetBegin()const{return _ptr;}
		const T* GetEnd()const{return _ptr + _size;}
		T& operator [] (std::size_t index)
		{
			//poco_assert (index < _size);
			return _ptr[index];
		}

		const T& operator [] (std::size_t index) const
		{
			//poco_assert (index < _size);
			return _ptr[index];
		}
	private:
		Buffer();
		Buffer(const Buffer&);
		Buffer& operator = (const Buffer&);
		uint32 _size;
		T* _ptr;
	};
}

#endif