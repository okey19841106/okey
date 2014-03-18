#include "PreCom.h"
#include "ClassManager.h"
#include "AnyTypeBase.h"
#include "XML.h"


namespace okey
{
	/*CClass* ClassManager::GetClass(uint32 classID)
	{
		std::vector<CClass*>::iterator itr = m_classlist.begin();
		for(; itr != m_classlist.end(); ++itr)
		{
			if ((*itr)->GetClassID() == classID)
			{
				return *itr;
			}
		}
		return NULL;
	}
	CClass* ClassManager::GetClass(const char* name)
	{
		std::vector<CClass*>::iterator itr = m_classlist.begin();
		for(; itr != m_classlist.end(); ++itr)
		{
			if (strcmp((*itr)->GetClassName() ,name) == 0)
			{
				return *itr;
			}
		}
		return NULL;
	}*/
	void ClassManager::PrintClass()
	{
		XmlDocument pDoc("class.xml");
		XmlDeclaration Dec( "1.0","UTF-8", "yes" );
		pDoc.InsertEndChild(Dec);
		std::map<UtilID,CClass*>::iterator itr = m_Tmap.begin();
		XmlElement* pTop = new XmlElement("ClassDes");
		pDoc.LinkEndChild(pTop);
		for (;itr!=m_Tmap.end();++itr)
		{
			XmlElement *pRoot = new XmlElement("Class");
			pTop->LinkEndChild(pRoot);
			pRoot->SetAttribute("classID", itr->second->GetClassID());
			pRoot->SetAttribute("name", itr->second->GetClassName());
			if(itr->second->GetParent())
			{
				pRoot->SetAttribute("pClassID", itr->second->GetParent()->GetClassID());
				pRoot->SetAttribute("pClassName", itr->second->GetParent()->GetClassName());
			}
			int32 sum = itr->second->GetMemberCount();
			for (int32 i = 0; i < sum; ++i)
			{
				XmlElement *pMem = new XmlElement("Member");
				pRoot->LinkEndChild(pMem);
				CTypeBase* tb= itr->second->GetMember(i);
				pMem->SetAttribute("MemberName", tb->GetName());
				pMem->SetAttribute("MemberType", tb->GetTypeName());
				pMem->SetAttribute("MemberOffset", tb->GetOffset());
				pMem->SetAttribute("MemberDes", tb->GetDes());
			}
		}
		pDoc.SaveFile();

	}
}