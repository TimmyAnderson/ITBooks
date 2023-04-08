

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:15:45 2012
 */
/* Compiler settings for CustomMarshalingByValueServer.idl:
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

#ifndef __CustomMarshalingByValueServer_h_h__
#define __CustomMarshalingByValueServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICustomMarshalingByValueTest_FWD_DEFINED__
#define __ICustomMarshalingByValueTest_FWD_DEFINED__
typedef interface ICustomMarshalingByValueTest ICustomMarshalingByValueTest;
#endif 	/* __ICustomMarshalingByValueTest_FWD_DEFINED__ */


#ifndef __CustomMarshalingByValueObject_FWD_DEFINED__
#define __CustomMarshalingByValueObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CustomMarshalingByValueObject CustomMarshalingByValueObject;
#else
typedef struct CustomMarshalingByValueObject CustomMarshalingByValueObject;
#endif /* __cplusplus */

#endif 	/* __CustomMarshalingByValueObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICustomMarshalingByValueTest_INTERFACE_DEFINED__
#define __ICustomMarshalingByValueTest_INTERFACE_DEFINED__

/* interface ICustomMarshalingByValueTest */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ICustomMarshalingByValueTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("18D909F7-AEBA-4D61-9A9E-2461BE1CE2A6")
    ICustomMarshalingByValueTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetValue( 
            /* [in] */ long Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [out] */ long *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICustomMarshalingByValueTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICustomMarshalingByValueTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICustomMarshalingByValueTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICustomMarshalingByValueTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetValue )( 
            ICustomMarshalingByValueTest * This,
            /* [in] */ long Value);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            ICustomMarshalingByValueTest * This,
            /* [out] */ long *Value);
        
        END_INTERFACE
    } ICustomMarshalingByValueTestVtbl;

    interface ICustomMarshalingByValueTest
    {
        CONST_VTBL struct ICustomMarshalingByValueTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICustomMarshalingByValueTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICustomMarshalingByValueTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICustomMarshalingByValueTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICustomMarshalingByValueTest_SetValue(This,Value)	\
    ( (This)->lpVtbl -> SetValue(This,Value) ) 

#define ICustomMarshalingByValueTest_GetValue(This,Value)	\
    ( (This)->lpVtbl -> GetValue(This,Value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICustomMarshalingByValueTest_INTERFACE_DEFINED__ */



#ifndef __CustomMarshalingByValueServerLib_LIBRARY_DEFINED__
#define __CustomMarshalingByValueServerLib_LIBRARY_DEFINED__

/* library CustomMarshalingByValueServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_CustomMarshalingByValueServerLib;

EXTERN_C const CLSID CLSID_CustomMarshalingByValueObject;

#ifdef __cplusplus

class DECLSPEC_UUID("1C235F9E-DEC0-4A69-A8A4-AAFE9962B953")
CustomMarshalingByValueObject;
#endif
#endif /* __CustomMarshalingByValueServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


