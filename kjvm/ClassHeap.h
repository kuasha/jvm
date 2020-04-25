#pragma once
class JavaClass;
class FilePathManager;

class ClassHeap
{
	CMapStringToPtr m_ClassMap;
	FilePathManager *pFilePathManager;
public:
	ClassHeap(void);
public:
	virtual ~ClassHeap(void);
public:
	BOOL AddClass(JavaClass* pJavaClass);
	JavaClass* GetClass(CString strClassName);
	BOOL LoadClass(CString strClassName, JavaClass *pClass);


};
