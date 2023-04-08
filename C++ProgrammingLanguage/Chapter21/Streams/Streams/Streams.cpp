//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <ios>
#include <iostream>
#include <strstream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "Name.h"
#include "SimpleManipulator.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void StreamCallback(ios_base::event Event, ios_base& Stream, int CustomState)
{
	if (Event==ios_base::copyfmt_event)
	{
		wprintf_s(L"EVENT: [COPY FORMAT], CusomState: [%d] !\n",CustomState);
	}
	else if (Event==ios_base::imbue_event)
	{
		wprintf_s(L"EVENT: [LOCALE CHANGED], CusomState: [%d] !\n",CustomState);
	}
	else if (Event==ios_base::erase_event)
	{
		wprintf_s(L"EVENT: [DESTRUCTOR CALLED], CusomState: [%d] !\n",CustomState);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	CName														Name(L"Timmy",L"Anderson",12);

	// !!! Pouzije sa CHAR verzia OPERATOR<<.
	cout << "[" << Name << "] !\n";

	// !!! Pouzije sa WCHAR_T verzia OPERATOR<<.
	wcout << L"[" << Name << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	wcout << L"TRUE: [" << true << L"] !\n";
	wcout << L"FALSE: [" << false << L"] !\n";

	// !!! Ak chcem vidiet TRUE a FALSE v TEXTOVEJ REPREZENTACII, musim pouzit LOCALE HELPER CLASS 'boolalpha'.
	wcout << boolalpha;

	wcout << L"TRUE: [" << true << L"] !\n";
	wcout << L"FALSE: [" << false << L"] !\n";

	int															Value=100;
	int*														Pointer=&Value;
	
	// !!! POINTERS sa vypisuju platformovo zavislym sposobom.
	wcout << L"POINTER: [" << Pointer << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	wstring														FirstName;
	wstring														LastName;
	int															Age;

	wstringstream												HelperStream;

	// !!! Kedze retazcne su oddelene znakom ' ', tak sa FirstName, LastName a Age uspesne nacitaju.
	HelperStream << L"Timmy Anderson 12";

	HelperStream.seekg(0);
	HelperStream.seekp(0);

	HelperStream >> FirstName >> LastName >> Age;

	wprintf_s(L"Name: [%s %s], Age: [%d] !\n",FirstName.c_str(),LastName.c_str(),Age);
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	wstring														Text1;
	wstring														Text2;
	wstring														Text3;

	wstringstream												HelperStream1;
	wstringstream												HelperStream2;

	// Ignoruje WHITE SPACES.
	// !!! Vyzera, ze to NEFUNGUJE.
	HelperStream1.unsetf(ios_base::skipws);

	HelperStream1 << L"Timmy Anderson 12";
	HelperStream1.seekg(0);
	HelperStream1.seekp(0);

	HelperStream2 << L"Timmy_Anderson";
	HelperStream2.seekg(0);
	HelperStream2.seekp(0);

	HelperStream1 >> Text1;

	wprintf_s(L"Name: [%s] !\n",Text1.c_str());

	// !!! Metoda width() ma platnost iba na NASLEDUJUCE VOLANIE OPERATOR>>.
	HelperStream2.width(3);
	// !!! Nacitaju sa iba prve 3 ZNAKY.
	HelperStream2 >> Text2;

	wprintf_s(L"Name: [%s] !\n",Text2.c_str());

	// !!! Metoda width() tu uz NEMA PLATNOST.
	HelperStream2 >> Text3;

	wprintf_s(L"Name: [%s] !\n",Text3.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	wstring														Text;
	wstringstream												HelperStream;

	wprintf_s(L"START - STATE: [%d], GOOD: [%d], EOF: [%d], FAIL: [%d], BAD: [%d] !\n",HelperStream.rdstate(),HelperStream.good(),HelperStream.eof(),HelperStream.fail(),HelperStream.bad());

	HelperStream << L"Timmy";

	wprintf_s(L"AFTER WRITE - STATE: [%d], GOOD: [%d], EOF: [%d], FAIL: [%d], BAD: [%d] !\n",HelperStream.rdstate(),HelperStream.good(),HelperStream.eof(),HelperStream.fail(),HelperStream.bad());

	HelperStream.seekg(0);
	HelperStream.seekp(0);

	wprintf_s(L"AFTER SEEK - STATE: [%d], GOOD: [%d], EOF: [%d], FAIL: [%d], BAD: [%d] !\n",HelperStream.rdstate(),HelperStream.good(),HelperStream.eof(),HelperStream.fail(),HelperStream.bad());

	// !!! STREAM sa dostane do EOF.
	HelperStream >> Text;

	wprintf_s(L"AFTER READ - STATE: [%d], GOOD: [%d], EOF: [%d], FAIL: [%d], BAD: [%d] !\n",HelperStream.rdstate(),HelperStream.good(),HelperStream.eof(),HelperStream.fail(),HelperStream.bad());

	// !!! STREAM sa dostane do FAIL STATE.
	HelperStream >> Text;

	wprintf_s(L"AFTER 2nd READ - STATE: [%d], GOOD: [%d], EOF: [%d], FAIL: [%d], BAD: [%d] !\n",HelperStream.rdstate(),HelperStream.good(),HelperStream.eof(),HelperStream.fail(),HelperStream.bad());

	HelperStream >> Text;

	wprintf_s(L"AFTER 3rd READ - STATE: [%d], GOOD: [%d], EOF: [%d], FAIL: [%d], BAD: [%d] !\n",HelperStream.rdstate(),HelperStream.good(),HelperStream.eof(),HelperStream.fail(),HelperStream.bad());
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	wstringstream												HelperStream;

	HelperStream << L"Timmy Anderson 12";
	HelperStream.seekg(0);
	HelperStream.seekp(0);

	wstring														Text;

	// !!! Pri TESTE sa vola OPERATOR void*(), ktory vracia hodnotu fail() konvertovanu na VOID*.
	while(HelperStream >> Text)
	{
		wprintf_s(L"Text: [%s] !\n",Text.c_str());

		wprintf_s(L"IN LOOP - STATE: [%d], GOOD: [%d], EOF: [%d], FAIL: [%d], BAD: [%d] !\n",HelperStream.rdstate(),HelperStream.good(),HelperStream.eof(),HelperStream.fail(),HelperStream.bad());
	}

	wprintf_s(L"AFTER WHILE - STATE: [%d], GOOD: [%d], EOF: [%d], FAIL: [%d], BAD: [%d] !\n",HelperStream.rdstate(),HelperStream.good(),HelperStream.eof(),HelperStream.fail(),HelperStream.bad());
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	wstringstream												HelperStream;

	HelperStream << L"Timmy Anderson 12";
	HelperStream.seekg(0);
	HelperStream.seekp(0);

	wstring														Text;

	// !!! Umyselne nastavim BAD STATE, cim sa zaroven nastavuje i FAIL STATE.
	HelperStream.setstate(ios_base::badbit);

	wprintf_s(L"BEFORE WHILE - STATE: [%d], GOOD: [%d], EOF: [%d], FAIL: [%d], BAD: [%d] !\n",HelperStream.rdstate(),HelperStream.good(),HelperStream.eof(),HelperStream.fail(),HelperStream.bad());

	// !!! Pri TESTE sa vola OPERATOR void*(), ktory vracia hodnotu fail() konvertovanu na VOID*.
	while(HelperStream >> Text)
	{
		wprintf_s(L"Text: [%s] !\n",Text.c_str());

		wprintf_s(L"IN LOOP - STATE: [%d], GOOD: [%d], EOF: [%d], FAIL: [%d], BAD: [%d] !\n",HelperStream.rdstate(),HelperStream.good(),HelperStream.eof(),HelperStream.fail(),HelperStream.bad());
	}

	wprintf_s(L"AFTER WHILE - STATE: [%d], GOOD: [%d], EOF: [%d], FAIL: [%d], BAD: [%d] !\n",HelperStream.rdstate(),HelperStream.good(),HelperStream.eof(),HelperStream.fail(),HelperStream.bad());
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	wstringstream												HelperStream;
	int															Value=0;

	// Do STREAM dam TEXT.
	HelperStream << L"Timmy";
	HelperStream.seekg(0);
	HelperStream.seekp(0);
	
	// !!! Skusam vsak citat INT.
	HelperStream >> Value;

	wprintf_s(L"AFTER READ - STATE: [%d], GOOD: [%d], EOF: [%d], FAIL: [%d], BAD: [%d] !\n",HelperStream.rdstate(),HelperStream.good(),HelperStream.eof(),HelperStream.fail(),HelperStream.bad());

	// !!! Pri zlyhani citania sa hodnota 'Value' NEZMENI.
	wprintf_s(L"Value: [%d] !\n",Value);
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	wstringstream												HelperStream;

	HelperStream << L"Timmy Anderson\nAtreyu";

	wchar_t														Line1[100];
	wchar_t														Line2[100];

	// !!! Ako LINE SEPARATOR pouziva NEW LINE.
	HelperStream.getline(Line1,_countof(Line1));

	// !!! Vracia POCET ZNAKOV, ktore nacitala posledna READ OPERACIA.
	wprintf_s(L"READ: [%d] CHARS !\n",HelperStream.gcount());
	
	HelperStream.getline(Line2,_countof(Line2));

	wprintf_s(L"READ: [%d] CHARS !\n",HelperStream.gcount());

	wprintf_s(L"Line1: [%s] !\n",Line1);
	wprintf_s(L"Line2: [%s] !\n",Line2);
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	wstringstream												HelperStream;

	HelperStream << L"Timmy Anderson\nAtreyu";

	wchar_t														Line[100];

	// !!! Ako LINE SEPARATOR pouziva NEW LINE.
	HelperStream.read(Line,_countof(Line));

	size_t														ReadChars=HelperStream.gcount();

	// !!! Kedze metoda read() NEDOPLNA na koniec znak '\0', treba ho tam doplnit rucne.
	Line[ReadChars]='\0';

	wprintf_s(L"Line: [%s] !\n",Line);
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	CName														Name1;
	CName														Name2;

	wstringstream												HelperStream1;
	wstringstream												HelperStream2;

	HelperStream1 << L"Timmy Anderson 12";
	// Ako AGE dam CHYBNU HODNOTU.
	HelperStream2 << L"Timmy Anderson !!!";

	HelperStream1.seekg(0);
	HelperStream1.seekp(0);
	HelperStream2.seekg(0);
	HelperStream2.seekp(0);

	HelperStream1 >> Name1;

	if (HelperStream1.fail()==false && HelperStream1.bad()==false)
	{
		wprintf_s(L"Name1 [Name: %s %s, Age: %d] !\n",Name1.GetFirstName().c_str(),Name1.GetLastName().c_str(),Name1.GetAge());
	}
	else
	{
		wprintf_s(L"Can't READ Name1 !\n");
	}

	HelperStream2 >> Name2;

	if (HelperStream2.fail()==false && HelperStream2.bad()==false)
	{
		wprintf_s(L"Name2 [Name: %s %s, Age: %d] !\n",Name2.GetFirstName().c_str(),Name2.GetLastName().c_str(),Name2.GetAge());
	}
	else
	{
		wprintf_s(L"Can't READ Name2 !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	wstringstream												HelperStream;
	int															Value=0;
	
	// Do STREAM dam TEXT.
	HelperStream << L"Timmy";
	HelperStream.seekg(0);
	HelperStream.seekp(0);

	HelperStream.exceptions(ios_base::failbit | ios_base::badbit);

	try
	{
		// !!! Skusam vsak citat INT.
		HelperStream >> Value;

		// !!! Pri zlyhani citania sa hodnota 'Value' NEZMENI.
		wprintf_s(L"Value: [%d] !\n",Value);
	}
	catch(ios_base::failure& E)
	{
		printf_s("EXCEPTION: [%s] !\n",E.what());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	wstringstream												HelperStream;
	int															Value=0;
	
	// Do STREAM dam TEXT.
	HelperStream << L"Timmy";
	HelperStream.seekg(0);
	HelperStream.seekp(0);

	// Umely SCOPE.
	{
		// !!!!! Pouziva sa iba v IOSTREAM CLASSES pre pretazovani tychto CLASSES.
		wistream::sentry										Sentry(HelperStream);

		if (!Sentry==false)
		{
			try
			{
				HelperStream.exceptions(ios_base::failbit | ios_base::badbit);

				// !!! Skusam vsak citat INT.
				HelperStream >> Value;

				// ??? Neviem preco, ale aj pri chybe citania tato podmienka prejde.
				if (!Sentry==false)
				{
					// !!! Pri zlyhani citania sa hodnota 'Value' NEZMENI.
					wprintf_s(L"Value: [%d] !\n",Value);
				}
				else
				{
					wprintf_s(L"ERROR !\n");
				}
			}
			catch(ios_base::failure& E)
			{
				printf_s("EXCEPTION: [%s] !\n",E.what());
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------
void Test14(void)
{
	wcout << L"INT: [" << 128 << L"] !\n";

	ios_base::fmtflags											OldFlags;

	// !!! Pridaju sa FLAGS na vypis HEXA hodnot.
	// !!!!! Kedze FLAG 'hex' je VIAC BITOVY, je potrebne ho nastavit cez 2 PARAMETRICKU verziu metody setf() s MASKOU ios_base::basefield.
	OldFlags=wcout.setf(ios_base::hex,ios_base::basefield);

	wcout << L"INT: [" << 128 << L"] !\n";

	wcout.setf(OldFlags);

	wcout << L"INT: [" << 128 << L"] !\n";

	OldFlags=wcout.setf(ios_base::hex,ios_base::basefield);

	// Nastavim aj vypisovanie RADU. To je iba 1 BITOVY FLAG a tak je mozne ho nastavit iba cez 1 PARAMETRICKU verziu metody setf().
	wcout.setf(ios_base::showbase);

	wcout << L"INT: [" << 128 << L"] !\n";

	wcout.setf(OldFlags);

	wcout << L"INT: [" << 128 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void Test15(void)
{
	wcout << L"FLOAT: [" << 123.456 << L"] !\n";

	// !!!!! Kedze FLAG 'scientific' je VIAC BITOVY, je potrebne ho nastavit cez 2 PARAMETRICKU verziu metody setf() s MASKOU ios_base::floatfield.
	wcout.setf(ios_base::scientific,ios_base::floatfield);

	wcout << L"FLOAT - SCIENTIFIC: [" << 123.456 << L"] !\n";

	wcout.setf(ios_base::fixed,ios_base::floatfield);

	wcout << L"FLOAT - FIXED: [" << 123.456 << L"] !\n";

	// !!! Zmenim PRECISON.
	wcout.precision(15);

	// !!! Kedze FLAG 'uppercase' je 1 BIT, mozem pouzit 1 PARAMETRICKU verziu setf().
	wcout.setf(ios_base::uppercase);

	wcout.setf(ios_base::scientific,ios_base::floatfield);

	wcout << L"FLOAT - SCIENTIFIC: [" << 123.456 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void Test16(void)
{
	wcout << L"INT: [";

	// !!! Metodu width() MUSIM aplikovat az TU, lebo 1. VOLANIE OPERATOR<< (trebars aj nad STRING) jej platnost RUSI.
	wcout.width(10);
	wcout << 128 << L"] !\n";

	// !!! Kedze width() ma platnost IBA do 1 volania OPERATOR<<, tak sa tu uz NEAPLIKUJE.
	wcout << L"INT: [" << 128 << L"] !\n";

	wcout << L"FLOAT: [";

	// !!! Metodu width() MUSIM aplikovat az TU, lebo 1. VOLANIE OPERATOR<< (trebars aj nad STRING) jej platnost RUSI.
	wcout.width(10);
	wcout << 123.456 << L"] !\n";

	// !!! Kedze width() ma platnost IBA do 1 volania OPERATOR<<, tak sa tu uz NEAPLIKUJE.
	wcout << L"FLOAT: [" << 123.456 << L"] !\n";

	wcout << L"FLOAT - LEFT: [";

	// !!! Metodu width() MUSIM aplikovat az TU, lebo 1. VOLANIE OPERATOR<< (trebars aj nad STRING) jej platnost RUSI.
	wcout.width(10);
	wcout.setf(ios_base::left,ios_base::adjustfield);
	wcout << -123.456 << L"] !\n";

	wcout << L"FLOAT - RIGHT: [";

	// !!! Metodu width() MUSIM aplikovat az TU, lebo 1. VOLANIE OPERATOR<< (trebars aj nad STRING) jej platnost RUSI.
	wcout.width(10);
	wcout.setf(ios_base::right,ios_base::adjustfield);
	wcout << -123.456 << L"] !\n";

	wcout << L"FLOAT - INTERNAL: [";

	// !!! Metodu width() MUSIM aplikovat az TU, lebo 1. VOLANIE OPERATOR<< (trebars aj nad STRING) jej platnost RUSI.
	wcout.width(10);
	wcout.setf(ios_base::internal,ios_base::adjustfield);
	wcout << -123.456 << L"] !\n";

	// !!! Nastavim FILL.
	wcout.fill(L'_');

	wcout << L"FLOAT - LEFT - FILL: [";

	// !!! Metodu width() MUSIM aplikovat az TU, lebo 1. VOLANIE OPERATOR<< (trebars aj nad STRING) jej platnost RUSI.
	wcout.width(10);
	wcout.setf(ios_base::left,ios_base::adjustfield);
	wcout << -123.456 << L"] !\n";

	wcout << L"FLOAT - RIGHT - FILL: [";

	// !!! Metodu width() MUSIM aplikovat az TU, lebo 1. VOLANIE OPERATOR<< (trebars aj nad STRING) jej platnost RUSI.
	wcout.width(10);
	wcout.setf(ios_base::right,ios_base::adjustfield);
	wcout << -123.456 << L"] !\n";

	wcout << L"FLOAT - INTERNAL - FILL: [";

	// !!! Metodu width() MUSIM aplikovat az TU, lebo 1. VOLANIE OPERATOR<< (trebars aj nad STRING) jej platnost RUSI.
	wcout.width(10);
	wcout.setf(ios_base::internal,ios_base::adjustfield);
	wcout << -123.456 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test17(void)
{
	// Pouzijem PARAMETRICKY MANIPULATOR.
	wcout << L"INT: [" << setw(10) << 128 << L"] !\n";

	// Cez MANIPULATORS sa daju nastavit i FLAGS.
	wcout << L"INT: [" << setbase(ios_base::basefield) << setiosflags(ios_base::hex) << 128 << L"] !\n";

	// !!! BEZPARAMETRICKY MAINPULATOR NEW LINE.
	wcout << L"FLOAT: [" << 123.456 << L"] !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void Test18(void)
{
	// Pouzijem PARAMETRICKY MANIPULATOR.
	wcout << L"INT: [" << setw(10) << 128 << L"] !\n";

	// !!!!! Pouzijem CUSTOM MANIPULATOR. Vytvaram INSTANCIU objektu CUSTOM MANIPULATOR.
	wcout << L"INT: [" << CSimpleManipulator(10) << 128 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void Test19(void)
{
	wfstream													File;

	File.exceptions(ios_base::failbit | ios_base::badbit);

	try
	{
		// !!! Nejako 'skipws' NEFUNGUJE.
		File >> skipws;

		File.open("!Files\\Test.txt");
		
		wstring													Text;
	
		File >> ws >> Text;

		wprintf_s(L"Text: [%s] !\n",Text.c_str());

		File.close();
	}
	catch(ios_base::failure& E)
	{
		// !!! Pri EXCEPTION sa NESMIE volat close().
		//File.close();

		printf_s("EXCEPTION: [%s] !\n",E.what());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test20(void)
{
	wfstream													File;

	File.open("!Files\\Test.txt");
		
	wstring														Text;
	
	wchar_t														Char;

	while(File.good()==true && File.eof()==false)
	{
		File.get(Char);

		if (File.eof()==false)
		{
			Text+=Char;
		}
	}

	wprintf_s(L"Text: [%s] !\n",Text.c_str());

	File.close();
}
//-------------------------------------------------------------------------------------------------------
void Test21(void)
{
	{
		wfstream												File;

		File.open("!Files\\Test.txt",ios_base::in | ios_base::out);
		
		wstring													Text;
	
		wchar_t													Char;

		while(File.good()==true && File.eof()==false)
		{
			File.get(Char);

			if (File.eof()==false)
			{
				Text+=Char;
			}
		}

		wprintf_s(L"Text: [%s] !\n",Text.c_str());

		// !!! Umyselne NEVOLA CLOSE.
		//File.close();
	}

	{
		wfstream												File;

		File.open("!Files\\Test.txt",ios_base::in | ios_base::out);
		
		wstring													Text;
	
		wchar_t													Char;

		while(File.good()==true && File.eof()==false)
		{
			File.get(Char);

			if (File.eof()==false)
			{
				Text+=Char;
			}
		}

		wprintf_s(L"Text: [%s] !\n",Text.c_str());

		// !!! Umyselne NEVOLA CLOSE.
		//File.close();
	}
}
//-------------------------------------------------------------------------------------------------------
void Test22(void)
{
	wstringstream												Stream1;

	Stream1 << L"Timmy" << L" " << L"Anderson" << L" " << 12;

	wstring														Text1=Stream1.str();

	wprintf_s(L"Text1: [%s] !\n",Text1.c_str());

	wstringstream												Stream2;

	Stream2 << 33;

	wstring														Text2=Stream2.str();

	wprintf_s(L"Text2: [%s] !\n",Text2.c_str());

	wstringstream												Stream3;

	Stream3 << 33.44;

	wstring														Text3=Stream3.str();

	wprintf_s(L"Text3: [%s] !\n",Text3.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test23(void)
{
	wstringstream												Stream;

	Stream << L"1234567890";

	// !!! Ziskam POINTER na INTERNY BUFFER.
	wstringbuf*													Buffer=Stream.rdbuf();
	
	// !!! Posuniem poziciu v BUFFER.
	Buffer->pubseekpos(5);

	wstring														String;

	wprintf_s(L"CHARS in BUFFER: [%d] !\n",Buffer->in_avail());

	Stream >> String;

	wprintf_s(L"String: [%s] !\n",String.c_str());

	wprintf_s(L"CHARS in BUFFER: [%d] !\n",Buffer->in_avail());
}
//-------------------------------------------------------------------------------------------------------
void Test24(void)
{
	// Definujem SLOVENSKY LOCALE.
	locale														L=locale("Slovak_slovakia");

	wcout << L"FLOAT DEFAULT: [" << 123.456 << L"] !\n";

	// Nastavim SLOVENSKY LOCALE.
	wcout.imbue(L);

	// Zobrazi sa DESATINNA CIARKA.
	wcout << L"FLOAT Slovak: [" << 123.456 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void Test25(void)
{
	// Definujem SLOVENSKY LOCALE.
	locale														L=locale("Slovak_slovakia");

	wstringstream												Stream;

	// !!! Zaregistrujem odber EVENTS. Druhy parameter je LUBOVOLNA CUSTOM hodnota.
	Stream.register_callback(StreamCallback,99);

	// Nastavim SLOVENSKY LOCALE.
	Stream.imbue(L);

	// Zobrazi sa DESATINNA CIARKA.
	Stream << L"FLOAT Slovak: [" << 123.456 << L"] !\n";

	wprintf_s(Stream.str().c_str());
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
	//Test16();
	//Test17();
	//Test18();
	//Test19();
	//Test20();
	//Test21();
	//Test22();
	//Test23();
	//Test24();
	Test25();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------