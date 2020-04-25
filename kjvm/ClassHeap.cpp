#include "StdAfx.h"
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

BOOL ClassHeap::AddClass(JavaClass* pJavaClass)
{
	if(!pJavaClass) return FALSE;
	CString name=pJavaClass->GetName();

	//TODO- check if already exists

	m_ClassMap.SetAt(name, pJavaClass);
	return TRUE;
}

JavaClass* ClassHeap::GetClass(CString strClassName)
{
	void *pClass=NULL;
	if(!m_ClassMap.Lookup(strClassName, pClass))
	{
		pClass = new JavaClass();
		BOOL bRet=this->LoadClass(strClassName, (JavaClass*)pClass);
		if(!bRet)
		{
			delete pClass;
			pClass=NULL;
		}		
	}

	return (JavaClass*)pClass;
}

BOOL ClassHeap::LoadClass(CString strClassName, JavaClass *pClass)
{
	CString path, relPath;
	if(!pClass) return FALSE;
	relPath=strClassName+_T(".class");
	if(!pFilePathManager->GetAbsolutePath(relPath, path))
		return FALSE;	

	BOOL bRet=pClass->LoadClassFromFile(path);

	if(!bRet) return FALSE;

	pClass->SetClassHeap(this);

	return AddClass(pClass);
}
