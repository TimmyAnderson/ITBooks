//----------------------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "MyDebug.h"
#include "CString.h"
#include "CException.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#pragma warning( disable : 26498 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
DWORD CreateNewProcess(LPCWSTR ApplicationName)
{
    LPWSTR														CommandLine=NULL;
    LPSECURITY_ATTRIBUTES										ProcessAttributes=NULL;
    LPSECURITY_ATTRIBUTES										ThreadAttributes=NULL;
    BOOL														InheritHandles=FALSE;
    DWORD														CreationFlags=NORMAL_PRIORITY_CLASS;
    LPVOID														Environment=NULL;
    LPCWSTR														CurrentDirectory=NULL;
	STARTUPINFOW												StartupInfo;

	ZeroMemory(&StartupInfo,sizeof(StartupInfo));
	StartupInfo.cb=sizeof(StartupInfo);

	PROCESS_INFORMATION											ProcessInformation{};

	ZeroMemory(&ProcessInformation,sizeof(ProcessInformation));

	if (CreateProcess(ApplicationName,CommandLine,ProcessAttributes,ThreadAttributes,InheritHandles,CreationFlags,Environment,CurrentDirectory,&StartupInfo,&ProcessInformation)!=FALSE)
	{
		CloseHandle(ProcessInformation.hProcess);
		CloseHandle(ProcessInformation.hThread);

		return(ProcessInformation.dwProcessId);
	}
	else
	{
		throw(CException(L"Can't CREATE PROCESS."));
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TerminateExistingProcess(DWORD PID, UINT ExitCode)
{
	HANDLE														Process=OpenProcess(PROCESS_TERMINATE,FALSE,PID);

	if (Process!=FALSE)
	{
		BOOL													Terminated=TerminateProcess(Process,ExitCode);

		CloseHandle(Process);

		if (Terminated==FALSE)
		{
			throw(CException(L"Can't TERMINATE PROCESS."));
		}
	}
	else
	{
		throw(CException(L"Can't OPEN PROCESS."));
	}
}
//----------------------------------------------------------------------------------------------------------------------
void Test(void)
{
	PrintLineSeparator();

	try
	{
		LPCWSTR													ApplicationName=L"C:\\WINDOWS\\system32\\notepad.exe";
		DWORD													PID=CreateNewProcess(ApplicationName);

		wcout << L"PROCESS CREATED." << endl;

		TerminateExistingProcess(PID,999);

		wcout << L"PROCESS TERMINATED." << endl;
	}
	catch(const CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	Test();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------