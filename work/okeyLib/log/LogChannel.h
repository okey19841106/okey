/********************************************************************
	created:	2015/01/04
	created:	14:43
	author:		okey
	
	purpose:	线程安全的日志
*********************************************************************/

#ifndef __LOG_CHANNEL_H__
#define __LOG_CHANNEL_H__

#include "Thread/Mutex.h"
#include "File/File.h"
#include "DateTime.h"
#include <sstream>

namespace okey
{
	extern const uint32 g_log_constant_value;//最大2M日志，超过不处理。

	template<int32 nCacheSize>
	class LogChannel
	{
	public:
		enum CONSTANT_VALUE
		{
			BUFFSIZE = nCacheSize,
			FLUSH_SIZE = BUFFSIZE * 7 / 8,
		};

		LogChannel()
		{
			memset(m_CheckBlock,0,BUFFSIZE);
			m_nPos = 0;
			m_nFileSize = 0;
			m_nHoldSize = 0;
			m_bDisplayEnabled = false;
			m_bInited = false;
		}
		~LogChannel()
		{
			if (true == m_bInited && 0 < m_nPos)
			{
				MutexGuard guid(m_cMutex);
				flush();
			}
		}

		bool Init(const std::string& filename)
		{
			if (filename.empty())
			{
				m_bInited = false;
				return false;
			}
			m_sFileName = filename;
			memset(m_CheckBlock,0,BUFFSIZE);
			m_nPos = 0;
			m_nFileSize = 0;
			m_nHoldSize = 0;
			m_bDisplayEnabled = false;
			m_bInited = true;
			return true;
		}
		bool DisplayEnabled() const{returm m_bDisplayEnabled;}
		void SetDisplayEnabedFlay(bool f){m_bDisplayEnabled = f;}
		bool Log(char const* szLog, uint32 nSize, bool bFlush)
		{
			bool bRet = false;
			MutexGuard gurd(m_cMutex);
			if (szLog == NULL  || nSize == 0 || nSize > g_log_constant_value)
			{
				return false;
			}
			std::stringstream sstr;
			DateTime dt;
			sstr<<"["<<DateTime::toString(dt)<<"]";
			Write(sstr.str().c_str(), sstr.str().length(), false);
			bRet = Write(szLog, nSize, false);
			Write("\n",1,bFlush);
			if (m_bDisplayEnabled)
			{
				printf("%s", szLog);
			}
			else
			{
				flush();
			}
			return true;
		}
	private:
		bool Write(char const* szLog, uint32 nSize, bool bFlush)
		{
			if (!m_bInited || szLog == NULL || nSize > g_log_constant_value || m_nPos > BUFFSIZE)
			{
				return false;
			}
			if (BUFFSIZE - m_nPos > nSize)
			{
				memcpy(m_CheckBlock + m_nPos , szLog, nSize);
				m_nPos += nSize;
			}
			else
			{
				uint32 nWlen = BUFFSIZE - m_nPos;
				memcpy(m_CheckBlock + m_nPos , szLog, nSize);
				m_nPos += nWlen;
				flush();
				char const *pleaves = szLog + nWlen;
				uint32 nllen = nSize - nWlen;
				Write(pleaves, nllen, bFlush);
			}
			if (0 < m_nPos)
			{
				if (FLUSH_SIZE < m_nPos || bFlush)
				{
					flush();
				}
			}
			return true;
		}
		void flush()
		{
			if (m_nPos == 0)
			{
				return;
			}
			try
			{
				File file(m_sFileName, File::acWrite, File::AllowWrite, File::Append);
				file.WriteBufer(m_CheckBlock,m_nPos);
			}
			catch(...)
			{
				printf("error init log file %s", m_sFileName.c_str());
			}
			m_nPos = 0;
		}

	private:
		std::string m_sFileName;
		char m_CheckBlock[BUFFSIZE];
		uint32 m_nPos;
		uint32 m_nFileSize;
		uint32 m_nHoldSize;
		bool m_bDisplayEnabled;
		bool m_bInited;
		Mutex m_cMutex;
	};
}

#endif