#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <shlobj.h>
//------------------------------------------------------------------------------
// 1. Funkcia vracia DVE HODNOTY.
//    A. ElevationType - vracia ci je ACCES TOKEN PROCESU LIMITOVANY.
//	  B. IsAdmin - urcuje ci user pod ktorym bol spusteny je ADMINISTRATOR.
// 2. KLUCOVE JE, ze I KED USER MOZE BYT ADMINISTRATOR, tak ZAROVEN ACCESS TOKEN MOZE BYT LIMITOVANY UAC.
//------------------------------------------------------------------------------
BOOL GetProcessElevation(TOKEN_ELEVATION_TYPE* ElevationType, BOOL* IsAdmin)
{
	HANDLE				Token=NULL;
	DWORD				Size;

	// Otvorim ACCESS TOKEN pre CURRENT PROCESS.
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &Token)==FALSE)
		return(FALSE);

	BOOL				Result=FALSE;

	// Ziskam informaciu o ACCESS TOKEN - ci je LIMITOVANY UAC.
	// !!!!! Funkcia je naprogramovana dobre, ale pod XP vracia ERROR - asi preto, lebo XP nepodporuje UAC.
	if (GetTokenInformation(Token, TokenElevationType, ElevationType, sizeof(TOKEN_ELEVATION_TYPE), &Size)!=FALSE)
	{
		// !!!!! Teraz, ked som ZISTIL TYP ACCESS TOKENU (ci je limitovany UAC) musim zistit ci sa jedna o ADMINISTRATORA.

		BYTE			AdminSID[SECURITY_MAX_SID_SIZE];

		Size=sizeof(AdminSID);

		// Ziskam SID skupiny ADMINISTRATORS.
		CreateWellKnownSid(WinBuiltinAdministratorsSid, NULL, &AdminSID, &Size);

		// Zistim ci je ACCESS TOKEN limitovany.
		if (*ElevationType==TokenElevationTypeLimited)
		{
			// !!! ACCESS TOKEN je LIMITOVANY a preto MUSIM POZORIET na hodnotu LINKED ACCESS TOKEN.

			HANDLE		UnfilteredToken=NULL;

			// !!!!! Ziskam HANDLE na LINKED ACCESS TOKEN - teda NELIMITOVANY ACCESS TOKEN - TOKEN, predtym ako ho UAC OMBEDZIL.
			GetTokenInformation(Token, TokenLinkedToken, (VOID*) &UnfilteredToken, sizeof(HANDLE), &Size);

			// !!! Porovnam NELIMITOVANY ACCESS TOKEN s ACCESS TOKEN skupiny ADMINISTRATORS na zistenie ci bol proces spusteny pod user ADMINISTRATOR.
			if (CheckTokenMembership(UnfilteredToken, &AdminSID, IsAdmin)==TRUE)
				Result=TRUE;

			CloseHandle(UnfilteredToken);
		}
		// !!! Ak ACCESS TOKEN NIE JE LIMITOVANY tak PRIAMO zavolam IsUserAnAdmin() na zistenie ci je user v skupine ADMINISTRATORS.
		else
		{
			*IsAdmin=IsUserAnAdmin();
			Result=TRUE;
		}
	}

	CloseHandle(Token);

	return(Result);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	TOKEN_ELEVATION_TYPE	ElevationType=TokenElevationTypeDefault;
	BOOL					IsAdmin=FALSE;

	if (GetProcessElevation(&ElevationType,&IsAdmin)==FALSE)
	{
		wprintf_s(L"GetProcessElevation() FAILED !\n");
		return;
	}

	wprintf_s(L"TOKEN_ELEVATION_TYPE: [%d] !\n",ElevationType);
	wprintf_s(L"IsAdmin: [%d] !\n",IsAdmin);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	Test();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------