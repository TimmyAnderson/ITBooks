#include "stdafx.h"
#include "ShowMessageBox.h"
//------------------------------------------------------------------------------
// Testovacia aplikacia na odskusanie funkcionality '22-LastMsgBoxInfoLib.dll' a '22-LastMsgBoxInfo.exe'.
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// !!! Tento prvy MessageBox sa NEZACHYTI.
	MessageBoxW(NULL,L"Test 1",L"Hooked MessageBox",MB_OK);
	
	// Tento MessageBox JE VSAK UZ ZACHYTENY v '22-LastMsgBoxInfo.exe'.
	MessageBoxW(NULL,L"Test 2",L"Hooked MessageBox",MB_OK);

	return(0);
}
//------------------------------------------------------------------------------