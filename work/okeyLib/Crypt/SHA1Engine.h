/********************************************************************
	created:	2015/08/27
	created:	16:10
	author:		okey
	
	purpose:	°²È«¹þÏ£Ëã·¨
*********************************************************************/
#ifndef __SHA1_ENGINE_H__
#define __SHA1_ENGINE_H__

#include "DigestEngine.h"

namespace okey
{
	class SHA1Engine: public DigestEngine
	{
	public:
		enum
		{
			BLOCK_SIZE  = 64,
			DIGEST_SIZE = 20
		};
		SHA1Engine();
		~SHA1Engine();

		unsigned digestLength() const;
		void reset();
		const DigestEngine::Digest& digest();

	protected:
		void updateImpl(const void* data, unsigned length);

	private:
		void transform();
		static void byteReverse(uint32* buffer, int byteCount);

		typedef uint8 BYTE;

		struct Context
		{
			uint32 digest[5]; // Message digest
			uint32 countLo;   // 64-bit bit count
			uint32 countHi;
			uint32 data[16];  // SHA data buffer
			uint32 slop;      // # of bytes saved in data[]
		};
		Context _context;
		DigestEngine::Digest _digest;
		SHA1Engine(const SHA1Engine&);
		SHA1Engine& operator = (const SHA1Engine&);
	};
}

#endif