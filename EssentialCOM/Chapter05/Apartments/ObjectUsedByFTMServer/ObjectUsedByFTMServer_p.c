

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:15:44 2012
 */
/* Compiler settings for ObjectUsedByFTMServer.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "ObjectUsedByFTMServer_h.h"

#define TYPE_FORMAT_STRING_SIZE   7                                 
#define PROC_FORMAT_STRING_SIZE   71                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _ObjectUsedByFTMServer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } ObjectUsedByFTMServer_MIDL_TYPE_FORMAT_STRING;

typedef struct _ObjectUsedByFTMServer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } ObjectUsedByFTMServer_MIDL_PROC_FORMAT_STRING;

typedef struct _ObjectUsedByFTMServer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } ObjectUsedByFTMServer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const ObjectUsedByFTMServer_MIDL_TYPE_FORMAT_STRING ObjectUsedByFTMServer__MIDL_TypeFormatString;
extern const ObjectUsedByFTMServer_MIDL_PROC_FORMAT_STRING ObjectUsedByFTMServer__MIDL_ProcFormatString;
extern const ObjectUsedByFTMServer_MIDL_EXPR_FORMAT_STRING ObjectUsedByFTMServer__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IObjectUsedByFTMTest_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IObjectUsedByFTMTest_ProxyInfo;



#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const ObjectUsedByFTMServer_MIDL_PROC_FORMAT_STRING ObjectUsedByFTMServer__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure IncrementValue */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 16 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 26 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 28 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 30 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetValue */

/* 32 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 34 */	NdrFcLong( 0x0 ),	/* 0 */
/* 38 */	NdrFcShort( 0x4 ),	/* 4 */
/* 40 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 42 */	NdrFcShort( 0x0 ),	/* 0 */
/* 44 */	NdrFcShort( 0x24 ),	/* 36 */
/* 46 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 48 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 50 */	NdrFcShort( 0x0 ),	/* 0 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Value */

/* 58 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 60 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 62 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 64 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 66 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 68 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const ObjectUsedByFTMServer_MIDL_TYPE_FORMAT_STRING ObjectUsedByFTMServer__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IObjectUsedByFTMTest, ver. 0.0,
   GUID={0x4FD8CBC3,0x914C,0x4B34,{0xBC,0x82,0x61,0x5C,0x73,0xFC,0x8F,0x31}} */

#pragma code_seg(".orpc")
static const unsigned short IObjectUsedByFTMTest_FormatStringOffsetTable[] =
    {
    0,
    32
    };

static const MIDL_STUBLESS_PROXY_INFO IObjectUsedByFTMTest_ProxyInfo =
    {
    &Object_StubDesc,
    ObjectUsedByFTMServer__MIDL_ProcFormatString.Format,
    &IObjectUsedByFTMTest_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IObjectUsedByFTMTest_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    ObjectUsedByFTMServer__MIDL_ProcFormatString.Format,
    &IObjectUsedByFTMTest_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IObjectUsedByFTMTestProxyVtbl = 
{
    &IObjectUsedByFTMTest_ProxyInfo,
    &IID_IObjectUsedByFTMTest,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IObjectUsedByFTMTest::IncrementValue */ ,
    (void *) (INT_PTR) -1 /* IObjectUsedByFTMTest::GetValue */
};

const CInterfaceStubVtbl _IObjectUsedByFTMTestStubVtbl =
{
    &IID_IObjectUsedByFTMTest,
    &IObjectUsedByFTMTest_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

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
    ObjectUsedByFTMServer__MIDL_TypeFormatString.Format,
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

const CInterfaceProxyVtbl * const _ObjectUsedByFTMServer_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IObjectUsedByFTMTestProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _ObjectUsedByFTMServer_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IObjectUsedByFTMTestStubVtbl,
    0
};

PCInterfaceName const _ObjectUsedByFTMServer_InterfaceNamesList[] = 
{
    "IObjectUsedByFTMTest",
    0
};


#define _ObjectUsedByFTMServer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _ObjectUsedByFTMServer, pIID, n)

int __stdcall _ObjectUsedByFTMServer_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_ObjectUsedByFTMServer_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo ObjectUsedByFTMServer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _ObjectUsedByFTMServer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _ObjectUsedByFTMServer_StubVtblList,
    (const PCInterfaceName * ) & _ObjectUsedByFTMServer_InterfaceNamesList,
    0, /* no delegation */
    & _ObjectUsedByFTMServer_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_AMD64)*/

