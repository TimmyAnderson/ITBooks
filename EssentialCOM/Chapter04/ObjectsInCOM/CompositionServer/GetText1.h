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
class CGetText1 : public IGetText1
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
		// !!! Do COMPOSITION CLASS zasielam POINTER na COM OBJECT.
		CGetText1(void);
		virtual ~CGetText1(void);
};
//------------------------------------------------------------------------------------------------------