//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "CallbacksInCOMServer_h.h"
//------------------------------------------------------------------------------------------------------
class CMyServerObject : public IMyServer
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		CSmartCOMPointer<IMyServerCallback>						MCallback;

	public:
        virtual HRESULT STDMETHODCALLTYPE RegisterCallback(IMyServerCallback* Callback);
        virtual HRESULT STDMETHODCALLTYPE UnRegisterCallback(void);
        virtual HRESULT STDMETHODCALLTYPE SendMessageToServer(BSTR Message);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CMyServerObject(void);
		virtual ~CMyServerObject(void);
};
//------------------------------------------------------------------------------------------------------