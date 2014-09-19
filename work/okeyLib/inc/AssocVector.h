/********************************************************************
	created:	2014/09/19
	created:	16:05
	author:		okey
	
	purpose:	assoc vector
*********************************************************************/
#ifndef _ASSOC_VECTOR_H__
#define _ASSOC_VECTOR_H__

#include <algorithm>
#include <functional>
#include <vector>
#include <utility>


namespace okey
{
	namespace Private
	{
		template<typename Value, typename C>
		class AssocVectorCompare : public C
		{
			typedef std::pair<typename C::first_argument_type, Value> Data;
			typedef typename C::first_argument_type first_argument_type;
		public:
			AssocVectorCompare(){}
			AssocVectorCompare(const C& src):C(src){}

			bool operator()(const first_argument_type& lhs, const first_argument_type& rhs)const
			{
				return C::operator()(lhs,rhs);
			}

			bool operator()(const Data& lhs, const first_argument_type& rhs)
			{
				return operator()(lhs.first,rhs);
			}

			bool operator()(const first_argument_type& lhs, const Data& rhs)
			{
				return operator()(lhs,rhs.first);
			}

			bool operator()(const Data& lhs, const Data& rhs)
			{
				return operator()(lhs.first, rhs.first);
			}
		};
	}

	template<typename K, typename V, typename C = std::less<K>, typename A = std::allocator<std::pair<K, V> > >
	class AssocVector: private std::vector< std::pair<K,V> ,A>, private Private::AssocVectorCompare<V, C>
	{
		typedef std::vector< std::pair<K,V>, A> Base;
		typedef Private::AssocVectorCompare<V, C> MyCompare;
	public:
		typedef K key_type;
		typedef V mapped_type;
		typedef typename Base::value_type	value_type;
		typedef	C key_compare;
		typedef A allocator_type;
		typedef typename A::reference	reference;
		typedef typename A::const_reference const_reference;
		typedef typename Base::iterator	iterator;
		typedef typename Base::const_iterator	const_iterator;
		typedef typename Base::size_type	size_type;
		typedef typename Base::difference_type difference_type;
		typedef typename A::pointer	pointer;
		typedef typename A::const_pointer	const_pointer;
		typedef typename Base::reverse_iterator	reverse_iterator;
		typedef typename Base::const_reverse_iterator const_reverse_iterator;
	public:
		class value_compare: public std::binary_function<value_type, value_type, bool>, private key_compare
		{
			friend class AssocVector;
		protected:
			value_compare(key_compare pred): key_compare(pred){}
		public:
			bool operator()(const value_type& lhs, const value_type& rhs) const
			{
				return key_compare::operator()(lsh.first,rhs.first);
			}
		};

	public:
		explicit AssocVector(const key_compare& comp = key_compare(), const A& alloc = A()):Base(alloc),MyCompare(comp){}
		template<typename InputIterator>
		AssocVector(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const A& alloc = A())
			:Base(first,last,alloc),MyCompare(comp)
		{
			MyCompare& me = *this;
			std::sort(begin(), end(), me);
		}

		AssocVector& operator=(const AssocVector& rhs) //为了释放掉临时变量。。。
		{
			AssocVector(rhs).swap(*this);
			return *this;
		}

		iterator begin(){return Base::begin();}
		const_iterator begin() const{return Base::begin();}
		iterator end(){return Base::end();}
		const_iterator end() const {return Base::end();}
		reverse_iterator rbegin(){return Base::rbegin();}
		const_reverse_iterator rbegin() const {return Base::rbegin();}
		reverse_iterator rend(){return Base::rend();}
		const_reverse_iterator rend() const {return Base::rend();}

		bool empty()const {return Base::empty();}
		size_type size()const {return Base::size();}
		size_type max_size(){return Base::max_size();}

		mapped_type& operator[](const key_type& key)
		{
			return insert(value_type(key,mapped_type())).first->second;
		}

		std::pair<iterator, bool> insert(const value_type& val)
		{
			bool found = true;
			iterator i(lower_bound(val.first));
			if (i == end() || this->operator()(val.first, i->first))
			{
				i = Base::insert(i, val);
				found = false;
			}
			return std::make_pair(i, !found);
		}

		iterator insert(iterator pos, const value_type& val)
		{
			if ((pos == begin() || this->operator()(*(pos - 1), val)) && (pos == end() || this->operator()(val, *pos)))
			{
				return Base::insert(pos, val);
			}
			return insert(val).first;
		}

		template<typename InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (; first != last; ++ first)
			{
				insert(*first);
			}
		}

