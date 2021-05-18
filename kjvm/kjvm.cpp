// kjvm.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <string.h>

#include "stdafx.h"
#include "kjvm.h"
#include "JavaClass.h"
#include "ClassHeap.h"
#include "types.h"
#include "constants.h"
#include "ExecutionEngine.h"
#include "ObjectHeap.h"

JavaClass* LoadClass(std::string strClassPath)
{	
	JavaClass *pClass= new JavaClass();
	if(!pClass->LoadClassFromFile(strClassPath))
	{
		delete pClass;
		pClass=NULL;
	}

	return pClass;
}

void ShowClassInfo(JavaClass* pClass);

int Execute(std::string strClass)
{
	std::string path=strClass;
	ClassHeap heap;
	JavaClass *pClass1, *pClass2, *pClass3;
	pClass1 = new JavaClass();
	pClass2 = new JavaClass();

	heap.AddClassRoot("/home/boltu/workspaces/jvm/kjvm/lib");
	bool bRet=heap.LoadClass(strClass, pClass1);
	bRet=heap.LoadClass("java/lang/Object", pClass2);

	ObjectHeap oheap;

	Frame *pFrameStack = new Frame[20];
	Frame::pBaseFrame = pFrameStack;

	memset(pFrameStack, 0, sizeof(Frame)*20);

	Frame::pOpStack = new Variable[100];
	memset(Frame::pOpStack, 0, sizeof(Variable)*100);

	ExecutionEngine ex;
	ex.pClassHeap = &heap;
	ex.pObjectHeap = &oheap;
	int startFrame=0;

	Object object=oheap.CreateObject(pClass1);
	JavaClass *pVirtualClass=pClass1;
	int mindex=pClass1->GetMethodIndex("Entry","()I",pVirtualClass);
	pFrameStack[startFrame].pClass = pVirtualClass;	

	pFrameStack[startFrame].pMethod = &pVirtualClass->methods[mindex];
	pFrameStack[startFrame].stack = Frame::pOpStack;
	pFrameStack[startFrame].sp = pFrameStack[startFrame].pMethod->pCode_attr->max_locals;
	pFrameStack[startFrame].stack[0].object = object;
	ex.Execute(&pFrameStack[startFrame]);

	return 0;
}

int main (int argc, char *argv[])
{
	if(argc<2) 
	{
		return -1;
	}

	return Execute(argv[1]);
}

void Test2()
{
	std::string path="Test";
	std::string path2="java\\lang\\Object";

	ClassHeap heap;	
	JavaClass *pClass1, *pClass2, *pClass3;
	pClass1 = new JavaClass();
	pClass2 = new JavaClass();

	bool bRet=heap.LoadClass(path, pClass1);
	bRet=heap.LoadClass(path2, pClass2);

	pClass3=heap.GetClass("Test");

	for(int i=0;pClass3&& i< pClass3->interfaces_count; i++)
	{
		u2 intr=pClass3->interfaces[i];
		std::string name;
		cp_info *pi=pClass3->constant_pool[intr];
		//ASSERT(pi->tag == CONSTANT_Class);
		char *p=(char *)pi;
		int ni=getu2((char *)(&p[1]));
		pClass3->GetStringFromConstPool(ni, name);

		printf("Loading Interface %s\n", name);
		JavaClass *pClass4 = new JavaClass();
		bRet=heap.LoadClass(name.c_str(), pClass4);

		if(bRet)ShowClassInfo(pClass4);
	}
}

void ShowClassInfo(JavaClass* pClass)
{
	if(!pClass) return;

	std::string name= pClass->GetName();
	printf("Class Name = [%s]\n",name);
	name= pClass->GetSuperClassName();
	printf("Super Class Name = [%s]\n",name);

	printf("Object Size = [%lu]\n", pClass->GetObjectSize());
	
	for(int i=1;i<pClass->constant_pool_count-1;i++)
	{		
		std::string strRetVal;
		printf("Pool %d Type = %d ", i,pClass->constant_pool[i]->tag); 
		if(1!=pClass->constant_pool[i]->tag)
			continue;
		pClass->GetStringFromConstPool(i, strRetVal);	
		printf("String at %d [%s]\n",i, strRetVal);
	}
	
	for(int i=0;i<pClass->methods_count;i++)
	{
		if(pClass->methods[i].pCode_attr != NULL)
		{
			printf("Method %d\nCode Length= %d\n", i,pClass->methods[i].pCode_attr->code_length);
			printf("Max stack = %d, Max Locals = %d, Exception table length= %d\nCODE\n",pClass->methods[i].pCode_attr->max_stack, pClass->methods[i].pCode_attr->max_locals, pClass->methods[i].pCode_attr->exception_table_length);		

			for(u4 j=0;j<pClass->methods[i].pCode_attr->code_length;j++)
				printf("%d ", pClass->methods[i].pCode_attr->code[j]);
			printf("\nENDCODE\n");
		}
		else if(pClass->methods[i].access_flags && ACC_NATIVE)
		{
			printf("Method %d is native\n",i);
		}
	}

	for(int i=0; i< pClass->fields_count; i++)
	{
		std::string name, desc;

		pClass->GetStringFromConstPool(pClass->fields[i].name_index, name);
		pClass->GetStringFromConstPool(pClass->fields[i].descriptor_index, desc);
		printf("Filed %d: Name: %s Type: %s\n",i, name, desc);
	}

	for(int i=0; i< pClass->interfaces_count; i++)
	{
		u2 intr=pClass->interfaces[i];
		std::string name;
		cp_info *pi=pClass->constant_pool[intr];
		//ASSERT(pi->tag == CONSTANT_Class);
		char *p=(char *)pi;
		int ni=getu2((char *)(&p[1]));
		pClass->GetStringFromConstPool(ni, name);

		printf("Interface %d: Name %s\n",i, name);

	}
}

