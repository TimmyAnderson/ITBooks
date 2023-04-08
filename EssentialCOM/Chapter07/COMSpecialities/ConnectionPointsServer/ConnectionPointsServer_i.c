

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Aug 09 22:52:31 2012
 */
/* Compiler settings for ConnectionPointsServer.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 7.00.0555 
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

MIDL_DEFINE_GUID(IID, IID_IMyConnectionPointsCallback,0xD179F4FA,0xDCAE,0x456F,0xB1,0x86,0x2A,0xF5,0x4A,0x0D,0x46,0x8F);


MIDL_DEFINE_GUID(IID, IID_IMyConnectionPoints,0x574AC1CE,0xA230,0x4D8A,0x89,0x32,0x07,0x56,0x5A,0x03,0xAE,0x1F);


MIDL_DEFINE_GUID(IID, LIBID_ConnectionPointsServerLib,0x94749E9A,0xF72F,0x4A57,0x87,0x7A,0x7B,0xA7,0x56,0x7E,0x73,0xB9);


MIDL_DEFINE_GUID(CLSID, CLSID_ConnectionPointsObject,0x013B83E1,0x964F,0x4970,0x8F,0x99,0x96,0xFE,0x14,0x66,0xC7,0x8B);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



