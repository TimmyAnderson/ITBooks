

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Aug 09 22:52:30 2012
 */
/* Compiler settings for ArraysServer.idl:
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


#include "ArraysServer_h.h"

#define TYPE_FORMAT_STRING_SIZE   1319                              
#define PROC_FORMAT_STRING_SIZE   1041                              
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

typedef struct _ArraysServer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } ArraysServer_MIDL_TYPE_FORMAT_STRING;

typedef struct _ArraysServer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } ArraysServer_MIDL_PROC_FORMAT_STRING;

typedef struct _ArraysServer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } ArraysServer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const ArraysServer_MIDL_TYPE_FORMAT_STRING ArraysServer__MIDL_TypeFormatString;
extern const ArraysServer_MIDL_PROC_FORMAT_STRING ArraysServer__MIDL_ProcFormatString;
extern const ArraysServer_MIDL_EXPR_FORMAT_STRING ArraysServer__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IArraysTest_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IArraysTest_ProxyInfo;


extern const EXPR_EVAL ExprEvalRoutines[];
extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const ArraysServer_MIDL_PROC_FORMAT_STRING ArraysServer__MIDL_ProcFormatString =
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

	/* Procedure JustPointer */

/* 32 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 34 */	NdrFcLong( 0x0 ),	/* 0 */
/* 38 */	NdrFcShort( 0x4 ),	/* 4 */
/* 40 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 42 */	NdrFcShort( 0x1c ),	/* 28 */
/* 44 */	NdrFcShort( 0x8 ),	/* 8 */
/* 46 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 48 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 50 */	NdrFcShort( 0x0 ),	/* 0 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Array */

/* 58 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 60 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 62 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 64 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 66 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 68 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FixedArray */

/* 70 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 72 */	NdrFcLong( 0x0 ),	/* 0 */
/* 76 */	NdrFcShort( 0x5 ),	/* 5 */
/* 78 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 80 */	NdrFcShort( 0x38 ),	/* 56 */
/* 82 */	NdrFcShort( 0x8 ),	/* 8 */
/* 84 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 86 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 88 */	NdrFcShort( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0x0 ),	/* 0 */
/* 92 */	NdrFcShort( 0x0 ),	/* 0 */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Array */

/* 96 */	NdrFcShort( 0xa ),	/* Flags:  must free, in, */
/* 98 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 100 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 102 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 104 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SizeIs1 */

/* 108 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 110 */	NdrFcLong( 0x0 ),	/* 0 */
/* 114 */	NdrFcShort( 0x6 ),	/* 6 */
/* 116 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 118 */	NdrFcShort( 0x8 ),	/* 8 */
/* 120 */	NdrFcShort( 0x8 ),	/* 8 */
/* 122 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 124 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 128 */	NdrFcShort( 0x1 ),	/* 1 */
/* 130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 132 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ArraySize */

/* 134 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 136 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 138 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Array */

/* 140 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 142 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 144 */	NdrFcShort( 0x10 ),	/* Type Offset=16 */

	/* Return value */

/* 146 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 148 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 150 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SizeIs2 */

/* 152 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 154 */	NdrFcLong( 0x0 ),	/* 0 */
/* 158 */	NdrFcShort( 0x7 ),	/* 7 */
/* 160 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 162 */	NdrFcShort( 0x8 ),	/* 8 */
/* 164 */	NdrFcShort( 0x8 ),	/* 8 */
/* 166 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 168 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 170 */	NdrFcShort( 0x0 ),	/* 0 */
/* 172 */	NdrFcShort( 0x1 ),	/* 1 */
/* 174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 176 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ArraySize */

/* 178 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 180 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 182 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Array */

/* 184 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 186 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 188 */	NdrFcShort( 0x10 ),	/* Type Offset=16 */

	/* Return value */

/* 190 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 192 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 194 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SizeIs3 */

/* 196 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 198 */	NdrFcLong( 0x0 ),	/* 0 */
/* 202 */	NdrFcShort( 0x8 ),	/* 8 */
/* 204 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 206 */	NdrFcShort( 0x8 ),	/* 8 */
/* 208 */	NdrFcShort( 0x8 ),	/* 8 */
/* 210 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 212 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 216 */	NdrFcShort( 0x1 ),	/* 1 */
/* 218 */	NdrFcShort( 0x0 ),	/* 0 */
/* 220 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ArraySize */

/* 222 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 224 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 226 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Array */

/* 228 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 230 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 232 */	NdrFcShort( 0x10 ),	/* Type Offset=16 */

	/* Return value */

/* 234 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 236 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 238 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SizeIsExpression */

/* 240 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 242 */	NdrFcLong( 0x0 ),	/* 0 */
/* 246 */	NdrFcShort( 0x9 ),	/* 9 */
/* 248 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 250 */	NdrFcShort( 0x10 ),	/* 16 */
/* 252 */	NdrFcShort( 0x8 ),	/* 8 */
/* 254 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 256 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 258 */	NdrFcShort( 0x0 ),	/* 0 */
/* 260 */	NdrFcShort( 0x1 ),	/* 1 */
/* 262 */	NdrFcShort( 0x0 ),	/* 0 */
/* 264 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ArraySize1 */

/* 266 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 268 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 270 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ArraySize2 */

/* 272 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 274 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 276 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Array */

/* 278 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 280 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 282 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 284 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 286 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 288 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SizeIsInStruct */

/* 290 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 292 */	NdrFcLong( 0x0 ),	/* 0 */
/* 296 */	NdrFcShort( 0xa ),	/* 10 */
/* 298 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 300 */	NdrFcShort( 0x0 ),	/* 0 */
/* 302 */	NdrFcShort( 0x8 ),	/* 8 */
/* 304 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 306 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 308 */	NdrFcShort( 0x0 ),	/* 0 */
/* 310 */	NdrFcShort( 0x1 ),	/* 1 */
/* 312 */	NdrFcShort( 0x0 ),	/* 0 */
/* 314 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Array */

