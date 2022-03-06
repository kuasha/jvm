#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "kjvm.h"
#include "JavaClass.h"
#include "ClassHeap.h"
#include "types.h"
#include "constants.h"
#include "ExecutionEngine.h"
#include "ObjectHeap.h"

void ShowClassInfo(JavaClass *pClass)
{
	if (!pClass)
		return;

	std::string name = pClass->GetName();
	printf("Class Name = [%s]\n", name.c_str());
	name = pClass->GetSuperClassName();
	printf("Super Class Name = [%s]\n", name.c_str());

	printf("Object Size = [%lu]\n", pClass->GetObjectSize());

	for (int i = 1; i < pClass->constant_pool_count - 1; i++)
	{
		std::string strRetVal;
		printf("Pool %d Type = %d ", i, pClass->constant_pool[i]->tag);
		if (1 != pClass->constant_pool[i]->tag)
			continue;
		pClass->GetStringFromConstPool(i, strRetVal);
		printf("String at %d [%s]\n", i, strRetVal.c_str());
	}

	for (int i = 0; i < pClass->methods_count; i++)
	{
	    std::cout << "Method " << i << ":" << std::endl;
	    std::cout << "Access flags: " << pClass->methods[i].access_flags << std::endl;
		if (pClass->methods[i].pCode_attr != NULL)
		{
			printf("ode Length= %d\n", pClass->methods[i].pCode_attr->code_length);
			printf("Max stack = %d, Max Locals = %d, Exception table length= %d\nCODE\n", pClass->methods[i].pCode_attr->max_stack, pClass->methods[i].pCode_attr->max_locals, pClass->methods[i].pCode_attr->exception_table_length);

			for (u4 j = 0; j < pClass->methods[i].pCode_attr->code_length; j++)
				printf("%d ", pClass->methods[i].pCode_attr->code[j]);
			printf("\nENDCODE\n");
		}
		else if (pClass->methods[i].access_flags && ACC_NATIVE)
		{
			printf("Method %d is native\n", i);
		}
	}

	for (int i = 0; i < pClass->fields_count; i++)
	{
		std::string name, desc;

		pClass->GetStringFromConstPool(pClass->fields[i].name_index, name);
		pClass->GetStringFromConstPool(pClass->fields[i].descriptor_index, desc);
		printf("Filed %d: Name: %s Type: %s\n", i, name, desc);
	}

	for (int i = 0; i < pClass->interfaces_count; i++)
	{
		u2 intr = pClass->interfaces[i];
		std::string name;
		cp_info *pi = pClass->constant_pool[intr];
		assert(pi->tag == CONSTANT_Class);
		char *p = (char *)pi;
		int ni = getu2((char *)(&p[1]));
		pClass->GetStringFromConstPool(ni, name);

		printf("Interface %d: Name %s\n", i, name);
	}
}
