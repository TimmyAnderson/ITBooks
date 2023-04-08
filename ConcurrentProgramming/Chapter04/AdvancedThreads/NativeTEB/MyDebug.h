//-----------------------------------------------------------------------------
#include <conio.h>
#include <crtdbg.h>
#include <stdlib.h>
//-----------------------------------------------------------------------------
void MyInvalidParameterHandler(const wchar_t* Expression, const wchar_t* Function, const wchar_t* File, unsigned int Line, uintptr_t pReserved)
{
   wprintf(L"\n\n\nInvalid parameter detected in function %s ! File: %s Line: %d !\n", Function, File, Line);
   wprintf(L"Expression: %s !\n\n\n", Expression);
}
//-----------------------------------------------------------------------------
void SafeMain()
{
	_set_invalid_parameter_handler(MyInvalidParameterHandler);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ASSERT, 0);
}
//-----------------------------------------------------------------------------
void ShowExitLine()
{
	printf_s("\nPress any key to EXIT !\n");
	_getch();
}
//-----------------------------------------------------------------------------