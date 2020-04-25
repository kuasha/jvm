#pragma once
extern TCHAR* OpcodeDesc[];

#define nop 0
#define aconst_null 1 /*(0x1)*/ 
#define iconst_m1 2 /*(0x2)*/ 
#define iconst_0 3 /*(0x3)*/
#define iconst_1 4 /*(0x4)*/ 
#define iconst_2 5 /*(0x5)*/ 
#define iconst_3 6 /*(0x6)*/ 
#define iconst_4 7 /*(0x7)*/ 
#define iconst_5 8 /*(0x8)*/

#define bipush 16 /*(0x10)*/
#define sipush 17 /*(0x11)*/

#define lconst_0 9 /*(0x9)*/ 
#define lconst_1 10 /*(0xa)*/

#define ldc 18 /* (0x12) */

#define ldc2_w 20 /*(0x14)*/

#define iload 21 /*(0x15)*/

#define lload 22 /*(0x16)*/

#define aload 25 /*(0x19)*/

#define iload_0 26 /*(0x1a)*/ 
#define iload_1 27 /*(0x1b)*/ 
#define iload_2 28 /*(0x1c)*/ 
#define iload_3 29 /*(0x1d)*/

#define lload_0 30 /*(0x1e) */
#define lload_1 31 /*(0x1f) */
#define lload_2 32 /*(0x20) */
#define lload_3 33 /*(0x21) */

#define fload_0 34 /*(0x22)*/ 
#define fload_1 35 /*(0x23) */
#define fload_2 36 /*(0x24) */
#define fload_3 37 /*(0x25)*/

#define aload_0 42 /* (0x2a) */
#define aload_1 43 /*(0x2b) */
#define aload_2 44 /*(0x2c) */
#define aload_3 45 /*(0x2d)*/

#define iaload 46 /*(0x2e)*/

#define aaload 50

#define istore 54 /*(0x36)*/
#define astore 58 /*(0x3a)*/

#define istore_0 59 /*(0x3b)*/ 
#define istore_1 60 /*(0x3c) */
#define istore_2 61 /*(0x3d) */
#define istore_3 62 /*(0x3e)*/

#define lstore_0 63 /*(0x3f) */
#define lstore_1 64 /*(0x40) */
#define lstore_2 65 /*(0x41) */
#define lstore_3 66 /*(0x42) */

#define fstore_0 67 /*(0x43) */
#define fstore_1 68 /*(0x44) */
#define fstore_2 69 /*(0x45) */
#define fstore_3 70 /*(0x46) */

#define astore_0 75 /*(0x4b) */
#define astore_1 76 /*(0x4c) */
#define astore_2 77 /*(0x4d) */
#define astore_3 78 /*(0x4e)*/
#define iastore 79 /*(0x4f)*/

#define aastore 83 /*(0x53)*/

#define dup 89 /*(0x59)*/
#define dup_x1 90 /*(0x5a)*/
#define dup_x2 91 /*(0x5b)*/

#define iadd 96 /*(0x60)*/
#define ladd 97 /*(0x61)*/

#define isub 100 /*(0x64)*/
#define imul 104 /*(0x68)*/

#define iinc 132 /*(0x84)*/

#define ifeq 153 /*(0x99) */
#define ifne 154 /*(0x9a) */
#define iflt 155 /*(0x9b) */
#define ifge 156 /*(0x9c) */
#define ifgt 157 /*(0x9d) */
#define ifle 158 /*(0x9e)*/


#define if_icmpeq 159 /*(0x9f) */
#define if_icmpne 160 /*(0xa0) */
#define if_icmplt 161 /*(0xa1) */
#define if_icmpge 162 /*(0xa2) */
#define if_icmpgt 163 /*(0xa3) */
#define if_icmple 164 /*(0xa4)*/


#define _goto 167 /*(0xa7)*/

#define ireturn 172 /*(0xac)*/
#define _return 177 /*(0xb1)*/

#define getfield 180 /*(0xb4)*/
#define putfield 181 /*(0xb5)*/

#define invokevirtual 182 /*(0xb6)*/
#define invokespecial  183 /*(0xb7) */
#define invokestatic 184 

#define _new 187 /*(0xbb)*/

#define newarray 188 /*(0xbc)*/
#define anewarray 189 /*(0xbd)*/

#define athrow 191 /* (0xbf) */
#define checkcast 192 /* (0xc0) */
#define instanceof 193 /* (0xc1) */ 
#define monitorenter 194 /* (0xc2) */
#define monitorexit 195 /* (0xc3) */

