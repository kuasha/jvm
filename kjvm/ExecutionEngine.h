#pragma once
#include "types.h"
class ClassHeap;
class ObjectHeap;
class ExecutionEngine
{
public:
	ExecutionEngine(void);
public:
	virtual ~ExecutionEngine(void);
public:
	virtual u4 Execute(Frame* pFrameStack);
public:
	void ExecuteInvokeSpecial(Frame* pFrameStack);
public:
	Variable LoadConstant(JavaClass *pClass, u1 nIndex);

	ClassHeap *pClassHeap;
	ObjectHeap *pObjectHeap;

public:
	Variable CreateObject(JavaClass *pClass);
public:
	void PutField(Frame* pFrameStack);
public:
	void GetField(Frame* pFrame);
public:
	void ExecuteInvokeVirtual(Frame* pFrameStack, u2 type);
public:
	u2 GetMethodParametersCount(CString strMethodDesc);
	u2 GetMethodParametersStackCount(CString strMethodDesc);

public:
	u4 ExecuteNativeMethod(Frame* pFrameStack);
	int ExecuteNew(Frame* pFrame);
public:
	int ExecuteNewArray(Frame* pFrame);
	int ExecuteANewArray(Frame* pFrame);
public:
	Variable* CreateNewArray(u1 type, i4 count);
public:
	void DumpObject(Object object);
};
