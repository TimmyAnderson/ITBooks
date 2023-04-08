

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 21:27:26 2012
 */
/* Compiler settings for OutOfProcessWithMarshallingServer.idl:
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


#include "OutOfProcessWithMarshallingServer_h.h"

#define TYPE_FORMAT_STRING_SIZE   27                                
#define PROC_FORMAT_STRING_SIZE   241                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _OutOfProcessWithMarshallingServer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } OutOfProcessWithMarshallingServer_MIDL_TYPE_FORMAT_STRING;

typedef struct _OutOfProcessWithMarshallingServer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } OutOfProcessWithMarshallingServer_MIDL_PROC_FORMAT_STRING;

typedef struct _OutOfProcessWithMarshallingServer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } OutOfProcessWithMarshallingServer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const OutOfProcessWithMarshallingServer_MIDL_TYPE_FORMAT_STRING OutOfProcessWithMarshallingServer__MIDL_TypeFormatString;
extern const OutOfProcessWithMarshallingServer_MIDL_PROC_FORMAT_STRING OutOfProcessWithMarshallingServer__MIDL_ProcFormatString;
extern const OutOfProcessWithMarshallingServer_MIDL_EXPR_FORMAT_STRING OutOfProcessWithMarshallingServer__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IName_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IName_ProxyInfo;



#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const OutOfProcessWithMarshallingServer_MIDL_PROC_FORMAT_STRING OutOfProcessWithMarshallingServer__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure SetFirstName */

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
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter FirstName */

/* 26 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 28 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 30 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Return value */

/* 32 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 34 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 36 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetLastName */

/* 38 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 40 */	NdrFcLong( 0x0 ),	/* 0 */
/* 44 */	NdrFcShort( 0x4 ),	/* 4 */
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

	/* Parameter LastName */

/* 64 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 66 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 68 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Return value */

/* 70 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 72 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 74 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetAge */

/* 76 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 78 */	NdrFcLong( 0x0 ),	/* 0 */
/* 82 */	NdrFcShort( 0x5 ),	/* 5 */
/* 84 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 86 */	NdrFcShort( 0x8 ),	/* 8 */
/* 88 */	NdrFcShort( 0x8 ),	/* 8 */
/* 90 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 92 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0x0 ),	/* 0 */
/* 98 */	NdrFcShort( 0x0 ),	/* 0 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Age */

/* 102 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 104 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 108 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 110 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetFirstName */

/* 114 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 116 */	NdrFcLong( 0x0 ),	/* 0 */
/* 120 */	NdrFcShort( 0x6 ),	/* 6 */
/* 122 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 124 */	NdrFcShort( 0x8 ),	/* 8 */
/* 126 */	NdrFcShort( 0x8 ),	/* 8 */
/* 128 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 130 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 132 */	NdrFcShort( 0x1 ),	/* 1 */
/* 134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 138 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter BufferSize */

/* 140 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 142 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 144 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter FirstName */

/* 146 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 148 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 150 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 152 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 154 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 156 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetLastName */

/* 158 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 160 */	NdrFcLong( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x7 ),	/* 7 */
/* 166 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 168 */	NdrFcShort( 0x8 ),	/* 8 */
/* 170 */	NdrFcShort( 0x8 ),	/* 8 */
/* 172 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 174 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 176 */	NdrFcShort( 0x1 ),	/* 1 */
/* 178 */	NdrFcShort( 0x0 ),	/* 0 */
/* 180 */	NdrFcShort( 0x0 ),	/* 0 */
/* 182 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter BufferSize */

/* 184 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 186 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 188 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter LastName */

/* 190 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 192 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 194 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 196 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 198 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 200 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetAge */

/* 202 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 204 */	NdrFcLong( 0x0 ),	/* 0 */
/* 208 */	NdrFcShort( 0x8 ),	/* 8 */
/* 210 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 214 */	NdrFcShort( 0x24 ),	/* 36 */
/* 216 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 218 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 220 */	NdrFcShort( 0x0 ),	/* 0 */
/* 222 */	NdrFcShort( 0x0 ),	/* 0 */
/* 224 */	NdrFcShort( 0x0 ),	/* 0 */
/* 226 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Age */

/* 228 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 230 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 232 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 234 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 236 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 238 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const OutOfProcessWithMarshallingServer_MIDL_TYPE_FORMAT_STRING OutOfProcessWithMarshallingServer__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  4 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x0,	/* FC_RP */
/*  8 */	NdrFcShort( 0x2 ),	/* Offset= 2 (10) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 18 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 20 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 22 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 24 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IName, ver. 0.0,
   GUID={0x21F82740,0x3C47,0x41B0,{0xAF,0x6B,0x6F,0x24,0x3D,0x3A,0xC7,0x9F}} */

#pragma code_seg(".orpc")
static const unsigned short IName_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    158,
    202
    };

static const MIDL_STUBLESS_PROXY_INFO IName_ProxyInfo =
    {
    &Object_StubDesc,
    OutOfProcessWithMarshallingServer__MIDL_ProcFormatString.Format,
    &IName_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IName_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    OutOfProcessWithMarshallingServer__MIDL_ProcFormatString.Format,
    &IName_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(9) _INameProxyVtbl = 
{
    &IName_ProxyInfo,
    &IID_IName,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IName::SetFirstName */ ,
    (void *) (INT_PTR) -1 /* IName::SetLastName */ ,
    (void *) (INT_PTR) -1 /* IName::SetAge */ ,
    (void *) (INT_PTR) -1 /* IName::GetFirstName */ ,
    (void *) (INT_PTR) -1 /* IName::GetLastName */ ,
    (void *) (INT_PTR) -1 /* IName::GetAge */
};

const CInterfaceStubVtbl _INameStubVtbl =
{
    &IID_IName,
    &IName_ServerInfo,
    9,
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
    OutOfProcessWithMarshallingServer__MIDL_TypeFormatString.Format,
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

const CInterfaceProxyVtbl * const _OutOfProcessWithMarshallingServer_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_INameProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _OutOfProcessWithMarshallingServer_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_INameStubVtbl,
    0
};

PCInterfaceName const _OutOfProcessWithMarshallingServer_InterfaceNamesList[] = 
{
    "IName",
    0
};


#define _OutOfProcessWithMarshallingServer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _OutOfProcessWithMarshallingServer, pIID, n)

int __stdcall _OutOfProcessWithMarshallingServer_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_OutOfProcessWithMarshallingServer_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo OutOfProcessWithMarshallingServer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _OutOfProcessWithMarshallingServer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _OutOfProcessWithMarshallingServer_StubVtblList,
    (const PCInterfaceName * ) & _OutOfProcessWithMarshallingServer_InterfaceNamesList,
    0, /* no delegation */
    & _OutOfProcessWithMarshallingServer_IID_Lookup, 
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

