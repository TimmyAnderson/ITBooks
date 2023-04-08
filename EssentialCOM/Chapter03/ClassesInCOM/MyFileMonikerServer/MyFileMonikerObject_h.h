

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 21:39:06 2012
 */
/* Compiler settings for MyFileMonikerObject.idl:
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

#ifndef __MyFileMonikerObject_h_h__
#define __MyFileMonikerObject_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMyFileMonikerName_FWD_DEFINED__
#define __IMyFileMonikerName_FWD_DEFINED__
typedef interface IMyFileMonikerName IMyFileMonikerName;
#endif 	/* __IMyFileMonikerName_FWD_DEFINED__ */


#ifndef __MyFileMonikerObject_FWD_DEFINED__
#define __MyFileMonikerObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyFileMonikerObject MyFileMonikerObject;
#else
typedef struct MyFileMonikerObject MyFileMonikerObject;
#endif /* __cplusplus */

#endif 	/* __MyFileMonikerObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IMyFileMonikerName_INTERFACE_DEFINED__
#define __IMyFileMonikerName_INTERFACE_DEFINED__

/* interface IMyFileMonikerName */
/* [oleautomation][local][unique][uuid][object] */ 


EXTERN_C const IID IID_IMyFileMonikerName;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("84B88743-D0EE-438A-929F-4C8CE49137F3")
    IMyFileMonikerName : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetFirstName( 
            /* [string][in] */ BSTR FirstName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetLastName( 
            /* [string][in] */ BSTR LastName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAge( 
            /* [in] */ int Age) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFirstName( 
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ BSTR *FirstName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLastName( 
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ BSTR *LastName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAge( 
            /* [retval][out] */ int *Age) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyFileMonikerNameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyFileMonikerName * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyFileMonikerName * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyFileMonikerName * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFirstName )( 
            IMyFileMonikerName * This,
            /* [string][in] */ BSTR FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *SetLastName )( 
            IMyFileMonikerName * This,
            /* [string][in] */ BSTR LastName);
        
        HRESULT ( STDMETHODCALLTYPE *SetAge )( 
            IMyFileMonikerName * This,
            /* [in] */ int Age);
        
        HRESULT ( STDMETHODCALLTYPE *GetFirstName )( 
            IMyFileMonikerName * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ BSTR *FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastName )( 
            IMyFileMonikerName * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ BSTR *LastName);
        
        HRESULT ( STDMETHODCALLTYPE *GetAge )( 
            IMyFileMonikerName * This,
            /* [retval][out] */ int *Age);
        
        END_INTERFACE
    } IMyFileMonikerNameVtbl;

    interface IMyFileMonikerName
    {
        CONST_VTBL struct IMyFileMonikerNameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyFileMonikerName_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyFileMonikerName_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyFileMonikerName_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyFileMonikerName_SetFirstName(This,FirstName)	\
    ( (This)->lpVtbl -> SetFirstName(This,FirstName) ) 

#define IMyFileMonikerName_SetLastName(This,LastName)	\
    ( (This)->lpVtbl -> SetLastName(This,LastName) ) 

#define IMyFileMonikerName_SetAge(This,Age)	\
    ( (This)->lpVtbl -> SetAge(This,Age) ) 

#define IMyFileMonikerName_GetFirstName(This,BufferSize,FirstName)	\
    ( (This)->lpVtbl -> GetFirstName(This,BufferSize,FirstName) ) 

#define IMyFileMonikerName_GetLastName(This,BufferSize,LastName)	\
    ( (This)->lpVtbl -> GetLastName(This,BufferSize,LastName) ) 

#define IMyFileMonikerName_GetAge(This,Age)	\
    ( (This)->lpVtbl -> GetAge(This,Age) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyFileMonikerName_INTERFACE_DEFINED__ */



#ifndef __MyFileMonikerServerLib_LIBRARY_DEFINED__
#define __MyFileMonikerServerLib_LIBRARY_DEFINED__

/* library MyFileMonikerServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MyFileMonikerServerLib;

EXTERN_C const CLSID CLSID_MyFileMonikerObject;

#ifdef __cplusplus

class DECLSPEC_UUID("B9A83743-624A-46AD-B409-DA0816C9F1C5")
MyFileMonikerObject;
#endif
#endif /* __MyFileMonikerServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


