#pragma once
#include "types.h"
#include "ClassHeap.h"

class ObjectHeap
{
public:
	ObjectHeap(void);
public:
	virtual ~ObjectHeap(void);
public:
	virtual Variable* GetObjectPointer(Object object);
	Object CreateObject(JavaClass* pClass);
	Object CreateStringObject(std::string* pStrValue, ClassHeap *pClassHeap);
	Object CreateNewArray(u1 type, i4 count);
	bool CreateObjectArray(JavaClass* pClass, u4 count, Object& object);
private:
	std::map<void*, void*> m_ObjectMap;
	u4 m_nNextObjectID;

};
