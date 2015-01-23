/********************************************************************
	created:	2015/01/23
	created:	13:36
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __ABSTRACT_DELEGATE_H__
#define __ABSTRACT_DELEGATE_H__


namespace okey
{
	template<typename TArgs>
	class AbstractDelegate
	{
	public:
		AbstractDelegate(){}
		AbstractDelegate(const AbstractDelegate&){}
		virtual ~AbstractDelegate(){}
		virtual bool Notify(const void* sender, TArgs& arguments) = 0;	/// Invokes the delegate's callback function.
		virtual bool Equals(const AbstractDelegate& other) const = 0;	/// Compares the AbstractDelegate with the other one for equality.
		virtual AbstractDelegate* Clone() const = 0;		/// Returns a deep copy of the AbstractDelegate.
		virtual void Disable() = 0;		/// Disables the delegate, which is done prior to removal.
		virtual const AbstractDelegate* Unwrap() const			/// Returns the unwrapped delegate. Must be overridden by decorators like Expire.
		{
			return this;
		}
	private:

	};
}

#endif