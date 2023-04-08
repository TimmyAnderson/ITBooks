#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
//------------------------------------------------------------------------------
void Test(void)
{
	wprintf_s(L"CHILD ID: [%d] !\n",GetCurrentProcessId());

	HANDLE		HProcess=GetCurrentProcess();
	BOOL		IsInJob=FALSE;

	if (IsProcessInJob(HProcess,NULL,&IsInJob)==FALSE)
		wprintf_s(L"IsProcessInJob() FAILED !\n");
	
	if (IsInJob==TRUE)
		wprintf_s(L"PROCESS IS IN JOB !!!\n");
	else
		wprintf_s(L"PROCESS IS NOT IN JOB !\n");

	// !!!!! Ak je JOB KO uzavrety PREDTYM ako je tento proces RESUMED (Test2() v Parent), tak nasledujuca funkcia ZLYHA, kedze k DELETED JOB NIE JE MOZNE PRISTUPOVAT, avsak PROCES BUDE I NADALEJ BEZAT v JOB, akurat NEBUDE MOZNE NA NOM VOLAT API FUNKCIE.
	if (OpenJobObject(JOB_OBJECT_ALL_ACCESS,FALSE,L"TIMMY")==FALSE)
		wprintf_s(L"Can't open JOB !\n");
	else
		wprintf_s(L"JOB SUCESSFULLY OPENED !\n");
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