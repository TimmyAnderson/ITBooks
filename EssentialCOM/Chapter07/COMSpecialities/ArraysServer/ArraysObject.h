//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "ArraysServer_h.h"
//------------------------------------------------------------------------------------------------------
class CArraysObject : public IArraysTest
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;

	public:
        virtual HRESULT STDMETHODCALLTYPE Dummy(void);
        virtual HRESULT STDMETHODCALLTYPE JustPointer(int* Array);
        virtual HRESULT STDMETHODCALLTYPE FixedArray(int Array[10]);
        virtual HRESULT STDMETHODCALLTYPE SizeIs1(int ArraySize, int* Array);
        virtual HRESULT STDMETHODCALLTYPE SizeIs2(int ArraySize, int Array[]);
        virtual HRESULT STDMETHODCALLTYPE SizeIs3(int ArraySize, int Array[]);
        virtual HRESULT STDMETHODCALLTYPE SizeIsExpression(int ArraySize1, int ArraySize2, int Array[]);
        virtual HRESULT STDMETHODCALLTYPE SizeIsInStruct(SArray* Array);
        virtual HRESULT STDMETHODCALLTYPE SizeIsConstant(int* Array);
        virtual HRESULT STDMETHODCALLTYPE MaxIsConstant(int* Array);
        virtual HRESULT STDMETHODCALLTYPE SizeIsForOutputParameter(int ArraySize, int* Array);
        virtual HRESULT STDMETHODCALLTYPE SizeIsForOutputStringParameter(int ArraySize, wchar_t* Array);
        virtual HRESULT STDMETHODCALLTYPE LengthIs(int ArrayLength, int Array[20]);
        virtual HRESULT STDMETHODCALLTYPE FirstIs(int StartIndex, int ArrayLength, int Array[20]);
        virtual HRESULT STDMETHODCALLTYPE LastIs(int StartIndex, int EndIndex, int Array[20]);
        virtual HRESULT STDMETHODCALLTYPE LengthIsAndSizeIs(int ArraySize, int ArrayLength, int* Array);
        virtual HRESULT STDMETHODCALLTYPE LengthIsAndSizeIsForOutputParamerter(int ArraySize, int* ArrayLength, int* Array);
        virtual HRESULT STDMETHODCALLTYPE PointerToPointer(int** Array);
        virtual HRESULT STDMETHODCALLTYPE ArrayOfPointers(int** Array);
        virtual HRESULT STDMETHODCALLTYPE PointerToArray(int** Array);
        virtual HRESULT STDMETHODCALLTYPE ArrayToArray(int** Array);
        virtual HRESULT STDMETHODCALLTYPE Matrix(int Array[3][4]);
        virtual HRESULT STDMETHODCALLTYPE String(wchar_t* String);
        virtual HRESULT STDMETHODCALLTYPE OutputString(wchar_t** String);
        virtual HRESULT STDMETHODCALLTYPE SafeArrayInt(SAFEARRAY** Array);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CArraysObject(void);
		virtual ~CArraysObject(void);
};
//------------------------------------------------------------------------------------------------------