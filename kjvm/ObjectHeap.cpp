#include "ObjectHeap.h"
#include "types.h"
#include "ClassHeap.h"
#include "JavaClass.h"
#include <string.h>

ObjectHeap::ObjectHeap(void)
:m_nNextObjectID(1)
{
}

ObjectHeap::~ObjectHeap(void)
{
}

Object ObjectHeap::CreateObject(JavaClass* pClass)
{
	Object object;	
	object.heapPtr=NULL;
	object.type=0;

	if(pClass == NULL) return object;
	u4 osize= pClass->GetObjectFieldCount()+1; //+1 for class pointer
	Variable *obj = new Variable[osize];
	if(!obj) return object;
	memset(obj, 0, sizeof(Variable)*osize);
	object.heapPtr=(void *)m_nNextObjectID++;
	obj[0].ptrValue =(void*) pClass;

	m_ObjectMap[(void *)object.heapPtr]=obj;

	return object;
}

Object ObjectHeap::CreateStringObject(std::string* pStrValue, ClassHeap *pClassHeap)
{
	Object object;	
	object.heapPtr=NULL;
	object.type=0;

	if(pClassHeap == NULL) return object;
	JavaClass *pClass=pClassHeap->GetClass("java/lang/String");

	if(pClass == NULL) return object;	

	object = CreateObject(pClass);
	Variable *pVar= this->GetObjectPointer(object);
	if(pVar==NULL) return object;

	pVar[1].ptrValue=(void*)pStrValue;

	return object;
}

bool ObjectHeap::CreateObjectArray(JavaClass* pClass, u4 count, Object& object)
{
	Variable *pVar= new Variable[count+1];

	if(pVar)
	{
		memset(pVar, 0, sizeof(Variable)*(count+1));
		pVar[0].ptrValue = (void*)pClass;
	}
	else
		return false;

	object.heapPtr=(void*)m_nNextObjectID++;
	
	m_ObjectMap[(void *)object.heapPtr]=pVar;

	return true;
}

Variable* ObjectHeap::GetObjectPointer(Object object)
{
	void *obj = NULL;
	auto it = m_ObjectMap.find((void *)object.heapPtr);
	if(it == m_ObjectMap.end())
		return NULL;
	obj=it->second;
	return (Variable*)obj;
}

Object ObjectHeap::CreateNewArray(u1 type, i4 count)
{
	Variable *obj= new Variable[count+1];
	Object object;
	object.heapPtr=0;
	object.type=type;

	if(obj)
	{
		memset(obj, 0, sizeof(Variable)*(count+1));
		object.heapPtr=(void *)m_nNextObjectID++;
		obj[0].intValue = type;

		m_ObjectMap[(void *)object.heapPtr] = obj;
	}

	return object;
}
