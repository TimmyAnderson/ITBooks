//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "CompositionServer_h.h"
#include "GetText1.h"
#include "GetText2.h"
//------------------------------------------------------------------------------------------------------
// !!! NEIMPLEMENTUJE ZIADEN INTERFACE.
class CCompositionObject
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;

	private:
		// !!! Obsahuje cele VALUES a NIE iba POINTERS.
		CGetText1												MGetText1;
		CGetText2												MGetText2;

	public:
		// !!! Implementuje METHODS IUnknown, aj ked z IUnknown CLASS NEDEDI.
        HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        ULONG STDMETHODCALLTYPE AddRef(void);
        ULONG STDMETHODCALLTYPE Release(void);

	public:
		CCompositionObject(void);
		virtual ~CCompositionObject(void);
};
//------------------------------------------------------------------------------------------------------