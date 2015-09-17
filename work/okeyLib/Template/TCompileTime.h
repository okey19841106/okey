/********************************************************************
	created:	2015/09/17
	created:	11:12
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TEMPLATE_COMPILE_TIME_H__
#define __TEMPLATE_COMPILE_TIME_H__

#include "TypeTraits.h"

namespace Template
{
	template<int left, int right> 
	struct static_max
	{
		enum{value = (left > right ? left : right)};
	};

	template<int left, int right> 
	struct static_min
	{
		enum{value = (left < right ? left : right)};
	};

	template<unsigned num>
	struct static_log2
	{
		enum{value = static_log2<(num>>1)>::value + 1};
	};

	template<>
	struct static_log2<1>
	{
		enum{value = 0};
	};

	template<> struct static_log2<0>{};

#ifdef WINDOWS
#define alignof _alignof
#else
#define alignof __alignof__
#endif

	template<size_t Alignment>
	struct alignment_type
	{
	private:
		template<typename AlignmentType>
		struct SameAlignment
		{
			enum{value = Alignment == alignof(AlignmentType)};
		};
	public:
		typedef int (alignment_type::*mptr);
		typedef int (alignment_type::*mfptr)();
		typedef typename TSelect<SameAlignment<char>::value, char,
			typename TSelect<SameAlignment<short>::value, short,
				typename TSelect<SameAlignment<int>::value, int,
					typename TSelect<SameAlignment<long>::value, long,
						typename TSelect<SameAlignment<long long>::value, long long,
							typename TSelect<SameAlignment<float>::value, float,
								typename TSelect<SameAlignment<double>::value, double,
									typename TSelect<SameAlignment<long double>::value, long double,
										typename TSelect<SameAlignment<void*>::value, void*,
											typename TSelect<SameAlignment<mptr>::value, mptr,
												typename TSelect<SameAlignment<mfptr>::value, mfptr,char>::Result
											>::Result 
										>::Result 
									>::Result 
								>::Result 
							>::Result 
						>::Result 
					>::Result 
				>::Result 
			>::Result 
		>::Result Result;
	};

	template<size_t Alignment, size_t Size>
	struct aligned_buffer
	{
	private:
		struct storage
		{
			union
			{
				typename alignment_type<Alignment>::Result _alignment;
				char _buffer[Size];
			} buffer;
		};

		storage buffer;
	};

	template<typename T>
	struct aligned_storage
	{
	private:
		struct storage
		{
			union
			{
				typename alignment_type<alignof(T)>::Result _alignment;
				char _buffer[sizeof(T)];
			} buffer;
		};

		storage buffer;
	};
}

#endif