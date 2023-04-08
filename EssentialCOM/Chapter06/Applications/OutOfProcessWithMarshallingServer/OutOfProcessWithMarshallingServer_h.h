

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 21:27:26 2012
 */
/* Compiler settings for OutOfProcessWithMarshallingServer.idl:
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

#ifndef __OutOfProcessWithMarshallingServer_h_h__
#define __OutOfProcessWithMarshallingServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IName_FWD_DEFINED__
#define __IName_FWD_DEFINED__
typedef interface IName IName;
#endif 	/* __IName_FWD_DEFINED__ */


#ifndef __OutOfProcessWithMarshallingObject_FWD_DEFINED__
#define __OutOfProcessWithMarshallingObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class OutOfProcessWithMarshallingObject OutOfProcessWithMarshallingObject;
#else
typedef struct OutOfProcessWithMarshallingObject OutOfProcessWithMarshallingObject;
#endif /* __cplusplus */

#endif 	/* __OutOfProcessWithMarshallingObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IName_INTERFACE_DEFINED__
#define __IName_INTERFACE_DEFINED__

/* interface IName */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IName;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("21F82740-3C47-41B0-AF6B-6F243D3AC79F")
    IName : public IUnknown
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
            /* [size_is][retval][out] */ wchar_t *FirstName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLastName( 
            /* [in] */ int BufferSize,
            /* [size_is][retval][out] */ wchar_t *LastName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAge( 
            /* [retval][out] */ int *Age) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IName * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IName * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IName * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFirstName )( 
            IName * This,
            /* [string][in] */ wchar_t *FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *SetLastName )( 
            IName * This,
            /* [string][in] */ wchar_t *LastName);
        
        HRESULT ( STDMETHODCALLTYPE *SetAge )( 
            IName * This,
            /* [in] */ int Age);
        
        HRESULT ( STDMETHODCALLTYPE *GetFirstName )( 
            IName * This,
            /* [in] */ int BufferSize,
            /* [size_is][retval][out] */ wchar_t *FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastName )( 
            IName * This,
            /* [in] */ int BufferSize,
            /* [size_is][retval][out] */ wchar_t *LastName);
        
        HRESULT ( STDMETHODCALLTYPE *GetAge )( 
            IName * This,
            /* [retval][out] */ int *Age);
        
        END_INTERFACE
    } INameVtbl;

    interface IName
    {
        CONST_VTBL struct INameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IName_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IName_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IName_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IName_SetFirstName(This,FirstName)	\
    ( (This)->lpVtbl -> SetFirstName(This,FirstName) ) 

#define IName_SetLastName(This,LastName)	\
    ( (This)->lpVtbl -> SetLastName(This,LastName) ) 

#define IName_SetAge(This,Age)	\
    ( (This)->lpVtbl -> SetAge(This,Age) ) 

#define IName_GetFirstName(This,BufferSize,FirstName)	\
    ( (This)->lpVtbl -> GetFirstName(This,BufferSize,FirstName) ) 

#define IName_GetLastName(This,BufferSize,LastName)	\
    ( (This)->lpVtbl -> GetLastName(This,BufferSize,LastName) ) 

#define IName_GetAge(This,Age)	\
    ( (This)->lpVtbl -> GetAge(This,Age) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IName_INTERFACE_DEFINED__ */



#ifndef __OutOfProcessWithMarshallingServerLib_LIBRARY_DEFINED__
#define __OutOfProcessWithMarshallingServerLib_LIBRARY_DEFINED__

/* library OutOfProcessWithMarshallingServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_OutOfProcessWithMarshallingServerLib;

EXTERN_C const CLSID CLSID_OutOfProcessWithMarshallingObject;

#ifdef __cplusplus

class DECLSPEC_UUID("1C856AB3-520C-4B2A-B6AC-4A12FEBC06B3")
OutOfProcessWithMarshallingObject;
#endif
#endif /* __OutOfProcessWithMarshallingServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


