

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 05 21:30:38 2012
 */
/* Compiler settings for MultiInterfaceCOM.idl:
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

#ifndef __MultiInterfaceCOM_h_h__
#define __MultiInterfaceCOM_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IName_FWD_DEFINED__
#define __IName_FWD_DEFINED__
typedef interface IName IName;
#endif 	/* __IName_FWD_DEFINED__ */


#ifndef __IToString_FWD_DEFINED__
#define __IToString_FWD_DEFINED__
typedef interface IToString IToString;
#endif 	/* __IToString_FWD_DEFINED__ */


#ifndef __ITest_FWD_DEFINED__
#define __ITest_FWD_DEFINED__
typedef interface ITest ITest;
#endif 	/* __ITest_FWD_DEFINED__ */


#ifndef __IExceptionTest_FWD_DEFINED__
#define __IExceptionTest_FWD_DEFINED__
typedef interface IExceptionTest IExceptionTest;
#endif 	/* __IExceptionTest_FWD_DEFINED__ */


#ifndef __MultiInterfaceCOM_FWD_DEFINED__
#define __MultiInterfaceCOM_FWD_DEFINED__

#ifdef __cplusplus
typedef class MultiInterfaceCOM MultiInterfaceCOM;
#else
typedef struct MultiInterfaceCOM MultiInterfaceCOM;
#endif /* __cplusplus */

#endif 	/* __MultiInterfaceCOM_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_MultiInterfaceCOM_0000_0000 */
/* [local] */ 

/* [uuid] */ struct  DECLSPEC_UUID("53B3B9B2-D565-4608-A8DD-CA9E767448D4") SName
    {
    wchar_t *MFirstName;
    wchar_t *MLastName;
    int MAge;
    } ;
/* [switch_type] */ union UAge
    {
    int MIntAge;
    long MLongAge;
    double MDouble;
    } ;


extern RPC_IF_HANDLE __MIDL_itf_MultiInterfaceCOM_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MultiInterfaceCOM_0000_0000_v0_0_s_ifspec;

#ifndef __IName_INTERFACE_DEFINED__
#define __IName_INTERFACE_DEFINED__

/* interface IName */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IName;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("66F4B6C1-2A1D-4CA7-8CEC-2A2369F583C4")
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
            /* [retval][string][out] */ wchar_t **FirstName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLastName( 
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **LastName) = 0;
        
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
            /* [retval][string][out] */ wchar_t **FirstName);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastName )( 
            IName * This,
            /* [in] */ int BufferSize,
            /* [retval][string][out] */ wchar_t **LastName);
        
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


#ifndef __IToString_INTERFACE_DEFINED__
#define __IToString_INTERFACE_DEFINED__