/* 316 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 318 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 320 */	NdrFcShort( 0x38 ),	/* Type Offset=56 */

	/* Return value */

/* 322 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 324 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 326 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SizeIsConstant */

/* 328 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 330 */	NdrFcLong( 0x0 ),	/* 0 */
/* 334 */	NdrFcShort( 0xb ),	/* 11 */
/* 336 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 338 */	NdrFcShort( 0x0 ),	/* 0 */
/* 340 */	NdrFcShort( 0x8 ),	/* 8 */
/* 342 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 344 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 348 */	NdrFcShort( 0x1 ),	/* 1 */
/* 350 */	NdrFcShort( 0x0 ),	/* 0 */
/* 352 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Array */

/* 354 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 356 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 358 */	NdrFcShort( 0x4c ),	/* Type Offset=76 */

	/* Return value */

/* 360 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 362 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 364 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MaxIsConstant */

/* 366 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 368 */	NdrFcLong( 0x0 ),	/* 0 */
/* 372 */	NdrFcShort( 0xc ),	/* 12 */
/* 374 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 376 */	NdrFcShort( 0x0 ),	/* 0 */
/* 378 */	NdrFcShort( 0x8 ),	/* 8 */
/* 380 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 382 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 384 */	NdrFcShort( 0x0 ),	/* 0 */
/* 386 */	NdrFcShort( 0x1 ),	/* 1 */
/* 388 */	NdrFcShort( 0x0 ),	/* 0 */
/* 390 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Array */

/* 392 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 394 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 396 */	NdrFcShort( 0x5c ),	/* Type Offset=92 */

	/* Return value */

/* 398 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 400 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 402 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SizeIsForOutputParameter */

/* 404 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 406 */	NdrFcLong( 0x0 ),	/* 0 */
/* 410 */	NdrFcShort( 0xd ),	/* 13 */
/* 412 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 414 */	NdrFcShort( 0x8 ),	/* 8 */
/* 416 */	NdrFcShort( 0x8 ),	/* 8 */
/* 418 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 420 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 422 */	NdrFcShort( 0x1 ),	/* 1 */
/* 424 */	NdrFcShort( 0x0 ),	/* 0 */
/* 426 */	NdrFcShort( 0x0 ),	/* 0 */
/* 428 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ArraySize */

/* 430 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 432 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 434 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Array */

/* 436 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 438 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 440 */	NdrFcShort( 0x10 ),	/* Type Offset=16 */

	/* Return value */

/* 442 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 444 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 446 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SizeIsForOutputStringParameter */

/* 448 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 450 */	NdrFcLong( 0x0 ),	/* 0 */
/* 454 */	NdrFcShort( 0xe ),	/* 14 */
/* 456 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 458 */	NdrFcShort( 0x8 ),	/* 8 */
/* 460 */	NdrFcShort( 0x8 ),	/* 8 */
/* 462 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 464 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 466 */	NdrFcShort( 0x1 ),	/* 1 */
/* 468 */	NdrFcShort( 0x0 ),	/* 0 */
/* 470 */	NdrFcShort( 0x0 ),	/* 0 */
/* 472 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ArraySize */

/* 474 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 476 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 478 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Array */

/* 480 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 482 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 484 */	NdrFcShort( 0x6c ),	/* Type Offset=108 */

	/* Return value */

/* 486 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 488 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 490 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LengthIs */

/* 492 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 494 */	NdrFcLong( 0x0 ),	/* 0 */
/* 498 */	NdrFcShort( 0xf ),	/* 15 */
/* 500 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 502 */	NdrFcShort( 0x8 ),	/* 8 */
/* 504 */	NdrFcShort( 0x8 ),	/* 8 */
/* 506 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 508 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 510 */	NdrFcShort( 0x0 ),	/* 0 */
/* 512 */	NdrFcShort( 0x1 ),	/* 1 */
/* 514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 516 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ArrayLength */

/* 518 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 520 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 522 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Array */

/* 524 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 526 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 528 */	NdrFcShort( 0x78 ),	/* Type Offset=120 */

	/* Return value */

/* 530 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 532 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 534 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FirstIs */

/* 536 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 538 */	NdrFcLong( 0x0 ),	/* 0 */
/* 542 */	NdrFcShort( 0x10 ),	/* 16 */
/* 544 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 546 */	NdrFcShort( 0x10 ),	/* 16 */
/* 548 */	NdrFcShort( 0x8 ),	/* 8 */
/* 550 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 552 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 556 */	NdrFcShort( 0x1 ),	/* 1 */
/* 558 */	NdrFcShort( 0x0 ),	/* 0 */
/* 560 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter StartIndex */

/* 562 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 564 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 566 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ArrayLength */

/* 568 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 570 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 572 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Array */

/* 574 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 576 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 578 */	NdrFcShort( 0x88 ),	/* Type Offset=136 */

	/* Return value */

/* 580 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 582 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 584 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LastIs */

/* 586 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 588 */	NdrFcLong( 0x0 ),	/* 0 */
/* 592 */	NdrFcShort( 0x11 ),	/* 17 */
/* 594 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 596 */	NdrFcShort( 0x10 ),	/* 16 */
/* 598 */	NdrFcShort( 0x8 ),	/* 8 */
/* 600 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 602 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 604 */	NdrFcShort( 0x0 ),	/* 0 */
/* 606 */	NdrFcShort( 0x1 ),	/* 1 */
/* 608 */	NdrFcShort( 0x0 ),	/* 0 */
/* 610 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter StartIndex */

/* 612 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 614 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 616 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter EndIndex */

/* 618 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 620 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 622 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Array */

/* 624 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 626 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 628 */	NdrFcShort( 0x98 ),	/* Type Offset=152 */

	/* Return value */

/* 630 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 632 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 634 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LengthIsAndSizeIs */

