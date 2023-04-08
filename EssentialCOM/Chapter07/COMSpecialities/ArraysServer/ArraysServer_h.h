

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Aug 09 22:52:30 2012
 */
/* Compiler settings for ArraysServer.idl:
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

#ifndef __ArraysServer_h_h__
#define __ArraysServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IArraysTest_FWD_DEFINED__
#define __IArraysTest_FWD_DEFINED__
typedef interface IArraysTest IArraysTest;
#endif 	/* __IArraysTest_FWD_DEFINED__ */


#ifndef __ArraysObject_FWD_DEFINED__
#define __ArraysObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class ArraysObject ArraysObject;
#else
typedef struct ArraysObject ArraysObject;
#endif /* __cplusplus */

#endif 	/* __ArraysObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_ArraysServer_0000_0000 */
/* [local] */ 

/* [uuid] */ struct  DECLSPEC_UUID("AAEF4EB8-6BF1-4D20-AF9F-D9C7CA7A6BC9") SArray
    {
    int ArraySize;
    int *Array;
    } ;


extern RPC_IF_HANDLE __MIDL_itf_ArraysServer_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ArraysServer_0000_0000_v0_0_s_ifspec;

#ifndef __IArraysTest_INTERFACE_DEFINED__
#define __IArraysTest_INTERFACE_DEFINED__

