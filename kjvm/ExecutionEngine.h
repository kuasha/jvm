#pragma once
#include "types.h"
class ClassHeap;
class ObjectHeap;
class ExecutionEngine
{
public:
	ExecutionEngine(void);
	virtual ~ExecutionEngine(void);
	virtual u4 Execute(Frame* pFrameStack);
	void ExecuteInvokeSpecial(Frame* pFrameStack);
	Variable LoadConstant(JavaClass *pClass, u1 nIndex);

	ClassHeap *pClassHeap;
	ObjectHeap *pObjectHeap;

	Variable CreateObject(JavaClass *pClass);
	void PutField(Frame* pFrameStack);
	void GetField(Frame* pFrame);

	void ExecuteInvokeDynamic(Frame *pFrameStack);
	void ExecuteInvokeVirtual(Frame* pFrameStack, u2 type);

	u2 GetMethodParametersCount(std::string strMethodDesc);
	u2 GetMethodParametersStackCount(std::string strMethodDesc);

	u4 ExecuteNativeMethod(Frame* pFrameStack);
	int ExecuteNew(Frame* pFrame);

	int ExecuteNewArray(Frame* pFrame);
	int ExecuteANewArray(Frame* pFrame);

	Variable* CreateNewArray(u1 type, i4 count);
	void DumpObject(Object object);
};
