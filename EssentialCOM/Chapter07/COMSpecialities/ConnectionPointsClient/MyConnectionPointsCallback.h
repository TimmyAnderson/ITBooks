//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "..\ConnectionPointsServer\ConnectionPointsServer_h.h"
//------------------------------------------------------------------------------------------------------
class CMyConnectionPointsCallback : public IMyConnectionPointsCallback
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		wchar_t*												MCallbackName;

	public:
        virtual HRESULT STDMETHODCALLTYPE SendMessageToClient(BSTR Message);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CMyConnectionPointsCallback(wchar_t* CallbackName);
		virtual ~CMyConnectionPointsCallback(void);
};
//------------------------------------------------------------------------------------------------------