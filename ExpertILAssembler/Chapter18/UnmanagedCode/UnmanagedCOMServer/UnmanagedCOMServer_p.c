

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sat Dec 28 00:04:55 2013
 */
/* Compiler settings for UnmanagedCOMServer.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
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


#include "UnmanagedCOMServer_h.h"

#define TYPE_FORMAT_STRING_SIZE   1067                              
#define PROC_FORMAT_STRING_SIZE   355                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _UnmanagedCOMServer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } UnmanagedCOMServer_MIDL_TYPE_FORMAT_STRING;

typedef struct _UnmanagedCOMServer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } UnmanagedCOMServer_MIDL_PROC_FORMAT_STRING;

typedef struct _UnmanagedCOMServer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } UnmanagedCOMServer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const UnmanagedCOMServer_MIDL_TYPE_FORMAT_STRING UnmanagedCOMServer__MIDL_TypeFormatString;
extern const UnmanagedCOMServer_MIDL_PROC_FORMAT_STRING UnmanagedCOMServer__MIDL_ProcFormatString;
extern const UnmanagedCOMServer_MIDL_EXPR_FORMAT_STRING UnmanagedCOMServer__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IUnmanagedCOMServerCallback_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IUnmanagedCOMServerCallback_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IUnmanagedCOMServer_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IUnmanagedCOMServer_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const UnmanagedCOMServer_MIDL_PROC_FORMAT_STRING UnmanagedCOMServer__MIDL_ProcFormatString =
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

	/* Procedure PrintMessage */

/* 146 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 148 */	NdrFcLong( 0x0 ),	/* 0 */
/* 152 */	NdrFcShort( 0x6 ),	/* 6 */
/* 154 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 156 */	NdrFcShort( 0x0 ),	/* 0 */
/* 158 */	NdrFcShort( 0x8 ),	/* 8 */
/* 160 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 162 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 164 */	NdrFcShort( 0x0 ),	/* 0 */
/* 166 */	NdrFcShort( 0x1 ),	/* 1 */
/* 168 */	NdrFcShort( 0x0 ),	/* 0 */
/* 170 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Message */

/* 172 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 174 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 176 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 178 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 180 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 182 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LoadName */

/* 184 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 186 */	NdrFcLong( 0x0 ),	/* 0 */
/* 190 */	NdrFcShort( 0x7 ),	/* 7 */
/* 192 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 196 */	NdrFcShort( 0x24 ),	/* 36 */
/* 198 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 200 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 202 */	NdrFcShort( 0x1 ),	/* 1 */
/* 204 */	NdrFcShort( 0x0 ),	/* 0 */
/* 206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 208 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Name */

/* 210 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 212 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 214 */	NdrFcShort( 0x40 ),	/* Type Offset=64 */

	/* Parameter Age */

/* 216 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 218 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 220 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 222 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 224 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 226 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SaveName */

/* 228 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 230 */	NdrFcLong( 0x0 ),	/* 0 */
/* 234 */	NdrFcShort( 0x8 ),	/* 8 */
/* 236 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 238 */	NdrFcShort( 0x8 ),	/* 8 */
/* 240 */	NdrFcShort( 0x8 ),	/* 8 */
/* 242 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 244 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 248 */	NdrFcShort( 0x1 ),	/* 1 */
/* 250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 252 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Name */

/* 254 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 256 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 258 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Parameter Age */

/* 260 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 262 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 264 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 266 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 268 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 270 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ArrayTest1 */

/* 272 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 274 */	NdrFcLong( 0x0 ),	/* 0 */
/* 278 */	NdrFcShort( 0x9 ),	/* 9 */
/* 280 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 282 */	NdrFcShort( 0x8 ),	/* 8 */
/* 284 */	NdrFcShort( 0x8 ),	/* 8 */
/* 286 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 288 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 290 */	NdrFcShort( 0x1 ),	/* 1 */
/* 292 */	NdrFcShort( 0x1 ),	/* 1 */
/* 294 */	NdrFcShort( 0x0 ),	/* 0 */
/* 296 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ArraySize */

/* 298 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 300 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 302 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Array */

