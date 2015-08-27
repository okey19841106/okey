/********************************************************************
	created:	2015/08/27
	created:	15:59
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __DIGEST_ENGINE_H__
#define __DIGEST_ENGINE_H__

#include <vector>

namespace okey
{
	class DigestEngine
	{
	public:
		typedef std::vector<unsigned char> Digest;

		DigestEngine();
		virtual ~DigestEngine();

		void update(const void* data, unsigned length)
		{
			updateImpl(data,length);
		}
		void update(char data)
		{
			updateImpl(&data,1);
		}
		void update(const std::string& data)
		{
			updateImpl(data.c_str(),data.length());
		}
		virtual unsigned digestLength() const = 0;
		virtual void reset() = 0;
		virtual const Digest& digest() = 0;
		static std::string digestToHex(const Digest& bytes);
	protected:
		virtual void updateImpl(const void* data, unsigned length) = 0;
	private:
		DigestEngine(const DigestEngine&);
		DigestEngine& operator = (const DigestEngine&);
	};
}

#endif