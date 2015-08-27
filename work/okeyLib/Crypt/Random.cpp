#include "PreCom.h"
#include "Random.h"
#include <ctime>
#ifdef _WINDOWS
#include <wincrypt.h>
#else

#endif


#define	TYPE_0		0		/* linear congruential */
#define	BREAK_0		8
#define	DEG_0		0
#define	SEP_0		0

#define	TYPE_1		1		/* x**7 + x**3 + 1 */
#define	BREAK_1		32
#define	DEG_1		7
#define	SEP_1		3

#define	TYPE_2		2		/* x**15 + x + 1 */
#define	BREAK_2		64
#define	DEG_2		15
#define	SEP_2		1

#define	TYPE_3		3		/* x**31 + x**3 + 1 */
#define	BREAK_3		128
#define	DEG_3		31
#define	SEP_3		3

#define	TYPE_4		4		/* x**63 + x + 1 */
#define	BREAK_4		256
#define	DEG_4		63
#define	SEP_4		1

namespace okey
{
	Random::Random(int32 sateSize)
	{
		_pBuffer = new char[sateSize];
		initSate((uint32)std::time(NULL),_pBuffer, sateSize);
	}
	Random::~Random()
	{
		delete []_pBuffer;
	}
	void Random::Seed(uint32 seed)
	{
		int32 i, lim;
		_state[0] = seed;
		if (_randType == TYPE_0)
		{
			lim = NSHUFF;
		}
		else
		{
			for (i = 1; i < _randDeg; ++i)
			{
				_state[i] = goodRand(_state[i - 1]);
				_fptr = & _state[_randSep];
				_rptr = & _state[0];
				lim = 10 * _randDeg;
			}
		}
		for(i = 0; i< lim; ++i)
		{
			Next();
		}
	}
	void Random::Seed()
	{
		std::streamsize len;
		if (_randType == TYPE_0)
		{
			len = sizeof(_state[0]);
		}
		else
		{
			len = _randDeg * sizeof(_state[0]);
		}
		RandomInputStream rstr;
		rstr.read((char*)_state, len);
	}

	uint32 Random::Next()
	{
		uint32 i;
		uint32 *f, *r;
		if (_randType == TYPE_0)
		{
			i = _state[0];
			_state[0] = i = goodRand(i) & 0x7fffffff;
		}
		else
		{
			f = _fptr; r = _rptr;
			*f += *r;
			i = (*f >> 1) & 0x7fffffff;
			if (++f >= _endPtr)
			{
				f = _state;
				++r;
			}
			else if( ++r >= _endPtr)
			{
				r = _state;
			}
			_fptr = f;
			_rptr = r;
		}
		return i;
	}

	void Random::initSate(uint32 seed, char* arg_state, int32 n)
	{
		uint32* intitArgState = (uint32*)arg_state;
		if (n < BREAK_0)
		{
			return;
		}
		if (n < BREAK_1) 
		{
			_randType = TYPE_0;
			_randDeg  = DEG_0;
			_randSep  = SEP_0;
		} 
		else if (n < BREAK_2) 
		{
			_randType = TYPE_1;
			_randDeg  = DEG_1;
			_randSep  = SEP_1;
		} 
		else if (n < BREAK_3) 
		{
			_randType = TYPE_2;
			_randDeg  = DEG_2;
			_randSep  = SEP_2;
		} 
		else if (n < BREAK_4) 
		{
			_randType = TYPE_3;
			_randDeg  = DEG_3;
			_randSep  = SEP_3;
		} 
		else 
		{
			_randType = TYPE_4;
			_randDeg = DEG_4;
			_randSep = SEP_4;
		}
		_state = intitArgState + 1;
		_endPtr = &_state[_randDeg];
		if (_randType == TYPE_0)
		{
			intitArgState[0] = _randType;
		}
		else
		{
			intitArgState[0] = MAX_TYPES * (int32)(_rptr - _state) + _randType;
		}
	}

	uint32 Random::goodRand(int32 x)
	{
		int32 hi, lo;
		if (x == 0)
		{
			x = 123459876;
		}
		hi = x / 127773;
		lo = x % 127773;
		x = 16807 * lo - 2836 * hi;
		if (x < 0)
		{
			x += 0x7fffffff;
		}
		return x;
	}

	RandomBuf::RandomBuf(): BufferedStreamBuf(256, std::ios::in)
	{
	}


	RandomBuf::~RandomBuf()
	{
	}


	int RandomBuf::readFromDevice(char* buffer, std::streamsize length)
	{
		int n = 0;

#ifdef _WINDOWS
		HCRYPTPROV hProvider = 0;
		CryptAcquireContext(&hProvider, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
		CryptGenRandom(hProvider, (DWORD) length, (BYTE*) buffer);
		CryptReleaseContext(hProvider, 0);
		n = static_cast<int>(length);
#else
		int fd = open("/dev/urandom", O_RDONLY, 0);
		if (fd >= 0) 
		{
			n = read(fd, buffer, length);
			close(fd);
		}
		if (n <= 0)
		{
			// x is here as a source of randomness, so it does not make
			// much sense to protect it with a Mutex.
			static uint32 x = 0;
			Random rnd1(256);
			Random rnd2(64);
			x += rnd1.next();

			n = 0;
			SHA1Engine engine;
			uint32 t = (uint32) std::time(NULL);
			engine.update(&t, sizeof(t));
			void* p = this;
			engine.update(&p, sizeof(p));
			engine.update(buffer, length);
			uint32 junk[32];
			engine.update(junk, sizeof(junk));
			while (n < length)
			{
				for (int i = 0; i < 100; ++i)
				{
					UInt32 r = rnd2.next();
					engine.update(&r, sizeof(r));
					engine.update(&x, sizeof(x));
					x += rnd1.next();
				}
				DigestEngine::Digest d = engine.digest();
				for (DigestEngine::Digest::const_iterator it = d.begin(); it != d.end() && n < length; ++it, ++n)
				{
					engine.update(*it);
					*buffer++ = *it++;
				}
			}
		}
#endif
		return n;
	}


	RandomIOS::RandomIOS()
	{
	}


	RandomIOS::~RandomIOS()
	{
	}


	RandomBuf* RandomIOS::rdbuf()
	{
		return &_buf;
	}


	RandomInputStream::RandomInputStream(): std::istream(&_buf)
	{
	}


	RandomInputStream::~RandomInputStream()
	{
	}
}