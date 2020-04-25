#pragma once

class ObjectHeap
{
public:
	ObjectHeap(void);
public:
	virtual ~ObjectHeap(void);
public:
	virtual Variable* GetObjectPointer(Object object);
	Object CreateObject(JavaClass* pClass);
	Object CreateStringObject(CString* pStrValue, ClassHeap *pClassHeap);
	Object CreateNewArray(u1 type, i4 count);
	BOOL CreateObjectArray(JavaClass* pClass, u4 count, Object& object);
private:
	CMapPtrToPtr m_ObjectMap;
	u4 m_nNextObjectID;

};
