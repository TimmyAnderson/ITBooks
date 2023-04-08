

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:00:06 2012
 */
/* Compiler settings for CompositionServer.idl:
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

MIDL_DEFINE_GUID(IID, IID_IGetText1,0x646D0B35,0x9E94,0x439A,0xB0,0x49,0x4C,0x59,0x12,0x09,0x40,0xB5);


MIDL_DEFINE_GUID(IID, IID_IGetText2,0x06C84E8D,0x52D5,0x4080,0xBF,0xC7,0x7D,0x8C,0x93,0x3A,0xD6,0x16);


MIDL_DEFINE_GUID(IID, LIBID_CompositionServerLib,0xB299B7F1,0x9811,0x4300,0xB3,0xB1,0xAC,0x58,0x7A,0x71,0x24,0x44);


MIDL_DEFINE_GUID(CLSID, CLSID_CompositionObject,0x48C0A70D,0xE917,0x49D9,0x85,0x5A,0xDC,0x44,0x59,0x06,0x6B,0x1C);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