/* 636 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 638 */	NdrFcLong( 0x0 ),	/* 0 */
/* 642 */	NdrFcShort( 0x12 ),	/* 18 */
/* 644 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 646 */	NdrFcShort( 0x10 ),	/* 16 */
/* 648 */	NdrFcShort( 0x8 ),	/* 8 */
/* 650 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 652 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 654 */	NdrFcShort( 0x0 ),	/* 0 */
/* 656 */	NdrFcShort( 0x1 ),	/* 1 */
/* 658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 660 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ArraySize */

/* 662 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 664 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 666 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ArrayLength */

/* 668 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 670 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 672 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Array */

/* 674 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 676 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 678 */	NdrFcShort( 0xac ),	/* Type Offset=172 */

	/* Return value */

/* 680 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 682 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 684 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LengthIsAndSizeIsForOutputParamerter */

/* 686 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 688 */	NdrFcLong( 0x0 ),	/* 0 */
/* 692 */	NdrFcShort( 0x13 ),	/* 19 */
/* 694 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 696 */	NdrFcShort( 0x8 ),	/* 8 */
/* 698 */	NdrFcShort( 0x24 ),	/* 36 */
/* 700 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 702 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 704 */	NdrFcShort( 0x1 ),	/* 1 */
/* 706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 710 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ArraySize */

/* 712 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 714 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 716 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ArrayLength */

/* 718 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 720 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 722 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Array */

/* 724 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 726 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 728 */	NdrFcShort( 0xc6 ),	/* Type Offset=198 */

	/* Return value */

/* 730 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 732 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 734 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PointerToPointer */

/* 736 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 738 */	NdrFcLong( 0x0 ),	/* 0 */
/* 742 */	NdrFcShort( 0x14 ),	/* 20 */
/* 744 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 746 */	NdrFcShort( 0x30 ),	/* 48 */
/* 748 */	NdrFcShort( 0x8 ),	/* 8 */
/* 750 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 752 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 756 */	NdrFcShort( 0x0 ),	/* 0 */
/* 758 */	NdrFcShort( 0x0 ),	/* 0 */
/* 760 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Array */

/* 762 */	NdrFcShort( 0x200a ),	/* Flags:  must free, in, srv alloc size=8 */
/* 764 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 766 */	NdrFcShort( 0xd8 ),	/* Type Offset=216 */

	/* Return value */

/* 768 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 770 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 772 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ArrayOfPointers */

/* 774 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 776 */	NdrFcLong( 0x0 ),	/* 0 */
/* 780 */	NdrFcShort( 0x15 ),	/* 21 */
/* 782 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 784 */	NdrFcShort( 0x0 ),	/* 0 */
/* 786 */	NdrFcShort( 0x8 ),	/* 8 */
/* 788 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 790 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 794 */	NdrFcShort( 0x1 ),	/* 1 */
/* 796 */	NdrFcShort( 0x0 ),	/* 0 */
/* 798 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Array */

/* 800 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 802 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 804 */	NdrFcShort( 0xe4 ),	/* Type Offset=228 */

	/* Return value */

/* 806 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 808 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 810 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PointerToArray */

/* 812 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 814 */	NdrFcLong( 0x0 ),	/* 0 */
/* 818 */	NdrFcShort( 0x16 ),	/* 22 */
/* 820 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 822 */	NdrFcShort( 0x0 ),	/* 0 */
/* 824 */	NdrFcShort( 0x8 ),	/* 8 */
/* 826 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 828 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 832 */	NdrFcShort( 0x1 ),	/* 1 */
/* 834 */	NdrFcShort( 0x0 ),	/* 0 */
/* 836 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Array */

/* 838 */	NdrFcShort( 0x200b ),	/* Flags:  must size, must free, in, srv alloc size=8 */
/* 840 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 842 */	NdrFcShort( 0xfa ),	/* Type Offset=250 */

	/* Return value */

/* 844 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 846 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 848 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ArrayToArray */

/* 850 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 852 */	NdrFcLong( 0x0 ),	/* 0 */
/* 856 */	NdrFcShort( 0x17 ),	/* 23 */
/* 858 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 860 */	NdrFcShort( 0x0 ),	/* 0 */
/* 862 */	NdrFcShort( 0x8 ),	/* 8 */
/* 864 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 866 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 868 */	NdrFcShort( 0x0 ),	/* 0 */
/* 870 */	NdrFcShort( 0x1 ),	/* 1 */
/* 872 */	NdrFcShort( 0x0 ),	/* 0 */
/* 874 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Array */

/* 876 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 878 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 880 */	NdrFcShort( 0x112 ),	/* Type Offset=274 */

	/* Return value */

/* 882 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 884 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 886 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Matrix */

/* 888 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 890 */	NdrFcLong( 0x0 ),	/* 0 */
/* 894 */	NdrFcShort( 0x18 ),	/* 24 */
/* 896 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 898 */	NdrFcShort( 0x60 ),	/* 96 */
/* 900 */	NdrFcShort( 0x8 ),	/* 8 */
/* 902 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 904 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 906 */	NdrFcShort( 0x0 ),	/* 0 */
/* 908 */	NdrFcShort( 0x0 ),	/* 0 */
/* 910 */	NdrFcShort( 0x0 ),	/* 0 */
/* 912 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Array */

/* 914 */	NdrFcShort( 0xa ),	/* Flags:  must free, in, */
/* 916 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 918 */	NdrFcShort( 0x12e ),	/* Type Offset=302 */

	/* Return value */

/* 920 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 922 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 924 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure String */

/* 926 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 928 */	NdrFcLong( 0x0 ),	/* 0 */
/* 932 */	NdrFcShort( 0x19 ),	/* 25 */
/* 934 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 936 */	NdrFcShort( 0x0 ),	/* 0 */
/* 938 */	NdrFcShort( 0x8 ),	/* 8 */
/* 940 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 942 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 944 */	NdrFcShort( 0x0 ),	/* 0 */
/* 946 */	NdrFcShort( 0x0 ),	/* 0 */
/* 948 */	NdrFcShort( 0x0 ),	/* 0 */
/* 950 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter String */

