

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#ifndef __CallbacksInCOMServer_h_h__
#define __CallbacksInCOMServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMyServerCallback_FWD_DEFINED__
#define __IMyServerCallback_FWD_DEFINED__
typedef interface IMyServerCallback IMyServerCallback;
#endif 	/* __IMyServerCallback_FWD_DEFINED__ */


#ifndef __IMyServer_FWD_DEFINED__
#define __IMyServer_FWD_DEFINED__
typedef interface IMyServer IMyServer;
#endif 	/* __IMyServer_FWD_DEFINED__ */


#ifndef __CallbacksInCOMObject_FWD_DEFINED__
#define __CallbacksInCOMObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CallbacksInCOMObject CallbacksInCOMObject;
#else
typedef struct CallbacksInCOMObject CallbacksInCOMObject;
#endif /* __cplusplus */

#endif 	/* __CallbacksInCOMObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IMyServerCallback_INTERFACE_DEFINED__
#define __IMyServerCallback_INTERFACE_DEFINED__

/* interface IMyServerCallback */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IMyServerCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("69086C22-221F-4A29-9F91-2D6EB9D1EFFB")
    IMyServerCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendMessageToClient( 
            /* [in] */ BSTR Message) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyServerCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyServerCallback * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyServerCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyServerCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *SendMessageToClient )( 
            IMyServerCallback * This,
            /* [in] */ BSTR Message);
        
        END_INTERFACE
    } IMyServerCallbackVtbl;

    interface IMyServerCallback
    {
        CONST_VTBL struct IMyServerCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyServerCallback_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyServerCallback_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyServerCallback_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyServerCallback_SendMessageToClient(This,Message)	\
    ( (This)->lpVtbl -> SendMessageToClient(This,Message) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyServerCallback_INTERFACE_DEFINED__ */


#ifndef __IMyServer_INTERFACE_DEFINED__
#define __IMyServer_INTERFACE_DEFINED__

/* interface IMyServer */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IMyServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DB83FED1-ED27-425C-87B7-FF5036C1F08E")
    IMyServer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RegisterCallback( 
            /* [in] */ IMyServerCallback *Callback) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnRegisterCallback( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendMessageToServer( 
            /* [in] */ BSTR Message) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyServer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyServer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyServer * This);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterCallback )( 
            IMyServer * This,
            /* [in] */ IMyServerCallback *Callback);
        
        HRESULT ( STDMETHODCALLTYPE *UnRegisterCallback )( 
            IMyServer * This);
        
        HRESULT ( STDMETHODCALLTYPE *SendMessageToServer )( 
            IMyServer * This,
            /* [in] */ BSTR Message);
        
        END_INTERFACE
    } IMyServerVtbl;

    interface IMyServer
    {
        CONST_VTBL struct IMyServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyServer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyServer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyServer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyServer_RegisterCallback(This,Callback)	\
    ( (This)->lpVtbl -> RegisterCallback(This,Callback) ) 

#define IMyServer_UnRegisterCallback(This)	\
    ( (This)->lpVtbl -> UnRegisterCallback(This) ) 

#define IMyServer_SendMessageToServer(This,Message)	\
    ( (This)->lpVtbl -> SendMessageToServer(This,Message) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyServer_INTERFACE_DEFINED__ */



#ifndef __CallbacksInCOMServerLib_LIBRARY_DEFINED__
#define __CallbacksInCOMServerLib_LIBRARY_DEFINED__

/* library CallbacksInCOMServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_CallbacksInCOMServerLib;

EXTERN_C const CLSID CLSID_CallbacksInCOMObject;

#ifdef __cplusplus

class DECLSPEC_UUID("91C07319-AD70-4A12-A070-DC8E76A5BC95")
CallbacksInCOMObject;
#endif
#endif /* __CallbacksInCOMServerLib_LIBRARY_DEFINED__ */

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


