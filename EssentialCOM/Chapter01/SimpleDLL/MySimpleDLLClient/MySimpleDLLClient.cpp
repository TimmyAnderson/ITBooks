//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <Windows.h>
#include <conio.h>
#include <crtdbg.h>
#include <stdio.h>
#include "Debug.h"
#include "MySimpleDLL.h"
//------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	// !!! Aby program fungoval, MUSI byt MySimpleDLL.dll ulozena v TOM ISTOM DIRECTORY, ako .EXE FILE.

	SafeMain();

	CExportedClass												ExportedClass(L"Timmy Anderson");

	wprintf_s(L"Name [%s] !\n",ExportedClass.GetText());
	wprintf_s(L"ExportedVariable [%d] !\n",MExportedVariable);

	ExportedFunction(ExportedClass);

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------