/* 952 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 954 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 956 */	NdrFcShort( 0x13a ),	/* Type Offset=314 */

	/* Return value */

/* 958 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 960 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 962 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OutputString */

/* 964 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 966 */	NdrFcLong( 0x0 ),	/* 0 */
/* 970 */	NdrFcShort( 0x1a ),	/* 26 */
/* 972 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 974 */	NdrFcShort( 0x0 ),	/* 0 */
/* 976 */	NdrFcShort( 0x8 ),	/* 8 */
/* 978 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 980 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 982 */	NdrFcShort( 0x0 ),	/* 0 */
/* 984 */	NdrFcShort( 0x0 ),	/* 0 */
/* 986 */	NdrFcShort( 0x0 ),	/* 0 */
/* 988 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter String */

/* 990 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 992 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 994 */	NdrFcShort( 0x13c ),	/* Type Offset=316 */

	/* Return value */

/* 996 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 998 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1000 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SafeArrayInt */

/* 1002 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1004 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1008 */	NdrFcShort( 0x1b ),	/* 27 */
/* 1010 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1012 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1014 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1016 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1018 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1020 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1022 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1024 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1026 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Array */

/* 1028 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1030 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1032 */	NdrFcShort( 0x51c ),	/* Type Offset=1308 */

	/* Return value */

/* 1034 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1036 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1038 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const ArraysServer_MIDL_TYPE_FORMAT_STRING ArraysServer__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  4 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x1d,		/* FC_SMFARRAY */
			0x3,		/* 3 */
/*  8 */	NdrFcShort( 0x28 ),	/* 40 */
/* 10 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 12 */	
			0x11, 0x0,	/* FC_RP */
/* 14 */	NdrFcShort( 0x2 ),	/* Offset= 2 (16) */
/* 16 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 18 */	NdrFcShort( 0x4 ),	/* 4 */
/* 20 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 22 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 24 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 26 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 28 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 30 */	NdrFcShort( 0x4 ),	/* 4 */
/* 32 */	0x20,		/* Corr desc:  parameter,  */
			0x59,		/* FC_CALLBACK */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 38 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 40 */	
			0x11, 0x0,	/* FC_RP */
/* 42 */	NdrFcShort( 0xe ),	/* Offset= 14 (56) */
/* 44 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 46 */	NdrFcShort( 0x4 ),	/* 4 */
/* 48 */	0x18,		/* Corr desc:  field pointer, FC_LONG */
			0x0,		/*  */
/* 50 */	NdrFcShort( 0x0 ),	/* 0 */
/* 52 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 54 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 56 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 58 */	NdrFcShort( 0x10 ),	/* 16 */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x6 ),	/* Offset= 6 (68) */
/* 64 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 66 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 68 */	
			0x12, 0x0,	/* FC_UP */
/* 70 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (44) */
/* 72 */	
			0x11, 0x0,	/* FC_RP */
/* 74 */	NdrFcShort( 0x2 ),	/* Offset= 2 (76) */
/* 76 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 78 */	NdrFcShort( 0x4 ),	/* 4 */
/* 80 */	0x40,		/* Corr desc:  constant, val=10 */
			0x0,		/* 0 */
/* 82 */	NdrFcShort( 0xa ),	/* 10 */
/* 84 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 86 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 88 */	
			0x11, 0x0,	/* FC_RP */
/* 90 */	NdrFcShort( 0x2 ),	/* Offset= 2 (92) */
/* 92 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 94 */	NdrFcShort( 0x4 ),	/* 4 */
/* 96 */	0x40,		/* Corr desc:  constant, val=9 */
			0x0,		/* 0 */
/* 98 */	NdrFcShort( 0x9 ),	/* 9 */
/* 100 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 102 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 104 */	
			0x11, 0x0,	/* FC_RP */
/* 106 */	NdrFcShort( 0x2 ),	/* Offset= 2 (108) */
/* 108 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 110 */	NdrFcShort( 0x2 ),	/* 2 */
/* 112 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 114 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 116 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 118 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 120 */	
			0x1f,		/* FC_SMVARRAY */
			0x3,		/* 3 */
/* 122 */	NdrFcShort( 0x50 ),	/* 80 */
/* 124 */	NdrFcShort( 0x14 ),	/* 20 */
/* 126 */	NdrFcShort( 0x4 ),	/* 4 */
/* 128 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 130 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 132 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 134 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 136 */	
			0x1f,		/* FC_SMVARRAY */
			0x3,		/* 3 */
/* 138 */	NdrFcShort( 0x50 ),	/* 80 */
/* 140 */	NdrFcShort( 0x14 ),	/* 20 */
/* 142 */	NdrFcShort( 0x4 ),	/* 4 */
/* 144 */	0x20,		/* Corr desc:  parameter,  */
			0x59,		/* FC_CALLBACK */
/* 146 */	NdrFcShort( 0x1 ),	/* 1 */
/* 148 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 150 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 152 */	
			0x1f,		/* FC_SMVARRAY */
			0x3,		/* 3 */
/* 154 */	NdrFcShort( 0x50 ),	/* 80 */
/* 156 */	NdrFcShort( 0x14 ),	/* 20 */
/* 158 */	NdrFcShort( 0x4 ),	/* 4 */
/* 160 */	0x20,		/* Corr desc:  parameter,  */
			0x59,		/* FC_CALLBACK */
/* 162 */	NdrFcShort( 0x2 ),	/* 2 */
/* 164 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 166 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 168 */	
			0x11, 0x0,	/* FC_RP */
/* 170 */	NdrFcShort( 0x2 ),	/* Offset= 2 (172) */
/* 172 */	
			0x1c,		/* FC_CVARRAY */
			0x3,		/* 3 */
/* 174 */	NdrFcShort( 0x4 ),	/* 4 */
/* 176 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 178 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 180 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 182 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 184 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 186 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 188 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 190 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 192 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 194 */	
			0x11, 0x0,	/* FC_RP */
