

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#ifndef __UnmanagedCOMServer_h_h__
#define __UnmanagedCOMServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IUnmanagedCOMServerCallback_FWD_DEFINED__
#define __IUnmanagedCOMServerCallback_FWD_DEFINED__
typedef interface IUnmanagedCOMServerCallback IUnmanagedCOMServerCallback;

#endif 	/* __IUnmanagedCOMServerCallback_FWD_DEFINED__ */


#ifndef __IUnmanagedCOMServer_FWD_DEFINED__
#define __IUnmanagedCOMServer_FWD_DEFINED__
typedef interface IUnmanagedCOMServer IUnmanagedCOMServer;

#endif 	/* __IUnmanagedCOMServer_FWD_DEFINED__ */


#ifndef __UnmanagedCOMObject_FWD_DEFINED__
#define __UnmanagedCOMObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class UnmanagedCOMObject UnmanagedCOMObject;
#else
typedef struct UnmanagedCOMObject UnmanagedCOMObject;
#endif /* __cplusplus */

#endif 	/* __UnmanagedCOMObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IUnmanagedCOMServerCallback_INTERFACE_DEFINED__
#define __IUnmanagedCOMServerCallback_INTERFACE_DEFINED__

/* interface IUnmanagedCOMServerCallback */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IUnmanagedCOMServerCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("69086C22-221F-4A29-9F91-2D6EB9D1EFFC")
    IUnmanagedCOMServerCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendMessageToClient( 
            /* [in] */ BSTR Message) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnmanagedCOMServerCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnmanagedCOMServerCallback * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnmanagedCOMServerCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnmanagedCOMServerCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *SendMessageToClient )( 
            IUnmanagedCOMServerCallback * This,
            /* [in] */ BSTR Message);
        
        END_INTERFACE
    } IUnmanagedCOMServerCallbackVtbl;

    interface IUnmanagedCOMServerCallback
    {
        CONST_VTBL struct IUnmanagedCOMServerCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnmanagedCOMServerCallback_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnmanagedCOMServerCallback_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnmanagedCOMServerCallback_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnmanagedCOMServerCallback_SendMessageToClient(This,Message)	\
    ( (This)->lpVtbl -> SendMessageToClient(This,Message) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnmanagedCOMServerCallback_INTERFACE_DEFINED__ */


#ifndef __IUnmanagedCOMServer_INTERFACE_DEFINED__
#define __IUnmanagedCOMServer_INTERFACE_DEFINED__

/* interface IUnmanagedCOMServer */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IUnmanagedCOMServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DB83FED1-ED27-425C-87B7-FF5036C1F08F")
    IUnmanagedCOMServer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RegisterCallback( 
            /* [in] */ IUnmanagedCOMServerCallback *Callback) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnRegisterCallback( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendMessageToServer( 
            /* [in] */ BSTR Message) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PrintMessage( 
            /* [in] */ BSTR Message) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LoadName( 
            /* [out] */ BSTR *Name,
            /* [out] */ int *Age) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SaveName( 
            /* [in] */ BSTR Name,
            /* [in] */ int Age) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ArrayTest1( 
            /* [in] */ int ArraySize,
            /* [size_is][out][in] */ int *Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ArrayTest2( 
            /* [out][in] */ SAFEARRAY * *Array) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnmanagedCOMServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnmanagedCOMServer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnmanagedCOMServer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnmanagedCOMServer * This);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterCallback )( 
            IUnmanagedCOMServer * This,
            /* [in] */ IUnmanagedCOMServerCallback *Callback);
        
        HRESULT ( STDMETHODCALLTYPE *UnRegisterCallback )( 
            IUnmanagedCOMServer * This);
        
        HRESULT ( STDMETHODCALLTYPE *SendMessageToServer )( 
            IUnmanagedCOMServer * This,
            /* [in] */ BSTR Message);
        
        HRESULT ( STDMETHODCALLTYPE *PrintMessage )( 
            IUnmanagedCOMServer * This,
            /* [in] */ BSTR Message);
        
        HRESULT ( STDMETHODCALLTYPE *LoadName )( 
            IUnmanagedCOMServer * This,
            /* [out] */ BSTR *Name,
            /* [out] */ int *Age);
        
        HRESULT ( STDMETHODCALLTYPE *SaveName )( 
            IUnmanagedCOMServer * This,
            /* [in] */ BSTR Name,
            /* [in] */ int Age);
        
        HRESULT ( STDMETHODCALLTYPE *ArrayTest1 )( 
            IUnmanagedCOMServer * This,
            /* [in] */ int ArraySize,
            /* [size_is][out][in] */ int *Array);
        
        HRESULT ( STDMETHODCALLTYPE *ArrayTest2 )( 
            IUnmanagedCOMServer * This,
            /* [out][in] */ SAFEARRAY * *Array);
        
        END_INTERFACE
    } IUnmanagedCOMServerVtbl;

    interface IUnmanagedCOMServer
    {
        CONST_VTBL struct IUnmanagedCOMServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnmanagedCOMServer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnmanagedCOMServer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnmanagedCOMServer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnmanagedCOMServer_RegisterCallback(This,Callback)	\
    ( (This)->lpVtbl -> RegisterCallback(This,Callback) ) 

#define IUnmanagedCOMServer_UnRegisterCallback(This)	\
    ( (This)->lpVtbl -> UnRegisterCallback(This) ) 

#define IUnmanagedCOMServer_SendMessageToServer(This,Message)	\
    ( (This)->lpVtbl -> SendMessageToServer(This,Message) ) 

#define IUnmanagedCOMServer_PrintMessage(This,Message)	\
    ( (This)->lpVtbl -> PrintMessage(This,Message) ) 

#define IUnmanagedCOMServer_LoadName(This,Name,Age)	\
    ( (This)->lpVtbl -> LoadName(This,Name,Age) ) 

#define IUnmanagedCOMServer_SaveName(This,Name,Age)	\
    ( (This)->lpVtbl -> SaveName(This,Name,Age) ) 

#define IUnmanagedCOMServer_ArrayTest1(This,ArraySize,Array)	\
    ( (This)->lpVtbl -> ArrayTest1(This,ArraySize,Array) ) 

#define IUnmanagedCOMServer_ArrayTest2(This,Array)	\
    ( (This)->lpVtbl -> ArrayTest2(This,Array) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnmanagedCOMServer_INTERFACE_DEFINED__ */



#ifndef __UnmanagedCOMServerLib_LIBRARY_DEFINED__
#define __UnmanagedCOMServerLib_LIBRARY_DEFINED__

/* library UnmanagedCOMServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_UnmanagedCOMServerLib;

EXTERN_C const CLSID CLSID_UnmanagedCOMObject;

#ifdef __cplusplus

class DECLSPEC_UUID("91C07319-AD70-4A12-A070-DC8E76A5BC94")
UnmanagedCOMObject;
#endif
#endif /* __UnmanagedCOMServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


