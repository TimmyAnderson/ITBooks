//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include <list>
#include "Helpers\CriticalSectionWrapper.h"
#include "MyFileMonikerObject_h.h"
//------------------------------------------------------------------------------------------------------
// !!!!! Aby bol FILE MONIKER PODPOROVANY, MUSI COM OBJECT implementovat IPersistFile.
class CMyFileMonikerObject : public IMyFileMonikerName, public IPersistFile
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		bstr_t													MFirstName;
		bstr_t													MLastName;
		int														MAge;
		std::list<DWORD>										MRegistredObjects;

	public:
        virtual HRESULT STDMETHODCALLTYPE SetFirstName(wchar_t* FirstName);
        virtual HRESULT STDMETHODCALLTYPE SetLastName(wchar_t* LastName);
        virtual HRESULT STDMETHODCALLTYPE SetAge(int Age);
        virtual HRESULT STDMETHODCALLTYPE GetFirstName(int BufferSize, wchar_t** FirstName);
        virtual HRESULT STDMETHODCALLTYPE GetLastName(int BufferSize, wchar_t** LastName);
        virtual HRESULT STDMETHODCALLTYPE GetAge(int* Age);

	public:
        virtual HRESULT STDMETHODCALLTYPE IsDirty(void);
        virtual HRESULT STDMETHODCALLTYPE Load(__RPC__in LPCOLESTR FileName, DWORD Mode);
        virtual HRESULT STDMETHODCALLTYPE Save(__RPC__in_opt LPCOLESTR FileName, BOOL Remember);
        virtual HRESULT STDMETHODCALLTYPE SaveCompleted(__RPC__in_opt LPCOLESTR FileName);
        virtual HRESULT STDMETHODCALLTYPE GetCurFile(__RPC__deref_out_opt LPOLESTR* FileName);
        virtual HRESULT STDMETHODCALLTYPE GetClassID(__RPC__out CLSID* ClassID);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CMyFileMonikerObject(void);
		virtual ~CMyFileMonikerObject(void);
};
//------------------------------------------------------------------------------------------------------