

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Aug 09 22:52:31 2012
 */
/* Compiler settings for ConnectionPointsServer.idl:
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

#ifndef __ConnectionPointsServer_h_h__
#define __ConnectionPointsServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMyConnectionPointsCallback_FWD_DEFINED__
#define __IMyConnectionPointsCallback_FWD_DEFINED__
typedef interface IMyConnectionPointsCallback IMyConnectionPointsCallback;
#endif 	/* __IMyConnectionPointsCallback_FWD_DEFINED__ */


#ifndef __IMyConnectionPoints_FWD_DEFINED__
#define __IMyConnectionPoints_FWD_DEFINED__
typedef interface IMyConnectionPoints IMyConnectionPoints;
#endif 	/* __IMyConnectionPoints_FWD_DEFINED__ */


#ifndef __ConnectionPointsObject_FWD_DEFINED__
#define __ConnectionPointsObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class ConnectionPointsObject ConnectionPointsObject;
#else
typedef struct ConnectionPointsObject ConnectionPointsObject;
#endif /* __cplusplus */

#endif 	/* __ConnectionPointsObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IMyConnectionPointsCallback_INTERFACE_DEFINED__
#define __IMyConnectionPointsCallback_INTERFACE_DEFINED__

/* interface IMyConnectionPointsCallback */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IMyConnectionPointsCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D179F4FA-DCAE-456F-B186-2AF54A0D468F")
    IMyConnectionPointsCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendMessageToClient( 
            /* [in] */ BSTR Message) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyConnectionPointsCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyConnectionPointsCallback * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyConnectionPointsCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyConnectionPointsCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *SendMessageToClient )( 
            IMyConnectionPointsCallback * This,
            /* [in] */ BSTR Message);
        
        END_INTERFACE
    } IMyConnectionPointsCallbackVtbl;

    interface IMyConnectionPointsCallback
    {
        CONST_VTBL struct IMyConnectionPointsCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyConnectionPointsCallback_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyConnectionPointsCallback_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyConnectionPointsCallback_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyConnectionPointsCallback_SendMessageToClient(This,Message)	\
    ( (This)->lpVtbl -> SendMessageToClient(This,Message) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyConnectionPointsCallback_INTERFACE_DEFINED__ */


#ifndef __IMyConnectionPoints_INTERFACE_DEFINED__
#define __IMyConnectionPoints_INTERFACE_DEFINED__

/* interface IMyConnectionPoints */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IMyConnectionPoints;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("574AC1CE-A230-4D8A-8932-07565A03AE1F")
    IMyConnectionPoints : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendMessageToServer( 
            /* [in] */ BSTR Message) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyConnectionPointsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyConnectionPoints * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyConnectionPoints * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyConnectionPoints * This);
        
        HRESULT ( STDMETHODCALLTYPE *SendMessageToServer )( 
            IMyConnectionPoints * This,
            /* [in] */ BSTR Message);
        
        END_INTERFACE
    } IMyConnectionPointsVtbl;

    interface IMyConnectionPoints
    {
        CONST_VTBL struct IMyConnectionPointsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyConnectionPoints_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyConnectionPoints_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyConnectionPoints_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyConnectionPoints_SendMessageToServer(This,Message)	\
    ( (This)->lpVtbl -> SendMessageToServer(This,Message) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyConnectionPoints_INTERFACE_DEFINED__ */



#ifndef __ConnectionPointsServerLib_LIBRARY_DEFINED__
#define __ConnectionPointsServerLib_LIBRARY_DEFINED__

/* library ConnectionPointsServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ConnectionPointsServerLib;

EXTERN_C const CLSID CLSID_ConnectionPointsObject;

#ifdef __cplusplus

class DECLSPEC_UUID("013B83E1-964F-4970-8F99-96FE1466C78B")
ConnectionPointsObject;
#endif
#endif /* __ConnectionPointsServerLib_LIBRARY_DEFINED__ */

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


