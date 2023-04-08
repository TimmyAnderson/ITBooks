

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:15:44 2012
 */
/* Compiler settings for ExternalConnectionServer.idl:
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

#ifndef __ExternalConnectionServer_h_h__
#define __ExternalConnectionServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IExternalConnectionTest_FWD_DEFINED__
#define __IExternalConnectionTest_FWD_DEFINED__
typedef interface IExternalConnectionTest IExternalConnectionTest;
#endif 	/* __IExternalConnectionTest_FWD_DEFINED__ */


#ifndef __ExternalConnectionObject_FWD_DEFINED__
#define __ExternalConnectionObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class ExternalConnectionObject ExternalConnectionObject;
#else
typedef struct ExternalConnectionObject ExternalConnectionObject;
#endif /* __cplusplus */

#endif 	/* __ExternalConnectionObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IExternalConnectionTest_INTERFACE_DEFINED__
#define __IExternalConnectionTest_INTERFACE_DEFINED__

/* interface IExternalConnectionTest */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IExternalConnectionTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1F838F40-5FF3-42FF-9807-25E9811D01C9")
    IExternalConnectionTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IncrementValue( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [out] */ long *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExternalConnectionTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IExternalConnectionTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IExternalConnectionTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IExternalConnectionTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *IncrementValue )( 
            IExternalConnectionTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            IExternalConnectionTest * This,
            /* [out] */ long *Value);
        
        END_INTERFACE
    } IExternalConnectionTestVtbl;

    interface IExternalConnectionTest
    {
        CONST_VTBL struct IExternalConnectionTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExternalConnectionTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IExternalConnectionTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IExternalConnectionTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IExternalConnectionTest_IncrementValue(This)	\
    ( (This)->lpVtbl -> IncrementValue(This) ) 

#define IExternalConnectionTest_GetValue(This,Value)	\
    ( (This)->lpVtbl -> GetValue(This,Value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IExternalConnectionTest_INTERFACE_DEFINED__ */



#ifndef __ExternalConnectionServerLib_LIBRARY_DEFINED__
#define __ExternalConnectionServerLib_LIBRARY_DEFINED__

/* library ExternalConnectionServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ExternalConnectionServerLib;

EXTERN_C const CLSID CLSID_ExternalConnectionObject;

#ifdef __cplusplus

class DECLSPEC_UUID("413F464E-2222-4752-83A7-B5526A7C64DA")
ExternalConnectionObject;
#endif
#endif /* __ExternalConnectionServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


