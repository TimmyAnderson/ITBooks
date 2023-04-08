

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:15:45 2012
 */
/* Compiler settings for CustomMarshalingByValueServer.idl:
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


#include "CustomMarshalingByValueServer_h.h"

#define TYPE_FORMAT_STRING_SIZE   7                                 
#define PROC_FORMAT_STRING_SIZE   77                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _CustomMarshalingByValueServer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } CustomMarshalingByValueServer_MIDL_TYPE_FORMAT_STRING;

typedef struct _CustomMarshalingByValueServer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } CustomMarshalingByValueServer_MIDL_PROC_FORMAT_STRING;

typedef struct _CustomMarshalingByValueServer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } CustomMarshalingByValueServer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const CustomMarshalingByValueServer_MIDL_TYPE_FORMAT_STRING CustomMarshalingByValueServer__MIDL_TypeFormatString;
extern const CustomMarshalingByValueServer_MIDL_PROC_FORMAT_STRING CustomMarshalingByValueServer__MIDL_ProcFormatString;
extern const CustomMarshalingByValueServer_MIDL_EXPR_FORMAT_STRING CustomMarshalingByValueServer__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ICustomMarshalingByValueTest_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ICustomMarshalingByValueTest_ProxyInfo;



#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const CustomMarshalingByValueServer_MIDL_PROC_FORMAT_STRING CustomMarshalingByValueServer__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure SetValue */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 10 */	NdrFcShort( 0x8 ),	/* 8 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Value */

/* 26 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 28 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 30 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 32 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 34 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 36 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetValue */

/* 38 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 40 */	NdrFcLong( 0x0 ),	/* 0 */
/* 44 */	NdrFcShort( 0x4 ),	/* 4 */
/* 46 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x24 ),	/* 36 */
/* 52 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 54 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Value */

/* 64 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 66 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 68 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 70 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 72 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 74 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const CustomMarshalingByValueServer_MIDL_TYPE_FORMAT_STRING CustomMarshalingByValueServer__MIDL_TypeFormatString =
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


/* Object interface: ICustomMarshalingByValueTest, ver. 0.0,
   GUID={0x18D909F7,0xAEBA,0x4D61,{0x9A,0x9E,0x24,0x61,0xBE,0x1C,0xE2,0xA6}} */

#pragma code_seg(".orpc")
static const unsigned short ICustomMarshalingByValueTest_FormatStringOffsetTable[] =
    {
    0,
    38
    };

static const MIDL_STUBLESS_PROXY_INFO ICustomMarshalingByValueTest_ProxyInfo =
    {
    &Object_StubDesc,
    CustomMarshalingByValueServer__MIDL_ProcFormatString.Format,
    &ICustomMarshalingByValueTest_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ICustomMarshalingByValueTest_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    CustomMarshalingByValueServer__MIDL_ProcFormatString.Format,
    &ICustomMarshalingByValueTest_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _ICustomMarshalingByValueTestProxyVtbl = 
{
    &ICustomMarshalingByValueTest_ProxyInfo,
    &IID_ICustomMarshalingByValueTest,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ICustomMarshalingByValueTest::SetValue */ ,
    (void *) (INT_PTR) -1 /* ICustomMarshalingByValueTest::GetValue */
};

const CInterfaceStubVtbl _ICustomMarshalingByValueTestStubVtbl =
{
    &IID_ICustomMarshalingByValueTest,
    &ICustomMarshalingByValueTest_ServerInfo,
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
    CustomMarshalingByValueServer__MIDL_TypeFormatString.Format,
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

const CInterfaceProxyVtbl * const _CustomMarshalingByValueServer_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ICustomMarshalingByValueTestProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _CustomMarshalingByValueServer_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ICustomMarshalingByValueTestStubVtbl,
    0
};

PCInterfaceName const _CustomMarshalingByValueServer_InterfaceNamesList[] = 
{
    "ICustomMarshalingByValueTest",
    0
};


#define _CustomMarshalingByValueServer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _CustomMarshalingByValueServer, pIID, n)

int __stdcall _CustomMarshalingByValueServer_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_CustomMarshalingByValueServer_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo CustomMarshalingByValueServer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _CustomMarshalingByValueServer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _CustomMarshalingByValueServer_StubVtblList,
    (const PCInterfaceName * ) & _CustomMarshalingByValueServer_InterfaceNamesList,
    0, /* no delegation */
    & _CustomMarshalingByValueServer_IID_Lookup, 
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

