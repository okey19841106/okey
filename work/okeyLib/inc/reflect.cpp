#include "reflect.h"

namespace okey
{


	RTTIRepository RTTIRepository::theRepository;

	inline unsigned hashFunction(const char* name)
	{ 
		unsigned h = 0;
		while (*name != '\0') { 
			h = ((h << 8) ^ (*name++ & 0xFF)) | (h >> 24);
		}
		return h;
	}

	bool RTTIRepository::addClass(RTTIClassDescriptor* cls) 
	{ 
		unsigned h = hashFunction(cls->name);

		for (RTTIClassDescriptor* cp = hashTable[h % RTTI_CLASS_HASH_SIZE]; cp != NULL; cp = cp->collisionChain) { 
			if (cp->hashCode == h && strcmp(cp->name, cls->name) == 0) {
				return false;
			}
		}	    
		cls->next = classes;
		classes = cls;
		cls->collisionChain = hashTable[h % RTTI_CLASS_HASH_SIZE];    
		hashTable[h % RTTI_CLASS_HASH_SIZE] = cls;
		cls->hashCode = h;
		return true;
	}

	RTTIClassDescriptor* RTTIRepository::findClass(char const* name)
	{
		unsigned h = hashFunction(name);
		for (RTTIClassDescriptor* cls = hashTable[h % RTTI_CLASS_HASH_SIZE]; cls != NULL; cls = cls->collisionChain) { 
			if (cls->hashCode == h && strcmp(cls->name, name) == 0) { 
				return cls;
			}
		}
		return NULL;
	}

	bool RTTIRepository::load(char const* filePath)
	{
		return false;
	}

}