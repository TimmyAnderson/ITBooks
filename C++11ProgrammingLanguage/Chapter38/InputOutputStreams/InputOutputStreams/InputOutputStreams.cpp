//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <memory>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ios>
#include <cstring>
#include <locale>
#include <fstream>
#include <iterator>
#include "MyDebug.h"
#include "CustomManipulators.h"
#include "CCustomManipulatorWriteNCharacters.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename TCharacter>
wstring GetStreamState(const basic_ios<TCharacter,char_traits<TCharacter>>& Stream)
{
	wstring														Value;

	if (Stream.good()==true)
	{
		Value+=L"GOOD";
	}

	if (Stream.eof()==true)
	{
		if (Value.empty()==false)
		{
			Value+=L" | ";
		}

		Value+=L"EOF";
	}

	// !!! Kedze METHOD fail() vracia TRUE, ak je nastaveny BUD BIT [ios_base::failbit], alebo BIT [ios_base::badbit], na zistenie ci je BIT [ios_base::failbit] nastaveny je nutne testovat ci METHOD Stream.bad() NEVRACIA TRUE.
	if (Stream.fail()==true && Stream.bad()==false)
	{
		if (Value.empty()==false)
		{
			Value+=L" | ";
		}

		Value+=L"FAIL";
	}

	if (Stream.bad()==true)
	{
		if (Value.empty()==false)
		{
			Value+=L" | ";
		}

		Value+=L"BAD";
	}

	return(Value);
}
//-----------------------------------------------------------------------------
template <typename TCharacter>
wstring GetStreamPositions(basic_iostream<TCharacter,char_traits<TCharacter>>& Stream)
{
	wstringstream												Value;

	Value << L"(";

	Value << Stream.tellg();

	Value << L",";

	Value << Stream.tellp();

	Value << L")";

	return(Value.str());
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSimpleOperations(void)
{
	PrintLineSeparator();

	try
	{
		wstringstream											StringStream(L"100 200");
		int														Value1;
		int														Value2;

		StringStream >> Value1;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 1 FAILED !"));
		}

		StringStream >> Value2;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 2 FAILED !"));
		}

		wcout << L"RESULT [" << (Value1+Value2) << L"] !" << endl;
	}
	catch(const wstring& E)
	{
		wcout << L"READ FAILED with EXCEPTION [" << E.c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		wstringstream											StringStream(L"ABC 200");
		int														Value1;
		int														Value2;

		StringStream >> Value1;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 1 FAILED !"));
		}

		StringStream >> Value2;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 2 FAILED !"));
		}

		wcout << L"RESULT [" << (Value1+Value2) << L"] !" << endl;
	}
	catch(const wstring& E)
	{
		wcout << L"READ FAILED with EXCEPTION [" << E.c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		wstringstream											StringStream(L"100 ABC");
		int														Value1;
		int														Value2;

		StringStream >> Value1;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 1 FAILED !"));
		}

		StringStream >> Value2;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 2 FAILED !"));
		}

		wcout << L"RESULT [" << (Value1+Value2) << L"] !" << endl;
	}
	catch(const wstring& E)
	{
		wcout << L"READ FAILED with EXCEPTION [" << E.c_str() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInputOutputOperators(void)
{
	PrintLineSeparator();

	try
	{
		wstringstream											StringStream;

		StringStream << 100;
		StringStream << L" ";
		StringStream << 200;

		int														Value1;
		int														Value2;

		StringStream >> Value1;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 1 FAILED !"));
		}

		StringStream >> Value2;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 2 FAILED !"));
		}

		wcout << L"RESULT [" << (Value1+Value2) << L"] !" << endl;
	}
	catch(const wstring& E)
	{
		wcout << L"READ FAILED with EXCEPTION [" << E.c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		wstringstream											StringStream;

		StringStream << L"ABC";
		StringStream << L" ";
		StringStream << 200;

		int														Value1;
		int														Value2;

		StringStream >> Value1;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 1 FAILED !"));
		}

		StringStream >> Value2;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 2 FAILED !"));
		}

		wcout << L"RESULT [" << (Value1+Value2) << L"] !" << endl;
	}
	catch(const wstring& E)
	{
		wcout << L"READ FAILED with EXCEPTION [" << E.c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		wstringstream											StringStream;

		StringStream << 100;
		StringStream << L" ";
		StringStream << L"ABC";

		int														Value1;
		int														Value2;

		StringStream >> Value1;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 1 FAILED !"));
		}

		StringStream >> Value2;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 2 FAILED !"));
		}

		wcout << L"RESULT [" << (Value1+Value2) << L"] !" << endl;
	}
	catch(const wstring& E)
	{
		wcout << L"READ FAILED with EXCEPTION [" << E.c_str() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStreamStates(void)
{
	PrintLineSeparator();

	wstringstream												StringStream;
	
	wcout << L"STATE AFTER CREATE [" << GetStreamState(StringStream) << L"] POSITIONS [" << GetStreamPositions(StringStream) << L"] !" << endl;

	StringStream << 1000;

	wcout << L"STATE AFTER WRITE [" << GetStreamState(StringStream) << L"] POSITIONS [" << GetStreamPositions(StringStream) << L"] !" << endl;

	int															IntValue;

	StringStream >> IntValue;

	wcout << L"STATE AFTER SUCCESSFULL READ [" << GetStreamState(StringStream) << L"] POSITIONS [" << GetStreamPositions(StringStream) << L"] VALUE [" << IntValue << L"] !" << endl;

	StringStream >> IntValue;

	wcout << L"STATE AFTER EOF REACHED [" << GetStreamState(StringStream) << L"] POSITIONS [" << GetStreamPositions(StringStream) << L"] !" << endl;

	StringStream << 1000;

	// !!! Zapis ZLYHA, pretoze STREAM je vo FAILED STATE.
	wcout << L"STATE AFTER WRITE [" << GetStreamState(StringStream) << L"] POSITIONS [" << GetStreamPositions(StringStream) << L"] !" << endl;

	StringStream.clear();

	wcout << L"STATE AFTER CLEAR [" << GetStreamState(StringStream) << L"] POSITIONS [" << GetStreamPositions(StringStream) << L"] !" << endl;

	StringStream << L"AAA";

	wstring														StringValue;

	/*
	StringStream >> StringValue;

	wcout << L"STATE AFTER SUCCESSFULL READ [" << GetStreamState(StringStream) << L"] POSITIONS [" << GetStreamPositions(StringStream) << L"] VALUE [" << StringValue << L"] !" << endl;
	*/

	wcout << L"STATE AFTER WRITE [" << GetStreamState(StringStream) << L"] POSITIONS [" << GetStreamPositions(StringStream) << L"] !" << endl;

	StringStream >> IntValue;

	wcout << L"STATE AFTER FAILED READ [" << GetStreamState(StringStream) << L"] POSITIONS [" << GetStreamPositions(StringStream) << L"] VALUE [" << IntValue << L"] !" << endl;

	StringStream >> StringValue;

	// !!! Citanie ZLYHA, pretoze STREAM je vo FAILED STATE.
	wcout << L"STATE AFTER FAILED READ [" << GetStreamState(StringStream) << L"] POSITIONS [" << GetStreamPositions(StringStream) << L"] VALUE [" << StringValue << L"] !" << endl;

	StringStream.clear();

	StringStream >> StringValue;

	// !!! Data sa nacitaju a zaroven sa nastavi EOF a FAIL BITS, pretoze sa dosiahol koniec STREAMU.
	wcout << L"STATE AFTER SUCCESSFULL READ [" << GetStreamState(StringStream) << L"] POSITIONS [" << GetStreamPositions(StringStream) << L"] VALUE [" << StringValue << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStreamTestOperators(void)
{
	PrintLineSeparator();

	wstringstream												StringStream;

	wcout << L"AFTER CREATE - OPERATOR BOOL() [" << StringStream.operator bool() << L"] !" << endl;
	wcout << L"AFTER CREATE - OPERATOR !() [" << StringStream.operator!() << L"] !" << endl;

	int															Value;

	// Sposobi ERROR.
	StringStream >> Value;

	wcout << L"AFTER ERROR - OPERATOR BOOL() [" << StringStream.operator bool() << L"] VALUE [" << Value << L"] !" << endl;
	wcout << L"AFTER ERROR - OPERATOR !() [" << StringStream.operator!() << L"] VALUE [" << Value << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStreamExceptions1(void)
{
	PrintLineSeparator();

	wstringstream												StringStream;

	StringStream.exceptions(ios::failbit | ios::badbit);

	try
	{
		StringStream << L"ABC";

		int														Value;

		// !!! Hodi EXCEPTION.
		StringStream >> Value;

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}
	catch(const ios_base::failure& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	try
	{
		// !!! Aj METHOD exceptions() hodi EXCEPTION, pretoze C++ STATE [ios_base::failbit] bol uz nastaveny.
		StringStream.exceptions(ios::failbit | ios::badbit);
	}
	catch(const ios_base::failure& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStreamExceptions2(void)
{
	PrintLineSeparator();

	wstringstream												StringStream;

	StringStream.exceptions(ios::failbit | ios::badbit);

	try
	{
		int														Value;

		// !!! Hodi EXCEPTION, pretoze bol detekovany END OF FILE.
		StringStream >> Value;

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}
	catch(const ios_base::failure& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattedIOOperations(void)
{
	PrintLineSeparator();

	wstringstream												StringStream;

	// !!! OPERATOR<< reprezentuje FORMATTED OUTPUT OPERATION.
	StringStream << 100;

	int															Value;

	// !!! OPERATOR>> reprezentuje FORMATTED INPUT OPERATION.
	StringStream >> Value;

	wcout << L"VALUE [" << Value << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnformattedIOOperationsPutGet(void)
{
	PrintLineSeparator();

	wstringstream												StringStream;

	StringStream.put('A');

	wstringstream::traits_type::int_type						Value1=StringStream.get();

	if (Value1!=wstringstream::traits_type::eof())
	{
		wcout << L"CHARACTER [" << Value1 << L"] READ from STREAM !" << endl;
	}
	else
	{
		wcout << L"END OF FILE REACHED !" << endl;
	}

	wstringstream::traits_type::int_type						Value2=StringStream.get();

	if (Value2!=wstringstream::traits_type::eof())
	{
		wcout << L"CHARACTER [" << Value2 << L"] READ from STREAM !" << endl;
	}
	else
	{
		wcout << L"END OF FILE REACHED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnformattedIOOperationsWriteGet(void)
{
	PrintLineSeparator();

	wstringstream												StringStream;

	// Zapise 3 CHARACTERS.
	StringStream.write(L"ABCDE",3);

	wchar_t														Value;

	StringStream.get(Value);

	if (StringStream.operator bool()==true)
	{
		wcout << L"CHARACTER [" << Value << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"END OF FILE REACHED !" << endl;
	}

	wchar_t														Buffer[100];
	streamsize													BufferSize=(sizeof(Buffer)/sizeof(wchar_t));

	memset(Buffer,0,sizeof(Buffer));

	StringStream.get(Buffer,BufferSize);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"END OF FILE REACHED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnformattedIOOperationsWriteGetGetLine(void)
{
	PrintLineSeparator();

	wstring														Text(L"ABCDE!FGHIJK!LMN!OPQRTS");
	wstringstream												StringStream;

	StringStream.write(Text.c_str(),Text.length());

	wchar_t														Buffer1[3];
	streamsize													Buffer1Size=(sizeof(Buffer1)/sizeof(wchar_t));

	memset(Buffer1,0,sizeof(Buffer1));

	// !!! Nacitaju sa 3 CHARACTERS, pretoze BUFFER je dlhy 3 CHARACTERS. 2 CHARACTERS su nacitane CHARACTERS a 3. CHARACTER je CHARACTER '\0'.
	// !!! METHOD UKLADA CHARACTER '\0' na KONIEC BUFFER.
	StringStream.get(Buffer1,Buffer1Size,L'!');

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer1 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"READ OPERATION FAILED !" << endl;
	}

	wchar_t														Buffer2[100];
	streamsize													Buffer2Size=(sizeof(Buffer2)/sizeof(wchar_t));

	memset(Buffer2,0,sizeof(Buffer2));

	// !!! Nacitaju sa CHARACTERS az po vyskyt DELIMITER, pricom vsak DELIMITER NIE JE SUCASTOU BUFFER.
	// !!! METHOD UKLADA CHARACTER '\0' na KONIEC BUFFER.
	// !!!!! DELIMITER NIE JE NACITANY zo STREAMU.
	StringStream.get(Buffer2,Buffer2Size,L'!');

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"READ OPERATION FAILED !" << endl;
	}

	wchar_t														Buffer3[100];
	streamsize													Buffer3Size=(sizeof(Buffer3)/sizeof(wchar_t));

	memset(Buffer3,0,sizeof(Buffer3));

	// !!!!! Nacita sa DELIMITER, pretoze DELIMITER NEBOL predchadzajucim volanim METHOD get() vytiahnuty zo STREAM.
	// !!! METHOD UKLADA CHARACTER '\0' na KONIEC BUFFER.
	StringStream.getline(Buffer3,Buffer3Size,L'!');

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer3 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"READ OPERATION FAILED !" << endl;
	}

	wchar_t														Buffer4[100];
	streamsize													Buffer4Size=(sizeof(Buffer4)/sizeof(wchar_t));

	memset(Buffer4,0,sizeof(Buffer4));

	// !!! Nacitaju sa CHARACTERS az po vyskyt DELIMITER, pricom DELIMITER JE SUCASTOU BUFFER.
	// !!! METHOD UKLADA CHARACTER '\0' na KONIEC BUFFER.
	StringStream.getline(Buffer4,Buffer4Size,L'!');

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer4 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"READ OPERATION FAILED !" << endl;
	}

	wchar_t														Buffer5[100];
	streamsize													Buffer5Size=(sizeof(Buffer5)/sizeof(wchar_t));

	memset(Buffer5,0,sizeof(Buffer5));

	// !!! Nacitaju sa CHARACTERS az po vyskyt DELIMITER, pricom DELIMITER JE SUCASTOU BUFFER.
	// !!! METHOD UKLADA CHARACTER '\0' na KONIEC BUFFER.
	StringStream.getline(Buffer5,Buffer5Size,L'!');

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer5 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"READ OPERATION FAILED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnformattedIOOperationsWriteRead(void)
{
	PrintLineSeparator();

	wstring														Text(L"ABCDE!FGHIJK!LMN!OPQRTS");
	wstringstream												StringStream;

	StringStream.write(Text.c_str(),Text.length());

	wchar_t														Buffer1[3];
	streamsize													Buffer1Size=(sizeof(Buffer1)/sizeof(wchar_t));

	memset(Buffer1,0,sizeof(Buffer1));

	// !!! Nacitaju sa 2 CHARACTERS. METHOD read() NEUKLADA CHARACTER '\0' na koniec BUFFER.
	StringStream.read(Buffer1,Buffer1Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer1 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"READ OPERATION FAILED !" << endl;
	}

	wchar_t														Buffer2[100];
	streamsize													Buffer2Size=(sizeof(Buffer2)/sizeof(wchar_t));

	memset(Buffer2,0,sizeof(Buffer2));

	// !!! Nacitaju sa CHARACTERS az po vyskyt EOF.
	StringStream.read(Buffer2,Buffer2Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"END OF FILE OCCURED - DATA [" << Buffer2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnformattedIOOperationsWriteReadSomeFlush(void)
{
	PrintLineSeparator();

	wstring														Text(L"ABCDE!FGHIJK!LMN!OPQRTS");
	wstringstream												StringStream;

	StringStream.write(Text.c_str(),Text.length());

	wcout << L"CHARACTERS in READ BUFFER [" << StringStream.rdbuf()->in_avail() << L"] !" << endl;

	wchar_t														Buffer1[3];
	streamsize													Buffer1Size=(sizeof(Buffer1)/sizeof(wchar_t));

	memset(Buffer1,0,sizeof(Buffer1));

	// !!! Pocet nacitanych CHARACTERS je IMPLEMENTATION SPECIFIC.
	StringStream.readsome(Buffer1,Buffer1Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer1 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"READ OPERATION FAILED !" << endl;
	}

	wchar_t														Buffer2[100];
	streamsize													Buffer2Size=(sizeof(Buffer2)/sizeof(wchar_t));

	memset(Buffer2,0,sizeof(Buffer2));

	// !!! Pocet nacitanych CHARACTERS je IMPLEMENTATION SPECIFIC.
	StringStream.readsome(Buffer2,Buffer2Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"END OF FILE OCCURED - DATA [" << Buffer2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}

	// !!! NEOVPLYVNI pocet CHARACTERS nacitanych pomocou METHOD readsome().
	StringStream.flush();

	wcout << L"CHARACTERS in READ BUFFER [" << StringStream.rdbuf()->in_avail() << L"] !" << endl;

	wchar_t														Buffer3[100];
	streamsize													Buffer3Size=(sizeof(Buffer3)/sizeof(wchar_t));

	memset(Buffer3,0,sizeof(Buffer3));

	// !!! Pocet nacitanych CHARACTERS je IMPLEMENTATION SPECIFIC.
	StringStream.readsome(Buffer3,Buffer3Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer3 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"END OF FILE OCCURED - DATA [" << Buffer3 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnformattedIOOperationsWriteReadIgnore(void)
{
	PrintLineSeparator();

	wstring														Text(L"ABCDEFGHIJK!LMN!OPQRTS");
	wstringstream												StringStream;

	StringStream.write(Text.c_str(),Text.length());

	// !!! Preskoci 2 CHARACTERS.
	StringStream.ignore(2,L'!');

	wchar_t														Buffer1[3];
	streamsize													Buffer1Size=(sizeof(Buffer1)/sizeof(wchar_t));

	memset(Buffer1,0,sizeof(Buffer1));

	// !!! Nacitaju sa 2 CHARACTERS. METHOD read() NEUKLADA CHARACTER '\0' na koniec BUFFER.
	StringStream.read(Buffer1,Buffer1Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer1 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"READ OPERATION FAILED !" << endl;
	}

	// !!! Preskoci CHARACTERS az po vyskyt DELIMITER CHARACTER.
	StringStream.ignore(100,L'!');

	wchar_t														Buffer2[100];
	streamsize													Buffer2Size=(sizeof(Buffer2)/sizeof(wchar_t));

	memset(Buffer2,0,sizeof(Buffer2));

	// !!! Nacitaju sa CHARACTERS az po vyskyt EOF.
	StringStream.read(Buffer2,Buffer2Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"END OF FILE OCCURED - DATA [" << Buffer2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnformattedIOOperationsWriteReadPeak(void)
{
	PrintLineSeparator();

	wstring														Text(L"ABCDEFGHIJK!LMN!OPQRTS");
	wstringstream												StringStream;

	StringStream.write(Text.c_str(),Text.length());

	wcout << L"PEEK VALUE [" << StringStream.peek() << L"] from STREAM !" << endl;

	wchar_t														Buffer1[3];
	streamsize													Buffer1Size=(sizeof(Buffer1)/sizeof(wchar_t));

	memset(Buffer1,0,sizeof(Buffer1));

	// !!! Nacitaju sa 2 CHARACTERS. METHOD read() NEUKLADA CHARACTER '\0' na koniec BUFFER.
	StringStream.read(Buffer1,Buffer1Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer1 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"READ OPERATION FAILED !" << endl;
	}

	wcout << L"PEEK VALUE [" << StringStream.peek() << L"] from STREAM !" << endl;

	wchar_t														Buffer2[100];
	streamsize													Buffer2Size=(sizeof(Buffer2)/sizeof(wchar_t));

	memset(Buffer2,0,sizeof(Buffer2));

	// !!! Nacitaju sa CHARACTERS az po vyskyt EOF.
	StringStream.read(Buffer2,Buffer2Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"END OF FILE OCCURED - DATA [" << Buffer2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnformattedIOOperationsWriteReadUnget(void)
{
	PrintLineSeparator();

	wstring														Text(L"ABCDE!FGHIJK!LMN!OPQRTS");
	wstringstream												StringStream;

	StringStream.write(Text.c_str(),Text.length());

	wchar_t														Buffer1[3];
	streamsize													Buffer1Size=(sizeof(Buffer1)/sizeof(wchar_t));

	memset(Buffer1,0,sizeof(Buffer1));

	// !!! Nacitaju sa 2 CHARACTERS. METHOD read() NEUKLADA CHARACTER '\0' na koniec BUFFER.
	StringStream.read(Buffer1,Buffer1Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer1 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"READ OPERATION FAILED !" << endl;
	}

	// !!! Vrati CHARACTER do STREAM.
	StringStream.unget();

	wchar_t														Buffer2[100];
	streamsize													Buffer2Size=(sizeof(Buffer2)/sizeof(wchar_t));

	memset(Buffer2,0,sizeof(Buffer2));

	// !!! Nacitaju sa CHARACTERS az po vyskyt EOF.
	StringStream.read(Buffer2,Buffer2Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"END OF FILE OCCURED - DATA [" << Buffer2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnformattedIOOperationsWriteReadPutback(void)
{
	PrintLineSeparator();

	wstring														Text(L"ABCDE!FGHIJK!LMN!OPQRTS");
	wstringstream												StringStream;

	StringStream.write(Text.c_str(),Text.length());

	wchar_t														Buffer1[3];
	streamsize													Buffer1Size=(sizeof(Buffer1)/sizeof(wchar_t));

	memset(Buffer1,0,sizeof(Buffer1));

	// !!! Nacitaju sa 2 CHARACTERS. METHOD read() NEUKLADA CHARACTER '\0' na koniec BUFFER.
	StringStream.read(Buffer1,Buffer1Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer1 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"READ OPERATION FAILED !" << endl;
	}

	// !!! Vrati CHARACTER do STREAM, ktory je INDETICKY s POSLEDNYM NACITANYM CHARACTER.
	StringStream.putback(L'B');

	wchar_t														Buffer2[10];
	streamsize													Buffer2Size=(sizeof(Buffer2)/sizeof(wchar_t));

	memset(Buffer2,0,sizeof(Buffer2));

	// !!! Nacita sa 9 CHARACTERS.
	StringStream.read(Buffer2,Buffer2Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"END OF FILE OCCURED - DATA [" << Buffer2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}

	// !!!!! Vrati CHARACTER do STREAM, ktory NIE je INDETICKY s POSLEDNYM NACITANYM CHARACTER.
	StringStream.putback(L'+');

	wchar_t														Buffer3[5];
	streamsize													Buffer3Size=(sizeof(Buffer3)/sizeof(wchar_t));

	memset(Buffer3,0,sizeof(Buffer3));

	// !!! Nacita sa 4 CHARACTERS.
	StringStream.read(Buffer3,Buffer3Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer3 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"END OF FILE OCCURED - DATA [" << Buffer3 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}

	wchar_t														Buffer5[100];
	streamsize													Buffer5Size=(sizeof(Buffer5)/sizeof(wchar_t));

	memset(Buffer5,0,sizeof(Buffer5));

	// !!! Nacitaju sa CHARACTERS az po vyskyt EOF.
	StringStream.read(Buffer5,Buffer5Size-1);

	if (StringStream.operator bool()==true)
	{
		wcout << L"DATA [" << Buffer5 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}
	else
	{
		wcout << L"END OF FILE OCCURED - DATA [" << Buffer5 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStreamBuffers(void)
{
	PrintLineSeparator();

	wstring														Text(L"   ABCDE");
	wstringbuf   												StringBuffer;
	std::streamsize												NumberOfCharactersWritten=StringBuffer.sputn(Text.c_str(),Text.length());

	wcout << L"NUMBER of CHARACTERS WRITTEN [" << NumberOfCharactersWritten << L"] !" << endl;

	wchar_t														Buffer[100];
	streamsize													BufferSize=((sizeof(Buffer)/sizeof(wchar_t))-1);

	memset(Buffer,0,sizeof(Buffer));

	std::streamsize												NumberOfCharactersRead=StringBuffer.sgetn(Buffer,BufferSize);

	wcout << L"NUMBER of CHARACTERS READ [" << NumberOfCharactersRead << L"] !" << endl;

	wcout << L"DATA [" << Buffer << L"] READ from STREAM BUFFER !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSentries(void)
{
	PrintLineSeparator();

	wstring														Text(L"   ABCDE");
	wstringstream												StringStream;

	StringStream.write(Text.c_str(),Text.length());

	{
		wchar_t													Buffer[100];
		streamsize												BufferSize=(sizeof(Buffer)/sizeof(wchar_t));

		memset(Buffer,0,sizeof(Buffer));

		StringStream.get(Buffer,BufferSize);

		if (StringStream.operator bool()==true)
		{
			wcout << L"DATA [" << Buffer << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
		}
		else
		{
			wcout << L"READ OPERATION FAILED !" << endl;
		}
	}

	StringStream.seekg(0);

	PrintLineSeparator();

	{
		wchar_t													Buffer[100];
		streamsize												BufferSize=(sizeof(Buffer)/sizeof(wchar_t));

		memset(Buffer,0,sizeof(Buffer));

		// !!! Preskakovanie WHITE CHARACTERS sposbilo, ze sa NENACITALI UVODNE 3 SPACES.
		wistringstream::sentry									Sentry(StringStream,false);
		{
			StringStream.get(Buffer,BufferSize);
		}

		if (StringStream.operator bool()==true)
		{
			wcout << L"DATA [" << Buffer << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
		}
		else
		{
			wcout << L"READ OPERATION FAILED !" << endl;
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestManipulators(void)
{
	PrintLineSeparator();

	// Standardne pouzitie MANIPULATOR.
	wcout << L"SOME TEXT !" << endl;

	// Volanie MANIPULATOR pomocou FUNCTION SYNTAX.
	// !!! MANIPULATOR sa APLIKUJE na [wcout].
	hex(wcout);

	// Volanie MANIPULATOR pomocou FUNCTION SYNTAX.
	// !!!!! Kedze volanie MANIPULATOR NIE JE ASOCIOVANE so ZIADNYM STREAM, NEAPLIKUJE sa na [wcout].
	void(setprecision(5));

	wcout << L"SOME HEXADECIMAL VALUE [" << 100 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TCharacter, typename TTraits>
basic_ostream<TCharacter,TTraits>& CustomManipulatorWrite10Dashes(basic_ostream<TCharacter,TTraits>& Stream)
{
	for(int Index=0;Index<10;Index++)
	{
		Stream.put(L'-');
	}

	return(Stream);
}
//-----------------------------------------------------------------------------
void TestCustomManipulators(void)
{
	PrintLineSeparator();

	wcout << L"BEFORE MANIPULATOR !";

	// !!! Vola sa BEZPARAMETRICKY CUSTOM MANIPULATOR.
	wcout << CustomManipulatorWrite10Dashes;

	wcout << L"AFTER MANIPULATOR !" << endl;

	PrintLineSeparator();

	wcout << L"BEFORE MANIPULATOR !";

	// !!! Vola sa PARAMETRICKY CUSTOM MANIPULATOR.
	wcout << CCustomManipulatorWriteNCharacters(20,L'+');

	wcout << L"AFTER MANIPULATOR !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingFlags(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		StringStream << 100;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
		wcout << L"STREAM FLAGS [" << StringStream.flags() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		StringStream.setf(ios::hex,ios::basefield);

		StringStream << 100;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
		wcout << L"STREAM FLAGS [" << StringStream.flags() << L"] !" << endl;

		StringStream << L" ";

		StringStream.unsetf(ios::hex);

		StringStream << 100;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
		wcout << L"STREAM FLAGS [" << StringStream.flags() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream1;

		StringStream1.setf(ios::hex,ios::basefield);

		StringStream1 << 100;

		wcout << L"STREAM CONTENT [" << StringStream1.str() << L"] !" << endl;
		wcout << L"STREAM FLAGS [" << StringStream1.flags() << L"] !" << endl;

		wstringstream											StringStream2;

		// Skopiruje FLAGS z ineho STREAM.
		StringStream2.copyfmt(StringStream1);

		StringStream2 << 100;

		wcout << L"STREAM CONTENT [" << StringStream2.str() << L"] !" << endl;
		wcout << L"STREAM FLAGS [" << StringStream2.flags() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Odstranenie a nastavenie FLAGS pomocou MANIPULATOR.
		StringStream  << resetiosflags(ios::dec) << setiosflags(ios::hex) << 100;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
		wcout << L"STREAM FLAGS [" << StringStream.flags() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingBoolAlphaNoBoolAlpha(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie BOOL ALPHA pomocou FLAGS.
		StringStream.setf(ios::boolalpha);

		StringStream << true;
		StringStream << L" ";
		StringStream << false;

		// Vypnutie BOOL ALPHA pomocou FLAGS.
		StringStream.unsetf(ios::boolalpha);

		StringStream << L" ";
		StringStream << true;
		StringStream << L" ";
		StringStream << false;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		bool													Value1;
		bool													Value2;
		bool													Value3;
		bool													Value4;

		// Nastavenie BOOL ALPHA pomocou FLAGS.
		StringStream.setf(ios::boolalpha);

		StringStream >> Value1;
		StringStream >> Value2;

		// Vypnutie BOOL ALPHA pomocou FLAGS.
		StringStream.unsetf(ios::boolalpha);

		StringStream >> Value3;
		StringStream >> Value4;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
		wcout << L"VALUE 3 [" << Value3 << L"] !" << endl;
		wcout << L"VALUE 4 [" << Value4 << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie BOOL ALPHA pomocou MANIPULATOR.
		StringStream << boolalpha;

		StringStream << true;
		StringStream << L" ";
		StringStream << false;

		// Nastavenie NO BOOL ALPHA pomocou MANIPULATOR.
		StringStream << noboolalpha;

		StringStream << L" ";
		StringStream << true;
		StringStream << L" ";
		StringStream << false;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		bool													Value1;
		bool													Value2;
		bool													Value3;
		bool													Value4;

		// Nastavenie BOOL ALPHA pomocou MANIPULATOR.
		StringStream << boolalpha;

		StringStream >> Value1;
		StringStream >> Value2;

		// Nastavenie NO BOOL ALPHA pomocou MANIPULATOR.
		StringStream << noboolalpha;

		StringStream >> Value3;
		StringStream >> Value4;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
		wcout << L"VALUE 3 [" << Value3 << L"] !" << endl;
		wcout << L"VALUE 4 [" << Value4 << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingWidthFill(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie WIDTH pomocou METHOD CALL.
		StringStream.width(10);
		// Nastavenie FILL pomocou METHOD CALL.
		StringStream.fill(L'_');

		StringStream << 123;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		StringStream << L" ";

		// !!!!! Platnost WIDTH konci po vykonani prvej OUTPUT OPERATION.
		StringStream << 500;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie WIDTH pomocou MANIPULATOR.
		StringStream << setw(10);
		// Nastavenie FILL pomocou MANIPULATOR.
		StringStream << setfill(L'_');

		StringStream << 123;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		StringStream << L" ";

		// !!!!! Platnost WIDTH konci po vykonani prvej OUTPUT OPERATION.
		StringStream << 500;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		StringStream << L"0123456789";

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		// BUFFER je dlhy iba 5 CHARACTERS.
		wchar_t													Buffer[5];

		// !!!!! WIDTH pri citani CHAR ARRAYS zo STREAM urcuje MAXIMALNY pocet CHARACTERS MINUS 1, ktore sa nacitaju zo STREAM.
		StringStream.width(sizeof(Buffer)/sizeof(wchar_t));

		// !!! NULL CHARACTER je AUTOMATICKY vlozeny na koniec BUFFER.
		StringStream >> Buffer;

		wcout << L"BUFFER [" << Buffer << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingLeft(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie WIDTH pomocou METHOD CALL.
		StringStream.width(10);
		// Nastavenie FILL pomocou METHOD CALL.
		StringStream.fill(L'_');
		// Nastavenie LEFT pomocou METHOD CALL.
		StringStream.setf(ios_base::left,ios_base::adjustfield);

		StringStream << -123.15;

		StringStream << L" ";

		// !!!!! Platnost WIDTH konci po vykonani prvej OUTPUT OPERATION.
		StringStream << -123.15;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie WIDTH pomocou MANIPULATOR.
		StringStream << setw(10);
		// Nastavenie FILL pomocou MANIPULATOR.
		StringStream << setfill(L'_');
		// Nastavenie LEFT pomocou MANIPULATOR.
		StringStream << left;

		StringStream << -123.15;

		StringStream << L" ";

		// !!!!! Platnost WIDTH konci po vykonani prvej OUTPUT OPERATION.
		StringStream << -123.15;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingRight(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie WIDTH pomocou METHOD CALL.
		StringStream.width(10);
		// Nastavenie FILL pomocou METHOD CALL.
		StringStream.fill(L'_');
		// Nastavenie RIGHT pomocou METHOD CALL.
		StringStream.setf(ios_base::right,ios_base::adjustfield);

		StringStream << -123.15;

		StringStream << L" ";

		// !!!!! Platnost WIDTH konci po vykonani prvej OUTPUT OPERATION.
		StringStream << -123.15;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie WIDTH pomocou MANIPULATOR.
		StringStream << setw(10);
		// Nastavenie FILL pomocou MANIPULATOR.
		StringStream << setfill(L'_');
		// Nastavenie RIGHT pomocou MANIPULATOR.
		StringStream << right;

		StringStream << -123.15;

		StringStream << L" ";

		// !!!!! Platnost WIDTH konci po vykonani prvej OUTPUT OPERATION.
		StringStream << -123.15;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingInternal(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie WIDTH pomocou METHOD CALL.
		StringStream.width(10);
		// Nastavenie FILL pomocou METHOD CALL.
		StringStream.fill(L'_');
		// Nastavenie INTERNAL pomocou METHOD CALL.
		StringStream.setf(ios_base::internal,ios_base::adjustfield);

		StringStream << -123.15;

		StringStream << L" ";

		// !!!!! Platnost WIDTH konci po vykonani prvej OUTPUT OPERATION.
		StringStream << -123.15;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie WIDTH pomocou MANIPULATOR.
		StringStream << setw(10);
		// Nastavenie FILL pomocou MANIPULATOR.
		StringStream << setfill(L'_');
		// Nastavenie INTERNAL pomocou MANIPULATOR.
		StringStream << internal;

		StringStream << -123.15;

		StringStream << L" ";

		// !!!!! Platnost WIDTH konci po vykonani prvej OUTPUT OPERATION.
		StringStream << -123.15;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingShowPosNoShowPos(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie SHOW POS pomocou FLAGS.
		StringStream.setf(ios::showpos);

		StringStream << 100;

		// Vypnutie SHOW POS pomocou FLAGS.
		StringStream.unsetf(ios::showpos);

		StringStream << L" ";
		StringStream << 100;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		int														Value1;
		int														Value2;

		// Nastavenie SHOW POS pomocou FLAGS.
		StringStream.setf(ios::showpos);

		StringStream >> Value1;

		// Vypnutie SHOW POS pomocou FLAGS.
		StringStream.unsetf(ios::showpos);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie SHOW POS pomocou MANIPULATOR.
		StringStream << showpos;

		StringStream << 100;

		// Nastavenie NO SHOW POS pomocou MANIPULATOR.
		StringStream << noshowpos;

		StringStream << L" ";
		StringStream << 100;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		int														Value1;
		int														Value2;

		// Nastavenie SHOW POS pomocou MANIPULATOR.
		StringStream << showpos;

		StringStream >> Value1;

		// Nastavenie NO SHOW POS pomocou MANIPULATOR.
		StringStream << noshowpos;

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingUpperCaseNoUpperCase(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie UPPER CASE pomocou FLAGS.
		StringStream.setf(ios::uppercase);

		StringStream << 12345678.9;

		// Vypnutie UPPER CASE pomocou FLAGS.
		StringStream.unsetf(ios::uppercase);

		StringStream << L" ";
		StringStream << 12345678.9;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		double													Value1;
		double													Value2;

		// Nastavenie UPPER CASE pomocou FLAGS.
		StringStream.setf(ios::uppercase);

		StringStream >> Value1;

		// Vypnutie UPPER CASE pomocou FLAGS.
		StringStream.unsetf(ios::uppercase);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie UPPER CASE pomocou MANIPULATOR.
		StringStream << uppercase;

		StringStream << 12345678.9;

		// Nastavenie NO UPPER CASE pomocou MANIPULATOR.
		StringStream << nouppercase;

		StringStream << L" ";
		StringStream << 12345678.9;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		double													Value1;
		double													Value2;

		// Nastavenie UPPER CASE pomocou MANIPULATOR.
		StringStream << uppercase;

		StringStream >> Value1;

		// Nastavenie NO UPPER CASE pomocou MANIPULATOR.
		StringStream << nouppercase;

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingDec(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie DEC pomocou FLAGS.
		StringStream.setf(ios::dec,ios::basefield);

		StringStream << 123;

		// Odstranenie DEC pomocou FLAGS.
		StringStream.unsetf(ios::dec);

		StringStream << L" ";
		StringStream << 123;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		int														Value1;
		int														Value2;

		// Nastavenie DEC pomocou FLAGS.
		StringStream.setf(ios::dec,ios::basefield);

		StringStream >> Value1;

		// Odstranenie DEC pomocou FLAGS.
		StringStream.unsetf(ios::dec);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie DEC pomocou MANIPULATOR.
		StringStream << dec;

		StringStream << 123;

		// Odstranenie DEC pomocou FLAGS.
		StringStream.unsetf(ios::dec);

		StringStream << L" ";
		StringStream << 123;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		int														Value1;
		int														Value2;

		// Nastavenie DEC pomocou MANIPULATOR.
		StringStream << dec;

		StringStream >> Value1;

		// Odstranenie DEC pomocou FLAGS.
		StringStream.unsetf(ios::dec);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingOct(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie OCT pomocou FLAGS.
		StringStream.setf(ios::oct,ios::basefield);

		StringStream << 123;

		// Odstranenie OCT pomocou FLAGS.
		StringStream.unsetf(ios::oct);

		StringStream << L" ";
		StringStream << 123;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		int														Value1;
		int														Value2;

		// Nastavenie OCT pomocou FLAGS.
		StringStream.setf(ios::oct,ios::basefield);

		StringStream >> Value1;

		// Odstranenie OCT pomocou FLAGS.
		StringStream.unsetf(ios::oct);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie OCT pomocou MANIPULATOR.
		StringStream << oct;

		StringStream << 123;

		// Odstranenie OCT pomocou FLAGS.
		StringStream.unsetf(ios::oct);

		StringStream << L" ";
		StringStream << 123;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		int														Value1;
		int														Value2;

		// Nastavenie OCT pomocou MANIPULATOR.
		StringStream << oct;

		StringStream >> Value1;

		// Odstranenie OCT pomocou FLAGS.
		StringStream.unsetf(ios::oct);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingHex(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie HEX pomocou FLAGS.
		StringStream.setf(ios::hex,ios::basefield);

		StringStream << 123;

		// Odstranenie HEX pomocou FLAGS.
		StringStream.unsetf(ios::hex);

		StringStream << L" ";
		StringStream << 123;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		int														Value1;
		int														Value2;

		// Nastavenie HEX pomocou FLAGS.
		StringStream.setf(ios::hex,ios::basefield);

		StringStream >> Value1;

		// Odstranenie HEX pomocou FLAGS.
		StringStream.unsetf(ios::hex);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie HEX pomocou MANIPULATOR.
		StringStream << hex;

		StringStream << 123;

		// Odstranenie HEX pomocou FLAGS.
		StringStream.unsetf(ios::hex);

		StringStream << L" ";
		StringStream << 123;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		int														Value1;
		int														Value2;

		// Nastavenie HEX pomocou MANIPULATOR.
		StringStream << hex;

		StringStream >> Value1;

		// Odstranenie HEX pomocou FLAGS.
		StringStream.unsetf(ios::hex);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingShowBaseNoShowBase(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie SHOW BASE pomocou FLAGS.
		StringStream.setf(ios::hex,ios::basefield);

		// Nastavenie SHOW BASE pomocou FLAGS.
		StringStream.setf(ios::showbase);

		StringStream << 123;

		// Odstranenie SHOW BASE pomocou FLAGS.
		StringStream.unsetf(ios::showbase);

		StringStream << L" ";
		StringStream << 123;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		int														Value1;
		int														Value2;

		// Nastavenie SHOW BASE pomocou FLAGS.
		StringStream.setf(ios::showbase);

		StringStream >> Value1;

		// Odstranenie SHOW BASE pomocou FLAGS.
		StringStream.unsetf(ios::showbase);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie HEX pomocou MANIPULATOR.
		StringStream << hex;

		// Nastavenie SHOW BASE pomocou MANIPULATOR.
		StringStream << showbase;

		StringStream << 123;

		// Nastavenie NO SHOW BASE pomocou MANIPULATOR.
		StringStream << noshowbase;

		StringStream << L" ";
		StringStream << 123;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		int														Value1;
		int														Value2;

		// Nastavenie SHOW BASE pomocou MANIPULATOR.
		StringStream << showbase;

		StringStream >> Value1;

		// Nastavenie NO SHOW BASE pomocou MANIPULATOR.
		StringStream << noshowbase;

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingDefaultFloat(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie DEFAULT FLOAT pomocou FLAGS.
		StringStream.setf(static_cast<ios_base::fmtflags>(0),ios::floatfield);

		StringStream << 12345678.9;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		double													Value;

		// Nastavenie DEFAULT FLOAT pomocou FLAGS.
		StringStream.setf(static_cast<ios_base::fmtflags>(0),ios::floatfield);

		StringStream >> Value;

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie DEFAULT FLOAT pomocou MANIPULATOR.
		StringStream << defaultfloat;

		StringStream << 12345678.9;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		double													Value;

		// Nastavenie DEFAULT FLOAT pomocou MANIPULATOR.
		StringStream << defaultfloat;

		StringStream >> Value;

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingFixed(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie FIXED pomocou FLAGS.
		StringStream.setf(ios::fixed,ios::floatfield);

		StringStream << 12345678.9;

		// Odstranenie FIXED pomocou FLAGS.
		StringStream.unsetf(ios::fixed);

		StringStream << L" ";
		StringStream << 12345678.9;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		double													Value1;
		double													Value2;

		// Nastavenie FIXED pomocou FLAGS.
		StringStream.setf(ios::fixed,ios::floatfield);

		StringStream >> Value1;

		// Odstranenie FIXED pomocou FLAGS.
		StringStream.unsetf(ios::fixed);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie FIXED pomocou MANIPULATOR.
		StringStream << fixed;

		StringStream << 12345678.9;

		// Odstranenie FIXED pomocou FLAGS.
		StringStream.unsetf(ios::fixed);

		StringStream << L" ";
		StringStream << 12345678.9;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		double													Value1;
		double													Value2;

		// Nastavenie FIXED pomocou MANIPULATOR.
		StringStream << fixed;

		StringStream >> Value1;

		// Odstranenie FIXED pomocou FLAGS.
		StringStream.unsetf(ios::fixed);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingScientific(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie SCIENTIFIC pomocou FLAGS.
		StringStream.setf(ios::scientific,ios::floatfield);

		StringStream << 123456.789;

		// Odstranenie SCIENTIFIC pomocou FLAGS.
		StringStream.unsetf(ios::scientific);

		StringStream << L" ";
		StringStream << 123456.789;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		double													Value1;
		double													Value2;

		// Nastavenie SCIENTIFIC pomocou FLAGS.
		StringStream.setf(ios::scientific,ios::floatfield);

		StringStream >> Value1;

		// Odstranenie SCIENTIFIC pomocou FLAGS.
		StringStream.unsetf(ios::scientific);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie SCIENTIFIC pomocou MANIPULATOR.
		StringStream << scientific;

		StringStream << 123456.789;

		// Odstranenie SCIENTIFIC pomocou FLAGS.
		StringStream.unsetf(ios::scientific);

		StringStream << L" ";
		StringStream << 123456.789;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		double													Value1;
		double													Value2;

		// Nastavenie SCIENTIFIC pomocou MANIPULATOR.
		StringStream << scientific;

		StringStream >> Value1;

		// Odstranenie SCIENTIFIC pomocou FLAGS.
		StringStream.unsetf(ios::scientific);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingFixedScientific(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie FIXED SCIENTIFIC pomocou FLAGS.
		StringStream.setf(ios::fixed | ios::scientific,ios::floatfield);

		StringStream << 123456.789;

		// Odstranenie FIXED pomocou FLAGS.
		StringStream.unsetf(ios::fixed);

		// Odstranenie SCIENTIFIC pomocou FLAGS.
		StringStream.unsetf(ios::scientific);

		StringStream << L" ";
		StringStream << 123456.789;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		double													Value1;
		double													Value2;

		// Nastavenie FIXED SCIENTIFIC pomocou FLAGS.
		StringStream.setf(ios::fixed | ios::scientific,ios::floatfield);

		StringStream >> Value1;

		// Odstranenie FIXED pomocou FLAGS.
		StringStream.unsetf(ios::fixed);

		// Odstranenie SCIENTIFIC pomocou FLAGS.
		StringStream.unsetf(ios::scientific);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie FIXED SCIENTIFIC pomocou MANIPULATOR.
		StringStream << hexfloat;

		StringStream << 123456.789;

		// Odstranenie FIXED pomocou FLAGS.
		StringStream.unsetf(ios::fixed);

		// Odstranenie SCIENTIFIC pomocou FLAGS.
		StringStream.unsetf(ios::scientific);

		StringStream << L" ";
		StringStream << 123456.789;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		double													Value1;
		double													Value2;

		// Nastavenie FIXED SCIENTIFIC pomocou MANIPULATOR.
		StringStream << hexfloat;

		StringStream >> Value1;

		// Odstranenie FIXED pomocou FLAGS.
		StringStream.unsetf(ios::fixed);

		// Odstranenie SCIENTIFIC pomocou FLAGS.
		StringStream.unsetf(ios::scientific);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingPrecision(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie FIXED pomocou FLAGS.
		StringStream.setf(ios::fixed,ios::floatfield);

		// Nastavenie PRECISION pomocou METHOD CALL.
		StringStream.precision(10);

		StringStream << 12345678.9;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		double													Value;

		// Nastavenie PRECISION pomocou METHOD CALL.
		StringStream.precision(10);

		StringStream >> Value;

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie FIXED pomocou FLAGS.
		StringStream << fixed;

		// Nastavenie PRECISION pomocou MANIPULATOR.
		StringStream << setprecision(10);

		StringStream << 12345678.9;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		double													Value;

		// Nastavenie PRECISION pomocou MANIPULATOR.
		StringStream << setprecision(10);

		StringStream >> Value;

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingShowPointNoShowPoint(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie SHOW POINT pomocou FLAGS.
		StringStream.setf(ios::showpoint);

		StringStream << 123456.;

		// Odstranenie SHOW POINT pomocou FLAGS.
		StringStream.unsetf(ios::showpoint);

		StringStream << L" ";
		StringStream << 123456.;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		double													Value1;
		double													Value2;

		// Nastavenie SHOW POINT pomocou FLAGS.
		StringStream.setf(ios::showpoint);

		StringStream >> Value1;

		// Odstranenie SHOW POINT pomocou FLAGS.
		StringStream.unsetf(ios::showpoint);

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie SHOW POINT pomocou MANIPULATOR.
		StringStream << showpoint;

		StringStream << 123456.;

		// Nastavenie NO SHOW POINT pomocou MANIPULATOR.
		StringStream << noshowpoint;

		StringStream << L" ";
		StringStream << 123456.;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		double													Value1;
		double													Value2;

		// Nastavenie SHOW POINT pomocou MANIPULATOR.
		StringStream << showpoint;

		StringStream >> Value1;

		// Nastavenie NO SHOW POINT pomocou MANIPULATOR.
		StringStream << noshowpoint;

		StringStream >> Value2;

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingSkipWhiteSpacesNoSkipWhiteSpaces(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie SKIP WHITE SPACES pomocou FLAGS.
		StringStream.setf(ios::skipws);

		StringStream << L"   ";
		StringStream << 100;

		// Odstranenie SKIP WHITE SPACES pomocou FLAGS.
		StringStream.unsetf(ios::skipws);

		StringStream << L"   ";
		StringStream << 200;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		int														Value1;
		int														Value2;

		// Nastavenie SKIP WHITE SPACES pomocou FLAGS.
		StringStream.setf(ios::skipws);

		StringStream >> Value1;

		if (StringStream.operator bool()==true)
		{
			// !!! Pocet CHARACTERS je 0, pretoze OPERATOR>> nenaplna tuto VALUE.
			wcout << L"VALUE [" << Value1 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
		}
		else
		{
			wcout << L"READ OPERATION FAILED !" << endl;
		}

		// Odstranenie SKIP WHITE SPACES pomocou FLAGS.
		StringStream.unsetf(ios::skipws);

		// !!!!! Dojde k ERROR, pretoze nasledujuci CHARACTER je SPACE a WHITE SPACE NIE SU IGNOROVANE.
		StringStream >> Value2;

		if (StringStream.operator bool()==true)
		{
			// !!! Pocet CHARACTERS je 0, pretoze OPERATOR>> nenaplna tuto VALUE.
			wcout << L"VALUE [" << Value2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
		}
		else
		{
			wcout << L"READ OPERATION FAILED !" << endl;
		}
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie SKIP WHITE SPACES pomocou MANIPULATOR.
		StringStream << skipws;

		StringStream << L"   ";
		StringStream << 100;

		// Nastavenie NO SKIP WHITE SPACES pomocou MANIPULATOR.
		StringStream << noskipws;

		StringStream << L"   ";
		StringStream << 200;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		int														Value1;
		int														Value2;

		// Nastavenie SKIP WHITE SPACES pomocou MANIPULATOR.
		StringStream.setf(ios::skipws);

		StringStream >> Value1;

		if (StringStream.operator bool()==true)
		{
			// !!! Pocet CHARACTERS je 0, pretoze OPERATOR>> nenaplna tuto VALUE.
			wcout << L"VALUE [" << Value1 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
		}
		else
		{
			wcout << L"READ OPERATION FAILED !" << endl;
		}

		// Nastavenie NO SKIP WHITE SPACES pomocou MANIPULATOR.
		StringStream << noskipws;

		// !!!!! Dojde k ERROR, pretoze nasledujuci CHARACTER je SPACE a WHITE SPACE NIE SU IGNOROVANE.
		StringStream >> Value2;

		if (StringStream.operator bool()==true)
		{
			// !!! Pocet CHARACTERS je 0, pretoze OPERATOR>> nenaplna tuto VALUE.
			wcout << L"VALUE [" << Value2 << L"] READ from STREAM ! NUMBER of CHARACTERS READ [" << StringStream.gcount() << L"] !" << endl;
		}
		else
		{
			wcout << L"READ OPERATION FAILED !" << endl;
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFormattingUnitBufferNoUnitBuffer(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie UNIT BUFFER pomocou FLAGS.
		StringStream.setf(ios::unitbuf);

		StringStream << L"ABCDE";

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		StringStream << L" EFG";

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		// Odstranenie UNIT BUFFER pomocou FLAGS.
		StringStream.unsetf(ios::unitbuf);

		StringStream << L" HIJKL";

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		StringStream << L" MNOPQRT";

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstringstream											StringStream;

		// Nastavenie UNIT BUFFER pomocou MANIPULATOR.
		StringStream << unitbuf;

		StringStream << L"ABCDE";

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		StringStream << L" EFG";

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		// Nastavenie NO UNIT BUFFER pomocou MANIPULATOR.
		StringStream << nounitbuf;

		StringStream << L" HIJKL";

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		StringStream << L" MNOPQRT";

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLocale(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		StringStream << 123.456;
		
		wcout << L"DEFAULT - LOCALE [" << ConvertStringToWideString(StringStream.getloc().name()) << L"] !" << endl;
		wcout << L"DEFAULT - STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		locale													Locale("en-US");
		wstringstream											StringStream;

		StringStream.imbue(Locale);

		StringStream << 123.456;

		wcout << L"DEFAULT - LOCALE [" << ConvertStringToWideString(StringStream.getloc().name()) << L"] !" << endl;
		wcout << L"SLOVAK - STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}
	catch(const exception& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		locale													Locale("sk-SK");
		wstringstream											StringStream;

		StringStream.imbue(Locale);

		StringStream << 123.456;

		wcout << L"DEFAULT - LOCALE [" << ConvertStringToWideString(StringStream.getloc().name()) << L"] !" << endl;
		wcout << L"SLOVAK - STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}
	catch(const exception& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTiedStreams(void)
{
	PrintLineSeparator();

	wstringstream												StringStream1;
	wostringstream												StringStream2;
	wostringstream												StringStream3;

	// STREAMS sa navzajom zviazu.
	StringStream1.tie(&StringStream2);
	StringStream2.tie(&StringStream3);
	StringStream3.tie(&wcout);

	StringStream1 << L"ABC";
	StringStream2 << L"DEFG";

	// !!!!! Zviazanie NEZNAMENA presmerovanie obsahu STREAM s TIED STREAM, iba to, ze pred kazdou IO OPERATION nad povodnym STREAM sa vykona FLUSH nad TIED STREAM.
	wcout << L"STREAM 1 CONTENT [" << StringStream1.str() << L"] !" << endl;
	wcout << L"STREAM 2 CONTENT [" << StringStream2.str() << L"] !" << endl;
	wcout << L"STREAM 3 CONTENT [" << StringStream3.str() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRedirectedStreams(void)
{
	PrintLineSeparator();

	{
		wstringbuf												Buffer;

		wcout << L"STREAM BUFFER CONTENT [" << Buffer.str() << L"] !" << endl;

		// !!! Pre STREAM sa nastavi explicitne vytvoreny STREAM BUFFER.
		wiostream												Stream1(&Buffer);
		wiostream												Stream2(&Buffer);

		Stream2 << hex;

		Stream1 << 100;
		Stream1 << L" ";

		// !!! VALUE sa zapise ako HEXADECIMAL VALUE.
		Stream2 << 100;

		wcout << L"STREAM BUFFER CONTENT [" << Buffer.str() << L"] !" << endl;
	}

	wstringbuf													SharedBuffer;

	{
		// !!! Pre STREAM sa nastavi explicitne vytvoreny STREAM BUFFER.
		wiostream												Stream(&SharedBuffer);

		Stream << 100;

		wcout << L"STREAM BUFFER CONTENT [" << SharedBuffer.str() << L"] !" << endl;

		// !!! DESTRUCTOR NEUVOLNUJE STREAM BUFFER, pretoze ho sam NEALOKOVAL.
	}

	{
		// !!! Pre STREAM sa nastavi explicitne vytvoreny STREAM BUFFER.
		wiostream												Stream(&SharedBuffer);

		Stream << hex;
		Stream << L" ";
		Stream << 100;

		wcout << L"STREAM BUFFER CONTENT [" << SharedBuffer.str() << L"] !" << endl;

		// !!! DESTRUCTOR NEUVOLNUJE STREAM BUFFER, pretoze ho sam NEALOKOVAL.
	}

	{
		wstringstream											Stream;
		wiostream&												HelperStream=Stream;

		// !!! Pre STREAM sa nastavi explicitne vytvoreny STREAM BUFFER.
		HelperStream.rdbuf(&SharedBuffer);

		Stream << oct;
		Stream << L" ";
		Stream << 100;

		wcout << L"STREAM BUFFER CONTENT [" << SharedBuffer.str() << L"] !" << endl;

		// !!! DESTRUCTOR NEUVOLNUJE STREAM BUFFER, pretoze ho sam NEALOKOVAL.
	}

	wcout << L"STREAM BUFFER CONTENT [" << SharedBuffer.str() << L"] !" << endl;

	{
		wstringbuf												Buffer;

		// !!! Pre STREAM sa nastavi explicitne vytvoreny STREAM BUFFER.
		wiostream												Stream1(&Buffer);
		wiostream												Stream2(&Buffer);

		Stream1 << 100;

		int														Value;

		Stream2 >> Value;

		if (Stream2.operator bool()==true)
		{
			wcout << L"VALUE [" << Value << L"] READ from STREAM !" << endl;
		}
		else
		{
			wcout << L"ERROR or END OF FILE REACHED !" << endl;
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStreamBufferIterators(void)
{
	PrintLineSeparator();

	wstringbuf													Buffer;
	ostreambuf_iterator<wchar_t>								OutputIterator(&Buffer);
	wstring														Text(L"ABC 123 DEF");

	copy(Text.begin(),Text.end(),OutputIterator);

	wcout << L"STREAM BUFFER CONTENT [" << Buffer.str() << L"] !" << endl;

	istreambuf_iterator<wchar_t>								InputIterator1(&Buffer);
	istreambuf_iterator<wchar_t>								InputIterator2;

	while(InputIterator1!=InputIterator2)
	{
		wchar_t													Value=*InputIterator1;

		wcout << L"VALUE [" << Value << L"] READ from STREAM !" << endl;

		InputIterator1++;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStringStream(void)
{
	PrintLineSeparator();

	{
		wstringstream											StringStream;

		StringStream << L"ABCD";
		StringStream << L" ";
		StringStream << 123;
		StringStream << L" ";
		StringStream << 456.789;
		StringStream << L" ";
		StringStream << L"EFGHIJ";

		wstring													Value1;

		StringStream >> Value1;

		if (StringStream.operator bool()==true)
		{
			wcout << L"VALUE 1 [" << Value1 << L"] READ from STREAM !" << endl;
		}
		else
		{
			wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
		}

		int														Value2;

		StringStream >> Value2;

		if (StringStream.operator bool()==true)
		{
			wcout << L"VALUE 2 [" << Value2 << L"] READ from STREAM !" << endl;
		}
		else
		{
			wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
		}

		double													Value3;

		StringStream >> Value3;

		if (StringStream.operator bool()==true)
		{
			wcout << L"VALUE 3 [" << Value3 << L"] READ from STREAM !" << endl;
		}
		else
		{
			wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
		}

		wstring													Value4;

		StringStream >> Value4;

		if (StringStream.operator bool()==true)
		{
			wcout << L"VALUE 4 [" << Value4 << L"] READ from STREAM !" << endl;
		}
		else
		{
			wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
		}

		wcout << L"STRING STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstring													String(L"ABCDE");

		// !!! Do existujuceho STRING prida dalsie CHARACTERS.
		wstringstream											StringStream(String,ios::out | ios::ate);

		StringStream << L" ";
		StringStream << 100;

		// Obsah STRING sa NEMENI.
		wcout << L"STRING CONTENT [" << String << L"] !" << endl;
		wcout << L"STRING STREAM CONTENT [" << StringStream.str() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstring													String1;
		wstring													String2;

		// !!! Pouzije sa MOVE SEMANTICS.
		wstringstream(L"ABC DEFGH") >> String1 >> String2;

		wcout << L"STRING 1 CONTENT [" << String1 << L"] !" << endl;
		wcout << L"STRING 2 CONTENT [" << String2 << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFileStreamReadWrite(void)
{
	PrintLineSeparator();

	{
		wofstream												FileStream(".//Text.txt");

		if (FileStream.is_open()==true)
		{
			FileStream << L"ABCD";
			FileStream << L" ";
			FileStream << 123;
			FileStream << L" ";
			FileStream << 456.789;
			FileStream << L" ";
			FileStream << L"EFGHIJ";

			wcout << L"DATA SUCESSFULLY WRITTEN to FILE !" << endl;
		}
		else
		{
			wcout << L"FILE STREAM FAILED to OPEN !" << endl;
		}
	}

	PrintLineSeparator();

	{
		wifstream												FileStream(".//Text.txt");

		if (FileStream.is_open()==true)
		{
			wstring												Value1;

			FileStream >> Value1;

			if (FileStream.operator bool()==true)
			{
				wcout << L"VALUE 1 [" << Value1 << L"] READ from STREAM !" << endl;
			}
			else
			{
				wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
			}

			int													Value2;

			FileStream >> Value2;

			if (FileStream.operator bool()==true)
			{
				wcout << L"VALUE 2 [" << Value2 << L"] READ from STREAM !" << endl;
			}
			else
			{
				wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
			}

			double												Value3;

			FileStream >> Value3;

			if (FileStream.operator bool()==true)
			{
				wcout << L"VALUE 3 [" << Value3 << L"] READ from STREAM !" << endl;
			}
			else
			{
				wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
			}

			wstring												Value4;

			FileStream >> Value4;

			if (FileStream.operator bool()==true)
			{
				wcout << L"VALUE 4 [" << Value4 << L"] READ from STREAM !" << endl;
			}
			else
			{
				wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
			}
		}
		else
		{
			wcout << L"FILE STREAM FAILED to OPEN !" << endl;
		}
	}

	PrintLineSeparator();

	remove(".//Text.txt");

	wcout << L"FILE DELETED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFileStreamMoveSemantics(void)
{
	PrintLineSeparator();

	{
		// !!! Na pristup k FILE sa pouziva MOVE SEMANTICS.
		wofstream(".//Text.txt") << L"ABCD" << L" " << 123 << L" " << 456.789 << L" " << L"EFGHIJ";

		wcout << L"DATA SUCESSFULLY WRITTEN to FILE !" << endl;
	}

	PrintLineSeparator();

	{
		wstring													Value1;
		int														Value2;
		double													Value3;
		wstring													Value4;

		// !!! Na pristup k FILE sa pouziva MOVE SEMANTICS.
		wifstream(".//Text.txt") >> Value1 >> Value2 >> Value3 >> Value4;

		wcout << L"VALUE 1 [" << Value1 << L"] READ from STREAM !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] READ from STREAM !" << endl;
		wcout << L"VALUE 3 [" << Value3 << L"] READ from STREAM !" << endl;
		wcout << L"VALUE 4 [" << Value4 << L"] READ from STREAM !" << endl;
	}

	PrintLineSeparator();

	remove(".//Text.txt");

	wcout << L"FILE DELETED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFileStreamFlags(void)
{
	PrintLineSeparator();

	{
		// !!! FILE STREAM je otvoreny so specifickymi FLAGS.
		wfstream												FileStream(".//Text.txt",ios::in | ios::out | ios::trunc | ios::binary);

		if (FileStream.is_open()==true)
		{
			FileStream << L"ABCD";
			FileStream << L" ";
			FileStream << 123;
			FileStream << L" ";
			FileStream << 456.789;
			FileStream << L" ";
			FileStream << L"EFGHIJ";

			wcout << L"DATA SUCESSFULLY WRITTEN to FILE !" << endl;

			PrintLineSeparator();

			// !!! Urobi sa SEEK na zaciatok FILE.
			FileStream.seekg(0);

			wstring												Value1;

			FileStream >> Value1;

			if (FileStream.operator bool()==true)
			{
				wcout << L"VALUE 1 [" << Value1 << L"] READ from STREAM !" << endl;
			}
			else
			{
				wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
			}

			int													Value2;

			FileStream >> Value2;

			if (FileStream.operator bool()==true)
			{
				wcout << L"VALUE 2 [" << Value2 << L"] READ from STREAM !" << endl;
			}
			else
			{
				wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
			}

			double												Value3;

			FileStream >> Value3;

			if (FileStream.operator bool()==true)
			{
				wcout << L"VALUE 3 [" << Value3 << L"] READ from STREAM !" << endl;
			}
			else
			{
				wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
			}

			wstring												Value4;

			FileStream >> Value4;

			if (FileStream.operator bool()==true)
			{
				wcout << L"VALUE 4 [" << Value4 << L"] READ from STREAM !" << endl;
			}
			else
			{
				wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
			}
		}
		else
		{
			wcout << L"FILE STREAM FAILED to OPEN !" << endl;
		}
	}

	PrintLineSeparator();

	remove(".//Text.txt");

	wcout << L"FILE DELETED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFileStreamTellSeek(void)
{
	PrintLineSeparator();

	{
		// !!! FILE STREAM je otvoreny so specifickymi FLAGS.
		wfstream												FileStream(".//Text.txt",ios::in | ios::out | ios::trunc | ios::binary);

		if (FileStream.is_open()==true)
		{
			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			FileStream << L"ABCD";

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			FileStream << L" ";

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			FileStream << 123;

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			FileStream << L" ";

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			FileStream << 456.789;

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			FileStream << L" ";

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			FileStream << L"EFGHIJ";

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			wcout << L"DATA SUCESSFULLY WRITTEN to FILE !" << endl;

			PrintLineSeparator();

			// !!! Urobi sa SEEK na zaciatok FILE.
			FileStream.seekg(0);

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			wstring												Value1;

			FileStream >> Value1;

			if (FileStream.operator bool()==true)
			{
				wcout << L"VALUE 1 [" << Value1 << L"] READ from STREAM !" << endl;
			}
			else
			{
				wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
			}

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			int													Value2;

			FileStream >> Value2;

			if (FileStream.operator bool()==true)
			{
				wcout << L"VALUE 2 [" << Value2 << L"] READ from STREAM !" << endl;
			}
			else
			{
				wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
			}

			// !!! Ulozi sa POSITION v STREAM.
			wstreampos											Position=FileStream.tellg();

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			double												Value3A;

			FileStream >> Value3A;

			if (FileStream.operator bool()==true)
			{
				wcout << L"VALUE 3A [" << Value3A << L"] READ from STREAM !" << endl;
			}
			else
			{
				wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
			}

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			wstring												Value4A;

			FileStream >> Value4A;

			if (FileStream.operator bool()==true)
			{
				wcout << L"VALUE 4A [" << Value4A << L"] READ from STREAM !" << endl;
			}
			else
			{
				wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
			}

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			PrintLineSeparator();

			// !!!!! Kedze bol dosiahnuty END OF FILE je NUTNE vykonat RESET END OF FILE FLAG.
			// !!!!! METHOD clear() je NUTNE volat PRED volanim METHOD seekg(), inak NEDOJDE k zmene POSITION v STREAM.
			FileStream.clear();

			// !!! Urobi sa SEEK na zadanu POSITION.
			FileStream.seekg(Position);

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			double												Value3B;

			FileStream >> Value3B;

			if (FileStream.operator bool()==true)
			{
				wcout << L"VALUE 3B [" << Value3B << L"] READ from STREAM !" << endl;
			}
			else
			{
				wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
			}

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;

			wstring												Value4B;

			FileStream >> Value4B;

			if (FileStream.operator bool()==true)
			{
				wcout << L"VALUE 4B [" << Value4B << L"] READ from STREAM !" << endl;
			}
			else
			{
				wcout << L"ERROR OCCURED or END OF FILE REACHED !" << endl;
			}

			wcout << L"FILE STREAM TELLG [" << FileStream.tellg() << L"] TELLP [" << FileStream.tellp() << L"] !" << endl;
		}
		else
		{
			wcout << L"FILE STREAM FAILED to OPEN !" << endl;
		}
	}

	PrintLineSeparator();

	remove(".//Text.txt");

	wcout << L"FILE DELETED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDirectStreamBufferUse(void)
{
	PrintLineSeparator();

	wstringstream												Stream1;

	Stream1 << "ABCD";
	Stream1 << " ";
	Stream1 << 123.456;

	wcout << L"STREAM 1 CONTENT [" << Stream1.str() << L"] !" << endl;

	wstringstream												Stream2;

	// !!! Cely obsah STREAM sa nacita do ineho STREAM priamym pristupom k STREAM BUFFER.
	Stream1 >> Stream2.rdbuf();

	wcout << L"STREAM 2 CONTENT [" << Stream2.str() << L"] !" << endl;

	wcout << L"STREAM 3 CONTENT [";

	// !!! Cely obsah STREAM sa zapise do C++ OUTPUT STREAM priamym pristupom k STREAM BUFFER.
	wcout << Stream2.rdbuf();

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStreamIterators(void)
{
	PrintLineSeparator();

	wstringstream												Stream;

	{
		ostream_iterator<double,wchar_t>						OutputIterator(Stream,L" ");

		OutputIterator=123.456;
		OutputIterator=234.567;
		OutputIterator=345.678;

		wcout << L"STREAM CONTENT [" << Stream.str() << L"] !" << endl;
	}

	for(istream_iterator<double,wchar_t> InputIterator(Stream);InputIterator!=istream_iterator<double,wchar_t>();InputIterator++)
	{
		wcout << L"VALUE [" << *InputIterator << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestSimpleOperations();
	//TestInputOutputOperators();
	//TestStreamStates();
	//TestStreamTestOperators();
	//TestStreamExceptions1();
	//TestStreamExceptions2();
	//TestFormattedIOOperations();
	//TestUnformattedIOOperationsPutGet();
	//TestUnformattedIOOperationsWriteGet();
	//TestUnformattedIOOperationsWriteGetGetLine();
	//TestUnformattedIOOperationsWriteRead();
	//TestUnformattedIOOperationsWriteReadSomeFlush();
	//TestUnformattedIOOperationsWriteReadIgnore();
	//TestUnformattedIOOperationsWriteReadPeak();
	//TestUnformattedIOOperationsWriteReadUnget();
	//TestUnformattedIOOperationsWriteReadPutback();
	//TestStreamBuffers();
	//TestSentries();
	//TestManipulators();
	//TestCustomManipulators();
	//TestFormattingFlags();
	//TestFormattingBoolAlphaNoBoolAlpha();
	//TestFormattingWidthFill();
	//TestFormattingLeft();
	//TestFormattingRight();
	//TestFormattingInternal();
	//TestFormattingShowPosNoShowPos();
	//TestFormattingUpperCaseNoUpperCase();
	//TestFormattingDec();
	//TestFormattingOct();
	//TestFormattingHex();
	//TestFormattingShowBaseNoShowBase();
	//TestFormattingDefaultFloat();
	//TestFormattingFixed();
	//TestFormattingScientific();
	//TestFormattingFixedScientific();
	//TestFormattingPrecision();
	//TestFormattingShowPointNoShowPoint();
	//TestFormattingSkipWhiteSpacesNoSkipWhiteSpaces();
	//TestFormattingUnitBufferNoUnitBuffer();
	//TestLocale();
	//TestTiedStreams();
	//TestRedirectedStreams();
	//TestStreamBufferIterators();
	//TestStringStream();
	//TestFileStreamReadWrite();
	//TestFileStreamMoveSemantics();
	//TestFileStreamFlags();
	//TestFileStreamTellSeek();
	//TestDirectStreamBufferUse();
	TestStreamIterators();
	
	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------