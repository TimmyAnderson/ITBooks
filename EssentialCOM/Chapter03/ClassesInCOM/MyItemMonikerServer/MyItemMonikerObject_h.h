

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 21:39:07 2012
 */
/* Compiler settings for MyItemMonikerObject.idl:
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

#ifndef __MyItemMonikerObject_h_h__
#define __MyItemMonikerObject_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMyItemMonikerName_FWD_DEFINED__
#define __IMyItemMonikerName_FWD_DEFINED__
typedef interface IMyItemMonikerName IMyItemMonikerName;
#endif 	/* __IMyItemMonikerName_FWD_DEFINED__ */


#ifndef __MyItemMonikerObject_FWD_DEFINED__
#define __MyItemMonikerObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyItemMonikerObject MyItemMonikerObject;
#else
typedef struct MyItemMonikerObject MyItemMonikerObject;
#endif /* __cplusplus */

#endif 	/* __MyItemMonikerObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IMyItemMonikerName_INTERFACE_DEFINED__
#define __IMyItemMonikerName_INTERFACE_DEFINED__

/* interface IMyItemMonikerName */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IMyItemMonikerName;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D933DB0E-B0E2-475E-B3E6-A27CE2B39E21")
    IMyItemMonikerName : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetFirstName( 
            /* [string][in] */ wchar_t *FirstName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetLastName( 
            /* [string][in] */ wchar_t *LastName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAge( 
            /* [in] */ int Age) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFirstName( 
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **FirstName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLastName( 
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **LastName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAge( 
            /* [retval][out] */ int *Age) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyItemMonikerNameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyItemMonikerName * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyItemMonikerName * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyItemMonikerName * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFirstName )( 
            IMyItemMonikerName * This,
            /* [string][in] */ wchar_t *FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *SetLastName )( 
            IMyItemMonikerName * This,
            /* [string][in] */ wchar_t *LastName);
        
        HRESULT ( STDMETHODCALLTYPE *SetAge )( 
            IMyItemMonikerName * This,
            /* [in] */ int Age);
        
        HRESULT ( STDMETHODCALLTYPE *GetFirstName )( 
            IMyItemMonikerName * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastName )( 
            IMyItemMonikerName * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **LastName);
        
        HRESULT ( STDMETHODCALLTYPE *GetAge )( 
            IMyItemMonikerName * This,
            /* [retval][out] */ int *Age);
        
        END_INTERFACE
    } IMyItemMonikerNameVtbl;

    interface IMyItemMonikerName
    {
        CONST_VTBL struct IMyItemMonikerNameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyItemMonikerName_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyItemMonikerName_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyItemMonikerName_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyItemMonikerName_SetFirstName(This,FirstName)	\
    ( (This)->lpVtbl -> SetFirstName(This,FirstName) ) 

#define IMyItemMonikerName_SetLastName(This,LastName)	\
    ( (This)->lpVtbl -> SetLastName(This,LastName) ) 

#define IMyItemMonikerName_SetAge(This,Age)	\
    ( (This)->lpVtbl -> SetAge(This,Age) ) 

#define IMyItemMonikerName_GetFirstName(This,BufferSize,FirstName)	\
    ( (This)->lpVtbl -> GetFirstName(This,BufferSize,FirstName) ) 

#define IMyItemMonikerName_GetLastName(This,BufferSize,LastName)	\
    ( (This)->lpVtbl -> GetLastName(This,BufferSize,LastName) ) 

#define IMyItemMonikerName_GetAge(This,Age)	\
    ( (This)->lpVtbl -> GetAge(This,Age) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyItemMonikerName_INTERFACE_DEFINED__ */



#ifndef __MyItemMonikerServerLib_LIBRARY_DEFINED__
#define __MyItemMonikerServerLib_LIBRARY_DEFINED__

/* library MyItemMonikerServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MyItemMonikerServerLib;

EXTERN_C const CLSID CLSID_MyItemMonikerObject;

#ifdef __cplusplus

class DECLSPEC_UUID("6F3F078E-D088-4F1E-BD62-C79F390E8AA6")
MyItemMonikerObject;
#endif
#endif /* __MyItemMonikerServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


