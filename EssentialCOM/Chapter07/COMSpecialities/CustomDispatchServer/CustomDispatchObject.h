//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "CustomDispatchServer_h.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
class CCustomDispatchObject : public ICustomDispatchTest
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		CSmartCOMPointer<ITypeInfo>								MTypeInfo;
		bstr_t													MValue;

	public:
        virtual HRESULT STDMETHODCALLTYPE SetValue(BSTR Value);
        virtual HRESULT STDMETHODCALLTYPE GetValue(BSTR* Value);

    public:
        virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(__RPC__out UINT* TypeInfo);
        virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT TInfo, LCID LCID, __RPC__deref_out_opt ITypeInfo** TypeInfo);
        virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(__RPC__in REFIID RIID, __RPC__in_ecount_full(CountNames) LPOLESTR* Names, __RPC__in_range(0,16384) UINT CountNames, LCID LCID, __RPC__out_ecount_full(CountNames) DISPID* DispID);
        virtual HRESULT STDMETHODCALLTYPE Invoke(DISPID DispIDMember, REFIID RIID, LCID LCID, WORD Flags, DISPPARAMS* DispParams, VARIANT* VarResult, EXCEPINFO* ExcepInfo, UINT* ArgErr);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CCustomDispatchObject(void);
		virtual ~CCustomDispatchObject(void);
};
//------------------------------------------------------------------------------------------------------