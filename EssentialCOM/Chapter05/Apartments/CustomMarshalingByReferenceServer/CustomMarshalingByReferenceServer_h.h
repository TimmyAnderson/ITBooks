

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:15:45 2012
 */
/* Compiler settings for CustomMarshalingByReferenceServer.idl:
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

#ifndef __CustomMarshalingByReferenceServer_h_h__
#define __CustomMarshalingByReferenceServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICustomMarshalingByReferenceTest_FWD_DEFINED__
#define __ICustomMarshalingByReferenceTest_FWD_DEFINED__
typedef interface ICustomMarshalingByReferenceTest ICustomMarshalingByReferenceTest;
#endif 	/* __ICustomMarshalingByReferenceTest_FWD_DEFINED__ */


#ifndef __CustomMarshalingByReferenceObject_FWD_DEFINED__
#define __CustomMarshalingByReferenceObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CustomMarshalingByReferenceObject CustomMarshalingByReferenceObject;
#else
typedef struct CustomMarshalingByReferenceObject CustomMarshalingByReferenceObject;
#endif /* __cplusplus */

#endif 	/* __CustomMarshalingByReferenceObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICustomMarshalingByReferenceTest_INTERFACE_DEFINED__
#define __ICustomMarshalingByReferenceTest_INTERFACE_DEFINED__

/* interface ICustomMarshalingByReferenceTest */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ICustomMarshalingByReferenceTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D58B5FD6-D7A7-4373-824F-DBBA096B0CF4")
    ICustomMarshalingByReferenceTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IncrementValue( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [out] */ long *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICustomMarshalingByReferenceTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICustomMarshalingByReferenceTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICustomMarshalingByReferenceTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICustomMarshalingByReferenceTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *IncrementValue )( 
            ICustomMarshalingByReferenceTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            ICustomMarshalingByReferenceTest * This,
            /* [out] */ long *Value);
        
        END_INTERFACE
    } ICustomMarshalingByReferenceTestVtbl;

    interface ICustomMarshalingByReferenceTest
    {
        CONST_VTBL struct ICustomMarshalingByReferenceTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICustomMarshalingByReferenceTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICustomMarshalingByReferenceTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICustomMarshalingByReferenceTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICustomMarshalingByReferenceTest_IncrementValue(This)	\
    ( (This)->lpVtbl -> IncrementValue(This) ) 

#define ICustomMarshalingByReferenceTest_GetValue(This,Value)	\
    ( (This)->lpVtbl -> GetValue(This,Value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICustomMarshalingByReferenceTest_INTERFACE_DEFINED__ */



#ifndef __CustomMarshalingByReferenceServerLib_LIBRARY_DEFINED__
#define __CustomMarshalingByReferenceServerLib_LIBRARY_DEFINED__

/* library CustomMarshalingByReferenceServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_CustomMarshalingByReferenceServerLib;

EXTERN_C const CLSID CLSID_CustomMarshalingByReferenceObject;

#ifdef __cplusplus

class DECLSPEC_UUID("42F8F1E5-C641-4FB6-A4BA-3593B248856C")
CustomMarshalingByReferenceObject;
#endif
#endif /* __CustomMarshalingByReferenceServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


