#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <conio.h>
#include <ErrorRep.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
wchar_t* ConvertReportToText(EFaultRepRetVal ReportResult)
{
	switch(ReportResult)
	{
		case frrvOk:
			return(L"frrvOk");

		case frrvOkManifest:
			return(L"frrvOkManifest");

		case frrvOkQueued:
			return(L"frrvOkQueued");

		case frrvErr:
			return(L"frrvErr");

		case frrvErrNoDW:
			return(L"frrvErrNoDW");

		case frrvErrTimeout:
			return(L"frrvErrTimeout");

		case frrvLaunchDebugger:
			return(L"frrvLaunchDebugger");

		case frrvOkHeadless:
			return(L"frrvOkHeadless");

		case frrvErrAnotherInstance:
			return(L"frrvErrAnotherInstance");

		default:
			return(L"UNKNOWN");
	}
}
//------------------------------------------------------------------------------
LONG ExceptionFilterCreatingDump(LPEXCEPTION_POINTERS PEP)
{
	EFaultRepRetVal					ReportResult;

	ReportResult=ReportFault(PEP,0);

	wchar_t*						Text=ConvertReportToText(ReportResult);

	wprintf_s(L"ReportResult: [%d], Text: [%s] !\n",ReportResult,Text);

	return(EXCEPTION_EXECUTE_HANDLER);
}
//------------------------------------------------------------------------------
void Test(void)
{
	wprintf_s(L"Before TRY !\n");

	__try
	{
		BYTE*		Temp=(BYTE*) 0x200;

		// Vyvolam EXCEPTION.
		*Temp=100;

		// Tento kod sa NIKDY NEVYKONA.
		wprintf_s(L"Inside TRY 2 !\n");
	}
	__except(ExceptionFilterCreatingDump(GetExceptionInformation()))
	{
		wprintf_s(L"Inside EXCEPT !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int Argc, _TCHAR* argv[])
{
	SafeMain();

	Test();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------