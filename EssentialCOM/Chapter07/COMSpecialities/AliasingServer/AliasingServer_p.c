

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Aug 09 22:52:31 2012
 */
/* Compiler settings for AliasingServer.idl:
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


#include "AliasingServer_h.h"

#define TYPE_FORMAT_STRING_SIZE   29                                
#define PROC_FORMAT_STRING_SIZE   115                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _AliasingServer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } AliasingServer_MIDL_TYPE_FORMAT_STRING;

typedef struct _AliasingServer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } AliasingServer_MIDL_PROC_FORMAT_STRING;

typedef struct _AliasingServer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } AliasingServer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const AliasingServer_MIDL_TYPE_FORMAT_STRING AliasingServer__MIDL_TypeFormatString;
extern const AliasingServer_MIDL_PROC_FORMAT_STRING AliasingServer__MIDL_ProcFormatString;
extern const AliasingServer_MIDL_EXPR_FORMAT_STRING AliasingServer__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAliasingTest_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAliasingTest_ProxyInfo;

/* [call_as] */ HRESULT STDMETHODCALLTYPE IAliasingTest_RemoteFillArray_Proxy( 
    IAliasingTest * This,
    /* [in] */ int ArraySize,
    /* [out] */ int *ArrayLength,
    /* [length_is][size_is][out] */ int *Array)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &AliasingServer__MIDL_ProcFormatString.Format[32],
                  ( unsigned char * )This,
                  ArraySize,
                  ArrayLength,
                  Array);
return ( HRESULT  )_RetVal.Simple;

}

void __RPC_API
IAliasingTest_RemoteFillArray_Thunk(
    PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(8)
    struct _PARAM_STRUCT
        {
        IAliasingTest *This;
        int ArraySize;
        char Pad0[4];
        int *ArrayLength;
        int *Array;
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT * pParamStruct;

    pParamStruct = (struct _PARAM_STRUCT *) pStubMsg->StackTop;
    
    /* Call the server */
    
    pParamStruct->_RetVal = IAliasingTest_FillArray_Stub(
                                       (IAliasingTest *) pParamStruct->This,
                                       pParamStruct->ArraySize,
                                       pParamStruct->ArrayLength,
                                       pParamStruct->Array);
    
}



#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const AliasingServer_MIDL_PROC_FORMAT_STRING AliasingServer__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Dummy */

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

	/* Procedure RemoteFillArray */

/* 32 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 34 */	NdrFcLong( 0x0 ),	/* 0 */
/* 38 */	NdrFcShort( 0x4 ),	/* 4 */
/* 40 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 42 */	NdrFcShort( 0x8 ),	/* 8 */
/* 44 */	NdrFcShort( 0x24 ),	/* 36 */
/* 46 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 48 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 50 */	NdrFcShort( 0x1 ),	/* 1 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ArraySize */

/* 58 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 60 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 62 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ArrayLength */

/* 64 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 66 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 68 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Array */

/* 70 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 72 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 74 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 76 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 78 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 80 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CallFunctionDefinedByCPPQuote */

/* 82 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 84 */	NdrFcLong( 0x0 ),	/* 0 */
/* 88 */	NdrFcShort( 0x5 ),	/* 5 */
/* 90 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 92 */	NdrFcShort( 0x0 ),	/* 0 */
/* 94 */	NdrFcShort( 0x8 ),	/* 8 */
/* 96 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 98 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 106 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 108 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 110 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const AliasingServer_MIDL_TYPE_FORMAT_STRING AliasingServer__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x0,	/* FC_RP */
/*  8 */	NdrFcShort( 0x2 ),	/* Offset= 2 (10) */
/* 10 */	
			0x1c,		/* FC_CVARRAY */
			0x3,		/* 3 */
/* 12 */	NdrFcShort( 0x4 ),	/* 4 */
/* 14 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 18 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 20 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x54,		/* FC_DEREFERENCE */
/* 22 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 24 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 26 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */

			0x0
        }
    };


/* Standard interface: __MIDL_itf_AliasingServer_0000_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IAliasingTest, ver. 0.0,
   GUID={0xB4B9C8FC,0x1C0C,0x4550,{0x8D,0x09,0x0E,0xCA,0x59,0x00,0xFB,0x85}} */

#pragma code_seg(".orpc")
static const unsigned short IAliasingTest_FormatStringOffsetTable[] =
    {
    0,
    32,
    82
    };

static const MIDL_STUBLESS_PROXY_INFO IAliasingTest_ProxyInfo =
    {
    &Object_StubDesc,
    AliasingServer__MIDL_ProcFormatString.Format,
    &IAliasingTest_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const STUB_THUNK IAliasingTest_StubThunkTable[] = 
    {
    0,
    IAliasingTest_RemoteFillArray_Thunk,
    0
    };

static const MIDL_SERVER_INFO IAliasingTest_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    AliasingServer__MIDL_ProcFormatString.Format,
    &IAliasingTest_FormatStringOffsetTable[-3],
    &IAliasingTest_StubThunkTable[-3],
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IAliasingTestProxyVtbl = 
{
    &IAliasingTest_ProxyInfo,
    &IID_IAliasingTest,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IAliasingTest::Dummy */ ,
    IAliasingTest_FillArray_Proxy ,
    (void *) (INT_PTR) -1 /* IAliasingTest::CallFunctionDefinedByCPPQuote */
};

const CInterfaceStubVtbl _IAliasingTestStubVtbl =
{
    &IID_IAliasingTest,
    &IAliasingTest_ServerInfo,
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
    AliasingServer__MIDL_TypeFormatString.Format,
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

const CInterfaceProxyVtbl * const _AliasingServer_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IAliasingTestProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _AliasingServer_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IAliasingTestStubVtbl,
    0
};

PCInterfaceName const _AliasingServer_InterfaceNamesList[] = 
{
    "IAliasingTest",
    0
};


#define _AliasingServer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _AliasingServer, pIID, n)

int __stdcall _AliasingServer_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_AliasingServer_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo AliasingServer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _AliasingServer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _AliasingServer_StubVtblList,
    (const PCInterfaceName * ) & _AliasingServer_InterfaceNamesList,
    0, /* no delegation */
    & _AliasingServer_IID_Lookup, 
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

