//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "TearOffServer_h.h"
#include "InnerTearOffObject.h"
//------------------------------------------------------------------------------------------------------
// !!! Implementuje sa iba NON TEAR-OFF INTERFACE.
class CTearOffObject : public ITearOffTextOuter
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		// !!! POINTER na CLASS implementujucu TEAR-OFF INTERFACE.
		ITearOffTextInner*										MTearOffInterface;

	private:
		wchar_t*												MText;

	public:
        virtual HRESULT STDMETHODCALLTYPE SetTextOuter(wchar_t* Text);
        virtual HRESULT STDMETHODCALLTYPE GetTextOuter(int BufferSize, wchar_t** Text);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CTearOffObject(void);
		virtual ~CTearOffObject(void);
};
//------------------------------------------------------------------------------------------------------