//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "OutOfProcessWithMarshallingServer_h.h"
//------------------------------------------------------------------------------------------------------
class COutOfProcessWithMarshallingObject : public IName
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		HANDLE													MProcessExitEvent;
		wchar_t*												MFirstName;
		wchar_t*												MLastName;
		int														MAge;

	public:
        virtual HRESULT STDMETHODCALLTYPE SetFirstName(wchar_t* FirstName);
        virtual HRESULT STDMETHODCALLTYPE SetLastName(wchar_t* LastName);
        virtual HRESULT STDMETHODCALLTYPE SetAge(int Age);
        virtual HRESULT STDMETHODCALLTYPE GetFirstName(int BufferSize, wchar_t* FirstName);
        virtual HRESULT STDMETHODCALLTYPE GetLastName(int BufferSize, wchar_t* LastName);
        virtual HRESULT STDMETHODCALLTYPE GetAge(int* Age);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		COutOfProcessWithMarshallingObject(HANDLE ProcessExitEvent);
		virtual ~COutOfProcessWithMarshallingObject(void);
};
//------------------------------------------------------------------------------------------------------