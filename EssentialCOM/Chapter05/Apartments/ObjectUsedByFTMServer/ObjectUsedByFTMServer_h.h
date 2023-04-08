

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:15:44 2012
 */
/* Compiler settings for ObjectUsedByFTMServer.idl:
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

#ifndef __ObjectUsedByFTMServer_h_h__
#define __ObjectUsedByFTMServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IObjectUsedByFTMTest_FWD_DEFINED__
#define __IObjectUsedByFTMTest_FWD_DEFINED__
typedef interface IObjectUsedByFTMTest IObjectUsedByFTMTest;
#endif 	/* __IObjectUsedByFTMTest_FWD_DEFINED__ */


#ifndef __ObjectUsedByFTMObject_FWD_DEFINED__
#define __ObjectUsedByFTMObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class ObjectUsedByFTMObject ObjectUsedByFTMObject;
#else
typedef struct ObjectUsedByFTMObject ObjectUsedByFTMObject;
#endif /* __cplusplus */

#endif 	/* __ObjectUsedByFTMObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IObjectUsedByFTMTest_INTERFACE_DEFINED__
#define __IObjectUsedByFTMTest_INTERFACE_DEFINED__

/* interface IObjectUsedByFTMTest */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IObjectUsedByFTMTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4FD8CBC3-914C-4B34-BC82-615C73FC8F31")
    IObjectUsedByFTMTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IncrementValue( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [out] */ long *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IObjectUsedByFTMTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IObjectUsedByFTMTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IObjectUsedByFTMTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IObjectUsedByFTMTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *IncrementValue )( 
            IObjectUsedByFTMTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            IObjectUsedByFTMTest * This,
            /* [out] */ long *Value);
        
        END_INTERFACE
    } IObjectUsedByFTMTestVtbl;

    interface IObjectUsedByFTMTest
    {
        CONST_VTBL struct IObjectUsedByFTMTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IObjectUsedByFTMTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IObjectUsedByFTMTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IObjectUsedByFTMTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IObjectUsedByFTMTest_IncrementValue(This)	\
    ( (This)->lpVtbl -> IncrementValue(This) ) 

#define IObjectUsedByFTMTest_GetValue(This,Value)	\
    ( (This)->lpVtbl -> GetValue(This,Value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IObjectUsedByFTMTest_INTERFACE_DEFINED__ */



#ifndef __ObjectUsedByFTMServerLib_LIBRARY_DEFINED__
#define __ObjectUsedByFTMServerLib_LIBRARY_DEFINED__

/* library ObjectUsedByFTMServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ObjectUsedByFTMServerLib;

EXTERN_C const CLSID CLSID_ObjectUsedByFTMObject;

#ifdef __cplusplus

class DECLSPEC_UUID("65D8909C-D4A0-47EF-A584-0DA233C724D5")
ObjectUsedByFTMObject;
#endif
#endif /* __ObjectUsedByFTMServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


