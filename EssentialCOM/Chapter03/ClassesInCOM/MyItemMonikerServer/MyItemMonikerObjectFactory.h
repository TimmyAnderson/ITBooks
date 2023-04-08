//------------------------------------------------------------------------------------------------------
#include <Unknwn.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
//------------------------------------------------------------------------------------------------------
// !!!!! Kedze implementujem MONIKER, tak NEMUSIM IMPLEMENTOVAT IClassFactory. Za vytvaranie COM OBJECTS je zodpovedny INTERFACE IOleItemContainer.
class CMyItemMonikerObjectFactory : /*public IClassFactory,*/ public IOleItemContainer
{
//------------------------------------------------------------------------------------------------------
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;

	public:
        virtual HRESULT STDMETHODCALLTYPE ParseDisplayName(__RPC__in_opt IBindCtx* PBC, __RPC__in LPOLESTR DisplayName, __RPC__out ULONG* Eaten, __RPC__deref_out_opt IMoniker** Moniker);

	public:
        virtual HRESULT STDMETHODCALLTYPE GetObject(__RPC__in LPOLESTR Item, DWORD SpeedNeeded, __RPC__in_opt IBindCtx* PBC, __RPC__in REFIID RIID, __RPC__deref_out_opt void** PointerToObject);
        virtual HRESULT STDMETHODCALLTYPE GetObjectStorage(__RPC__in LPOLESTR Item, __RPC__in_opt IBindCtx* PBC, __RPC__in REFIID RIID, __RPC__deref_out_opt void** PointerToStorage);
        virtual HRESULT STDMETHODCALLTYPE IsRunning(__RPC__in LPOLESTR Item);
        virtual HRESULT STDMETHODCALLTYPE EnumObjects(DWORD Flags, __RPC__deref_out_opt IEnumUnknown** Enum);
        virtual HRESULT STDMETHODCALLTYPE LockContainer(BOOL Lock);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CMyItemMonikerObjectFactory(void);
		virtual ~CMyItemMonikerObjectFactory(void);
//------------------------------------------------------------------------------------------------------
};
//------------------------------------------------------------------------------------------------------