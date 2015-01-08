/********************************************************************
	created:	2015/01/06
	created:	11:13
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef _T_BUFFER_TEMPLATE_H__
#define _T_BUFFER_TEMPLATE_H__


namespace okey
{
	template<typename T>
	class TBuffer
	{
	public:
		TBuffer(uint32 nSize):m_nSize(nSize),m_pPtr(new T[nSize])
		{

		}
		~TBuffer()
		{
			m_nSize = 0;
			delete [] m_pPtr;
		}
		void Resize(uint32 newSize, bool preserveContent = true)
		{
			T* ptr = new T[newSize];
			if (preserveContent)
			{
				uint32 n = newSize > m_nSize ? m_nSize : newSize;
				memcpy(ptr, m_pPtr, n*sizeof(T));
			}
			delete [] m_pPtr;
			m_pPtr  = ptr;
			m_nSize = newSize;
		}

		T* Begin()
		{
			return m_pPtr;
		}
		const T* Begin()
		{
			return m_pPtr;
		}

		T* End()
		{
			return m_pPtr + m_nSize;
		}

		const T* End()
		{
			return m_pPtr + m_nSize;
		}

		uint32 Size()const {return m_nSize;}
		T& operator [] (uint32 index)
		{
			//poco_assert (index < _size);
			return _ptr[index];
		}

		const T& operator [] (uint32 index) const
		{
			//poco_assert (index < _size);
			return _ptr[index];
		}
	private:
		TBuffer();
		TBuffer(const TBuffer&);
		TBuffer& operator = (const TBuffer&);

		uint32 m_nSize;
		T* m_pPtr;
	};
}

#endif