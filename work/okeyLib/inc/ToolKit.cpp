#include "PreCom.h"
#include "ToolKit.h"
#include <stack>
#include "Thread/Mutex.h"

namespace okey
{
	void ToolKit::BytesToHex(uchar* buf, uint32 len, uchar* hex)
	{
		uchar* end = buf + len;
		do 
		{
			uchar c = *buf;
			uchar hexc = (c >> 4);
			*hex++ = ((hexc <= 9) ? (hexc + '0') : (hexc + ('A' - 10)));
			hexc = c & 0x0F;
			*hex++ = ((hexc < 9) ? (hexc + '0') : (hexc + ('A' - 10)));
		} while (++buf != end);
	}

	void ToolKit::HexToBytes(uchar* hex, uint32 len, uchar* buf)
	{
		len = (len / 2 * 2);
		uchar* end = hex + len;
		while(hex != end)
		{
			uchar hexc = *hex++;
			uchar c = ((hexc <= '9') ? (hexc - '0') : (hexc - 'A' + 10));
			c = c << 4;
			hexc = *hex++;
			*buf++ = c + ((hexc <= '9') ? (hexc - '0') : (hexc - 'A' + 10));
		}
		*buf = 0;
	}

	class LCAExitHelper
	{
		typedef void (*fun)(void);
	public:
		LCAExitHelper(){}
		~LCAExitHelper()
		{
			m_Mutex.Lock();
			while(!m_stack.empty())
			{
				fun f = m_stack.top();
				m_stack.pop();
				(*f)();
			}
			m_Mutex.UnLock();
		}

		void RegisterFunc(fun f)
		{
			m_Mutex.Lock();
			m_stack.push(f);
			m_Mutex.UnLock();
		}

	private:
		std::stack<fun> m_stack;
		Mutex m_Mutex;
	};

	inline LCAExitHelper& GetExitHelper()
	{
		static LCAExitHelper ins;
		return ins;
	}

	void ToolKit::AtExit(void (*fuction)(void))
	{
		GetExitHelper().RegisterFunc(fuction);
	}
}