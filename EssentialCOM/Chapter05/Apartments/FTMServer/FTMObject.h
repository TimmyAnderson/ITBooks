//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "FTMServer_h.h"
#include "..\ObjectUsedByFTMServer\ObjectUsedByFTMServer_h.h"
//------------------------------------------------------------------------------------------------------
// !!!!! COM OBJECT pouziva FTM. THREADING MODEL ma preto FREE. Interne vyuziva STA COM OBJECT.
class CFTMObject : public IFTMTest
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		long													MValue;
		// FREE THREADED MARSHALER.
		CSmartCOMPointer<IUnknown>								MFTM;
		// GLOBAL INTERFACE TABLE.
		CSmartCOMPointer<IGlobalInterfaceTable>					MGIT;
		// !!! COOKIE na STA COM OBJECT, ktory demonstruje RIESENIE problemov FTM pri pouzivani STA COM OBJECTS z COM OBJECTS implementujucich FTM.
		DWORD													MSTAObjectCookie;

	public:
        virtual HRESULT STDMETHODCALLTYPE IncrementValue(void);
        virtual HRESULT STDMETHODCALLTYPE GetValue(long* Value);
        virtual HRESULT STDMETHODCALLTYPE IncrementValueToRemoteObject(void);
        virtual HRESULT STDMETHODCALLTYPE GetValueFromRemoteObject(long* Value);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CFTMObject(void);
		virtual ~CFTMObject(void);
};
//------------------------------------------------------------------------------------------------------