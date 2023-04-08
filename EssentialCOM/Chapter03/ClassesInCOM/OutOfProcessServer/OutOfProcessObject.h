//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "OutOfProcessObject_h.h"
//------------------------------------------------------------------------------------------------------
class COutOfProcessObject : public IOutOfProcessName
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		HANDLE													MProcessExitEvent;
		bstr_t													MFirstName;
		bstr_t													MLastName;
		int														MAge;

	public:
        virtual HRESULT STDMETHODCALLTYPE SetFirstName(BSTR FirstName);
        virtual HRESULT STDMETHODCALLTYPE SetLastName(BSTR LastName);
        virtual HRESULT STDMETHODCALLTYPE SetAge(int Age);
        virtual HRESULT STDMETHODCALLTYPE GetFirstName(BSTR* FirstName);
        virtual HRESULT STDMETHODCALLTYPE GetLastName(BSTR* LastName);
        virtual HRESULT STDMETHODCALLTYPE GetAge(int* Age);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		COutOfProcessObject(HANDLE ProcessExitEvent);
		virtual ~COutOfProcessObject(void);
};
//------------------------------------------------------------------------------------------------------