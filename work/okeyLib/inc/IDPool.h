/********************************************************************
	created:	2015/03/10
	created:	15:24
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __ID_POOL_H__
#define __ID_POOL_H__

#include <vector>
#include <assert.h>
#include "Template/TCompileTime.h"


namespace okey
{
// 	class IDPool
// 	{
// 	public:
// 		IDPool(uint32 maxvalue, const std::string& des = "");
// 		~IDPool();
// 		bool AllocID(uint32& allocid);
// 		void FreeID(uint32 allocid);
// 	private:
// 		std::string m_szDes;
// 		uint32 m_uMax;
// 		uint32 m_uCur;
// 		std::deque<uint32> m_FreeIDs;
// 	};
// 
// 	template<typename Value, int32 MAX_VALUE = 1024>
// 	class IDMap
// 	{
// 	public:
// 		typedef hash_map<uint32, Value> MapType;
// 		typedef typename MapType::iterator iterator;
// 		typedef typename MapType::const_iterator const_iterator;
// 		typedef typename MapType::reference reference;
// 		typedef typename MapType::const_reference const_reference;
// 	public:
// 		IDMap(const std::string& des = ""):m_IDPool(MAX_VALUE, des){}
// 		~IDMap(){}
// 
// 		iterator begin()
// 		{
// 			return m_IDMap.begin();
// 		}
// 		iterator end()
// 		{
// 			return m_IDMap.end();
// 		}
// 		iterator find(const uint32& id)
// 		{
// 			return m_IDMap.find(id);
// 		}
// 
// 		const_iterator find(const uint32& id) const
// 		{
// 			return m_IDMap.find(id);
// 		}
// 
// 		void erase(const_iterator itr)
// 		{
// 			m_IDPool.FreeID(itr->first);
// 			m_IDMap.erase(itr);
// 		}
// 
// 		bool insert(const Value& v, uint32& key)
// 		{
// 			if (m_IDPool.AllocID(key))
// 			{
// 				m_IDMap.insert(std::make_pair<uint32, Value>(key, v));
// 				return true;
// 			}
// 			return false;
// 		}
// 
// 		void erase(uint32 id)
// 		{
// 			iterator itr = m_IDMap.find(id);
// 			if (itr != m_IDMap.end())
// 			{
// 				erase(itr);
// 			}
// 		}
// 	private:
// 		MapType m_IDMap;
// 		IDPool m_IDPool;
// 	};
	//16-31: counter 0-15: index
	template<typename IDType, typename ValueType, typename IndexType = uint16, typename CounterType = uint16>
	class id_map
	{
	public:
		typedef ValueType value_type;
		typedef IDType id_type;
		typedef IndexType index_type;
		typedef CounterType counter_type;
		typedef id_map<IDType, ValueType, IndexType, CounterType> this_type;
	protected:
		enum{index_bits = sizeof(index_type) * 8};
		enum{counter_bits = sizeof(counter_type)*8};
		enum{counter_free_bit = 1 <<(counter_bits -1)};
		struct Container
		{
			Container():_counter(counter_free_bit){}
			Template::aligned_storage<value_type> _value;
			counter_type _counter;
		};
		typedef std::vector<index_type> Frees;
		Frees _frees;
		typedef std::vector<Container> Values;
		Values _values;
	public:
		id_map(size_t size):_values(size), _frees(size)
		{
			for (size_t i = 0; i < size; ++i)
			{
				_frees[i] = static_cast<index_type>(size - i - 1);
			}
		}

		void clear()
		{
			_frees.clear();
			size_t count = _values.size();
			for (size_t i = 0; i < count; ++i)
			{
				Container& container = _values[i];
				if (!free_(container._counter))
				{
					destruct_(&container._value);
				}
				_frees.push_back(static_cast<index_type>(count - i - 1));
			}
		}

		id_type insert(const value_type& v)
		{
			assert(!_frees.empty());
			if (!_frees.empty())
			{
				index_type index = _frees.back();
				_frees.pop_back();
				Container& container = _values[index];
				counter_type counter = container._counter;
				construct_(&container._value, v);
				assert(free_(counter));
				counter = (counter & (~counter_free_bit)) + 1;
				assert(counter != 0);
				container._counter = counter;
				return id_(index, counter);
			}
			return 0;
		}

		void insert(id_type id, const value_type& value) //只能按照格式来。
		{
			index_type index = index_(id);
			assert(index < _values.size());
			if (index < _values.size())
			{
				counter_type counter = counter_(id);
				Container& container = _values[index];
				construct_(&container._value, value);
				container._counter = counter;
				typename Frees::iterator itr = std::find(_frees.begin(), _frees.end(), index);
				assert(itr != _frees.end());
				std::swap(*itr, _frees.back());
				_frees.pop_back();
			}
		}

		void erase(id_type id)
		{
			index_type index = index_(id);
			assert(index < _values.size());
			if (index < _values.size())
			{
				counter_type counter = counter_(id);
				Container& container = _values[index];
				if (container._counter = counter)
				{
					_frees.push_back(index);
					destruct_(&container._value);
					container._counter |= counter_free_bit;
				}
			}
		}

		void swap(this_type& other)
		{
			_values.swap(other._values);
			_frees.swap(other._frees);
		}

		void grow(size_t amount)
		{
			if (amount)
			{
				_frees.reserve(_frees.capacity() + amount);
				size_t size = _values.size();
				size_t first = size;
				for (size_t i = 0; i < amount; ++i)
				{
					_frees.push_back(first++);
				}
				Values grown(size + amount);
				for (size_t i = 0; i < size; ++i)
				{
					Container& container = _values[i];
					Container& grownContainer = grown[i];
					if (!free_(counter))
					{
						construct_(&grownContainer._value, *(value_type*)&container._value);
						destruct_(&container._value);
						container._counter = 0;
					}
				}
				grown.swap(_values);
			}
		}

		inline size_t size() const {return _values.size() - _frees.size();}
		inline size_t capacity() const{ return _values.size();}
		inline bool empty() const{ return _frees.size() == _frees.capacity();}
		inline bool full() const{return _frees.empty();}
		inline bool validate(id_type id) const
		{
			index_type index = index_(id);
			counter_type counter = counter_(id);
			return (index < _values.size()) && !free_(counter) && (_values[index]._counter == counter);
		}
		inline bool index_free(index_type index) const
		{
			const Container& container = _values[index];
			return free_(container._counter);
		}
		inline id_type get_index_id(index_type index) const
		{
			const Container& container = _values[index];
			return id_(index, container._counter);
		}
		inline const value_type& get_index(index_type index) const
		{
			const Container& container = _values[index];
			return *reinterpret_cast<const value_type*>(&container._value);
		}
		value_type& get_index(index_type index)
		{
			Container& container = _values[index];
			return *reinterpret_cast<value_type*>(&container._value);
		}
		const value_type& get(id_type id) const
		{
			index_type index = index_(id);
			const Container& container = _values[index];
			assert(counter_(id) == container._counter);
			return *reinterpret_cast<const value_type*>(&container._value);
		}
		value_type& get()
		{
			index_type index = index_(id);
			Container& container = _values[index];
			assert(counter_(id) == container._counter);
			return *reinterpret_cast<value_type*>(&container._value);
		}
		index_type get_index_for_id(id_type id){return index_(id);}
		const value_type& operator[](id_type id) const{return get(id);}
		value_type& operator[](id_type id){return get(id);}
	protected:
		inline id_type id_(index_type index, counter_type counter) const
		{
			return (counter << index_bits) | (index + 1);
		}
		inline id_type counter_(id_type id) const{return id >> index_bits;}
		inline id_type index_(id_type id) const{return (id & ((1<<index_bits) -1)) - 1;}
		inline bool free_(counter_type counter) const{return (counter& counter_free_bit)!=0;}
		inline void construct_(void* buffer, const value_type& v)const
		{
			new (buffer) value_type(v);
		}
		inline void destruct_(void* buffer) const
		{
			static_cast<value_type*>(buffer)->~value_type();
		}
	};
}


#endif