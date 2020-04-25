#pragma once

typedef unsigned int u4;
typedef unsigned short u2;
typedef unsigned char u1;

typedef __int64 i8;
typedef unsigned __int64 u8;

typedef int i4;
typedef short i2;

typedef float f4;
typedef double f8;

#define LOINT64(I8) (u4)(I8 &0xFFFFFFFF)
#define HIINT64(I8) (u4)(I8 >> 32)
#define getu4(p) (u4)( (u4)((p)[0])<<24 & 0xFF000000 | (u4)((p)[1])<<16 & 0x00FF0000 | (u4)((p)[2])<<8 & 0x0000FF00| (u4)((p)[3]) & 0x000000FF)
#define getu2(p) (u2)((p)[0]<< 8 & 0x0000FF00 |(p)[1])

#define MAKEI8(i4high, i4low) (i8) (((i8)i4high) << 32 | (i8)i4low)

//getf4 depents on geti4 : carefull when changing...
#define geti4(p) (i4)( (u4)((p)[0])<<24 | (u4)((p)[1])<<16 | (u4)((p)[2])<<8 | (u4)((p)[3]) )
#define geti2(p) (i2)(((p)[0]<<8)|(p)[1])

f4 getf4(char *p);

#define castu4(p) *((u4 *)p)
#define castu2(p) *((u2 *)p)

#define casti4(p) *((i4 *)p)
#define casti2(p) *((i2 *)p)

class JavaClass;
struct method_info_ex;

class Object
{
public:
	LONG_PTR heapPtr;
	u1 type;
};

union Variable
{
	u1 charValue;
	u2 shortValue;
	u4 intValue;
	f4 floatValue;
	LONG_PTR ptrValue;
	Object object;
};

class Frame
{
public:
	static Variable *pOpStack;
	static Frame* pBaseFrame;
	JavaClass *pClass;
	method_info_ex *pMethod;
	u4 pc;
	i2 sp;
	Variable *stack;
	Frame()
	{
		sp=-1;
		pClass=NULL;
		pc=0;
		stack=NULL;
		pBaseFrame=NULL;
		pOpStack=NULL;
	}

	Frame(i2 sp)
	{
		this->sp=sp;
		pClass=NULL;
		pc=0;
		stack=NULL;
	}
};