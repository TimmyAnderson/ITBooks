//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
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
int main(void)
{
	SafeMain();

	PrintLineSeparator();

	{
		// !!!!! SYMBOLIC LINK NAME [PROCEXP152] odkazuje na DRIVER, ktory interne vytvara SYSINTERNALS PROGRAM [Process Explorer], ak je spusteny s ELEVATED RIGHTS (v ADMIN MODE). Jeho NAME je mozne overit pomocou SYSINTERNALS TOOL [WinObj64], kde by sa mal nachadzat v DIRECTORY [GLOBAL??].
		// !!!!! NAME [PROCEXP152] sa moze zmenit s novsou verziou SYSINTERNALS PROGRAM [Process Explorer].
		// !!!!! SYMBOLIC LINK NAME [PROCEXP152] sa NEVYTVORI, kym nie je spusteni SYSINTERNALS PROGRAM [Process Explorer] s ELEVATED RIGHTS.
		const wchar_t*											SymbolicLinkName=L"\\\\.\\PROCEXP152";

		// !!! Alternativna SYNTAX pre C++ STRINGS v C++ 11.
		//const wchar_t*										SymbolicLinkName=LR"(\\.\PROCEXP152)";

		HANDLE													DeviceHandle=CreateFile(SymbolicLinkName,GENERIC_WRITE | GENERIC_READ,0,nullptr,OPEN_EXISTING,0,nullptr);

		if (DeviceHandle!=INVALID_HANDLE_VALUE)
		{
			wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] OPENED SUCCESSFULLY." << endl;

			CloseHandle(DeviceHandle);
		}
		else
		{
			wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] FAILED to OPEN." << endl;
		}
	}

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------