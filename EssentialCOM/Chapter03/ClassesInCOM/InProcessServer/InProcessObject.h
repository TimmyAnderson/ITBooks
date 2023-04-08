//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "InProcessObject_h.h"
//------------------------------------------------------------------------------------------------------
class CInProcessObject : public IInProcessName
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		wchar_t*												MFirstName;
		wchar_t*												MLastName;
		int														MAge;

	public:
        virtual HRESULT STDMETHODCALLTYPE SetFirstName(wchar_t* FirstName);
        virtual HRESULT STDMETHODCALLTYPE SetLastName(wchar_t* LastName);
        virtual HRESULT STDMETHODCALLTYPE SetAge(int Age);
        virtual HRESULT STDMETHODCALLTYPE GetFirstName(int BufferSize, wchar_t** FirstName);
        virtual HRESULT STDMETHODCALLTYPE GetLastName(int BufferSize, wchar_t** LastName);
        virtual HRESULT STDMETHODCALLTYPE GetAge(int* Age);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CInProcessObject(void);
		virtual ~CInProcessObject(void);
};
//------------------------------------------------------------------------------------------------------