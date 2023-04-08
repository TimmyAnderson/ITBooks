#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <conio.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
DWORD FilterFunction(void)
{
	return(EXCEPTION_EXECUTE_HANDLER);
}
//------------------------------------------------------------------------------
void ExceptionRaiser(void)
{
	wprintf_s(L"Before RaiseException() !\n");

	RaiseException(0,0,0,NULL);

	wprintf_s(L"After RaiseException() !\n");
}
//------------------------------------------------------------------------------
void Test1(void)
{
	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY !\n");

		// NESPRAVI UNWIND.
	}
	__finally
	{
		wprintf_s(L"Inside FINALLY !\n");

		if (AbnormalTermination()==FALSE)
			wprintf_s(L"!!! Test1() - NO UNWIND !\n");
		else
			wprintf_s(L"!!! Test1() - UNWIND !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Test2(void)
{
	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY !\n");

		// !!! SPRAVI UNWIND.
		ExceptionRaiser();
	}
	__finally
	{
		wprintf_s(L"Inside FINALLY !\n");

		if (AbnormalTermination()==FALSE)
			wprintf_s(L"!!! Test2() - NO UNWIND !\n");
		else
			wprintf_s(L"!!! Test2() - UNWIND !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Test3(void)
{
	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY !\n");

		// !!! SPRAVI UNWIND.
		return;
	}
	__finally
	{
		wprintf_s(L"Inside FINALLY !\n");

		if (AbnormalTermination()==FALSE)
			wprintf_s(L"!!! Test3() - NO UNWIND !\n");
		else
			wprintf_s(L"!!! Test3() - UNWIND !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Test4(void)
{
	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY !\n");

		// NESPRAVI UNWIND.
		__leave;
	}
	__finally
	{
		wprintf_s(L"Inside FINALLY !\n");

		if (AbnormalTermination()==FALSE)
			wprintf_s(L"!!! Test4() - NO UNWIND !\n");
		else
			wprintf_s(L"!!! Test4() - UNWIND !\n");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Tester(int FunctionNumber)
{
	__try
	{
		wprintf_s(L"Tester() TRY !\n");

		if (FunctionNumber==1)
			Test1();
		else if (FunctionNumber==2)
			Test2();
		else if (FunctionNumber==3)
			Test3();
		else if (FunctionNumber==4)
			Test4();
	}
	__except(FilterFunction())
	{
		wprintf_s(L"Tester() EXCEPT !\n");
	}
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	//Tester(1);
	//Tester(2);
	//Tester(3);
	Tester(4);

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------