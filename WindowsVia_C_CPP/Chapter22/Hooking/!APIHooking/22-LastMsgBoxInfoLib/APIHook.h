#pragma once
//------------------------------------------------------------------------------
// !!! INSTANCIA CAPIHook reprezentuje 1 HOOKED API FUNKCIU.
class CAPIHook
{
	public:
		// Vykona HOOKING vo vsetkych MODULES.
		CAPIHook(PSTR CalleeModName, PSTR FuncName, PROC Hook);

		// Vykona UNHOOKING vo vsetkych MODULES.
		~CAPIHook();

		// Komverzny operator vracia POVODNU ADRESU API FUNKCIE.
		operator PROC() { return(MOrig); }

		// Blokuje aby '22-LastMsgBoxInfoLib.dll' HOOKOVALA sama seba.
		static BOOL						MExcludeAPIHookMod; 

	public:
		// Funkcia vrati POVODNU ADRESU API FUNKCIE.
		static FARPROC WINAPI GetProcAddressRaw(HMODULE hmod, PCSTR pszProcName);

	private:
		// Maximalna privatna pamatova adresa.
		static PVOID					MMaxAppAddr;
		// Hlavicka LINKED LIST s CAPIHook objektmi.
		// !!!!! Kazdy objekt CAPIHook predstavuje JEDNU HOOKED FUNKCIU.
		static CAPIHook*				MHead;
		// Adresa NASLEDUJUCEHO CAPIHook v LINKED LIST.
		CAPIHook*						MNext;

		// Meno MODULE obsahujuceho API funkciu, ktora ma byt HOOKED.
		PCSTR							MCalleeModName;
		// Meno FUNKCIE, ktora ma byt HOOKED.
		PCSTR							MFuncName;
		// Adresa POVODNEJ API FUNKCIE.
		PROC							MOrig;
		// Adresa HOOKED API FUNKCIE.
		PROC							MHook;

	private:
		// Funkcia robi HOOKING vo VSETKYCH ZAVEDENYCH MODULES (DLL).
		static void WINAPI ReplaceIATEntryInAllMods(PCSTR CalleeModName, PROC Orig, PROC Hook);

		// !!!!! Klucova funkcia, ktora v IMPORT SECTION NAHRADI povodnu adresu API funkcie za HOOKED FUNKCIU.
		static void WINAPI ReplaceIATEntryInOneMod(PCSTR CalleeModName, PROC Current, PROC New, HMODULE Caller);

		// Nahradza adresu API funkcie v EXPORT SECTION.
		static void ReplaceEATEntryInOneMod(HMODULE Mod, PCSTR FunctionName, PROC New);

	private:
		// Urobi ZMENU adries API funkcii za HOOKED funkcie pri DYNAMICKOM NAHRATI DLL - napriklad pri volani LoadLibrar().
		static void WINAPI FixupNewlyLoadedModule(HMODULE Mod, DWORD Flags);

		// HOOK funkcie, ktore zistuju ci nimi zavedena DLL neobsahuje API funkciu, ktora MA BYT HOOKED a ak ano tak VYKONA HOOKING.

		// HOOK funkcia pre LoadLibraryA().
		static HMODULE WINAPI LoadLibraryA(PCSTR ModulePath);
		// HOOK funkcia pre LoadLibraryW().
		static HMODULE WINAPI LoadLibraryW(PCWSTR ModulePath);
		// HOOK funkcia pre LoadLibraryExA().
		static HMODULE WINAPI LoadLibraryExA(PCSTR ModulePath, HANDLE File, DWORD dwFlags);
		// HOOK funkcia pre LoadLibraryExW().
		static HMODULE WINAPI LoadLibraryExW(PCWSTR ModulePath, HANDLE File, DWORD Flags);
		// HOOK funkcia pre GetProcAddress().
		static FARPROC WINAPI GetProcAddress(HMODULE Mod, PCSTR ProcName);

	private:
		// !!!!! Instancie tychto funkcii spravia HOOKING na API FUNKCIE, ktore DYNAMICKY ZAVADZAJU DLL a pri ich volani by sa MOHLA ZAVIEST DLL, ktora obsahuje API funkciu, ktora MA BYT HOOKED. Preto tieto funckie TIEZ MUSIA BYT HOOKED a HOOKED verzie spravia FIXACIU ADREIS - teda ak zavadzana DLL obsahuje API FUNKCIU, ktora mala byt HOOKED, tak SPRAVI TENTO HOOKING.
		// !!!!! Instancie su STATICKE co znamena, ze pri NAHRATI '22-LastMsgBoxInfoLib.dll' do pamate procesu sa VYTVORIA a HNED je volany ICH KONSTRUKTOR, ktory IHNED ROBI HOOKING. Tak je zabezpecene, ze UZ PRI NAHRANI '22-LastMsgBoxInfoLib.dll' do ADDRESS SPACE PROCESU, budu tieto funkcie HOOKED.
		static CAPIHook					MLoadLibraryA;
		static CAPIHook					MLoadLibraryW;
		static CAPIHook					MLoadLibraryExA;
		static CAPIHook					MLoadLibraryExW;
		static CAPIHook					MGetProcAddress;
};
//------------------------------------------------------------------------------