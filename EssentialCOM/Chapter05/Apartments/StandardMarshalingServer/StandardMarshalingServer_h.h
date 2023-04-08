

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 22:15:44 2012
 */
/* Compiler settings for StandardMarshalingServer.idl:
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

#ifndef __StandardMarshalingServer_h_h__
#define __StandardMarshalingServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IStandardMarshalingTest_FWD_DEFINED__
#define __IStandardMarshalingTest_FWD_DEFINED__
typedef interface IStandardMarshalingTest IStandardMarshalingTest;
#endif 	/* __IStandardMarshalingTest_FWD_DEFINED__ */


#ifndef __StandardMarshalingObject_FWD_DEFINED__
#define __StandardMarshalingObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class StandardMarshalingObject StandardMarshalingObject;
#else
typedef struct StandardMarshalingObject StandardMarshalingObject;
#endif /* __cplusplus */

#endif 	/* __StandardMarshalingObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IStandardMarshalingTest_INTERFACE_DEFINED__
#define __IStandardMarshalingTest_INTERFACE_DEFINED__

/* interface IStandardMarshalingTest */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IStandardMarshalingTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1E353167-DFFC-4374-92A6-504259BE17D9")
    IStandardMarshalingTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IncrementValue( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [out] */ long *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStandardMarshalingTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStandardMarshalingTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStandardMarshalingTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStandardMarshalingTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *IncrementValue )( 
            IStandardMarshalingTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            IStandardMarshalingTest * This,
            /* [out] */ long *Value);
        
        END_INTERFACE
    } IStandardMarshalingTestVtbl;

    interface IStandardMarshalingTest
    {
        CONST_VTBL struct IStandardMarshalingTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStandardMarshalingTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStandardMarshalingTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStandardMarshalingTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStandardMarshalingTest_IncrementValue(This)	\
    ( (This)->lpVtbl -> IncrementValue(This) ) 

#define IStandardMarshalingTest_GetValue(This,Value)	\
    ( (This)->lpVtbl -> GetValue(This,Value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStandardMarshalingTest_INTERFACE_DEFINED__ */



#ifndef __StandardMarshalingServerLib_LIBRARY_DEFINED__
#define __StandardMarshalingServerLib_LIBRARY_DEFINED__

/* library StandardMarshalingServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_StandardMarshalingServerLib;

EXTERN_C const CLSID CLSID_StandardMarshalingObject;

#ifdef __cplusplus

class DECLSPEC_UUID("A7D6E752-4695-4958-BF57-BCE759EB3C97")
StandardMarshalingObject;
#endif
#endif /* __StandardMarshalingServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


