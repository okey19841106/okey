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
//  created:	2011-11-27 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////

#ifndef __BASE_PRPCESS_H__
#define __BASE_PRPCESS_H__

#include "Types.h"

namespace okey
{
	template<typename FunObj>
	class ProcessNode
	{
	public:
		ProcessNode(const char* name,FunObj* pFun)
		{
			m_name = name;
			m_pFun = pFun;
			m_next = NULL;
			m_prev = NULL;
		}
		~ProcessNode()
		{

		}
		FunObj* GetFunction(){return m_pFun;}
		bool CheckName(const char* name)
		{
			if (strcmp(name, m_name.c_str()) == 0)
			{
				return true;
			}
			return false;
		}
		const char* GetName(){return m_name.c_str();}
	public:
		ProcessNode<FunObj>* m_next;
		ProcessNode<FunObj>* m_prev;
	private:
		FunObj* m_pFun;
		std::string m_name;
	};

	template<typename FunObj, typename EventObj>
	class ProcessBase
	{
	public:
		ProcessBase()
		{
			m_head = NULL;
		}
		~ProcessBase()
		{

		}
		virtual ProcessNode<FunObj>* RegFunction(const char* name, FunObj* pFun)
		{
			ProcessNode<FunObj>* pNode = new ProcessNode<FunObj>(name, pFun);
			Add(pNode);
			return pNode;
		}
		virtual ProcessNode<FunObj>* RegFunction(ProcessNode<FunObj>* pNode)
		{
			Add(pNode);
			return pNode;
		}

		virtual void RemoveFunction(FunObj* pFun)
		{
			ProcessNode<FunObj>* pNode = NULL;
			do 
			{
				pNode = GetNextNode(pNode);
				if (pNode)
				{
					FunObj* pF = pNode->GetFunction();
					if (pF == pFun)
					{
						Remove(pNode);
					}
				}
			} while (pNode);
		}
		virtual void RemoveFunction(ProcessNode<FunObj>* pNode)
		{
			ProcessNode<FunObj>* tNode = NULL;
			do 
			{
				tNode = GetNextNode(tNode);
				if (tNode)
				{
					if (tNode->CheckName(pNode->GetName()))
					{
						Remove(pNode);
					}
				}
			} while (pNode);
		}

		virtual void Process(const EventObj& eo)
		{
			ProcessNode<FunObj>* pNode = NULL;
			do 
			{
				pNode = GetNextNode(pNode);
				if (pNode)
				{
					FunObj* pF = pNode->GetFunction();
					if (pF)
					{
						(*pF)(eo);
					}
				}
			} while (pNode);
		}
	protected:
		bool Add(ProcessNode<FunObj>* pNode)
		{
			if (!pNode)
			{
				return false;
			}
			if (!m_head)
			{
				m_head = pNode;
				return false;
			}
			ProcessNode<FunObj>* t = m_head;
			while (t->m_next)
			{
				if (t->CheckName(pNode->GetName()))
				{
					return false;
				}
				t = t->m_next;
			}
			t->m_next = pNode;
			pNode->m_prev = t;
			return true;

		}
		ProcessNode<FunObj>* GetNextNode(ProcessNode<FunObj>* pNode)
		{
			if (!pNode)
			{
				return m_head;
			}
			ProcessNode<FunObj>* t = m_head;
			while (t)
			{
				if (t->CheckName(pNode->GetName()))
				{
					return t;
				}
				t = t->m_next;
			}
			return false;

		}

		bool Remove(ProcessNode<FunObj>* pNode)
		{
			if (!pNode || !m_head)
			{
				return false;
			}
			ProcessNode<FunObj>* t = m_head;
			while (t)
			{
				if (t->CheckName(pNode->GetName()))
				{
					ProcessNode<FunObj>* tprev = t->m_prev;
					ProcessNode<FunObj>* tnext = t->m_next;
					tnext->m_prev = t->m_prev;
					tprev->m_next = t->m_next;
					delete t;
					t = NULL;
					return true;
				}
				t = t->m_next;
			}
			return false;

		}
	private:
		ProcessNode<FunObj>* m_head;
	};
}


#endif