		void erase(iterator pos){Base::erase(pos);}
		size_type erase(const key_type& k)
		{
			iterator i(find(k));
			if (i == end())
			{
				return 0;
			}
			erase(i);
			return 1;
		}

		void erase(iterator first, iterator last){Base::erase(first, last);}

		void swap(AssocVector& other)
		{
			Base::swap(other);
			MyCompare& me = *this;
			MyCompare& rhs = other;
			std::swap(me, rhs);
		}

		void clear(){Base::clear();}

		key_compare key_comp() const{return *this;}
		value_compare val_comp()const
		{
			const key_compare& comp = *this;
			return value_compare(comp);
		}

		iterator find(const key_type& k)
		{
			iterator i(lower_bound(k));
			if (i != end() && this->operator()(k, i->first))
			{
				i = end();
			}
			return i;
		}

		const_iterator find(const key_type& k) const
		{
			const_iterator i(lower_bound(k));
			if (i != end() && this->operator()(k, i->first))
			{
				i = end();
			}
			return i;
		}

		size_type count(const key_type& k)const //感觉像has。。。
		{
			return find(k) != end();
		}

		iterator lower_bound(const key_type& k)
		{
			MyCompare& me = *this;
			return std::lower_bound(begin(), end(), k, me);
		}

		const_iterator lower_bound(const key_type& k) const 
		{
			const MyCompare& me = *this;
			return std::lower_bound(begin(), end(), k, me);
		}

		iterator upper_bound(const key_type& k)
		{
			MyCompare& me = *this;
			return std::upper_bound(begin(), end(), k, me);
		}

		const_iterator upper_bound(const key_type& k) const
		{
			const MyCompare& me = *this;
			return std::upper_bound(begin(), end(), k, me);
		}

		std::pair<iterator, iterator> equal_range(const key_type& k)
		{
			MyCompare& me = *this;
			std::equal_range(begin(), end(), k , me);
		}

		std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{
			const MyCompare& me = *this;
			std::equal_range(begin(), end(), k , me);
		}

		template<typename K1, typename V1, typename C1, typename A1>
		friend bool operator==(const AssocVector<K1,V1,C1,A1>& lsh, const AssocVector<K1,V1,C1,A1>& rhs);
		template<typename K1, typename V1, typename C1, typename A1>
		friend bool operator!=(const AssocVector<K1,V1,C1,A1>& lsh, const AssocVector<K1,V1,C1,A1>& rhs);
		template<typename K1, typename V1, typename C1, typename A1>
		friend bool operator>(const AssocVector<K1,V1,C1,A1>& lsh, const AssocVector<K1,V1,C1,A1>& rhs);
		template<typename K1, typename V1, typename C1, typename A1>
		friend bool operator>=(const AssocVector<K1,V1,C1,A1>& lsh, const AssocVector<K1,V1,C1,A1>& rhs);
		template<typename K1, typename V1, typename C1, typename A1>
		friend bool operator<=(const AssocVector<K1,V1,C1,A1>& lsh, const AssocVector<K1,V1,C1,A1>& rhs);
		bool operator<(const AssocVector& rhs) const
		{
			const Base& me = *this;
			const Base& yo = rhs;
			return me < yo;
		}

	};

	template<typename K, typename V, typename C, typename A>
	inline bool operator==(const AssocVector<K,V,C,A>& lhs, const AssocVector<K,V,C,A>& rhs)
	{
		const std::vector< std::pair<K, V> , A>& me = lhs;
		return me == rhs;
	}

	template<typename K, typename V, typename C, typename A>
	inline bool operator!=(const AssocVector<K,V,C,A>& lhs, const AssocVector<K,V,C,A>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename K, typename V, typename C, typename A>
	inline bool operator>(const AssocVector<K,V,C,A>& lhs, const AssocVector<K,V,C,A>& rhs)
	{
		return rhs < lhs;
	}

	template<typename K, typename V, typename C, typename A>
	inline bool operator>=(const AssocVector<K,V,C,A>& lhs, const AssocVector<K,V,C,A>& rhs)
	{
		return !(lhs<rhs);
	}

	template<typename K, typename V, typename C, typename A>
	inline bool operator<=(const AssocVector<K,V,C,A>& lhs, const AssocVector<K,V,C,A>& rhs)
	{
		return !(rhs < lhs);
	}

	template<typename K, typename V, typename C, typename A>
	void swap(const AssocVector<K,V,C,A>& lhs, const AssocVector<K,V,C,A>& rhs)
	{
		lhs.swap(rhs);
	}
}


#endif