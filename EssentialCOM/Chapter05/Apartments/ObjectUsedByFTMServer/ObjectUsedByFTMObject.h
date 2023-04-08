//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "ObjectUsedByFTMServer_h.h"
//------------------------------------------------------------------------------------------------------
// !!!!! COM OBJECT je pouzivany z FTM COM OBJECT. Je to STA COM OBJECT, aby sa demonstrovalo riziko pouzivania STA COM OBJECTS z FTM COM OBJECTS.
class CObjectUsedByFTMObject : public IObjectUsedByFTMTest
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
		CObjectUsedByFTMObject(void);
		virtual ~CObjectUsedByFTMObject(void);
};
//------------------------------------------------------------------------------------------------------