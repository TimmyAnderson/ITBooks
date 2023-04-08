

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Aug 09 22:52:30 2012
 */
/* Compiler settings for AsynchronousMethodsServer.idl:
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


#include "AsynchronousMethodsServer_h.h"

#define TYPE_FORMAT_STRING_SIZE   57                                
#define PROC_FORMAT_STRING_SIZE   217                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

typedef struct _AsynchronousMethodsServer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } AsynchronousMethodsServer_MIDL_TYPE_FORMAT_STRING;

typedef struct _AsynchronousMethodsServer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } AsynchronousMethodsServer_MIDL_PROC_FORMAT_STRING;

typedef struct _AsynchronousMethodsServer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } AsynchronousMethodsServer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const AsynchronousMethodsServer_MIDL_TYPE_FORMAT_STRING AsynchronousMethodsServer__MIDL_TypeFormatString;
extern const AsynchronousMethodsServer_MIDL_PROC_FORMAT_STRING AsynchronousMethodsServer__MIDL_ProcFormatString;
extern const AsynchronousMethodsServer_MIDL_EXPR_FORMAT_STRING AsynchronousMethodsServer__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAsynchronousMethodsTest_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAsynchronousMethodsTest_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO AsyncIAsynchronousMethodsTest_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO AsyncIAsynchronousMethodsTest_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const AsynchronousMethodsServer_MIDL_PROC_FORMAT_STRING AsynchronousMethodsServer__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure SetValue */

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

	/* Parameter Value */

/* 26 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 28 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 30 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

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
/* 50 */	NdrFcShort( 0x8 ),	/* 8 */
/* 52 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 54 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 56 */	NdrFcShort( 0x1 ),	/* 1 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Value */

/* 64 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 66 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 68 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Return value */

/* 70 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 72 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 74 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Begin_SetValue */

/* 76 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 78 */	NdrFcLong( 0x0 ),	/* 0 */
/* 82 */	NdrFcShort( 0x3 ),	/* 3 */
/* 84 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 86 */	NdrFcShort( 0x0 ),	/* 0 */
/* 88 */	NdrFcShort( 0x8 ),	/* 8 */
/* 90 */	0x66,		/* Oi2 Flags:  clt must size, has return, has async uuid, has ext, */
			0x2,		/* 2 */
/* 92 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0x1 ),	/* 1 */
/* 98 */	NdrFcShort( 0x0 ),	/* 0 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Value */

/* 102 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 104 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 106 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 108 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 110 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Finish_SetValue */

/* 114 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 116 */	NdrFcLong( 0x0 ),	/* 0 */
/* 120 */	NdrFcShort( 0x4 ),	/* 4 */
/* 122 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x8 ),	/* 8 */
/* 128 */	0x64,		/* Oi2 Flags:  has return, has async uuid, has ext, */
			0x1,		/* 1 */
/* 130 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 138 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 140 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 142 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 144 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Begin_GetValue */

/* 146 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 148 */	NdrFcLong( 0x0 ),	/* 0 */
/* 152 */	NdrFcShort( 0x5 ),	/* 5 */
/* 154 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 156 */	NdrFcShort( 0x0 ),	/* 0 */
/* 158 */	NdrFcShort( 0x8 ),	/* 8 */
/* 160 */	0x64,		/* Oi2 Flags:  has return, has async uuid, has ext, */
			0x1,		/* 1 */
/* 162 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 164 */	NdrFcShort( 0x0 ),	/* 0 */
/* 166 */	NdrFcShort( 0x0 ),	/* 0 */
/* 168 */	NdrFcShort( 0x0 ),	/* 0 */
/* 170 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 172 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 174 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 176 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Finish_GetValue */

/* 178 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 180 */	NdrFcLong( 0x0 ),	/* 0 */
/* 184 */	NdrFcShort( 0x6 ),	/* 6 */
/* 186 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 190 */	NdrFcShort( 0x8 ),	/* 8 */
/* 192 */	0x65,		/* Oi2 Flags:  srv must size, has return, has async uuid, has ext, */
			0x2,		/* 2 */
/* 194 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 196 */	NdrFcShort( 0x1 ),	/* 1 */
/* 198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 202 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Value */

/* 204 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 206 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 208 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Return value */

/* 210 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 212 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 214 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const AsynchronousMethodsServer_MIDL_TYPE_FORMAT_STRING AsynchronousMethodsServer__MIDL_TypeFormatString =
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
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 40 */	NdrFcShort( 0x6 ),	/* Offset= 6 (46) */
/* 42 */	
			0x13, 0x0,	/* FC_OP */
/* 44 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (18) */
/* 46 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x8 ),	/* 8 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (42) */

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


