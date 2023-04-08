#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <conio.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
// !!! Program je potrebne spustat MIMO Visual Studia.
//------------------------------------------------------------------------------
int			GlobalDivisor=0;
//------------------------------------------------------------------------------
LONG WINAPI MyVectoredHandler_HANDLED(PEXCEPTION_POINTERS PEP)
{
	wchar_t				Buf[1024];
	wchar_t*			P;

	PEXCEPTION_RECORD	ER=PEP->ExceptionRecord;

	// Ziskam ExceptionCode.
	DWORD				ExceptionCode=ER->ExceptionCode;

	StringCchPrintf(Buf,_countof(Buf),L"!!! MyVectoredHandler_HANDLED() - Code = [%x], Address = [%p] !\n",ExceptionCode,ER->ExceptionAddress);

	P=wcschr(Buf,'\0');

	switch (ExceptionCode)
	{
		case EXCEPTION_ACCESS_VIOLATION:
		{
			StringCchPrintf(P,_countof(Buf),L"--> Attempt to [%s] data at address [%p] !\n",ER->ExceptionInformation[0] ? L"write" : L"read",ER->ExceptionInformation[1]);
		}
		break;

		default:
		break;
	}
	
	wprintf_s(Buf);

	// !!! Opravim chybu, ktora sposobila EXCEPTION.
	if (GlobalDivisor==0)
		GlobalDivisor=1;

	wprintf_s(L"MyVectoredHandler_HANDLED() - ERROR has been CORRECTED ! Execution WILL CONTINUE !\n");

	// EXCEPTION som SPRAVOVAL.
	return(EXCEPTION_CONTINUE_EXECUTION);
}
//------------------------------------------------------------------------------
LONG WINAPI MyVectoredHandler_UNHANDLED(PEXCEPTION_POINTERS PEP)
{
	wchar_t				Buf[1024];
	wchar_t*			P;

	PEXCEPTION_RECORD	ER=PEP->ExceptionRecord;

	// Ziskam ExceptionCode.
	DWORD				ExceptionCode=ER->ExceptionCode;

	StringCchPrintf(Buf,_countof(Buf),L"!!! MyVectoredHandler_HANDLED() - Code = [%x], Address = [%p] !\n",ExceptionCode,ER->ExceptionAddress);

	P=wcschr(Buf,'\0');

	switch (ExceptionCode)
	{
		case EXCEPTION_ACCESS_VIOLATION:
		{
			StringCchPrintf(P,_countof(Buf),L"--> Attempt to [%s] data at address [%p] !\n",ER->ExceptionInformation[0] ? L"write" : L"read",ER->ExceptionInformation[1]);
		}
		break;

		default:
		break;
	}
	
	wprintf_s(Buf);

	// EXCEPTION som NESPRAVOVAL.
	return(EXCEPTION_CONTINUE_SEARCH);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
LONG WINAPI MyUnhandledFilter_HANDLED(_EXCEPTION_POINTERS* PEP)
{
	wchar_t				Buf[1024];
	wchar_t*			P;

	PEXCEPTION_RECORD	ER=PEP->ExceptionRecord;

	// Ziskam ExceptionCode.
	DWORD				ExceptionCode=ER->ExceptionCode;

	StringCchPrintf(Buf,_countof(Buf),L"!!! MyUnhandledFilter_HANDLED() - Code = [%x], Address = [%p] !\n",ExceptionCode,ER->ExceptionAddress);

	P=wcschr(Buf,'\0');

	switch (ExceptionCode)
	{
		case EXCEPTION_ACCESS_VIOLATION:
		{
			StringCchPrintf(P,_countof(Buf),L"--> Attempt to [%s] data at address [%p] !\n",ER->ExceptionInformation[0] ? L"write" : L"read",ER->ExceptionInformation[1]);
		}
		break;

		default:
		break;
	}
	
	wprintf_s(Buf);

	// Simulujem, ze EXCEPTION BOLA SPRACOVANA.
	return(EXCEPTION_EXECUTE_HANDLER);
}
//------------------------------------------------------------------------------
LONG WINAPI MyUnhandledFilter_UNHANDLED(_EXCEPTION_POINTERS* PEP)
{
	wchar_t				Buf[1024];
	wchar_t*			P;

	PEXCEPTION_RECORD	ER=PEP->ExceptionRecord;

	// Ziskam ExceptionCode.
	DWORD				ExceptionCode=ER->ExceptionCode;

	StringCchPrintf(Buf,_countof(Buf),L"!!! MyUnhandledFilter_UNHANDLED() - Code = [%x], Address = [%p] !\n",ExceptionCode,ER->ExceptionAddress);

	P=wcschr(Buf,'\0');

	switch (ExceptionCode)
	{
		case EXCEPTION_ACCESS_VIOLATION:
		{
			StringCchPrintf(P,_countof(Buf),L"--> Attempt to [%s] data at address [%p] !\n",ER->ExceptionInformation[0] ? L"write" : L"read",ER->ExceptionInformation[1]);
		}
		break;

		default:
		break;
	}
	
	wprintf_s(Buf);

	// Simulujem, ze EXCEPTION NEBOLA SPRACOVANA - PROGRAM KOMPLETNE ZLYHA a naskoci moznost DEBUGGOVAT PROGRAM.
	return(EXCEPTION_CONTINUE_SEARCH);
}
//------------------------------------------------------------------------------
LONG WINAPI MyUnhandledFilter_CONTINUE_EXECUTION(_EXCEPTION_POINTERS* PEP)
{
	wchar_t				Buf[1024];
	wchar_t*			P;

	PEXCEPTION_RECORD	ER=PEP->ExceptionRecord;

	// Ziskam ExceptionCode.
	DWORD				ExceptionCode=ER->ExceptionCode;

	StringCchPrintf(Buf,_countof(Buf),L"!!! MyUnhandledFilter_CONTINUE_EXECUTION() - Code = [%x], Address = [%p] !\n",ExceptionCode,ER->ExceptionAddress);

	P=wcschr(Buf,'\0');

	switch (ExceptionCode)
	{
		case EXCEPTION_ACCESS_VIOLATION:
		{
			StringCchPrintf(P,_countof(Buf),L"--> Attempt to [%s] data at address [%p] !\n",ER->ExceptionInformation[0] ? L"write" : L"read",ER->ExceptionInformation[1]);
		}
		break;

		default:
		break;
	}
	
	wprintf_s(Buf);

	// !!! Opravim chybu, ktora sposobila EXCEPTION.
	if (GlobalDivisor==0)
		GlobalDivisor=1;

	wprintf_s(L"MyUnhandledFilter_CONTINUE_EXECUTION() - ERROR has been CORRECTED ! Execution WILL CONTINUE !\n");

	// Simulujem POKRACOVANIE CINNOSTI a program NIE JE TERMINATED, ale pokracuje dalej.
	return(EXCEPTION_CONTINUE_EXECUTION);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test1(void)
{
	SetUnhandledExceptionFilter(MyUnhandledFilter_HANDLED);

	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY 1 !\n");

		BYTE*		Temp=(BYTE*) 0x200;

		// Vyvolam EXCEPTION.
		*Temp=100;

		// Tento kod sa NIKDY NEVYKONA.
		wprintf_s(L"Inside TRY 2 !\n");
	}
	// EXCEPTION NEZACHYTAVAM - FINALLY sa ZAVOLA.
	__finally
	{
		wprintf_s(L"Inside FINALLY !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Test2(void)
{
	SetUnhandledExceptionFilter(MyUnhandledFilter_UNHANDLED);

	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY 1 !\n");

		BYTE*		Temp=(BYTE*) 0x200;

		// Vyvolam EXCEPTION.
		*Temp=100;

		// Tento kod sa NIKDY NEVYKONA.
		wprintf_s(L"Inside TRY 2 !\n");
	}
	// EXCEPTION NEZACHYTAVAM - FINALLY sa ZAVOLA.
	__finally
	{
		wprintf_s(L"Inside FINALLY !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Test3(void)
{
	SetUnhandledExceptionFilter(MyUnhandledFilter_CONTINUE_EXECUTION);

	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY 1 !\n");

		int			Result;

		// Vyvolam EXCEPTION.
		Result=100/GlobalDivisor;

		wprintf_s(L"Result: [%d] !\n",Result);

		// Tento kod sa NIKDY NEVYKONA.
		wprintf_s(L"Inside TRY 2 !\n");
	}
	// EXCEPTION NEZACHYTAVAM - FINALLY sa ZAVOLA.
	__finally
	{
		wprintf_s(L"Inside FINALLY !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Test4(void)
{
	// !!! Zaregistrujem VECTORED EXCEPTION HANDLER - ktora OPRAVI CHYBU.
	PVOID		Handler=AddVectoredExceptionHandler(0,MyVectoredHandler_HANDLED);

	// !!! Pri pouzivani VECTORED EXCEPTION HANDLERS, ak tieto dokazu odstranit chybu, NIE JE TREBA pouzivat '__try' BLOK.
	int			Result;

	// Vyvolam EXCEPTION.
	Result=100/GlobalDivisor;

	wprintf_s(L"Result: [%d] !\n",Result);

	RemoveVectoredExceptionHandler(Handler);
}
//------------------------------------------------------------------------------
void Test5(void)
{
	// !!! Zaregistrujem VECTORED EXCEPTION HANDLER - ktora OPRAVI CHYBU.
	PVOID		Handler=AddVectoredExceptionHandler(0,MyVectoredHandler_HANDLED);

	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY 1 !\n");

		int			Result;

		// Vyvolam EXCEPTION.
		Result=100/GlobalDivisor;

		wprintf_s(L"Result: [%d] !\n",Result);

		// Tento kod sa NIKDY NEVYKONA.
		wprintf_s(L"Inside TRY 2 !\n");
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		// !!! Nikdy sa NEVYKONA, lebo chybu odstrani MyVectoredHandler().
		wprintf_s(L"!!! Inside EXCEPT !\n");
	}

	wprintf_s(L"After FINALLY !\n");

	RemoveVectoredExceptionHandler(Handler);
}
//------------------------------------------------------------------------------
void Test6(void)
{
	// Zaregistrujem VECTORED EXCEPTION HANDLER.
	// !!! K oprave chyby NEDOJDE a je GENEROVANA EXCEPTION, ktora je zachytena az v '__except' bloku.
	PVOID		Handler=AddVectoredExceptionHandler(0,MyVectoredHandler_UNHANDLED);

	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY 1 !\n");

		int			Result;

		// Vyvolam EXCEPTION.
		Result=100/GlobalDivisor;

		wprintf_s(L"Result: [%d] !\n",Result);

		// Tento kod sa NIKDY NEVYKONA.
		wprintf_s(L"Inside TRY 2 !\n");
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		// Kedze VECTORED EXCEPTION HANDLER chybu NEODSTRANIL, tak sa vola kod v '__except' bloku.
		wprintf_s(L"!!! Inside EXCEPT !\n");
	}

	wprintf_s(L"After FINALLY !\n");

	RemoveVectoredExceptionHandler(Handler);
}
//------------------------------------------------------------------------------
/*
// Je mozne spustit IBA vo VISTE.
void Test7(void)
{
	// !!! Zaregistrujem VECTORED EXCEPTION HANDLER pre UNHANDLED EXCEPTIONS.
	PVOID		Handler=AddVectoredContinueHandler(0,MyVectoredHandler_HANDLED);

	// !!! Pri pouzivani VECTORED EXCEPTION HANDLERS, ak tieto dokazu odstranit chybu, NIE JE TREBA pouzivat '__try' BLOK.
	int			Result;

	// Vyvolam EXCEPTION.
	Result=100/GlobalDivisor;

	wprintf_s(L"Result: [%d] !\n",Result);

	RemoveVectoredContinueHandler(Handler);
}
*/
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------