

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Sep 07 22:06:17 2010
 */
/* Compiler settings for MyCOM.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
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

#ifndef __MyCOM_i_h__
#define __MyCOM_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBasicMathClass_FWD_DEFINED__
#define __IBasicMathClass_FWD_DEFINED__
typedef interface IBasicMathClass IBasicMathClass;
#endif 	/* __IBasicMathClass_FWD_DEFINED__ */


#ifndef __BasicMathClass_FWD_DEFINED__
#define __BasicMathClass_FWD_DEFINED__

#ifdef __cplusplus
typedef class BasicMathClass BasicMathClass;
#else
typedef struct BasicMathClass BasicMathClass;
#endif /* __cplusplus */

#endif 	/* __BasicMathClass_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IBasicMathClass_INTERFACE_DEFINED__
#define __IBasicMathClass_INTERFACE_DEFINED__

/* interface IBasicMathClass */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IBasicMathClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("89155F6A-EBB2-406D-827F-8E482057342F")
    IBasicMathClass : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ LONG A,
            /* [in] */ LONG B,
            /* [out] */ LONG *Result) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBasicMathClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBasicMathClass * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBasicMathClass * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBasicMathClass * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBasicMathClass * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBasicMathClass * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBasicMathClass * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBasicMathClass * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IBasicMathClass * This,
            /* [in] */ LONG A,
            /* [in] */ LONG B,
            /* [out] */ LONG *Result);
        
        END_INTERFACE
    } IBasicMathClassVtbl;

    interface IBasicMathClass
    {
        CONST_VTBL struct IBasicMathClassVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBasicMathClass_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBasicMathClass_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBasicMathClass_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBasicMathClass_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBasicMathClass_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBasicMathClass_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBasicMathClass_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IBasicMathClass_Add(This,A,B,Result)	\
    ( (This)->lpVtbl -> Add(This,A,B,Result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBasicMathClass_INTERFACE_DEFINED__ */



#ifndef __MyCOMLib_LIBRARY_DEFINED__
#define __MyCOMLib_LIBRARY_DEFINED__

/* library MyCOMLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MyCOMLib;

EXTERN_C const CLSID CLSID_BasicMathClass;

#ifdef __cplusplus

class DECLSPEC_UUID("BEBA7D9F-4DB7-4677-AFBC-73073AACCBA9")
BasicMathClass;
#endif
#endif /* __MyCOMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


