

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 21:39:06 2012
 */
/* Compiler settings for InProcessObject.idl:
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

#ifndef __InProcessObject_h_h__
#define __InProcessObject_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IInProcessName_FWD_DEFINED__
#define __IInProcessName_FWD_DEFINED__
typedef interface IInProcessName IInProcessName;
#endif 	/* __IInProcessName_FWD_DEFINED__ */


#ifndef __InProcessObject_FWD_DEFINED__
#define __InProcessObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class InProcessObject InProcessObject;
#else
typedef struct InProcessObject InProcessObject;
#endif /* __cplusplus */

#endif 	/* __InProcessObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IInProcessName_INTERFACE_DEFINED__
#define __IInProcessName_INTERFACE_DEFINED__

/* interface IInProcessName */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IInProcessName;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7B494096-E8B0-46B2-AC87-9A0C1B04395F")
    IInProcessName : public IUnknown
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

    typedef struct IInProcessNameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInProcessName * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInProcessName * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInProcessName * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFirstName )( 
            IInProcessName * This,
            /* [string][in] */ wchar_t *FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *SetLastName )( 
            IInProcessName * This,
            /* [string][in] */ wchar_t *LastName);
        
        HRESULT ( STDMETHODCALLTYPE *SetAge )( 
            IInProcessName * This,
            /* [in] */ int Age);
        
        HRESULT ( STDMETHODCALLTYPE *GetFirstName )( 
            IInProcessName * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastName )( 
            IInProcessName * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **LastName);
        
        HRESULT ( STDMETHODCALLTYPE *GetAge )( 
            IInProcessName * This,
            /* [retval][out] */ int *Age);
        
        END_INTERFACE
    } IInProcessNameVtbl;

    interface IInProcessName
    {
        CONST_VTBL struct IInProcessNameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInProcessName_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInProcessName_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInProcessName_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInProcessName_SetFirstName(This,FirstName)	\
    ( (This)->lpVtbl -> SetFirstName(This,FirstName) ) 

#define IInProcessName_SetLastName(This,LastName)	\
    ( (This)->lpVtbl -> SetLastName(This,LastName) ) 

#define IInProcessName_SetAge(This,Age)	\
    ( (This)->lpVtbl -> SetAge(This,Age) ) 

#define IInProcessName_GetFirstName(This,BufferSize,FirstName)	\
    ( (This)->lpVtbl -> GetFirstName(This,BufferSize,FirstName) ) 

#define IInProcessName_GetLastName(This,BufferSize,LastName)	\
    ( (This)->lpVtbl -> GetLastName(This,BufferSize,LastName) ) 

#define IInProcessName_GetAge(This,Age)	\
    ( (This)->lpVtbl -> GetAge(This,Age) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInProcessName_INTERFACE_DEFINED__ */



#ifndef __InProcessServerLib_LIBRARY_DEFINED__
#define __InProcessServerLib_LIBRARY_DEFINED__

/* library InProcessServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_InProcessServerLib;

EXTERN_C const CLSID CLSID_InProcessObject;

#ifdef __cplusplus

class DECLSPEC_UUID("4E72CC54-3EC7-4240-9AAB-45285DB4B2FD")
InProcessObject;
#endif
#endif /* __InProcessServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


