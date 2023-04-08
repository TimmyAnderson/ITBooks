#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
void Test1(_TCHAR* Env[])
{
	wchar_t**	Pos=Env;

	while((*Pos)!=NULL)
	{
		wprintf_s(L"[%s] !\n",*Pos);
		Pos++;
	}
}
//------------------------------------------------------------------------------
void Test2()
{
	// Tento retazec je ukonceny DVOMA '\0'.
	wchar_t*		Strings=GetEnvironmentStrings();
	wchar_t*		Pos=Strings;

	while((*Pos)!=NULL)
	{
		wprintf(L"[%s] !\n",Pos);

		int			Length=wcslen(Pos);

		Pos+=(Length+1);
	}

	FreeEnvironmentStrings(Strings);
}
//------------------------------------------------------------------------------
void Test3()
{
	wchar_t			EV1[100];
	wchar_t			EV2[100];
		
	GetEnvironmentVariable(L"SystemDrive",EV1,_countof(EV1));

	wprintf_s(L"SystemDrive: [%s] !\n",EV1);

	SetEnvironmentVariable(L"SystemDrive",L"D:");

	GetEnvironmentVariable(L"SystemDrive",EV2,_countof(EV2));

	wprintf_s(L"SystemDrive: [%s] !\n",EV2);
}
//------------------------------------------------------------------------------
void Test4()
{
	wchar_t			In[]=L"%OS%";
	wchar_t			Out[100];

	ExpandEnvironmentStrings(In,Out,_countof(Out));

	wprintf(L"In: [%s] !\n",In);
	wprintf(L"Out: [%s] !\n",Out);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[], _TCHAR* env[])
{
	SafeMain();
	
	//Test1(env);
	//Test2();
	//Test3();
	Test4();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------