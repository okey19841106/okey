/********************************************************************
	created:	2015/09/18
	created:	11:00
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_AUTO_VECTOR_H__
#define __BASE_AUTO_VECTOR_H__

#include <vector>

namespace okey
{
	template<typename T>
	class auto_vector
	{
	public:
		class auto_lvalue
		{
		public:
			auto_lvalue(T* &p): _p(p){}
			operator T*() const{return _p;}
			T* operator->() const{return _p;}
			auto_lvalue& operator=(std::auto_ptr<T> ap)
			{
				delete _p;
				_p = ap.release();
				return *this;
			}
		private:
			T*& _p;
		};
	public:
		typedef typename std::vector<T*>::iterator iterator;
		typedef typename std::vector<T*>::const_iterator const_iterator;
		typedef typename std::vector<T*>::reverse_iterator reverse_iterator;
		typedef typename std::vector<T*>::const_reverse_iterator const_reverse_iterator;

		explicit auto_vector(size_t capacity = 0)
		{
			_arr.reserve(capacity);
		}

		~auto_vector()
		{
			clear();
		}

		void push_back(std::auto_ptr<T> ptr)
		{
			_arr.push_back(ptr->get());
			ptr->release();
		}

		inline std::auto_ptr<T> pop_back()
		{
			assert(size() != 0);
			T* p = _arr.back();
			_arr.pop_back();
			return std::auto_ptr<T>(p);
		}

		void clear();

		inline void assign_direct(size_t i, T* p)
		{
			assert(i < size());
			if (_arr[i] != p)
			{
				delete _arr[i];
			}
			_arr[i] = p;
		}
		void assign(size_t i, std::auto_ptr<T> p)
		{
			assert(i < size());
			if (_arr[i] != p.get())
			{
				delete _arr[i];
			}
			_arr[i] = p.release();
		}

		void erase(size_t idx)
		{
			assert(i < size());
			delete _arr[idx];
			_arr.erase(ToIter(idx));
		}

		iterator erase(iterator it)
		{
			assert(it < end());
			delete *it;
			return _arr.erase(it);
		}

		void compact()
		{
			T* null = NULL;
			iterator pos = std::remove(begin(), end(), null);
			_arr.resize(pos - begin());
		}

		size_t ToIndex(iterator const& it)
		{
			assert(it - begin() >= 0);
			return static_cast<size_t>(it - begin());
		}

		size_t ToIndex(reverse_iterator const& rit)
		{
			iterator it = rit.base();
			--it;
			assert(it - begin() >= 0);
			return static_cast<size_t>(it - begin());
		}

		iterator ToIter(size_t idx)
		{
			return begin() + idx;
		}

		reverse_iterator ToRIter(size_t idx)
		{
			++idx;
			return reverse_iterator(ToIter(idx));
		}

		inline void reserve(size_t count)
		{
			_arr.reserve(count);
		}

		void resize(unsigned int newSize);
		
		void insert(size_t idx, std::auto_ptr<T> p)
		{
			assert(idx <= size());
			_arr.insert(ToIter(idx), p.get());
			p->release();
		}
		
		inline bool empty() const{return _arr.empty();}
		inline size_t size() const{return _arr.size();}
		inline size_t capacity() const{ return _arr.capacity();}
		void swap(auto_vector<T>& other)
		{
			_arr.swap(other);
		}
		T const* operator[](size_t i) const{return _arr[i];}
		auto_lvalue operator[](size_t i){return auto_lvalue(_arr[i]);}

		T* back(){return _arr.back();}
		T const* back()const{return _arr.back();}
		T* front(){return _arr.front();}
		T const* front()const{return _arr.front();}

		iterator begin(){return _arr.begin();}
		iterator end(){return _arr.end();}
		const_iterator begin()const{return _arr.begin();}
		const_iterator end()const{return _arr.end();}
		reverse_iterator rbegin(){return _arr.rbegin();}
		reverse_iterator rend(){return _arr.rend();}
		const_reverse_iterator rbegin()const{return _arr.rbegin();}
		const_reverse_iterator rend()const{return _arr.rend();}

	private:
		auto_vector(auto_vector<T> const& src);
		auto_vector<T> operator=(auto_vector<T> const& src);
	private:
		std::vector<T*> _arr;
	};

	template<typename T>
	class DeletePtr
	{
	public:
		void operator()(T* p)
		{
			delete p;
		}
	};

	template<typename T>
	void auto_vector<T>::clear()
	{
		std::for_each(begin(), end(), DeletePtr<T>());
		_arr.clear();
	}

	template<typename T>
	inline void auto_vector<T>::resize(unsigned int newSize)
	{
		if (newSize < size())
		{
			std::for_each(ToIter(newSize), end(), DeletePtr<T>());
		}
		_arr.resize(newSize);
	}
}

#endif