/* Object interface: IAsynchronousMethodsTest, ver. 0.0,
   GUID={0xFFBC006F,0x662B,0x4817,{0x9B,0x72,0x8D,0xD6,0x94,0x3B,0xDA,0xEB}} */

#pragma code_seg(".orpc")
static const unsigned short IAsynchronousMethodsTest_FormatStringOffsetTable[] =
    {
    0,
    38
    };

static const MIDL_STUBLESS_PROXY_INFO IAsynchronousMethodsTest_ProxyInfo =
    {
    &Object_StubDesc,
    AsynchronousMethodsServer__MIDL_ProcFormatString.Format,
    &IAsynchronousMethodsTest_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAsynchronousMethodsTest_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    AsynchronousMethodsServer__MIDL_ProcFormatString.Format,
    &IAsynchronousMethodsTest_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IAsynchronousMethodsTestProxyVtbl = 
{
    &IAsynchronousMethodsTest_ProxyInfo,
    &IID_IAsynchronousMethodsTest,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IAsynchronousMethodsTest::SetValue */ ,
    (void *) (INT_PTR) -1 /* IAsynchronousMethodsTest::GetValue */
};

const CInterfaceStubVtbl _IAsynchronousMethodsTestStubVtbl =
{
    &IID_IAsynchronousMethodsTest,
    &IAsynchronousMethodsTest_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: AsyncIAsynchronousMethodsTest, ver. 0.0,
   GUID={0x1E610375,0xB6DE,0x44F3,{0x83,0x4D,0x99,0xD7,0x51,0x9E,0x09,0xD8}} */

#pragma code_seg(".orpc")
static const unsigned short AsyncIAsynchronousMethodsTest_FormatStringOffsetTable[] =
    {
    76,
    114,
    146,
    178
    };

static const MIDL_STUBLESS_PROXY_INFO AsyncIAsynchronousMethodsTest_ProxyInfo =
    {
    &Object_StubDesc,
    AsynchronousMethodsServer__MIDL_ProcFormatString.Format,
    &AsyncIAsynchronousMethodsTest_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO AsyncIAsynchronousMethodsTest_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    AsynchronousMethodsServer__MIDL_ProcFormatString.Format,
    &AsyncIAsynchronousMethodsTest_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _AsyncIAsynchronousMethodsTestProxyVtbl = 
{
    &AsyncIAsynchronousMethodsTest_ProxyInfo,
    &IID_AsyncIAsynchronousMethodsTest,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* AsyncIAsynchronousMethodsTest::Begin_SetValue */ ,
    (void *) (INT_PTR) -1 /* AsyncIAsynchronousMethodsTest::Finish_SetValue */ ,
    (void *) (INT_PTR) -1 /* AsyncIAsynchronousMethodsTest::Begin_GetValue */ ,
    (void *) (INT_PTR) -1 /* AsyncIAsynchronousMethodsTest::Finish_GetValue */
};

CInterfaceStubVtbl _AsyncIAsynchronousMethodsTestStubVtbl =
{
    &IID_AsyncIAsynchronousMethodsTest,
    &AsyncIAsynchronousMethodsTest_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdAsyncStubBuffer_METHODS
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
    AsynchronousMethodsServer__MIDL_TypeFormatString.Format,
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

const CInterfaceProxyVtbl * const _AsynchronousMethodsServer_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IAsynchronousMethodsTestProxyVtbl,
    ( CInterfaceProxyVtbl *) &_AsyncIAsynchronousMethodsTestProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _AsynchronousMethodsServer_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IAsynchronousMethodsTestStubVtbl,
    ( CInterfaceStubVtbl *) &_AsyncIAsynchronousMethodsTestStubVtbl,
    0
};

PCInterfaceName const _AsynchronousMethodsServer_InterfaceNamesList[] = 
{
    "IAsynchronousMethodsTest",
    "AsyncIAsynchronousMethodsTest",
    0
};


#define _AsynchronousMethodsServer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _AsynchronousMethodsServer, pIID, n)

int __stdcall _AsynchronousMethodsServer_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _AsynchronousMethodsServer, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _AsynchronousMethodsServer, 2, *pIndex )
    
}

static const IID * const _AsyncInterfaceTable[] = 
{
    (IID*) &IID_AsyncIAsynchronousMethodsTest,
    (IID*)(LONG_PTR) -1,
    (IID*) 0
};

const ExtendedProxyFileInfo AsynchronousMethodsServer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _AsynchronousMethodsServer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _AsynchronousMethodsServer_StubVtblList,
    (const PCInterfaceName * ) & _AsynchronousMethodsServer_InterfaceNamesList,
    0, /* no delegation */
    & _AsynchronousMethodsServer_IID_Lookup, 
    2,
    6,
    (const IID**) &_AsyncInterfaceTable[0], /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_AMD64)*/

