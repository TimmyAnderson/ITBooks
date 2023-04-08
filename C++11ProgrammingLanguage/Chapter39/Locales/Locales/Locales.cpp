//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <locale>
#include <limits>
#include <ctime>
#include <cstring>
#include "MyDebug.h"
#include "CMyNumPunctByNameFacet.h"
#include "CMyMoneyPunctByNameFacetTrue.h"
#include "CMyMoneyPunctByNameFacetFalse.h"
#include "CMySuperFacet.h"
#include "CMySuperFacetUS.h"
#include "CMySuperFacetSK.h"
//-----------------------------------------------------------------------------
#undef max
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCharTypeSizes(void)
{
	PrintLineSeparator();

	wcout << L"TYPE [char] SIZE [" << sizeof(char) << L"] !" << endl;
	wcout << L"TYPE [signed char] SIZE [" << sizeof(signed char) << L"] !" << endl;
	wcout << L"TYPE [unsigned char] SIZE [" << sizeof(unsigned char) << L"] !" << endl;
	wcout << L"TYPE [char16_t] SIZE [" << sizeof(char16_t) << L"] !" << endl;
	wcout << L"TYPE [char32_t] SIZE [" << sizeof(char32_t) << L"] !" << endl;

	// !!! SIZEOF(wchar_t) vo WINDOWS je 2 BYTES a v LINUX 4 BYTES.
	wcout << L"TYPE [wchar_t] SIZE [" << sizeof(wchar_t) << L"] !" << endl;

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
void TestWidenCharacters(void)
{
	PrintLineSeparator();

	wstringstream												Stream1;

	wcout << L"WIDEN(NEW_LINE) [" << static_cast<int>(Stream1.widen('\n')) << L"] !" << endl;

	wcout << L"NARROW(NEW_LINE) [" << static_cast<int>(Stream1.narrow(Stream1.widen('\n'),'\0')) << L"] !" << endl;
	
	PrintLineSeparator();

	try
	{
#ifdef _MSC_VER
		locale													Locale("en-US");
#else
		locale													Locale("en_US");
#endif
		wstringstream											Stream2;

		Stream2.imbue(Locale);

		wcout << L"WIDEN(NEW_LINE) [" << static_cast<int>(Stream2.widen('\n')) << L"] !" << endl;

		wcout << L"NARROW(NEW_LINE) [" << static_cast<int>(Stream2.narrow(Stream2.widen('\n'),'\0')) << L"] !" << endl;
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();

	try
	{
#ifdef _MSC_VER
		locale													Locale("en-US.utf8");
#else
		locale													Locale("en_US.utf8");
#endif
		wstringstream											Stream3;

		Stream3.imbue(Locale);

		wcout << L"WIDEN(NEW_LINE) [" << static_cast<int>(Stream3.widen('\n')) << L"] !" << endl;

		wcout << L"NARROW(NEW_LINE) [" << static_cast<int>(Stream3.narrow(Stream3.widen('\n'),'\0')) << L"] !" << endl;
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLocaleConstruction(void)
{
	PrintLineSeparator();

	try
	{
		// !!! Pouzije sa C-LOCALE vytvoreny DEFAULT CONSTRUCTOR.
		locale													LocaleC;
		wstringstream											Stream;

		Stream.imbue(LocaleC);

		Stream << 123.456;

		wcout << L"LOCALE C [" << ConvertStringToWideString(Stream.getloc().name()) << L"] - NUMERIC VALUE [" << Stream.str() << L"] !" << endl;
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! Pouzije sa C-LOCALE vytvoreny kopiou volania STATIC METHOD locale::classic().
		locale													LocaleC(locale::classic());
		wstringstream											Stream;

		Stream.imbue(LocaleC);

		Stream << 123.456;

		wcout << L"LOCALE CLASSIC [" << ConvertStringToWideString(Stream.getloc().name()) << L"] - NUMERIC VALUE [" << Stream.str() << L"] !" << endl;
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! Pouzije sa LOCALE, ktory je nastaveny ako DEFAULT v OS.
		locale													LocaleDefault("");
		wstringstream											Stream;

		Stream.imbue(LocaleDefault);

		Stream << 123.456;

		wcout << L"LOCALE DEFAULT [" << ConvertStringToWideString(Stream.getloc().name()) << L"] - NUMERIC VALUE [" << Stream.str() << L"] !" << endl;
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();

	try
	{
#ifdef _MSC_VER
		locale													LocaleSlovak("sk-SK");
#else
		locale													LocaleSlovak("sk_SK.utf8");
#endif

		wstringstream											Stream;

		Stream.imbue(LocaleSlovak);

		Stream << 123.456;

		wcout << L"LOCALE CUSTOM [" << ConvertStringToWideString(Stream.getloc().name()) << L"] - NUMERIC VALUE [" << Stream.str() << L"] !" << endl;
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();

	try
	{
#ifdef _MSC_VER
		locale													LocaleSlovak("sk-SK");
#else
		locale													LocaleSlovak("sk_SK.utf8");
#endif

		// !!!!! Volanim METHOD locale::global() sa nastavi DEFAULT LOCALE na LOCALE, ktory je zaslany do METHOD locale::global().
		locale::global(LocaleSlovak);

		// !!! Pouzije sa LOCALE, ktory bol nastaveny pomocou METHOD locale::global().
		locale													LocaleDefault;
		wstringstream											Stream;

		Stream.imbue(LocaleDefault);

		Stream << 123.456;

		wcout << L"LOCALE DEFAULT (GLOBAL) [" << ConvertStringToWideString(Stream.getloc().name()) << L"] - NUMERIC VALUE [" << Stream.str() << L"] !" << endl;
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void HasFacets(const locale& Locale)
{
	wcout << L"HAS FACET num_get<wchar_t> [" << has_facet<num_get<wchar_t>>(Locale) << L"] !" << endl;
	wcout << L"HAS FACET num_put<wchar_t> [" << has_facet<num_put<wchar_t>>(Locale) << L"] !" << endl;
	wcout << L"HAS FACET numpunct<wchar_t> [" << has_facet<numpunct<wchar_t>>(Locale) << L"] !" << endl;
	wcout << L"HAS FACET money_get<wchar_t> [" << has_facet<money_get<wchar_t>>(Locale) << L"] !" << endl;
	wcout << L"HAS FACET money_put<wchar_t> [" << has_facet<money_put<wchar_t>>(Locale) << L"] !" << endl;
	wcout << L"HAS FACET moneypunct<wchar_t> [" << has_facet<moneypunct<wchar_t>>(Locale) << L"] !" << endl;
	wcout << L"HAS FACET time_get<wchar_t> [" << has_facet<time_get<wchar_t>>(Locale) << L"] !" << endl;
	wcout << L"HAS FACET time_put<wchar_t> [" << has_facet<time_put<wchar_t>>(Locale) << L"] !" << endl;
	wcout << L"HAS FACET ctype<wchar_t> [" << has_facet<ctype<wchar_t>>(Locale) << L"] !" << endl;
	wcout << L"HAS FACET codecvt<wchar_t,wchar_t,char_traits<wchar_t>::state_type> [" << has_facet<codecvt<wchar_t,wchar_t,char_traits<wchar_t>::state_type>>(Locale) << L"] !" << endl;
	wcout << L"HAS FACET collate<wchar_t> [" << has_facet<collate<wchar_t>>(Locale) << L"] !" << endl;
	wcout << L"HAS FACET messages<wchar_t> [" << has_facet<messages<wchar_t>>(Locale) << L"] !" << endl;
}
//-----------------------------------------------------------------------------
// !!! GROUPING obsahuje BINARY VALUES.
wstring GetGroupingString(const string& Grouping)
{
	wstringstream												Stream;

	for(size_t Index=0;Index<Grouping.length();Index++)
	{
		if (Index>0)
		{
			Stream << L" ";
		}

		Stream << int(Grouping[Index]);
	}

	return(Stream.str());
}
//-----------------------------------------------------------------------------
void UseFacets(const locale& Locale)
{
	if (has_facet<num_put<wchar_t>>(Locale)==true)
	{
		const num_put<wchar_t>&									FacetNumPut=use_facet<num_put<wchar_t>>(Locale);
		wstringstream											Stream;

		// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
		Stream << fixed;

		Stream.imbue(Locale);
		
		FacetNumPut.put(Stream,Stream,Stream.fill(),double(123456.789));

		wcout << L"PRINTED NUMERIC VALUE [" << Stream.str() << L"] !" << endl;

		if (has_facet<num_get<wchar_t>>(Locale)==true)
		{
			const num_get<wchar_t>&								FacetNumGet=use_facet<num_get<wchar_t>>(Locale);
			wstringstream										WriteStream;
			double												Value=0;
			ios_base::iostate									Error=ios_base::goodbit;

			// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
			WriteStream << fixed;

			FacetNumGet.get(Stream,{},Stream,Error,Value);
			
			if ((Error & ios_base::badbit)==0 && (Error & ios_base::failbit)==0)
			{
				WriteStream << Value;

				wcout << L"PARSED NUMERIC VALUE [" << WriteStream.str() << L"] !" << endl;
			}
			else
			{
				wcout << L"FACET num_get<wchar_t> FAILED to PARSE !" << endl;
			}
		}
		else
		{
			wcout << L"FACET num_get<wchar_t> is UNSUPPORTED !" << endl;
		}
	}
	else
	{
		wcout << L"FACET num_put<wchar_t> is UNSUPPORTED !" << endl;
	}

	PrintLineSeparator();

	if (has_facet<numpunct<wchar_t>>(Locale)==true)
	{
		const numpunct<wchar_t>&								FacetNumPunct=use_facet<numpunct<wchar_t>>(Locale);

		wcout << L"DECIMAL POINT [" << FacetNumPunct.decimal_point() << L"] !" << endl;
		wcout << L"THOUSANDS SEPARATOR [" << FacetNumPunct.thousands_sep() << L"] !" << endl;
		wcout << L"GROUPING [" << GetGroupingString(FacetNumPunct.grouping()) << L"] !" << endl;
		wcout << L"TRUE NAME [" << FacetNumPunct.truename() << L"] !" << endl;
		wcout << L"FALSE NAME [" << FacetNumPunct.falsename() << L"] !" << endl;
	}
	else
	{
		wcout << L"FACET numpunct<wchar_t> is UNSUPPORTED !" << endl;
	}

	PrintLineSeparator();

	// !!! Pouzitie CUSTOM FACET.
	if (has_facet<CMySuperFacet>(Locale)==true)
	{
		// !!! FACET sa identifikuje podla ID. V tomto pripade je to VALUE [CMySuperFacet::id].
		const CMySuperFacet&									FacetMySuperFacet=use_facet<CMySuperFacet>(Locale);

		wcout << L"YES STRING [" << FacetMySuperFacet.GetYesString() << L"] !" << endl;
		wcout << L"NO STRING [" << FacetMySuperFacet.GetNoString() << L"] !" << endl;
	}
	else
	{
		wcout << L"FACET CMySuperFacet is UNSUPPORTED !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestFacets(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		HasFacets(LocaleC);

		PrintLineSeparator();

		UseFacets(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
#ifdef _MSC_VER
		locale													LocaleSlovak("sk-SK");
#else
		locale													LocaleSlovak("sk_SK.utf8");
#endif

		HasFacets(LocaleSlovak);

		PrintLineSeparator();

		UseFacets(LocaleSlovak);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleCustom(locale(),new CMyNumPunctByNameFacet(locale().name()));

		HasFacets(LocaleCustom);

		PrintLineSeparator();

		UseFacets(LocaleCustom);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		// !!! Pouzije sa CUSTOM FACET pre LOCALE US.
		locale													LocaleCustom(locale(),new CMySuperFacetUS());

		HasFacets(LocaleCustom);

		PrintLineSeparator();

		UseFacets(LocaleCustom);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		// !!! Pouzije sa CUSTOM FACET pre LOCALE SK.
		locale													LocaleCustom(locale(),new CMySuperFacetSK());

		HasFacets(LocaleCustom);

		PrintLineSeparator();

		UseFacets(LocaleCustom);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLocales(void)
{
	PrintLineSeparator();

	try
	{
		locale													Locale1;
		locale													Locale2(locale::classic());

#ifdef _MSC_VER
		locale													Locale3("sk-SK");
#else
		locale													Locale3("sk_SK.utf8");
#endif

		locale													Locale4;

		// !!! FACET [numpunct<wchar_t>] sa zoberie zo SLOVENSKEHO LOCALE.
		Locale4=Locale1.combine<numpunct<wchar_t>>(Locale3);

		wcout << L"LOCALE 1 NAME [" << ConvertStringToWideString(Locale1.name()) << L"] !" << endl;
		wcout << L"LOCALE 2 NAME [" << ConvertStringToWideString(Locale2.name()) << L"] !" << endl;
		wcout << L"LOCALE 3 NAME [" << ConvertStringToWideString(Locale3.name()) << L"] !" << endl;
		wcout << L"LOCALE 4 NAME [" << ConvertStringToWideString(Locale4.name()) << L"] !" << endl;

		PrintLineSeparator();

		if (Locale1==Locale2)
		{
			wcout << L"LOCALE 1 and LOCALE 2 are SAME !" << endl;
		}
		else
		{
			wcout << L"LOCALE 1 and LOCALE 2 are DIFFERENT !" << endl;
		}

		if (Locale1==Locale3)
		{
			wcout << L"LOCALE 1 and LOCALE 3 are SAME !" << endl;
		}
		else
		{
			wcout << L"LOCALE 1 and LOCALE 3 are DIFFERENT !" << endl;
		}

		if (Locale3==Locale4)
		{
			wcout << L"LOCALE 3 and LOCALE 4 are SAME !" << endl;
		}
		else
		{
			wcout << L"LOCALE 3 and LOCALE 4 are DIFFERENT !" << endl;
		}

		if (Locale1!=Locale2)
		{
			wcout << L"LOCALE 1 and LOCALE 2 are DIFFERENT !" << endl;
		}
		else
		{
			wcout << L"LOCALE 1 and LOCALE 2 are SAME !" << endl;
		}

		if (Locale1!=Locale3)
		{
			wcout << L"LOCALE 1 and LOCALE 3 are DIFFERENT !" << endl;
		}
		else
		{
			wcout << L"LOCALE 1 and LOCALE 3 are SAME !" << endl;
		}

		if (Locale3!=Locale4)
		{
			wcout << L"LOCALE 3 and LOCALE 4 are DIFFERENT !" << endl;
		}
		else
		{
			wcout << L"LOCALE 3 and LOCALE 4 are SAME !" << endl;
		}

		PrintLineSeparator();

		// !!! Vracia BOOLEAN VALUE ci 1. PARAMETER je MENSI ako 2. PARAMETER.
		wcout << L"LOCALE 1 COMPARE 'H' and 'CH' [" << Locale1.operator()(wstring(L"H"),wstring(L"CH")) << L"] !" << endl;
		wcout << L"LOCALE 1 COMPARE 'CH' and 'H' [" << Locale1.operator()(wstring(L"CH"),wstring(L"H")) << L"] !" << endl;

		PrintLineSeparator();

		// !!! Vracia BOOLEAN VALUE ci 1. PARAMETER je MENSI ako 2. PARAMETER.
		wcout << L"LOCALE 2 COMPARE 'H' and 'CH' [" << Locale2.operator()(wstring(L"H"),wstring(L"CH")) << L"] !" << endl;
		wcout << L"LOCALE 2 COMPARE 'CH' and 'H' [" << Locale2.operator()(wstring(L"CH"),wstring(L"H")) << L"] !" << endl;

		PrintLineSeparator();

		// !!! Vracia BOOLEAN VALUE ci 1. PARAMETER je MENSI ako 2. PARAMETER.
		// !!!!! V slovencine sa 'CH' sa nachadza v ABECEDE az ZA 'H'.
		wcout << L"LOCALE 3 COMPARE 'H' and 'CH' [" << Locale3.operator()(wstring(L"H"),wstring(L"CH")) << L"] !" << endl;
		wcout << L"LOCALE 3 COMPARE 'CH' and 'H' [" << Locale3.operator()(wstring(L"CH"),wstring(L"H")) << L"] !" << endl;

		PrintLineSeparator();

		// !!! Vracia BOOLEAN VALUE ci 1. PARAMETER je MENSI ako 2. PARAMETER.
		wcout << L"LOCALE 4 COMPARE 'H' and 'CH' [" << Locale4.operator()(wstring(L"H"),wstring(L"CH")) << L"] !" << endl;
		wcout << L"LOCALE 4 COMPARE 'CH' and 'H' [" << Locale4.operator()(wstring(L"CH"),wstring(L"H")) << L"] !" << endl;

		PrintLineSeparator();

		{
			wstringstream										Stream;

			// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
			Stream << fixed;

			Stream.imbue(Locale1);

			Stream << 123456.789;

			wcout << L"LOCALE 1 NUMERIC VALUE [" << Stream.str() << L"] !" << endl;
		}

		PrintLineSeparator();

		{
			wstringstream										Stream;

			// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
			Stream << fixed;

			Stream.imbue(Locale2);

			Stream << 123456.789;

			wcout << L"LOCALE 2 NUMERIC VALUE [" << Stream.str() << L"] !" << endl;
		}

		PrintLineSeparator();

		{
			wstringstream										Stream;

			// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
			Stream << fixed;

			Stream.imbue(Locale3);

			Stream << 123456.789;

			wcout << L"LOCALE 3 NUMERIC VALUE [" << Stream.str() << L"] !" << endl;
		}

		PrintLineSeparator();

		{
			wstringstream										Stream;

			// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
			Stream << fixed;

			Stream.imbue(Locale4);

			// !!! Pouzije sa SLOVENSKE FORMATOVANIE, pretoze LOCALE 4 vzniklo ako COMBINED LOCALE C LOCALE so SLOVENSKYMI ZNAKMI pre vypis NUMERIC VALUES.
			Stream << 123456.789;

			wcout << L"LOCALE 4 NUMERIC VALUE [" << Stream.str() << L"] !" << endl;
		}
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void UseNumPunct(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	if (has_facet<numpunct<wchar_t>>(Locale)==true)
	{
		PrintLineSeparator();

		const numpunct<wchar_t>&								FacetNumPunct=use_facet<numpunct<wchar_t>>(Locale);

		wcout << L"DECIMAL POINT [" << FacetNumPunct.decimal_point() << L"] !" << endl;
		wcout << L"THOUSANDS SEPARATOR [" << FacetNumPunct.thousands_sep() << L"] !" << endl;
		wcout << L"GROUPING [" << GetGroupingString(FacetNumPunct.grouping()) << L"] !" << endl;
		wcout << L"TRUE NAME [" << FacetNumPunct.truename() << L"] !" << endl;
		wcout << L"FALSE NAME [" << FacetNumPunct.falsename() << L"] !" << endl;
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET numpunct<wchar_t> is UNSUPPORTED !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestNumPunct(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseNumPunct(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseNumPunct(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleCustom(locale(),new CMyNumPunctByNameFacet(locale().name()));

		UseNumPunct(LocaleCustom);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void UseNumPut(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	if (has_facet<num_put<wchar_t>>(Locale)==true)
	{
		PrintLineSeparator();

		const num_put<wchar_t>&									FacetNumPut=use_facet<num_put<wchar_t>>(Locale);

		wstringstream											Stream;

		// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
		Stream << fixed;

		Stream.imbue(Locale);

		double													Value=-1234567.89;

		FacetNumPut.put(Stream,Stream,L' ',Value);

		wcout << L"VALUE [" << Stream.str() << L"] !" << endl;
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET num_put<wchar_t> is UNSUPPORTED !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestNumPut(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseNumPut(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseNumPut(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleCustom(locale(),new CMyNumPunctByNameFacet(locale().name()));

		UseNumPut(LocaleCustom);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void UseNumGet(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	if (has_facet<num_put<wchar_t>>(Locale)==true)
	{
		PrintLineSeparator();

		const num_put<wchar_t>&									FacetNumPut=use_facet<num_put<wchar_t>>(Locale);

		wstringstream											Stream;

		// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
		Stream << fixed;

		Stream.imbue(Locale);

		double													Value=-1234567.89;

		FacetNumPut.put(Stream,Stream,L' ',Value);

		wcout << L"VALUE [" << Stream.str() << L"] !" << endl;

		if (has_facet<num_get<wchar_t>>(Locale)==true)
		{
			const num_get<wchar_t>&								FacetNumGet=use_facet<num_get<wchar_t>>(Locale);
			double												ParsedValue=0;
			ios_base::iostate									Error=ios_base::goodbit;

			FacetNumGet.get(Stream,istreambuf_iterator<wchar_t>(),Stream,Error,ParsedValue);

			if ((Error & ios_base::badbit)==0 && (Error & ios_base::failbit)==0)
			{
				wstringstream									OutputStream;

				// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
				OutputStream << fixed;

				// Pouzije sa C LOCALE.
				OutputStream.imbue(locale());

				OutputStream << ParsedValue;

				wcout << L"PARSED VALUE [" << OutputStream.str() << L"] !" << endl;
			}
			else
			{
				wcout << L"FACET num_get<wchar_t> FAILED to PARSE !" << endl;
			}
		}
		else
		{
			wcout << L"FACET num_get<wchar_t> is UNSUPPORTED !" << endl;
		}
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET num_put<wchar_t> is UNSUPPORTED !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestNumGet(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseNumGet(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseNumGet(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleCustom(locale(),new CMyNumPunctByNameFacet(locale().name()));

		UseNumGet(LocaleCustom);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
wstring DumpMoneyPunctPattern(money_base::pattern Pattern)
{
	wstringstream												Stream;

	for(size_t Index=0;Index<4;Index++)
	{
		if (Index>0)
		{
			Stream << L" ";
		}

		char													Part=Pattern.field[Index];

		if (Part==money_base::none)
		{
			Stream << L"NONE";
		}
		else if (Part==money_base::space)
		{
			Stream << L"SPACE";
		}
		else if (Part==money_base::symbol)
		{
			Stream << L"SYMBOL";
		}
		else if (Part==money_base::sign)
		{
			Stream << L"SIGN";
		}
		else if (Part==money_base::value)
		{
			Stream << L"VALUE";
		}
	}

	return(Stream.str());
}
//-----------------------------------------------------------------------------
void UseMoneyPunct(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	if (has_facet<moneypunct<wchar_t,false>>(Locale)==true)
	{
		PrintLineSeparator();

		const moneypunct<wchar_t,false>&						FacetMoneyPunct=use_facet<moneypunct<wchar_t,false>>(Locale);

		wcout << L"DECIMAL POINT [" << FacetMoneyPunct.decimal_point() << L"] !" << endl;
		wcout << L"THOUSANDS SEPARATOR [" << FacetMoneyPunct.thousands_sep() << L"] !" << endl;
		wcout << L"GROUPING [" << GetGroupingString(FacetMoneyPunct.grouping()) << L"] !" << endl;
		wcout << L"CURRENCY SYMBOL [" << FacetMoneyPunct.curr_symbol() << L"] !" << endl;
		wcout << L"POSITIVE SIGN [" << FacetMoneyPunct.positive_sign() << L"] !" << endl;
		wcout << L"NEGATIVE SIGN [" << FacetMoneyPunct.negative_sign() << L"] !" << endl;
		wcout << L"FRACTION DIGITS [" << FacetMoneyPunct.frac_digits() << L"] !" << endl;
		wcout << L"POSITIVE FORMAT [" << DumpMoneyPunctPattern(FacetMoneyPunct.pos_format()) << L"] !" << endl;
		wcout << L"NEGATIVE FORMAT [" << DumpMoneyPunctPattern(FacetMoneyPunct.neg_format()) << L"] !" << endl;
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET moneypunct<wchar_t,false> is UNSUPPORTED !" << endl;
	}

	if (has_facet<moneypunct<wchar_t,true>>(Locale)==true)
	{
		PrintLineSeparator();

		const moneypunct<wchar_t,true>&							FacetMoneyPunct=use_facet<moneypunct<wchar_t,true>>(Locale);

		wcout << L"DECIMAL POINT [" << FacetMoneyPunct.decimal_point() << L"] !" << endl;
		wcout << L"THOUSANDS SEPARATOR [" << FacetMoneyPunct.thousands_sep() << L"] !" << endl;
		wcout << L"GROUPING [" << GetGroupingString(FacetMoneyPunct.grouping()) << L"] !" << endl;
		wcout << L"CURRENCY SYMBOL [" << FacetMoneyPunct.curr_symbol() << L"] !" << endl;
		wcout << L"POSITIVE SIGN [" << FacetMoneyPunct.positive_sign() << L"] !" << endl;
		wcout << L"NEGATIVE SIGN [" << FacetMoneyPunct.negative_sign() << L"] !" << endl;
		wcout << L"FRACTION DIGITS [" << FacetMoneyPunct.frac_digits() << L"] !" << endl;
		wcout << L"POSITIVE FORMAT [" << DumpMoneyPunctPattern(FacetMoneyPunct.pos_format()) << L"] !" << endl;
		wcout << L"NEGATIVE FORMAT [" << DumpMoneyPunctPattern(FacetMoneyPunct.neg_format()) << L"] !" << endl;
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET moneypunct<wchar_t,true> is UNSUPPORTED !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestMoneyPunct(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseMoneyPunct(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseMoneyPunct(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleCustom1(locale(),new CMyMoneyPunctByNameFacetFalse(locale().name()));
		locale													LocaleCustom2(LocaleCustom1,new CMyMoneyPunctByNameFacetTrue(locale().name()));

		UseMoneyPunct(LocaleCustom2);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void UseMoneyPut(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	if (has_facet<money_put<wchar_t>>(Locale)==true)
	{
		PrintLineSeparator();

		const money_put<wchar_t>&								FacetMoneyPut=use_facet<money_put<wchar_t>>(Locale);

		long double												Value=-1234567.89;

		wstringstream											Stream1;

		// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
		Stream1 << fixed;

		// !!!!! Na zobrazenie CURRENCY SYMBOL je NUTNE pouzit MANIPULATOR [showbase].
		Stream1 << showbase;

		Stream1.imbue(Locale);

		FacetMoneyPut.put(Stream1,false,Stream1,L' ',Value);

		wcout << L"VALUE (INTERNATIONALIZATION FALSE) [" << Stream1.str() << L"] !" << endl;

		wstringstream											Stream2;

		// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
		Stream2 << fixed;

		// !!!!! Na zobrazenie CURRENCY SYMBOL je NUTNE pouzit MANIPULATOR [showbase].
		Stream2 << showbase;

		Stream2.imbue(Locale);

		FacetMoneyPut.put(Stream2,true,Stream2,L' ',Value);

		wcout << L"VALUE (INTERNATIONALIZATION TRUE) [" << Stream2.str() << L"] !" << endl;
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET money_put<wchar_t> is UNSUPPORTED !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestMoneyPut(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseMoneyPut(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseMoneyPut(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleCustom1(locale(),new CMyMoneyPunctByNameFacetFalse(locale().name()));
		locale													LocaleCustom2(LocaleCustom1,new CMyMoneyPunctByNameFacetTrue(locale().name()));

		UseMoneyPut(LocaleCustom2);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void UseMoneyGet(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	if (has_facet<money_put<wchar_t>>(Locale)==true)
	{
		PrintLineSeparator();

		const money_put<wchar_t>&								FacetMoneyPut=use_facet<money_put<wchar_t>>(Locale);

		long double												Value=-1234567.89;

		wstringstream											Stream1;

		// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
		Stream1 << fixed;

		// !!!!! Na zobrazenie CURRENCY SYMBOL je NUTNE pouzit MANIPULATOR [showbase].
		Stream1 << showbase;

		Stream1.imbue(Locale);

		FacetMoneyPut.put(Stream1,false,Stream1,L' ',Value);

		wcout << L"VALUE (INTERNATIONALIZATION FALSE) [" << Stream1.str() << L"] !" << endl;

		if (has_facet<money_get<wchar_t>>(Locale)==true)
		{
			const money_get<wchar_t>&							FacetMoneyGet=use_facet<money_get<wchar_t>>(Locale);
			long double											ParsedValue=0;
			ios_base::iostate									Error=ios_base::goodbit;

			FacetMoneyGet.get(Stream1,istreambuf_iterator<wchar_t>(),false,Stream1,Error,ParsedValue);

			if ((Error & ios_base::badbit)==0 && (Error & ios_base::failbit)==0)
			{
				wstringstream									OutputStream;

				// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
				OutputStream << fixed;

				// !!!!! Na zobrazenie CURRENCY SYMBOL je NUTNE pouzit MANIPULATOR [showbase].
				OutputStream << showbase;

				// Pouzije sa C LOCALE.
				OutputStream.imbue(locale());

				OutputStream << ParsedValue;

				wcout << L"PARSED VALUE [" << OutputStream.str() << L"] !" << endl;
			}
			else
			{
				wcout << L"FACET money_get<wchar_t> FAILED to PARSE !" << endl;
			}
		}
		else
		{
			wcout << L"FACET money_get<wchar_t> is UNSUPPORTED !" << endl;
		}

		wstringstream											Stream2;

		// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
		Stream2 << fixed;

		// !!!!! Na zobrazenie CURRENCY SYMBOL je NUTNE pouzit MANIPULATOR [showbase].
		Stream2 << showbase;

		Stream2.imbue(Locale);

		FacetMoneyPut.put(Stream2,true,Stream2,L' ',Value);

		wcout << L"VALUE (INTERNATIONALIZATION TRUE) [" << Stream2.str() << L"] !" << endl;

		if (has_facet<money_get<wchar_t>>(Locale)==true)
		{
			const money_get<wchar_t>&							FacetMoneyGet=use_facet<money_get<wchar_t>>(Locale);
			long double											ParsedValue=0;
			ios_base::iostate									Error=ios_base::goodbit;

			FacetMoneyGet.get(Stream2,istreambuf_iterator<wchar_t>(),true,Stream2,Error,ParsedValue);

			if ((Error & ios_base::badbit)==0 && (Error & ios_base::failbit)==0)
			{
				wstringstream									OutputStream;

				// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
				OutputStream << fixed;

				// !!!!! Na zobrazenie CURRENCY SYMBOL je NUTNE pouzit MANIPULATOR [showbase].
				OutputStream << showbase;

				// Pouzije sa C LOCALE.
				OutputStream.imbue(locale());

				OutputStream << ParsedValue;

				wcout << L"PARSED VALUE [" << OutputStream.str() << L"] !" << endl;
			}
			else
			{
				wcout << L"FACET money_get<wchar_t> FAILED to PARSE !" << endl;
			}
		}
		else
		{
			wcout << L"FACET money_get<wchar_t> is UNSUPPORTED !" << endl;
		}
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET money_put<wchar_t> is UNSUPPORTED !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestMoneyGet(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseMoneyGet(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseMoneyGet(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleCustom1(locale(),new CMyMoneyPunctByNameFacetFalse(locale().name()));
		locale													LocaleCustom2(LocaleCustom1,new CMyMoneyPunctByNameFacetTrue(locale().name()));

		UseMoneyGet(LocaleCustom2);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void UseMoneyManipulators(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	PrintLineSeparator();

	long double													Value=-1234567.89;
	wstringstream												Stream1;

	// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
	Stream1 << fixed;

	// !!!!! Na zobrazenie CURRENCY SYMBOL je NUTNE pouzit MANIPULATOR [showbase].
	Stream1 << showbase;

	Stream1.imbue(Locale);

	Stream1 << put_money(Value,false);

	wcout << L"VALUE (INTERNATIONALIZATION FALSE) [" << Stream1.str() << L"] !" << endl;

	long double													ParsedValue1=0;

	Stream1 >> get_money(ParsedValue1,false);

	if (Stream1.operator bool()==true)
	{
		wstringstream											OutputStream;

		// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
		OutputStream << fixed;

		// !!!!! Na zobrazenie CURRENCY SYMBOL je NUTNE pouzit MANIPULATOR [showbase].
		OutputStream << showbase;

		// Pouzije sa C LOCALE.
		OutputStream.imbue(locale());

		OutputStream << ParsedValue1;

		wcout << L"PARSED VALUE (INTERNATIONALIZATION FALSE) [" << OutputStream.str() << L"] !" << endl;
	}
	else
	{
		wcout << L"MANIPULATOR FAILED to PARSE !" << endl;
	}

	PrintLineSeparator();

	wstringstream												Stream2;

	// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
	Stream2 << fixed;

	// !!!!! Na zobrazenie CURRENCY SYMBOL je NUTNE pouzit MANIPULATOR [showbase].
	Stream2 << showbase;

	Stream2.imbue(Locale);

	Stream2 << put_money(Value,true);

	wcout << L"VALUE (INTERNATIONALIZATION TRUE) [" << Stream2.str() << L"] !" << endl;

	long double													ParsedValue2=0;

	Stream2 >> get_money(ParsedValue2,true);

	if (Stream2.operator bool()==true)
	{
		wstringstream											OutputStream;

		// !!!!! Kedze sa zapisuje FLOATING POINT VALUE, je nutne nastavit STREAM na pracu s FLOATING POINT VALUES.
		OutputStream << fixed;

		// !!!!! Na zobrazenie CURRENCY SYMBOL je NUTNE pouzit MANIPULATOR [showbase].
		OutputStream << showbase;

		// Pouzije sa C LOCALE.
		OutputStream.imbue(locale());

		OutputStream << ParsedValue2;

		wcout << L"PARSED VALUE (INTERNATIONALIZATION TRUE) [" << OutputStream.str() << L"] !" << endl;
	}
	else
	{
		wcout << L"MANIPULATOR FAILED to PARSE !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestMoneyManipulators(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseMoneyManipulators(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseMoneyManipulators(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleCustom1(locale(),new CMyMoneyPunctByNameFacetFalse(locale().name()));
		locale													LocaleCustom2(LocaleCustom1,new CMyMoneyPunctByNameFacetTrue(locale().name()));

		UseMoneyManipulators(LocaleCustom2);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void UseTimePut(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	wstring														Format(L"%A %x %I%p");

	if (has_facet<time_put<wchar_t>>(Locale)==true)
	{
		PrintLineSeparator();

		tm														Value;

		memset(&Value,0,sizeof(Value));

		Value.tm_isdst=true;
		Value.tm_year=2018;
		Value.tm_yday=281;
		Value.tm_mon=9;
		Value.tm_wday=1;
		Value.tm_mday=8;
		Value.tm_hour=10;
		Value.tm_min=30;
		Value.tm_sec=15;

		const time_put<wchar_t>&								FacetTimePut=use_facet<time_put<wchar_t>>(Locale);

		wstringstream											Stream1;

		Stream1.imbue(Locale);

		FacetTimePut.put(Stream1,Stream1,L' ',&Value,Format.c_str(),Format.c_str()+Format.size());

		wcout << L"VALUE [" << Stream1.str() << L"] !" << endl;

		wstringstream											Stream2;

		Stream2.imbue(Locale);

		FacetTimePut.put(Stream2,Stream2,L' ',&Value,'x');

		wcout << L"VALUE [" << Stream2.str() << L"] !" << endl;
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET time_put<wchar_t> is UNSUPPORTED !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestTimePut(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseTimePut(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseTimePut(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void UseTimeGet(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	wstring														Format(L"%A %x %I%p");

	if (has_facet<time_put<wchar_t>>(Locale)==true)
	{
		PrintLineSeparator();

		tm														Value;

		memset(&Value,0,sizeof(Value));

		Value.tm_isdst=true;
		Value.tm_year=2018;
		Value.tm_yday=281;
		Value.tm_mon=9;
		Value.tm_wday=1;
		Value.tm_mday=8;
		Value.tm_hour=10;
		Value.tm_min=30;
		Value.tm_sec=15;

		const time_put<wchar_t>&								FacetTimePut=use_facet<time_put<wchar_t>>(Locale);

		wstringstream											Stream1;

		Stream1.imbue(Locale);

		FacetTimePut.put(Stream1,Stream1,L' ',&Value,Format.c_str(),Format.c_str()+Format.size());

		wcout << L"VALUE [" << Stream1.str() << L"] !" << endl;

		if (has_facet<time_get<wchar_t>>(Locale)==true)
		{
			const time_get<wchar_t>&							FacetTimeGet=use_facet<time_get<wchar_t>>(Locale);
			tm													ParsedValue;
			ios_base::iostate									Error=ios_base::goodbit;

			memset(&ParsedValue,0,sizeof(ParsedValue));

			FacetTimeGet.get(Stream1,istreambuf_iterator<wchar_t>(),Stream1,Error,&ParsedValue,Format.c_str(),Format.c_str()+Format.size());

			if ((Error & ios_base::badbit)==0 && (Error & ios_base::failbit)==0)
			{
				wstringstream									OutputStream;

				// Pouzije sa C LOCALE.
				OutputStream.imbue(locale());

				FacetTimePut.put(OutputStream,OutputStream,L' ',&ParsedValue,'x');

				wcout << L"PARSED VALUE [" << OutputStream.str() << L"] !" << endl;
			}
			else
			{
				wcout << L"FACET time_get<wchar_t> FAILED to PARSE !" << endl;
			}
		}
		else
		{
			wcout << L"FACET time_get<wchar_t> is UNSUPPORTED !" << endl;
		}

		PrintLineSeparator();

		wstringstream											Stream2;

		Stream2.imbue(Locale);

		FacetTimePut.put(Stream2,Stream2,L' ',&Value,'x');

		wcout << L"VALUE [" << Stream2.str() << L"] !" << endl;

		if (has_facet<time_get<wchar_t>>(Locale)==true)
		{
			const time_get<wchar_t>&							FacetTimeGet=use_facet<time_get<wchar_t>>(Locale);
			tm													ParsedValue;
			ios_base::iostate									Error=ios_base::goodbit;

			memset(&ParsedValue,0,sizeof(ParsedValue));

			FacetTimeGet.get(Stream2,istreambuf_iterator<wchar_t>(),Stream2,Error,&ParsedValue,'x');

			if ((Error & ios_base::badbit)==0 && (Error & ios_base::failbit)==0)
			{
				wstringstream									OutputStream;

				// Pouzije sa C LOCALE.
				OutputStream.imbue(locale());

				FacetTimePut.put(OutputStream,OutputStream,L' ',&ParsedValue,'x');

				wcout << L"PARSED VALUE [" << OutputStream.str() << L"] !" << endl;
			}
			else
			{
				wcout << L"FACET time_get<wchar_t> FAILED to PARSE !" << endl;
			}
		}
		else
		{
			wcout << L"FACET time_get<wchar_t> is UNSUPPORTED !" << endl;
		}
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET time_put<wchar_t> is UNSUPPORTED !" << endl;
	}

	if (has_facet<time_get<wchar_t>>(Locale)==true)
	{
		PrintLineSeparator();

		const time_get<wchar_t>&								FacetTimeGet=use_facet<time_get<wchar_t>>(Locale);

		time_base::dateorder									DateOrder=FacetTimeGet.date_order();

		if (DateOrder==time_base::no_order)
		{
			wcout << L"DATE ORDER [NO ORDER] !" << endl;
		}
		else if (DateOrder==time_base::dmy)
		{
			wcout << L"DATE ORDER [DMY] !" << endl;
		}
		else if (DateOrder==time_base::mdy)
		{
			wcout << L"DATE ORDER [MDY] !" << endl;
		}
		else if (DateOrder==time_base::ymd)
		{
			wcout << L"DATE ORDER [YMD] !" << endl;
		}
		else if (DateOrder==time_base::ydm)
		{
			wcout << L"DATE ORDER [YDM] !" << endl;
		}
	}
}
//-----------------------------------------------------------------------------
void TestTimeGet(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseTimeGet(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseTimeGet(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void UseTimeManipulators(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	PrintLineSeparator();

	tm															Value;

	memset(&Value,0,sizeof(Value));

	Value.tm_isdst=true;
	Value.tm_year=2018;
	Value.tm_yday=281;
	Value.tm_mon=9;
	Value.tm_wday=1;
	Value.tm_mday=8;
	Value.tm_hour=10;
	Value.tm_min=30;
	Value.tm_sec=15;

	wstringstream												Stream;

	Stream.imbue(Locale);

	Stream << put_time(&Value,L"%x");

	wcout << L"VALUE [" << Stream.str() << L"] !" << endl;

	tm															ParsedValue;

	memset(&ParsedValue,0,sizeof(ParsedValue));

	Stream >> get_time(&ParsedValue,L"%x");

	if (Stream.operator bool()==true)
	{
		wstringstream											OutputStream;

		// Pouzije sa C LOCALE.
		OutputStream.imbue(locale());

		OutputStream << put_time(&Value,L"%x");

		wcout << L"PARSED VALUE [" << OutputStream.str() << L"] !" << endl;
	}
	else
	{
		wcout << L"MANIPULATOR FAILED to PARSE !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestTimeManipulators(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseTimeManipulators(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseTimeManipulators(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
string ToString(const wstring& Value, const ctype<wchar_t>& FacetCType)
{
	string														Result;

	for(wchar_t WideChar : Value)
	{
		// !!! Konvertuje WIDE CHARACTER na CHARACTER, pricom sa pouzije CHARACTER '?', ake CONVERSION ZLYHA.
		char													Char=FacetCType.narrow(WideChar,'?');

		Result.push_back(Char);
	}

	return(Result);
}
//-----------------------------------------------------------------------------
wstring ToWideString(const string& Value, const ctype<wchar_t>& FacetCType)
{
	wstring														Result;

	for(char Char : Value)
	{
		// !!! Konvertuje CHARACTER na WIDE CHARACTER.
		wchar_t													WideChar=FacetCType.widen(Char);

		Result.push_back(WideChar);
	}

	return(Result);
}
//-----------------------------------------------------------------------------
wstring ToLower(const wstring& Value, const ctype<wchar_t>& FacetCType)
{
	wstring														Result;

	for(wchar_t Char : Value)
	{
		wchar_t													ConvertedChar=FacetCType.tolower(Char);

		Result.push_back(ConvertedChar);
	}

	return(Result);
}
//-----------------------------------------------------------------------------
wstring ToUpper(const wstring& Value, const ctype<wchar_t>& FacetCType)
{
	wstring														Result;

	for(wchar_t Char : Value)
	{
		wchar_t													ConvertedChar=FacetCType.toupper(Char);

		Result.push_back(ConvertedChar);
	}

	return(Result);
}
//-----------------------------------------------------------------------------
wstring CharacterType(wchar_t Value, const ctype<wchar_t>& FacetCType)
{
	wstring														Result;

	if (FacetCType.is(ctype_base::space,Value)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"SPACE";
	}

	if (FacetCType.is(ctype_base::print,Value)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"PRINT";
	}

	if (FacetCType.is(ctype_base::cntrl,Value)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"CONTROL";
	}

	if (FacetCType.is(ctype_base::upper,Value)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"UPPER";
	}

	if (FacetCType.is(ctype_base::lower,Value)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"LOWER";
	}

	if (FacetCType.is(ctype_base::alpha,Value)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"ALPHA";
	}

	if (FacetCType.is(ctype_base::digit,Value)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"DIGIT";
	}

	if (FacetCType.is(ctype_base::punct,Value)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"PUNCTUATION";
	}

	if (FacetCType.is(ctype_base::xdigit,Value)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"HEXADECIMAL_DIGIT";
	}

	if (FacetCType.is(ctype_base::blank,Value)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"BLANK";
	}

	if (FacetCType.is(ctype_base::alnum,Value)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"ALPHA_NUMERIC";
	}

	if (FacetCType.is(ctype_base::graph,Value)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"GRAPHICAL";
	}

	return(Result);
}
//-----------------------------------------------------------------------------
wstring CharacterType(ctype_base::mask Mask)
{
	wstring														Result;

	if ((Mask & ctype_base::space)!=0)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"SPACE";
	}

	if ((Mask & ctype_base::print)!=0)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"PRINT";
	}

	if ((Mask & ctype_base::cntrl)!=0)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"CONTROL";
	}

	if ((Mask & ctype_base::upper)!=0)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"UPPER";
	}

	if ((Mask & ctype_base::lower)!=0)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"LOWER";
	}

	if ((Mask & ctype_base::alpha)!=0)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"ALPHA";
	}

	if ((Mask & ctype_base::digit)!=0)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"DIGIT";
	}

	if ((Mask & ctype_base::punct)!=0)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"PUNCTUATION";
	}

	if ((Mask & ctype_base::xdigit)!=0)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"HEXADECIMAL_DIGIT";
	}

	if ((Mask & ctype_base::blank)!=0)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"BLANK";
	}

	if ((Mask & ctype_base::alnum)!=0)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"ALPHA_NUMERIC";
	}

	if ((Mask & ctype_base::graph)!=0)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"GRAPHICAL";
	}

	return(Result);
}
//-----------------------------------------------------------------------------
void UseCType(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	if (has_facet<ctype<wchar_t>>(Locale)==true)
	{
		PrintLineSeparator();

		const ctype<wchar_t>&									FacetCType=use_facet<ctype<wchar_t>>(Locale);

		wcout << L"TO STRING [" << ConvertStringToWideString(ToString(L"Timmy Anderson",FacetCType)) << L"] !" << endl;

		wcout << L"TO WIDE STRING [" << ToWideString("Timmy Anderson",FacetCType) << L"] !" << endl;

		wcout << L"TO LOWER [" << ToLower(L"Timmy Anderson",FacetCType) << L"] !" << endl;
		
		wcout << L"TO UPPER [" << ToUpper(L"Timmy Anderson",FacetCType) << L"] !" << endl;

		wstring													Text(L"Timmy Anderson");
		const wchar_t*											Begin=Text.c_str();
		const wchar_t*											End=Text.c_str()+Text.length();
		const wchar_t*											SpacePosition=FacetCType.scan_is(ctype_base::space,Begin,End);

		if (SpacePosition!=End)
		{
			wcout << L"SPACE CHARACTER FOUND at POSITION [" << (SpacePosition-Begin) << L"] !" << endl;
		}
		else
		{
			wcout << L"SPACE CHARACTER NOT FOUND !" << endl;
		}

		const wchar_t*											NonLetter=FacetCType.scan_not(ctype_base::alpha,Begin,End);

		if (SpacePosition!=End)
		{
			wcout << L"NON LETTER FOUND at POSITION [" << (NonLetter-Begin) << L"] !" << endl;
		}
		else
		{
			wcout << L"NON LETTER CHARACTER NOT FOUND !" << endl;
		}

		wcout << L"CHARACTER 'a' IS [" << CharacterType(L'a',FacetCType) << L"] !" << endl;
		wcout << L"CHARACTER 'A' IS [" << CharacterType(L'A',FacetCType) << L"] !" << endl;
		wcout << L"CHARACTER '1' IS [" << CharacterType(L'1',FacetCType) << L"] !" << endl;
		wcout << L"CHARACTER '.' IS [" << CharacterType(L'.',FacetCType) << L"] !" << endl;
		wcout << L"CHARACTER 'NEW LINE' IS [" << CharacterType(L'\n',FacetCType) << L"] !" << endl;
		wcout << L"CHARACTER '0x03' IS [" << CharacterType(L'\3',FacetCType) << L"] !" << endl;
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET ctype<wchar_t> is UNSUPPORTED !" << endl;
	}

	if (has_facet<ctype<char>>(Locale)==true)
	{
		PrintLineSeparator();

		const ctype<char>&										FacetCType=use_facet<ctype<char>>(Locale);

		wcout << L"CHARACTER TABLE SIZE [" << ctype<char>::table_size << L"] !" << endl;

		wcout << L"CHARACTER 'a' IS [" << CharacterType(FacetCType.classic_table()['a']) << L"] !" << endl;
		wcout << L"CHARACTER ' ' IS [" << CharacterType(FacetCType.classic_table()[' ']) << L"] !" << endl;
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET ctype<char> is UNSUPPORTED !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestCType(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseCType(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseCType(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
wstring CharacterTypeByFunctions(wchar_t Value, const locale& Locale)
{
	wstring														Result;
	
	if (isspace(Value,Locale)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"SPACE";
	}

	if (isprint(Value,Locale)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"PRINT";
	}

	if (iscntrl(Value,Locale)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"CONTROL";
	}

	if (isupper(Value,Locale)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"UPPER";
	}

	if (islower(Value,Locale)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"LOWER";
	}

	if (isalpha(Value,Locale)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"ALPHA";
	}

	if (isdigit(Value,Locale)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"DIGIT";
	}

	if (ispunct(Value,Locale)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"PUNCTUATION";
	}

	if (isxdigit(Value,Locale)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"HEXADECIMAL_DIGIT";
	}

	if (isblank(Value,Locale)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"BLANK";
	}

	if (isalnum(Value,Locale)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"ALPHA_NUMERIC";
	}

	if (isgraph(Value,Locale)==true)
	{
		if (Result.length()>0)
		{
			Result+=L' ';
		}

		Result+=L"GRAPHICAL";
	}

	return(Result);
}
//-----------------------------------------------------------------------------
void UseCTypeHelperFunctions(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"CHARACTER 'a' IS [" << CharacterTypeByFunctions(L'a',Locale) << L"] !" << endl;
	wcout << L"CHARACTER 'A' IS [" << CharacterTypeByFunctions(L'A',Locale) << L"] !" << endl;
	wcout << L"CHARACTER '1' IS [" << CharacterTypeByFunctions(L'1',Locale) << L"] !" << endl;
	wcout << L"CHARACTER '.' IS [" << CharacterTypeByFunctions(L'.',Locale) << L"] !" << endl;
	wcout << L"CHARACTER 'NEW LINE' IS [" << CharacterTypeByFunctions(L'\n',Locale) << L"] !" << endl;
	wcout << L"CHARACTER '0x03' IS [" << CharacterTypeByFunctions(L'\3',Locale) << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestCTypeHelperFunctions(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseCTypeHelperFunctions(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseCTypeHelperFunctions(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void UseCodeCvt(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	if (has_facet<codecvt<wchar_t,char,mbstate_t>>(Locale)==true)
	{
		PrintLineSeparator();

		const codecvt<wchar_t,char,mbstate_t>&					FacetCodeCvt=use_facet<codecvt<wchar_t,char,mbstate_t>>(Locale);

		wcout << L"MAX LENGTH IS [" << FacetCodeCvt.max_length() << L"] !" << endl;
		wcout << L"ALWAYS CONVERT [" << FacetCodeCvt.always_noconv() << L"] !" << endl;
		wcout << L"ENCODING [" << FacetCodeCvt.encoding() << L"] !" << endl;

		{
			string												SourceString("Timmy Anderson");
			const char*											StartSourceString=SourceString.c_str();
			const char*											EndSourceString=SourceString.c_str()+SourceString.length();
			int													DestinationStringLength=0;

			{
				mbstate_t										State=mbstate_t();

				DestinationStringLength=FacetCodeCvt.length(State,StartSourceString,EndSourceString,numeric_limits<size_t>::max());

				wcout << L"CONVERTED WIDE STRING LENGTH will be have [" << DestinationStringLength << L"] CHARACTERS !" << endl;
			}
		}

		PrintLineSeparator();

		{
			string												SourceString("Timmy Anderson");
			const char*											StartSourceString=SourceString.c_str();
			const char*											EndSourceString=SourceString.c_str()+SourceString.length();

			// !!! DESTINATION LENGTH v CHARACTERS je rovny SIZE SOURCE LENGTH.
			size_t												DestinationLengthInBytes=SourceString.size();
			wstring												DestinationString(DestinationLengthInBytes,L'\0');
			mbstate_t											State=mbstate_t();
			wchar_t*											StartDestinationString=&DestinationString[0];
			wchar_t*											EndDestinationString=&DestinationString[DestinationString.size()];
			const char*											MiddleSourceString=nullptr;
			wchar_t*											MiddleDestinationString=nullptr;

			codecvt_base::result								Result=FacetCodeCvt.in(State,StartSourceString,EndSourceString,MiddleSourceString,StartDestinationString,EndDestinationString,MiddleDestinationString);
			wstring												ConversionResult;

			if (Result==codecvt_base::ok)
			{
				ConversionResult=L"OK";
			}
			else if (Result==codecvt_base::partial)
			{
				ConversionResult=L"PARTIAL";
			}
			else if (Result==codecvt_base::noconv)
			{
				ConversionResult=L"NO CONVERSION";
			}
			else if (Result==codecvt_base::error)
			{
				ConversionResult=L"ERROR";
			}

			wstring												SourceMiddleResult;

			if (MiddleSourceString==EndSourceString)
			{
				SourceMiddleResult=L"FULL";
			}
			else
			{
				size_t											Difference=(EndSourceString-MiddleSourceString);
				wstringstream									Stream;

				Stream << Difference;

				SourceMiddleResult+=Stream.str();
			}

			wstring												DestinationMiddleResult;

			if (MiddleDestinationString==EndDestinationString)
			{
				DestinationMiddleResult=L"FULL";
			}
			else
			{
				size_t											Difference=(EndDestinationString-MiddleDestinationString);
				wstringstream									Stream;

				Stream << Difference;

				DestinationMiddleResult+=Stream.str();

				// !!! Kedze sa NEPOUZIL CELY BUFFER, je nutne odstranit prebytocne CHARACTERS.
				size_t											SizeToCrop=(MiddleDestinationString-StartDestinationString);

				DestinationString.resize(SizeToCrop);
			}

			wcout << L"CONVERSION STRING to WIDE STRING [" << ConversionResult << L"] - VALUE [" << DestinationString << L"] SOURCE MIDDLE DIFFERENCE [" << SourceMiddleResult << L"] DESTINATION MIDDLE DIFFERENCE [" << DestinationMiddleResult << L"] !" << endl;
		}

		PrintLineSeparator();

		{
			wstring												SourceString(L"Timmy Anderson");
			const wchar_t*										StartSourceString=SourceString.c_str();
			const wchar_t*										EndSourceString=SourceString.c_str()+SourceString.length();

			// !!! Na vypocet DESTINATION LENGTH v BYTES je nutne SIZE SOURCE LENGTH vynasobit MAX LENGTH.
			size_t												DestinationLengthInBytes=SourceString.size()*FacetCodeCvt.max_length();
			string												DestinationString(DestinationLengthInBytes,L'\0');
			mbstate_t											State=mbstate_t();
			char*												StartDestinationString=&DestinationString[0];
			char*												EndDestinationString=&DestinationString[DestinationString.size()];
			const wchar_t*										MiddleSourceString=nullptr;
			char*												MiddleDestinationString=nullptr;

			codecvt_base::result								Result=FacetCodeCvt.out(State,StartSourceString,EndSourceString,MiddleSourceString,StartDestinationString,EndDestinationString,MiddleDestinationString);
			wstring												ConversionResult;

			if (Result==codecvt_base::ok)
			{
				ConversionResult=L"OK";
			}
			else if (Result==codecvt_base::partial)
			{
				ConversionResult=L"PARTIAL";
			}
			else if (Result==codecvt_base::noconv)
			{
				ConversionResult=L"NO CONVERSION";
			}
			else if (Result==codecvt_base::error)
			{
				ConversionResult=L"ERROR";
			}

			wstring												SourceMiddleResult;

			if (MiddleSourceString==EndSourceString)
			{
				SourceMiddleResult=L"FULL";
			}
			else
			{
				size_t											Difference=(EndSourceString-MiddleSourceString);
				wstringstream									Stream;

				Stream << Difference;

				SourceMiddleResult+=Stream.str();
			}

			wstring												DestinationMiddleResult;

			if (MiddleDestinationString==EndDestinationString)
			{
				DestinationMiddleResult=L"FULL";
			}
			else
			{
				size_t											Difference=(EndDestinationString-MiddleDestinationString);
				wstringstream									Stream;

				Stream << Difference;

				DestinationMiddleResult+=Stream.str();

				// !!! Kedze sa NEPOUZIL CELY BUFFER, je nutne odstranit prebytocne CHARACTERS.
				size_t											SizeToCrop=(MiddleDestinationString-StartDestinationString);

				DestinationString.resize(SizeToCrop);
			}

			wcout << L"CONVERSION WIDE STRING to STRING [" << ConversionResult << L"] - VALUE [" << ConvertStringToWideString(DestinationString) << L"] SOURCE MIDDLE DIFFERENCE [" << SourceMiddleResult << L"] DESTINATION MIDDLE DIFFERENCE [" << DestinationMiddleResult << L"] !" << endl;
		}
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET codecvt<wchar_t,char,mbstate_t> is UNSUPPORTED !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestCodeCvt(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseCodeCvt(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseCodeCvt(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
wstring ToNumericValue(const wstring& Value)
{
	wstring														Result;

	for(wchar_t Char : Value)
	{
		wstringstream											Stream;

		Stream << static_cast<size_t>(Char);

		if (Result.empty()==false)
		{
			Result+=L" ";
		}

		Result+=Stream.str();
	}

	return(Result);
}
//-----------------------------------------------------------------------------
void UseCollate(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	if (has_facet<collate<wchar_t>>(Locale)==true)
	{
		PrintLineSeparator();

		const collate<wchar_t>&									FacetCollate=use_facet<collate<wchar_t>>(Locale);

		wstring													String1(L"H");
		wstring													String2(L"CH");
		const wchar_t*											StartString1=String1.c_str();
		const wchar_t*											EndString1=String1.c_str()+String1.size();
		const wchar_t*											StartString2=String2.c_str();
		const wchar_t*											EndString2=String2.c_str()+String2.size();

		wcout << L"COMPARE [" << String1 << L"] and [" << String2 << L"] [" << FacetCollate.compare(StartString1,EndString1,StartString2,EndString2) << L"] !" << endl;
		wcout << L"COMPARE [" << String2 << L"] and [" << String1 << L"] [" << FacetCollate.compare(StartString2,EndString2,StartString1,EndString1) << L"] !" << endl;

		PrintLineSeparator();

		wcout << L"STRING [" << String1 << L"] is TRANSFORMED to [" << ToNumericValue(FacetCollate.transform(StartString1,EndString1)) << L"] !" << endl;
		wcout << L"STRING [" << String2 << L"] is TRANSFORMED to [" << ToNumericValue(FacetCollate.transform(StartString2,EndString2)) << L"] !" << endl;

		PrintLineSeparator();

		wcout << L"STRING [" << String1 << L"] is HASHED to [" << FacetCollate.hash(StartString1,EndString1) << L"] !" << endl;
		wcout << L"STRING [" << String2 << L"] is HASHED to [" << FacetCollate.hash(StartString2,EndString2) << L"] !" << endl;
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET collate<wchar_t> is UNSUPPORTED !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestCollate(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseCollate(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseCollate(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
#ifdef _MSC_VER
		locale													LocaleSlovak("sk-SK");
#else
		locale													LocaleSlovak("sk_SK.utf8");
#endif

		UseCollate(LocaleSlovak);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void UseMessages(const locale& Locale)
{
	wcout << L"LOCALE [" << ConvertStringToWideString(Locale.name()) << L"] !" << endl;

	if (has_facet<messages<char>>(Locale)==true)
	{
		PrintLineSeparator();

		const messages<char>&									FacetMessages=use_facet<messages<char>>(Locale);

		// !!! V LINUXE sa SUBOR nachadza v PATH [/usr/share/locale/sk/LC_MESSAGES/xed.mo].
		string													CatalogName("xed");
		messages_base::catalog									Catalog=FacetMessages.open(CatalogName,Locale);

		if (Catalog>0)
		{
			messages<char>::string_type							String1("Installed: ");

			wcout << L"MESSAGE [" << ConvertStringToWideString(String1) << L"] is [" << ConvertStringToWideString(FacetMessages.get(Catalog,0,0,String1)) << L"] !" << endl;

			messages<char>::string_type							String2("Missing: ");

			wcout << L"MESSAGE [" << ConvertStringToWideString(String2) << L"] is [" << ConvertStringToWideString(FacetMessages.get(Catalog,0,0,String2)) << L"] !" << endl;

			FacetMessages.close(Catalog);
		}
		else
		{
			wcout << L"CATALOG [" << ConvertStringToWideString(CatalogName) << L"] NOT FOUND !" << endl;
		}
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET messages<char> is UNSUPPORTED !" << endl;
	}

	if (has_facet<messages<wchar_t>>(Locale)==true)
	{
		PrintLineSeparator();

		const messages<wchar_t>&								FacetMessages=use_facet<messages<wchar_t>>(Locale);

		// !!! V LINUXE sa SUBOR nachadza v PATH [/usr/share/locale/sk/LC_MESSAGES/xed.mo].
		string													CatalogName("xed");
		messages_base::catalog									Catalog=FacetMessages.open(CatalogName,Locale);

		if (Catalog>0)
		{
			messages<wchar_t>::string_type						String1(L"Installed: ");

			wcout << L"MESSAGE [" << String1 << L"] is [" << FacetMessages.get(Catalog,0,0,String1) << L"] !" << endl;

			messages<wchar_t>::string_type						String2(L"Missing: ");

			wcout << L"MESSAGE [" << String2 << L"] is [" << FacetMessages.get(Catalog,0,0,String2) << L"] !" << endl;

			FacetMessages.close(Catalog);
		}
		else
		{
			wcout << L"CATALOG [" << ConvertStringToWideString(CatalogName) << L"] NOT FOUND !" << endl;
		}
	}
	else
	{
		PrintLineSeparator();

		wcout << L"FACET messages<wchar_t> is UNSUPPORTED !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestMessages(void)
{
	PrintLineSeparator();

	try
	{
		locale													LocaleC;

		UseMessages(LocaleC);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		locale													LocaleGlobal("");

		UseMessages(LocaleGlobal);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
#ifdef _MSC_VER
		locale													LocaleSlovak("sk-SK");
#else
		locale													LocaleSlovak("sk_SK.utf8");
#endif

		UseMessages(LocaleSlovak);
	}
	catch(const runtime_error&)
	{
		wcout << L"UNSUPPORTED LOCALE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestCharTypeSizes();
	//TestCharacterTraits();
	//TestWidenCharacters();
	//TestLocaleConstruction();
	TestFacets();
	//TestLocales();
	//TestNumPunct();
	//TestNumPut();
	//TestNumGet();
	//TestMoneyPunct();
	//TestMoneyPut();
	//TestMoneyGet();
	//TestMoneyManipulators();
	//TestTimePut();
	//TestTimeGet();
	//TestTimeManipulators();
	//TestCType();
	//TestCTypeHelperFunctions();
	//TestCodeCvt();
	//TestCollate();
	//TestMessages();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------