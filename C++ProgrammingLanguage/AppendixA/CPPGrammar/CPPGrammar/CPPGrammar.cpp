//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <vector>
#include <list>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	int															X=1;

	wprintf_s(L"Value of X [%d] !\n",X);

	// !!! SIZEOF umoznuje brat ako argument i EXPRESSION, pricom vsak tento EXPRESSSION je vyhodnocovany v COMPILE TIME co vedie k nejednoznacnemu kodu.
	// !!!!!! OPERATOR ++ je v RUNTIME IGNOROVANY a NIE JE VYKONANY.
	sizeof(++X);

	wprintf_s(L"Value of X [%d] !\n",X);

	// !!!!!! OPERATOR ++ je v RUNTIME IGNOROVANY a NIE JE VYKONANY.
	sizeof(X++);

	wprintf_s(L"Value of X [%d] !\n",X);
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	int															SIZEOF=sizeof(3+4*sizeof('A'));

	// !!! SIZEOF umoznuje brat ako argument i INY SIZEOF co vedie k nejednoznacnemu kodu.
	wprintf_s(L"SIZEOF [%d] !\n",SIZEOF);
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	// !!! Niektore COMPILERS maju problem s DVOMA '>>'.
	vector<list<int>>											Vector;

	wprintf_s(L"SIZE [%d] !\n",Vector.size());
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//Test1();
	//Test2();
	Test3();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();
}
//-------------------------------------------------------------------------------------------------------