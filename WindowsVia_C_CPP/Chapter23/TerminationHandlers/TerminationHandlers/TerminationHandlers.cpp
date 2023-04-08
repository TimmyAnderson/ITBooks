#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <conio.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
// Ked spravim RETURN z __finally - hodi WARNING 4532.
//#pragma warning(disable : 4532)
//------------------------------------------------------------------------------
DWORD FilterFunction(void)
{
	return(EXCEPTION_EXECUTE_HANDLER);
}
//------------------------------------------------------------------------------
void Test1(void)
{
	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY !\n");
	}
	__finally
	{
		wprintf_s(L"Inside FINALLY !\n");
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

		return;
	}
	__finally
	{
		wprintf_s(L"Inside FINALLY !\n");
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

		goto Exit;
	}
	__finally
	{
		wprintf_s(L"Inside FINALLY !\n");
	}

	wprintf_s(L"After FINALLY !\n");

Exit:
	wprintf_s(L"[Exit] identifier !\n");
}
//------------------------------------------------------------------------------
void Test4(void)
{
	wprintf_s(L"START !\n");

	int				Counter=0;

	while(Counter<10)
	{
		Counter++;

		wprintf_s(L"Before TRY [%d] !\n",Counter);

		__try
		{
			wprintf_s(L"Inside TRY [%d] !\n",Counter);

			if (Counter==2)
			{
				wprintf_s(L"CONTINUE [%d] !\n",Counter);
				continue;
			}

			if (Counter==3)
			{
				wprintf_s(L"BREAK [%d] !\n",Counter);
				break;
			}
		}
		__finally
		{
			wprintf_s(L"Inside FINALLY [%d] !\n",Counter);
		}

		wprintf_s(L"After FINALLY [%d] !\n",Counter);
	}

	wprintf_s(L"END !\n");
}
//------------------------------------------------------------------------------
// Testujem aka bude skutocna navratova hodnota.
wchar_t* Tester5(void)
{
	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY !\n");

		// Vraciam navratovu hodnotu.
		return(L"Return in TRY");
	}
	__finally
	{
		wprintf_s(L"Inside FINALLY !\n");

		// !!! Vo __finally vratim INU NAVRATOVU HODNOTU.
		// !!!!! Pri pokuse o pouzitie 'return' vo '__finally' bloku HADZE COMPILATOR WARNING 4532.
		return(L"Return in FINALLY");
	}

	wprintf_s(L"After FINALLY !\n");
}
//------------------------------------------------------------------------------
void Test5(void)
{
	wchar_t*		Ret=Tester5();

	wprintf_s(L"Tester5() returned [%s] !\n",Ret);
}
//------------------------------------------------------------------------------
void Test6(void)
{
	wprintf_s(L"Before TRY !\n");

	__try
	{
		wprintf_s(L"Inside TRY !\n");

		// Ukoncim thread.
		ExitThread(0);
	}
	__finally
	{
		// !!!!! Teraz sa '__finally' NEVOLA.
		wprintf_s(L"Inside FINALLY !\n");
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
	Test6();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------