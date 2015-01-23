/********************************************************************
	created:	2015/01/23
	created:	16:12
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __FIFO_STRATEGY_H__
#define __FIFO_STRATEGY_H__

namespace okey
{
	template <class TArgs, class TDelegate> 
	class FIFOStrategy: public DefaultStrategy<TArgs, TDelegate>
	{
	public:
		FIFOStrategy(){}
		FIFOStrategy(const FIFOStrategy& s):DefaultStrategy<TArgs, TDelegate>(s){}
		~FIFOStrategy(){}
		FIFOStrategy& operator = (const FIFOStrategy& s)
		{
			DefaultStrategy<TArgs, TDelegate>::operator = (s);
			return *this;
		}
	};
}

#endif