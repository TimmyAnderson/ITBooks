

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 21:30:38 2012
 */
/* Compiler settings for MultiInterfaceCOM.idl:
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

MIDL_DEFINE_GUID(IID, IID_IName,0x66F4B6C1,0x2A1D,0x4CA7,0x8C,0xEC,0x2A,0x23,0x69,0xF5,0x83,0xC4);


MIDL_DEFINE_GUID(IID, IID_IToString,0x9BF6F5F0,0xC48B,0x4919,0xA7,0x3D,0xFA,0x28,0xF0,0x5C,0x60,0xBE);


MIDL_DEFINE_GUID(IID, IID_ITest,0xCB02484F,0x0B97,0x47F4,0xA2,0xE7,0x70,0x9B,0x25,0x75,0xD9,0x8D);


MIDL_DEFINE_GUID(IID, IID_IExceptionTest,0xA73BCD2D,0x2095,0x4D12,0x8C,0xC0,0x4E,0x90,0x45,0xFB,0xF4,0x61);


MIDL_DEFINE_GUID(IID, LIBID_MultiInterfaceCOMServerLib,0x8D006922,0x4404,0x464A,0xA6,0x08,0x3F,0x34,0xF9,0x8E,0x9D,0x9B);


MIDL_DEFINE_GUID(CLSID, CLSID_MultiInterfaceCOM,0x888F3A01,0xC4DB,0x4C00,0xA4,0x59,0x15,0x33,0x61,0xD3,0xCF,0x81);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



