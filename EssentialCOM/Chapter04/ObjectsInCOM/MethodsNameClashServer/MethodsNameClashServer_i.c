

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:00:06 2012
 */
/* Compiler settings for MethodsNameClashServer.idl:
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

MIDL_DEFINE_GUID(IID, IID_IGetText1,0xF567B9C9,0xE34B,0x4ACD,0x87,0xA1,0xF4,0x65,0x5E,0x2B,0x5B,0xCB);


MIDL_DEFINE_GUID(IID, IID_IGetText2,0xB0722B76,0xBB23,0x4216,0x84,0x68,0x87,0xCA,0x68,0x0A,0xAE,0xD3);


MIDL_DEFINE_GUID(IID, LIBID_MethodsNameClashServerLib,0xEFFA0431,0x155B,0x433E,0x95,0xB2,0xF1,0x23,0x9D,0xAF,0x59,0x36);


MIDL_DEFINE_GUID(CLSID, CLSID_MethodsNameClashObject,0xD30F8E8F,0xCD97,0x4255,0x90,0xBF,0x0D,0x7E,0xC9,0xB8,0x53,0xFA);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



