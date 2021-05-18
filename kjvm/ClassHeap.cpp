#include "ClassHeap.h"
#include "JavaClass.h"
#include "FilePathManager.h"
ClassHeap::ClassHeap(void)
{
	pFilePathManager = new FilePathManager();
}

ClassHeap::~ClassHeap(void)
{
	
}

bool ClassHeap::AddClass(JavaClass* pJavaClass)
{
	if(!pJavaClass) return false;
	std::string name=pJavaClass->GetName();

	//TODO- check if already exists

	m_ClassMap[name]=pJavaClass;
	return true;
}

JavaClass* ClassHeap::GetClass(std::string strClassName)
{
	JavaClass *pClass=NULL;
	auto it = m_ClassMap.find(strClassName);
	if(it == m_ClassMap.end())
	{
		pClass = new JavaClass();
		bool bRet=this->LoadClass(strClassName, pClass);
		if(!bRet)
		{
			delete pClass;
			pClass=NULL;
		}		
	}
	else 
	{
		pClass = (JavaClass*)it->second;
	}

	return pClass;
}

bool ClassHeap::LoadClass(std::string strClassName, JavaClass *pClass)
{
	std::string path, relPath;
	if(!pClass) return false;
	relPath=strClassName+".class";
	if(!pFilePathManager->GetAbsolutePath(relPath, path))
		return false;	

	bool bRet=pClass->LoadClassFromFile(path);

	if(!bRet) return false;

	pClass->SetClassHeap(this);

	return AddClass(pClass);
}
