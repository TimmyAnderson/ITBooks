#include "..\..\..\..\CommonFiles\CmnHdr.h"     /* See Appendix A. */
#include <windowsx.h>
#include <tchar.h>
#include "Resource.h"
#include "..\22-LastMsgBoxInfoLib\LastMsgBoxInfoLib.h"
//------------------------------------------------------------------------------
BOOL Dlg_OnInitDialog(HWND Wnd, HWND WndFocus, LPARAM Param)
{
	chSETDLGICONS(Wnd, IDI_LASTMSGBOXINFO);

	SetDlgItemText(Wnd, IDC_INFO, TEXT("Waiting for a Message Box to be dismissed !"));

	return(TRUE);
}
//------------------------------------------------------------------------------
void Dlg_OnSize(HWND Wnd, UINT State, int CX, int CY)
{
	SetWindowPos(GetDlgItem(Wnd, IDC_INFO), NULL, 0, 0, CX, CY, SWP_NOZORDER);
}
//------------------------------------------------------------------------------
void Dlg_OnCommand(HWND Wnd, int ID, HWND WndCtl, UINT CodeNotify)
{
	switch (ID)
	{
		case IDCANCEL:
			EndDialog(Wnd, ID);
        break;
	}
}
//------------------------------------------------------------------------------
// !!! WM_COPYDATA je volana z HOOKED DLL a obsahuje text o poslednom uzavretom MessageBox().
BOOL Dlg_OnCopyData(HWND Wnd, HWND WndFrom, PCOPYDATASTRUCT PCDS)
{
	SetDlgItemTextW(Wnd,IDC_INFO,(PCWSTR) PCDS->lpData);

	return(TRUE);
}
//------------------------------------------------------------------------------
// Obsluzna rutina pre dialogove okno.
INT_PTR WINAPI Dlg_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		chHANDLE_DLGMSG(hWnd, WM_INITDIALOG, Dlg_OnInitDialog);
		chHANDLE_DLGMSG(hWnd, WM_SIZE,       Dlg_OnSize);
		chHANDLE_DLGMSG(hWnd, WM_COMMAND,    Dlg_OnCommand);
		chHANDLE_DLGMSG(hWnd, WM_COPYDATA,   Dlg_OnCopyData);
	}

	return(FALSE);
}
//------------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE InstExe, HINSTANCE, PTSTR CmdLine, int)
{
	// Kedze ThreadId==0 - zavadzam HOOK pre VSETKY spustene GUI APLIKACIE.
	DWORD		ThreadId=0;

	// Instalujem HOOK DLL, ktora zavedie HOOK pre WH_GETMESSAGE na VSETKY beziace GUI aplikacie.
	LastMsgBoxInfo_HookAllApps(TRUE,ThreadId);

	DialogBox(InstExe,MAKEINTRESOURCE(IDD_LASTMSGBOXINFO), NULL, Dlg_Proc);

	// Odinstalujem HOOK DLL zo VSETKYCH beziacich GUI aplikacii.
	LastMsgBoxInfo_HookAllApps(FALSE,0);

	return(0);
}
//------------------------------------------------------------------------------