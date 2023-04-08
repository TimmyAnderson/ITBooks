

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:00:06 2012
 */
/* Compiler settings for InnerAggregationObject.idl:
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

#ifndef __InnerAggregationObject_h_h__
#define __InnerAggregationObject_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IInnerAggregationText_FWD_DEFINED__
#define __IInnerAggregationText_FWD_DEFINED__
typedef interface IInnerAggregationText IInnerAggregationText;
#endif 	/* __IInnerAggregationText_FWD_DEFINED__ */


#ifndef __InnerAggregationObject_FWD_DEFINED__
#define __InnerAggregationObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class InnerAggregationObject InnerAggregationObject;
#else
typedef struct InnerAggregationObject InnerAggregationObject;
#endif /* __cplusplus */

#endif 	/* __InnerAggregationObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IInnerAggregationText_INTERFACE_DEFINED__
#define __IInnerAggregationText_INTERFACE_DEFINED__

/* interface IInnerAggregationText */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IInnerAggregationText;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0B2BAE96-B537-4B45-AD84-A044E31F934C")
    IInnerAggregationText : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetText( 
            /* [string][in] */ wchar_t *Text) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetText( 
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **Text) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInnerAggregationTextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInnerAggregationText * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInnerAggregationText * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInnerAggregationText * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetText )( 
            IInnerAggregationText * This,
            /* [string][in] */ wchar_t *Text);
        
        HRESULT ( STDMETHODCALLTYPE *GetText )( 
            IInnerAggregationText * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **Text);
        
        END_INTERFACE
    } IInnerAggregationTextVtbl;

    interface IInnerAggregationText
    {
        CONST_VTBL struct IInnerAggregationTextVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInnerAggregationText_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInnerAggregationText_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInnerAggregationText_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInnerAggregationText_SetText(This,Text)	\
    ( (This)->lpVtbl -> SetText(This,Text) ) 

#define IInnerAggregationText_GetText(This,BufferSize,Text)	\
    ( (This)->lpVtbl -> GetText(This,BufferSize,Text) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInnerAggregationText_INTERFACE_DEFINED__ */



#ifndef __InnerAggregationServerLib_LIBRARY_DEFINED__
#define __InnerAggregationServerLib_LIBRARY_DEFINED__

/* library InnerAggregationServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_InnerAggregationServerLib;

EXTERN_C const CLSID CLSID_InnerAggregationObject;

#ifdef __cplusplus

class DECLSPEC_UUID("F5ED13D1-CF4A-41CC-96D7-9F54E995052F")
InnerAggregationObject;
#endif
#endif /* __InnerAggregationServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


