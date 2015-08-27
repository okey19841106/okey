/********************************************************************
	created:	2015/08/27
	created:	10:52
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_RANDOM_H__
#define __BASE_RANDOM_H__

#include "Stream/BufferedStreamBuf.h"

namespace okey
{
	class Random
	{
	public:
		enum Type
		{
			RND_STATE_0 = 8,
			RND_STATE_32 = 32,
			RND_STATE_64 = 64,
			RND_STATE_128 = 128,
			RND_STATE_256 = 256,
		};

		Random(int32 sateSize = 256);
		~Random();
		void Seed(uint32 seed);
		void Seed();
		uint32 Next();
		inline uint32 Next(uint32 n)
		{
			return Next()%n;
		}
		inline char NextChar()
		{
			return char((Next() >> 3)&0xff);
		}
		inline bool NextBool()
		{
			return (Next()&0x1000) != 0;
		}
		inline f32 NextFloat()
		{
			return f32(Next())/0x7fffffff;
		}
		inline f64 NextDouble()
		{
			return f32(Next())/0x7fffffff;
		}
	protected:
		void initSate(uint32 seed, char* arg_state, int32 n);
		static uint32 goodRand(int32 x);
	private:
		enum
		{
			MAX_TYPES = 5,
			NSHUFF = 50,
		};

		uint32* _fptr;
		uint32* _rptr;
		uint32* _state;
		int32 _randType;
		int32 _randDeg;
		int32 _randSep;
		uint32* _endPtr;
		char* _pBuffer;
	};

	class RandomBuf: public BufferedStreamBuf
	{
	public:
		RandomBuf();
		~RandomBuf();
		int readFromDevice(char* buffer, std::streamsize length);
	};


	class RandomIOS: public virtual std::ios
	{
	public:
		RandomIOS();
		~RandomIOS();
		RandomBuf* rdbuf();

	protected:
		RandomBuf _buf;
	};


	class RandomInputStream: public RandomIOS, public std::istream
	{
	public:
		RandomInputStream();
		~RandomInputStream();
	};
}

#endif