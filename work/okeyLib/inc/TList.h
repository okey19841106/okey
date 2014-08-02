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

#ifndef __T_LIST_H__
#define __T_LIST_H__

#include "Types.h"

namespace okey
{

	template<typename T> class TList;

	template<typename T>
	class TListNode
	{
		friend class TList< TListNode<T> >;
	public:
		TListNode():m_owner(NULL),m_next(NULL),m_prev(NULL),m_plist(NULL){}
		~TListNode(){}
		T* GetOwner()const{return m_owner;}
		void SetOwner(const T* powner){m_owner = powner;}
		T* GetNext()const {return m_next;}
		void SetNext(const T* pnext){m_next = pnext;}
		T* GetPrev()const {return m_prev;}
		void SetPrev(T* prev){m_prev = prev;}
		bool IsInList()
		{
			return m_plist != NULL;
		}
		bool Remove()
		{
			return m_plist->Remove(this);
		}
	protected:
		T* m_owner;
		TListNode<T>* m_next;
		TListNode<T>* m_prev;
		TList< TListNode<T> >* m_plist;
	private:
	};

	template<typename T> class TList
	{
	public:
		TList():m_count(0),m_head(NULL),m_back(NULL){}
		~TList(){}
		bool Add(T* ptr)
		{
			if (!ptr || NULL != ptr->m_plist)
			{
				return false;
			}
			ptr->m_prev = NULL;
			ptr->m_next = m_head;
			if (m_head)
			{
				m_head->m_prev = ptr;
				m_head = ptr;
			}
			else
				m_head = m_back = ptr;
			ptr->m_plist = this;
			++m_count;
			return true;
		}

		bool Push_Back(T* ptr)
		{
			if (!ptr || NULL != ptr->m_plist)
			{
				return false;
			}
			ptr->m_next = NULL;
			ptr->m_prev = m_back;
			if (m_back)
			{
				m_back->m_next = ptr;
				m_back = ptr;
			}
			else
				m_head = m_back = ptr;
			ptr->m_plist = this;
			++m_count;
			return true;
		}

		bool Push_Head(T* ptr)
		{
			return Add(ptr);
		}

		T* Pop_Head()
		{
			if (m_count == 0 || m_head == NULL || m_back == NULL)
			{
				return NULL;
			}
			T* res = m_head;
			Remove(m_head);
			return res;
		}

		T* Pop_Back()
		{
			if (m_count == 0 || m_head == NULL || m_back == NULL)
			{
				return NULL;
			}
			T* res = m_back;
			Remove(m_back);
			return res;
		}

		T* GetNext(T* ptr)
		{
			if (!ptr)
			{
				return m_head;
			}
			if (this != ptr->m_plist)
			{
				return NULL;
			}
			return ptr->m_next;
		}

		T* GetPrev(T* ptr)
		{
			if (!ptr)
			{
				return m_back;
			}
			if (this != ptr->m_plist)
			{
				return NULL;
			}
			return ptr->m_prev;
		}

		T* Remove(T* ptr)
		{
			if (!ptr || this != ptr->m_plist)
			{
				return NULL;
			}
			T* res = ptr->m_next;
			if (ptr->m_prev)
			{
				ptr->m_prev->m_next = ptr->m_next;
			}
			else
			{
				m_head = ptr->m_next;
				if (m_head)
				{
					m_head->m_prev = NULL;
				}
			}
			if (ptr->m_next)
			{
				ptr->m_next->m_prev = ptr->m_prev;
			}
			else
			{
				m_back = ptr->m_prev;
				if (m_back)
				{
					m_back->m_next = NULL;
				}
			}
			//ptr->m_owner = NULL;
			ptr->m_next = NULL;
			ptr->m_prev = NULL;
			ptr->m_plist = NULL;
			--m_count;
			return res;

		}
		
		bool InsertAfter(T* ptr, T* pNode)
		{
			if (!ptr || NULL != ptr->m_plist)
			{
				return false;
			}
			if (!ptr->m_next)
			{
				Push_Back(pNode);
				return true;
			}
			pNode->m_next = ptr->m_next;
			ptr->m_next->m_prev = pNode;
			pNode->m_prev = ptr;
			ptr->m_next = pNode;
			pNode->m_plist = this;
			++m_count;
			return true;
		}

		bool InsertBefore(T* ptr, T*pNode)
		{
			if (!ptr || NULL != ptr->m_plist)
			{
				return false;
			}
			if (!ptr->m_prev)
			{
				Push_Head(pNode);
				return true;
			}
			pNode->m_prev = ptr->m_prev;
			ptr->m_prev->m_next = pNode;
			pNode->m_next = ptr;
			ptr->m_prev = pNode;
			pNode->m_plist = this;
			++m_count;
			return true;
		}

		int32 GetListCount()const{return m_count;}
	protected:
		int32 m_count;
		T* m_head;
		T* m_back;
	};


}






#endif




