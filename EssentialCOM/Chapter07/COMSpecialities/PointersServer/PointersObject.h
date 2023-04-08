//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "PointersServer_h.h"
//------------------------------------------------------------------------------------------------------
class CPointersObject : public IPointersTest
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;

	public:
        virtual HRESULT STDMETHODCALLTYPE Dummy(void);
        virtual HRESULT STDMETHODCALLTYPE NoAttributePointer(int* Pointer);
        virtual HRESULT STDMETHODCALLTYPE RefAttributePointer(int* Pointer);
        virtual HRESULT STDMETHODCALLTYPE UniqueAttributePointer(int* Pointer);
        virtual HRESULT STDMETHODCALLTYPE NoPtrAttributePointer(int* Pointer1, int* Pointer2);
        virtual HRESULT STDMETHODCALLTYPE PtrAttributePointer(int* Pointer1, int* Pointer2);
        virtual HRESULT STDMETHODCALLTYPE MallocSpyTest(int** PointerToMallocData);
        virtual HRESULT STDMETHODCALLTYPE MemoryAllocatedByServer(struct SName* Name);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CPointersObject(void);
		virtual ~CPointersObject(void);
};
//------------------------------------------------------------------------------------------------------