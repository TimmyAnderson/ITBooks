

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Aug 09 22:52:31 2012
 */
/* Compiler settings for CustomDispatchServer.idl:
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

#ifndef __CustomDispatchServer_h_h__
#define __CustomDispatchServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICustomDispatchTest_FWD_DEFINED__
#define __ICustomDispatchTest_FWD_DEFINED__
typedef interface ICustomDispatchTest ICustomDispatchTest;
#endif 	/* __ICustomDispatchTest_FWD_DEFINED__ */


#ifndef __CustomDispatchObject_FWD_DEFINED__
#define __CustomDispatchObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CustomDispatchObject CustomDispatchObject;
#else
typedef struct CustomDispatchObject CustomDispatchObject;
#endif /* __cplusplus */

#endif 	/* __CustomDispatchObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICustomDispatchTest_INTERFACE_DEFINED__
#define __ICustomDispatchTest_INTERFACE_DEFINED__

/* interface ICustomDispatchTest */
/* [dual][unique][uuid][object] */ 


EXTERN_C const IID IID_ICustomDispatchTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("96F3935B-E856-4DBC-89FC-5E0B2D0FB5A8")
    ICustomDispatchTest : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetValue( 
            BSTR Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetValue( 
            BSTR *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICustomDispatchTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICustomDispatchTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICustomDispatchTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICustomDispatchTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICustomDispatchTest * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICustomDispatchTest * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICustomDispatchTest * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICustomDispatchTest * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetValue )( 
            ICustomDispatchTest * This,
            BSTR Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            ICustomDispatchTest * This,
            BSTR *Value);
        
        END_INTERFACE
    } ICustomDispatchTestVtbl;

    interface ICustomDispatchTest
    {
        CONST_VTBL struct ICustomDispatchTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICustomDispatchTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICustomDispatchTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICustomDispatchTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICustomDispatchTest_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICustomDispatchTest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICustomDispatchTest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICustomDispatchTest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICustomDispatchTest_SetValue(This,Value)	\
    ( (This)->lpVtbl -> SetValue(This,Value) ) 

#define ICustomDispatchTest_GetValue(This,Value)	\
    ( (This)->lpVtbl -> GetValue(This,Value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICustomDispatchTest_INTERFACE_DEFINED__ */



#ifndef __CustomDispatchServerLib_LIBRARY_DEFINED__
#define __CustomDispatchServerLib_LIBRARY_DEFINED__

/* library CustomDispatchServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_CustomDispatchServerLib;

EXTERN_C const CLSID CLSID_CustomDispatchObject;

#ifdef __cplusplus

class DECLSPEC_UUID("9101D33D-B5D7-438F-849B-17908A034969")
CustomDispatchObject;
#endif
#endif /* __CustomDispatchServerLib_LIBRARY_DEFINED__ */

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


