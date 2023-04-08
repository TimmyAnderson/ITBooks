//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include <mscoree.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "BagFileRecords.h"
//------------------------------------------------------------------------------------------------------
// !!! Nacitava CUSTOM ASSEMBLIES do PROCESSU.
// !!!!! ASSEMBLIES mozu byt NA ROZDIEL od PROBING MECHANIZMU CLR nacitavane NIELEN z FILE SYSTEM, ale napriklad aj z .ZIP ci .CAB FILES, alebo DB TABLES. Je to CISTOM IMPLEMENTACNA ZALEZITOST ODKIAL budu ASSEMBLIES NACITANE.
class CBagHostAssemblyStore : public IHostAssemblyStore
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		CBagFileRecords*										MBagFileRecords;

	public:
        virtual HRESULT STDMETHODCALLTYPE ProvideAssembly(AssemblyBindInfo* BindInfo, UINT64* AssemblyID, UINT64* Context, IStream** StmAssemblyImage, IStream** StmPDB);
        virtual HRESULT STDMETHODCALLTYPE ProvideModule(ModuleBindInfo* BindInfo, DWORD* ModuleID, IStream** StmModuleImage, IStream** StmPDB);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CBagHostAssemblyStore(CBagFileRecords* BagFileRecords);
		~CBagHostAssemblyStore(void);
};
//------------------------------------------------------------------------------------------------------