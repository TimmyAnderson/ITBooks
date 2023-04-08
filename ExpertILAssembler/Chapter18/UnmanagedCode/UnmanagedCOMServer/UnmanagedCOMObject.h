//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "UnmanagedCOMServer_h.h"
//------------------------------------------------------------------------------------------------------
class CUnmanagedCOMObject : public IUnmanagedCOMServer
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		CSmartCOMPointer<IUnmanagedCOMServerCallback>			MCallback;
		_bstr_t													MName;
		int														MAge;

	public:
		virtual HRESULT STDMETHODCALLTYPE RegisterCallback(IUnmanagedCOMServerCallback* Callback);
		virtual HRESULT STDMETHODCALLTYPE UnRegisterCallback(void);
		virtual HRESULT STDMETHODCALLTYPE SendMessageToServer(BSTR Message);
		virtual HRESULT STDMETHODCALLTYPE PrintMessage(BSTR Message);
		virtual HRESULT STDMETHODCALLTYPE LoadName(BSTR* Name, int* Age);
		virtual HRESULT STDMETHODCALLTYPE SaveName(BSTR Name, int Age);
		virtual HRESULT STDMETHODCALLTYPE ArrayTest1(int ArraySize, int* Array);
		virtual HRESULT STDMETHODCALLTYPE ArrayTest2(SAFEARRAY** Array);

	public:
		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
		virtual ULONG STDMETHODCALLTYPE AddRef(void);
		virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CUnmanagedCOMObject(void);
		virtual ~CUnmanagedCOMObject(void);
};
//------------------------------------------------------------------------------------------------------