/* 304 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 306 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 308 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 310 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 312 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 314 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ArrayTest2 */

/* 316 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 318 */	NdrFcLong( 0x0 ),	/* 0 */
/* 322 */	NdrFcShort( 0xa ),	/* 10 */
/* 324 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 328 */	NdrFcShort( 0x8 ),	/* 8 */
/* 330 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 332 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 334 */	NdrFcShort( 0x1 ),	/* 1 */
/* 336 */	NdrFcShort( 0x1 ),	/* 1 */
/* 338 */	NdrFcShort( 0x0 ),	/* 0 */
/* 340 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Array */

/* 342 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 344 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 346 */	NdrFcShort( 0x420 ),	/* Type Offset=1056 */

	/* Return value */

/* 348 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 350 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 352 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const UnmanagedCOMServer_MIDL_TYPE_FORMAT_STRING UnmanagedCOMServer__MIDL_TypeFormatString =
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
			0xfc,		/* 252 */
/* 56 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 58 */	NdrFcShort( 0x6 ),	/* Offset= 6 (64) */
/* 60 */	
			0x13, 0x0,	/* FC_OP */
/* 62 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (18) */
/* 64 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x8 ),	/* 8 */
/* 70 */	NdrFcShort( 0x0 ),	/* 0 */
/* 72 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (60) */
/* 74 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 76 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 78 */	
			0x11, 0x0,	/* FC_RP */
/* 80 */	NdrFcShort( 0x2 ),	/* Offset= 2 (82) */
/* 82 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 84 */	NdrFcShort( 0x4 ),	/* 4 */
/* 86 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 88 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 90 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 92 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 94 */	
			0x11, 0x0,	/* FC_RP */
/* 96 */	NdrFcShort( 0x3c0 ),	/* Offset= 960 (1056) */
/* 98 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 100 */	NdrFcShort( 0x2 ),	/* Offset= 2 (102) */
/* 102 */	
			0x13, 0x0,	/* FC_OP */
/* 104 */	NdrFcShort( 0x3a6 ),	/* Offset= 934 (1038) */
/* 106 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x89,		/* 137 */
/* 108 */	NdrFcShort( 0x20 ),	/* 32 */
/* 110 */	NdrFcShort( 0xa ),	/* 10 */
/* 112 */	NdrFcLong( 0x8 ),	/* 8 */
/* 116 */	NdrFcShort( 0x50 ),	/* Offset= 80 (196) */
/* 118 */	NdrFcLong( 0xd ),	/* 13 */
/* 122 */	NdrFcShort( 0x82 ),	/* Offset= 130 (252) */
/* 124 */	NdrFcLong( 0x9 ),	/* 9 */
/* 128 */	NdrFcShort( 0xb4 ),	/* Offset= 180 (308) */
/* 130 */	NdrFcLong( 0xc ),	/* 12 */
/* 134 */	NdrFcShort( 0x2a4 ),	/* Offset= 676 (810) */
/* 136 */	NdrFcLong( 0x24 ),	/* 36 */
/* 140 */	NdrFcShort( 0x2c4 ),	/* Offset= 708 (848) */
/* 142 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 146 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (882) */
/* 148 */	NdrFcLong( 0x10 ),	/* 16 */
/* 152 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (914) */
/* 154 */	NdrFcLong( 0x2 ),	/* 2 */
/* 158 */	NdrFcShort( 0x310 ),	/* Offset= 784 (942) */
/* 160 */	NdrFcLong( 0x3 ),	/* 3 */
/* 164 */	NdrFcShort( 0x326 ),	/* Offset= 806 (970) */
/* 166 */	NdrFcLong( 0x14 ),	/* 20 */
/* 170 */	NdrFcShort( 0x33c ),	/* Offset= 828 (998) */
/* 172 */	NdrFcShort( 0xffff ),	/* Offset= -1 (171) */
/* 174 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 176 */	NdrFcShort( 0x0 ),	/* 0 */
/* 178 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 180 */	NdrFcShort( 0x0 ),	/* 0 */
/* 182 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 184 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 188 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 190 */	
			0x13, 0x0,	/* FC_OP */