/* interface IToString */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IToString;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9BF6F5F0-C48B-4919-A73D-FA28F05C60BE")
    IToString : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ToString( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IToStringVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IToString * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IToString * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IToString * This);
        
        HRESULT ( STDMETHODCALLTYPE *ToString )( 
            IToString * This);
        
        END_INTERFACE
    } IToStringVtbl;

    interface IToString
    {
        CONST_VTBL struct IToStringVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IToString_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IToString_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IToString_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IToString_ToString(This)	\
    ( (This)->lpVtbl -> ToString(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IToString_INTERFACE_DEFINED__ */


#ifndef __ITest_INTERFACE_DEFINED__
#define __ITest_INTERFACE_DEFINED__

/* interface ITest */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_ITest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CB02484F-0B97-47F4-A2E7-709B2575D98D")
    ITest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetString( 
            /* [in] */ BSTR Text) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetString( 
            /* [retval][out] */ BSTR *Text) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetName( 
            /* [in] */ struct SName Name) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetName( 
            /* [retval][out] */ struct SName *Name) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetUnion( 
            /* [in] */ int DiscriminatorField,
            /* [switch_is][in] */ union UAge Age) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetUnion( 
            /* [in] */ int DiscriminatorField,
            /* [retval][switch_is][out] */ union UAge *Age) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVariant( 
            /* [in] */ VARIANT Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVariant( 
            /* [retval][out] */ VARIANT *Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Print1( 
            /* [in] */ IToString *Interface) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Print2( 
            /* [in] */ REFIID InterfaceID,
            /* [iid_is][in] */ IUnknown *Interface) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MyProperty( 
            /* [in] */ int Value) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MyProperty( 
            /* [retval][out] */ int *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITest * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetString )( 
            ITest * This,
            /* [in] */ BSTR Text);
        
        HRESULT ( STDMETHODCALLTYPE *GetString )( 
            ITest * This,
            /* [retval][out] */ BSTR *Text);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ITest * This,
            /* [in] */ struct SName Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            ITest * This,
            /* [retval][out] */ struct SName *Name);
        
        HRESULT ( STDMETHODCALLTYPE *SetUnion )( 
            ITest * This,
            /* [in] */ int DiscriminatorField,
            /* [switch_is][in] */ union UAge Age);
        
        HRESULT ( STDMETHODCALLTYPE *GetUnion )( 
            ITest * This,
            /* [in] */ int DiscriminatorField,
            /* [retval][switch_is][out] */ union UAge *Age);
        
        HRESULT ( STDMETHODCALLTYPE *SetVariant )( 
            ITest * This,
            /* [in] */ VARIANT Value);
        
        HRESULT ( STDMETHODCALLTYPE *GetVariant )( 
            ITest * This,
            /* [retval][out] */ VARIANT *Value);
        
        HRESULT ( STDMETHODCALLTYPE *Print1 )( 
            ITest * This,
            /* [in] */ IToString *Interface);
        
        HRESULT ( STDMETHODCALLTYPE *Print2 )( 
            ITest * This,
            /* [in] */ REFIID InterfaceID,
            /* [iid_is][in] */ IUnknown *Interface);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MyProperty )( 
            ITest * This,
            /* [in] */ int Value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MyProperty )( 
            ITest * This,
            /* [retval][out] */ int *Value);
        
        END_INTERFACE
    } ITestVtbl;

    interface ITest
    {
        CONST_VTBL struct ITestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITest_SetString(This,Text)	\
    ( (This)->lpVtbl -> SetString(This,Text) ) 

#define ITest_GetString(This,Text)	\
    ( (This)->lpVtbl -> GetString(This,Text) ) 

#define ITest_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 

#define ITest_GetName(This,Name)	\
    ( (This)->lpVtbl -> GetName(This,Name) ) 

#define ITest_SetUnion(This,DiscriminatorField,Age)	\
    ( (This)->lpVtbl -> SetUnion(This,DiscriminatorField,Age) ) 

#define ITest_GetUnion(This,DiscriminatorField,Age)	\
    ( (This)->lpVtbl -> GetUnion(This,DiscriminatorField,Age) ) 

#define ITest_SetVariant(This,Value)	\
    ( (This)->lpVtbl -> SetVariant(This,Value) ) 

#define ITest_GetVariant(This,Value)	\
    ( (This)->lpVtbl -> GetVariant(This,Value) ) 

#define ITest_Print1(This,Interface)	\
    ( (This)->lpVtbl -> Print1(This,Interface) ) 

#define ITest_Print2(This,InterfaceID,Interface)	\
    ( (This)->lpVtbl -> Print2(This,InterfaceID,Interface) ) 

#define ITest_put_MyProperty(This,Value)	\
    ( (This)->lpVtbl -> put_MyProperty(This,Value) ) 

#define ITest_get_MyProperty(This,Value)	\
    ( (This)->lpVtbl -> get_MyProperty(This,Value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITest_INTERFACE_DEFINED__ */


#ifndef __IExceptionTest_INTERFACE_DEFINED__
#define __IExceptionTest_INTERFACE_DEFINED__

/* interface IExceptionTest */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IExceptionTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A73BCD2D-2095-4D12-8CC0-4E9045FBF461")
    IExceptionTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ThrowException( 
            /* [in] */ boolean Throw) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExceptionTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IExceptionTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IExceptionTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IExceptionTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *ThrowException )( 
            IExceptionTest * This,
            /* [in] */ boolean Throw);
        
        END_INTERFACE
    } IExceptionTestVtbl;

    interface IExceptionTest
    {
        CONST_VTBL struct IExceptionTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExceptionTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IExceptionTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IExceptionTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IExceptionTest_ThrowException(This,Throw)	\
    ( (This)->lpVtbl -> ThrowException(This,Throw) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IExceptionTest_INTERFACE_DEFINED__ */



#ifndef __MultiInterfaceCOMServerLib_LIBRARY_DEFINED__
#define __MultiInterfaceCOMServerLib_LIBRARY_DEFINED__

/* library MultiInterfaceCOMServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MultiInterfaceCOMServerLib;

EXTERN_C const CLSID CLSID_MultiInterfaceCOM;

#ifdef __cplusplus

class DECLSPEC_UUID("888F3A01-C4DB-4C00-A459-153361D3CF81")
MultiInterfaceCOM;
#endif
#endif /* __MultiInterfaceCOMServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