/* 196 */	NdrFcShort( 0x2 ),	/* Offset= 2 (198) */
/* 198 */	
			0x1c,		/* FC_CVARRAY */
			0x3,		/* 3 */
/* 200 */	NdrFcShort( 0x4 ),	/* 4 */
/* 202 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 204 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 206 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 208 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x54,		/* FC_DEREFERENCE */
/* 210 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 212 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 214 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 216 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 218 */	NdrFcShort( 0x2 ),	/* Offset= 2 (220) */
/* 220 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 222 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 224 */	
			0x11, 0x0,	/* FC_RP */
/* 226 */	NdrFcShort( 0x2 ),	/* Offset= 2 (228) */
/* 228 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 230 */	NdrFcShort( 0x0 ),	/* 0 */
/* 232 */	0x40,		/* Corr desc:  constant, val=3 */
			0x0,		/* 0 */
/* 234 */	NdrFcShort( 0x3 ),	/* 3 */
/* 236 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 238 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 242 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 244 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 246 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 248 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 250 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 252 */	NdrFcShort( 0x2 ),	/* Offset= 2 (254) */
/* 254 */	
			0x12, 0x0,	/* FC_UP */
/* 256 */	NdrFcShort( 0x2 ),	/* Offset= 2 (258) */
/* 258 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 260 */	NdrFcShort( 0x4 ),	/* 4 */
/* 262 */	0x40,		/* Corr desc:  constant, val=4 */
			0x0,		/* 0 */
/* 264 */	NdrFcShort( 0x4 ),	/* 4 */
/* 266 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 268 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 270 */	
			0x11, 0x0,	/* FC_RP */
/* 272 */	NdrFcShort( 0x2 ),	/* Offset= 2 (274) */
/* 274 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 276 */	NdrFcShort( 0x0 ),	/* 0 */
/* 278 */	0x40,		/* Corr desc:  constant, val=3 */
			0x0,		/* 0 */
/* 280 */	NdrFcShort( 0x3 ),	/* 3 */
/* 282 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 284 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 288 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 290 */	
			0x12, 0x0,	/* FC_UP */
/* 292 */	NdrFcShort( 0xffde ),	/* Offset= -34 (258) */
/* 294 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 296 */	
			0x1d,		/* FC_SMFARRAY */
			0x3,		/* 3 */
/* 298 */	NdrFcShort( 0x10 ),	/* 16 */
/* 300 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 302 */	
			0x1d,		/* FC_SMFARRAY */
			0x3,		/* 3 */
/* 304 */	NdrFcShort( 0x30 ),	/* 48 */
/* 306 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 308 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (296) */
/* 310 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 312 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 314 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 316 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 318 */	NdrFcShort( 0x2 ),	/* Offset= 2 (320) */
/* 320 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 322 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 324 */	
			0x11, 0x0,	/* FC_RP */
/* 326 */	NdrFcShort( 0x3d6 ),	/* Offset= 982 (1308) */
/* 328 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 330 */	NdrFcShort( 0x2 ),	/* Offset= 2 (332) */
/* 332 */	
			0x12, 0x0,	/* FC_UP */
/* 334 */	NdrFcShort( 0x3bc ),	/* Offset= 956 (1290) */
/* 336 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x89,		/* 137 */
/* 338 */	NdrFcShort( 0x20 ),	/* 32 */
/* 340 */	NdrFcShort( 0xa ),	/* 10 */
/* 342 */	NdrFcLong( 0x8 ),	/* 8 */
/* 346 */	NdrFcShort( 0x66 ),	/* Offset= 102 (448) */
/* 348 */	NdrFcLong( 0xd ),	/* 13 */
/* 352 */	NdrFcShort( 0x98 ),	/* Offset= 152 (504) */
/* 354 */	NdrFcLong( 0x9 ),	/* 9 */
/* 358 */	NdrFcShort( 0xca ),	/* Offset= 202 (560) */
/* 360 */	NdrFcLong( 0xc ),	/* 12 */
/* 364 */	NdrFcShort( 0x2ba ),	/* Offset= 698 (1062) */
/* 366 */	NdrFcLong( 0x24 ),	/* 36 */
/* 370 */	NdrFcShort( 0x2da ),	/* Offset= 730 (1100) */
/* 372 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 376 */	NdrFcShort( 0x2f6 ),	/* Offset= 758 (1134) */
/* 378 */	NdrFcLong( 0x10 ),	/* 16 */
/* 382 */	NdrFcShort( 0x310 ),	/* Offset= 784 (1166) */
/* 384 */	NdrFcLong( 0x2 ),	/* 2 */
/* 388 */	NdrFcShort( 0x326 ),	/* Offset= 806 (1194) */
/* 390 */	NdrFcLong( 0x3 ),	/* 3 */
/* 394 */	NdrFcShort( 0x33c ),	/* Offset= 828 (1222) */
/* 396 */	NdrFcLong( 0x14 ),	/* 20 */
/* 400 */	NdrFcShort( 0x352 ),	/* Offset= 850 (1250) */
/* 402 */	NdrFcShort( 0xffff ),	/* Offset= -1 (401) */
/* 404 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 406 */	NdrFcShort( 0x2 ),	/* 2 */
/* 408 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 410 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 412 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 414 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 416 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 418 */	NdrFcShort( 0x8 ),	/* 8 */
/* 420 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (404) */
/* 422 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 424 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 426 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 430 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 432 */	NdrFcShort( 0x0 ),	/* 0 */
/* 434 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 436 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 440 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 442 */	
			0x12, 0x0,	/* FC_UP */
/* 444 */	NdrFcShort( 0xffe4 ),	/* Offset= -28 (416) */
/* 446 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 448 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 450 */	NdrFcShort( 0x10 ),	/* 16 */
/* 452 */	NdrFcShort( 0x0 ),	/* 0 */
/* 454 */	NdrFcShort( 0x6 ),	/* Offset= 6 (460) */
/* 456 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 458 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 460 */	
			0x11, 0x0,	/* FC_RP */
