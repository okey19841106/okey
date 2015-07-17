/********************************************************************
	created:	2015/07/17
	created:	15:54
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef STACK_H
#define STACK_H

#include "Types.h"
#include <vector>

namespace okey
{

/**
 * our own stack
 */
template<typename T, uint32 N>
class Stack
{
public:
	/**
	 * stack constructor
	 * @param size the max count of the elements in stack
	 */
	Stack(): m_Size(0), m_Capacity(N), m_Top(-1)
	{
		m_List.reserve(m_Capacity);
	}
	~Stack(){}

public:
	size_t Size() const{return m_Size;}
	bool Push( const T& element )
	{
		
		if( m_Capacity <= Size() )
		{
			return false;
		}

		++m_Top;
		m_List.push_back(element);

		++m_Size;

		return true;
		
	}
	bool Pop()
	{
		
		if( Size() <= 0 )
		{
			return false;
		}

		--m_Top;
		m_List.pop_back();
		--m_Size;

		return true;
		
	}
	bool Top( T& element )
	{
		if( Size() <= 0 )
		{
			return false;
		}

		element = m_List[m_Top];

		return true;
	}

private:
	std::vector<T> m_List;
	uint32 m_Size;
	uint32 m_Capacity;
private:
	int32 m_Top;
};

}

#endif //STACK_H
