

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:16:07 2012
 */
/* Compiler settings for FTMServer.idl:
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

#ifndef __FTMServer_h_h__
#define __FTMServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFTMTest_FWD_DEFINED__
#define __IFTMTest_FWD_DEFINED__
typedef interface IFTMTest IFTMTest;
#endif 	/* __IFTMTest_FWD_DEFINED__ */


#ifndef __FTMObject_FWD_DEFINED__
#define __FTMObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class FTMObject FTMObject;
#else
typedef struct FTMObject FTMObject;
#endif /* __cplusplus */

#endif 	/* __FTMObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IFTMTest_INTERFACE_DEFINED__
#define __IFTMTest_INTERFACE_DEFINED__

/* interface IFTMTest */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IFTMTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D83BC28B-DDBD-4316-8087-AF0E11E401CA")
    IFTMTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IncrementValue( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [out] */ long *Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IncrementValueToRemoteObject( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValueFromRemoteObject( 
            /* [out] */ long *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFTMTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFTMTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFTMTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFTMTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *IncrementValue )( 
            IFTMTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            IFTMTest * This,
            /* [out] */ long *Value);
        
        HRESULT ( STDMETHODCALLTYPE *IncrementValueToRemoteObject )( 
            IFTMTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetValueFromRemoteObject )( 
            IFTMTest * This,
            /* [out] */ long *Value);
        
        END_INTERFACE
    } IFTMTestVtbl;

    interface IFTMTest
    {
        CONST_VTBL struct IFTMTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFTMTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFTMTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFTMTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFTMTest_IncrementValue(This)	\
    ( (This)->lpVtbl -> IncrementValue(This) ) 

#define IFTMTest_GetValue(This,Value)	\
    ( (This)->lpVtbl -> GetValue(This,Value) ) 

#define IFTMTest_IncrementValueToRemoteObject(This)	\
    ( (This)->lpVtbl -> IncrementValueToRemoteObject(This) ) 

#define IFTMTest_GetValueFromRemoteObject(This,Value)	\
    ( (This)->lpVtbl -> GetValueFromRemoteObject(This,Value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFTMTest_INTERFACE_DEFINED__ */



#ifndef __FTMServerLib_LIBRARY_DEFINED__
#define __FTMServerLib_LIBRARY_DEFINED__

/* library FTMServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_FTMServerLib;

EXTERN_C const CLSID CLSID_FTMObject;

#ifdef __cplusplus

class DECLSPEC_UUID("C0F5A9A6-6621-4CF1-AB5A-08508FE46911")
FTMObject;
#endif
#endif /* __FTMServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


