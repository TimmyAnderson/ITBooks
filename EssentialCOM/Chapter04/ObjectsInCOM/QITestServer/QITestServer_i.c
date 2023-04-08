

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:00:06 2012
 */
/* Compiler settings for QITestServer.idl:
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

MIDL_DEFINE_GUID(IID, IID_IGetText1,0xDEDF2F66,0x3D4D,0x497C,0xB9,0xD4,0xE8,0x66,0x13,0xEE,0x5E,0x9F);


MIDL_DEFINE_GUID(IID, IID_IGetText2,0x280BA5E9,0x9EF5,0x4E68,0x9E,0x58,0xBB,0x0B,0xE4,0x41,0xF2,0x08);


MIDL_DEFINE_GUID(IID, IID_IGetText3,0x8A50080A,0xCF08,0x44A8,0x8C,0x57,0xB4,0xC7,0x38,0x43,0xD3,0x87);


MIDL_DEFINE_GUID(IID, LIBID_QITestServerLib,0xB23C4ED4,0xAB93,0x417E,0xA7,0x2F,0xD8,0x97,0x86,0x88,0xA5,0xF2);


MIDL_DEFINE_GUID(CLSID, CLSID_QITestObject,0xDCAE9847,0xCCA3,0x4B1F,0x8E,0x80,0x9E,0x6C,0x04,0x84,0xF9,0xA4);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