/* 462 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (426) */
/* 464 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 466 */	NdrFcLong( 0x0 ),	/* 0 */
/* 470 */	NdrFcShort( 0x0 ),	/* 0 */
/* 472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 474 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 476 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 478 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 480 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 482 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 486 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 488 */	NdrFcShort( 0x0 ),	/* 0 */
/* 490 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 492 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 496 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 498 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 500 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (464) */
/* 502 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 504 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 506 */	NdrFcShort( 0x10 ),	/* 16 */
/* 508 */	NdrFcShort( 0x0 ),	/* 0 */
/* 510 */	NdrFcShort( 0x6 ),	/* Offset= 6 (516) */
/* 512 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 514 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 516 */	
			0x11, 0x0,	/* FC_RP */
/* 518 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (482) */
/* 520 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 522 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 526 */	NdrFcShort( 0x0 ),	/* 0 */
/* 528 */	NdrFcShort( 0x0 ),	/* 0 */
/* 530 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 532 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 534 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 536 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 538 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 540 */	NdrFcShort( 0x0 ),	/* 0 */
/* 542 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 546 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 548 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 552 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 554 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 556 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (520) */
/* 558 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 560 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 562 */	NdrFcShort( 0x10 ),	/* 16 */
/* 564 */	NdrFcShort( 0x0 ),	/* 0 */
/* 566 */	NdrFcShort( 0x6 ),	/* Offset= 6 (572) */
/* 568 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 570 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 572 */	
			0x11, 0x0,	/* FC_RP */
/* 574 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (538) */
/* 576 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 578 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 580 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 582 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 584 */	NdrFcShort( 0x2 ),	/* Offset= 2 (586) */
/* 586 */	NdrFcShort( 0x10 ),	/* 16 */
/* 588 */	NdrFcShort( 0x2f ),	/* 47 */
/* 590 */	NdrFcLong( 0x14 ),	/* 20 */
/* 594 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 596 */	NdrFcLong( 0x3 ),	/* 3 */
/* 600 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 602 */	NdrFcLong( 0x11 ),	/* 17 */
/* 606 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 608 */	NdrFcLong( 0x2 ),	/* 2 */
/* 612 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 614 */	NdrFcLong( 0x4 ),	/* 4 */
/* 618 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 620 */	NdrFcLong( 0x5 ),	/* 5 */
/* 624 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 626 */	NdrFcLong( 0xb ),	/* 11 */
/* 630 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 632 */	NdrFcLong( 0xa ),	/* 10 */
/* 636 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 638 */	NdrFcLong( 0x6 ),	/* 6 */
/* 642 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (874) */
/* 644 */	NdrFcLong( 0x7 ),	/* 7 */
/* 648 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 650 */	NdrFcLong( 0x8 ),	/* 8 */
/* 654 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (880) */
/* 656 */	NdrFcLong( 0xd ),	/* 13 */
/* 660 */	NdrFcShort( 0xff3c ),	/* Offset= -196 (464) */
/* 662 */	NdrFcLong( 0x9 ),	/* 9 */
/* 666 */	NdrFcShort( 0xff6e ),	/* Offset= -146 (520) */
/* 668 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 672 */	NdrFcShort( 0xd4 ),	/* Offset= 212 (884) */
/* 674 */	NdrFcLong( 0x24 ),	/* 36 */
/* 678 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (892) */
/* 680 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 684 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (892) */
/* 686 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 690 */	NdrFcShort( 0x100 ),	/* Offset= 256 (946) */
/* 692 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 696 */	NdrFcShort( 0xfe ),	/* Offset= 254 (950) */
/* 698 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 702 */	NdrFcShort( 0xfe1e ),	/* Offset= -482 (220) */
/* 704 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 708 */	NdrFcShort( 0xf6 ),	/* Offset= 246 (954) */
/* 710 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 714 */	NdrFcShort( 0xf4 ),	/* Offset= 244 (958) */
/* 716 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 720 */	NdrFcShort( 0xf2 ),	/* Offset= 242 (962) */
/* 722 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 726 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (950) */
/* 728 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 732 */	NdrFcShort( 0xfe00 ),	/* Offset= -512 (220) */
/* 734 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 738 */	NdrFcShort( 0xe4 ),	/* Offset= 228 (966) */
/* 740 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 744 */	NdrFcShort( 0xda ),	/* Offset= 218 (962) */
/* 746 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 750 */	NdrFcShort( 0xdc ),	/* Offset= 220 (970) */
/* 752 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 756 */	NdrFcShort( 0xda ),	/* Offset= 218 (974) */
/* 758 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 762 */	NdrFcShort( 0xd8 ),	/* Offset= 216 (978) */
/* 764 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 768 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (982) */
/* 770 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 774 */	NdrFcShort( 0xdc ),	/* Offset= 220 (994) */
/* 776 */	NdrFcLong( 0x10 ),	/* 16 */
/* 780 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 782 */	NdrFcLong( 0x12 ),	/* 18 */
/* 786 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 788 */	NdrFcLong( 0x13 ),	/* 19 */
/* 792 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 794 */	NdrFcLong( 0x15 ),	/* 21 */
/* 798 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 800 */	NdrFcLong( 0x16 ),	/* 22 */
/* 804 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 806 */	NdrFcLong( 0x17 ),	/* 23 */
/* 810 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 812 */	NdrFcLong( 0xe ),	/* 14 */
/* 816 */	NdrFcShort( 0xba ),	/* Offset= 186 (1002) */
/* 818 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 822 */	NdrFcShort( 0xbe ),	/* Offset= 190 (1012) */
/* 824 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 828 */	NdrFcShort( 0xbc ),	/* Offset= 188 (1016) */
/* 830 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 834 */	NdrFcShort( 0x74 ),	/* Offset= 116 (950) */
/* 836 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 840 */	NdrFcShort( 0xfd94 ),	/* Offset= -620 (220) */
/* 842 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 846 */	NdrFcShort( 0x6c ),	/* Offset= 108 (954) */
/* 848 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 852 */	NdrFcShort( 0xfd88 ),	/* Offset= -632 (220) */
/* 854 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 858 */	NdrFcShort( 0xfd82 ),	/* Offset= -638 (220) */
/* 860 */	NdrFcLong( 0x0 ),	/* 0 */
/* 864 */	NdrFcShort( 0x0 ),	/* Offset= 0 (864) */
/* 866 */	NdrFcLong( 0x1 ),	/* 1 */
/* 870 */	NdrFcShort( 0x0 ),	/* Offset= 0 (870) */
/* 872 */	NdrFcShort( 0xffff ),	/* Offset= -1 (871) */
/* 874 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 876 */	NdrFcShort( 0x8 ),	/* 8 */
/* 878 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 880 */	
			0x12, 0x0,	/* FC_UP */
