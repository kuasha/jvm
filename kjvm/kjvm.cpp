// kjvm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "kjvm.h"
#include "JavaClass.h"
#include "ClassHeap.h"
#include "types.h"
#include "constants.h"
#include "ExecutionEngine.h"
#include "ObjectHeap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp theApp;

using namespace std;

JavaClass* LoadClass(LPTSTR strClassPath)
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

void Execute(CString strClass)
{
	CString path=strClass;
	ClassHeap heap;
	JavaClass *pClass1, *pClass2, *pClass3;
	pClass1 = new JavaClass();
	pClass2 = new JavaClass();

	BOOL bRet=heap.LoadClass(strClass, pClass1);
	bRet=heap.LoadClass(_T("java/lang/Object"), pClass2);

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
	int mindex=pClass1->GetMethodIndex(_T("Entry"),_T("()I"),pVirtualClass);
	pFrameStack[startFrame].pClass = pVirtualClass;	

	pFrameStack[startFrame].pMethod = &pVirtualClass->methods[mindex];
	pFrameStack[startFrame].stack = Frame::pOpStack;
	pFrameStack[startFrame].sp = pFrameStack[startFrame].pMethod->pCode_attr->max_locals;
	pFrameStack[startFrame].stack[0].object = object;
	ex.Execute(&pFrameStack[startFrame]);

}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	if(argc<2) return -1;

	Execute(argv[1]); 
	
	return nRetCode;
}

void Test2()
{
	CString path=_T("Test");

	CString path2=_T("java\\lang\\Object");

	ClassHeap heap;
	JavaClass *pClass1, *pClass2, *pClass3;
	pClass1 = new JavaClass();
	pClass2 = new JavaClass();

	BOOL bRet=heap.LoadClass(path, pClass1);
	bRet=heap.LoadClass(path2, pClass2);

	pClass3=heap.GetClass(CString("Test"));

	for(int i=0;pClass3&& i< pClass3->interfaces_count; i++)
	{
		u2 intr=pClass3->interfaces[i];
		CString name;
		cp_info *pi=pClass3->constant_pool[intr];
		ASSERT(pi->tag == CONSTANT_Class);
		char *p=(char *)pi;
		int ni=getu2((char *)(&p[1]));
		pClass3->GetStringFromConstPool(ni, name);

		wprintf(_T("Loading Interface %s\n"), name);
		JavaClass *pClass4 = new JavaClass();
		bRet=heap.LoadClass(name.GetBuffer(), pClass4);

		if(bRet)ShowClassInfo(pClass4);
	}
}

void ShowClassInfo(JavaClass* pClass)
{
	if(!pClass) return;

	CString name= pClass->GetName();
	wprintf(_T("Class Name = [%s]\n"),name);
	name= pClass->GetSuperClassName();
	wprintf(_T("Super Class Name = [%s]\n"),name);

	wprintf(_T("Object Size = [%lu]\n"), pClass->GetObjectSize());
	
	for(int i=1;i<pClass->constant_pool_count-1;i++)
	{		
		CString strRetVal;
		wprintf(_T("Pool %d Type = %d "), i,pClass->constant_pool[i]->tag); 
		if(1!=pClass->constant_pool[i]->tag)
			continue;
		pClass->GetStringFromConstPool(i, strRetVal);	
		wprintf(_T("String at %d [%s]\n"),i, strRetVal);
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
		CString name, desc;

		pClass->GetStringFromConstPool(pClass->fields[i].name_index, name);
		pClass->GetStringFromConstPool(pClass->fields[i].descriptor_index, desc);
		wprintf(_T("Filed %d: Name: %s Type: %s\n"),i, name, desc);
	}

	for(int i=0; i< pClass->interfaces_count; i++)
	{
		u2 intr=pClass->interfaces[i];
		CString name;
		cp_info *pi=pClass->constant_pool[intr];
		ASSERT(pi->tag == CONSTANT_Class);
		char *p=(char *)pi;
		int ni=getu2((char *)(&p[1]));
		pClass->GetStringFromConstPool(ni, name);

		wprintf(_T("Interface %d: Name %s\n"),i, name);

	}
}

