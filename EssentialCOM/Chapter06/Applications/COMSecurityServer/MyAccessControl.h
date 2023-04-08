//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include <IAccess.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "COMSecurityServer_h.h"
//------------------------------------------------------------------------------------------------------
class CMyAccessControl : public IAccessControl
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;

	public:
        virtual HRESULT STDMETHODCALLTYPE GrantAccessRights(__RPC__in PACTRL_ACCESSW AccessList);
        virtual HRESULT STDMETHODCALLTYPE SetAccessRights(__RPC__in PACTRL_ACCESSW AccessList);
        virtual HRESULT STDMETHODCALLTYPE SetOwner(__RPC__in PTRUSTEEW Owner, __RPC__in PTRUSTEEW Group);
        virtual HRESULT STDMETHODCALLTYPE RevokeAccessRights(__RPC__in LPWSTR Property, ULONG CTrustees, __RPC__in_ecount_full(CTrustees) TRUSTEEW Trustees[]);
        virtual HRESULT STDMETHODCALLTYPE GetAllAccessRights(__RPC__in LPWSTR Property, __RPC__deref_out_opt PACTRL_ACCESSW_ALLOCATE_ALL_NODES* AccessList, __RPC__deref_out_opt PTRUSTEEW* Owner, __RPC__deref_out_opt PTRUSTEEW* Group);
        // !!! JEDINA METHOD, ktora MUSI byt implementovana.
        virtual HRESULT STDMETHODCALLTYPE IsAccessAllowed(__RPC__in PTRUSTEEW Trustee, __RPC__in LPWSTR Property, ACCESS_RIGHTS AccessRights, __RPC__out BOOL* AccessAllowed);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CMyAccessControl(void);
		virtual ~CMyAccessControl(void);
};
//------------------------------------------------------------------------------------------------------