/* 192 */	NdrFcShort( 0xff52 ),	/* Offset= -174 (18) */
/* 194 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 196 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 198 */	NdrFcShort( 0x10 ),	/* 16 */
/* 200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 202 */	NdrFcShort( 0x6 ),	/* Offset= 6 (208) */
/* 204 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 206 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 208 */	
			0x11, 0x0,	/* FC_RP */
/* 210 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (174) */
/* 212 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 214 */	NdrFcLong( 0x0 ),	/* 0 */
/* 218 */	NdrFcShort( 0x0 ),	/* 0 */
/* 220 */	NdrFcShort( 0x0 ),	/* 0 */
/* 222 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 224 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 226 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 228 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 230 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 232 */	NdrFcShort( 0x0 ),	/* 0 */
/* 234 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 236 */	NdrFcShort( 0x0 ),	/* 0 */
/* 238 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 240 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 244 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 246 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 248 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (212) */
/* 250 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 252 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 254 */	NdrFcShort( 0x10 ),	/* 16 */
/* 256 */	NdrFcShort( 0x0 ),	/* 0 */
/* 258 */	NdrFcShort( 0x6 ),	/* Offset= 6 (264) */
/* 260 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 262 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 264 */	
			0x11, 0x0,	/* FC_RP */
/* 266 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (230) */
/* 268 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 270 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 274 */	NdrFcShort( 0x0 ),	/* 0 */
/* 276 */	NdrFcShort( 0x0 ),	/* 0 */
/* 278 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 280 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 282 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 284 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 286 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 288 */	NdrFcShort( 0x0 ),	/* 0 */
/* 290 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 292 */	NdrFcShort( 0x0 ),	/* 0 */
/* 294 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 296 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 300 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 302 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 304 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (268) */
/* 306 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 308 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 310 */	NdrFcShort( 0x10 ),	/* 16 */
/* 312 */	NdrFcShort( 0x0 ),	/* 0 */
/* 314 */	NdrFcShort( 0x6 ),	/* Offset= 6 (320) */
/* 316 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 318 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 320 */	
			0x11, 0x0,	/* FC_RP */
