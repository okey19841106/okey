
#include "PreCom.h"
#include "TreeNodeBase.h"

namespace okey
{
	TreeNodeBase::TreeNodeBase():m_ChildActive(false),m_ChildSlot(NULL),
	m_prev(NULL),m_next(NULL),m_parent(NULL)
	{

	}

	TreeNodeBase::~TreeNodeBase()
	{

	}

	bool TreeNodeBase::AddChild(TreeNodeBase* pNode)
	{
		if (!pNode)
		{
			return false;
		}
		pNode->m_parent = this;
		if (m_ChildSlot)
		{
			m_ChildSlot->AddBrother(pNode);
			return true;
		}
		m_ChildSlot = pNode;
		return true;
	}

	TreeNodeBase* TreeNodeBase::GetNextChild(TreeNodeBase* pNode)
	{
		if (!pNode)
		{
			return m_ChildSlot;
		}
		return pNode->m_next;
	}

	TreeNodeBase* TreeNodeBase::GetPrevChild(TreeNodeBase* pNode)
	{
		if (!pNode)
		{
			return m_ChildSlot;
		}
		return pNode->m_prev;
	}

	bool TreeNodeBase::RemoveChild(TreeNodeBase* pNode)
	{
		if (!pNode)
		{
			return false;
		}
		pNode->RemoveThisNode();
		return true;
	}

	void TreeNodeBase::RemoveAllChild()
	{
		TreeNodeBase* pChild = GetNextChild(NULL);
		while (pChild)
		{
			pChild->RemoveAllChild();
			pChild = pChild->RemoveThisNode();
		}
	}

	bool TreeNodeBase::AddBrother(TreeNodeBase* pNode)
	{
		if (!pNode)
		{
			return false;
		}
		pNode->m_next = m_next;
		if (m_next)
		{
			m_next->m_prev = pNode;
		}
		pNode->m_prev = this;
		pNode->m_parent = m_parent;
		m_next = pNode;
		return true;
	}

	TreeNodeBase* TreeNodeBase::RemoveThisNode()
	{
		TreeNodeBase* res = m_next;
		if (m_parent)
		{
			m_parent->m_ChildSlot = m_next;
		}
		if (m_next)
		{
			m_next->m_prev = m_prev;
		}
		if (m_prev)
		{
			m_prev->m_next = m_next;
		}
		m_next = m_prev = m_parent = NULL;
		return res;
	}
}