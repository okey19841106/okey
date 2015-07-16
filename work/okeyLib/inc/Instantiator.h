/********************************************************************
	created:	2015/07/16
	created:	16:34
	author:		okey
	
	purpose:	ÊµÀý»¯Ä£°å
*********************************************************************/
#ifndef __TEMPLATE_INSTANTIATOR_H__
#define __TEMPLATE_INSTANTIATOR_H__



namespace okey
{
	template <typename Base>
	class AbstractInstantiator/// Used by DynamicFactory.
	{
	public:
		AbstractInstantiator(){}
		virtual ~AbstractInstantiator(){}
		virtual Base* CreateInstance() const = 0;
		virtual void DestroyInstance(Base* ptr) = 0;
	private:
		AbstractInstantiator(const AbstractInstantiator&);
		AbstractInstantiator& operator = (const AbstractInstantiator&);
	};

	template<typename C, typename Base>
	class Instantiator: public AbstractInstantiator<Base>
	{
		Instantiator(){}
		~Instantiator(){}
		Base* CreateInstance()
		{
			return new C;
		}
		void DestroyInstance(Base* ptr)
		{
			delete ptr;
		}
	public:
		Base* _base;
	};
}

#endif