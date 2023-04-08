

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:00:06 2012
 */
/* Compiler settings for CompositionServer.idl:
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

#ifndef __CompositionServer_h_h__
#define __CompositionServer_h_h__

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


#ifndef __CompositionObject_FWD_DEFINED__
#define __CompositionObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CompositionObject CompositionObject;
#else
typedef struct CompositionObject CompositionObject;
#endif /* __cplusplus */

#endif 	/* __CompositionObject_FWD_DEFINED__ */


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
    
    MIDL_INTERFACE("646D0B35-9E94-439A-B049-4C59120940B5")
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
    
    MIDL_INTERFACE("06C84E8D-52D5-4080-BFC7-7D8C933AD616")
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



#ifndef __CompositionServerLib_LIBRARY_DEFINED__
#define __CompositionServerLib_LIBRARY_DEFINED__

/* library CompositionServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_CompositionServerLib;

EXTERN_C const CLSID CLSID_CompositionObject;

#ifdef __cplusplus

class DECLSPEC_UUID("48C0A70D-E917-49D9-855A-DC4459066B1C")
CompositionObject;
#endif
#endif /* __CompositionServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


