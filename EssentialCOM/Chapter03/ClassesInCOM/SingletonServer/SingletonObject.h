//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "SingletonObject_h.h"
//------------------------------------------------------------------------------------------------------
class CSingletonObject : public ISingletonName
{
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
		CSingletonObject(void);
		virtual ~CSingletonObject(void);
};
//------------------------------------------------------------------------------------------------------