/* interface IArraysTest */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IArraysTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E408DA33-1FB3-4064-BB6E-F5A056AFA9A1")
    IArraysTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Dummy( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE JustPointer( 
            /* [in] */ int *Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FixedArray( 
            /* [in] */ int Array[ 10 ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SizeIs1( 
            /* [in] */ int ArraySize,
            /* [size_is][in] */ int *Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SizeIs2( 
            /* [in] */ int ArraySize,
            /* [size_is][in] */ int Array[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SizeIs3( 
            /* [in] */ int ArraySize,
            /* [size_is][in] */ int Array[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SizeIsExpression( 
            /* [in] */ int ArraySize1,
            /* [in] */ int ArraySize2,
            /* [size_is][in] */ int Array[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SizeIsInStruct( 
            /* [in] */ struct SArray *Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SizeIsConstant( 
            /* [size_is][in] */ int *Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MaxIsConstant( 
            /* [size_is][in] */ int *Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SizeIsForOutputParameter( 
            /* [in] */ int ArraySize,
            /* [size_is][out] */ int *Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SizeIsForOutputStringParameter( 
            /* [in] */ int ArraySize,
            /* [size_is][out] */ wchar_t *Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LengthIs( 
            /* [in] */ int ArrayLength,
            /* [length_is][in] */ int Array[ 20 ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FirstIs( 
            /* [in] */ int StartIndex,
            /* [in] */ int ArrayLength,
            /* [length_is][first_is][in] */ int Array[ 20 ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LastIs( 
            /* [in] */ int StartIndex,
            /* [in] */ int EndIndex,
            /* [last_is][first_is][in] */ int Array[ 20 ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LengthIsAndSizeIs( 
            /* [in] */ int ArraySize,
            /* [in] */ int ArrayLength,
            /* [length_is][size_is][in] */ int *Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LengthIsAndSizeIsForOutputParamerter( 
            /* [in] */ int ArraySize,
            /* [out] */ int *ArrayLength,
            /* [length_is][size_is][out] */ int *Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PointerToPointer( 
            /* [in] */ int **Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ArrayOfPointers( 
            /* [size_is][in] */ int **Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PointerToArray( 
            /* [size_is][size_is][in] */ int **Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ArrayToArray( 
            /* [size_is][size_is][in] */ int **Array) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Matrix( 
            /* [in] */ int Array[ 3 ][ 4 ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE String( 
            /* [string][in] */ wchar_t *String) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OutputString( 
            /* [string][out] */ wchar_t **String) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SafeArrayInt( 
            /* [in] */ SAFEARRAY * *Array) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IArraysTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IArraysTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IArraysTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IArraysTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *Dummy )( 
            IArraysTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *JustPointer )( 
            IArraysTest * This,
            /* [in] */ int *Array);
        
        HRESULT ( STDMETHODCALLTYPE *FixedArray )( 
            IArraysTest * This,
            /* [in] */ int Array[ 10 ]);
        
        HRESULT ( STDMETHODCALLTYPE *SizeIs1 )( 
            IArraysTest * This,
            /* [in] */ int ArraySize,
            /* [size_is][in] */ int *Array);
        
        HRESULT ( STDMETHODCALLTYPE *SizeIs2 )( 
            IArraysTest * This,
            /* [in] */ int ArraySize,
            /* [size_is][in] */ int Array[  ]);
        
        HRESULT ( STDMETHODCALLTYPE *SizeIs3 )( 
            IArraysTest * This,
            /* [in] */ int ArraySize,
            /* [size_is][in] */ int Array[  ]);
        
        HRESULT ( STDMETHODCALLTYPE *SizeIsExpression )( 
            IArraysTest * This,
            /* [in] */ int ArraySize1,
            /* [in] */ int ArraySize2,
            /* [size_is][in] */ int Array[  ]);
        
        HRESULT ( STDMETHODCALLTYPE *SizeIsInStruct )( 
            IArraysTest * This,
            /* [in] */ struct SArray *Array);
        
        HRESULT ( STDMETHODCALLTYPE *SizeIsConstant )( 
            IArraysTest * This,
            /* [size_is][in] */ int *Array);
        
        HRESULT ( STDMETHODCALLTYPE *MaxIsConstant )( 
            IArraysTest * This,
            /* [size_is][in] */ int *Array);
        
        HRESULT ( STDMETHODCALLTYPE *SizeIsForOutputParameter )( 
            IArraysTest * This,
            /* [in] */ int ArraySize,
            /* [size_is][out] */ int *Array);
        
        HRESULT ( STDMETHODCALLTYPE *SizeIsForOutputStringParameter )( 
            IArraysTest * This,
            /* [in] */ int ArraySize,
            /* [size_is][out] */ wchar_t *Array);
        
        HRESULT ( STDMETHODCALLTYPE *LengthIs )( 
            IArraysTest * This,
            /* [in] */ int ArrayLength,
            /* [length_is][in] */ int Array[ 20 ]);
        
        HRESULT ( STDMETHODCALLTYPE *FirstIs )( 
            IArraysTest * This,
            /* [in] */ int StartIndex,
            /* [in] */ int ArrayLength,
            /* [length_is][first_is][in] */ int Array[ 20 ]);
        
        HRESULT ( STDMETHODCALLTYPE *LastIs )( 
            IArraysTest * This,
            /* [in] */ int StartIndex,
            /* [in] */ int EndIndex,
            /* [last_is][first_is][in] */ int Array[ 20 ]);
        
        HRESULT ( STDMETHODCALLTYPE *LengthIsAndSizeIs )( 
            IArraysTest * This,
            /* [in] */ int ArraySize,
            /* [in] */ int ArrayLength,
            /* [length_is][size_is][in] */ int *Array);
        
        HRESULT ( STDMETHODCALLTYPE *LengthIsAndSizeIsForOutputParamerter )( 
            IArraysTest * This,
            /* [in] */ int ArraySize,
            /* [out] */ int *ArrayLength,
            /* [length_is][size_is][out] */ int *Array);
        
        HRESULT ( STDMETHODCALLTYPE *PointerToPointer )( 
            IArraysTest * This,
            /* [in] */ int **Array);
        
        HRESULT ( STDMETHODCALLTYPE *ArrayOfPointers )( 
            IArraysTest * This,
            /* [size_is][in] */ int **Array);
        
        HRESULT ( STDMETHODCALLTYPE *PointerToArray )( 
            IArraysTest * This,
            /* [size_is][size_is][in] */ int **Array);
        
        HRESULT ( STDMETHODCALLTYPE *ArrayToArray )( 
            IArraysTest * This,
            /* [size_is][size_is][in] */ int **Array);
        
        HRESULT ( STDMETHODCALLTYPE *Matrix )( 
            IArraysTest * This,
            /* [in] */ int Array[ 3 ][ 4 ]);
        
        HRESULT ( STDMETHODCALLTYPE *String )( 
            IArraysTest * This,
            /* [string][in] */ wchar_t *String);
        
        HRESULT ( STDMETHODCALLTYPE *OutputString )( 
            IArraysTest * This,
            /* [string][out] */ wchar_t **String);
        
        HRESULT ( STDMETHODCALLTYPE *SafeArrayInt )( 
            IArraysTest * This,
            /* [in] */ SAFEARRAY * *Array);
        
        END_INTERFACE
    } IArraysTestVtbl;

    interface IArraysTest
    {
        CONST_VTBL struct IArraysTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IArraysTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IArraysTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IArraysTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IArraysTest_Dummy(This)	\
    ( (This)->lpVtbl -> Dummy(This) ) 

#define IArraysTest_JustPointer(This,Array)	\
    ( (This)->lpVtbl -> JustPointer(This,Array) ) 

#define IArraysTest_FixedArray(This,Array)	\
    ( (This)->lpVtbl -> FixedArray(This,Array) ) 

#define IArraysTest_SizeIs1(This,ArraySize,Array)	\
    ( (This)->lpVtbl -> SizeIs1(This,ArraySize,Array) ) 

#define IArraysTest_SizeIs2(This,ArraySize,Array)	\
    ( (This)->lpVtbl -> SizeIs2(This,ArraySize,Array) ) 

#define IArraysTest_SizeIs3(This,ArraySize,Array)	\
    ( (This)->lpVtbl -> SizeIs3(This,ArraySize,Array) ) 

#define IArraysTest_SizeIsExpression(This,ArraySize1,ArraySize2,Array)	\
    ( (This)->lpVtbl -> SizeIsExpression(This,ArraySize1,ArraySize2,Array) ) 

#define IArraysTest_SizeIsInStruct(This,Array)	\
    ( (This)->lpVtbl -> SizeIsInStruct(This,Array) ) 

#define IArraysTest_SizeIsConstant(This,Array)	\
    ( (This)->lpVtbl -> SizeIsConstant(This,Array) ) 

#define IArraysTest_MaxIsConstant(This,Array)	\
    ( (This)->lpVtbl -> MaxIsConstant(This,Array) ) 

#define IArraysTest_SizeIsForOutputParameter(This,ArraySize,Array)	\
    ( (This)->lpVtbl -> SizeIsForOutputParameter(This,ArraySize,Array) ) 

#define IArraysTest_SizeIsForOutputStringParameter(This,ArraySize,Array)	\
    ( (This)->lpVtbl -> SizeIsForOutputStringParameter(This,ArraySize,Array) ) 

#define IArraysTest_LengthIs(This,ArrayLength,Array)	\
    ( (This)->lpVtbl -> LengthIs(This,ArrayLength,Array) ) 

#define IArraysTest_FirstIs(This,StartIndex,ArrayLength,Array)	\
    ( (This)->lpVtbl -> FirstIs(This,StartIndex,ArrayLength,Array) ) 

#define IArraysTest_LastIs(This,StartIndex,EndIndex,Array)	\
    ( (This)->lpVtbl -> LastIs(This,StartIndex,EndIndex,Array) ) 

#define IArraysTest_LengthIsAndSizeIs(This,ArraySize,ArrayLength,Array)	\
    ( (This)->lpVtbl -> LengthIsAndSizeIs(This,ArraySize,ArrayLength,Array) ) 

#define IArraysTest_LengthIsAndSizeIsForOutputParamerter(This,ArraySize,ArrayLength,Array)	\
    ( (This)->lpVtbl -> LengthIsAndSizeIsForOutputParamerter(This,ArraySize,ArrayLength,Array) ) 

#define IArraysTest_PointerToPointer(This,Array)	\
    ( (This)->lpVtbl -> PointerToPointer(This,Array) ) 

#define IArraysTest_ArrayOfPointers(This,Array)	\
    ( (This)->lpVtbl -> ArrayOfPointers(This,Array) ) 

#define IArraysTest_PointerToArray(This,Array)	\
    ( (This)->lpVtbl -> PointerToArray(This,Array) ) 

#define IArraysTest_ArrayToArray(This,Array)	\
    ( (This)->lpVtbl -> ArrayToArray(This,Array) ) 

#define IArraysTest_Matrix(This,Array)	\
    ( (This)->lpVtbl -> Matrix(This,Array) ) 

#define IArraysTest_String(This,String)	\
    ( (This)->lpVtbl -> String(This,String) ) 

#define IArraysTest_OutputString(This,String)	\
    ( (This)->lpVtbl -> OutputString(This,String) ) 

#define IArraysTest_SafeArrayInt(This,Array)	\
    ( (This)->lpVtbl -> SafeArrayInt(This,Array) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IArraysTest_INTERFACE_DEFINED__ */



#ifndef __ArraysServerLib_LIBRARY_DEFINED__
#define __ArraysServerLib_LIBRARY_DEFINED__

/* library ArraysServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ArraysServerLib;

EXTERN_C const CLSID CLSID_ArraysObject;

#ifdef __cplusplus

class DECLSPEC_UUID("E1D422BC-1A2A-4951-B13E-C38B9D055C64")
ArraysObject;
#endif
#endif /* __ArraysServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


