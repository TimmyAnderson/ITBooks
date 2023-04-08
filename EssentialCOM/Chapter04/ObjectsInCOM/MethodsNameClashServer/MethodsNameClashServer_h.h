

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:00:06 2012
 */
/* Compiler settings for MethodsNameClashServer.idl:
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

#ifndef __MethodsNameClashServer_h_h__
#define __MethodsNameClashServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IGetText1_FWD_DEFINED__
#define __IGetText1_FWD_DEFINED__
typedef interface IGetText1 IGetText1;
#endif 	/* __IGetText1_FWD_DEFINED__ */


#ifndef __IGetText2_FWD_DEFINED__
#define __IGetText2_FWD_DEFINED__
typedef interface IGetText2 IGetText2;
#endif 	/* __IGetText2_FWD_DEFINED__ */


#ifndef __MethodsNameClashObject_FWD_DEFINED__
#define __MethodsNameClashObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class MethodsNameClashObject MethodsNameClashObject;
#else
typedef struct MethodsNameClashObject MethodsNameClashObject;
#endif /* __cplusplus */

#endif 	/* __MethodsNameClashObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IGetText1_INTERFACE_DEFINED__
#define __IGetText1_INTERFACE_DEFINED__

/* interface IGetText1 */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IGetText1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F567B9C9-E34B-4ACD-87A1-F4655E2B5BCB")
    IGetText1 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetText( 
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **Text) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGetText1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetText1 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetText1 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetText1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetText )( 
            IGetText1 * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **Text);
        
        END_INTERFACE
    } IGetText1Vtbl;

    interface IGetText1
    {
        CONST_VTBL struct IGetText1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetText1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetText1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetText1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetText1_GetText(This,BufferSize,Text)	\
    ( (This)->lpVtbl -> GetText(This,BufferSize,Text) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetText1_INTERFACE_DEFINED__ */


#ifndef __IGetText2_INTERFACE_DEFINED__
#define __IGetText2_INTERFACE_DEFINED__

/* interface IGetText2 */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IGetText2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B0722B76-BB23-4216-8468-87CA680AAED3")
    IGetText2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetText( 
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **Text) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGetText2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetText2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetText2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetText2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetText )( 
            IGetText2 * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **Text);
        
        END_INTERFACE
    } IGetText2Vtbl;

    interface IGetText2
    {
        CONST_VTBL struct IGetText2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetText2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetText2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetText2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetText2_GetText(This,BufferSize,Text)	\
    ( (This)->lpVtbl -> GetText(This,BufferSize,Text) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetText2_INTERFACE_DEFINED__ */



#ifndef __MethodsNameClashServerLib_LIBRARY_DEFINED__
#define __MethodsNameClashServerLib_LIBRARY_DEFINED__

/* library MethodsNameClashServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MethodsNameClashServerLib;

EXTERN_C const CLSID CLSID_MethodsNameClashObject;

#ifdef __cplusplus

class DECLSPEC_UUID("D30F8E8F-CD97-4255-90BF-0D7EC9B853FA")
MethodsNameClashObject;
#endif
#endif /* __MethodsNameClashServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


