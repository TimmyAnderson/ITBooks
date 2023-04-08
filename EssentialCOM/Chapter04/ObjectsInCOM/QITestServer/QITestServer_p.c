

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "QITestServer_h.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   1                                 
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _QITestServer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } QITestServer_MIDL_TYPE_FORMAT_STRING;

typedef struct _QITestServer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } QITestServer_MIDL_PROC_FORMAT_STRING;

typedef struct _QITestServer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } QITestServer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const QITestServer_MIDL_TYPE_FORMAT_STRING QITestServer__MIDL_TypeFormatString;
extern const QITestServer_MIDL_PROC_FORMAT_STRING QITestServer__MIDL_ProcFormatString;
extern const QITestServer_MIDL_EXPR_FORMAT_STRING QITestServer__MIDL_ExprFormatString;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const QITestServer_MIDL_PROC_FORMAT_STRING QITestServer__MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const QITestServer_MIDL_TYPE_FORMAT_STRING QITestServer__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IGetText1, ver. 0.0,
   GUID={0xDEDF2F66,0x3D4D,0x497C,{0xB9,0xD4,0xE8,0x66,0x13,0xEE,0x5E,0x9F}} */


/* Object interface: IGetText2, ver. 0.0,
   GUID={0x280BA5E9,0x9EF5,0x4E68,{0x9E,0x58,0xBB,0x0B,0xE4,0x41,0xF2,0x08}} */


/* Object interface: IGetText3, ver. 0.0,
   GUID={0x8A50080A,0xCF08,0x44A8,{0x8C,0x57,0xB4,0xC7,0x38,0x43,0xD3,0x87}} */

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    QITestServer__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _QITestServer_ProxyVtblList[] = 
{
    0
};

const CInterfaceStubVtbl * const _QITestServer_StubVtblList[] = 
{
    0
};

PCInterfaceName const _QITestServer_InterfaceNamesList[] = 
{
    0
};


#define _QITestServer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _QITestServer, pIID, n)

int __stdcall _QITestServer_IID_Lookup( const IID * pIID, int * pIndex )
{
    return 0;
}

const ExtendedProxyFileInfo QITestServer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _QITestServer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _QITestServer_StubVtblList,
    (const PCInterfaceName * ) & _QITestServer_InterfaceNamesList,
    0, /* no delegation */
    & _QITestServer_IID_Lookup, 
    0,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/
