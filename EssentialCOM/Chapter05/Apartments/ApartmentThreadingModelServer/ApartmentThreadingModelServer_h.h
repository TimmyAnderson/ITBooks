

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:15:44 2012
 */
/* Compiler settings for ApartmentThreadingModelServer.idl:
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

#ifndef __ApartmentThreadingModelServer_h_h__
#define __ApartmentThreadingModelServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IApartmentThreadingModelTest_FWD_DEFINED__
#define __IApartmentThreadingModelTest_FWD_DEFINED__
typedef interface IApartmentThreadingModelTest IApartmentThreadingModelTest;
#endif 	/* __IApartmentThreadingModelTest_FWD_DEFINED__ */


#ifndef __ApartmentThreadingModelObject_FWD_DEFINED__
#define __ApartmentThreadingModelObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class ApartmentThreadingModelObject ApartmentThreadingModelObject;
#else
typedef struct ApartmentThreadingModelObject ApartmentThreadingModelObject;
#endif /* __cplusplus */

#endif 	/* __ApartmentThreadingModelObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IApartmentThreadingModelTest_INTERFACE_DEFINED__
#define __IApartmentThreadingModelTest_INTERFACE_DEFINED__

/* interface IApartmentThreadingModelTest */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IApartmentThreadingModelTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F68296BA-8181-4D93-9C94-7F530CD0EFF8")
    IApartmentThreadingModelTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IncrementValue( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [out] */ long *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApartmentThreadingModelTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IApartmentThreadingModelTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IApartmentThreadingModelTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IApartmentThreadingModelTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *IncrementValue )( 
            IApartmentThreadingModelTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            IApartmentThreadingModelTest * This,
            /* [out] */ long *Value);
        
        END_INTERFACE
    } IApartmentThreadingModelTestVtbl;

    interface IApartmentThreadingModelTest
    {
        CONST_VTBL struct IApartmentThreadingModelTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApartmentThreadingModelTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IApartmentThreadingModelTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IApartmentThreadingModelTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IApartmentThreadingModelTest_IncrementValue(This)	\
    ( (This)->lpVtbl -> IncrementValue(This) ) 

#define IApartmentThreadingModelTest_GetValue(This,Value)	\
    ( (This)->lpVtbl -> GetValue(This,Value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IApartmentThreadingModelTest_INTERFACE_DEFINED__ */



#ifndef __ApartmentThreadingModelServerLib_LIBRARY_DEFINED__
#define __ApartmentThreadingModelServerLib_LIBRARY_DEFINED__

/* library ApartmentThreadingModelServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ApartmentThreadingModelServerLib;

EXTERN_C const CLSID CLSID_ApartmentThreadingModelObject;

#ifdef __cplusplus

class DECLSPEC_UUID("6FCC169E-4F6F-4000-A5B6-190B6E18FCE2")
ApartmentThreadingModelObject;
#endif
#endif /* __ApartmentThreadingModelServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


