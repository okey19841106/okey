#ifndef OKEY_BASE_COPYABLE_H
#define OKEY_BASE_COPYABLE_H

namespace okey
{

class nocopyable
{
protected:
	nocopyable() {}
	virtual ~nocopyable() {}
private:  // emphasize the following members are private
	nocopyable( const nocopyable& );
	const nocopyable& operator=( const nocopyable& );
};

}



#endif  
