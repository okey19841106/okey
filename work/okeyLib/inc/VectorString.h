/********************************************************************
	created:	2014/09/11
	created:	15:26
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __VECTOR_STRING_H__
#define __VECTOR_STRING_H__

#include <memory>
#include <vector>

namespace okey
{

	template<typename E, class A = std::allocator<E> >
	class VectorString : protected std::vector<E, A>
	{
		typedef std::vector<E, A> base;
	public:
		typedef E value_type;
		typedef typename base::iterator iterator;
		typedef typename base::const_iterator const_iterator;
		typedef A allocate_type;
		typedef typename A::size_type size_type;
		typedef typename A::reference reference;

	public:
		VectorString():base()
		{
			base::push_back(value_type());
		}
		VectorString(const value_type* s, size_type len)
		{
			base::reserve(len + 1);
			base::insert(base::end(),s,s + len);
			base::push_back(value_type());
		}
		VectorString(const VectorString& s): base(s){}
		VectorString(const A&a):base(1, value_type(), a){}
		VectorString(const value_type* s, size_type len, const A&a):base(a)
		{
			base::reserve(len + 1);
			base::insert(base::end(),s,s + len);
			base::push_back(value_type());
		}

		VectorString(size_type len, E c, const A& a):base(len+1, c, a)
		{
			base::back() = value_type();
		}

		VectorString& operator = (const VectorString& rhs)
		{
			base& v = *this;
			v = rhs;
			return *this;
		}

		iterator begin()
		{
			return base::begin();
		}
		iterator end()
		{
			return base::end() - 1;
		}

		const_iterator begin()const
		{
			return base::begin();
		}
		const_iterator end()const
		{
			return base::end() - 1;
		}

		size_type size() const
		{
			return base::size() - 1;
		}

		size_type max_size() const
		{
			return base::max_size() - 1;
		}

		size_type capacity() const
		{
			return base::capacity() - 1;
		}

		void reserve(size_type res_arg)
		{
			//assert(res_arg < max_size());
			base::reserve(res_arg + 1);
		}

		template<class ForwardItertoar>
		void append(ForwardItertoar b, ForwardItertoar e)
		{
			const typename std::iterator_traits<ForwardItertoar>::difference_type sz = std::distance(b, e);
			//assert(sz >= 0);
			if (sz == 0)
			{
				return;
			}
			base::reserve(base::size() + sz);
			const value_type& v = *b;
			struct OnBlockExit
			{
				VectorString* that;
				~OnBlockExit()
				{
					that->base::push_back(value_type());
				}
			} onBlockExit = {this};
			(void)onBlockExit;
			//assert(!base::empty());
			//assert(base::back() == value_type());
			base::back() = v;
			base::insert(base::end(), ++b, e);
		}

		void resize(size_type n, E c)
		{
			base::reserve(n + 1);
			base::back() = c;
			base::resize(n + 1, c);
			base::back() = E();
		}

		void swap(VectorString& rhs)
		{
			base::swap(rhs);
		}

		const E* c_str() const
		{
			return &*begin();
		}

		const E* data() const
		{
			return &*begin();
		}

		A get_allocator()const
		{
			return base::get_allocator();
		}
	};

	typedef VectorString<char> BinString;
}


#endif