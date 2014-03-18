//////////////////////////////////////////////////////////////
//                    .----.
//                 _.'__    `.
//             .--(#)(##)---/#\
//           .' @          /###\
//           :       ,     #####
//            `-..__.-' _.-\###/ 
//                   `;_:   `"'
//                 .'"""""`.
//                /,        ,\
//               //          \\
//               `-._______.-'
//              ___`. | .'___
//             (______|______)
//
//  created:	2011-11-24 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////

#ifndef _DATA_BUFFER_ALL_H__
#define _DATA_BUFFER_ALL_H__

#include "Types.h"

namespace okey
{
	class DataBufferBase
	{
	public:
		DataBufferBase(){}
		~DataBufferBase(){}
		virtual char* GetBuffer(){return NULL;}
	protected:
	private:
	};
	
	template<int32 MAX_DATA_BUFFER>
	class DataBuffer: public DataBufferBase
	{
	public:
		DataBuffer()
		{
			memset(m_buffer, 0 , MAX_DATA_BUFFER);
		}
		~DataBuffer(){}
		virtual char* GetBuffer(){return m_buffer;}
	protected:
	private:
		char m_buffer[MAX_DATA_BUFFER];
	};

	class DataBufferEx: public DataBufferBase
	{
	public:
		DataBufferEx(int32 size);
		~DataBufferEx();
		virtual char* GetBuffer(){return m_buffer;}
	protected:
	private:
		char* m_buffer;
	};

#define MAX_DATA_LIST 32

	class DataGroup
	{
	public:
		DataGroup();
		~DataGroup();
		bool Init(int32 size);
		bool CreateDataBuffer(int32 dataID);
		DataBufferBase* GetDataBuffer(int32 dataID);
		bool AddDataBuffer(int32 dataID, char* pBuffer, int32 nSize);
		int32 GetSize()const {return m_size;}
		void SetSize(int32 size){Init(size);}
	protected:
	private:
		int32 m_size;
		DataBufferBase* m_datalist[MAX_DATA_LIST];
	};

	class CfgLoaderBase;

#define DATA_GROUP_MAX 64

	class DataManager
	{
	public:
		DataManager();
		~DataManager();
		virtual bool Load(const char* sFile, CfgLoaderBase* pLoader) = 0;
		DataBufferBase* GetDataBuffer(int32 dataGroupID, int32 dataID);
	protected:
		DataGroup *m_datagrouplist[DATA_GROUP_MAX];
	};
}





#endif