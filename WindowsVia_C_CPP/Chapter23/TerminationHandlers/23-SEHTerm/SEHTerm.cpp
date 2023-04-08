#include "..\..\..\CommonFiles\CmnHdr.h"     /* See Appendix A. */
#include <windows.h>
#include <tchar.h>
//-----------------------------------------------------------------------------
// Zistim ci je program spusteny vo Viste.
BOOL IsWindowsVista()
{
	OSVERSIONINFOEX			OSVer={0};

	OSVer.dwOSVersionInfoSize=sizeof(OSVer);
	OSVer.dwMajorVersion=6;
	OSVer.dwMinorVersion=0;
	OSVer.dwPlatformId=VER_PLATFORM_WIN32_NT;

	DWORDLONG				DWLConditionMask=0;

	VER_SET_CONDITION(DWLConditionMask,VER_MAJORVERSION,VER_EQUAL);
	VER_SET_CONDITION(DWLConditionMask,VER_MINORVERSION,VER_EQUAL);
	VER_SET_CONDITION(DWLConditionMask,VER_PLATFORMID,VER_EQUAL);

	if (VerifyVersionInfo(&OSVer,VER_MAJORVERSION | VER_MINORVERSION | VER_PLATFORMID,DWLConditionMask)==TRUE)
	{
		// Som na Viste.
		return(TRUE);
	}
	else
		return(FALSE);
}
//-----------------------------------------------------------------------------
// Simulujem hodenie EXCEPTION.
void TriggerException(void)
{
	__try
	{
		int			N=MessageBox(NULL,L"Perform invalid memory access ?",L"TriggerException() - BEGIN",MB_YESNO);
      
		if (N==IDYES)
		{
			// Vykonam ACCESS VIOLATION.
			*(PBYTE) NULL=5;
		}
	}
	// V XP sa VZDY VYKONA.
	// !!! Vo Viste, IBA ked niektory EXCEPTION HANDLER vrati EXCEPTION_EXECUTE_HANDLER.
	__finally
	{
		if (AbnormalTermination()==TRUE)
			MessageBox(NULL,L"INSIDE '__finally' BLOCK - ABNORMAL TERMINATION !", L"TriggerException() - FINALLY",MB_OK);
		else
			MessageBox(NULL,L"INSIDE '__finally' BLOCK - NORMAL TERMINATION !", L"TriggerException() - FINALLY",MB_OK);
	}

	MessageBox(NULL,L"AFTER '__finally' BLOCK !", L"TriggerException() - END",MB_OK);
}
//-----------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, PTSTR, int)
{
	// !!! Vo Viste ku GLOBAL UNWIND (volaniu '__finally') pri EXCEPTION dojde IBA AK EXCEPTION FILTER vrati EXCEPTION_EXECUTE_HANDLER.
	// Ak dojde k UNHANDLED EXCEPTION proces je TERMINATED a '__finally' NIE JE VYKONANY.
	if (IsWindowsVista()==TRUE)
	{
		DWORD		N=MessageBox(NULL,L"Protect with try/except ?",L"_tWinMain() - BEGIN",MB_YESNO);

		if (N==IDYES)
		{
			__try
			{
				TriggerException();
			}
			__except(EXCEPTION_EXECUTE_HANDLER)
			{
				// Systemovy dialog sa nezobrazi - lebo som zachytil EXCEPTION.
				MessageBox(NULL,L"INSIDE '__except' BLOCK !",L"_tWinMain() - EXCEPT",MB_OK);

				// Vratim error code.
				//return(-1);
			}
		}
		else
		{
			TriggerException();
		}
	}
	// NIE SOM VO VISTE.
	else
	{
		DWORD		N=MessageBox(NULL,L"Protect with try/except ?",L"_tWinMain() - BEGIN",MB_YESNO);

		if (N==IDYES)
		{
			__try
			{
				TriggerException();
			}
			__except(EXCEPTION_EXECUTE_HANDLER)
			{
				MessageBox(NULL,L"INSIDE '__except' BLOCK !",L"_tWinMain() - EXCEPT",MB_OK);

				// Vratim error code.
				//return(-1);
			}
		}
		else
		{
			TriggerException();
		}
	}
   
	MessageBox(NULL,L"AFTER '__finally' BLOCK !", L"_tWinMain() - END",MB_OK);

	return(0);
}
//-----------------------------------------------------------------------------