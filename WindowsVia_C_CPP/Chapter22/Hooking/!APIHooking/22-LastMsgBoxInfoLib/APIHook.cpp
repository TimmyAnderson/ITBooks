#include "..\..\..\..\CommonFiles\CmnHdr.h"
#include <ImageHlp.h>
#pragma comment(lib, "ImageHlp")
//------------------------------------------------------------------------------
#include "APIHook.h"
#include "..\..\..\..\CommonFiles\Toolhelp.h"
#include <StrSafe.h>
//------------------------------------------------------------------------------
// Hlavicka LINKED LIST s CAPIHook objektmi.
// !!!!! Kazdy objekt CAPIHook predstavuje JEDNU HOOKED FUNKCIU.
CAPIHook*					CAPIHook::MHead=NULL;
// Zablokujem aby '22-LastMsgBoxInfoLib.dll' HOOKOVALA sama seba.
BOOL						CAPIHook::MExcludeAPIHookMod=TRUE; 
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// !!!!! Instancie tychto funkcii spravia HOOKING na API FUNKCIE, ktore DYNAMICKY ZAVADZAJU DLL a pri ich volani by sa MOHLA ZAVIEST DLL, ktora obsahuje API funkciu, ktora MA BYT HOOKED. Preto tieto funckie TIEZ MUSIA BYT HOOKED a HOOKED verzie spravia FIXACIU ADREIS - teda ak zavadzana DLL obsahuje API FUNKCIU, ktora mala byt HOOKED, tak SPRAVI TENTO HOOKING.
// !!!!! Instancie su STATICKE co znamena, ze pri NAHRATI '22-LastMsgBoxInfoLib.dll' do pamate procesu sa VYTVORIA a HNED je volany ICH KONSTRUKTOR, ktory IHNED ROBI HOOKING. Tak je zabezpecene, ze UZ PRI NAHRANI '22-LastMsgBoxInfoLib.dll' do ADDRESS SPACE PROCESU, budu tieto funkcie HOOKED.
CAPIHook					CAPIHook::MLoadLibraryA("Kernel32.dll", "LoadLibraryA", (PROC) CAPIHook::LoadLibraryA);
CAPIHook					CAPIHook::MLoadLibraryW("Kernel32.dll", "LoadLibraryW", (PROC) CAPIHook::LoadLibraryW);
CAPIHook					CAPIHook::MLoadLibraryExA("Kernel32.dll", "LoadLibraryExA", (PROC) CAPIHook::LoadLibraryExA);
CAPIHook					CAPIHook::MLoadLibraryExW("Kernel32.dll", "LoadLibraryExW", (PROC) CAPIHook::LoadLibraryExW);
CAPIHook					CAPIHook::MGetProcAddress("Kernel32.dll", "GetProcAddress", (PROC) CAPIHook::GetProcAddress);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Exception HANDLER, ktory ignoruje EXCEPTIONS.
LONG WINAPI InvalidReadExceptionFilter(PEXCEPTION_POINTERS EP)
{
   LONG			Disposition=EXCEPTION_EXECUTE_HANDLER;

   return(Disposition);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
CAPIHook::CAPIHook(PSTR CalleeModName, PSTR FuncName, PROC Hook)
{
	// NextNode nastavim na aktualny vrchol LINKED LIST.
	MNext=MHead;
	// Prihodim NODE (CAPIHook) na vrchol LINKED LIST HOOKED FUNKCII.
	MHead=this;

	MCalleeModName=CalleeModName;
	MFuncName=FuncName;
	MHook=Hook;
	// Ziskam POVODNU ADRESU funkcie, ktora ma byt HOOKED.
	MOrig=GetProcAddressRaw(GetModuleHandleA(CalleeModName), MFuncName);

	// Ak funkciu ktora ma byt HOOKED nieviem najst, tak skoncim. Stava sa to vtedy, ked funkcia napriklad cez FreeLibrary() bola z ADDRESS SPACE odstranena.
	if (MOrig==NULL)
	{
		wchar_t			Pathname[MAX_PATH];

		GetModuleFileNameW(NULL,Pathname,_countof(Pathname));

		wchar_t			SZ[1024];

		StringCchPrintfW(SZ,_countof(SZ),TEXT("[%4u - %s] impossible to find [%S] !\r\n"),GetCurrentProcessId(),Pathname,FuncName);
		OutputDebugString(SZ);
		return;
	}

	// Vykonam HOOKING vo VSETKYCH MODULES - vsetkych DLL.
	ReplaceIATEntryInAllMods(MCalleeModName,MOrig,MHook);
}
//------------------------------------------------------------------------------
CAPIHook::~CAPIHook()
{
	// Spravim UNHOOKING API funkcie, ktoru reprezentuje tato instacia CAPIHook vo VSETKYCH MODULES.
	ReplaceIATEntryInAllMods(MCalleeModName,MHook,MOrig);

	// Odstranim Module z LINKED LIST.
	CAPIHook*		P=MHead; 

	if (P==this)
		MHead=P->MNext; 
	else
	{
		BOOL		Found=FALSE;

		for (;Found==FALSE && (P->MNext!=NULL);P=P->MNext)
		{
			if (P->MNext==this)
			{ 
				P->MNext=P->MNext->MNext; 
				Found=TRUE;
			}
		}
	}
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Funkcia vrati POVODNU ADRESU API FUNKCIE.
FARPROC CAPIHook::GetProcAddressRaw(HMODULE Mod, PCSTR ProcName)
{
	return(::GetProcAddress(Mod,ProcName));
}
//------------------------------------------------------------------------------
// Returns the HMODULE that contains the specified memory address
static HMODULE ModuleFromAddress(PVOID pv) {

   MEMORY_BASIC_INFORMATION mbi;
   return((VirtualQuery(pv, &mbi, sizeof(mbi)) != 0) 
      ? (HMODULE) mbi.AllocationBase : NULL);
}
//------------------------------------------------------------------------------
// Funkcia robi HOOKING vo VSETKYCH ZAVEDENYCH MODULES (DLL).
void CAPIHook::ReplaceIATEntryInAllMods(PCSTR CalleeModName, PROC Current, PROC New)
{
	HMODULE				ThisMod=(MExcludeAPIHookMod==TRUE) ? ModuleFromAddress(ReplaceIATEntryInAllMods) : NULL;

   // Ziskam zoznam MODULES v procese.
	CToolhelp			TH(TH32CS_SNAPMODULE, GetCurrentProcessId());
	MODULEENTRY32		ME={sizeof(ME)};

	for (BOOL Ok=TH.ModuleFirst(&ME);Ok!=FALSE;Ok=TH.ModuleNext(&ME))
	{
		// Nerobim HOOKING na HOOK-DLL.
		if (ME.hModule!=ThisMod)
		{
			// Vykonam HOOKING v danom MODULE.
			ReplaceIATEntryInOneMod(CalleeModName,Current,New,ME.hModule);
		}
	}
}
//------------------------------------------------------------------------------
// !!!!! Klucova funkcia, ktora v IMPORT SECTION NAHRADI povodnu adresu API funkcie za HOOKED FUNKCIU.
void CAPIHook::ReplaceIATEntryInOneMod(PCSTR CalleeModName, PROC Current, PROC New, HMODULE Caller)
{
	// Velkost IMPORT SECTION.
	ULONG						Size;
	PIMAGE_IMPORT_DESCRIPTOR	ImportDesc=NULL;

	__try
	{
		// Nacitam IMPORT SECTION - 'IMAGE_DIRECTORY_ENTRY_IMPORT'.
		ImportDesc=(PIMAGE_IMPORT_DESCRIPTOR) ImageDirectoryEntryToData(Caller,TRUE,IMAGE_DIRECTORY_ENTRY_IMPORT,&Size);
	} 
	__except (InvalidReadExceptionFilter(GetExceptionInformation()))
	{
		// Exceptions ignorujem.
	}
   
	// Nenasiel som IMPORT SECTION.
	if (ImportDesc==NULL)
		return;

	// Najdem IMPORT DESCRIPTOR, ktory reprezentuje MODULE (DLL), obsahujuci hladanu API funkciu.
	for (;ImportDesc->Name;ImportDesc++)
	{
		// Ziskam meno Module.
		PSTR					ModName=(PSTR) ((PBYTE) Caller + ImportDesc->Name);

		// Module name v ktorom je hladana API sa zhoduje s Module Name DESCRIPTOR.
		if (lstrcmpiA(ModName, CalleeModName)==0)
		{
			// Ziskam adresu na TABULKU IMPORTOVANYCH FUNKCII.
			PIMAGE_THUNK_DATA	Thunk=(PIMAGE_THUNK_DATA) ((PBYTE) Caller + ImportDesc->FirstThunk);

			// Prechadzam TABULKU IMPORTOVANYCH FUNKCII.
			for (;Thunk->u1.Function;Thunk++)
			{
				// Adresu o importovanej funkcii.
				PROC*			Pfn=(PROC*) &Thunk->u1.Function;

				// Zistim ci adresa importovanej funkcie je ROVNAKA ako ADRESA HLADANEJ API FUNKCIE.
				BOOL			Found=(*Pfn==Current);

				if (Found==TRUE)
				{
					// Skusim NAHRADIT adresu API funkcie za adresu HOOKED FUNKCIE.
					if (WriteProcessMemory(GetCurrentProcess(),Pfn,&New,sizeof(New),NULL)==FALSE && (ERROR_NOACCESS==GetLastError()))
					{
						DWORD	OldProtect;
                  
						// Ak sa zmena adresy nepodarila pre PAGE PROTECTION zmenim PAGE PROTECTION, aby bola zapisovatelna.
						if (VirtualProtect(Pfn,sizeof(New),PAGE_WRITECOPY,&OldProtect)==TRUE)
						{
							// Nahradim adresu povodnej API funkcie za novu.
							WriteProcessMemory(GetCurrentProcess(),Pfn,&New,sizeof(New),NULL);

							// Vratim PROTECTION na povodnu hodnotu.
							VirtualProtect(Pfn,sizeof(New),OldProtect,&OldProtect);
						}
					}

					return;
				}
			}
		}
	}
}
//------------------------------------------------------------------------------
// Nahradza adresu API funkcie v EXPORT SECTION.
void CAPIHook::ReplaceEATEntryInOneMod(HMODULE Mod, PCSTR FunctionName, PROC New)
{
	// Velkost EXPORT SECTION.
	ULONG						Size;
	PIMAGE_EXPORT_DIRECTORY		ExportDir=NULL;

	__try
	{
		// Nacitam EXPORT SECTION - 'IMAGE_DIRECTORY_ENTRY_EXPORT'.
		ExportDir=(PIMAGE_EXPORT_DIRECTORY) ImageDirectoryEntryToData(Mod,TRUE,IMAGE_DIRECTORY_ENTRY_EXPORT,&Size);
	} 
	__except (InvalidReadExceptionFilter(GetExceptionInformation()))
	{
		// Exceptions ignorujem.
	}
   
	// Nenasiel som EXPORT SECTION.
	if (ExportDir==NULL)
		return;

   PDWORD						NamesRvas=(PDWORD) ((PBYTE) Mod+ExportDir->AddressOfNames);
   PWORD						NameOrdinals=(PWORD) ((PBYTE) Mod+ExportDir->AddressOfNameOrdinals);
   PDWORD						FunctionAddresses=(PDWORD) ((PBYTE) Mod+ExportDir->AddressOfFunctions);

	// Prechadzam pole MIEN exportovanych funkcii.
	for (DWORD n=0;n<ExportDir->NumberOfNames;n++)
	{
		// Get the function name
		PSTR					FuncName=(PSTR) ((PBYTE) Mod+NamesRvas[n]);

		// Porovnavam meno funkcie s hladanym menom API funkcie.
		if (lstrcmpiA(FuncName,FunctionName)!=0)
			continue;

		// Ziskam ORDINAL NUMBER exportovanej funkcie.
		WORD					Ordinal=NameOrdinals[n];

		// Ziskam adresu API funkcie.
		PROC*					Pfn=(PROC*) &FunctionAddresses[Ordinal];
      
		// Vypocitam RVA adresu - relativnu adresu voci BASE ADDRESS DLL.
		New=(PROC) ((PBYTE) New-((PBYTE)Mod));

		// Skusim NAHRADIT adresu API funkcie za adresu HOOKED FUNKCIE.
		if (WriteProcessMemory(GetCurrentProcess(),Pfn,&New,sizeof(New),NULL)==FALSE && (ERROR_NOACCESS==GetLastError()))
		{
			DWORD				OldProtect;

			// Ak sa zmena adresy nepodarila pre PAGE PROTECTION zmenim PAGE PROTECTION, aby bola zapisovatelna.
			if (VirtualProtect(Pfn,sizeof(New),PAGE_WRITECOPY,&OldProtect)==TRUE)
			{
				// Nahradim adresu povodnej API funkcie za novu.
				WriteProcessMemory(GetCurrentProcess(),Pfn,&New,sizeof(New),NULL);

				// Vratim PROTECTION na povodnu hodnotu.
				VirtualProtect(Pfn,sizeof(New),OldProtect,&OldProtect);
			}
		}
		break;
	}
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Urobi ZMENU adries API funkcii za HOOKED funkcie pri DYNAMICKOM NAHRATI DLL - napriklad pri volani LoadLibrary().
void CAPIHook::FixupNewlyLoadedModule(HMODULE Mod, DWORD Flags)
{
	// Ak nova DLL je nahrata skontrolujem, ci neimportovala funkciu, ktora MA BYT HOOKED.
	if ((Mod!=NULL) && (Mod!=ModuleFromAddress(FixupNewlyLoadedModule)) && ((Flags & LOAD_LIBRARY_AS_DATAFILE)==0) && ((Flags & LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE)==0) && ((Flags & LOAD_LIBRARY_AS_IMAGE_RESOURCE)==0))
	{
		// !!!!! Prechadzam zoznam HOOKED FUNKCII - LINKED LIST vsetkych funkcii, ktore MAJU BYT HOOKED.
		for (CAPIHook* P=MHead;P!=NULL;P=P->MNext)
		{
			// Ak som nasiel funkciu, ktora MA BYT HOOKED, spravim HOOKING.
			if (P->MOrig!=NULL)
			{
				ReplaceIATEntryInAllMods(P->MCalleeModName,P->MOrig,P->MHook);
			}
			else
			{
#ifdef _DEBUG
				wchar_t		Pathname[MAX_PATH];
            
				GetModuleFileNameW(NULL,Pathname,_countof(Pathname));

				wchar_t		SZ[1024];
            
				StringCchPrintfW(SZ,_countof(SZ),TEXT("[%4u - %s] impossible to find [%S] !\r\n"),GetCurrentProcessId(),Pathname,P->MCalleeModName);
				OutputDebugString(SZ);
#endif
			}
		}
	}
}
//------------------------------------------------------------------------------
// HOOK funkcia pre LoadLibraryA().
HMODULE WINAPI CAPIHook::LoadLibraryA(PCSTR ModulePath)
{
	HMODULE					Mod=::LoadLibraryA(ModulePath);

	// Ak DLL obsahuje API funkciu, ktora ma byt HOOKED, tak vykonam HOOKING.
	FixupNewlyLoadedModule(Mod, 0);

	return(Mod);
}
//------------------------------------------------------------------------------
// HOOK funkcia pre LoadLibraryW().
HMODULE WINAPI CAPIHook::LoadLibraryW(PCWSTR ModulePath) {

   HMODULE					Mod=::LoadLibraryW(ModulePath);

	// Ak DLL obsahuje API funkciu, ktora ma byt HOOKED, tak vykonam HOOKING.
   FixupNewlyLoadedModule(Mod,0);

   return(Mod);
}
//------------------------------------------------------------------------------
// HOOK funkcia pre LoadLibraryExA().
HMODULE WINAPI CAPIHook::LoadLibraryExA(PCSTR ModulePath, HANDLE File, DWORD Flags)
{
	HMODULE					Mod=::LoadLibraryExA(ModulePath,File,Flags);

	// Ak DLL obsahuje API funkciu, ktora ma byt HOOKED, tak vykonam HOOKING.
	FixupNewlyLoadedModule(Mod,Flags);

	return(Mod);
}
//------------------------------------------------------------------------------
// HOOK funkcia pre LoadLibraryExW().
HMODULE WINAPI CAPIHook::LoadLibraryExW(PCWSTR ModulePath, HANDLE File, DWORD Flags)
{
	HMODULE					Mod=::LoadLibraryExW(ModulePath,File,Flags);

	// Ak DLL obsahuje API funkciu, ktora ma byt HOOKED, tak vykonam HOOKING.
	FixupNewlyLoadedModule(Mod,Flags);

	return(Mod);
}
//------------------------------------------------------------------------------
// HOOK funkcia pre GetProcAddress().
FARPROC WINAPI CAPIHook::GetProcAddress(HMODULE Mod, PCSTR ProcName)
{
	// Zisti SKUTOCNU adresu API funkcie.
	FARPROC					Pfn=GetProcAddressRaw(Mod,ProcName);
	CAPIHook*				P=MHead;

	// Zistim ci funckia, ktora ma byt cez GetProcAddress() byt volana PATRI do ZOZNAMU FUNCKII, ktore MAJU BYT HOOKED.
	for (;(Pfn!=NULL) && (P!=NULL);P=P->MNext)
	{
		if (Pfn==P->MOrig)
		{
			// Ak je pozadovana funkcia, ktora ma byt HOOKED, tak vratim adresu na HOOKED funkciu.
			Pfn=P->MHook;
			break;
		}
   }

   return(Pfn);
}
//------------------------------------------------------------------------------