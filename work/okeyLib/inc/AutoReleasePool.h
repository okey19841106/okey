/********************************************************************
	created:	2015/07/30
	created:	11:15
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_AUTO_RELEASE_POOL_H__
#define __BASE_AUTO_RELEASE_POOL_H__

namespace okey
{

	template<typename T>
	class AutoReleasePool
	{
	public:
		AutoReleasePool(){}
		~AutoReleasePool()
		{
			Release();
		}
		void Add(T* obj)
		{
			if (obj)
			{
				_objList.push_back(obj);
			}
		}

		void Release()
		{
			while (!_objList.empty())
			{
				_objList.front()->Release();
				_objList.pop_front();
			}
		}
	private:
		std::list<T*> _objList;

	};
}

#endif