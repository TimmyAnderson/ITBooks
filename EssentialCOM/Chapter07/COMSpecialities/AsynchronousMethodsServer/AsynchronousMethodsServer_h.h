

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#ifndef __AsynchronousMethodsServer_h_h__
#define __AsynchronousMethodsServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAsynchronousMethodsTest_FWD_DEFINED__
#define __IAsynchronousMethodsTest_FWD_DEFINED__
typedef interface IAsynchronousMethodsTest IAsynchronousMethodsTest;
#endif 	/* __IAsynchronousMethodsTest_FWD_DEFINED__ */


#ifndef __AsyncIAsynchronousMethodsTest_FWD_DEFINED__
#define __AsyncIAsynchronousMethodsTest_FWD_DEFINED__
typedef interface AsyncIAsynchronousMethodsTest AsyncIAsynchronousMethodsTest;
#endif 	/* __AsyncIAsynchronousMethodsTest_FWD_DEFINED__ */


#ifndef __AsynchronousMethodsObject_FWD_DEFINED__
#define __AsynchronousMethodsObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class AsynchronousMethodsObject AsynchronousMethodsObject;
#else
typedef struct AsynchronousMethodsObject AsynchronousMethodsObject;
#endif /* __cplusplus */

#endif 	/* __AsynchronousMethodsObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IAsynchronousMethodsTest_INTERFACE_DEFINED__
#define __IAsynchronousMethodsTest_INTERFACE_DEFINED__

/* interface IAsynchronousMethodsTest */
/* [unique][async_uuid][uuid][object] */ 


EXTERN_C const IID IID_IAsynchronousMethodsTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FFBC006F-662B-4817-9B72-8DD6943BDAEB")
    IAsynchronousMethodsTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetValue( 
            /* [in] */ BSTR Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [out] */ BSTR *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAsynchronousMethodsTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAsynchronousMethodsTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAsynchronousMethodsTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAsynchronousMethodsTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetValue )( 
            IAsynchronousMethodsTest * This,
            /* [in] */ BSTR Value);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            IAsynchronousMethodsTest * This,
            /* [out] */ BSTR *Value);
        
        END_INTERFACE
    } IAsynchronousMethodsTestVtbl;

    interface IAsynchronousMethodsTest
    {
        CONST_VTBL struct IAsynchronousMethodsTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAsynchronousMethodsTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAsynchronousMethodsTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAsynchronousMethodsTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAsynchronousMethodsTest_SetValue(This,Value)	\
    ( (This)->lpVtbl -> SetValue(This,Value) ) 

#define IAsynchronousMethodsTest_GetValue(This,Value)	\
    ( (This)->lpVtbl -> GetValue(This,Value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAsynchronousMethodsTest_INTERFACE_DEFINED__ */


#ifndef __AsyncIAsynchronousMethodsTest_INTERFACE_DEFINED__
#define __AsyncIAsynchronousMethodsTest_INTERFACE_DEFINED__

/* interface AsyncIAsynchronousMethodsTest */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_AsyncIAsynchronousMethodsTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1E610375-B6DE-44F3-834D-99D7519E09D8")
    AsyncIAsynchronousMethodsTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Begin_SetValue( 
            /* [in] */ BSTR Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Finish_SetValue( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Begin_GetValue( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Finish_GetValue( 
            /* [out] */ BSTR *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct AsyncIAsynchronousMethodsTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            AsyncIAsynchronousMethodsTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            AsyncIAsynchronousMethodsTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            AsyncIAsynchronousMethodsTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *Begin_SetValue )( 
            AsyncIAsynchronousMethodsTest * This,
            /* [in] */ BSTR Value);
        
        HRESULT ( STDMETHODCALLTYPE *Finish_SetValue )( 
            AsyncIAsynchronousMethodsTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *Begin_GetValue )( 
            AsyncIAsynchronousMethodsTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *Finish_GetValue )( 
            AsyncIAsynchronousMethodsTest * This,
            /* [out] */ BSTR *Value);
        
        END_INTERFACE
    } AsyncIAsynchronousMethodsTestVtbl;

    interface AsyncIAsynchronousMethodsTest
    {
        CONST_VTBL struct AsyncIAsynchronousMethodsTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define AsyncIAsynchronousMethodsTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define AsyncIAsynchronousMethodsTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define AsyncIAsynchronousMethodsTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define AsyncIAsynchronousMethodsTest_Begin_SetValue(This,Value)	\
    ( (This)->lpVtbl -> Begin_SetValue(This,Value) ) 

#define AsyncIAsynchronousMethodsTest_Finish_SetValue(This)	\
    ( (This)->lpVtbl -> Finish_SetValue(This) ) 

#define AsyncIAsynchronousMethodsTest_Begin_GetValue(This)	\
    ( (This)->lpVtbl -> Begin_GetValue(This) ) 

#define AsyncIAsynchronousMethodsTest_Finish_GetValue(This,Value)	\
    ( (This)->lpVtbl -> Finish_GetValue(This,Value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __AsyncIAsynchronousMethodsTest_INTERFACE_DEFINED__ */



#ifndef __AsynchronousMethodsServerLib_LIBRARY_DEFINED__
#define __AsynchronousMethodsServerLib_LIBRARY_DEFINED__

/* library AsynchronousMethodsServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_AsynchronousMethodsServerLib;

EXTERN_C const CLSID CLSID_AsynchronousMethodsObject;

#ifdef __cplusplus

class DECLSPEC_UUID("FB76EEC7-C53D-44E6-9390-123922BEEEB2")
AsynchronousMethodsObject;
#endif
#endif /* __AsynchronousMethodsServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


