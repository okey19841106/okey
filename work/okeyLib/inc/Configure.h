/********************************************************************
	created:	2015/07/20
	created:	11:27
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_CONFIGURE_H__
#define __BASE_CONFIGURE_H__

#include <map>
#include <string>

namespace okey
{
	class ConfigStore;

	class Configure
	{
	public:
		Configure(ConfigStore& configstore);
		~Configure();
		void Reload();
		void Save();

		class Key
		{
			friend Configure;
		public:
			typedef std::multimap<std::string, std::string> value_map;
			typedef value_map::const_iterator value_iterator;
			typedef std::multimap<std::string, Key*> key_map;
			typedef key_map::const_iterator key_iterator;
			const std::string& GetValue(const std::string& name, const std::string& def);
			void SetValue(const std::string& name, const std::string& value);
			void RemoveValue(const std::string& name);
			Key* GetKey(const std::string& name);
			Key* AddKey(const std::string& name);
			void RemoveKey(const std::string& name);
			inline const value_map& GetValues() const{ return _values; }
			inline const key_map& GetKeys() const{ return _keys; }
		protected:
			Key(Configure* cfg, const std::string& name);
			~Key();
		private:
			Key(const Key&);
			Key& operator=(const Key&);
			Configure*     _cfg;
			std::string _name;
			value_map   _values;
			key_map     _keys;
		};
		friend class Key;
		inline Key& GetRoot(){ return _root; }
		inline ConfigStore& GetStore(){ return _store; }
		inline bool IsModified() const{ return _modified; }
	private:
		Configure(const Configure&);
		Configure& operator=(const Configure&);
		bool          _modified;
		ConfigStore&  _store;
		Key           _root;
	};
}


#endif