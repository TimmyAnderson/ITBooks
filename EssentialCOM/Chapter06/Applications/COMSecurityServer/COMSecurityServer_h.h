

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 21:27:26 2012
 */
/* Compiler settings for COMSecurityServer.idl:
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

#ifndef __COMSecurityServer_h_h__
#define __COMSecurityServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IName_FWD_DEFINED__
#define __IName_FWD_DEFINED__
typedef interface IName IName;
#endif 	/* __IName_FWD_DEFINED__ */


#ifndef __COMSecurityObject_FWD_DEFINED__
#define __COMSecurityObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class COMSecurityObject COMSecurityObject;
#else
typedef struct COMSecurityObject COMSecurityObject;
#endif /* __cplusplus */

#endif 	/* __COMSecurityObject_FWD_DEFINED__ */


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
    
    MIDL_INTERFACE("65A09033-94A6-47A4-8C8F-5BA1FE41DFC9")
    IName : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetName( 
            /* [string][in] */ wchar_t *Name) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetName( 
            /* [in] */ int BufferSize,
            /* [size_is][retval][out] */ wchar_t *Name) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PrintSecuritySettings( void) = 0;
        
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
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            IName * This,
            /* [string][in] */ wchar_t *Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IName * This,
            /* [in] */ int BufferSize,
            /* [size_is][retval][out] */ wchar_t *Name);
        
        HRESULT ( STDMETHODCALLTYPE *PrintSecuritySettings )( 
            IName * This);
        
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


#define IName_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 

#define IName_GetName(This,BufferSize,Name)	\
    ( (This)->lpVtbl -> GetName(This,BufferSize,Name) ) 

#define IName_PrintSecuritySettings(This)	\
    ( (This)->lpVtbl -> PrintSecuritySettings(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IName_INTERFACE_DEFINED__ */



#ifndef __COMSecurityServerLib_LIBRARY_DEFINED__
#define __COMSecurityServerLib_LIBRARY_DEFINED__

/* library COMSecurityServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_COMSecurityServerLib;

EXTERN_C const CLSID CLSID_COMSecurityObject;

#ifdef __cplusplus

class DECLSPEC_UUID("9D19A76B-4368-4818-89D1-F9E27E0B96A6")
COMSecurityObject;
#endif
#endif /* __COMSecurityServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


