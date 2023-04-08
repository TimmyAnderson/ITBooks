//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cwctype>
//-------------------------------------------------------------------------------------------------------
#pragma warning(disable : 4996)
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	wprintf_s(L"CHAR - LENGTH: [%d] !\n",char_traits<char>::length("Timmy Anderson"));
	wprintf_s(L"WCHAR - LENGTH: [%d] !\n",char_traits<wchar_t>::length(L"Timmy Anderson"));

	wprintf_s(L"WCHAR - COMPARE: [%d] !\n",char_traits<wchar_t>::compare(L"Timmy Anderson",L"Timmy Anderson",char_traits<wchar_t>::length(L"Timmy Anderson")));

	wchar_t														Buffer[100];

	// !!! Musim prihodit 1 znak k dlzke, kedze '\0' sa automaticky NEKOPIRUJE.
	char_traits<wchar_t>::copy(Buffer,L"Timmy Anderson",char_traits<wchar_t>::length(L"Timmy Anderson")+1);

	wprintf_s(L"WCHAR - COPIED STRING: [%s] !\n",Buffer);
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	wstring														Text=L"Timmy";

	wprintf_s(L"TEXT:\n");

	for(wstring::iterator i=Text.begin();i!=Text.end();i++)
	{
		wprintf_s(L"CHAR: [%c] !\n",*i);
	}

	wprintf_s(L"\n");

	wprintf_s(L"TEXT-BACKWARD:\n");

	for(wstring::reverse_iterator i=Text.rbegin();i!=Text.rend();i++)
	{
		wprintf_s(L"CHAR: [%c] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	wstring														Text=L"Timmy";

	wprintf_s(L"OPERTOR[]:\n");

	for(int i=0;i<Text.length();i++)
	{
		wprintf_s(L"CHAR: [%c] !\n",Text[i]);
	}

	wprintf_s(L"\n");

	wprintf_s(L"METHOD at():\n");

	for(int i=0;i<Text.length();i++)
	{
		wprintf_s(L"CHAR: [%c] !\n",Text.at(i));
	}

	wprintf_s(L"\n");

	wprintf_s(L"METHOD at(1000):\n");

	try
	{
		// !!! Hodi EXCEPTION.
		wprintf_s(L"CHAR[1000]: [%c] !\n",Text.at(1000));
	}
	catch(const out_of_range& E)
	{
		printf_s("EXCEPTION: [%s] !\n",E.what());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	wstringstream												StringStream;

	// !!! Pomcou 'wstringstream' je mozne vykonat KONVERZIU INT na STRING.
	StringStream << 123;

	wstring														String=StringStream.str();

	wprintf_s(L"NUMBER: [%s] !\n",String.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	try
	{
		// !!! Vytvorim PRILIS DLHY STRING.
		wstring													Text(wstring::npos,'A');
		
		wprintf_s(L"LENGTH: [%s] !\n",Text.c_str());
	}
	catch(const length_error& E)
	{
		printf_s("EXCEPTION: [%s] !\n",E.what());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	wstring														Text(L"Timmy Anderson");

	wchar_t														Buffer[100];

	Text.copy(Buffer,Text.length(),0);

	// !!! Kedze copy() NEPRIDAVA na koniec NULL TERMINATOR, tak je ho nutne pridat.
	Buffer[Text.length()]='\0';

	wprintf_s(L"Method c_str(): [%s] !\n",Text.c_str());

	wprintf_s(L"Method copy(): [%s] !\n",Buffer);
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	wstring														Text1(L"Timmy Anderson");
	wstring														Text2(L"Jenny Thompson");

	if (Text1<Text2)
	{
		wprintf_s(L"Text1<Text2 !\n");
	}
	else if (Text1>Text2)
	{
		wprintf_s(L"Text1>Text2 !\n");
	}
	else
	{
		wprintf_s(L"Text1==Text2 !\n");
	}

	wprintf_s(L"Text1.compare(Text2): [%d] !\n",Text1.compare(Text2));
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	wstring														Text(L"Timmy Anderson");

	Text.insert(0,L"First name: ");
	Text.insert(17,L", Last name:");

	wprintf_s(L"Text: [%s] !\n",Text.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	wstring														Text;
		
	Text=L"Timmy";
	Text+=L" ";
	Text.append(L"Anderson");

	wprintf_s(L"Text: [%s] !\n",Text.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	wstring														Text(L"Tim Timothy Timmy");

	size_t														Index1=Text.find(L"Tim");
	size_t														Index2=Text.find_first_not_of(L"Tim");
	size_t														Index3=Text.find_last_of(L"Tim");

	wprintf_s(L"Index1: [%s] !\n",&Text[Index1]);
	wprintf_s(L"Index2: [%s] !\n",&Text[Index2]);
	wprintf_s(L"Index3: [%s] !\n",&Text[Index3]);

	size_t														Index4=Text.find_last_of(L"XXX");

	if (Index4!=wstring::npos)
	{
		wprintf_s(L"Index4: [%s] !\n",&Text[Index4]);
	}
	else
	{
		wprintf_s(L"STRING WAS NOT FOUND !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	wstring														Text(L"Timmy Anderson");
	wstring::iterator											Begin=Text.begin();
	wstring::iterator											End=Text.begin()+5;
	
	Text.replace(Begin,End,L"Timothy");

	wprintf_s(L"Text: [%s] !\n",Text.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	wstring														Text(L"Timmy Anderson");
	wstring::iterator											Begin=Text.begin();
	wstring::iterator											End=Text.begin()+6;

	Text.erase(Begin,End);

	wprintf_s(L"Text: [%s] !\n",Text.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	wstring														Text(L"Timmy Anderson");

	wstring														Text1=Text.substr(0,5);
	wstring														Text2=Text.substr(6);

	wprintf_s(L"Text1: [%s] !\n",Text1.c_str());
	wprintf_s(L"Text2: [%s] !\n",Text2.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test14(void)
{
	wcout << "My name is Timmy Anderson !\n";
}
//-------------------------------------------------------------------------------------------------------
void Test15(void)
{
	wstring														Text1(L"Timmy Anderson");
	wstring														Text2(L"Jenny Thompson");

	wprintf_s(L"Text1: [%s] !\n",Text1.c_str());
	wprintf_s(L"Text2: [%s] !\n",Text2.c_str());

	Text1.swap(Text2);

	wprintf_s(L"Text1: [%s] !\n",Text1.c_str());
	wprintf_s(L"Text2: [%s] !\n",Text2.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test16(void)
{
	wprintf_s(L"Result isalpha('A'): [%d] !\n",isalpha(L'A'));
	wprintf_s(L"Result isalpha('1'): [%d] !\n",isalpha(L'1'));
	wprintf_s(L"Result isdigit('A'): [%d] !\n",isdigit(L'A'));
	wprintf_s(L"Result isdigit('1'): [%d] !\n",isdigit(L'1'));
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
	//Test9();
	//Test10();
	//Test11();
	//Test12();
	//Test13();
	//Test14();
	//Test15();
	Test16();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------