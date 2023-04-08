

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 21:39:07 2012
 */
/* Compiler settings for OutOfProcessObject.idl:
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


#ifndef __OutOfProcessObject_h_h__
#define __OutOfProcessObject_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IOutOfProcessName_FWD_DEFINED__
#define __IOutOfProcessName_FWD_DEFINED__
typedef interface IOutOfProcessName IOutOfProcessName;
#endif 	/* __IOutOfProcessName_FWD_DEFINED__ */


#ifndef __OutOfProcessObject_FWD_DEFINED__
#define __OutOfProcessObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class OutOfProcessObject OutOfProcessObject;
#else
typedef struct OutOfProcessObject OutOfProcessObject;
#endif /* __cplusplus */

#endif 	/* __OutOfProcessObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __OutOfProcessServerLib_LIBRARY_DEFINED__
#define __OutOfProcessServerLib_LIBRARY_DEFINED__

/* library OutOfProcessServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_OutOfProcessServerLib;

#ifndef __IOutOfProcessName_INTERFACE_DEFINED__
#define __IOutOfProcessName_INTERFACE_DEFINED__

/* interface IOutOfProcessName */
/* [oleautomation][local][unique][uuid][object] */ 


EXTERN_C const IID IID_IOutOfProcessName;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9146DF93-9AAD-4E0B-B185-2A2B49CA81B0")
    IOutOfProcessName : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetFirstName( 
            /* [string][in] */ BSTR FirstName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetLastName( 
            /* [string][in] */ BSTR LastName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAge( 
            /* [in] */ int Age) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFirstName( 
            /* [retval][string][out] */ BSTR *FirstName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLastName( 
            /* [retval][string][out] */ BSTR *LastName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAge( 
            /* [retval][out] */ int *Age) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOutOfProcessNameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOutOfProcessName * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOutOfProcessName * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOutOfProcessName * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFirstName )( 
            IOutOfProcessName * This,
            /* [string][in] */ BSTR FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *SetLastName )( 
            IOutOfProcessName * This,
            /* [string][in] */ BSTR LastName);
        
        HRESULT ( STDMETHODCALLTYPE *SetAge )( 
            IOutOfProcessName * This,
            /* [in] */ int Age);
        
        HRESULT ( STDMETHODCALLTYPE *GetFirstName )( 
            IOutOfProcessName * This,
            /* [retval][string][out] */ BSTR *FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastName )( 
            IOutOfProcessName * This,
            /* [retval][string][out] */ BSTR *LastName);
        
        HRESULT ( STDMETHODCALLTYPE *GetAge )( 
            IOutOfProcessName * This,
            /* [retval][out] */ int *Age);
        
        END_INTERFACE
    } IOutOfProcessNameVtbl;

    interface IOutOfProcessName
    {
        CONST_VTBL struct IOutOfProcessNameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOutOfProcessName_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IOutOfProcessName_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IOutOfProcessName_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IOutOfProcessName_SetFirstName(This,FirstName)	\
    ( (This)->lpVtbl -> SetFirstName(This,FirstName) ) 

#define IOutOfProcessName_SetLastName(This,LastName)	\
    ( (This)->lpVtbl -> SetLastName(This,LastName) ) 

#define IOutOfProcessName_SetAge(This,Age)	\
    ( (This)->lpVtbl -> SetAge(This,Age) ) 

#define IOutOfProcessName_GetFirstName(This,FirstName)	\
    ( (This)->lpVtbl -> GetFirstName(This,FirstName) ) 

#define IOutOfProcessName_GetLastName(This,LastName)	\
    ( (This)->lpVtbl -> GetLastName(This,LastName) ) 

#define IOutOfProcessName_GetAge(This,Age)	\
    ( (This)->lpVtbl -> GetAge(This,Age) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IOutOfProcessName_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_OutOfProcessObject;

#ifdef __cplusplus

class DECLSPEC_UUID("85BB4CBC-1E27-425B-92E9-B23E4F8240C7")
OutOfProcessObject;
#endif
#endif /* __OutOfProcessServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


