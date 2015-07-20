#include "PreCom.h"
#include "Configure.h"
#include "ConfigStore.h"

namespace okey
{
	Configure::Configure(ConfigStore& configstore):_store(configstore),_modified(false),_root(Key(this, ""))
	{
		_store.read(_root);

	}

	Configure::~Configure()
	{
		Save();
	}

	void Configure::Reload()
	{
		_store.read(_root);
		_modified = false;
	}

	void Configure::Save()
	{
		if(_modified)
		{
			_store.update(_root);
			_modified = false;
		}
	}

	const std::string& Configure::Key::GetValue(const std::string& name, const std::string& def)
	{
		value_map::iterator itr = _values.find(name);
		if (itr != _values.end())
		{
			return itr->second;
		}
		return def;
	}

	void Configure::Key::SetValue(const std::string& name, const std::string& value)
	{
		_values.insert(make_pair(name, value));
		_cfg->_modified = true;
	}

	void Configure::Key::RemoveValue(const std::string& name)
	{
		_values.erase(name);
		_cfg->_modified = true;
	}

	Configure::Key* Configure::Key::GetKey(const std::string& name)
	{
		key_map::iterator itr = _keys.find(name);
		if (itr != _keys.end())
		{
			return itr->second;
		}
		return NULL;
	}

	Configure::Key* Configure::Key::AddKey(const std::string& name)
	{
		Key* k = new Key(_cfg, name);
		_keys.insert(make_pair(name, k));
		_cfg->_modified = true;
		return k;
	}

	void Configure::Key::RemoveKey(const std::string& name)
	{
		std::pair<key_map::iterator, key_map::iterator> mi = _keys.equal_range(name);
		for(key_map::iterator i = mi.first; i != mi.second; ++i)
			delete i->second;
		if(distance(mi.first, mi.second) > 0)
		{
			_keys.erase(mi.first, mi.second);
			_cfg->_modified = true;
		}
	}

	Configure::Key::Key(Configure* cfg, const std::string& name): _cfg(cfg), _name(name) 
	{
	}

	Configure::Key::~Key()
	{
		for(key_map::const_iterator i = _keys.begin();i != _keys.end(); i++)
		{
			delete i->second;
		}
	}
}