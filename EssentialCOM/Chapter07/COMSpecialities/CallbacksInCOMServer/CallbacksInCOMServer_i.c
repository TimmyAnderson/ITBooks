

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Aug 09 22:52:31 2012
 */
/* Compiler settings for CallbacksInCOMServer.idl:
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

MIDL_DEFINE_GUID(IID, IID_IMyServerCallback,0x69086C22,0x221F,0x4A29,0x9F,0x91,0x2D,0x6E,0xB9,0xD1,0xEF,0xFB);


MIDL_DEFINE_GUID(IID, IID_IMyServer,0xDB83FED1,0xED27,0x425C,0x87,0xB7,0xFF,0x50,0x36,0xC1,0xF0,0x8E);


MIDL_DEFINE_GUID(IID, LIBID_CallbacksInCOMServerLib,0x493FFE87,0xB267,0x4D96,0x8C,0xF5,0x0D,0x78,0x6F,0xAA,0x60,0x4F);


MIDL_DEFINE_GUID(CLSID, CLSID_CallbacksInCOMObject,0x91C07319,0xAD70,0x4A12,0xA0,0x70,0xDC,0x8E,0x76,0xA5,0xBC,0x95);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



