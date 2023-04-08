

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 21:39:06 2012
 */
/* Compiler settings for ComponentCategoriesObject.idl:
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

#ifndef __ComponentCategoriesObject_h_h__
#define __ComponentCategoriesObject_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IComponentCategoriesName_FWD_DEFINED__
#define __IComponentCategoriesName_FWD_DEFINED__
typedef interface IComponentCategoriesName IComponentCategoriesName;
#endif 	/* __IComponentCategoriesName_FWD_DEFINED__ */


#ifndef __ComponentCategoriesObject_FWD_DEFINED__
#define __ComponentCategoriesObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class ComponentCategoriesObject ComponentCategoriesObject;
#else
typedef struct ComponentCategoriesObject ComponentCategoriesObject;
#endif /* __cplusplus */

#endif 	/* __ComponentCategoriesObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IComponentCategoriesName_INTERFACE_DEFINED__
#define __IComponentCategoriesName_INTERFACE_DEFINED__

/* interface IComponentCategoriesName */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IComponentCategoriesName;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8F86F1ED-437A-4AD3-9145-C8555480C394")
    IComponentCategoriesName : public IUnknown
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

    typedef struct IComponentCategoriesNameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IComponentCategoriesName * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IComponentCategoriesName * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IComponentCategoriesName * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFirstName )( 
            IComponentCategoriesName * This,
            /* [string][in] */ wchar_t *FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *SetLastName )( 
            IComponentCategoriesName * This,
            /* [string][in] */ wchar_t *LastName);
        
        HRESULT ( STDMETHODCALLTYPE *SetAge )( 
            IComponentCategoriesName * This,
            /* [in] */ int Age);
        
        HRESULT ( STDMETHODCALLTYPE *GetFirstName )( 
            IComponentCategoriesName * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastName )( 
            IComponentCategoriesName * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **LastName);
        
        HRESULT ( STDMETHODCALLTYPE *GetAge )( 
            IComponentCategoriesName * This,
            /* [retval][out] */ int *Age);
        
        END_INTERFACE
    } IComponentCategoriesNameVtbl;

    interface IComponentCategoriesName
    {
        CONST_VTBL struct IComponentCategoriesNameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComponentCategoriesName_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IComponentCategoriesName_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IComponentCategoriesName_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IComponentCategoriesName_SetFirstName(This,FirstName)	\
    ( (This)->lpVtbl -> SetFirstName(This,FirstName) ) 

#define IComponentCategoriesName_SetLastName(This,LastName)	\
    ( (This)->lpVtbl -> SetLastName(This,LastName) ) 

#define IComponentCategoriesName_SetAge(This,Age)	\
    ( (This)->lpVtbl -> SetAge(This,Age) ) 

#define IComponentCategoriesName_GetFirstName(This,BufferSize,FirstName)	\
    ( (This)->lpVtbl -> GetFirstName(This,BufferSize,FirstName) ) 

#define IComponentCategoriesName_GetLastName(This,BufferSize,LastName)	\
    ( (This)->lpVtbl -> GetLastName(This,BufferSize,LastName) ) 

#define IComponentCategoriesName_GetAge(This,Age)	\
    ( (This)->lpVtbl -> GetAge(This,Age) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IComponentCategoriesName_INTERFACE_DEFINED__ */



#ifndef __ComponentCategoriesServerLib_LIBRARY_DEFINED__
#define __ComponentCategoriesServerLib_LIBRARY_DEFINED__

/* library ComponentCategoriesServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ComponentCategoriesServerLib;

EXTERN_C const CLSID CLSID_ComponentCategoriesObject;

#ifdef __cplusplus

class DECLSPEC_UUID("7B863799-2690-4EC0-86DD-F4D485FEE332")
ComponentCategoriesObject;
#endif
#endif /* __ComponentCategoriesServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