/* 322 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (286) */
/* 324 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 326 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 328 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 330 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 332 */	NdrFcShort( 0x2 ),	/* Offset= 2 (334) */
/* 334 */	NdrFcShort( 0x10 ),	/* 16 */
/* 336 */	NdrFcShort( 0x2f ),	/* 47 */
/* 338 */	NdrFcLong( 0x14 ),	/* 20 */
/* 342 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 344 */	NdrFcLong( 0x3 ),	/* 3 */
/* 348 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 350 */	NdrFcLong( 0x11 ),	/* 17 */
/* 354 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 356 */	NdrFcLong( 0x2 ),	/* 2 */
/* 360 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 362 */	NdrFcLong( 0x4 ),	/* 4 */
/* 366 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 368 */	NdrFcLong( 0x5 ),	/* 5 */
/* 372 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 374 */	NdrFcLong( 0xb ),	/* 11 */
/* 378 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 380 */	NdrFcLong( 0xa ),	/* 10 */
/* 384 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 386 */	NdrFcLong( 0x6 ),	/* 6 */
/* 390 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (622) */
/* 392 */	NdrFcLong( 0x7 ),	/* 7 */
/* 396 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 398 */	NdrFcLong( 0x8 ),	/* 8 */
/* 402 */	NdrFcShort( 0xfeaa ),	/* Offset= -342 (60) */
/* 404 */	NdrFcLong( 0xd ),	/* 13 */
/* 408 */	NdrFcShort( 0xff3c ),	/* Offset= -196 (212) */
/* 410 */	NdrFcLong( 0x9 ),	/* 9 */
/* 414 */	NdrFcShort( 0xff6e ),	/* Offset= -146 (268) */
/* 416 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 420 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (628) */
/* 422 */	NdrFcLong( 0x24 ),	/* 36 */
/* 426 */	NdrFcShort( 0xd2 ),	/* Offset= 210 (636) */
/* 428 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 432 */	NdrFcShort( 0xcc ),	/* Offset= 204 (636) */
/* 434 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 438 */	NdrFcShort( 0xfc ),	/* Offset= 252 (690) */
/* 440 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 444 */	NdrFcShort( 0xfa ),	/* Offset= 250 (694) */
/* 446 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 450 */	NdrFcShort( 0xf8 ),	/* Offset= 248 (698) */
/* 452 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 456 */	NdrFcShort( 0xf6 ),	/* Offset= 246 (702) */
/* 458 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 462 */	NdrFcShort( 0xf4 ),	/* Offset= 244 (706) */
/* 464 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 468 */	NdrFcShort( 0xf2 ),	/* Offset= 242 (710) */
/* 470 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 474 */	NdrFcShort( 0xdc ),	/* Offset= 220 (694) */
/* 476 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 480 */	NdrFcShort( 0xda ),	/* Offset= 218 (698) */
/* 482 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 486 */	NdrFcShort( 0xe4 ),	/* Offset= 228 (714) */
/* 488 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 492 */	NdrFcShort( 0xda ),	/* Offset= 218 (710) */
/* 494 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 498 */	NdrFcShort( 0xdc ),	/* Offset= 220 (718) */
/* 500 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 504 */	NdrFcShort( 0xda ),	/* Offset= 218 (722) */
/* 506 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 510 */	NdrFcShort( 0xd8 ),	/* Offset= 216 (726) */
/* 512 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 516 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (730) */
/* 518 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 522 */	NdrFcShort( 0xdc ),	/* Offset= 220 (742) */
/* 524 */	NdrFcLong( 0x10 ),	/* 16 */
/* 528 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 530 */	NdrFcLong( 0x12 ),	/* 18 */
/* 534 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 536 */	NdrFcLong( 0x13 ),	/* 19 */
/* 540 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 542 */	NdrFcLong( 0x15 ),	/* 21 */
/* 546 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 548 */	NdrFcLong( 0x16 ),	/* 22 */
/* 552 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 554 */	NdrFcLong( 0x17 ),	/* 23 */
/* 558 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 560 */	NdrFcLong( 0xe ),	/* 14 */
/* 564 */	NdrFcShort( 0xba ),	/* Offset= 186 (750) */
/* 566 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 570 */	NdrFcShort( 0xbe ),	/* Offset= 190 (760) */
/* 572 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 576 */	NdrFcShort( 0xbc ),	/* Offset= 188 (764) */
/* 578 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 582 */	NdrFcShort( 0x70 ),	/* Offset= 112 (694) */
/* 584 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 588 */	NdrFcShort( 0x6e ),	/* Offset= 110 (698) */
/* 590 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 594 */	NdrFcShort( 0x6c ),	/* Offset= 108 (702) */
/* 596 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 600 */	NdrFcShort( 0x62 ),	/* Offset= 98 (698) */
/* 602 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 606 */	NdrFcShort( 0x5c ),	/* Offset= 92 (698) */
/* 608 */	NdrFcLong( 0x0 ),	/* 0 */
/* 612 */	NdrFcShort( 0x0 ),	/* Offset= 0 (612) */
/* 614 */	NdrFcLong( 0x1 ),	/* 1 */
/* 618 */	NdrFcShort( 0x0 ),	/* Offset= 0 (618) */
/* 620 */	NdrFcShort( 0xffff ),	/* Offset= -1 (619) */
/* 622 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 624 */	NdrFcShort( 0x8 ),	/* 8 */
/* 626 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 628 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 630 */	NdrFcShort( 0x2 ),	/* Offset= 2 (632) */
/* 632 */	
			0x13, 0x0,	/* FC_OP */
/* 634 */	NdrFcShort( 0x194 ),	/* Offset= 404 (1038) */
/* 636 */	
			0x13, 0x0,	/* FC_OP */
