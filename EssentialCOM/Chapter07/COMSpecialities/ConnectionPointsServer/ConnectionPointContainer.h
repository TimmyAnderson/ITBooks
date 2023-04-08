//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "ConnectionPointsServer_h.h"
#include "ConnectionPointsManager.h"
//------------------------------------------------------------------------------------------------------
// !!!!! CLASS predstavuje implementaciu IConnectionPointContainer COM INTERFACE.
class CConnectionPointContainer : public IMyConnectionPoints, public IConnectionPointContainer
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		CConnectionPointsManager								MConnectionPointsManager;

	public:
        virtual HRESULT STDMETHODCALLTYPE SendMessageToServer(BSTR Message);

	public:
        virtual HRESULT STDMETHODCALLTYPE EnumConnectionPoints(__RPC__deref_out_opt IEnumConnectionPoints** Enum);
        virtual HRESULT STDMETHODCALLTYPE FindConnectionPoint(__RPC__in REFIID RIID, __RPC__deref_out_opt IConnectionPoint** CP);
        
	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CConnectionPointContainer(void);
		virtual ~CConnectionPointContainer(void);
};
//------------------------------------------------------------------------------------------------------