

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Aug 09 22:52:30 2012
 */
/* Compiler settings for AsynchronousMethodsServer.idl:
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

MIDL_DEFINE_GUID(IID, IID_IAsynchronousMethodsTest,0xFFBC006F,0x662B,0x4817,0x9B,0x72,0x8D,0xD6,0x94,0x3B,0xDA,0xEB);


MIDL_DEFINE_GUID(IID, IID_AsyncIAsynchronousMethodsTest,0x1E610375,0xB6DE,0x44F3,0x83,0x4D,0x99,0xD7,0x51,0x9E,0x09,0xD8);


MIDL_DEFINE_GUID(IID, LIBID_AsynchronousMethodsServerLib,0x3A158138,0xF9A2,0x4209,0x8F,0xCA,0xF3,0x0F,0x47,0x26,0x1D,0xEC);


MIDL_DEFINE_GUID(CLSID, CLSID_AsynchronousMethodsObject,0xFB76EEC7,0xC53D,0x44E6,0x93,0x90,0x12,0x39,0x22,0xBE,0xEE,0xB2);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