/* 638 */	NdrFcShort( 0x20 ),	/* Offset= 32 (670) */
/* 640 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 642 */	NdrFcLong( 0x2f ),	/* 47 */
/* 646 */	NdrFcShort( 0x0 ),	/* 0 */
/* 648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 650 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 652 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 654 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 656 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 658 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 660 */	NdrFcShort( 0x1 ),	/* 1 */
/* 662 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 664 */	NdrFcShort( 0x4 ),	/* 4 */
/* 666 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 668 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 670 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 672 */	NdrFcShort( 0x18 ),	/* 24 */
/* 674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 676 */	NdrFcShort( 0xa ),	/* Offset= 10 (686) */
/* 678 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 680 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 682 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (640) */
/* 684 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 686 */	
			0x13, 0x0,	/* FC_OP */
/* 688 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (658) */
/* 690 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 692 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 694 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 696 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 698 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 700 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 702 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 704 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 706 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 708 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 710 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 712 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 714 */	
			0x13, 0x0,	/* FC_OP */
/* 716 */	NdrFcShort( 0xffa2 ),	/* Offset= -94 (622) */
/* 718 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 720 */	NdrFcShort( 0xfd6c ),	/* Offset= -660 (60) */
/* 722 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 724 */	NdrFcShort( 0xfe00 ),	/* Offset= -512 (212) */
/* 726 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 728 */	NdrFcShort( 0xfe34 ),	/* Offset= -460 (268) */
/* 730 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 732 */	NdrFcShort( 0x2 ),	/* Offset= 2 (734) */
/* 734 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 736 */	NdrFcShort( 0x2 ),	/* Offset= 2 (738) */
/* 738 */	
			0x13, 0x0,	/* FC_OP */
/* 740 */	NdrFcShort( 0x12a ),	/* Offset= 298 (1038) */
/* 742 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 744 */	NdrFcShort( 0x2 ),	/* Offset= 2 (746) */
/* 746 */	
			0x13, 0x0,	/* FC_OP */
/* 748 */	NdrFcShort( 0x14 ),	/* Offset= 20 (768) */
/* 750 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 752 */	NdrFcShort( 0x10 ),	/* 16 */
/* 754 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 756 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 758 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 760 */	
			0x13, 0x0,	/* FC_OP */
/* 762 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (750) */
/* 764 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 766 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 768 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 770 */	NdrFcShort( 0x20 ),	/* 32 */
/* 772 */	NdrFcShort( 0x0 ),	/* 0 */
/* 774 */	NdrFcShort( 0x0 ),	/* Offset= 0 (774) */
/* 776 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 778 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 780 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 782 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 784 */	NdrFcShort( 0xfe34 ),	/* Offset= -460 (324) */
/* 786 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 788 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 790 */	NdrFcShort( 0x0 ),	/* 0 */
/* 792 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 794 */	NdrFcShort( 0x0 ),	/* 0 */
/* 796 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 798 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 802 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 804 */	
			0x13, 0x0,	/* FC_OP */
/* 806 */	NdrFcShort( 0xffda ),	/* Offset= -38 (768) */
/* 808 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 810 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 812 */	NdrFcShort( 0x10 ),	/* 16 */
/* 814 */	NdrFcShort( 0x0 ),	/* 0 */
/* 816 */	NdrFcShort( 0x6 ),	/* Offset= 6 (822) */
/* 818 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 820 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 822 */	
			0x11, 0x0,	/* FC_RP */
/* 824 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (788) */
/* 826 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 828 */	NdrFcShort( 0x0 ),	/* 0 */
/* 830 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 832 */	NdrFcShort( 0x0 ),	/* 0 */
/* 834 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 836 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 840 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 842 */	
			0x13, 0x0,	/* FC_OP */
/* 844 */	NdrFcShort( 0xff52 ),	/* Offset= -174 (670) */
/* 846 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 848 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 850 */	NdrFcShort( 0x10 ),	/* 16 */
/* 852 */	NdrFcShort( 0x0 ),	/* 0 */
/* 854 */	NdrFcShort( 0x6 ),	/* Offset= 6 (860) */
/* 856 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 858 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 860 */	
			0x11, 0x0,	/* FC_RP */
/* 862 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (826) */
/* 864 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 866 */	NdrFcShort( 0x8 ),	/* 8 */
/* 868 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 870 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 872 */	NdrFcShort( 0x10 ),	/* 16 */
/* 874 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 876 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 878 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (864) */
			0x5b,		/* FC_END */
