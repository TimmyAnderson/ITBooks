#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include "StrSafe.h"
//------------------------------------------------------------------------------
wchar_t* StringComparisionResult(int Result)
{
	if (Result==0)
		return(L"ERROR");
	else if (Result==CSTR_LESS_THAN)
		return(L"LESS THAN");
	else if (Result==CSTR_EQUAL)
		return(L"EQUAL");
	else if (Result==CSTR_GREATER_THAN)
		return(L"GREATER THAN");
	else
		return(L"UNKNOWN");
}
//------------------------------------------------------------------------------
void PrintComparisionResult(wchar_t* String1, wchar_t* String2, int Result)
{
	wchar_t*		ResultString=StringComparisionResult(Result);

	wprintf(L"%s [%s] %s !\n",String1,ResultString,String2);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test1(void)
{
	LCID			LID=GetThreadLocale();
	wchar_t*		String1;
	wchar_t*		String2;
	int				Result;
	
	String1=L"Timmy";
	String2=L"timmy";

	Result=CompareString(LID,0,String1,-1,String2,-1);
	wprintf(L"CASE takes place - ");
	PrintComparisionResult(String1,String2,Result);

	Result=CompareString(LID,NORM_IGNORECASE,String1,-1,String2,-1);
	wprintf(L"CASE IGNORED - ");
	PrintComparisionResult(String1,String2,Result);

	// 'F' je v slovencine pred 'Ch'.
	String1=L"Fero - čšťŕ !";
	String2=L"Chlapec - čšťŕ !";

	Result=CompareString(LID,0,String1,-1,String2,-1);
	PrintComparisionResult(String1,String2,Result);

	// Zmenim LCID.
	LID=MAKELCID(MAKELANGID(LANG_SLOVAK,SUBLANG_DEFAULT),SORT_DEFAULT);

	Result=CompareString(LID,0,String1,-1,String2,-1);
	PrintComparisionResult(String1,String2,Result);

	// A teraz este i zmenim jazyk current threadu - bohuzial to NESPOSOBILO KOREKTNY VYPIS v SLOVENCINE.
	SetThreadLocale(LID);

	Result=CompareString(LID,0,String1,-1,String2,-1);
	PrintComparisionResult(String1,String2,Result);
}
//------------------------------------------------------------------------------
void Test2(void)
{
	/*
	wchar_t*		String1;
	wchar_t*		String2;
	int				Result;
	
	String1=L"Timmy";
	String2=L"timmy";

	// Testujem ORDINAL porovnanie.
	// !!!!! Funkcia CompareStringOrdinal() je podporovna AZ VO VISTE.
	Result=CompareStringOrdinal(String1,-1,String2,-1,FALSE);
	wprintf(L"CASE takes place - ");
	PrintComparisionResult(String1,String2,Result);

	Result=CompareStringOrdinal(String1,-1,String2,-1,TRUE);
	wprintf(L"CASE IGNORED - ");
	PrintComparisionResult(String1,String2,Result);
	*/
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	Test1();
	//Test2();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------