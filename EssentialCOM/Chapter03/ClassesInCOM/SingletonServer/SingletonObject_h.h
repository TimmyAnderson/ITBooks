

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 21:39:06 2012
 */
/* Compiler settings for SingletonObject.idl:
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

#ifndef __SingletonObject_h_h__
#define __SingletonObject_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISingletonName_FWD_DEFINED__
#define __ISingletonName_FWD_DEFINED__
typedef interface ISingletonName ISingletonName;
#endif 	/* __ISingletonName_FWD_DEFINED__ */


#ifndef __SingletonObject_FWD_DEFINED__
#define __SingletonObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class SingletonObject SingletonObject;
#else
typedef struct SingletonObject SingletonObject;
#endif /* __cplusplus */

#endif 	/* __SingletonObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ISingletonName_INTERFACE_DEFINED__
#define __ISingletonName_INTERFACE_DEFINED__

/* interface ISingletonName */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_ISingletonName;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DA20BB21-ED75-4C4D-939A-367D7E63F8D3")
    ISingletonName : public IUnknown
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

    typedef struct ISingletonNameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISingletonName * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISingletonName * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISingletonName * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFirstName )( 
            ISingletonName * This,
            /* [string][in] */ wchar_t *FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *SetLastName )( 
            ISingletonName * This,
            /* [string][in] */ wchar_t *LastName);
        
        HRESULT ( STDMETHODCALLTYPE *SetAge )( 
            ISingletonName * This,
            /* [in] */ int Age);
        
        HRESULT ( STDMETHODCALLTYPE *GetFirstName )( 
            ISingletonName * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastName )( 
            ISingletonName * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **LastName);
        
        HRESULT ( STDMETHODCALLTYPE *GetAge )( 
            ISingletonName * This,
            /* [retval][out] */ int *Age);
        
        END_INTERFACE
    } ISingletonNameVtbl;

    interface ISingletonName
    {
        CONST_VTBL struct ISingletonNameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISingletonName_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISingletonName_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISingletonName_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISingletonName_SetFirstName(This,FirstName)	\
    ( (This)->lpVtbl -> SetFirstName(This,FirstName) ) 

#define ISingletonName_SetLastName(This,LastName)	\
    ( (This)->lpVtbl -> SetLastName(This,LastName) ) 

#define ISingletonName_SetAge(This,Age)	\
    ( (This)->lpVtbl -> SetAge(This,Age) ) 

#define ISingletonName_GetFirstName(This,BufferSize,FirstName)	\
    ( (This)->lpVtbl -> GetFirstName(This,BufferSize,FirstName) ) 

#define ISingletonName_GetLastName(This,BufferSize,LastName)	\
    ( (This)->lpVtbl -> GetLastName(This,BufferSize,LastName) ) 

#define ISingletonName_GetAge(This,Age)	\
    ( (This)->lpVtbl -> GetAge(This,Age) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISingletonName_INTERFACE_DEFINED__ */



#ifndef __SingletonServerLib_LIBRARY_DEFINED__
#define __SingletonServerLib_LIBRARY_DEFINED__

/* library SingletonServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_SingletonServerLib;

EXTERN_C const CLSID CLSID_SingletonObject;

#ifdef __cplusplus

class DECLSPEC_UUID("BC66939B-0747-4085-8F12-42BE0423AB5B")
SingletonObject;
#endif
#endif /* __SingletonServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


