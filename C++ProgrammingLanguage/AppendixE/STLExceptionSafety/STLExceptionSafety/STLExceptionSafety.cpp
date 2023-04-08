//-------------------------------------------------------------------------------------------------------
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <vector>
#include <algorithm>
#include "ExceptionTestType.h"
#include "OuterClass.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	vector<CExceptionTestType>									Vector;

	try
	{
		Vector.push_back(CExceptionTestType(8));
		Vector.push_back(CExceptionTestType(6));
		Vector.push_back(CExceptionTestType(3));
		Vector.push_back(CExceptionTestType(4));

		wprintf_s(L"BEFORE SORT !\n");

		for(vector<CExceptionTestType>::iterator i=Vector.begin();i!=Vector.end();i++)
		{
			wprintf_s(L"\t%d !\n",(*i).GetValue());
		}

		// !!! Hodi EXCEPTION.
		// !!!!! Vysledkom je NEDOKONCENY SORT.
		sort(Vector.begin(),Vector.end());
	}
	catch(const wstring& E)
	{
		wprintf_s(L"EXCEPTION [%s] !\n",E.c_str());
	}

	wprintf_s(L"AFTER SORT !\n");

	for(vector<CExceptionTestType>::iterator i=Vector.begin();i!=Vector.end();i++)
	{
		wprintf_s(L"\t%d !\n",(*i).GetValue());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	vector<CExceptionTestType>									Vector;

	try
	{
		Vector.push_back(CExceptionTestType(8));
		Vector.push_back(CExceptionTestType(6));
		Vector.push_back(CExceptionTestType(55));
		Vector.push_back(CExceptionTestType(4));
	}
	catch(const wstring& E)
	{
		wprintf_s(L"EXCEPTION [%s] !\n",E.c_str());
	}

	wprintf_s(L"Number of ELEMENTS in VECTOR [%d] !\n",Vector.size());
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	vector<CExceptionTestType>									Vector1;
	vector<CExceptionTestType>									Vector2;

	try
	{
		Vector1.reserve(100);

		Vector1.push_back(CExceptionTestType(8));
		Vector1.push_back(CExceptionTestType(6));
		Vector1.push_back(CExceptionTestType(100));
		Vector1.push_back(CExceptionTestType(200));

		Vector2=Vector1;
	}
	catch(const wstring& E)
	{
		wprintf_s(L"EXCEPTION [%s] !\n",E.c_str());
	}

	wprintf_s(L"Number of ELEMENTS in VECTOR1 [%d] !\n",Vector1.size());
	wprintf_s(L"Number of ELEMENTS in VECTOR2 [%d] !\n",Vector2.size());
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	vector<CExceptionTestType>									Vector1;
	vector<CExceptionTestType>									Vector2;

	try
	{
		Vector1.reserve(100);

		Vector1.push_back(CExceptionTestType(8));
		Vector1.push_back(CExceptionTestType(6));
		Vector1.push_back(CExceptionTestType(100));
		Vector1.push_back(CExceptionTestType(200));

		// !!! Vector2 UMYSELNE ZVACSIM, aby mal VIAC ITEMS ako Vector1.
		Vector2.push_back(CExceptionTestType(1));
		Vector2.push_back(CExceptionTestType(1));
		Vector2.push_back(CExceptionTestType(1));
		Vector2.push_back(CExceptionTestType(1));
		Vector2.push_back(CExceptionTestType(1));
		Vector2.push_back(CExceptionTestType(1));
		Vector2.push_back(CExceptionTestType(1));

		// !!! Pri EXCEPTION sa Vector2 dostane do NEKONZISTENTNEHO STAVU.
		Vector2=Vector1;
	}
	catch(const wstring& E)
	{
		wprintf_s(L"EXCEPTION [%s] !\n",E.c_str());
	}

	wprintf_s(L"Number of ELEMENTS in VECTOR1 [%d] !\n",Vector1.size());
	wprintf_s(L"Number of ELEMENTS in VECTOR2 [%d] !\n",Vector2.size());

	wprintf_s(L"VECTOR2:\n");

	for(vector<CExceptionTestType>::iterator i=Vector2.begin();i!=Vector2.end();i++)
	{
		wprintf_s(L"\t%d !\n",(*i).GetValue());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	try
	{
		// EXCEPTION hodi v CONSTRUCTORE COuterClass.
		// !!!!! Vola sa DESTRUCTOR CInnerClass1 a CInnerClass2, ale NIE COuterClass.
		COuterClass												Outer(0);

		Outer.DoNothing();
	}
	catch(const wstring& E)
	{
		wprintf_s(L"EXCEPTION [%s] !\n",E.c_str());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	try
	{
		// EXCEPTION hodi v CONSTRUCTORE CInnerClass2.
		// !!!!! Vola sa DESTRUCTOR CInnerClass1, ale NIE COuterClass a CInnerClass2.
		COuterClass												Outer(2);

		Outer.DoNothing();
	}
	catch(const wstring& E)
	{
		wprintf_s(L"EXCEPTION [%s] !\n",E.c_str());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	try
	{
		// EXCEPTION hodi v CONSTRUCTORE CInnerClass1.
		// !!!!! NEVOLA sa ZIADEN DESTRUCTOR.
		COuterClass												Outer(1);

		Outer.DoNothing();
	}
	catch(const wstring& E)
	{
		wprintf_s(L"EXCEPTION [%s] !\n",E.c_str());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	vector<CExceptionTestType>									Vector;

	try
	{
		Vector.push_back(CExceptionTestType(8));
		Vector.push_back(CExceptionTestType(6));
		Vector.push_back(CExceptionTestType(4));

		wprintf_s(L"BEFORE INSERT !\n");

		for(vector<CExceptionTestType>::iterator i=Vector.begin();i!=Vector.end();i++)
		{
			wprintf_s(L"\t%d !\n",(*i).GetValue());
		}

		// !!! Hodi EXCEPTION.
		// !!!!! Vysledkom je NEKONZISTANTNY STAV, kedze novy ITEM by mal byt NA ZACIATKU.
		Vector.insert(Vector.begin(),CExceptionTestType(100));
	}
	catch(const wstring& E)
	{
		wprintf_s(L"EXCEPTION [%s] !\n",E.c_str());
	}

	wprintf_s(L"AFTER INSERT !\n");

	for(vector<CExceptionTestType>::iterator i=Vector.begin();i!=Vector.end();i++)
	{
		wprintf_s(L"\t%d !\n",(*i).GetValue());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	CExceptionTestType											Value1(100);
	CExceptionTestType											Value2(8);

	try
	{
		wprintf_s(L"Value1: [%d] !\n",Value1.GetValue());
		wprintf_s(L"Value2: [%d] !\n",Value2.GetValue());

		// !!! Hodi EXCEPTION.
		// !!!!! Vysledkom je NEKONZISTANTNY STAV hodnot Value1 a Value2.
		swap(Value1,Value2);
	}
	catch(const wstring& E)
	{
		wprintf_s(L"EXCEPTION [%s] !\n",E.c_str());
	}

	wprintf_s(L"Value1: [%d] !\n",Value1.GetValue());
	wprintf_s(L"Value2: [%d] !\n",Value2.GetValue());
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	//Test8();
	Test9();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------