/* 882 */	NdrFcShort( 0xfe2e ),	/* Offset= -466 (416) */
/* 884 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 886 */	NdrFcShort( 0x2 ),	/* Offset= 2 (888) */
/* 888 */	
			0x12, 0x0,	/* FC_UP */
/* 890 */	NdrFcShort( 0x190 ),	/* Offset= 400 (1290) */
/* 892 */	
			0x12, 0x0,	/* FC_UP */
/* 894 */	NdrFcShort( 0x20 ),	/* Offset= 32 (926) */
/* 896 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 898 */	NdrFcLong( 0x2f ),	/* 47 */
/* 902 */	NdrFcShort( 0x0 ),	/* 0 */
/* 904 */	NdrFcShort( 0x0 ),	/* 0 */
/* 906 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 908 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 910 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 912 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 914 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 916 */	NdrFcShort( 0x1 ),	/* 1 */
/* 918 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 920 */	NdrFcShort( 0x4 ),	/* 4 */
/* 922 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 924 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 926 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 928 */	NdrFcShort( 0x18 ),	/* 24 */
/* 930 */	NdrFcShort( 0x0 ),	/* 0 */
/* 932 */	NdrFcShort( 0xa ),	/* Offset= 10 (942) */
/* 934 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 936 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 938 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (896) */
/* 940 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 942 */	
			0x12, 0x0,	/* FC_UP */
/* 944 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (914) */
/* 946 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 948 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 950 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 952 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 954 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 956 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 958 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 960 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 962 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 964 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 966 */	
			0x12, 0x0,	/* FC_UP */
/* 968 */	NdrFcShort( 0xffa2 ),	/* Offset= -94 (874) */
/* 970 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 972 */	NdrFcShort( 0xffa4 ),	/* Offset= -92 (880) */
/* 974 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 976 */	NdrFcShort( 0xfe00 ),	/* Offset= -512 (464) */
/* 978 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 980 */	NdrFcShort( 0xfe34 ),	/* Offset= -460 (520) */
/* 982 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 984 */	NdrFcShort( 0x2 ),	/* Offset= 2 (986) */
/* 986 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 988 */	NdrFcShort( 0x2 ),	/* Offset= 2 (990) */
/* 990 */	
			0x12, 0x0,	/* FC_UP */
/* 992 */	NdrFcShort( 0x12a ),	/* Offset= 298 (1290) */
/* 994 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 996 */	NdrFcShort( 0x2 ),	/* Offset= 2 (998) */
/* 998 */	
			0x12, 0x0,	/* FC_UP */
/* 1000 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1020) */
/* 1002 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 1004 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1006 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 1008 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 1010 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1012 */	
			0x12, 0x0,	/* FC_UP */
/* 1014 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1002) */
/* 1016 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1018 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 1020 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1022 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1024 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1026 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1026) */
/* 1028 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1030 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1032 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1034 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1036 */	NdrFcShort( 0xfe34 ),	/* Offset= -460 (576) */
/* 1038 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1040 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1042 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1044 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1046 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1048 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1050 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1054 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1056 */	
			0x12, 0x0,	/* FC_UP */
/* 1058 */	NdrFcShort( 0xffda ),	/* Offset= -38 (1020) */
/* 1060 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1062 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1064 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1066 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1068 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1074) */
/* 1070 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1072 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1074 */	
			0x11, 0x0,	/* FC_RP */
/* 1076 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (1040) */
/* 1078 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1080 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1082 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1084 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1086 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1088 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1092 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1094 */	
			0x12, 0x0,	/* FC_UP */
/* 1096 */	NdrFcShort( 0xff56 ),	/* Offset= -170 (926) */
/* 1098 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1100 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1102 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1106 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1112) */
/* 1108 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1110 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1112 */	
			0x11, 0x0,	/* FC_RP */
/* 1114 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (1078) */
/* 1116 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 1118 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1120 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 1122 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 1124 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1126 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 1128 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1130 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (1116) */
			0x5b,		/* FC_END */
/* 1134 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1136 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1140 */	NdrFcShort( 0xa ),	/* Offset= 10 (1150) */
/* 1142 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1144 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1146 */	0x0,		/* 0 */
			NdrFcShort( 0xffe7 ),	/* Offset= -25 (1122) */
			0x5b,		/* FC_END */
/* 1150 */	
			0x11, 0x0,	/* FC_RP */
/* 1152 */	NdrFcShort( 0xfd62 ),	/* Offset= -670 (482) */
/* 1154 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1156 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1158 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1162 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1164 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 1166 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1168 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1170 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1172 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1178) */
/* 1174 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1176 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1178 */	
			0x12, 0x0,	/* FC_UP */
/* 1180 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (1154) */
/* 1182 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 1184 */	NdrFcShort( 0x2 ),	/* 2 */
/* 1186 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1190 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1192 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 1194 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1196 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1200 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1206) */
/* 1202 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1204 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1206 */	
			0x12, 0x0,	/* FC_UP */
