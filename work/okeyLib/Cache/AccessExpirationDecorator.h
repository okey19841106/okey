/********************************************************************
	created:	2015/09/07
	created:	16:32
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_ACCESS_EXPIRATION_DECORATOR_H__
#define __CACHE_ACCESS_EXPIRATION_DECORATOR_H__


namespace okey
{
	template <typename TArgs>
	class AccessExpirationDecorator
	{
	public:
		AccessExpirationDecorator(): _value()
		{
		}
		AccessExpirationDecorator(const TArgs& p, const int64& diffInMs):_value(p), _span(diffInMs)
		{
		}
		~AccessExpirationDecorator()
		{
		}
		const int64& GetTimeOut() const
		{
			return _span;
		}
		const TArgs& GetValue() const
		{
			return _value;
		}
		TArgs& GetValue()
		{
			return _value;
		}

	private:
		TArgs  _value;
		int64  _span;
	};
}

#endif