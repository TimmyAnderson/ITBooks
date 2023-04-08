

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __AliasingServer_h_h__
#define __AliasingServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAliasingTest_FWD_DEFINED__
#define __IAliasingTest_FWD_DEFINED__
typedef interface IAliasingTest IAliasingTest;
#endif 	/* __IAliasingTest_FWD_DEFINED__ */


#ifndef __AliasingObject_FWD_DEFINED__
#define __AliasingObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class AliasingObject AliasingObject;
#else
typedef struct AliasingObject AliasingObject;
#endif /* __cplusplus */

#endif 	/* __AliasingObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_AliasingServer_0000_0000 */
/* [local] */ 

#ifndef XXXXX
#define XXXXX
void PrintText(void);
#endif


extern RPC_IF_HANDLE __MIDL_itf_AliasingServer_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AliasingServer_0000_0000_v0_0_s_ifspec;

#ifndef __IAliasingTest_INTERFACE_DEFINED__
#define __IAliasingTest_INTERFACE_DEFINED__

/* interface IAliasingTest */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAliasingTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B4B9C8FC-1C0C-4550-8D09-0ECA5900FB85")
    IAliasingTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Dummy( void) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE FillArray( 
            /* [in] */ int ArraySize,
            /* [out] */ int *ArrayLength,
            /* [out] */ int *Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CallFunctionDefinedByCPPQuote( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAliasingTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAliasingTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAliasingTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAliasingTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *Dummy )( 
            IAliasingTest * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *FillArray )( 
            IAliasingTest * This,
            /* [in] */ int ArraySize,
            /* [out] */ int *ArrayLength,
            /* [out] */ int *Array);
        
        HRESULT ( STDMETHODCALLTYPE *CallFunctionDefinedByCPPQuote )( 
            IAliasingTest * This);
        
        END_INTERFACE
    } IAliasingTestVtbl;

    interface IAliasingTest
    {
        CONST_VTBL struct IAliasingTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAliasingTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAliasingTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAliasingTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAliasingTest_Dummy(This)	\
    ( (This)->lpVtbl -> Dummy(This) ) 

#define IAliasingTest_FillArray(This,ArraySize,ArrayLength,Array)	\
    ( (This)->lpVtbl -> FillArray(This,ArraySize,ArrayLength,Array) ) 

#define IAliasingTest_CallFunctionDefinedByCPPQuote(This)	\
    ( (This)->lpVtbl -> CallFunctionDefinedByCPPQuote(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IAliasingTest_RemoteFillArray_Proxy( 
    IAliasingTest * This,
    /* [in] */ int ArraySize,
    /* [out] */ int *ArrayLength,
    /* [length_is][size_is][out] */ int *Array);


void __RPC_STUB IAliasingTest_RemoteFillArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAliasingTest_INTERFACE_DEFINED__ */



#ifndef __AliasingServerLib_LIBRARY_DEFINED__
#define __AliasingServerLib_LIBRARY_DEFINED__

/* library AliasingServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_AliasingServerLib;

EXTERN_C const CLSID CLSID_AliasingObject;

#ifdef __cplusplus

class DECLSPEC_UUID("5EF6C5A9-D07D-4B70-9544-15BB4B267F7B")
AliasingObject;
#endif
#endif /* __AliasingServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* [local] */ HRESULT STDMETHODCALLTYPE IAliasingTest_FillArray_Proxy( 
    IAliasingTest * This,
    /* [in] */ int ArraySize,
    /* [out] */ int *ArrayLength,
    /* [out] */ int *Array);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IAliasingTest_FillArray_Stub( 
    IAliasingTest * This,
    /* [in] */ int ArraySize,
    /* [out] */ int *ArrayLength,
    /* [length_is][size_is][out] */ int *Array);



/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