/* 1208 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (1182) */
/* 1210 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1212 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1214 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1216 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1218 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1220 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 1222 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1224 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1226 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1228 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1234) */
/* 1230 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1232 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1234 */	
			0x12, 0x0,	/* FC_UP */
/* 1236 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (1210) */
/* 1238 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 1240 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1242 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1246 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1248 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1250 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1252 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1254 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1256 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1262) */
/* 1258 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1260 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1262 */	
			0x12, 0x0,	/* FC_UP */
/* 1264 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (1238) */
/* 1266 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 1268 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1270 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1272 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1274 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1276 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1278 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 1280 */	NdrFcShort( 0xffc8 ),	/* -56 */
/* 1282 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1284 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1286 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1266) */
/* 1288 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1290 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1292 */	NdrFcShort( 0x38 ),	/* 56 */
/* 1294 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1274) */
/* 1296 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1296) */
/* 1298 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1300 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1302 */	0x40,		/* FC_STRUCTPAD4 */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1304 */	0x0,		/* 0 */
			NdrFcShort( 0xfc37 ),	/* Offset= -969 (336) */
			0x5b,		/* FC_END */
/* 1308 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1310 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1312 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1314 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1316 */	NdrFcShort( 0xfc24 ),	/* Offset= -988 (328) */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            LPSAFEARRAY_UserSize
            ,LPSAFEARRAY_UserMarshal
            ,LPSAFEARRAY_UserUnmarshal
            ,LPSAFEARRAY_UserFree
            }

        };


static void __RPC_USER IArraysTest_SizeIsExpressionExprEval_0000( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(8)
    struct _PARAM_STRUCT
        {
        IArraysTest *This;
        int ArraySize1;
        char Pad0[4];
        int ArraySize2;
        char Pad1[4];
        int ( *Array )[  ];
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = 0;
    pStubMsg->MaxCount = (ULONG_PTR) ( ( pS->ArraySize1 < pS->ArraySize2 )  ? pS->ArraySize1 : pS->ArraySize2 );
}

static void __RPC_USER IArraysTest_FirstIsExprEval_0001( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(8)
    struct _PARAM_STRUCT
        {
        IArraysTest *This;
        int StartIndex;
        char Pad0[4];
        int ArrayLength;
        char Pad1[4];
        int ( *Array )[ 20 ];
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = pS->StartIndex;
    pStubMsg->MaxCount = (ULONG_PTR) ( pS->ArrayLength );
}

static void __RPC_USER IArraysTest_LastIsExprEval_0002( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(8)
    struct _PARAM_STRUCT
        {
        IArraysTest *This;
        int StartIndex;
        char Pad0[4];
        int EndIndex;
        char Pad1[4];
        int ( *Array )[ 20 ];
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = pS->StartIndex;
    pStubMsg->MaxCount = (ULONG_PTR) ( ( ( pS->EndIndex - pS->StartIndex )  + 1 )  );
}

static const EXPR_EVAL ExprEvalRoutines[] = 
    {
    IArraysTest_SizeIsExpressionExprEval_0000
    ,IArraysTest_FirstIsExprEval_0001
    ,IArraysTest_LastIsExprEval_0002
    };



/* Standard interface: __MIDL_itf_ArraysServer_0000_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IArraysTest, ver. 0.0,
   GUID={0xE408DA33,0x1FB3,0x4064,{0xBB,0x6E,0xF5,0xA0,0x56,0xAF,0xA9,0xA1}} */

#pragma code_seg(".orpc")
static const unsigned short IArraysTest_FormatStringOffsetTable[] =
    {
    0,
    32,
    70,
    108,
    152,
    196,
    240,
    290,
    328,
    366,
    404,
    448,
    492,
    536,
    586,
    636,
    686,
    736,
    774,
    812,
    850,
    888,
    926,
    964,
    1002
    };

static const MIDL_STUBLESS_PROXY_INFO IArraysTest_ProxyInfo =
    {
    &Object_StubDesc,
    ArraysServer__MIDL_ProcFormatString.Format,
    &IArraysTest_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IArraysTest_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    ArraysServer__MIDL_ProcFormatString.Format,
    &IArraysTest_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(28) _IArraysTestProxyVtbl = 
{
    &IArraysTest_ProxyInfo,
    &IID_IArraysTest,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IArraysTest::Dummy */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::JustPointer */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::FixedArray */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::SizeIs1 */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::SizeIs2 */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::SizeIs3 */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::SizeIsExpression */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::SizeIsInStruct */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::SizeIsConstant */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::MaxIsConstant */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::SizeIsForOutputParameter */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::SizeIsForOutputStringParameter */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::LengthIs */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::FirstIs */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::LastIs */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::LengthIsAndSizeIs */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::LengthIsAndSizeIsForOutputParamerter */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::PointerToPointer */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::ArrayOfPointers */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::PointerToArray */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::ArrayToArray */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::Matrix */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::String */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::OutputString */ ,
    (void *) (INT_PTR) -1 /* IArraysTest::SafeArrayInt */
};

const CInterfaceStubVtbl _IArraysTestStubVtbl =
{
    &IID_IArraysTest,
    &IArraysTest_ServerInfo,
    28,
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
    ExprEvalRoutines,
    0,
    ArraysServer__MIDL_TypeFormatString.Format,
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

const CInterfaceProxyVtbl * const _ArraysServer_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IArraysTestProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _ArraysServer_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IArraysTestStubVtbl,
    0
};

PCInterfaceName const _ArraysServer_InterfaceNamesList[] = 
{
    "IArraysTest",
    0
};


#define _ArraysServer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _ArraysServer, pIID, n)

int __stdcall _ArraysServer_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_ArraysServer_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo ArraysServer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _ArraysServer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _ArraysServer_StubVtblList,
    (const PCInterfaceName * ) & _ArraysServer_InterfaceNamesList,
    0, /* no delegation */
    & _ArraysServer_IID_Lookup, 
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

