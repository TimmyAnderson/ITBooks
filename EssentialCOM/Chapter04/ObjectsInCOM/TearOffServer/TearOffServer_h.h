

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:00:06 2012
 */
/* Compiler settings for TearOffServer.idl:
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

#ifndef __TearOffServer_h_h__
#define __TearOffServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITearOffTextOuter_FWD_DEFINED__
#define __ITearOffTextOuter_FWD_DEFINED__
typedef interface ITearOffTextOuter ITearOffTextOuter;
#endif 	/* __ITearOffTextOuter_FWD_DEFINED__ */


#ifndef __ITearOffTextInner_FWD_DEFINED__
#define __ITearOffTextInner_FWD_DEFINED__
typedef interface ITearOffTextInner ITearOffTextInner;
#endif 	/* __ITearOffTextInner_FWD_DEFINED__ */


#ifndef __TearOffObject_FWD_DEFINED__
#define __TearOffObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class TearOffObject TearOffObject;
#else
typedef struct TearOffObject TearOffObject;
#endif /* __cplusplus */

#endif 	/* __TearOffObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ITearOffTextOuter_INTERFACE_DEFINED__
#define __ITearOffTextOuter_INTERFACE_DEFINED__

/* interface ITearOffTextOuter */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_ITearOffTextOuter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("93664F4D-CA8C-4F8D-AD0B-5AFF9B210DB1")
    ITearOffTextOuter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetTextOuter( 
            /* [string][in] */ wchar_t *Text) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTextOuter( 
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **Text) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITearOffTextOuterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITearOffTextOuter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITearOffTextOuter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITearOffTextOuter * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetTextOuter )( 
            ITearOffTextOuter * This,
            /* [string][in] */ wchar_t *Text);
        
        HRESULT ( STDMETHODCALLTYPE *GetTextOuter )( 
            ITearOffTextOuter * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **Text);
        
        END_INTERFACE
    } ITearOffTextOuterVtbl;

    interface ITearOffTextOuter
    {
        CONST_VTBL struct ITearOffTextOuterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITearOffTextOuter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITearOffTextOuter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITearOffTextOuter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITearOffTextOuter_SetTextOuter(This,Text)	\
    ( (This)->lpVtbl -> SetTextOuter(This,Text) ) 

#define ITearOffTextOuter_GetTextOuter(This,BufferSize,Text)	\
    ( (This)->lpVtbl -> GetTextOuter(This,BufferSize,Text) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITearOffTextOuter_INTERFACE_DEFINED__ */


#ifndef __ITearOffTextInner_INTERFACE_DEFINED__
#define __ITearOffTextInner_INTERFACE_DEFINED__

/* interface ITearOffTextInner */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_ITearOffTextInner;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B84E7F7C-9E8B-48BC-85A7-29C387B5241A")
    ITearOffTextInner : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetTextInner( 
            /* [string][in] */ wchar_t *Text) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTextInner( 
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **Text) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITearOffTextInnerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITearOffTextInner * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITearOffTextInner * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITearOffTextInner * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetTextInner )( 
            ITearOffTextInner * This,
            /* [string][in] */ wchar_t *Text);
        
        HRESULT ( STDMETHODCALLTYPE *GetTextInner )( 
            ITearOffTextInner * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **Text);
        
        END_INTERFACE
    } ITearOffTextInnerVtbl;

    interface ITearOffTextInner
    {
        CONST_VTBL struct ITearOffTextInnerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITearOffTextInner_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITearOffTextInner_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITearOffTextInner_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITearOffTextInner_SetTextInner(This,Text)	\
    ( (This)->lpVtbl -> SetTextInner(This,Text) ) 

#define ITearOffTextInner_GetTextInner(This,BufferSize,Text)	\
    ( (This)->lpVtbl -> GetTextInner(This,BufferSize,Text) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITearOffTextInner_INTERFACE_DEFINED__ */



#ifndef __TearOffServerLib_LIBRARY_DEFINED__
#define __TearOffServerLib_LIBRARY_DEFINED__

/* library TearOffServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_TearOffServerLib;

EXTERN_C const CLSID CLSID_TearOffObject;

#ifdef __cplusplus

class DECLSPEC_UUID("549C91FE-1B9D-4A38-B0C8-A03D50FFD04B")
TearOffObject;
#endif
#endif /* __TearOffServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


