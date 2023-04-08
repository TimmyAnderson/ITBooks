//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "ConnectionPointsServer_h.h"
#include "ConnectionPointsManager.h"
//------------------------------------------------------------------------------------------------------
class CConnectionPointContainer;
//------------------------------------------------------------------------------------------------------
// !!!!! CLASS predstavuje implementaciu IConnectionPoint COM INTERFACE.
class CConnectionPoint : public IConnectionPoint
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		CConnectionPointsManager*								MConnectionPointsManager;
		CConnectionPointContainer*								MConnectionPointContainer;

	public:
        virtual HRESULT STDMETHODCALLTYPE GetConnectionInterface(__RPC__out IID* IID);
        virtual HRESULT STDMETHODCALLTYPE GetConnectionPointContainer(__RPC__deref_out_opt IConnectionPointContainer** CPC);
        virtual HRESULT STDMETHODCALLTYPE Advise(__RPC__in_opt IUnknown* UnkSink, __RPC__out DWORD* Cookie);
        virtual HRESULT STDMETHODCALLTYPE Unadvise(DWORD Cookie);
        virtual HRESULT STDMETHODCALLTYPE EnumConnections(__RPC__deref_out_opt IEnumConnections** Enum);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CConnectionPoint(CConnectionPointsManager* ConnectionPointsManager, CConnectionPointContainer* ConnectionPointContainer);
		virtual ~CConnectionPoint(void);
};
//------------------------------------------------------------------------------------------------------