#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "JavaClass.h"
#include "ClassHeap.h"
#include "ObjectHeap.h"

JavaClass::JavaClass(void) : m_pClassHeap(NULL),
							 m_pByteCode(NULL),
							 m_nByteCodeLength(0),
							 m_nObjectFieldsCount(0)
{
}

JavaClass::~JavaClass(void)
{
	// TODO: delete constant_pool, fields, methods and attributes etc.
	//if(methods) delete[] methods;
	//if(fields) delete[] fields;
}

bool JavaClass::LoadClassFromFile(std::string lpszFilePath)
{
	size_t lenRead, len;

	std::ifstream file(lpszFilePath.c_str(), std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	byteCode_.reserve(size + 1);
	if (file.read((char *)byteCode_.data(), size))
	{
		m_nByteCodeLength = size;
		u1 *p = &byteCode_[0];
		SetByteCode(p);
		return true;
	}
	else
	{
		return false;
	}
}

void JavaClass::SetByteCode(void *pByteCode)
{
	m_pByteCode = pByteCode;

	if (m_pByteCode)
		ParseClass();
}

bool JavaClass::ParseClass(void)
{
	//just to be safe
	if (m_pByteCode == NULL || m_nByteCodeLength < sizeof(JavaClassFileFormat) + 20)
		return false;

	char *p = (char *)m_pByteCode;

	magic = getu4(p);
	p += 4;

	assert(magic == 0xCAFEBABE);

	minor_version = getu2(p);
	p += 2;
	major_version = getu2(p);
	p += 2;
	constant_pool_count = getu2(p);
	p += 2;

	if (constant_pool_count > 0)
		ParseConstantPool(p);

	access_flags = getu2(p);
	p += 2;
	this_class = getu2(p);
	p += 2;
	super_class = getu2(p);
	p += 2;
	interfaces_count = getu2(p);
	p += 2;

	if (interfaces_count > 0)
		ParseInterfaces(p);

	fields_count = getu2(p);
	p += 2;

	if (fields_count > 0)
		ParseFields(p);

	methods_count = getu2(p);
	p += 2;

	//printf("Methods count = %d\n", methods_count);

	if (methods_count > 0)
	{
		ParseMethods(p);
	}

	attributes_count = getu2(p);
	p += 2;

	//printf("Class attributes_count = %d\n", attributes_count);

	if (attributes_count > 0)
	{
		ParseAttributes(p);
	}

	return 0;
}

bool JavaClass::ParseAttributes(char *&p)
{
	attributes.reserve(attributes_count);

	for (int i = 0; i < attributes_count; i++)
	{
		attributes[i] = (attribute_info *)p;
		u2 name_index = getu2(p);		
		p += 2; //attribute_name_index
		u4 len = getu4(p);
		p += 4; //len
		p += len;
		//attributes[i]->info = (u1*)p;
	}

	ParseClassBootstrapMethodsAttribute();
	ParseInnerClasses();
	
	return true;
}

bool JavaClass::ParseClassBootstrapMethodsAttribute()
{
	for (int i = 0; i < attributes_count; i++)
	{
		char *p = (char *) attributes[i];		
		u2 name_index = getu2(p);
		p += 2; //attribute_name_index
		u4 len = getu4(p);
		p += 4; //len

		std::string strAttributeName;
		GetStringFromConstPool(name_index, strAttributeName);		
		if (!strAttributeName.compare("BootstrapMethods"))
		{			
			std::cout << "Found BootstrapMethods" << std::endl;
			pBootstrapMethods_attribute_ = new BootstrapMethods_attribute();

			pBootstrapMethods_attribute_->attribute_name_index = name_index;
			pBootstrapMethods_attribute_->attribute_length = len;
			u2 num_bootstrap_methods = getu2(p);
			p += 2;
			pBootstrapMethods_attribute_->num_bootstrap_methods = num_bootstrap_methods;

			std::cout << "num_bootstrap_methods " << num_bootstrap_methods << std::endl;
			pBootstrapMethods_attribute_->bootstrap_methods_.reserve(num_bootstrap_methods);

			for(int m=0; m<num_bootstrap_methods; m++) 
			{
				auto method = new bootstrap_methods;
				method->bootstrap_method_ref = getu2(p);
				p+=2;
				method->num_bootstrap_arguments = getu2(p);
				p+=2;

				for(int a=0; a < method->num_bootstrap_arguments; a++) 
				{
					u2 argi = getu2(p);
					p+=2;
					method->bootstrap_arguments.push_back(argi);
				}

				pBootstrapMethods_attribute_->bootstrap_methods_[m] = method;
				std::cout << "bootstrap method ref = " << method->bootstrap_method_ref << std::endl;				
			}
			return true;
		}
	}

	//not found
	pBootstrapMethods_attribute_ = nullptr;
	return false;
}

bool JavaClass::ParseInnerClasses()
{
	return false;
}

//TODO: Cache the findings here
bool JavaClass::ParseMethods(char *&p)
{
	methods.reserve(methods_count);

	for (int i = 0; i < methods_count; i++)
	{
		//methods[i] = new method_info_ex;
		methods[i].pMethodInfoBase = (method_info *)p;
		methods[i].access_flags = getu2(p);
		p += 2; //access_flags
		methods[i].name_index = getu2(p);
		p += 2; //name_index
		methods[i].descriptor_index = getu2(p);
		p += 2; //descriptor_index
		methods[i].attributes_count = getu2(p);
		p += 2;

		std::string strName, strDesc;
		GetStringFromConstPool(methods[i].name_index, strName);
		GetStringFromConstPool(methods[i].descriptor_index, strDesc);

		//wprintf(_T("Method = %s%s\n"),strName, strDesc);

		//printf("Method has total %d attributes\n",methods[i].attributes_count);

		methods[i].pCode_attr = NULL;
		if (methods[i].attributes_count > 0)
		{
			//skip attributes
			for (int a = 0; a < methods[i].attributes_count; a++)
			{
				u2 name_index = getu2(p);
				p += 2;

				//printf("Attribute name index = %d\n", name_index);
				u4 len = getu4(p);
				p += 4;
				p += len;
			}

			methods[i].pCode_attr = new Code_attribute;
			ParseMethodCodeAttribute(i, methods[i].pCode_attr);
		}
	}

	return true;
}

bool JavaClass::ParseConstantPool(char *&p)
{
	constant_pool.resize(constant_pool_count);

	for (int i = 1; i < constant_pool_count; i++)
	{
		constant_pool[i] = (cp_info *)p;

		int size = GetConstantPoolSize(p);
		p += size;

		//printf("Constant pool %d type %d\n",i,(u1)constant_pool[i]->tag);

		if (constant_pool[i]->tag == CONSTANT_Long || constant_pool[i]->tag == CONSTANT_Double)
		{
			constant_pool[i + 1] = NULL;
			i++;
		}
	}

	return true;
}

bool JavaClass::ParseFields(char *&p)
{
	fields.reserve(fields_count);

	for (int i = 0; i < fields_count; i++)
	{
		fields[i].pFieldInfoBase = (field_info *)p;

		fields[i].access_flags = getu2(p);
		p += 2; //access_flags
		fields[i].name_index = getu2(p);
		p += 2; //
		fields[i].descriptor_index = getu2(p);
		p += 2; //
		fields[i].attributes_count = getu2(p);
		p += 2;

		//printf("Field %d has total %d attributes\n",i, fields[i].attributes_count);
		if (fields[i].attributes_count > 0)
		{
			//skip attributes
			for (int a = 0; a < fields[i].attributes_count; a++)
			{
				u2 name_index = getu2(p);
				p += 2;
				//printf("Attribute name index = %d\n", name_index);
				u4 len = getu4(p);
				p += 4;
				p += len;
			}
		}
	}

	return true;
}

bool JavaClass::ParseInterfaces(char *&p)
{
	interfaces.reserve(interfaces_count);

	for (int i = 0; i < interfaces_count; i++)
	{
		interfaces[i] = getu2(p);
		p += 2;
		//printf("Interface at %d\n",interfaces[i]);
	}

	return true;
}

int JavaClass::GetConstantPoolSize(char *p)
{
	cp_info *cp = (cp_info *)p;
	u2 len;
	u1 a, b;
	char *op;

	switch (cp->tag)
	{
	case CONSTANT_Class:
		return 3;
	case CONSTANT_Fieldref:
		return 5;
	case CONSTANT_Methodref:
		return 5;
	case CONSTANT_InterfaceMethodref:
		return 5;
	case CONSTANT_String:
		return 3;
	case CONSTANT_Integer:
		return 5;
	case CONSTANT_Float:
		return 5;
	case CONSTANT_Long:
		return 9;
	case CONSTANT_Double:
		return 9;
	case CONSTANT_NameAndType:
		return 5;
	case CONSTANT_Utf8:
		op = p + 1;
		a = op[0];
		b = op[1];
		len = (u2)(a << 8 & 0x0000FF00 | b);
		return 3 + len;
	case CONSTANT_MethodHandle:
		return 4;
	case CONSTANT_MethodType:
		return 3;
	case CONSTANT_InvokeDynamic:
		return 5;
	default:
		assert(false);
		break;
	}

	return 0;
}

bool JavaClass::GetConstantPool(u2 nIndex, cp_info &const_pool)
{
	if (nIndex > constant_pool_count - 1)
		return false;

	char *cpool = (char *)constant_pool[nIndex];

	//int nLen=GetConstantPoolSize(cpool);

	const_pool.tag = cpool[0];
	cpool++;
	if (CONSTANT_Utf8 == const_pool.tag)
	{
		int len = getu2(cpool);
		cpool += 2;
		const_pool.info = new u1[len + 1];
		memset(const_pool.info, 0, len + 1);
		memcpy(const_pool.info, cpool, len);
	}
	if (CONSTANT_Class == const_pool.tag)
	{
		const_pool.info = new u1[2];
		memcpy(const_pool.info, cpool, 2);
	}

	return 0;
}

bool JavaClass::GetStringFromConstPool(int nIndex, std::string &strValue)
{

	if (nIndex < 1 || nIndex >= constant_pool_count)
	{
		return false;
	}

	if (constant_pool[nIndex]->tag != CONSTANT_Utf8)
	{
		assert(false);
		return false;
	}

	u1 *p = (u1 *)constant_pool[nIndex];

	short length = getu2(&p[1]);
	strValue.append((char *)&p[3], length);
	return true;
}

std::string JavaClass::GetName(void)
{
	std::string retVal = "";
	if (constant_pool[this_class]->tag != CONSTANT_Class)
		return retVal;
	char *bc = (char *)constant_pool[this_class];
	u2 name_index = getu2(&bc[1]);
	GetStringFromConstPool(name_index, retVal);
	return retVal;
}

std::string JavaClass::GetSuperClassName(void)
{
	std::string retVal = "";
	if (super_class < 1)
		return retVal;

	if (constant_pool[super_class]->tag != CONSTANT_Class)
		return retVal;
	char *bc = (char *)constant_pool[super_class];
	u2 name_index = getu2(&bc[1]);
	GetStringFromConstPool(name_index, retVal);
	return retVal;
}

bool JavaClass::ParseMethodCodeAttribute(int nMethodIndex, Code_attribute *pCode_attr)
{
	if (nMethodIndex > methods_count)
	{
		return false;
	}

	char *pMi, *bc;
	pMi = bc = (char *)methods[nMethodIndex].pMethodInfoBase;
	bc += 6;
	int nAttributes = getu2(bc);
	bc += 2;

	if (nAttributes > 0)
	{
		//skip attributes
		for (int a = 0; a < nAttributes; a++)
		{
			u2 name_index = getu2(bc);
			bc += 2;
			std::string strAttributeName;
			GetStringFromConstPool(name_index, strAttributeName);
			// may be we can compare indexe directly??
			if (!strAttributeName.compare("Code"))
			{
				char *ca = bc;
				pCode_attr->attribute_name_index = name_index; //already scanned;
				pCode_attr->attribute_length = getu4(ca);
				ca += 4;
				pCode_attr->max_stack = getu2(ca);
				ca += 2;
				pCode_attr->max_locals = getu2(ca);
				ca += 2;
				pCode_attr->code_length = getu4(ca);
				ca += 4;
				if (pCode_attr->code_length > 0)
				{
					pCode_attr->code = new u1[pCode_attr->code_length];
					memcpy(pCode_attr->code, ca, pCode_attr->code_length);

					/*
					printf("\nCODE\n");
					for(u4 i=0;i<pCode_attr->code_length;i++)
						printf("%d ", pCode_attr->code[i]);
					printf("\nENDCODE\n");
					*/
				}
				else
				{
					// may be native code ??
					pCode_attr->code = NULL;
				}
				ca += pCode_attr->code_length;
				pCode_attr->exception_table_length = getu2(ca);
				ca += 2;

				if (pCode_attr->exception_table_length > 0)
				{
					pCode_attr->exception_table = new Exception_table[pCode_attr->exception_table_length];
					for (int ext = 0; ext < pCode_attr->exception_table_length; ext++)
					{
						pCode_attr->exception_table[ext].start_pc = getu2(ca);
						ca += 2;
						pCode_attr->exception_table[ext].end_pc = getu2(ca);
						ca += 2;
						pCode_attr->exception_table[ext].handler_pc = getu2(ca);
						ca += 2;
						pCode_attr->exception_table[ext].catch_type = getu2(ca);
						ca += 2;
					}
				}
			}

			u4 len = getu4(bc);
			bc += 4;
			bc += len;
		}
	}

	return 0;
}

int JavaClass::GetMethodIndex(std::string strMethodName, std::string strMethodDesc, JavaClass *&pClass)
{
	JavaClass *pCurClass = this;
	while (pCurClass)
	{
		//_tprintf(_T("Searching class %s\n"), pCurClass->GetName());
		for (int i = 0; i < pCurClass->methods_count; i++)
		{
			std::string name, desc;

			pCurClass->GetStringFromConstPool(pCurClass->methods[i].name_index, name);
			if (name.compare(strMethodName))
				continue;

			pCurClass->GetStringFromConstPool(pCurClass->methods[i].descriptor_index, desc);

			if (!desc.compare(strMethodDesc))
			{
				if (pClass)
					pClass = pCurClass;

				return i;
			}
		}

		if (pClass != NULL)
		{
			pCurClass = pCurClass->GetSuperClass();
		}
		else
		{
			break;
		}
	}

	return -1;
}

int JavaClass::GetFieldIndex(std::string strName, std::string &strDesc)
{
	for (int i = 0; i < fields_count; i++)
	{
		std::string name, desc;
		GetStringFromConstPool(fields[i].name_index, name);
		if (name.compare(strName))
			continue;

		GetStringFromConstPool(fields[i].descriptor_index, desc);

		strDesc = desc;
		return i;
	}

	return -1;
}

u4 JavaClass::GetObjectSize(void)
{
	u4 size = fields_count * sizeof(Variable);
	std::string superClass = GetSuperClassName();
	JavaClass *pSuperClass = m_pClassHeap->GetClass(superClass);
	u4 superObjSize = 0;
	if (pSuperClass)
		superObjSize = pSuperClass->GetObjectSize();

	size += superObjSize;
	return size;
}

u4 JavaClass::GetObjectFieldCount(void)
{
	u4 count = fields_count;
	std::string superClass = GetSuperClassName();
	u4 superObjFieldCount = 0;

	if (superClass.length() < 1)
	{
		// This is probaly java/lang/Object class
	}
	else
	{
		JavaClass *pSuperClass = m_pClassHeap->GetClass(superClass);
		if (pSuperClass)
		{
			superObjFieldCount = pSuperClass->GetObjectFieldCount();
		}
	}

	count += superObjFieldCount;
	return count;
}

JavaClass *JavaClass::GetSuperClass(void)
{
	std::string superClass = GetSuperClassName();
	JavaClass *pSuperClass = m_pClassHeap->GetClass(superClass);

	return pSuperClass;
}

bool JavaClass::CreateObject(u2 index, ObjectHeap *pObjectHeap, Object &object)
{
	char *cp = (char *)this->constant_pool[index];
	assert(cp[0] == CONSTANT_Class);
	assert(pObjectHeap);
	if (cp[0] != CONSTANT_Class)
		return false;

	u2 name_index = getu2(&cp[1]);
	std::string strClassName;
	if (!this->GetStringFromConstPool(name_index, strClassName))
		return false;

	printf("Creating new object of class [%ws]\n", strClassName);

	JavaClass *pNewClass = this->m_pClassHeap->GetClass(strClassName);
	if (pNewClass == NULL)
		return false;
	object = pObjectHeap->CreateObject(pNewClass);
	return true;
}

bool JavaClass::CreateObjectArray(u2 index, u4 count, ObjectHeap *pObjectHeap, Object &object)
{
	char *cp = (char *)this->constant_pool[index];
	assert(cp[0] == CONSTANT_Class);
	assert(pObjectHeap);
	if (cp[0] != CONSTANT_Class)
		return false;

	u2 name_index = getu2(&cp[1]);
	std::string strClassName;
	if (!this->GetStringFromConstPool(name_index, strClassName))
		return false;
	JavaClass *pNewClass = this->m_pClassHeap->GetClass(strClassName);
	if (pNewClass == NULL)
		return false;

	return pObjectHeap->CreateObjectArray(pNewClass, count, object);
}
