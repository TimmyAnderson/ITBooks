#include "..\..\..\..\CommonFiles\CmnHdr.h"
#include <WindowsX.h>
#include <tchar.h>
#include <stdio.h>
#include "APIHook.h"
//------------------------------------------------------------------------------
#define LASTMSGBOXINFOLIBAPI extern "C" __declspec(dllexport)
#include "LastMsgBoxInfoLib.h"
#include <StrSafe.h>
//------------------------------------------------------------------------------
// Prototypy NMessageBox() funkcii, ktore budu HOOKED.
typedef int (WINAPI *PFNMESSAGEBOXA)(HWND Wnd, PCSTR Text, PCSTR Caption, UINT Type);
typedef int (WINAPI *PFNMESSAGEBOXW)(HWND Wnd, PCWSTR Text, PCWSTR Caption, UINT Type);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Dopredne referencie na premenne.
extern CAPIHook		GMessageBoxA;
extern CAPIHook		GMessageBoxW;
//------------------------------------------------------------------------------
// Notifikacna funkcia, ktora zobrazi informaciu o ukonceni MessageBox() v hlavnom okne '22-LastMsgBoxInfo.exe'.
void SendLastMsgBoxInfo(BOOL Unicode, PVOID Caption, PVOID Text, int Result)
{
	wchar_t			ProcessPathname[MAX_PATH];

	// Ziskam meno procesu, v ktorom sa volala MessageBox().
	GetModuleFileNameW(NULL,ProcessPathname,MAX_PATH);

	// Konverujem navratovu hodnotu MessageBox() na text.
	PCWSTR			TResult=L"(Unknown)";

	switch(Result)
	{
		case IDOK:       TResult=L"Ok";        break;
		case IDCANCEL:   TResult=L"Cancel";    break;
		case IDABORT:    TResult=L"Abort";     break;
		case IDRETRY:    TResult=L"Retry";     break;
		case IDIGNORE:   TResult=L"Ignore";    break;
		case IDYES:      TResult=L"Yes";       break;
		case IDNO:       TResult=L"No";        break;
		case IDCLOSE:    TResult=L"Close";     break;
		case IDHELP:     TResult=L"Help";      break;
		case IDTRYAGAIN: TResult=L"Try Again"; break;
		case IDCONTINUE: TResult=L"Continue";  break;
	}

	// Vytvorim text, ktory sa zobrazi do okna '22-LastMsgBoxInfo.exe'.
	wchar_t			SZ[2048];

	StringCchPrintfW(SZ,_countof(SZ),(Unicode==TRUE) ? L"Process: (%d) [%s] !\r\nCaption: [%s] !\r\nMessage: [%s] !\r\nResult: [%s] !" : L"Process: (%d) [%s] !\r\nCaption: [%S] !\r\nMessage: [%S] !\r\nResult: [%s] !",GetCurrentProcessId(),ProcessPathname,Caption,Text,TResult);

	// Zaslem text do okna '22-LastMsgBoxInfo.exe'.
	COPYDATASTRUCT	CDS={ 0, ((DWORD)wcslen(SZ) + 1) * sizeof(wchar_t), SZ };

	// Na zaslanie pouzijem WM_COPYDATA.
	FORWARD_WM_COPYDATA(FindWindow(NULL, TEXT("Last MessageBox Info")), NULL, &CDS, SendMessage);
}
//------------------------------------------------------------------------------
// HOOKED MessageBoxW().
int WINAPI Hook_MessageBoxW(HWND Wnd, PCWSTR Text, LPCWSTR Caption, UINT Type)
{
	// Zavolam POVODNU API FUNKCIU. Vyuziva sa KONVERZNY OPERATOR, ktory vracia adresu POVODNEJ funkcie.
	int			Result=((PFNMESSAGEBOXW)(PROC) GMessageBoxW) (Wnd, Text, Caption, Type);

	// Zaslem notifikaciu o volani MessageBox() do hlavneho okna '22-LastMsgBoxInfo.exe'.
	SendLastMsgBoxInfo(TRUE,(PVOID) Caption,(PVOID) Text,Result);

	return(Result);
}
//------------------------------------------------------------------------------
// HOOKED MessageBoxA().
int WINAPI Hook_MessageBoxA(HWND Wnd, PCSTR Text, PCSTR Caption, UINT Type)
{
	// Zavolam POVODNU API FUNKCIU. Vyuziva sa KONVERZNY OPERATOR, ktory vracia adresu POVODNEJ funkcie.
	int			Result=((PFNMESSAGEBOXA)(PROC) GMessageBoxA)(Wnd,Text,Caption,Type);

	// Zaslem notifikaciu o volani MessageBox() do hlavneho okna '22-LastMsgBoxInfo.exe'.
	SendLastMsgBoxInfo(FALSE,(PVOID) Caption,(PVOID) Text, Result);

	return(Result);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// !!!!! Toto je NAJDOLEZITEJSIA CAST HOOK DLL. Su to GLOBALNE PPREMENNE, ktore v KONSTURKTORE VYKONAJU HOOKING na funkcie MessageBoxA() a MessageBoxW().
// Funguje to nasledovne.
// 1. '22-LastMsgBoxInfo.EXE' zavadza '22-LastMsgBoxInfoLib.dll' do pamate a LastMsgBoxInfo_HookAllApps(), ktora vykona HOOKING VSETKYCH BEZIACICH GUI APLIKACII vytvorenim HOOK na WH_GETMESSAGE. Vytvorenim tohto HOOK KAZDA APLIKACIA pri prichode MESSAGE NOTIFIKUJE HOOK FUNKCIU GetMsgProc() '22-LastMsgBoxInfoLib.dll'.
// 2. Funkcia GetMsgProc() NIC NEROBI, iba forwarduje volanie do GetMsgProc().
// !!!!! 3. KLUCOVE VSAK JE, ze pri sa zavedenim HOOKU ZAVIEDLA do OSTATNYCH PROCESOV '22-LastMsgBoxInfoLib.dll'.
// !!!!! 4. Kedze '22-LastMsgBoxInfoLib.dll' ma GLOBALNE PREMENNE GMessageBoxA a GMessageBoxW, tieto SPUSTIA SVOJE KONTRUKTORY v HOOKED PROCESE.
// !!!!! 5. Konstruktory CAPIHook potom vykonaju API HOOKING pre API funkcie MessageBoxA() a MessageBoxW().
CAPIHook			GMessageBoxA("User32.dll", "MessageBoxA", (PROC) Hook_MessageBoxA);
CAPIHook			GMessageBoxW("User32.dll", "MessageBoxW", (PROC) Hook_MessageBoxW);
//------------------------------------------------------------------------------
HHOOK				GHook=NULL;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Hook funkcia, ktora NEROBI NIC, pretoze CELA CINNOST je vykonana v KONSTRUKTOROCH GLOBALNYCH PREMENNYCH CAPIHook.
static LRESULT WINAPI GetMsgProc(int Code, WPARAM WParam, LPARAM LParam)
{
	return(CallNextHookEx(GHook,Code,WParam,LParam));
}
//------------------------------------------------------------------------------
// Vrati HMODULE z adresy funkcie.
static HMODULE ModuleFromAddress(PVOID PV)
{
	MEMORY_BASIC_INFORMATION		MBI;

	return((VirtualQuery(PV, &MBI, sizeof(MBI))!= 0) ? (HMODULE) MBI.AllocationBase : NULL);
}
//------------------------------------------------------------------------------
// Funkcia vykona HOOKING VSETKYCH BEZIACICH GUI APLIKACII vytvorenim HOOK na WH_GETMESSAGE. Vytvorenim tohto HOOK KAZDA APLIKACIA pri prichode MESSAGE NOTIFIKUJE HOOK FUNKCIU GetMsgProc() '22-LastMsgBoxInfoLib.dll'.
BOOL WINAPI LastMsgBoxInfo_HookAllApps(BOOL Install, DWORD ThreadId)
{
	BOOL		Ok;

	if (Install==TRUE)
	{
	    // Illegal to install twice in a row.
		chASSERT(GHook==NULL);

		// Instalujem HOOK.
		GHook=SetWindowsHookEx(WH_GETMESSAGE,GetMsgProc,ModuleFromAddress(LastMsgBoxInfo_HookAllApps), ThreadId);

		Ok=(GHook!=NULL);
	}
	else
	{
		// Can't uninstall if not installed.
		chASSERT(GHook!=NULL); 

		// Odinstalujem HOOK.
		Ok=UnhookWindowsHookEx(GHook);
		GHook=NULL;
	}

	return(Ok);
}
//------------------------------------------------------------------------------