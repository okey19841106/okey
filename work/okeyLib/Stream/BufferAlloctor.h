/********************************************************************
	created:	2014/12/15
	created:	17:36
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BUFFER_ALLOCTOR_H__
#define __BUFFER_ALLOCTOR_H__

#include <iosfwd>
#include <ios>

namespace okey
{
	template <typename ch>
	class TBuffAlloctor
	{
	public:
		typedef ch char_type;

		static char_type* allocate(std::streamsize size)
		{
			return new char_type[static_cast<std::size_t>(size)];
		}

		static void deallocate(char_type* ptr, std::streamsize size)
		{
			delete [] ptr;
		}
	};

}


#endif