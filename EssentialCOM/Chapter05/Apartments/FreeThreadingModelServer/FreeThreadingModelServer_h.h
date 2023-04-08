

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:15:45 2012
 */
/* Compiler settings for FreeThreadingModelServer.idl:
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

#ifndef __FreeThreadingModelServer_h_h__
#define __FreeThreadingModelServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFreeThreadingModelTest_FWD_DEFINED__
#define __IFreeThreadingModelTest_FWD_DEFINED__
typedef interface IFreeThreadingModelTest IFreeThreadingModelTest;
#endif 	/* __IFreeThreadingModelTest_FWD_DEFINED__ */


#ifndef __FreeThreadingModelObject_FWD_DEFINED__
#define __FreeThreadingModelObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class FreeThreadingModelObject FreeThreadingModelObject;
#else
typedef struct FreeThreadingModelObject FreeThreadingModelObject;
#endif /* __cplusplus */

#endif 	/* __FreeThreadingModelObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IFreeThreadingModelTest_INTERFACE_DEFINED__
#define __IFreeThreadingModelTest_INTERFACE_DEFINED__

/* interface IFreeThreadingModelTest */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IFreeThreadingModelTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("43CAC48C-9F2A-4FDE-B829-E63CABB80E73")
    IFreeThreadingModelTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IncrementValue( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [out] */ long *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFreeThreadingModelTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFreeThreadingModelTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFreeThreadingModelTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFreeThreadingModelTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *IncrementValue )( 
            IFreeThreadingModelTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            IFreeThreadingModelTest * This,
            /* [out] */ long *Value);
        
        END_INTERFACE
    } IFreeThreadingModelTestVtbl;

    interface IFreeThreadingModelTest
    {
        CONST_VTBL struct IFreeThreadingModelTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFreeThreadingModelTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFreeThreadingModelTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFreeThreadingModelTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFreeThreadingModelTest_IncrementValue(This)	\
    ( (This)->lpVtbl -> IncrementValue(This) ) 

#define IFreeThreadingModelTest_GetValue(This,Value)	\
    ( (This)->lpVtbl -> GetValue(This,Value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFreeThreadingModelTest_INTERFACE_DEFINED__ */



#ifndef __FreeThreadingModelServerLib_LIBRARY_DEFINED__
#define __FreeThreadingModelServerLib_LIBRARY_DEFINED__

/* library FreeThreadingModelServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_FreeThreadingModelServerLib;

EXTERN_C const CLSID CLSID_FreeThreadingModelObject;

#ifdef __cplusplus

class DECLSPEC_UUID("D348A05D-3A32-42F8-B41F-0A31B495F3BC")
FreeThreadingModelObject;
#endif
#endif /* __FreeThreadingModelServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


