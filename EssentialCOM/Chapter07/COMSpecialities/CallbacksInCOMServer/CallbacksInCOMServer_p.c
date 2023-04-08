

/* this ALWAYS GENERATED file contains the proxy stub code */


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


#include "CallbacksInCOMServer_h.h"

#define TYPE_FORMAT_STRING_SIZE   57                                
#define PROC_FORMAT_STRING_SIZE   147                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

typedef struct _CallbacksInCOMServer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } CallbacksInCOMServer_MIDL_TYPE_FORMAT_STRING;

typedef struct _CallbacksInCOMServer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } CallbacksInCOMServer_MIDL_PROC_FORMAT_STRING;

typedef struct _CallbacksInCOMServer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } CallbacksInCOMServer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const CallbacksInCOMServer_MIDL_TYPE_FORMAT_STRING CallbacksInCOMServer__MIDL_TypeFormatString;
extern const CallbacksInCOMServer_MIDL_PROC_FORMAT_STRING CallbacksInCOMServer__MIDL_ProcFormatString;
extern const CallbacksInCOMServer_MIDL_EXPR_FORMAT_STRING CallbacksInCOMServer__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMyServerCallback_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMyServerCallback_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMyServer_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMyServer_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const CallbacksInCOMServer_MIDL_PROC_FORMAT_STRING CallbacksInCOMServer__MIDL_ProcFormatString =
    {
        0,
        {

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

/* 26 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 28 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 30 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 32 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 34 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 36 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RegisterCallback */

/* 38 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 40 */	NdrFcLong( 0x0 ),	/* 0 */
/* 44 */	NdrFcShort( 0x3 ),	/* 3 */
/* 46 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x8 ),	/* 8 */
/* 52 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 54 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Callback */

/* 64 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 66 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 68 */	NdrFcShort( 0x26 ),	/* Type Offset=38 */

	/* Return value */

/* 70 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 72 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 74 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnRegisterCallback */

/* 76 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 78 */	NdrFcLong( 0x0 ),	/* 0 */
/* 82 */	NdrFcShort( 0x4 ),	/* 4 */
/* 84 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 86 */	NdrFcShort( 0x0 ),	/* 0 */
/* 88 */	NdrFcShort( 0x8 ),	/* 8 */
/* 90 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 92 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0x0 ),	/* 0 */
/* 98 */	NdrFcShort( 0x0 ),	/* 0 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 102 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 104 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SendMessageToServer */

/* 108 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 110 */	NdrFcLong( 0x0 ),	/* 0 */
/* 114 */	NdrFcShort( 0x5 ),	/* 5 */
/* 116 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 120 */	NdrFcShort( 0x8 ),	/* 8 */
/* 122 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 124 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 128 */	NdrFcShort( 0x1 ),	/* 1 */
/* 130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 132 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Message */

/* 134 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 136 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 138 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 140 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 142 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 144 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const CallbacksInCOMServer_MIDL_TYPE_FORMAT_STRING CallbacksInCOMServer__MIDL_TypeFormatString =
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
/* 38 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 40 */	NdrFcLong( 0x69086c22 ),	/* 1762159650 */
/* 44 */	NdrFcShort( 0x221f ),	/* 8735 */
/* 46 */	NdrFcShort( 0x4a29 ),	/* 18985 */
/* 48 */	0x9f,		/* 159 */
			0x91,		/* 145 */
/* 50 */	0x2d,		/* 45 */
			0x6e,		/* 110 */
/* 52 */	0xb9,		/* 185 */
			0xd1,		/* 209 */
/* 54 */	0xef,		/* 239 */
			0xfb,		/* 251 */

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


/* Object interface: IMyServerCallback, ver. 0.0,
   GUID={0x69086C22,0x221F,0x4A29,{0x9F,0x91,0x2D,0x6E,0xB9,0xD1,0xEF,0xFB}} */

#pragma code_seg(".orpc")
static const unsigned short IMyServerCallback_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IMyServerCallback_ProxyInfo =
    {
    &Object_StubDesc,
    CallbacksInCOMServer__MIDL_ProcFormatString.Format,
    &IMyServerCallback_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMyServerCallback_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    CallbacksInCOMServer__MIDL_ProcFormatString.Format,
    &IMyServerCallback_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IMyServerCallbackProxyVtbl = 
{
    &IMyServerCallback_ProxyInfo,
    &IID_IMyServerCallback,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IMyServerCallback::SendMessageToClient */
};

const CInterfaceStubVtbl _IMyServerCallbackStubVtbl =
{
    &IID_IMyServerCallback,
    &IMyServerCallback_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IMyServer, ver. 0.0,
   GUID={0xDB83FED1,0xED27,0x425C,{0x87,0xB7,0xFF,0x50,0x36,0xC1,0xF0,0x8E}} */

#pragma code_seg(".orpc")
static const unsigned short IMyServer_FormatStringOffsetTable[] =
    {
    38,
    76,
    108
    };

static const MIDL_STUBLESS_PROXY_INFO IMyServer_ProxyInfo =
    {
    &Object_StubDesc,
    CallbacksInCOMServer__MIDL_ProcFormatString.Format,
    &IMyServer_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMyServer_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    CallbacksInCOMServer__MIDL_ProcFormatString.Format,
    &IMyServer_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IMyServerProxyVtbl = 
{
    &IMyServer_ProxyInfo,
    &IID_IMyServer,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IMyServer::RegisterCallback */ ,
    (void *) (INT_PTR) -1 /* IMyServer::UnRegisterCallback */ ,
    (void *) (INT_PTR) -1 /* IMyServer::SendMessageToServer */
};

const CInterfaceStubVtbl _IMyServerStubVtbl =
{
    &IID_IMyServer,
    &IMyServer_ServerInfo,
    6,
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
    CallbacksInCOMServer__MIDL_TypeFormatString.Format,
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

const CInterfaceProxyVtbl * const _CallbacksInCOMServer_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IMyServerCallbackProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMyServerProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _CallbacksInCOMServer_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IMyServerCallbackStubVtbl,
    ( CInterfaceStubVtbl *) &_IMyServerStubVtbl,
    0
};

PCInterfaceName const _CallbacksInCOMServer_InterfaceNamesList[] = 
{
    "IMyServerCallback",
    "IMyServer",
    0
};


#define _CallbacksInCOMServer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _CallbacksInCOMServer, pIID, n)

int __stdcall _CallbacksInCOMServer_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _CallbacksInCOMServer, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _CallbacksInCOMServer, 2, *pIndex )
    
}

const ExtendedProxyFileInfo CallbacksInCOMServer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _CallbacksInCOMServer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _CallbacksInCOMServer_StubVtblList,
    (const PCInterfaceName * ) & _CallbacksInCOMServer_InterfaceNamesList,
    0, /* no delegation */
    & _CallbacksInCOMServer_IID_Lookup, 
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

