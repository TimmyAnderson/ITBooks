//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
//-------------------------------------------------------------------------------------------------------
void StandardFunction(int Param1, int Param2)
{
	wprintf_s(L"StandardFunction - Param1: [%d], Param2: [%d] !\n",Param1,Param2);
}
//-------------------------------------------------------------------------------------------------------
void __stdcall StdcallFunction(int Param1, int Param2)
{
	wprintf_s(L"StdCallFunction - Param1: [%d], Param2: [%d] !\n",Param1,Param2);
}
//-------------------------------------------------------------------------------------------------------
void __cdecl CdeclFunction(int Param1, int Param2)
{
	wprintf_s(L"CdeclFunction - Param1: [%d], Param2: [%d] !\n",Param1,Param2);
}
//-------------------------------------------------------------------------------------------------------
void __fastcall FastcallFunction(int Param1, int Param2)
{
	wprintf_s(L"FastcallFunction - Param1: [%d], Param2: [%d] !\n",Param1,Param2);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	int						Value1=10;

	StandardFunction(++Value1,Value1);

	int						Value2=10;

	StdcallFunction(++Value2,Value2);

	int						Value3=10;

	CdeclFunction(++Value3,Value3);

	int						Value4=10;

	FastcallFunction(++Value4,Value4);

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------