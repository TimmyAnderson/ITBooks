//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "CompositionServer_h.h"
//------------------------------------------------------------------------------------------------------
class CCompositionObject;
//------------------------------------------------------------------------------------------------------
class CGetText2 : public IGetText2
{
	private:
		CCriticalSectionWrapper									MCS;

	private:
		CCompositionObject*										MCompositionObject;

	public:
        virtual HRESULT STDMETHODCALLTYPE GetText(int BufferSize, wchar_t** Text);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		// !!! Do COMPOSITION CLASS zasielam POINTER na COM OBJECT.
		void Initialize(CCompositionObject* CompositionObject);

	public:
		CGetText2(void);
		virtual ~CGetText2(void);
};
//------------------------------------------------------------------------------------------------------