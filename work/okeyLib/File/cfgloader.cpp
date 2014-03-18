#include "PreCom.h"
#include "cfgloader.h"
#include "FileBase.h"


namespace okey
{

	CfgLoaderStream::CfgLoaderStream(FileBase* pFile):CfgLoaderBase(pFile)
	{

	}
	CfgLoaderStream::~CfgLoaderStream()
	{

	}
	bool CfgLoaderStream::Load(const char* pFileName)
	{
		if (!m_pFile || !pFileName)
		{
			return false;
		}
		Clear();
		if(!m_pFile->Open(pFileName))
		{
			return false;
		}
		char buffer[1024];
		if(!m_pFile->ReadLine(buffer,1024))
		{
			return false;
		}
		std::string slab = buffer;
		if (slab[slab.length() - 1] == '\n')
		{
			slab = slab.substr(0,slab.length() -1);
		}
		if (slab[slab.length() - 1] == '\r')
		{
			slab = slab.substr(0,slab.length() -1);
		}
		slab += '\t';
		ValueVector tmpval;
		while (m_pFile->ReadLine(buffer, 1024))
		{
			std::string val;
			val = buffer;
			if (slab[slab.length() - 1] == '\n')
			{
				slab = slab.substr(0,slab.length() -1);
			}
			if (val[val.length() - 1] == '\r')
			{
				val = val.substr(0,val.length() -1);
			}
			val += '\t';
			tmpval.push_back(val);
		}
		{
			int32 pos1 = -1;
			std::string st = slab;
			int32 i = 0;
			while (true)
			{
				int32 pos2 = (int32)st.find('\t',++pos1);
				if (pos2 == -1)
				{
					break;
				}
				std::string vlab = st.substr(pos1,pos2-pos1);
				m_label.push_back(vlab);
				m_StringMap[vlab] = i;
				pos1 = pos2;
				++i;
			}
		}
		{
			ValueVector::iterator itr = tmpval.begin();
			for (;itr != tmpval.end(); ++itr)
			{
				int32 pos1 = -1;
				std::string st = (*itr);
				ValueVector vvalue;
				while (true)
				{
					int32 pos2 = st.find('\t',++pos1);
					if (pos2 == -1)
					{
						break;
					}
					std::string vlab = st.substr(pos1,pos2-pos1);
					vvalue.push_back(vlab);
					pos1 = pos2;
				}
				if (!vvalue.empty())
				{
					m_value.push_back(vvalue);
				}
			}
		}


		return true;
	}
	bool CfgLoaderStream::GetLabel(LabelVector& vlist)
	{
		if (m_label.size() == 0)
		{
			return false;
		}
		vlist = m_label;
		return true;
	}
	bool CfgLoaderStream::GetValueList(int32 index, ValueVector& vlist)
	{
		if (m_value.size() == 0 || (int32)m_value.size() <= index || index < 0)
		{
			return false;
		}
		vlist = m_value[index];
		return true;
	}
	void CfgLoaderStream::Clear()
	{
		m_label.clear();
		AllValue::iterator itr = m_value.begin();
		for (;itr != m_value.end(); ++itr)
		{
			itr->clear();
		}
		m_value.clear();
	}

}
