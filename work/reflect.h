/********************************************************************
	created:	2014/03/10
	author:		okey
	
	purpose:	RTTI∑¥…‰Ω·ππ
*********************************************************************/
#ifndef _OKEY_REFLECT_H__
#define _OKEY_REFLECT_H__

#ifdef USE_RTTI
#include <typeinfo>
#endif

#include "type.h"
#include "class.h"
#include "field.h"
#include "method.h"

namespace okey
{

	const int RTTI_CLASS_HASH_SIZE = 1013;

	/**
	 * Repository with runtime type information
	 */
	class  RTTIRepository { 
	  public:
		/**
		 * Get first class in repostiory.
		 * Classes in repository are linked in L1 list. <code>RTTIClassDescriptor::getNext()</code>
		 * method can be used to iterate through elements of this list
		 * @return head element of L1 list of classes
		 */
		RTTIClassDescriptor* getFirstClass() { 
		return classes;
		}

		/**
		 * Find class with specified name
		 * @param name name of the class
		 * @return class descriptor with specified name or <code>NULL</code> if not found
		 */
		RTTIClassDescriptor*               findClass(char const* name);

	#ifdef USE_RTTI
		/**
		 * Find class using RTTI <code>type_info</code> object
		 * @param tinfo <code>type_info</code> object returned by compiler
		 * @return class descriptor or <code>NULL</code> if not found
		 */
		 * 
		RTTIClassDescriptor*               findClass(class type_info const& tinfo) { 
		return findClass(tinfo.getName());
		}
	#endif

		/**
		 * Get instance of repostory
		 * @return instance of repository
		 */
		static RTTIRepository* getInstance() { 
		return &theRepository;
		}

		/**
		 * Add new class descriptor to the repository
		 * @param cls new class descriptor
		 */
		bool addClass(RTTIClassDescriptor* cls); 

		/**
		 * Load type information from specified file. Implementation of this method in this always return false.
		 * At this moment there is only one other source of extracting type information - executable files
		 * in ELF format compiled with debug information. To be able to extract type information from
		 * debug information, you should use <code>RTTIBfdRepository</code> class derived from 
		 * <code>RTTIRepostiory</code> class and overriding thids method.
		 * @param filePath path to the file contaning type information.
		 * @return <code>true</code> if infomation was successfully loaded, <code>false</code> otherwise
		 */
		virtual bool load(char const* filePath);

	  protected:
		static RTTIRepository theRepository;
		RTTIClassDescriptor*  classes;
		RTTIClassDescriptor*  hashTable[RTTI_CLASS_HASH_SIZE];    
	};

}
#endif


