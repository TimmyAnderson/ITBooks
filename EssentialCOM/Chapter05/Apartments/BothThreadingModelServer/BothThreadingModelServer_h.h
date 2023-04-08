

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:15:44 2012
 */
/* Compiler settings for BothThreadingModelServer.idl:
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

#ifndef __BothThreadingModelServer_h_h__
#define __BothThreadingModelServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBothThreadingModelTest_FWD_DEFINED__
#define __IBothThreadingModelTest_FWD_DEFINED__
typedef interface IBothThreadingModelTest IBothThreadingModelTest;
#endif 	/* __IBothThreadingModelTest_FWD_DEFINED__ */


#ifndef __BothThreadingModelObject_FWD_DEFINED__
#define __BothThreadingModelObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class BothThreadingModelObject BothThreadingModelObject;
#else
typedef struct BothThreadingModelObject BothThreadingModelObject;
#endif /* __cplusplus */

#endif 	/* __BothThreadingModelObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IBothThreadingModelTest_INTERFACE_DEFINED__
#define __IBothThreadingModelTest_INTERFACE_DEFINED__

/* interface IBothThreadingModelTest */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IBothThreadingModelTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("466DCC56-1104-4936-AB9B-0A5803FE8786")
    IBothThreadingModelTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IncrementValue( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [out] */ long *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBothThreadingModelTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBothThreadingModelTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBothThreadingModelTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBothThreadingModelTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *IncrementValue )( 
            IBothThreadingModelTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            IBothThreadingModelTest * This,
            /* [out] */ long *Value);
        
        END_INTERFACE
    } IBothThreadingModelTestVtbl;

    interface IBothThreadingModelTest
    {
        CONST_VTBL struct IBothThreadingModelTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBothThreadingModelTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBothThreadingModelTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBothThreadingModelTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBothThreadingModelTest_IncrementValue(This)	\
    ( (This)->lpVtbl -> IncrementValue(This) ) 

#define IBothThreadingModelTest_GetValue(This,Value)	\
    ( (This)->lpVtbl -> GetValue(This,Value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBothThreadingModelTest_INTERFACE_DEFINED__ */



#ifndef __BothThreadingModelServerLib_LIBRARY_DEFINED__
#define __BothThreadingModelServerLib_LIBRARY_DEFINED__

/* library BothThreadingModelServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_BothThreadingModelServerLib;

EXTERN_C const CLSID CLSID_BothThreadingModelObject;

#ifdef __cplusplus

class DECLSPEC_UUID("21C461AC-4829-4D05-BA34-189E5C83FD52")
BothThreadingModelObject;
#endif
#endif /* __BothThreadingModelServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


