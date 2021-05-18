#pragma once
#include <map>

class JavaClass;
class FilePathManager;

class ClassHeap
{
	std::map<std::string, void*> m_ClassMap;
	FilePathManager *pFilePathManager;
public:
	ClassHeap(void);
public:
	virtual ~ClassHeap(void);
public:
	bool AddClass(JavaClass* pJavaClass);
	JavaClass* GetClass(std::string strClassName);
	bool LoadClass(std::string strClassName, JavaClass *pClass);


};
