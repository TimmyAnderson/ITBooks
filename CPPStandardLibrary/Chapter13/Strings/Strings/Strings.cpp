//-----------------------------------------------------------------------------
#define _SCL_SECURE_NO_WARNINGS  
//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <sstream>
#include <string>
#include "MyDebug.h"
#include "CCustomCodeConverter.h"
#include "CCaseInsensitiveCharacterTraits.h"
#include "CStringAllocator.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#undef min
#undef max
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRangeCheck(void)
{
	PrintLineSeparator();

	wstring														Text1=L"ABC";

	wcout << L"TEXT 1 [" << Text1 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TEXT 1 [0] [" << int(Text1[0]) << L"] !" << endl;
	wcout << L"TEXT 1 [1] [" << int(Text1[1]) << L"] !" << endl;
	wcout << L"TEXT 1 [2] [" << int(Text1[2]) << L"] !" << endl;

	// !!! Od C++11 je pristup k [INDEX==SIZE] VALIDNY a vysledok je CHARACTER '\0'.
	wcout << L"TEXT 1 [3] [" << int(Text1[3]) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TEXT 1 at(0) [" << int(Text1.at(0)) << L"] !" << endl;
	wcout << L"TEXT 1 at(1) [" << int(Text1.at(1)) << L"] !" << endl;
	wcout << L"TEXT 1 at(2) [" << int(Text1.at(2)) << L"] !" << endl;

	try
	{
		// !!! METHOD at() NEUMOZNUJE pristup k CHARACTER s [INDEX==SIZE].
		wcout << L"TEXT 1 at(3) [" << int(Text1.at(3)) << L"] !" << endl;
	}
	catch(const out_of_range& E)
	{
		wcout << L"TEXT 1 at(3) EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();

	wstring														Text2;

	Text2.resize(3);

	Text2[0]=L'A';
	Text2[1]=L'B';
	Text2[2]=L'C';

	wcout << L"TEXT 2 [" << Text2 << L"] !" << endl;
	wcout << L"TEXT 2 CAPACITY [" << Text2.capacity() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TEXT 2 [0] [" << int(Text2[0]) << L"] !" << endl;
	wcout << L"TEXT 2 [1] [" << int(Text2[1]) << L"] !" << endl;
	wcout << L"TEXT 2 [2] [" << int(Text2[2]) << L"] !" << endl;

	// !!! Od C++11 je pristup k [INDEX==SIZE] VALIDNY a vysledok je CHARACTER '\0'.
	wcout << L"TEXT 2 [3] [" << int(Text2[3]) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TEXT 2 at(0) [" << int(Text2.at(0)) << L"] !" << endl;
	wcout << L"TEXT 2 at(1) [" << int(Text2.at(1)) << L"] !" << endl;
	wcout << L"TEXT 2 at(2) [" << int(Text2.at(2)) << L"] !" << endl;

	try
	{
		// !!! METHOD at() NEUMOZNUJE pristup k CHARACTER s [INDEX==SIZE].
		wcout << L"TEXT 2 at(3) [" << int(Text2.at(3)) << L"] !" << endl;
	}
	catch(const out_of_range& E)
	{
		wcout << L"TEXT 2 at(3) EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifndef _MSC_VER
// !!! Tento CODE vdaka BUG vo VISUAL STUDIO 2017 NEMOZE byt COMPILED.
wstring ConvertUnicode16StringToWideString(const u16string& Value)
{
	using														TConverter=wstring_convert<CCustomCodeConverter<char16_t,char,mbstate_t>,char16_t>;

	TConverter													Converter;

	string														RawString=Converter.to_bytes(Value);
	wstring														ConvertedValue=ConvertStringToWideString(RawString);

	return(ConvertedValue);
}
//-----------------------------------------------------------------------------
// !!! Tento CODE vdaka BUG vo VISUAL STUDIO 2017 NEMOZE byt COMPILED.
wstring ConvertUnicode32StringToWideString(const u32string& Value)
{
	using														TConverter=wstring_convert<CCustomCodeConverter<char32_t,char,mbstate_t>,char32_t>;

	TConverter													Converter;

	string														RawString=Converter.to_bytes(Value);
	wstring														ConvertedValue=ConvertStringToWideString(RawString);

	return(ConvertedValue);
}
#endif
//-----------------------------------------------------------------------------
void TestVariousStrings(void)
{
	PrintLineSeparator();

	string														String({"Timmy Anderson"});
	wstring														WideString({L"Timmy Anderson"});
	u16string													Unicode16String({u"Timmy Anderson"});
	u32string													Unicode32String({U"Timmy Anderson"});

	wcout << L"STRING [" << ConvertStringToWideString(String) << L"] !" << endl;
	wcout << L"WIDE STRING [" << WideString << L"] !" << endl;
#ifndef _MSC_VER
	wcout << L"UNICODE16 STRING [" << ConvertUnicode16StringToWideString(Unicode16String) << L"] !" << endl;
	wcout << L"UNICODE32 STRING [" << ConvertUnicode32StringToWideString(Unicode32String) << L"] !" << endl;
#endif

	PrintLineSeparator();

	wcout << L"STRING LENGTH [" << String.length() << L"] !" << endl;
	wcout << L"WIDE STRING LENGTH [" << WideString.length() << L"] !" << endl;
	wcout << L"UNICODE16 STRING LENGTH [" << Unicode16String.length() << L"] !" << endl;
	wcout << L"UNICODE32 STRING LENGTH [" << Unicode32String.length() << L"] !" << endl;
	
	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCharacterTraits(void)
{
	PrintLineSeparator();

	char_traits<wchar_t>										CharTraits;
	wchar_t														String1[]{L"AAA"};
	wchar_t														String2[]{L"BBB"};
	wchar_t														String3[]{L"AAB"};
	wchar_t														String4[]{L"Timmy Anderson"};

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;
	wcout << L"STRING 2 [" << String2 << L"] !" << endl;
	wcout << L"STRING 3 [" << String3 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"COMPARE(STRING 1,STRING 1) [" << CharTraits.compare(String1,String1,sizeof(String1)/sizeof(wchar_t)) << L"] !" << endl;
	wcout << L"COMPARE(STRING 1,STRING 2) [" << CharTraits.compare(String1,String2,min(sizeof(String1),sizeof(String2)/sizeof(wchar_t))) << L"] !" << endl;
	wcout << L"COMPARE(STRING 2,STRING 1) [" << CharTraits.compare(String2,String1,min(sizeof(String2),sizeof(String1)/sizeof(wchar_t))) << L"] !" << endl;
	wcout << L"COMPARE(STRING 1,STRING 3) [" << CharTraits.compare(String1,String3,min(sizeof(String1),sizeof(String3)/sizeof(wchar_t))) << L"] !" << endl;
	wcout << L"COMPARE(STRING 3,STRING 1) [" << CharTraits.compare(String3,String1,min(sizeof(String3),sizeof(String1)/sizeof(wchar_t))) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"STRING 4 [" << String3 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"LENGTH(STRING 4) [" << CharTraits.length(String4) << L"] !" << endl;

	PrintLineSeparator();
	
	wcout << L"TO_INT(A) [" << CharTraits.to_int_type('A') << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"EOF [" << CharTraits.eof() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNullTerminatorCharacter(void)
{
	PrintLineSeparator();

	wstring														String1(L"Timmy Anderson");
	// !!! NULL TERMINATOR CHARACTER sa APLIKUJE, pretoze inicializacny STRING je C-STRING.
	wstring														String2(L"Timmy\0 Anderson");
	// !!! NULL TERMINATOR CHARACTER sa APLIKUJE, pretoze inicializacny STRING je C-STRING.
	wstring														String3(L"Timmy\0 Anderson",0,15);
	// !!!!! STRING bude obsahovat 10 NULL TERMINATOR CHARACTERS, pretoze do STRING JE mozne ulozit NULL TERMINATOR CHARACTERS.
	wstring														String4(10,L'\0');
	// !!! NULL TERMINATOR CHARACTER sa NEAPLIKUJE (neznaci KONIEC STRING), pretoze sa pouziva INITIALIZER LIST namiesto C-STRING.
	wstring														String5({L'T',L'i',L'm',L'm',L'y',L'\0',L' ',L'A',L'n',L'd',L'e',L'r',L's',L'o',L'n'});

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;
	wcout << L"STRING 1 LENGTH [" << String1.length() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;
	wcout << L"STRING 2 LENGTH [" << String2.length() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"STRING 3 [" << String3 << L"] !" << endl;
	wcout << L"STRING 3 LENGTH [" << String3.length() << L"] !" << endl;

	PrintLineSeparator();

	// !!! WINDOWS namiesto NULL TERMINATOR CHARACTERS vypise MEDZERY, zatial co LINUX nevypise nic a STRING ma prazdny obsah, aj ked dlzka je 10.
	wcout << L"STRING 4 [" << String4 << L"] !" << endl;
	wcout << L"STRING 4 LENGTH [" << String4.length() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"STRING 5 [" << String5 << L"] !" << endl;
	wcout << L"STRING 5 LENGTH [" << String5.length() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConstructors(void)
{
	PrintLineSeparator();

	wstring														String1(L"Timmy Anderson");
	wstring														String2(L"Timmy Anderson",0,10);
	wstring														String3(10,L'Z');
	wstring														String4({L'A',L'B',L'C'});
	wstring														String5(String1.cbegin()+4,String1.cend());
	// Pouzije sa MOVE CONSTRUCTOR.
	wstring														String6(wstring(L"QWERTY"));

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;
	wcout << L"STRING 2 [" << String2 << L"] !" << endl;
	wcout << L"STRING 3 [" << String3 << L"] !" << endl;
	wcout << L"STRING 4 [" << String4 << L"] !" << endl;
	wcout << L"STRING 5 [" << String5 << L"] !" << endl;
	wcout << L"STRING 6 [" << String6 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDataAndCStr(void)
{
	PrintLineSeparator();

	wstring														String1(L"Timmy Anderson");
	wstring														String2({L'T',L'i',L'm',L'm',L'y',L'\0',L' ',L'A',L'n',L'd',L'e',L'r',L's',L'o',L'n'});

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;
	wcout << L"STRING 1 DATA() [" << String1.data() << L"] !" << endl;
	wcout << L"STRING 1 C_STR() [" << String1.c_str() << L"] !" << endl;
	wcout << L"STRING 1 LENGTH [" << String1.length() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Vypise CELY STRING.
	wcout << L"STRING 2 [" << String2 << L"] !" << endl;
	// !!! Vypise STRING iba po 1. vyskyt NULL TERMINATOR CHARACTER.
	wcout << L"STRING 2 DATA() [" << String2.data() << L"] !" << endl;
	// !!! Vypise STRING iba po 1. vyskyt NULL TERMINATOR CHARACTER.
	wcout << L"STRING 2 C_STR() [" << String2.c_str() << L"] !" << endl;
	wcout << L"STRING 2 LENGTH [" << String2.length() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCopy(void)
{
	PrintLineSeparator();

	wstring														String1(L"Timmy Anderson");
	wstring														String2({L'T',L'i',L'm',L'm',L'y',L'\0',L' ',L'A',L'n',L'd',L'e',L'r',L's',L'o',L'n'});

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;
	wcout << L"STRING 1 LENGTH [" << String1.length() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;
	wcout << L"STRING 2 LENGTH [" << String2.length() << L"] !" << endl;

	PrintLineSeparator();

	wchar_t														Buffer1[100];
	size_t														Result1=String1.copy(Buffer1,10,2);

	// !!! Kedze pri pouziti METHOD COPY sa NEPRIDAVA na koniec NULL TERMINATOR CHARACTER, je ho nutne doplnit EXPLICITNE.
	Buffer1[Result1]='\0';

	wcout << L"BUFFER 1 [" << Buffer1 << L"] !" << endl;
	wcout << L"RESULT 1 [" << Result1 << L"] !" << endl;

	PrintLineSeparator();

	wchar_t														Buffer2[100];
	size_t														Result2=String2.copy(Buffer2,10,2);

	// !!! Kedze pri pouziti METHOD COPY sa NEPRIDAVA na koniec NULL TERMINATOR CHARACTER, je ho nutne doplnit EXPLICITNE.
	Buffer2[Result2]='\0';

	wcout << L"BUFFER 2 [" << Buffer2 << L"] !" << endl;
	wcout << L"RESULT 2 [" << Result2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSize(void)
{
	PrintLineSeparator();

	wstring														String(L"Timmy Anderson");

	wcout << L"STRING [" << String << L"] !" << endl;
	wcout << L"SIZE [" << String.size() << L"] !" << endl;
	wcout << L"MAX SIZE [" << String.max_size() << L"] !" << endl;
	wcout << L"EMPTY [" << String.empty() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCapacity(void)
{
	PrintLineSeparator();

	wstring														String;

	wcout << L"STRING [" << String << L"] !" << endl;
	wcout << L"STRING CAPACITY [" << String.capacity() << L"] !" << endl;

	PrintLineSeparator();

	String=L"Timmy Anderson !!!";

	wcout << L"STRING [" << String << L"] !" << endl;
	wcout << L"STRING CAPACITY [" << String.capacity() << L"] !" << endl;

	PrintLineSeparator();

	String.reserve(50);

	wcout << L"STRING CAPACITY [" << String.capacity() << L"] !" << endl;

	PrintLineSeparator();

	String.shrink_to_fit();

	wcout << L"STRING CAPACITY [" << String.capacity() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAtAndOperatorSubscript(void)
{
	PrintLineSeparator();

	wstring														Text1=L"ABC";

	wcout << L"TEXT 1 [" << Text1 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TEXT 1 [0] [" << int(Text1[0]) << L"] !" << endl;
	wcout << L"TEXT 1 [1] [" << int(Text1[1]) << L"] !" << endl;
	wcout << L"TEXT 1 [2] [" << int(Text1[2]) << L"] !" << endl;

	// !!! Od C++11 je pristup k [INDEX==SIZE] VALIDNY a vysledok je CHARACTER '\0'.
	wcout << L"TEXT 1 [3] [" << int(Text1[3]) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TEXT 1 at(0) [" << int(Text1.at(0)) << L"] !" << endl;
	wcout << L"TEXT 1 at(1) [" << int(Text1.at(1)) << L"] !" << endl;
	wcout << L"TEXT 1 at(2) [" << int(Text1.at(2)) << L"] !" << endl;

	try
	{
		// !!! METHOD at() NEUMOZNUJE pristup k CHARACTER s [INDEX==SIZE].
		wcout << L"TEXT 1 at(3) [" << int(Text1.at(3)) << L"] !" << endl;
	}
	catch(const out_of_range& E)
	{
		wcout << L"TEXT 1 at(3) EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! OPERATOR[] je mozne pouzit aj na zapis CHARACTERS.
	Text1[1]=L'!';

	wcout << L"TEXT 1 [" << Text1 << L"] !" << endl;

	PrintLineSeparator();

	wstring														Text2;

	Text2.resize(3);

	Text2[0]=L'A';
	Text2[1]=L'B';
	Text2[2]=L'C';

	wcout << L"TEXT 2 [" << Text2 << L"] !" << endl;
	wcout << L"TEXT 2 CAPACITY [" << Text2.capacity() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TEXT 2 [0] [" << int(Text2[0]) << L"] !" << endl;
	wcout << L"TEXT 2 [1] [" << int(Text2[1]) << L"] !" << endl;
	wcout << L"TEXT 2 [2] [" << int(Text2[2]) << L"] !" << endl;

	// !!! Od C++11 je pristup k [INDEX==SIZE] VALIDNY a vysledok je CHARACTER '\0'.
	wcout << L"TEXT 2 [3] [" << int(Text2[3]) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TEXT 2 at(0) [" << int(Text2.at(0)) << L"] !" << endl;
	wcout << L"TEXT 2 at(1) [" << int(Text2.at(1)) << L"] !" << endl;
	wcout << L"TEXT 2 at(2) [" << int(Text2.at(2)) << L"] !" << endl;

	try
	{
		// !!! METHOD at() NEUMOZNUJE pristup k CHARACTER s [INDEX==SIZE].
		wcout << L"TEXT 2 at(3) [" << int(Text2.at(3)) << L"] !" << endl;
	}
	catch(const out_of_range& E)
	{
		wcout << L"TEXT 2 at(3) EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! METHOD at() je mozne pouzit aj na zapis CHARACTERS.
	Text2.at(1)=L'!';

	wcout << L"TEXT 2 [" << Text2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFrontBack(void)
{
	PrintLineSeparator();

	wstring														String(L"Timmy Anderson");

	wcout << L"STRING [" << String << L"] !" << endl;
	wcout << L"STRING FRONT [" << String.front() << L"] !" << endl;
	wcout << L"STRING BACK [" << String.back() << L"] !" << endl;

	PrintLineSeparator();

	// !!! METHOD front() je mozne pouzit aj na zapis CHARACTERS.
	String.front()=L'!';

	// !!! METHOD back() je mozne pouzit aj na zapis CHARACTERS.
	String.back()=L'.';

	wcout << L"STRING [" << String << L"] !" << endl;
	wcout << L"STRING FRONT [" << String.front() << L"] !" << endl;
	wcout << L"STRING BACK [" << String.back() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCompare(void)
{
	PrintLineSeparator();

	wstring														String1(L"AAA");
	wstring														String2(L"BBB");
	wstring														String3(L"AAB");

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;
	wcout << L"STRING 2 [" << String2 << L"] !" << endl;
	wcout << L"STRING 3 [" << String3 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"COMPARE(STRING 1,STRING 1) [" << String1.compare(String1) << L"] !" << endl;
	wcout << L"COMPARE(STRING 1,STRING 2) [" << String1.compare(String2) << L"] !" << endl;
	wcout << L"COMPARE(STRING 2,STRING 1) [" << String2.compare(String1) << L"] !" << endl;
	wcout << L"COMPARE(STRING 1,STRING 3) [" << String1.compare(String3) << L"] !" << endl;
	wcout << L"COMPARE(STRING 3,STRING 1) [" << String3.compare(String1) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestComparisonOperators(void)
{
	PrintLineSeparator();

	wstring														String1(L"AAA");
	wstring														String2(L"BBB");

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;
	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"OPERATOR== [" << ((String1==String2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR!= [" << ((String1!=String2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR< [" << ((String1<String2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR<= [" << ((String1<=String2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR>= [" << ((String1>=String2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR> [" << ((String1>String2) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOperatorAssignment(void)
{
	PrintLineSeparator();

	wstring														String(L"AAA");
	wstring														NewString(L"BBB");

	wcout << L"STRING [" << String << L"] !" << endl;

	String=NewString;

	wcout << L"STRING [" << String << L"] !" << endl;

	String=L"QQQQQ";

	wcout << L"STRING [" << String << L"] !" << endl;

	// !!! Priradi sa 1 CHARACTER.
	String=L'W';

	wcout << L"STRING [" << String << L"] !" << endl;

	String={L'X',L'Y',L'Z'};

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAssign(void)
{
	PrintLineSeparator();

	wstring														String(L"AAA");
	wstring														NewString(L"BBBCCCDDD");

	wcout << L"STRING [" << String << L"] !" << endl;

	String.assign(NewString);

	wcout << L"STRING [" << String << L"] !" << endl;

	String.assign(L"Some C-STRING !");

	wcout << L"STRING [" << String << L"] !" << endl;

	String.assign(L"Some C-STRING !",3,5);

	wcout << L"STRING [" << String << L"] !" << endl;

	String.assign(NewString.cbegin()+3,NewString.cend()-3);

	wcout << L"STRING [" << String << L"] !" << endl;

	String.assign(10,L'?');

	wcout << L"STRING [" << String << L"] !" << endl;

	String.assign({L'X',L'Y',L'Z'});

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSwap(void)
{
	PrintLineSeparator();

	wstring														String1(L"AAA");
	wstring														String2(L"BBBCCCDDD");

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;
	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	PrintLineSeparator();

	String1.swap(String2);

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;
	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	PrintLineSeparator();

	swap(String1,String2);

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;
	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestClear(void)
{
	PrintLineSeparator();

	wstring														String(L"AAA");

	wcout << L"STRING [" << String << L"] !" << endl;
	wcout << L"CAPACITY [" << String.capacity() << L"] !" << endl;

	PrintLineSeparator();

	String.clear();

	wcout << L"STRING [" << String << L"] !" << endl;
	wcout << L"CAPACITY [" << String.capacity() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInsert(void)
{
	PrintLineSeparator();

	wstring														String(L"AAA");

	wcout << L"STRING [" << String << L"] !" << endl;

	String.insert(2,L"CC");

	wcout << L"STRING [" << String << L"] !" << endl;

	String.insert(2,L"123456",2,3);

	wcout << L"STRING [" << String << L"] !" << endl;

	String.insert(2,L"123456",2);

	wcout << L"STRING [" << String << L"] !" << endl;

	String.insert(2,3,'!');

	wcout << L"STRING [" << String << L"] !" << endl;

	String.insert(2,wstring(L"123456"),2,3);

	wcout << L"STRING [" << String << L"] !" << endl;

	String.insert(2,wstring(L"QWE"));

	wcout << L"STRING [" << String << L"] !" << endl;

#ifdef _MSC_VER
	PrintLineSeparator();

	wstring::iterator											Result1=String.insert(String.cbegin()+2,L'_');

	wcout << L"STRING [" << String << L"] !" << endl;
	wcout << L"RESULT 1 [" << *Result1 << L"] !" << endl;

	PrintLineSeparator();

	wstring::iterator											Result2=String.insert(String.cbegin()+2,2,L'+');

	wcout << L"STRING [" << String << L"] !" << endl;
	wcout << L"RESULT 2 [" << *Result2 << L"] !" << endl;

	PrintLineSeparator();

	wstring														TempString(L"098");
	wstring::iterator											Result3=String.insert(String.cbegin()+2,TempString.cbegin(),TempString.cend());

	wcout << L"STRING [" << String << L"] !" << endl;
	wcout << L"RESULT 3 [" << *Result3 << L"] !" << endl;

	PrintLineSeparator();

	wstring::iterator											Result4=String.insert(String.cbegin()+2,{L'X',L'Y',L'Z'});

	wcout << L"STRING [" << String << L"] !" << endl;
	wcout << L"RESULT 4 [" << *Result4 << L"] !" << endl;
#endif

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReplace(void)
{
	PrintLineSeparator();

	wstring														String1(L"Timmy Anderson");

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;

	String1.replace(2,3,L"AAA");

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;

	String1.replace(2,3,wstring(L"BBB"));

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;

	String1.replace(2,3,wstring(L"123456"),1,4);

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;

	String1.replace(2,3,L"123456",4);

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;

	String1.replace(2,3,5,L'!');

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;

	PrintLineSeparator();

	wstring														String2(L"Timmy Anderson");

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	String2.replace(String2.begin()+2,String2.begin()+5,L"AAA");

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	String2.replace(String2.begin()+2,String2.begin()+5,wstring(L"BBB"));

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	wstring														TempString(L"123456");

	String2.replace(String2.begin()+2,String2.begin()+5,TempString.cbegin()+1,TempString.cbegin()+5);

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	String2.replace(String2.begin()+2,String2.begin()+5,L"123456",4);

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	String2.replace(String2.begin()+2,String2.begin()+5,5,L'!');

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestErase(void)
{
	PrintLineSeparator();

	wstring														String(L"Timmy Anderson");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.erase(3,2);

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.erase(String.begin(),String.begin()+3);

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.erase(String.begin());

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPushBackPopBack(void)
{
	PrintLineSeparator();

	wstring														String(L"Timmy Anderson");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.push_back('!');
	String.push_back('?');

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.pop_back();

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAppend(void)
{
	PrintLineSeparator();

	wstring														String(L"1");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.append(3,'A');

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.append(L"QW");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.append(L"12345",3);

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.append(wstring(L"12345"),1,3);

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.append(wstring(L"++"));

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	wstring														StringToAdd(L"XYZ");

	String.append(StringToAdd.cbegin(),StringToAdd.cend());

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.append({L'~',L'|',L'!'});

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOperatorAppend(void)
{
	PrintLineSeparator();

	wstring														String(L"1");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String+=wstring(L"Hi");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String+=L"XYZ";

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String+=L'!';

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String+={L'~',L'|',L'!'};

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestResize(void)
{
	PrintLineSeparator();

	wstring														String(L"0123456789");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.resize(14);

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.resize(7);

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.resize(12,L'!');

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSubstring(void)
{
	PrintLineSeparator();

	wstring														String(L"Timmy Anderson");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"SUBSTRING [" << String.substr(5,15) << L"] !" << endl;
	wcout << L"SUBSTRING [" << String.substr(10,15) << L"] !" << endl;
	wcout << L"SUBSTRING [" << String.substr(10,150) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOperatorPlus(void)
{
	PrintLineSeparator();

	wcout << L"CONCATENATION [" << (wstring(L"AAA")+wstring(L"BBB")) << L"] !" << endl;
	wcout << L"CONCATENATION [" << (wstring(L"AAA")+L"BBB") << L"] !" << endl;
	wcout << L"CONCATENATION [" << (wstring(L"AAA")+L'B') << L"] !" << endl;
	wcout << L"CONCATENATION [" << (L"AAA"+wstring(L"BBB")) << L"] !" << endl;
	wcout << L"CONCATENATION [" << (L'A'+wstring(L"BBB")) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStreams(void)
{
	PrintLineSeparator();

	wstringstream												Stream;

	Stream << "   Timmy Anderson";

	wcout << L"STREAM [" << Stream.str() << L"] !" << endl;

	PrintLineSeparator();

	wstring														String1;

	// !!!!! Pretoze STREAM ma nastaveny FLAG [skipws], LEADING WHITE SPACES su pri citani IGNOROVANE.
	// !!! Cita sa obsah do vyskytu PRVEHO WHITE CHARACTER.
	Stream >> String1;

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;

	wstring														String2;

	// !!! Cita sa obsah do vyskytu PRVEHO WHITE CHARACTER.
	Stream >> String2;

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGetLine(void)
{
	PrintLineSeparator();

	wstringstream												Stream1;

	Stream1 << "Timmy\nAnderson";

	wcout << L"STREAM 1 [" << Stream1.str() << L"] !" << endl;

	PrintLineSeparator();

	wstring														String1;

	// !!! Cita sa obsah do vyskytu PRVEHO NEW LINE CHARACTER.
	getline(Stream1,String1);

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;

	wstring														String2;

	// !!! Cita sa obsah do vyskytu PRVEHO NEW LINE CHARACTER.
	getline(Stream1,String2);

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	PrintLineSeparator();

	wstringstream												Stream2;

	Stream2 << "Timmy!Anderson";

	wcout << L"STREAM 2 [" << Stream2.str() << L"] !" << endl;

	PrintLineSeparator();

	wstring														String3;

	// !!! Cita sa obsah do vyskytu PRVEHO CHARACTER '!'.
	getline(Stream2,String3,L'!');

	wcout << L"STRING 3 [" << String3 << L"] !" << endl;

	wstring														String4;

	// !!! Cita sa obsah do vyskytu PRVEHO CHARACTER '!'.
	getline(Stream2,String4,L'!');

	wcout << L"STRING 4 [" << String4 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFind(void)
{
	PrintLineSeparator();

	wstring														String(L"AAA BBB AAA BBB");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	wstring::size_type											Result1=String.find(wstring(L"AA"),0);

	if (Result1!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result1 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result2=String.find(wstring(L"qq"),0);

	if (Result2!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result2 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result3=String.find(L"BBB",0);

	if (Result3!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result3 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result4=String.find(L"AAAQQQ",5,5);

	if (Result4!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result4 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result5=String.find(L"AAAQQQ",5,3);

	if (Result5!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result5 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result6=String.find(L"AAAQQQ",10,3);

	if (Result6!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result6 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result7=String.find(L'A',3);

	if (Result7!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result7 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRFind(void)
{
	PrintLineSeparator();

	wstring														String(L"AAA BBB AAA BBB");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	wstring::size_type											Result1=String.rfind(wstring(L"AA"),wstring::npos);

	if (Result1!=wstring::npos)
	{
		wcout << "REVERSE FIND SUCCEEDED at POSITION [" << Result1 << L"] !" << endl;
	}
	else
	{
		wcout << "REVERSE FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result2=String.rfind(wstring(L"qq"),wstring::npos);

	if (Result2!=wstring::npos)
	{
		wcout << "REVERSE FIND SUCCEEDED at POSITION [" << Result2 << L"] !" << endl;
	}
	else
	{
		wcout << "REVERSE FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result3=String.rfind(L"BBB",wstring::npos);

	if (Result3!=wstring::npos)
	{
		wcout << "REVERSE FIND SUCCEEDED at POSITION [" << Result3 << L"] !" << endl;
	}
	else
	{
		wcout << "REVERSE FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result4=String.rfind(L"AAAQQQ",5,5);

	if (Result4!=wstring::npos)
	{
		wcout << "REVERSE FIND SUCCEEDED at POSITION [" << Result4 << L"] !" << endl;
	}
	else
	{
		wcout << "REVERSE FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result5=String.rfind(L"AAAQQQ",5,3);

	if (Result5!=wstring::npos)
	{
		wcout << "REVERSE FIND SUCCEEDED at POSITION [" << Result5 << L"] !" << endl;
	}
	else
	{
		wcout << "REVERSE FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result6=String.rfind(L"AAAQQQ",10,3);

	if (Result6!=wstring::npos)
	{
		wcout << "REVERSE FIND SUCCEEDED at POSITION [" << Result6 << L"] !" << endl;
	}
	else
	{
		wcout << "REVERSE FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result7=String.rfind(L'A',3);

	if (Result7!=wstring::npos)
	{
		wcout << "REVERSE FIND SUCCEEDED at POSITION [" << Result7 << L"] !" << endl;
	}
	else
	{
		wcout << "REVERSE FIND FAILED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFindFirstOf(void)
{
	PrintLineSeparator();

	wstring														String(L"Timmy Anderson Timmy Anderson");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	wstring::size_type											Result1=String.find_first_of(wstring(L"qvanz"),0);

	if (Result1!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result1 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result2=String.find_first_of(wstring(L"qvabz"),0);

	if (Result2!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result2 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result3=String.find_first_of(L"qvanz",0);

	if (Result3!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result3 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result4=String.find_first_of(L"qvabzAnd",5,5);

	if (Result4!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result4 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result5=String.find_first_of(L"qvabzAnd",5,8);

	if (Result5!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result5 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result6=String.find_first_of(L"qvabzAnd",10,8);

	if (Result6!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result6 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result7=String.find_first_of(L'A',3);

	if (Result7!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result7 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFindFirstNotOf(void)
{
	PrintLineSeparator();

	wstring														String(L"Timmy Anderson Timmy Anderson");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	wstring::size_type											Result1=String.find_first_not_of(wstring(L"qvanz"),0);

	if (Result1!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result1 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result2=String.find_first_not_of(wstring(L"Timmy Anderson"),0);

	if (Result2!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result2 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result3=String.find_first_not_of(L"qvanz",0);

	if (Result3!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result3 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result4=String.find_first_not_of(L"qvabzAnd",5,5);

	if (Result4!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result4 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result5=String.find_first_not_of(L"qvabzAnd",5,8);

	if (Result5!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result5 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result6=String.find_first_not_of(L"qvabzAnd",10,8);

	if (Result6!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result6 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result7=String.find_first_not_of(L'A',3);

	if (Result7!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result7 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFindLastOf(void)
{
	PrintLineSeparator();

	wstring														String(L"Timmy Anderson Timmy Anderson");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	wstring::size_type											Result1=String.find_last_of(wstring(L"qvanz"),wstring::npos);

	if (Result1!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result1 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result2=String.find_last_of(wstring(L"qvabz"),wstring::npos);

	if (Result2!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result2 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result3=String.find_last_of(L"qvanz",wstring::npos);

	if (Result3!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result3 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result4=String.find_last_of(L"qvabzAnd",5,5);

	if (Result4!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result4 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result5=String.find_last_of(L"qvabzAnd",5,8);

	if (Result5!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result5 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result6=String.find_last_of(L"qvabzAnd",10,8);

	if (Result6!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result6 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result7=String.find_last_of(L'A',3);

	if (Result7!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result7 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFindLastNotOf(void)
{
	PrintLineSeparator();

	wstring														String(L"Timmy Anderson Timmy Anderson");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	wstring::size_type											Result1=String.find_last_not_of(wstring(L"qvanz"),wstring::npos);

	if (Result1!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result1 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result2=String.find_last_not_of(wstring(L"Timmy Anderson"),wstring::npos);

	if (Result2!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result2 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result3=String.find_last_not_of(L"qvanz",wstring::npos);

	if (Result3!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result3 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result4=String.find_last_not_of(L"qvabzAnd",5,5);

	if (Result4!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result4 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result5=String.find_last_not_of(L"qvabzAnd",5,8);

	if (Result5!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result5 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result6=String.find_last_not_of(L"qvabzAnd",10,8);

	if (Result6!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result6 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();

	wstring::size_type											Result7=String.find_last_not_of(L'A',3);

	if (Result7!=wstring::npos)
	{
		wcout << "FIND SUCCEEDED at POSITION [" << Result7 << L"] !" << endl;
	}
	else
	{
		wcout << "FIND FAILED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ConversionToInt(const wstring& Value, int Base)
{
	try
	{
		size_t													Position;
		int														NumericValue=stoi(Value,&Position,Base);

		wcout << L"VALUE [" << Value << L"] CONVERTED to [" << NumericValue << L"] ! NUMBER of PROCESSED CHARACTERS [" << Position << L"] !" << endl;
	}
	catch(const invalid_argument&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! INVALID ARGUMENT EXCEPTION !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! OUT OF RANGE EXCEPTION !" << endl;
	}
}
//-----------------------------------------------------------------------------
void ConversionToLong(const wstring& Value, int Base)
{
	try
	{
		size_t													Position;
		long													NumericValue=stol(Value,&Position,Base);

		wcout << L"VALUE [" << Value << L"] CONVERTED to [" << NumericValue << L"] ! NUMBER of PROCESSED CHARACTERS [" << Position << L"] !" << endl;
	}
	catch(const invalid_argument&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! INVALID ARGUMENT EXCEPTION !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! OUT OF RANGE EXCEPTION !" << endl;
	}
}
//-----------------------------------------------------------------------------
void ConversionToUnsignedLong(const wstring& Value, int Base)
{
	try
	{
		size_t													Position;
		unsigned long											NumericValue=stoul(Value,&Position,Base);

		wcout << L"VALUE [" << Value << L"] CONVERTED to [" << NumericValue << L"] ! NUMBER of PROCESSED CHARACTERS [" << Position << L"] !" << endl;
	}
	catch(const invalid_argument&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! INVALID ARGUMENT EXCEPTION !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! OUT OF RANGE EXCEPTION !" << endl;
	}
}
//-----------------------------------------------------------------------------
void ConversionToLongLong(const wstring& Value, int Base)
{
	try
	{
		size_t													Position;
		long long												NumericValue=stoull(Value,&Position,Base);

		wcout << L"VALUE [" << Value << L"] CONVERTED to [" << NumericValue << L"] ! NUMBER of PROCESSED CHARACTERS [" << Position << L"] !" << endl;
	}
	catch(const invalid_argument&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! INVALID ARGUMENT EXCEPTION !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! OUT OF RANGE EXCEPTION !" << endl;
	}
}
//-----------------------------------------------------------------------------
void ConversionToUnsignedLongLong(const wstring& Value, int Base)
{
	try
	{
		size_t													Position;
		unsigned long long										NumericValue=stoull(Value,&Position,Base);

		wcout << L"VALUE [" << Value << L"] CONVERTED to [" << NumericValue << L"] ! NUMBER of PROCESSED CHARACTERS [" << Position << L"] !" << endl;
	}
	catch(const invalid_argument&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! INVALID ARGUMENT EXCEPTION !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! OUT OF RANGE EXCEPTION !" << endl;
	}
}
//-----------------------------------------------------------------------------
void ConversionToFloat(const wstring& Value)
{
	try
	{
		size_t													Position;
		float													NumericValue=stof(Value,&Position);

		wcout << L"VALUE [" << Value << L"] CONVERTED to [" << NumericValue << L"] ! NUMBER of PROCESSED CHARACTERS [" << Position << L"] !" << endl;
	}
	catch(const invalid_argument&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! INVALID ARGUMENT EXCEPTION !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! OUT OF RANGE EXCEPTION !" << endl;
	}
}
//-----------------------------------------------------------------------------
void ConversionToDouble(const wstring& Value)
{
	try
	{
		size_t													Position;
		double													NumericValue=stod(Value,&Position);

		wcout << L"VALUE [" << Value << L"] CONVERTED to [" << NumericValue << L"] ! NUMBER of PROCESSED CHARACTERS [" << Position << L"] !" << endl;
	}
	catch(const invalid_argument&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! INVALID ARGUMENT EXCEPTION !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! OUT OF RANGE EXCEPTION !" << endl;
	}
}
//-----------------------------------------------------------------------------
void ConversionToLongDouble(const wstring& Value)
{
	try
	{
		size_t													Position;
		long double												NumericValue=stold(Value,&Position);

		wcout << L"VALUE [" << Value << L"] CONVERTED to [" << NumericValue << L"] ! NUMBER of PROCESSED CHARACTERS [" << Position << L"] !" << endl;
	}
	catch(const invalid_argument&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! INVALID ARGUMENT EXCEPTION !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"CONVERSION of [" << Value << L"] FAILED ! OUT OF RANGE EXCEPTION !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestConversionStringToNumber(void)
{
	PrintLineSeparator();

	ConversionToInt(L"100",10);
	ConversionToInt(L"1FF",16);
	ConversionToInt(L"100",8);
	ConversionToInt(L"  100",10);
	ConversionToInt(L"  -100",10);
	ConversionToInt(L"50q",10);
	ConversionToInt(L"q50",10);
	ConversionToInt(L"9999999999999",10);
	ConversionToInt(L"33.345",10);

	PrintLineSeparator();

	ConversionToLong(L"999999999999",10);
	ConversionToLongLong(L"999999999999",10);

	PrintLineSeparator();

	ConversionToUnsignedLong(L"123456789",10);
	ConversionToUnsignedLong(L"-123456789",10);
	ConversionToUnsignedLongLong(L"1234567890123",10);
	ConversionToUnsignedLongLong(L"-1234567890123",10);

	PrintLineSeparator();

	ConversionToFloat(L"33.345");
	ConversionToFloat(L"33333333333333333333333333333333333333.345");
	ConversionToFloat(L"33.3451234567890123");
	ConversionToDouble(L"33.3451234567890123");
	ConversionToLongDouble(L"33.3451234567890123");
	ConversionToLongDouble(L"-33.3451234567890123");
	ConversionToLongDouble(L"a-33.3451234567890123");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void ConversionToString(TType Value)
{
	wcout << L"VALUE [" << Value << L"] CONVERTED to [" << to_wstring(Value) << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestConversionNumberToString(void)
{
	PrintLineSeparator();

	ConversionToString(int(100));
	ConversionToString(long(1000000000));
	ConversionToString((long long)(99999999999999));
	ConversionToString((long long)(-99999999999999));
	ConversionToString((unsigned int)(100));
	ConversionToString((unsigned long)(1000000000));
	ConversionToString((unsigned long long)(99999999999999));
	ConversionToString(float(123.456));
	ConversionToString(double(1239999999999.456987654321));
	ConversionToString((long double)(1239999999999.456987654321));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIterators(void)
{
	PrintLineSeparator();
	
	wstring														String(L"Timmy Anderson");
	const wstring&												ConstString=String;

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"CONST ITERATOR [";

	for(wstring::const_iterator Iterator=ConstString.begin();Iterator!=ConstString.end();Iterator++)
	{
		if (Iterator!=ConstString.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"CONST REVERSE ITERATOR [";

	for(wstring::const_reverse_iterator Iterator=ConstString.rbegin();Iterator!=ConstString.rend();Iterator++)
	{
		if (Iterator!=ConstString.crbegin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"ITERATOR [";

	for(wstring::iterator Iterator=String.begin();Iterator!=String.end();Iterator++)
	{
		if (Iterator!=String.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;

		// Modifikuje sa VALUE.
		*Iterator=*Iterator+1;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"STRING [" << String << L"] !" << endl;
	wcout << L"CONST STRING [" << ConstString << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"CONST ITERATOR [";

	for(wstring::const_iterator Iterator=String.begin();Iterator!=String.end();Iterator++)
	{
		if (Iterator!=String.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	wcout << L"REVERSE ITERATOR [";

	for(wstring::reverse_iterator Iterator=String.rbegin();Iterator!=String.rend();Iterator++)
	{
		if (Iterator!=String.rbegin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;

		// Modifikuje sa VALUE.
		*Iterator=*Iterator-1;
	}

	wcout << L"] !" << endl;

	wcout << L"CONST REVERSE ITERATOR [";

	for(wstring::const_reverse_iterator Iterator=String.crbegin();Iterator!=String.crend();Iterator++)
	{
		if (Iterator!=String.crbegin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"STRING [" << String << L"] !" << endl;
	
	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCustomCharacterTraits(void)
{
	PrintLineSeparator();

	CWideStringCaseInsensitive									String1(L"Timmy Anderson");
	CWideStringCaseInsensitive									String2(L"Tim Anderson");
	CWideStringCaseInsensitive									String3(L"TIMMY ANDERSON");

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;
	wcout << L"STRING 2 [" << String2 << L"] !" << endl;
	wcout << L"STRING 3 [" << String3 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"OPERATOR== [" << ((String1==String1) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR== [" << ((String1==String2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR== [" << ((String1==String3) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	CWideStringCaseInsensitive::size_type						Index=String1.find(L"ANDER");

	if (Index!=CWideStringCaseInsensitive::npos)
	{
		wcout << L"SUBSTRING FOUND at POSITION [" << Index << L"] !" << endl;
	}
	else
	{
		wcout << L"SUBSTRING NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCustomAllocator(void)
{
	PrintLineSeparator();

	{
		using													WideStringWithAllocator=basic_string<wchar_t,char_traits<wchar_t>,CStringAllocator<wchar_t>>;

		WideStringWithAllocator									String;

		String+=L"AAA aaa";
		String+=L" ";
		String+=L"BBB bbb";
		String+=L" ";
		String+=L"CCC ccc";

		wcout << L"STRING [" << String << L"] !" << endl;

		PrintLineSeparator();

		wcout << L"ALLOCATORS are [" << ((String.get_allocator()==String.get_allocator()) ? L"SAME" : L"DIFFERENT") << L"] !" << endl;
		wcout << L"ALLOCATORS are [" << ((String.get_allocator()!=String.get_allocator()) ? L"DIFFERENT" : L"SAME") << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestRangeCheck();
	//TestVariousStrings();
	//TestCharacterTraits();
	//TestNullTerminatorCharacter();
	//TestConstructors();
	//TestDataAndCStr();
	//TestCopy();
	//TestSize();
	//TestCapacity();
	//TestAtAndOperatorSubscript();
	//TestFrontBack();
	//TestCompare();
	//TestComparisonOperators();
	//TestOperatorAssignment();
	//TestAssign();
	//TestSwap();
	//TestClear();
	//TestInsert();
	//TestReplace();
	//TestErase();
	//TestPushBackPopBack();
	//TestAppend();
	//TestOperatorAppend();
	//TestResize();
	//TestSubstring();
	//TestOperatorPlus();
	//TestStreams();
	//TestGetLine();
	//TestFind();
	//TestRFind();
	//TestFindFirstOf();
	//TestFindFirstNotOf();
	//TestFindLastOf();
	//TestFindLastNotOf();
	//TestConversionStringToNumber();
	//TestConversionNumberToString();
	//TestIterators();
	//TestCustomCharacterTraits();
	TestCustomAllocator();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------