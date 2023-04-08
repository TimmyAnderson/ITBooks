

/* this ALWAYS GENERATED file contains the proxy stub code */


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


#include "ConnectionPointsServer_h.h"

#define TYPE_FORMAT_STRING_SIZE   39                                
#define PROC_FORMAT_STRING_SIZE   39                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

typedef struct _ConnectionPointsServer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } ConnectionPointsServer_MIDL_TYPE_FORMAT_STRING;

typedef struct _ConnectionPointsServer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } ConnectionPointsServer_MIDL_PROC_FORMAT_STRING;

typedef struct _ConnectionPointsServer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } ConnectionPointsServer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const ConnectionPointsServer_MIDL_TYPE_FORMAT_STRING ConnectionPointsServer__MIDL_TypeFormatString;
extern const ConnectionPointsServer_MIDL_PROC_FORMAT_STRING ConnectionPointsServer__MIDL_ProcFormatString;
extern const ConnectionPointsServer_MIDL_EXPR_FORMAT_STRING ConnectionPointsServer__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMyConnectionPointsCallback_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMyConnectionPointsCallback_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMyConnectionPoints_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMyConnectionPoints_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const ConnectionPointsServer_MIDL_PROC_FORMAT_STRING ConnectionPointsServer__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure SendMessageToServer */


	/* Procedure SendMessageToClient */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x1 ),	/* 1 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Message */


	/* Parameter Message */

/* 26 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 28 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 30 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */


	/* Return value */

/* 32 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 34 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 36 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const ConnectionPointsServer_MIDL_TYPE_FORMAT_STRING ConnectionPointsServer__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x12, 0x0,	/* FC_UP */
/*  4 */	NdrFcShort( 0xe ),	/* Offset= 14 (18) */
/*  6 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/*  8 */	NdrFcShort( 0x2 ),	/* 2 */
/* 10 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 12 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 14 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 16 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 18 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 20 */	NdrFcShort( 0x8 ),	/* 8 */
/* 22 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (6) */
/* 24 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 26 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 28 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 30 */	NdrFcShort( 0x0 ),	/* 0 */
/* 32 */	NdrFcShort( 0x8 ),	/* 8 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0xffde ),	/* Offset= -34 (2) */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IMyConnectionPointsCallback, ver. 0.0,
   GUID={0xD179F4FA,0xDCAE,0x456F,{0xB1,0x86,0x2A,0xF5,0x4A,0x0D,0x46,0x8F}} */

#pragma code_seg(".orpc")
static const unsigned short IMyConnectionPointsCallback_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IMyConnectionPointsCallback_ProxyInfo =
    {
    &Object_StubDesc,
    ConnectionPointsServer__MIDL_ProcFormatString.Format,
    &IMyConnectionPointsCallback_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMyConnectionPointsCallback_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    ConnectionPointsServer__MIDL_ProcFormatString.Format,
    &IMyConnectionPointsCallback_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IMyConnectionPointsCallbackProxyVtbl = 
{
    &IMyConnectionPointsCallback_ProxyInfo,
    &IID_IMyConnectionPointsCallback,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IMyConnectionPointsCallback::SendMessageToClient */
};

const CInterfaceStubVtbl _IMyConnectionPointsCallbackStubVtbl =
{
    &IID_IMyConnectionPointsCallback,
    &IMyConnectionPointsCallback_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IMyConnectionPoints, ver. 0.0,
   GUID={0x574AC1CE,0xA230,0x4D8A,{0x89,0x32,0x07,0x56,0x5A,0x03,0xAE,0x1F}} */

#pragma code_seg(".orpc")
static const unsigned short IMyConnectionPoints_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IMyConnectionPoints_ProxyInfo =
    {
    &Object_StubDesc,
    ConnectionPointsServer__MIDL_ProcFormatString.Format,
    &IMyConnectionPoints_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMyConnectionPoints_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    ConnectionPointsServer__MIDL_ProcFormatString.Format,
    &IMyConnectionPoints_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IMyConnectionPointsProxyVtbl = 
{
    &IMyConnectionPoints_ProxyInfo,
    &IID_IMyConnectionPoints,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IMyConnectionPoints::SendMessageToServer */
};

const CInterfaceStubVtbl _IMyConnectionPointsStubVtbl =
{
    &IID_IMyConnectionPoints,
    &IMyConnectionPoints_ServerInfo,
    4,
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
    ConnectionPointsServer__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _ConnectionPointsServer_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IMyConnectionPointsProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMyConnectionPointsCallbackProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _ConnectionPointsServer_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IMyConnectionPointsStubVtbl,
    ( CInterfaceStubVtbl *) &_IMyConnectionPointsCallbackStubVtbl,
    0
};

PCInterfaceName const _ConnectionPointsServer_InterfaceNamesList[] = 
{
    "IMyConnectionPoints",
    "IMyConnectionPointsCallback",
    0
};


#define _ConnectionPointsServer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _ConnectionPointsServer, pIID, n)

int __stdcall _ConnectionPointsServer_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _ConnectionPointsServer, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _ConnectionPointsServer, 2, *pIndex )
    
}

const ExtendedProxyFileInfo ConnectionPointsServer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _ConnectionPointsServer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _ConnectionPointsServer_StubVtblList,
    (const PCInterfaceName * ) & _ConnectionPointsServer_InterfaceNamesList,
    0, /* no delegation */
    & _ConnectionPointsServer_IID_Lookup, 
    2,
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

