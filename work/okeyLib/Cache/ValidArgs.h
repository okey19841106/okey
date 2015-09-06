/********************************************************************
	created:	2015/09/06
	created:	16:29
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_VALID_ARGS_H__
#define __CACHE_VALID_ARGS_H__

namespace okey
{
	template<typename Key>
	class ValidArgs
	{
	public:
		ValidArgs(const Key& key):_key(key),_isValid(true){}
		~ValidArgs(){}
		ValidArgs(const ValidArgs& key):_key(key._key),_isValid(key._isValid){}
		const Key& key()const{return _key;}
		bool isValid() const{return _isValid;}
		void invalidate(){_isValid = false;}
	protected:
		const Key& _key;
		bool _isValid;
	private:
		ValidArgs& operator=(const ValidArgs&);
	};
}

#endif