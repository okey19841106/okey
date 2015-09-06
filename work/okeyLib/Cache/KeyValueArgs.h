/********************************************************************
	created:	2015/09/06
	created:	16:25
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_KEY_VALUE_ARGS_H__
#define __CACHE_KEY_VALUE_ARGS_H__


namespace okey
{
	template<typename Key, typename Value>
	class KeyValueArgs
	{
	public:
		KeyValueArgs(const Key& k, const Value& v):_key(k),_value(v){}
		~KeyValueArgs(){}
		KeyValueArgs(const KeyValueArgs& k):_key(k._key),_value(k._value){}
		const Key& key()const{return _key;}
		const Value& value()const{return _value;}
	protected:
		const Key& _key;
		const Value& _value;
	private:
		KeyValueArgs& operator=(const KeyValueArgs&);
	};
}

#endif