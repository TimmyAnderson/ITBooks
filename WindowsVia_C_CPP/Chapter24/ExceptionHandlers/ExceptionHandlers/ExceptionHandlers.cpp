#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <conio.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
int				ValueToDivide=0;
//------------------------------------------------------------------------------
LONG ExceptionDump(LPEXCEPTION_POINTERS PEP)
{
	wchar_t				Buf[1024];
	wchar_t*			P;

	PEXCEPTION_RECORD	ER=PEP->ExceptionRecord;

	// Ziskam ExceptionCode.
	DWORD				ExceptionCode=ER->ExceptionCode;

	StringCchPrintf(Buf,_countof(Buf),L"Code = [%x], Address = [%p] !\n",ExceptionCode,ER->ExceptionAddress);

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

	return(EXCEPTION_EXECUTE_HANDLER);
}
//------------------------------------------------------------------------------
/*
// !!!!! Tato funkcia NEBUDE SKOMPILOVANA.
DWORD MyExceptionFilter(void)
{
	// !!! Funkciu GetExceptionCode() je mozne pouzit iba za zatvorkami __except(GetExceptionCode()), alebo v __except(...){...GetExceptionCode()...}.
	DWORD		ErrorCode=GetExceptionCode();

	if (ErrorCode==EXCEPTION_ACCESS_VIOLATION)
		wprintf_s(L"EXCEPTION_ACCESS_VIOLATION - ERROR CODE: [%x] !\n",ErrorCode);
	else
		wprintf_s(L"Some OTHER EXCEPTION - ERROR CODE: [%x] !\n",ErrorCode);
}
*/
//------------------------------------------------------------------------------
DWORD MyExceptionFilter_ContinueExecution(void)
{
	wprintf_s(L"Inside MyExceptionFilter_ContinueExecution() !\n");

	// Upravim hodnotu GLOBALNEJ PREMENNEJ a to tak, ze NEDOJDE k DELENIU 0.
	// !!!!! Oprava NEMUSI FUNGOVAT ak kompilator si hodnotu ValueToDivide nastavenu na 0 ulozi do REGISTRA a ja nastavenim na 1 zmenim iba hondotu v PAMATI, ale NIE V REGISTRY.
	ValueToDivide=1;

	// Po 'oprave' moze kod pokracovat instrukciou, ktora sposobila volanie EXCEPTION.
	return(EXCEPTION_CONTINUE_EXECUTION);
}
//------------------------------------------------------------------------------
void Level3(void)
{
	wprintf_s(L"Level3 - Before TRY !\n");

	__try
	{
		BYTE*		Temp=NULL;

		wprintf_s(L"Level3 - Before EXCEPTION !\n");

		*Temp=0;

		wprintf_s(L"Level3 - After EXCEPTION !\n");
	}
	__finally
	{
		wprintf_s(L"Level3 - Inside FINALLY !\n");
	}

	wprintf_s(L"Level3 - After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Level2(bool DoReturnInFinallyBlock)
{
	wprintf_s(L"Level2 - Before OUTER TRY !\n");

	__try
	{
		wprintf_s(L"Level2 - Inside OUTER TRY !\n");

		wprintf_s(L"Level2 - Before INNER TRY !\n");

		__try
		{
			wprintf_s(L"Level2 - Inside INNER TRY - Level3() is CALLING !\n");

			Level3();
		}
		__finally
		{
			wprintf_s(L"Level2 - Inside INNER FINALLY !\n");

			if (DoReturnInFinallyBlock==true)
			{
				wprintf_s(L"!!! Level2 - Inside INNER FINALLY - RETURN WILL BE EXECUTED !\n");

				// Generuje WARINING.
				return;
			}
		}

		wprintf_s(L"Level2 - After INNER FINALLY !\n");
	}
	__finally
	{
		wprintf_s(L"Level2 - Inside OUTER FINALLY !\n");
	}

	wprintf_s(L"Level2 - After OUTER FINALLY !\n");
}
//------------------------------------------------------------------------------
void Level1(bool DoReturnInFinallyBlock)
{
	wprintf_s(L"Level1 - Before TRY !\n");

	__try
	{
		wprintf_s(L"Level1 - Inside TRY - Level2() is CALLING !\n");

		Level2(DoReturnInFinallyBlock);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		wprintf_s(L"Level1 - Inside EXCEPT !\n");
	}

	wprintf_s(L"Level1 - After EXCEPT !\n");
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test1(void)
{
	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY !\n");
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		wprintf_s(L"Inside EXCEPT !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Test2(void)
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
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		wprintf_s(L"Inside EXCEPT !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Test3(void)
{
	// Prebehne NORMALNY GLOBAL UNWIND.
	Level1(false);
}
//------------------------------------------------------------------------------
void Test4(void)
{
	// Kedze v Level2() sa vyvola 'return', dojde k ZRUSENIU GLOBAL UNWIND.
	Level1(true);
}
//------------------------------------------------------------------------------
void Test5(void)
{
	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY 1 !\n");

		int			Result=0;
		int			SomeValue=100;

		wprintf_s(L"Dividing: [%d/%d] !\n",SomeValue,ValueToDivide);

		// Sposobi EXCEPTION, pretoze GLOBALNA premena ValueToDivide je ==0.
		Result=SomeValue/ValueToDivide;

		wprintf_s(L"DIVIDED: [%d/%d]=[%d] !\n",SomeValue,ValueToDivide,Result);

		// Tento kod sa NIKDY NEVYKONA.
		wprintf_s(L"Inside TRY 2 !\n");
	}
	__except(MyExceptionFilter_ContinueExecution())
	{
		wprintf_s(L"Inside EXCEPT !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Test6(void)
{
	wprintf_s(L"Before OUTER TRY !\n");

	__try
	{
		wprintf_s(L"Inside OUTER TRY !\n");

		wprintf_s(L"Before INNER TRY !\n");

		__try
		{
			BYTE*		Temp=NULL;

			wprintf_s(L"Inside INNER TRY - EXCEPTION will be GENERATED !\n");

			*Temp=1;
		}
		__except(EXCEPTION_CONTINUE_SEARCH)
		{
			// Tento kod sa NIKDY NEVYKONA.
			wprintf_s(L"Inside INNER EXCEPT !\n");
		}

		wprintf_s(L"After INNER TRY !\n");
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		wprintf_s(L"Inside OUTER EXCEPT !\n");
	}

	wprintf_s(L"After OUTER TRY !\n");
}
//------------------------------------------------------------------------------
void Test7(void)
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
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		DWORD		ErrorCode=GetExceptionCode();

		if (ErrorCode==EXCEPTION_ACCESS_VIOLATION)
			wprintf_s(L"EXCEPTION_ACCESS_VIOLATION - ERROR CODE: [%x] !\n",ErrorCode);
		else
			wprintf_s(L"Some OTHER EXCEPTION - ERROR CODE: [%x] !\n",ErrorCode);
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Test8(void)
{
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
	__except(ExceptionDump(GetExceptionInformation()))
	{
		wprintf_s(L"Inside EXCEPT !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Test9(void)
{
	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY 1 !\n");

		// Hodim EXCEPTION s kodom 0x1000.
		// !!! Hodnota 1. parametra by mala mat 32-bitovu strukturu rovnaku ako maju HW EXCEPTIONS.
		RaiseException(0x1000,0,0,NULL);

		// Tento kod sa NIKDY NEVYKONA.
		wprintf_s(L"Inside TRY 2 !\n");
	}
	__except(ExceptionDump(GetExceptionInformation()))
	{
		wprintf_s(L"Inside EXCEPT !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
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
	Test8();
	//Test9();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------