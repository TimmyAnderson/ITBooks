#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <conio.h>
#include <Werapi.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
wchar_t* ConvertReportToText(WER_SUBMIT_RESULT ReportResult)
{
	switch(ReportResult)
	{
		case WerReportQueued:
			return(L"WerReportQueued");

		case WerReportUploaded:
			return(L"WerReportUploaded");

		case WerReportDebug:
			return(L"WerReportDebug");

		case WerReportFailed:
			return(L"WerReportFailed");

		case WerDisabled:
			return(L"WerDisabled");

		case WerReportCancelled:
			return(L"WerReportCancelled");

		case WerDisabledQueue:
			return(L"WerDisabledQueue");

		case WerReportAsync:
			return(L"WerReportAsync");

		default:
			return(L"UNKNOWN");
	}
}
//------------------------------------------------------------------------------
LONG ExceptionFilterCreatingDump(LPEXCEPTION_POINTERS PEP)
{
	HREPORT							HReport;
	WER_REPORT_INFORMATION			Information;

	ZeroMemory(&Information,sizeof(WER_REPORT_INFORMATION));

	Information.dwSize=sizeof(WER_REPORT_INFORMATION);

	StringCchCopy(Information.wzApplicationName,_countof(Information.wzApplicationName),L"My Custom WER REPORT");
	StringCchCopy(Information.wzDescription,_countof(Information.wzDescription),L"This is my application used for customizing WER report.");
	StringCchCopy(Information.wzFriendlyEventName,_countof(Information.wzFriendlyEventName),L"Some event OCCURED !");

	if (WerReportCreate(L"Big Error",WerReportNonCritical,&Information,&HReport)==S_OK)
	{
		wprintf_s(L"WerReportCreate() SUCCESSFULLY CREATED !\n");

		bool		Error=false;

		if (WerReportSetParameter(HReport,WER_P0,L"Application Name",L"XYZ")!=S_OK)
		{
			wprintf_s(L"WerReportSetParameter() - WER_P0 FAILED !\n");
			Error=true;
		}
		else
			wprintf_s(L"WerReportSetParameter() - WER_P0 SUCCESSFULLY CALLED !\n");

		if (WerReportSetParameter(HReport,WER_P1,L"My Name",L"Timmy Anderson")!=S_OK)
		{
			wprintf_s(L"WerReportSetParameter() - WER_P1 FAILED !\n");
			Error=true;
		}
		else
			wprintf_s(L"WerReportSetParameter() - WER_P1 SUCCESSFULLY CALLED !\n");

		if (WerReportSetParameter(HReport,WER_P2,L"My Friend's Name",L"Jenny Thompson")!=S_OK)
		{
			wprintf_s(L"WerReportSetParameter() - WER_P2 FAILED !\n");
			Error=true;
		}
		else
			wprintf_s(L"WerReportSetParameter() - WER_P2 SUCCESSFULLY CALLED !\n");

		if (Error==false)
		{
			WER_EXCEPTION_INFORMATION	ExceptionInformation;

			ExceptionInformation.bClientPointers=FALSE;
			ExceptionInformation.pExceptionPointers=PEP;

			if (WerReportAddDump(HReport,GetCurrentProcess(),GetCurrentThread(),WerDumpTypeHeapDump,&ExceptionInformation,NULL,0)==S_OK)
			{
				wprintf_s(L"WerReportAddDump() - SUCCESSFULLY CALLED !\n");

				wchar_t			FileName1[]={L"C:\\CustomDumpFile.txt"};
				wchar_t			FileName2[]={L"C:\\CustomTextFile.txt"};

				if (WerReportAddFile(HReport,FileName1,WerFileTypeMinidump,WER_FILE_ANONYMOUS_DATA)==S_OK)
					wprintf_s(L"WerReportAddFile() SUCCESSFULLY CALLED - FILE: [%s] !\n",FileName1);
				else
					wprintf_s(L"WerReportAddFile() FAILED - FILE: [%s] !\n",FileName1);

				if (WerReportAddFile(HReport,FileName2,WerFileTypeOther,WER_FILE_ANONYMOUS_DATA)==S_OK)
					wprintf_s(L"WerReportAddFile() SUCCESSFULLY CALLED - FILE: [%s] !\n",FileName2);
				else
					wprintf_s(L"WerReportAddFile() FAILED - FILE: [%s] !\n",FileName2);


				WER_SUBMIT_RESULT		ReportResult;

				if (WerReportSubmit(HReport,WerConsentNotAsked,WER_SUBMIT_QUEUE,&ReportResult)==S_OK)
				{
					wchar_t*			TextReport=ConvertReportToText(ReportResult);

					wprintf_s(L"WerReportSubmit() SUCCESSFULLY SENT REPORT - Result: [%d], Text: [%s] !\n",ReportResult,TextReport);
				}
				else
				{
					wchar_t*			TextReport=ConvertReportToText(ReportResult);

					wprintf_s(L"WerReportSubmit() FAILED to SEND REPORT - Result: [%d], Text: [%s] !\n",ReportResult,TextReport);
				}
			}
			else
				wprintf_s(L"WerReportAddDump() FAILED !\n");
		}

		if (WerReportCloseHandle(HReport)==S_OK)
			wprintf_s(L"WerReportCloseHandle() SUCCESSFULLY CLOSED !\n");
		else
			wprintf_s(L"WerReportCloseHandle() FAILED !\n");
	}
	else
		wprintf_s(L"WerReportCreate() FAILED !\n");

	return(EXCEPTION_EXECUTE_HANDLER);
}
//------------------------------------------------------------------------------
// Generuje DUMP bez EXCEPTION.
void Test1(void)
{
	HREPORT							HReport;
	WER_REPORT_INFORMATION			Information;

	ZeroMemory(&Information,sizeof(WER_REPORT_INFORMATION));

	Information.dwSize=sizeof(WER_REPORT_INFORMATION);

	StringCchCopy(Information.wzApplicationName,_countof(Information.wzApplicationName),L"My Custom WER REPORT");
	StringCchCopy(Information.wzDescription,_countof(Information.wzDescription),L"This is my application used for customizing WER report.");
	StringCchCopy(Information.wzFriendlyEventName,_countof(Information.wzFriendlyEventName),L"Some event OCCURED !");

	if (WerReportCreate(L"Big Error",WerReportNonCritical,&Information,&HReport)==S_OK)
	{
		wprintf_s(L"WerReportCreate() SUCCESSFULLY CREATED !\n");

		bool		Error=false;

		if (WerReportSetParameter(HReport,WER_P0,L"Application Name",L"XYZ")!=S_OK)
		{
			wprintf_s(L"WerReportSetParameter() - WER_P0 FAILED !\n");
			Error=true;
		}
		else
			wprintf_s(L"WerReportSetParameter() - WER_P0 SUCCESSFULLY CALLED !\n");

		if (WerReportSetParameter(HReport,WER_P1,L"My Name",L"Timmy Anderson")!=S_OK)
		{
			wprintf_s(L"WerReportSetParameter() - WER_P1 FAILED !\n");
			Error=true;
		}
		else
			wprintf_s(L"WerReportSetParameter() - WER_P1 SUCCESSFULLY CALLED !\n");

		if (WerReportSetParameter(HReport,WER_P2,L"My Friend's Name",L"Jenny Thompson")!=S_OK)
		{
			wprintf_s(L"WerReportSetParameter() - WER_P2 FAILED !\n");
			Error=true;
		}
		else
			wprintf_s(L"WerReportSetParameter() - WER_P2 SUCCESSFULLY CALLED !\n");

		if (Error==false)
		{
			WER_SUBMIT_RESULT		ReportResult;

			if (WerReportSubmit(HReport,WerConsentNotAsked,WER_SUBMIT_QUEUE,&ReportResult)==S_OK)
			{
				wchar_t*			TextReport=ConvertReportToText(ReportResult);

				wprintf_s(L"WerReportSubmit() SUCCESSFULLY SENT REPORT - Result: [%d], Text: [%s] !\n",ReportResult,TextReport);
			}
			else
			{
				wchar_t*			TextReport=ConvertReportToText(ReportResult);

				wprintf_s(L"WerReportSubmit() FAILED to SEND REPORT - Result: [%d], Text: [%s] !\n",ReportResult,TextReport);
			}
		}

		if (WerReportCloseHandle(HReport)==S_OK)
			wprintf_s(L"WerReportCloseHandle() SUCCESSFULLY CLOSED !\n");
		else
			wprintf_s(L"WerReportCloseHandle() FAILED !\n");
	}
	else
		wprintf_s(L"WerReportCreate() FAILED !\n");
}
//------------------------------------------------------------------------------
// Generuje DUMP PO VZNIKU EXCEPTION.
void Test2(void)
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

	//Test1();
	Test2();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------