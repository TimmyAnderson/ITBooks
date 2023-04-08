//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "MethodsNameClashServer_h.h"
#include "GetText1.h"
#include "GetText2.h"
//------------------------------------------------------------------------------------------------------
// !!! IMPLEMENTUJE CLASSES, ktore implementuju COM INTERFACES.
class CMethodsNameClashObject : public CGetText1, public CGetText2
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;

	public:
		// !!! Implementuje ABSTRACT METHOD z CGetText1 cim RIESI NAME CLASH.
        virtual HRESULT STDMETHODCALLTYPE GetText1(int BufferSize, wchar_t** Text);

	public:
		// !!! Implementuje ABSTRACT METHOD z CGetText2 cim RIESI NAME CLASH.
        virtual HRESULT STDMETHODCALLTYPE GetText2(int BufferSize, wchar_t** Text);

	public:
        HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        ULONG STDMETHODCALLTYPE AddRef(void);
        ULONG STDMETHODCALLTYPE Release(void);

	public:
		CMethodsNameClashObject(void);
		virtual ~CMethodsNameClashObject(void);
};
//------------------------------------------------------------------------------------------------------