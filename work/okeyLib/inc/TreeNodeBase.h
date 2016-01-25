/*****************************************************************************
	created: 2016-1-25
	author:  suxin
	purpose:                                                             
*****************************************************************************/


#ifndef __TREE_NODE_BASE_H__
#define __TREE_NODE_BASE_H__

#include "Types.h"

namespace okey
{
	class TreeNodeBase
	{
	public:
		TreeNodeBase();
		~TreeNodeBase();
		bool AddChild(TreeNodeBase* pNode);
		void ActiveChild(bool f = true){m_ChildActive = f;}
		TreeNodeBase* GetNextChild(TreeNodeBase* pNode);
		TreeNodeBase* GetPrevChild(TreeNodeBase* pNode);
		bool RemoveChild(TreeNodeBase* pNode);
		void RemoveAllChild();
		bool AddBrother(TreeNodeBase* pNode);
		TreeNodeBase* RemoveThisNode();
		bool IsChildActive(){return m_ChildActive;}
	protected:
		bool m_ChildActive;
		TreeNodeBase* m_ChildSlot;
		TreeNodeBase* m_prev;
		TreeNodeBase* m_next;
		TreeNodeBase* m_parent;
	private:
	};
}


#endif