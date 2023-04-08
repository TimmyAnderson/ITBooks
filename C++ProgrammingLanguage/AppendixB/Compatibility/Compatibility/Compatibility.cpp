//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include "Template.h"
#include "Template.cpp"
//-------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
#pragma message ("This is C++ !")
#else
#pragma message ("This is NOT C++ !")
#endif
//-------------------------------------------------------------------------------------------------------
// !!! Toto je vraj DEPRECATED. Visual C++ to vyzera, ze akceptuje.
static int														Variable;
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	CTemplate<wstring>											Template(L"Timmy Anderson");

	wprintf_s(L"Value is [%s] !\n",Template.GetValue().c_str());

	int															Out1;
	wstring														Out2;

	Out1=Template.GetValues<int>(12,&Out2);

	wprintf_s(L"Value1 is [%d] and Value2 is [%s] !\n",Out1,Out2.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	for(int i=0;i<10;i++)
	{
		wprintf_s(L"In SCOPE [%d] !\n",i);
	}

	// !!! Novsie implementacie C++ toto NEPRELOZIA.
	//wprintf_s(L"Out of SCOPE [%d] !\n",i);
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	while(true)
	{
		// !!! NEHODI EXCEPTION, ale vracia NULL.
		void*													Temp=new (nothrow) char[100000000];

		if (Temp!=NULL)
		{
			wprintf_s(L"Memory ALLOCATED !\n");
		}
		else
		{
			wprintf_s(L"OUT OF MEMORY !\n");
			break;
		}
	}
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

	return(0);
}
//-------------------------------------------------------------------------------------------------------