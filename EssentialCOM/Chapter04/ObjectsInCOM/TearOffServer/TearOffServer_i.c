

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:00:06 2012
 */
/* Compiler settings for TearOffServer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ITearOffTextOuter,0x93664F4D,0xCA8C,0x4F8D,0xAD,0x0B,0x5A,0xFF,0x9B,0x21,0x0D,0xB1);


MIDL_DEFINE_GUID(IID, IID_ITearOffTextInner,0xB84E7F7C,0x9E8B,0x48BC,0x85,0xA7,0x29,0xC3,0x87,0xB5,0x24,0x1A);


MIDL_DEFINE_GUID(IID, LIBID_TearOffServerLib,0xCF07F595,0x45B7,0x4F18,0x87,0x60,0xE6,0x40,0x71,0x79,0xFF,0xA1);


MIDL_DEFINE_GUID(CLSID, CLSID_TearOffObject,0x549C91FE,0x1B9D,0x4A38,0xB0,0xC8,0xA0,0x3D,0x50,0xFF,0xD0,0x4B);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



