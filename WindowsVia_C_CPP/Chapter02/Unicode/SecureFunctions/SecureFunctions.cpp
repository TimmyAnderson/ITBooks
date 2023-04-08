#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include "StrSafe.h"
//------------------------------------------------------------------------------
void MyErrorHandler(const wchar_t* Expression, const wchar_t* Function, const wchar_t* File, unsigned int Line, uintptr_t pReserved)
{
   wprintf(L"\n\n\nInvalid parameter detected in function %s ! File: %s Line: %d !\n", Function, File, Line);
   wprintf(L"Expression: %s !\n\n\n", Expression);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test1(void)
{
	wchar_t			BufferDest[10];
	wchar_t			BufferSource[]=L"Too long text !";
	int				Size=_countof(BufferDest);

	errno_t			Ret=wcscpy_s(BufferDest,Size,BufferSource);

	// !!!!! Tu sa kod NIKDY NEDOSTANE.
	wprintf(L"Size: [%d], Ret: [%d] !\n",Size,Ret);
}
//------------------------------------------------------------------------------
void Test2(void)
{
	// Nastavim CUSTOM ERROR HANDLER.
	_set_invalid_parameter_handler(MyErrorHandler);

	// Zablokujem ABORT APLIKACIE.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ASSERT, 0);

	wchar_t			BufferDest[10];
	wchar_t			BufferSource[]=L"Too long text !";
	// Dlzka je v pocte 'wchar_t'.
	int				Size=_countof(BufferDest);

	// Tato funkcia SKONCI v VRATI NAVRATOVU HODNOTU.
	errno_t			Ret=wcscpy_s(BufferDest,Size,BufferSource);

	wprintf(L"Size: [%d], Ret: [%d] !\n",Size,Ret);
}
//------------------------------------------------------------------------------
void Test3(void)
{
	wchar_t			BufferDestCch[100];
	wchar_t			BufferDestCb[100];
	wchar_t			BufferSource[]=L"Some text !";

	// Dlzka je v pocte 'wchar_t'.
	int				SizeInItems=_countof(BufferDestCch);
	int				SizeInBytes=sizeof(BufferDestCb);

	HRESULT			HR1=StringCchCopyW(BufferDestCch,SizeInItems,BufferSource);
	HRESULT			HR2=StringCbCopyW(BufferDestCb,SizeInBytes,BufferSource);

	wprintf(L"SizeInItems: [%d], SizeInBytes: [%d] !\n",SizeInItems,SizeInBytes);
	wprintf(L"HR1: [%d], HR2: [%d] !\n",HR1,HR2);
	wprintf(L"BufferDestCch: [%s], BufferDestCb: [%s] !\n",BufferDestCch,BufferDestCb);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	// !!! Nesmiem pouzit SafeMain(), lebo vyblokujem standardnu obsluhu chyb v C-runtime.
	//SafeMain();

	//Test1();
	//Test2();
	Test3();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------