/* 882 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 884 */	NdrFcShort( 0x20 ),	/* 32 */
/* 886 */	NdrFcShort( 0x0 ),	/* 0 */
/* 888 */	NdrFcShort( 0xa ),	/* Offset= 10 (898) */
/* 890 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 892 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 894 */	0x0,		/* 0 */
			NdrFcShort( 0xffe7 ),	/* Offset= -25 (870) */
			0x5b,		/* FC_END */
/* 898 */	
			0x11, 0x0,	/* FC_RP */
/* 900 */	NdrFcShort( 0xfd62 ),	/* Offset= -670 (230) */
/* 902 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 904 */	NdrFcShort( 0x1 ),	/* 1 */
/* 906 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 908 */	NdrFcShort( 0x0 ),	/* 0 */
/* 910 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 912 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 914 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 916 */	NdrFcShort( 0x10 ),	/* 16 */
/* 918 */	NdrFcShort( 0x0 ),	/* 0 */
/* 920 */	NdrFcShort( 0x6 ),	/* Offset= 6 (926) */
/* 922 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 924 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 926 */	
			0x13, 0x0,	/* FC_OP */
/* 928 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (902) */
/* 930 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 932 */	NdrFcShort( 0x2 ),	/* 2 */
/* 934 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 936 */	NdrFcShort( 0x0 ),	/* 0 */
/* 938 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 940 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 942 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 944 */	NdrFcShort( 0x10 ),	/* 16 */
/* 946 */	NdrFcShort( 0x0 ),	/* 0 */
/* 948 */	NdrFcShort( 0x6 ),	/* Offset= 6 (954) */
/* 950 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 952 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 954 */	
			0x13, 0x0,	/* FC_OP */
/* 956 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (930) */
/* 958 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 960 */	NdrFcShort( 0x4 ),	/* 4 */
/* 962 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 964 */	NdrFcShort( 0x0 ),	/* 0 */
/* 966 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 968 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 970 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 972 */	NdrFcShort( 0x10 ),	/* 16 */
/* 974 */	NdrFcShort( 0x0 ),	/* 0 */
/* 976 */	NdrFcShort( 0x6 ),	/* Offset= 6 (982) */
/* 978 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 980 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 982 */	
			0x13, 0x0,	/* FC_OP */
/* 984 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (958) */
/* 986 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 988 */	NdrFcShort( 0x8 ),	/* 8 */
/* 990 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 992 */	NdrFcShort( 0x0 ),	/* 0 */
/* 994 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 996 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 998 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1000 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1004 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1010) */
/* 1006 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1008 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1010 */	
			0x13, 0x0,	/* FC_OP */
/* 1012 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (986) */
/* 1014 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 1016 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1018 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1020 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1022 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1024 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1026 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 1028 */	NdrFcShort( 0xffc8 ),	/* -56 */
/* 1030 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1032 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1034 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1014) */
/* 1036 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1038 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1040 */	NdrFcShort( 0x38 ),	/* 56 */
/* 1042 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1022) */
/* 1044 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1044) */
/* 1046 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1048 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1050 */	0x40,		/* FC_STRUCTPAD4 */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1052 */	0x0,		/* 0 */
			NdrFcShort( 0xfc4d ),	/* Offset= -947 (106) */
			0x5b,		/* FC_END */
