//-------------------------------------------------------------------------------------------------------
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <locale>
#include <time.h>
#include "ISeasonFacet.h"
#include "SeasonFacet_USA.h"
#include "SeasonFacet_SK.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	wcout << L"Default: [" << 10.5 << L"] !\n";

	// !!!!! Vyzera, ze Visual C++ pouziva INU KONVENCIU pre pomenovanie CULTURES.
	wcout.imbue(locale("Slovak_slovakia"));
	
	// Pouzije znak ',' ako oddelovat desatinneho miesta.
	wcout << L"Slovak: [" << 10.5 << L"] !\n";
	
	wcout.imbue(locale("English_US"));

	wcout << L"USA: [" << 10.5 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	locale														L1=locale("Slovak_slovakia");
	locale														L2=locale("English_US");

	printf_s("Slovak [%s] !\n",L1.c_str());
	printf_s("USA [%s] !\n",L2.c_str());

	locale														L3=locale();

	printf_s("Default [%s] !\n",L3.c_str());

	// Specialny 'C' LOCALE, co je DEFAULT LOCALE z jazyka C.
	locale														L4=locale("C");

	printf_s("C [%s] !\n",L4.c_str());

	// DEFAULT NASTAVENIE OS.
	locale														L5=locale("");

	printf_s("Empty [%s] !\n",L5.c_str());

	// Metoda name() vracia 'string' s menom LOCALE.
	printf_s("Empty - name() [%s] !\n",L5.name().c_str());

	/*
	// Visual C++ NEPODPORUJE 'POSIX' LOCALE.
	locale														L6=locale("POSIX");

	printf_s("POSIX [%s] !\n",L6.c_str());
	*/

	/*
	// Hodi EXCEPTION.
	locale														L7=locale(L1,"MyCUSTOMNAME",locale::all);

	printf_s("CUSTOM [%s] !\n",L7.c_str());
	*/

	locale														L8=locale(L1,L2,locale::all);

	printf_s("CUSTOM [%s] !\n",L8.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	// DEFAULT LOCALE.
	locale														L0=locale("");
	locale														L1=locale("Slovak_slovakia");
	// Zoberiem IBA NUMERIC FACET z L1.
	locale														L2=locale(L0,L1,locale::numeric);
	// Zoberiem IBA TIME FACET z L1.
	locale														L3=locale(L0,L1,locale::time);

	wcout.imbue(L0);
	wcout << L"L0: [" << 10.5 << L"] !\n";

	wcout.imbue(L1);
	wcout << L"L1: [" << 10.5 << L"] !\n";

	wcout.imbue(L2);
	// Vypise [10,5] - lebo sa SLOVENSKY NUMERIC FACET SKOPIROVAL.
	wcout << L"L2: [" << 10.5 << L"] !\n";

	wcout.imbue(L3);
	// Vypise [10.5] - lebo sa SLOVENSKY NUMERIC FACET NESKOPIROVAL.
	wcout << L"L3: [" << 10.5 << L"] !\n";
	
	// Zoberiem z L1 VSETKY FACETS OKREM 'num_get'.
	locale														L4=L0.combine<num_get<wchar_t>>(L1);
	
	// Zoberiem z L1 VSETKY FACETS OKREM 'numpunct'.
	locale														L5=L0.combine<numpunct<wchar_t>>(L1);

	wcout.imbue(L4);
	// Vypise [10.5] - lebo sa SLOVENSKY 'num_get' FACET NESKOPIROVAL.
	wcout << L"L4: [" << 10.5 << L"] !\n";

	wcout.imbue(L5);
	// Vypise [10,5] - lebo sa SLOVENSKY 'num_get' FACET SKOPIROVAL. Neskopiroval sa 'numpunct'.
	wcout << L"L5: [" << 10.5 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	locale														L1=locale("Slovak_slovakia");

	locale::global(L1);

	// !!! Zobrazi ANGLICKU VERZIU CISLA, pretoze na EXISTUJUCE STREAMS uz NEMA VOLANIE global() VPLYV.
	wcout << L"AFTER global(): [" << 10.5 << L"] !\n";

	stringstream												SS;

	SS << 10.5;
	
	SS.seekg(0);

	char														Buffer[100];

	memset(Buffer,0,sizeof(Buffer));

	SS.read(Buffer,10);

	// !!! Vypise desatinne cislo po SLOVENSKY (aktualny GLOBAL LOCALE), pretoze na NOVE STREAMS sa aplikuje vysledok posledneho volania global().
	wcout << L"AFTER global() on STRING STREAM: [" << Buffer << L"] !\n";

	// !!!!! Aj vsetky C FUNKCIE sa volanim global() ZMENIA, takze vysledok je SLOVENSKE DESATINNE CISLO.
	wprintf_s(L"Using wprintf_s(): [%f] !\n",10.5);
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ASSERT, 0);

	// !!! Hodnota 0 znamena, ze LOCALE AUTOMATICKY VYMAZE INSTANCIU 'Facet'.
	num_get<wchar_t>*											Facet=new num_get<wchar_t>(0);
	
	locale														L1=locale("Slovak_slovakia");
	locale														L2=locale(L1,Facet);

	wcout.imbue(L1);
	wcout << L"L1: [" << 10.5 << L"] !\n";

	wcout.imbue(L2);
	wcout << L"L2: [" << 10.5 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	locale														L=locale("Slovak_slovakia");
	
	if (has_facet<numpunct_byname<wchar_t>>(L)==true)
	{
		wprintf_s(L"LOCALE HAS FACET [num_put<wchar_t>] !\n");

		// !!! Kedze DESTRUCTOR je PROTECTED, musim pristupovat k FACET cez REFERENCES.
		const numpunct_byname<wchar_t>&							Facet=use_facet<numpunct_byname<wchar_t>>(L);

		// !!! Vrati znak [,], lebo sa jedna o FACET SLOVENSKEHO LOCALE.
		wcout << L"Facet.decimal_point(): [" << Facet.decimal_point() << L"] !\n";
	}
	else
	{
		wprintf_s(L"LOCALE HAS NOT FACET [num_put<wchar_t>] !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	cout << "NO FACET: [" << E_WINTER << "] !\n";

	// !!! FACETS sa MUSIA vytvarat na HEAP.
	CSeasonFacet_USA*											FacetUSA=new CSeasonFacet_USA();
	CSeasonFacet_SK*											FacetSK=new CSeasonFacet_SK();

	locale														L1=locale(locale(),FacetUSA);
	locale														L2=locale(locale(),FacetSK);

	// !!! CSeasonFacet_USA a CSeasonFacet_SK podporuju IBA STRING a NIE WSTRING, preto pouzivam COUT a NIE WCOUT.
	cout.imbue(L1);
	cout << "USA FACET: [" << E_WINTER << "] !\n";

	// !!! CSeasonFacet_USA a CSeasonFacet_SK podporuju IBA STRING a NIE WSTRING, preto pouzivam COUT a NIE WCOUT.
	cout.imbue(L2);
	cout << "SK FACET: [" << E_WINTER << "] !\n";
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	locale														L=locale("Slovak_slovakia");
	const numpunct<wchar_t>&									Facet=use_facet<numpunct<wchar_t>>(L);
	locale														LocaleDefault;

	// Skopiruje sa DEFAULT LOCALE s FACET obsahujucim numpunct<wchar_t> zo SLOVENSKEHO LOCALE.
	locale														LocaleWithFacet1(L,&Facet);

	wcout.imbue(LocaleWithFacet1);
	wcout << L"LocaleWithFacet1: [" << 10.5 << L"] !\n";

	// Skopiruje sa DEFAULT LOCALE so VSETKYMI FACETS typu NUMERIC.
	locale														LocaleWithFacet2(LocaleDefault,L,locale::numeric);

	wcout.imbue(LocaleWithFacet2);
	wcout << L"LocaleWithFacet2: [" << 10.5 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	wstring														Value1=L"CH";
	wstring														Value2=L"DH";
	const wchar_t*												Value1Begin=Value1.c_str();
	const wchar_t*												Value1End=Value1.c_str()+Value1.size();
	const wchar_t*												Value2Begin=Value2.c_str();
	const wchar_t*												Value2End=Value2.c_str()+Value2.size();

	locale														LocaleDefault=locale("");
	locale														LocaleSlovak=locale("Slovak_slovakia");

	const collate<wchar_t>&										FacetDefault=use_facet<collate<wchar_t>>(LocaleDefault);
	const collate<wchar_t>&										FacetSlovak=use_facet<collate<wchar_t>>(LocaleSlovak);

	wprintf_s(L"FacetDefault - COMPARE CH and DH - RESULT: [%d] !\n",FacetDefault.compare(Value1Begin,Value1End,Value2Begin,Value1End));
	// !!! SLOVENSKY COLLATE povazuje 'CH' za JEDEN ZNAK, ktory je NIZSIE v ABECEDE ako 'DH'.
	wprintf_s(L"FacetSlovak - COMPARE CH and DH - RESULT: [%d] !\n",FacetSlovak.compare(Value1Begin,Value1End,Value2Begin,Value1End));

	wstring														TransformedStringDefault1=FacetDefault.transform(Value1Begin,Value1End);
	wstring														TransformedStringDefault2=FacetDefault.transform(Value2Begin,Value2End);
	wstring														TransformedStringSlovak1=FacetSlovak.transform(Value1Begin,Value1End);
	wstring														TransformedStringSlovak2=FacetSlovak.transform(Value2Begin,Value2End);

	if (TransformedStringDefault1>TransformedStringDefault2)
	{
		wprintf_s(L"FacetDefault - CH>DH !\n");
	}
	else
	{
		wprintf_s(L"FacetDefault - CH<DH !\n");
	}

	// !!! Porovnanie SLOVENSKYCH ZNAKOV.
	if (TransformedStringSlovak1>TransformedStringSlovak2)
	{
		wprintf_s(L"FacetSlovak - CH>DH !\n");
	}
	else
	{
		wprintf_s(L"FacetSlovak - CH<DH !\n");
	}

	const collate_byname<wchar_t>&								FacetByNameSlovak=use_facet<collate_byname<wchar_t>>(LocaleSlovak);

	wprintf_s(L"FacetSlovak HASH(CH): [%d] !\n",FacetSlovak.hash(Value1Begin,Value1End));
	wprintf_s(L"FacetByNameSlovak HASH(CH): [%d] !\n",FacetByNameSlovak.hash(Value1Begin,Value1End));
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	locale														LocaleSlovak=locale("Slovak_slovakia");
	const numpunct<wchar_t>&									FacetByNameSlovak=use_facet<numpunct<wchar_t>>(LocaleSlovak);

	printf_s("FacetSlovak grouping(): [%s] !\n",FacetByNameSlovak.grouping().c_str());
	wprintf_s(L"FacetSlovak decimal_point(): [%c] !\n",FacetByNameSlovak.decimal_point());
	wprintf_s(L"FacetSlovak thousands_sep(): [%c] !\n",FacetByNameSlovak.thousands_sep());
	wprintf_s(L"FacetSlovak truename(): [%s] !\n",FacetByNameSlovak.truename().c_str());
	wprintf_s(L"FacetSlovak falsename(): [%s] !\n",FacetByNameSlovak.falsename().c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	locale														LocaleSlovak=locale("Slovak_slovakia");
	const num_put<wchar_t>&										Facet=use_facet<num_put<wchar_t>>(LocaleSlovak);

	wprintf_s(L"Facet [");
	// !!! Vypise DEFAULT VERZIU (anglicku), lebo LOCALE vytiahne z 2. PARAMETRA (wcout) na ktorom je zatial nastaveny DEFAULT.
	Facet.put(wcout,wcout,L' ',10.5);
	wprintf_s(L"] !\n");

	wprintf_s(L"Facet [");
	wcout.imbue(LocaleSlovak);
	// !!! Vypise SLOVENSKU VERZIU (anglicku), lebo LOCALE vytiahne z 2. PARAMETRA (wcout) na ktorom je uz nastavena SLOVENSKA LOCALE.
	Facet.put(wcout,wcout,L' ',10.5);
	wprintf_s(L"] !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	locale														LocaleSlovak=locale("Slovak_slovakia");
	// !!! Kedze ako DEFAULT ITERATORS sa pouziva 'istreambuf', MUSIM to zmenit na wstring::iterator.
	const num_get<wchar_t,wstring::iterator>&					Facet=use_facet<num_get<wchar_t,wstring::iterator>>(LocaleSlovak);

	double														ValueUSA=0.0;
	double														ValueSlovak=0.0;
	ios_base::iostate											StateUSA=0;
	ios_base::iostate											StateSlovak=0;

	wstring														TextUSA=L"3.14";
	wstring														TextSlovak=L"3,14";

	// !!! 3. parameter sluzi iba na to, aby si FACET zo STREAMU vytiahol LOCALE.
	Facet.get(TextUSA.begin(),TextUSA.end(),wcin,StateUSA,ValueUSA);

	printf_s("ValueUSA: [%f] !\n",ValueUSA);

	wcin.imbue(LocaleSlovak);
	// !!! 3. parameter sluzi iba na to, aby si FACET zo STREAMU vytiahol LOCALE.
	Facet.get(TextSlovak.begin(),TextSlovak.end(),wcin,StateSlovak,ValueSlovak);

	printf_s("ValueSlovak: [%f] !\n",ValueSlovak);
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	locale														Locale=locale("");
	const moneypunct<wchar_t,true>&								Facet=use_facet<moneypunct<wchar_t,true>>(Locale);

	printf_s("Facet grouping(): [%s] !\n",Facet.grouping().c_str());
	wprintf_s(L"Facet decimal_point(): [%c] !\n",Facet.decimal_point());
	wprintf_s(L"Facet thousands_sep(): [%c] !\n",Facet.thousands_sep());
	wprintf_s(L"Facet pos_format(): [%c %c %c %c] !\n",Facet.pos_format().field[0],Facet.pos_format().field[1],Facet.pos_format().field[2],Facet.pos_format().field[3]);
	wprintf_s(L"Facet neg_format(): [%c %c %c %c] !\n",Facet.neg_format().field[0],Facet.neg_format().field[1],Facet.neg_format().field[2],Facet.neg_format().field[3]);
	wprintf_s(L"Facet frac_digits(): [%d] !\n",Facet.frac_digits());
	wprintf_s(L"Facet positive_sign(): [%s] !\n",Facet.positive_sign().c_str());
	wprintf_s(L"Facet negative_sign(): [%s] !\n",Facet.negative_sign().c_str());

	locale														LocaleSlovak=locale("Slovak_slovakia");
	const moneypunct_byname<wchar_t,true>&						FacetSlovak=use_facet<moneypunct_byname<wchar_t,true>>(LocaleSlovak);

	printf_s("FacetSlovak grouping(): [%s] !\n",FacetSlovak.grouping().c_str());
	wprintf_s(L"FacetSlovak decimal_point(): [%c] !\n",FacetSlovak.decimal_point());
	wprintf_s(L"FacetSlovak thousands_sep(): [%c] !\n",FacetSlovak.thousands_sep());
	wprintf_s(L"FacetSlovak pos_format(): [%c %c %c %c] !\n",FacetSlovak.pos_format().field[0],Facet.pos_format().field[1],Facet.pos_format().field[2],Facet.pos_format().field[3]);
	wprintf_s(L"FacetSlovak neg_format(): [%c %c %c %c] !\n",FacetSlovak.neg_format().field[0],Facet.neg_format().field[1],Facet.neg_format().field[2],Facet.neg_format().field[3]);
	wprintf_s(L"FacetSlovak frac_digits(): [%d] !\n",FacetSlovak.frac_digits());
	wprintf_s(L"FacetSlovak positive_sign(): [%s] !\n",FacetSlovak.positive_sign().c_str());
	wprintf_s(L"FacetSlovak negative_sign(): [%s] !\n",FacetSlovak.negative_sign().c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test14(void)
{
	locale														LocaleUSA=locale("");
	locale														LocaleSlovak=locale("Slovak_slovakia");
	const money_put<wchar_t>&									Facet=use_facet<money_put<wchar_t>>(LocaleSlovak);

	wprintf_s(L"Facet [");
	wcout.imbue(LocaleUSA);
	// !!! Vypise DEFAULT VERZIU (anglicku), lebo LOCALE vytiahne z 3. PARAMETRA (wcout) na ktorom je zatial nastaveny DEFAULT.
	Facet.put(wcout,false,wcout,L' ',1234.56);
	wprintf_s(L"] !\n");

	wprintf_s(L"Facet [");
	wcout.imbue(LocaleSlovak);
	// !!! Vypise SLOVENSKU VERZIU (anglicku), lebo LOCALE vytiahne z 3. PARAMETRA (wcout) na ktorom je uz nastavena SLOVENSKA LOCALE.
	// !!! Vypise hodnotu 12.35, lebo frac_digits()==2.
	Facet.put(wcout,true,wcout,L' ',1234.56);
	wprintf_s(L"] !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test15(void)
{
	locale														LocaleUSA=locale("");
	locale														LocaleSlovak=locale("Slovak_slovakia");
	// !!! Kedze ako DEFAULT ITERATORS sa pouziva 'istreambuf', MUSIM to zmenit na wstring::iterator.
	const money_get<wchar_t>&									FacetGetUSA=use_facet<money_get<wchar_t>>(LocaleUSA);
	const money_get<wchar_t>&									FacetGetSlovak=use_facet<money_get<wchar_t>>(LocaleSlovak);

	long double													ValueUSA=0.0;
	long double													ValueSlovak=0.0;
	ios_base::iostate											StateUSA=0;
	ios_base::iostate											StateSlovak=0;

	basic_stringstream<wchar_t>									StreamUSA;
	basic_stringstream<wchar_t>									StreamSlovak;
	
	const money_put<wchar_t>&									FacetPutUSA=use_facet<money_put<wchar_t>>(LocaleUSA);
	const money_put<wchar_t>&									FacetPutSlovak=use_facet<money_put<wchar_t>>(LocaleSlovak);

	wcout.imbue(LocaleUSA);
	// !!! Vypise DEFAULT VERZIU (anglicku), lebo LOCALE vytiahne z 3. PARAMETRA (wcout) na ktorom je zatial nastaveny DEFAULT.
	FacetPutUSA.put(StreamUSA,false,wcout,L' ',1234.56);

	wcout.imbue(LocaleSlovak);
	// !!! Vypise SLOVENSKU VERZIU (anglicku), lebo LOCALE vytiahne z 3. PARAMETRA (wcout) na ktorom je uz nastavena SLOVENSKA LOCALE.
	FacetPutSlovak.put(StreamSlovak,false,wcout,L' ',1234.56);

	wcin.imbue(LocaleUSA);
	// !!! 4. parameter sluzi iba na to, aby si FACET zo STREAMU vytiahol LOCALE.
	FacetGetUSA.get(basic_istream<wchar_t>::_Iter(StreamUSA.rdbuf()),basic_istream<wchar_t>::_Iter(0),false,wcin,StateUSA,ValueUSA);

	printf_s("ValueUSA: [%f] !\n",ValueUSA);

	wcin.imbue(LocaleSlovak);
	// !!! 4. parameter sluzi iba na to, aby si FACET zo STREAMU vytiahol LOCALE.
	FacetGetSlovak.get(basic_istream<wchar_t>::_Iter(StreamSlovak.rdbuf()),basic_istream<wchar_t>::_Iter(0),false,wcin,StateSlovak,ValueSlovak);

	printf_s("ValueSlovak: [%f] !\n",ValueSlovak);
}
//-------------------------------------------------------------------------------------------------------
void Test16(void)
{
	locale														LocaleUSA=locale("English_USA");
	locale														LocaleSlovak=locale("Slovak_slovakia");

	const time_put<wchar_t>&									FacetPutUSA=use_facet<time_put<wchar_t>>(LocaleUSA);
	const time_put<wchar_t>&									FacetPutSlovak=use_facet<time_put<wchar_t>>(LocaleSlovak);

	tm															Time;
	__time64_t													TimeT;

	_time64(&TimeT); 
	_localtime64_s(&Time,&TimeT);

	wcout.imbue(LocaleUSA);
	wprintf_s(L"Facet [");
	FacetPutUSA.put(wcout,wcout,L' ',&Time,'x');
	wprintf_s(L" ");
	FacetPutUSA.put(wcout,wcout,L' ',&Time,'X');
	wprintf_s(L"] !\n");

	wcout.imbue(LocaleSlovak);
	wprintf_s(L"FacetSlovak [");
	FacetPutSlovak.put(wcout,wcout,L' ',&Time,'x');
	wprintf_s(L" ");
	FacetPutSlovak.put(wcout,wcout,L' ',&Time,'X');
	wprintf_s(L"] !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test17(void)
{
	locale														LocaleUSA=locale("");
	locale														LocaleSlovak=locale("Slovak_slovakia");
	// !!! Kedze ako DEFAULT ITERATORS sa pouziva 'istreambuf', MUSIM to zmenit na wstring::iterator.
	const time_get<wchar_t>&									FacetGetUSA=use_facet<time_get<wchar_t>>(LocaleUSA);
	const time_get<wchar_t>&									FacetGetSlovak=use_facet<time_get<wchar_t>>(LocaleSlovak);
	const time_put<wchar_t>&									FacetPutUSA=use_facet<time_put<wchar_t>>(LocaleUSA);
	const time_put<wchar_t>&									FacetPutSlovak=use_facet<time_put<wchar_t>>(LocaleSlovak);

	tm															Time;
	__time64_t													TimeT;

	_time64(&TimeT); 
	_localtime64_s(&Time,&TimeT);

	basic_stringstream<wchar_t>									StreamUSA;
	basic_stringstream<wchar_t>									StreamSlovak;

	StreamUSA.imbue(LocaleUSA);
	FacetPutUSA.put(StreamUSA,StreamUSA,L' ',&Time,'X');

	StreamSlovak.imbue(LocaleSlovak);
	FacetPutSlovak.put(StreamSlovak,StreamSlovak,L' ',&Time,'X');

	tm															ValueUSA;
	tm															ValueSlovak;
	ios_base::iostate											StateUSA=0;
	ios_base::iostate											StateSlovak=0;

	wcin.imbue(LocaleUSA);
	FacetGetUSA.get_time(basic_istream<wchar_t>::_Iter(StreamUSA.rdbuf()),basic_istream<wchar_t>::_Iter(0),wcin,StateUSA,&ValueUSA);

	wcin.imbue(LocaleSlovak);
	FacetGetSlovak.get_time(basic_istream<wchar_t>::_Iter(StreamSlovak.rdbuf()),basic_istream<wchar_t>::_Iter(0),wcin,StateSlovak,&ValueSlovak);

	wcout.imbue(LocaleUSA);
	wprintf_s(L"Facet [");
	FacetPutUSA.put(wcout,wcout,L' ',&ValueUSA,'X');
	wprintf_s(L"] !\n");

	wcout.imbue(LocaleSlovak);
	wprintf_s(L"FacetSlovak [");
	FacetPutSlovak.put(wcout,wcout,L' ',&ValueSlovak,'X');
	wprintf_s(L"] !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test18(void)
{
	locale														LocaleUSA=locale("");
	locale														LocaleSlovak=locale("Slovak_slovakia");

	const ctype<wchar_t>&										CTypeUSA=use_facet<ctype<wchar_t>>(LocaleUSA);
	const ctype<wchar_t>&										CTypeSlovak=use_facet<ctype<wchar_t>>(LocaleSlovak);

	wprintf_s(L"USA alnum('A') [%d] !\n",CTypeUSA.is(ctype_base::alnum,L'A'));
	wprintf_s(L"Slovak alnum('A') [%d] !\n",CTypeSlovak.is(ctype_base::alnum,L'A'));
	
	wprintf_s(L"USA alnum('}') [%d] !\n",CTypeUSA.is(ctype_base::alnum,L'}'));
	wprintf_s(L"Slovak alnum('}') [%d] !\n",CTypeSlovak.is(ctype_base::alnum,L'}'));

	wprintf_s(L"USA alnum('á') [%d] !\n",CTypeUSA.is(ctype_base::alnum,L'á'));
	wprintf_s(L"Slovak alnum('á') [%d] !\n",CTypeSlovak.is(ctype_base::alnum,L'á'));

	wprintf_s(L"USA alnum('dlhe l') [%d] !\n",CTypeUSA.is(ctype_base::alnum,L'ĺ'));
	wprintf_s(L"Slovak alnum('dlhe l') [%d] !\n",CTypeSlovak.is(ctype_base::alnum,L'ĺ'));

	wprintf_s(L"USA toupper('a') [%c] !\n",CTypeUSA.toupper(L'a'));
	wprintf_s(L"Slovak toupper('a') [%c] !\n",CTypeSlovak.toupper(L'a'));

	// !!!!! Konvertuje CHAR na WCHAR_T.
	wprintf_s(L"USA widen('a') [%c] !\n",CTypeUSA.widen(L'a'));
	wprintf_s(L"Slovak widen('a') [%c] !\n",CTypeSlovak.widen(L'a'));
}
//-------------------------------------------------------------------------------------------------------
void Test19(void)
{
	locale														LocaleUSA=locale("");
	const codecvt<wchar_t,char,mbstate_t>&						FacetUSA=use_facet<codecvt<wchar_t,char,mbstate_t>>(LocaleUSA);

	wchar_t														WCharText[]=L"Timmy Anderson";
	char														CharText[]="Timmy Anderson";
	// !!!!! State1 a State2 MUSIA byt INICIALIZOVANE na 0.
	mbstate_t													State1={0};
	mbstate_t													State2={0};

	wchar_t														WCharTextSize=wcslen(WCharText)+1;
	char														CharTextSize=strlen(CharText)+1;

	wchar_t														WCharTextResult[sizeof(WCharText)+1];
	char														CharTextResult[sizeof(CharText)+1];

	wchar_t*													WCharMiddle1=NULL;
	const char*													CharMiddle1=NULL;
	const wchar_t*												WCharMiddle2=NULL;
	char*														CharMiddle2=NULL;

	codecvt_base::result										Result1;
	codecvt_base::result										Result2;

	Result1=FacetUSA.in(State1,CharText,CharText+CharTextSize,CharMiddle1,WCharTextResult,WCharTextResult+WCharTextSize,WCharMiddle1);
	Result2=FacetUSA.out(State2,WCharText,WCharText+WCharTextSize,WCharMiddle2,CharTextResult,CharTextResult+CharTextSize,CharMiddle2);

	if (Result1==codecvt_base::ok)
	{
		wprintf_s(L"Result1 [%s] !\n",WCharTextResult);
	}
	else
	{
		wprintf_s(L"Result1 ERROR !\n");
	}

	if (Result2==codecvt_base::ok)
	{
		printf_s("Result2 [%s] !\n",CharTextResult);
	}
	else
	{
		printf_s("Result2 ERROR !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test20(void)
{
	locale														LocaleUSA=locale("");
	const messages<wchar_t>&									FacetUSA=use_facet<messages<wchar_t>>(LocaleUSA);

	messages_base::catalog										Catalog=FacetUSA.open("XYZ",LocaleUSA);

	if (Catalog!=-1)
	{
		wprintf_s(L"CATALOG was OPENED !\n");

		FacetUSA.close(Catalog);
	}
	else
	{
		wprintf_s(L"CATALOG was NOT OPENED !\n");
	}
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
	Test20();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------