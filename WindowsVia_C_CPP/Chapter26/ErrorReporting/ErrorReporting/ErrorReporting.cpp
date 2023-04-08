#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <conio.h>
#include <Werapi.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
// !!! Program je potrebne spustat MIMO Visual Studia.
//------------------------------------------------------------------------------
void Test1(void)
{
	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY 1 !\n");

		BYTE*		Temp=NULL;

		// Vyvolam EXCEPTION.
		*Temp=100;

		// Tento kod sa NIKDY NEVYKONA.
		wprintf_s(L"Inside TRY 2 !\n");
	}
	__finally
	{
		wprintf_s(L"Inside FINALLY !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Test2(void)
{
	// !!!!! Vdaka tomuto nastaveniu bude DUMP ulozeny i na LOKALNOM PC a je ho mozne prezerat.
	WerSetFlags(WER_FAULT_REPORTING_FLAG_QUEUE);

	DWORD			Flags=0;

	if (WerGetFlags(GetCurrentProcess(),&Flags)==S_OK)
		wprintf_s(L"WerGetFlags() returned [%d] !\n",Flags);
	else
		wprintf_s(L"WerGetFlags() FAILED !\n");

	_getch();

	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY 1 !\n");

		BYTE*		Temp=NULL;

		// Vyvolam EXCEPTION.
		*Temp=100;

		// Tento kod sa NIKDY NEVYKONA.
		wprintf_s(L"Inside TRY 2 !\n");
	}
	__finally
	{
		wprintf_s(L"Inside FINALLY !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Test3(void)
{
	// !!!!! Vdaka tomuto nastaveniu bude DUMP ulozeny i na LOKALNOM PC a je ho mozne prezerat.
	WerSetFlags(WER_FAULT_REPORTING_FLAG_QUEUE);

	DWORD			Flags=0;

	if (WerGetFlags(GetCurrentProcess(),&Flags)==S_OK)
		wprintf_s(L"WerGetFlags() returned [%d] !\n",Flags);
	else
		wprintf_s(L"WerGetFlags() FAILED !\n");

	// Maximalna dlzka dat je WER_MAX_MEM_BLOCK_SIZE - co je 64 KB,
	BYTE			SomeDataToWER[1024];

	for(int i=0;i<_countof(SomeDataToWER);i++)
		SomeDataToWER[i]=65;

	// Pridam CUSTOM data do WER reportu.
	if (WerRegisterMemoryBlock(SomeDataToWER,sizeof(SomeDataToWER))==S_OK)
		wprintf_s(L"WerRegisterMemoryBlock() was SUCCESSFUL !\n");
	else
		wprintf_s(L"WerRegisterMemoryBlock() FAILED !\n");

	wchar_t			FileName[]={L"C:\\CustomReportFile.txt"};

	if (WerRegisterFile(FileName,WerRegFileTypeOther,WER_FILE_ANONYMOUS_DATA)==S_OK)
		wprintf_s(L"WerRegisterFile() was SUCCESSFULLY CALLED - File: [%s] !\n",FileName);
	else
		wprintf_s(L"WerRegisterFile() FAILED - File: [%s] !\n",FileName);

	_getch();

	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY 1 !\n");

		BYTE*		Temp=NULL;

		// Vyvolam EXCEPTION.
		*Temp=100;

		// Tento kod sa NIKDY NEVYKONA.
		wprintf_s(L"Inside TRY 2 !\n");
	}
	__finally
	{
		wprintf_s(L"Inside FINALLY !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int Argc, _TCHAR* argv[])
{
	SafeMain();

	//Test1();
	//Test2();
	Test3();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------