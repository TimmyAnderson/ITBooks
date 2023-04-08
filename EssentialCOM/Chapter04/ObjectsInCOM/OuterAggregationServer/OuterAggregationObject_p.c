

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:00:16 2012
 */
/* Compiler settings for OuterAggregationObject.idl:
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


#include "OuterAggregationObject_h.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   1                                 
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _OuterAggregationObject_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } OuterAggregationObject_MIDL_TYPE_FORMAT_STRING;

typedef struct _OuterAggregationObject_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } OuterAggregationObject_MIDL_PROC_FORMAT_STRING;

typedef struct _OuterAggregationObject_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } OuterAggregationObject_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const OuterAggregationObject_MIDL_TYPE_FORMAT_STRING OuterAggregationObject__MIDL_TypeFormatString;
extern const OuterAggregationObject_MIDL_PROC_FORMAT_STRING OuterAggregationObject__MIDL_ProcFormatString;
extern const OuterAggregationObject_MIDL_EXPR_FORMAT_STRING OuterAggregationObject__MIDL_ExprFormatString;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const OuterAggregationObject_MIDL_PROC_FORMAT_STRING OuterAggregationObject__MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const OuterAggregationObject_MIDL_TYPE_FORMAT_STRING OuterAggregationObject__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IOuterAggregationText, ver. 0.0,
   GUID={0x5C0AE81B,0x2AA7,0x43E6,{0x9C,0xC4,0x3C,0xA4,0x59,0x91,0xE3,0x8C}} */

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
    OuterAggregationObject__MIDL_TypeFormatString.Format,
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

const CInterfaceProxyVtbl * const _OuterAggregationObject_ProxyVtblList[] = 
{
    0
};

const CInterfaceStubVtbl * const _OuterAggregationObject_StubVtblList[] = 
{
    0
};

PCInterfaceName const _OuterAggregationObject_InterfaceNamesList[] = 
{
    0
};


#define _OuterAggregationObject_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _OuterAggregationObject, pIID, n)

int __stdcall _OuterAggregationObject_IID_Lookup( const IID * pIID, int * pIndex )
{
    return 0;
}

const ExtendedProxyFileInfo OuterAggregationObject_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _OuterAggregationObject_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _OuterAggregationObject_StubVtblList,
    (const PCInterfaceName * ) & _OuterAggregationObject_InterfaceNamesList,
    0, /* no delegation */
    & _OuterAggregationObject_IID_Lookup, 
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

