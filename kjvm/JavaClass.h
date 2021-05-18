#pragma once
#include <iostream>
#include <string>

#include "types.h"
#include "constants.h"
#include <vector>

class ClassHeap;
class ObjectHeap;

struct cp_info
{
	u1 tag;
    u1* info;
};

struct CONSTANT_Class_info {
 	u1 tag;
   	u2 name_index;
};

struct CONSTANT_Fieldref_info {
    	u1 tag;
    	u2 class_index;
    	u2 name_and_type_index;
};


struct CONSTANT_Methodref_info {
    	u1 tag;
    	u2 class_index;
    	u2 name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info {
    	u1 tag;
    	u2 class_index;
    	u2 name_and_type_index;
};

struct CONSTANT_string_info {
    	u1 tag;
    	u2 string_index;
    };

struct CONSTANT_Integer_info {
    	u1 tag;
    	u4 bytes;
    };
struct CONSTANT_Float_info {
    	u1 tag;
    	u4 bytes;
    };

struct CONSTANT_Long_info {
    	u1 tag;
    	u4 high_bytes;
    	u4 low_bytes;
    };
struct CONSTANT_Double_info {
    	u1 tag;
    	u4 high_bytes;
    	u4 low_bytes;
    };
struct CONSTANT_NameAndType_info {
    	u1 tag;
    	u2 name_index;
    	u2 descriptor_index;
    };

struct CONSTANT_Utf8_info {
    	u1 tag;
    	u2 length;
    	u1* bytes;//[length];
    };



struct attribute_info
{
	u2 attribute_name_index;
    u4 attribute_length;
    u1* info;//[attribute_length];
};

struct field_info
{
	u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info* attributes;//[attributes_count];
};

struct field_info_ex: public field_info
{
	field_info *pFieldInfoBase;
};
struct method_info
{
	u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info* attributes;//[attributes_count];
};


struct ConstantValue_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 constantvalue_index;
};
struct Exception_table
{
	u2 start_pc;
	u2 end_pc;
    u2  handler_pc;
    u2  catch_type;
};

struct Code_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	u1* code;//[code_length];
	u2 exception_table_length;
	Exception_table* exception_table;//[exception_table_length];
	u2 attributes_count;
	attribute_info* attributes;//[attributes_count];
};

struct method_info_ex: method_info
{
	method_info *pMethodInfoBase;
	Code_attribute *pCode_attr;
};


struct JavaClassFileFormat
{
	u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info **constant_pool;//[constant_pool_count-1];
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2* interfaces;//[interfaces_count];
    u2 fields_count;
    field_info_ex *fields;//[fields_count];
    u2 methods_count;
    method_info_ex* methods;//[methods_count];
    u2 attributes_count;
    attribute_info** attributes;//[attributes_count];
};

class JavaClass: public JavaClassFileFormat
{
public:
	JavaClass(void);
	virtual ~JavaClass(void);

public:
	virtual bool LoadClassFromFile(std::string lpszFilePath);
	void SetByteCode(void* pByteCode);

	bool ParseClass(void);
	bool ParseInterfaces(char* &p);
	bool ParseFields(char* &p);
	bool ParseMethods(char* &p);
	bool ParseAttributes(char* &p);
	bool GetConstantPool(u2 nIndex, cp_info& const_pool);

	bool GetStringFromConstPool(int nIndex,std::string& strValue);
	std::string GetName(void);
	std::string GetSuperClassName(void);
	bool ParseMethodCodeAttribute(int nMethodIndex, Code_attribute* pCode_attr);
	int GetMethodIndex(std::string strMethodName, std::string strMethodDesc,JavaClass* &pClass);
	int GetFieldIndex(std::string strName, std::string& strDesc);
	void SetClassHeap(ClassHeap *pClassHeap){this->m_pClassHeap=pClassHeap;}
	virtual u4 GetObjectSize(void);
	virtual u4 GetObjectFieldCount(void);
	JavaClass* GetSuperClass(void);
	bool CreateObject(u2 index, ObjectHeap *pObjectHeap, Object& object);
	bool CreateObjectArray(u2 index, u4 count, ObjectHeap *pObjectHeap, Object& object);
private:
	size_t m_nByteCodeLength;
	void *m_pByteCode;
	std::vector<unsigned char> byteCode_;
	u2	m_nObjectFieldsCount;
	bool ParseConstantPool(char* &p);
	int GetConstantPoolSize(char* p);
	ClassHeap *m_pClassHeap;
};

class Utf8String: private CONSTANT_Utf8_info
{
public:
	Utf8String();
	~Utf8String();

private:	
};