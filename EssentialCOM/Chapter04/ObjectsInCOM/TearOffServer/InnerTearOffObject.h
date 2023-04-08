//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "TearOffServer_h.h"
//------------------------------------------------------------------------------------------------------
class CInnerTearOffObject : public ITearOffTextInner
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		// !!! POINTER na COM OBJECT.
		ITearOffTextOuter*										MCOMObjectInterface;

	private:
		wchar_t*												MText;

	public:
        virtual HRESULT STDMETHODCALLTYPE SetTextInner(wchar_t* Text);
        virtual HRESULT STDMETHODCALLTYPE GetTextInner(int BufferSize, wchar_t** Text);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		// !!! Do TEAR-OFF INTERFACE musi COM OBJECT zasielat THIS POINTER.
		CInnerTearOffObject(ITearOffTextOuter* COMObjectInterface);
		virtual ~CInnerTearOffObject(void);
};
//------------------------------------------------------------------------------------------------------