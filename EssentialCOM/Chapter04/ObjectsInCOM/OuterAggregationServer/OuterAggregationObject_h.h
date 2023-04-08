

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:00:16 2012
 */
/* Compiler settings for OuterAggregationObject.idl:
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

#ifndef __OuterAggregationObject_h_h__
#define __OuterAggregationObject_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IOuterAggregationText_FWD_DEFINED__
#define __IOuterAggregationText_FWD_DEFINED__
typedef interface IOuterAggregationText IOuterAggregationText;
#endif 	/* __IOuterAggregationText_FWD_DEFINED__ */


#ifndef __OuterAggregationObject_FWD_DEFINED__
#define __OuterAggregationObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class OuterAggregationObject OuterAggregationObject;
#else
typedef struct OuterAggregationObject OuterAggregationObject;
#endif /* __cplusplus */

#endif 	/* __OuterAggregationObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IOuterAggregationText_INTERFACE_DEFINED__
#define __IOuterAggregationText_INTERFACE_DEFINED__

/* interface IOuterAggregationText */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IOuterAggregationText;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5C0AE81B-2AA7-43E6-9CC4-3CA45991E38C")
    IOuterAggregationText : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetText( 
            /* [string][in] */ wchar_t *Text) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetText( 
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **Text) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOuterAggregationTextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOuterAggregationText * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOuterAggregationText * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOuterAggregationText * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetText )( 
            IOuterAggregationText * This,
            /* [string][in] */ wchar_t *Text);
        
        HRESULT ( STDMETHODCALLTYPE *GetText )( 
            IOuterAggregationText * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **Text);
        
        END_INTERFACE
    } IOuterAggregationTextVtbl;

    interface IOuterAggregationText
    {
        CONST_VTBL struct IOuterAggregationTextVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOuterAggregationText_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IOuterAggregationText_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IOuterAggregationText_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IOuterAggregationText_SetText(This,Text)	\
    ( (This)->lpVtbl -> SetText(This,Text) ) 

#define IOuterAggregationText_GetText(This,BufferSize,Text)	\
    ( (This)->lpVtbl -> GetText(This,BufferSize,Text) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IOuterAggregationText_INTERFACE_DEFINED__ */



#ifndef __OuterAggregationServerLib_LIBRARY_DEFINED__
#define __OuterAggregationServerLib_LIBRARY_DEFINED__

/* library OuterAggregationServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_OuterAggregationServerLib;

EXTERN_C const CLSID CLSID_OuterAggregationObject;

#ifdef __cplusplus

class DECLSPEC_UUID("DC12616F-3D71-46E2-A6E7-03E736FE20DF")
OuterAggregationObject;
#endif
#endif /* __OuterAggregationServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


