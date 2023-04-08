//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <vector>
#include <CorError.h>
#include "BagHostAssemblyStore.h"
#include "Helpers\Lock.h"
#include "Helpers\Helpers.h"
//------------------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------------------
CBagHostAssemblyStore::CBagHostAssemblyStore(CBagFileRecords* BagFileRecords)
	: MReferenceCounter(0), MBagFileRecords(BagFileRecords)
{
}
//------------------------------------------------------------------------------------------------------
CBagHostAssemblyStore::~CBagHostAssemblyStore(void)
{
	wprintf_s(L"!!!!!!!!!! HOST ASSEMBLY STORE COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// !!! Nacitava CUSTOM ASSEMBLIES do PROCESSU.
// !!!!! ASSEMBLIES mozu byt NA ROZDIEL od PROBING MECHANIZMU CLR nacitavane NIELEN z FILE SYSTEM, ale napriklad aj z .ZIP ci .CAB FILES, alebo DB TABLES. Je to CISTOM IMPLEMENTACNA ZALEZITOST ODKIAL budu ASSEMBLIES NACITANE.
HRESULT STDMETHODCALLTYPE CBagHostAssemblyStore::ProvideAssembly(AssemblyBindInfo* BindInfo, UINT64* AssemblyID, UINT64* Context, IStream** StmAssemblyImage, IStream** StmPDB)
{
	// !!!!! MUSI BYT IDENTICKY s HODNOTOU v BagAppDomainManager.
	int															ASSEMBLY_FROM_BAG=999;
	CLock														Lock(MCS);

	HRESULT														HR;

	// !!! VALUE Context je LUBOVOLNA VALUE, ktora je prenesena do MANAGED CODE a pristupna cez PROPERTY Assembly.HostContext.
	*Context=0;
	*StmAssemblyImage=NULL;
	*StmPDB=NULL;

	vector<CBagFileRecord*>										BagFileRecordList=MBagFileRecords->GetBagFileRecords();
	UINT64														AssemblyIDCounter=0;

	// !!! Prejdem cely .BAG FILE a hladam zaznam, ktoreho ASSEMBLY IDENTITY NAME je ZHODNY s ASSEMBLY IDENTITY NAME ASSEMBLY, ktora sa ma nacitat.
	for (vector<CBagFileRecord*>::iterator Iterator=BagFileRecordList.begin();Iterator!=BagFileRecordList.end();Iterator++)
	{
		wstring													AssemblyIdentity=(*Iterator)->GetAssemblyIdentity();
		wstring													AssemblyToLoadIdentity=wstring(BindInfo->lpReferencedIdentity);

		// !!! Beriem do uvahy iba ASSEMBLY FRIENDLY NAME a ostatne casti FULLY-QUALIFIED NAME IGNORUJEM.
		size_t													Position1=AssemblyIdentity.find(L",");
		size_t													Position2=AssemblyIdentity.find(L",");

		if (Position1==wstring::npos || Position2==wstring::npos)
		{
			continue;
		}

		wstring													FriendlyNameAssemblyIdentity=AssemblyIdentity.substr(0,Position1);
		wstring													FriendlyNameAssemblyToLoadIdentity=AssemblyToLoadIdentity.substr(0,Position2);

		// !!! ASSEMBLY IDENTITY NAME ASSEMBLY, ktora sa ma nacitat sa musi zhodovat s ASSEMBLY IDENTITY NAME zaznamu v .BAG FILE.
		if (FriendlyNameAssemblyIdentity==FriendlyNameAssemblyToLoadIdentity)
		{
			IStream*											Stream=NULL;

			// !!! Vytvori sa OBJECT typu IStream.
			if (SUCCEEDED(HR=CreateStreamOnHGlobal(NULL,FALSE,&Stream)))
			{
				ULONG											Written;

				// !!! Do IStream sa zapise obsah ASSEMBLY.
				if (SUCCEEDED(HR=Stream->Write((*Iterator)->GetFileData(),(*Iterator)->GetFileSize(),&Written)))
				{
					LARGE_INTEGER								LI;

					LI.QuadPart=0;

					// !!! Pozicia v IStream sa presunie na zaciatok STREAM.
					if (SUCCEEDED(HR=Stream->Seek(LI,STREAM_SEEK_SET,NULL)))
					{
						*AssemblyID=AssemblyIDCounter;
						*StmAssemblyImage=Stream;
						*Context=ASSEMBLY_FROM_BAG;

						return(S_OK);
					}
				}

				Stream->Release();
			}
		}

		AssemblyIDCounter++;
	}

	return(COR_E_FILENOTFOUND);
}
//------------------------------------------------------------------------------------------------------
// !!! Pri MULTI-MODULE ASSEMBLIES je volana pre VSETKY MODULES OKREM MANIFEST MODULE.
// !!!!! Kedze .BAG obsahuje iba SINGLE-MODULE ASSEMBLIES, tak tato METHOD NIE JE IMPLEMENTOVANA.
HRESULT STDMETHODCALLTYPE CBagHostAssemblyStore::ProvideModule(ModuleBindInfo* BindInfo, DWORD* ModuleID, IStream** StmModuleImage, IStream** StmPDB)
{
	CLock														Lock(MCS);

	// !!! Nie je implementovana.
	return(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CBagHostAssemblyStore::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IHostAssemblyStore*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IHostControl)
	{
		*PointerToObject=static_cast<IHostAssemblyStore*>(this);
		AddRef();
		return(S_OK);
	}
	else
	{
		*PointerToObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CBagHostAssemblyStore::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CBagHostAssemblyStore::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------