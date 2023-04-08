//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "ApartmentThreadingModelServer_h.h"
//------------------------------------------------------------------------------------------------------
class CApartmentThreadingModelObject : public IApartmentThreadingModelTest
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		long													MValue;

	public:
        virtual HRESULT STDMETHODCALLTYPE IncrementValue(void);
        virtual HRESULT STDMETHODCALLTYPE GetValue(long* Value);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CApartmentThreadingModelObject(void);
		virtual ~CApartmentThreadingModelObject(void);
};
//------------------------------------------------------------------------------------------------------