//////////////////////////////////////////////////////////////
//                    .----.
//                 _.'__    `.
//             .--(#)(##)---/#\
//           .' @          /###\
//           :       ,     #####
//            `-..__.-' _.-\###/ 
//                   `;_:   `"'
//                 .'"""""`.
//                /,        ,\
//               //          \\
//               `-._______.-'
//              ___`. | .'___
//             (______|______)
//
//  created:	2011-12-15 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////


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