/* 1056 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1058 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1060 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1062 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1064 */	NdrFcShort( 0xfc3a ),	/* Offset= -966 (98) */

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
            },
            {
            LPSAFEARRAY_UserSize
            ,LPSAFEARRAY_UserMarshal
            ,LPSAFEARRAY_UserUnmarshal
            ,LPSAFEARRAY_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IUnmanagedCOMServerCallback, ver. 0.0,
   GUID={0x69086C22,0x221F,0x4A29,{0x9F,0x91,0x2D,0x6E,0xB9,0xD1,0xEF,0xFC}} */

#pragma code_seg(".orpc")
static const unsigned short IUnmanagedCOMServerCallback_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IUnmanagedCOMServerCallback_ProxyInfo =
    {
    &Object_StubDesc,
    UnmanagedCOMServer__MIDL_ProcFormatString.Format,
    &IUnmanagedCOMServerCallback_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IUnmanagedCOMServerCallback_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    UnmanagedCOMServer__MIDL_ProcFormatString.Format,
    &IUnmanagedCOMServerCallback_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IUnmanagedCOMServerCallbackProxyVtbl = 
{
    &IUnmanagedCOMServerCallback_ProxyInfo,
    &IID_IUnmanagedCOMServerCallback,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IUnmanagedCOMServerCallback::SendMessageToClient */
};

const CInterfaceStubVtbl _IUnmanagedCOMServerCallbackStubVtbl =
{
    &IID_IUnmanagedCOMServerCallback,
    &IUnmanagedCOMServerCallback_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IUnmanagedCOMServer, ver. 0.0,
   GUID={0xDB83FED1,0xED27,0x425C,{0x87,0xB7,0xFF,0x50,0x36,0xC1,0xF0,0x8F}} */

#pragma code_seg(".orpc")
static const unsigned short IUnmanagedCOMServer_FormatStringOffsetTable[] =
    {
    38,
    76,
    108,
    146,
    184,
    228,
    272,
    316
    };

static const MIDL_STUBLESS_PROXY_INFO IUnmanagedCOMServer_ProxyInfo =
    {
    &Object_StubDesc,
    UnmanagedCOMServer__MIDL_ProcFormatString.Format,
    &IUnmanagedCOMServer_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IUnmanagedCOMServer_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    UnmanagedCOMServer__MIDL_ProcFormatString.Format,
    &IUnmanagedCOMServer_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IUnmanagedCOMServerProxyVtbl = 
{
    &IUnmanagedCOMServer_ProxyInfo,
    &IID_IUnmanagedCOMServer,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IUnmanagedCOMServer::RegisterCallback */ ,
    (void *) (INT_PTR) -1 /* IUnmanagedCOMServer::UnRegisterCallback */ ,
    (void *) (INT_PTR) -1 /* IUnmanagedCOMServer::SendMessageToServer */ ,
    (void *) (INT_PTR) -1 /* IUnmanagedCOMServer::PrintMessage */ ,
    (void *) (INT_PTR) -1 /* IUnmanagedCOMServer::LoadName */ ,
    (void *) (INT_PTR) -1 /* IUnmanagedCOMServer::SaveName */ ,
    (void *) (INT_PTR) -1 /* IUnmanagedCOMServer::ArrayTest1 */ ,
    (void *) (INT_PTR) -1 /* IUnmanagedCOMServer::ArrayTest2 */
};

const CInterfaceStubVtbl _IUnmanagedCOMServerStubVtbl =
{
    &IID_IUnmanagedCOMServer,
    &IUnmanagedCOMServer_ServerInfo,
    11,
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
    UnmanagedCOMServer__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x800025b, /* MIDL Version 8.0.603 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _UnmanagedCOMServer_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IUnmanagedCOMServerCallbackProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IUnmanagedCOMServerProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _UnmanagedCOMServer_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IUnmanagedCOMServerCallbackStubVtbl,
    ( CInterfaceStubVtbl *) &_IUnmanagedCOMServerStubVtbl,
    0
};

PCInterfaceName const _UnmanagedCOMServer_InterfaceNamesList[] = 
{
    "IUnmanagedCOMServerCallback",
    "IUnmanagedCOMServer",
    0
};


#define _UnmanagedCOMServer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _UnmanagedCOMServer, pIID, n)

int __stdcall _UnmanagedCOMServer_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _UnmanagedCOMServer, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _UnmanagedCOMServer, 2, *pIndex )
    
}

const ExtendedProxyFileInfo UnmanagedCOMServer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _UnmanagedCOMServer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _UnmanagedCOMServer_StubVtblList,
    (const PCInterfaceName * ) & _UnmanagedCOMServer_InterfaceNamesList,
    0, /* no delegation */
    & _UnmanagedCOMServer_IID_Lookup, 
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

