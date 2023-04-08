

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:16:07 2012
 */
/* Compiler settings for FTMServer.idl:
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


#include "FTMServer_h.h"

#define TYPE_FORMAT_STRING_SIZE   7                                 
#define PROC_FORMAT_STRING_SIZE   141                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _FTMServer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } FTMServer_MIDL_TYPE_FORMAT_STRING;

typedef struct _FTMServer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } FTMServer_MIDL_PROC_FORMAT_STRING;

typedef struct _FTMServer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } FTMServer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const FTMServer_MIDL_TYPE_FORMAT_STRING FTMServer__MIDL_TypeFormatString;
extern const FTMServer_MIDL_PROC_FORMAT_STRING FTMServer__MIDL_ProcFormatString;
extern const FTMServer_MIDL_EXPR_FORMAT_STRING FTMServer__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IFTMTest_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IFTMTest_ProxyInfo;



#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const FTMServer_MIDL_PROC_FORMAT_STRING FTMServer__MIDL_ProcFormatString =
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

	/* Procedure IncrementValueToRemoteObject */

/* 70 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 72 */	NdrFcLong( 0x0 ),	/* 0 */
/* 76 */	NdrFcShort( 0x5 ),	/* 5 */
/* 78 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 80 */	NdrFcShort( 0x0 ),	/* 0 */
/* 82 */	NdrFcShort( 0x8 ),	/* 8 */
/* 84 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 86 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 88 */	NdrFcShort( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0x0 ),	/* 0 */
/* 92 */	NdrFcShort( 0x0 ),	/* 0 */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 96 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 98 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 100 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetValueFromRemoteObject */

/* 102 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 104 */	NdrFcLong( 0x0 ),	/* 0 */
/* 108 */	NdrFcShort( 0x6 ),	/* 6 */
/* 110 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 112 */	NdrFcShort( 0x0 ),	/* 0 */
/* 114 */	NdrFcShort( 0x24 ),	/* 36 */
/* 116 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 118 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 122 */	NdrFcShort( 0x0 ),	/* 0 */
/* 124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Value */

/* 128 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 130 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 132 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 134 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 136 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 138 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const FTMServer_MIDL_TYPE_FORMAT_STRING FTMServer__MIDL_TypeFormatString =
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


/* Object interface: IFTMTest, ver. 0.0,
   GUID={0xD83BC28B,0xDDBD,0x4316,{0x80,0x87,0xAF,0x0E,0x11,0xE4,0x01,0xCA}} */

#pragma code_seg(".orpc")
static const unsigned short IFTMTest_FormatStringOffsetTable[] =
    {
    0,
    32,
    70,
    102
    };

static const MIDL_STUBLESS_PROXY_INFO IFTMTest_ProxyInfo =
    {
    &Object_StubDesc,
    FTMServer__MIDL_ProcFormatString.Format,
    &IFTMTest_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IFTMTest_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    FTMServer__MIDL_ProcFormatString.Format,
    &IFTMTest_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IFTMTestProxyVtbl = 
{
    &IFTMTest_ProxyInfo,
    &IID_IFTMTest,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IFTMTest::IncrementValue */ ,
    (void *) (INT_PTR) -1 /* IFTMTest::GetValue */ ,
    (void *) (INT_PTR) -1 /* IFTMTest::IncrementValueToRemoteObject */ ,
    (void *) (INT_PTR) -1 /* IFTMTest::GetValueFromRemoteObject */
};

const CInterfaceStubVtbl _IFTMTestStubVtbl =
{
    &IID_IFTMTest,
    &IFTMTest_ServerInfo,
    7,
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
    FTMServer__MIDL_TypeFormatString.Format,
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

const CInterfaceProxyVtbl * const _FTMServer_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IFTMTestProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _FTMServer_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IFTMTestStubVtbl,
    0
};

PCInterfaceName const _FTMServer_InterfaceNamesList[] = 
{
    "IFTMTest",
    0
};


#define _FTMServer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _FTMServer, pIID, n)

int __stdcall _FTMServer_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_FTMServer_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo FTMServer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _FTMServer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _FTMServer_StubVtblList,
    (const PCInterfaceName * ) & _FTMServer_InterfaceNamesList,
    0, /* no delegation */
    & _FTMServer_IID_Lookup, 
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

