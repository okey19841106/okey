/********************************************************************
	created:	2015/09/07
	created:	11:01
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_EXPIRATION_DECORATOR_H__
#define __CACHE_EXPIRATION_DECORATOR_H__

#include "TimeStamp.h"

namespace okey
{
	template<typename TArgs>
	class ExpirationDecorator
	{
	public:
		ExpirationDecorator():_value(),_expiresAt(){}
		ExpirationDecorator(const TArgs& p, const int64& diffms):_value(p),_expiresAt()//∫¡√Î
		{
			_expiresAt += diffms;
		}
		ExpirationDecorator(const TArgs& p, const TimeStamp& t):_value(p),_expiresAt(t){}
		~ExpirationDecorator(){}

		const TimeStamp& GetExpiration() const{return _expiresAt;}
		const TArgs& GetValue() const{return _value;}
		TArgs& GetValue(){return _value;}
	private:
		TArgs _value;
		TimeStamp _expiresAt;
	};
}

#endif