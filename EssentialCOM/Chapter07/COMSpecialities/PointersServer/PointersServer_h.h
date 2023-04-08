

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Aug 09 22:52:30 2012
 */
/* Compiler settings for PointersServer.idl:
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

#ifndef __PointersServer_h_h__
#define __PointersServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPointersTest_FWD_DEFINED__
#define __IPointersTest_FWD_DEFINED__
typedef interface IPointersTest IPointersTest;
#endif 	/* __IPointersTest_FWD_DEFINED__ */


#ifndef __PointersObject_FWD_DEFINED__
#define __PointersObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class PointersObject PointersObject;
#else
typedef struct PointersObject PointersObject;
#endif /* __cplusplus */

#endif 	/* __PointersObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_PointersServer_0000_0000 */
/* [local] */ 

/* [uuid] */ struct  DECLSPEC_UUID("E4768B86-34C3-4228-A517-A6D3D2F48D09") SName
    {
    wchar_t *MName;
    } ;


extern RPC_IF_HANDLE __MIDL_itf_PointersServer_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_PointersServer_0000_0000_v0_0_s_ifspec;

#ifndef __IPointersTest_INTERFACE_DEFINED__
#define __IPointersTest_INTERFACE_DEFINED__

/* interface IPointersTest */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IPointersTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1C1DEA36-A300-49EA-9726-DE638A6F56C9")
    IPointersTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Dummy( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NoAttributePointer( 
            /* [in] */ int *Pointer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RefAttributePointer( 
            /* [ref][in] */ int *Pointer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UniqueAttributePointer( 
            /* [unique][in] */ int *Pointer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NoPtrAttributePointer( 
            /* [in] */ int *Pointer1,
            /* [in] */ int *Pointer2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PtrAttributePointer( 
            /* [full][in] */ int *Pointer1,
            /* [full][in] */ int *Pointer2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MallocSpyTest( 
            /* [out] */ int **PointerToMallocData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MemoryAllocatedByServer( 
            /* [out] */ struct SName *Name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPointersTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPointersTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPointersTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPointersTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *Dummy )( 
            IPointersTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *NoAttributePointer )( 
            IPointersTest * This,
            /* [in] */ int *Pointer);
        
        HRESULT ( STDMETHODCALLTYPE *RefAttributePointer )( 
            IPointersTest * This,
            /* [ref][in] */ int *Pointer);
        
        HRESULT ( STDMETHODCALLTYPE *UniqueAttributePointer )( 
            IPointersTest * This,
            /* [unique][in] */ int *Pointer);
        
        HRESULT ( STDMETHODCALLTYPE *NoPtrAttributePointer )( 
            IPointersTest * This,
            /* [in] */ int *Pointer1,
            /* [in] */ int *Pointer2);
        
        HRESULT ( STDMETHODCALLTYPE *PtrAttributePointer )( 
            IPointersTest * This,
            /* [full][in] */ int *Pointer1,
            /* [full][in] */ int *Pointer2);
        
        HRESULT ( STDMETHODCALLTYPE *MallocSpyTest )( 
            IPointersTest * This,
            /* [out] */ int **PointerToMallocData);
        
        HRESULT ( STDMETHODCALLTYPE *MemoryAllocatedByServer )( 
            IPointersTest * This,
            /* [out] */ struct SName *Name);
        
        END_INTERFACE
    } IPointersTestVtbl;

    interface IPointersTest
    {
        CONST_VTBL struct IPointersTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPointersTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPointersTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPointersTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPointersTest_Dummy(This)	\
    ( (This)->lpVtbl -> Dummy(This) ) 

#define IPointersTest_NoAttributePointer(This,Pointer)	\
    ( (This)->lpVtbl -> NoAttributePointer(This,Pointer) ) 

#define IPointersTest_RefAttributePointer(This,Pointer)	\
    ( (This)->lpVtbl -> RefAttributePointer(This,Pointer) ) 

#define IPointersTest_UniqueAttributePointer(This,Pointer)	\
    ( (This)->lpVtbl -> UniqueAttributePointer(This,Pointer) ) 

#define IPointersTest_NoPtrAttributePointer(This,Pointer1,Pointer2)	\
    ( (This)->lpVtbl -> NoPtrAttributePointer(This,Pointer1,Pointer2) ) 

#define IPointersTest_PtrAttributePointer(This,Pointer1,Pointer2)	\
    ( (This)->lpVtbl -> PtrAttributePointer(This,Pointer1,Pointer2) ) 

#define IPointersTest_MallocSpyTest(This,PointerToMallocData)	\
    ( (This)->lpVtbl -> MallocSpyTest(This,PointerToMallocData) ) 

#define IPointersTest_MemoryAllocatedByServer(This,Name)	\
    ( (This)->lpVtbl -> MemoryAllocatedByServer(This,Name) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPointersTest_INTERFACE_DEFINED__ */



#ifndef __PointersServerLib_LIBRARY_DEFINED__
#define __PointersServerLib_LIBRARY_DEFINED__

/* library PointersServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_PointersServerLib;

EXTERN_C const CLSID CLSID_PointersObject;

#ifdef __cplusplus

class DECLSPEC_UUID("FF456034-3E42-4591-B1A4-382A1470F96D")
PointersObject;
#endif
#endif /* __PointersServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


