//-------------------------------------------------------------------------------------------------------
#include "Name.h"
#include <iostream>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
// Pouziva sa pre COUT.
std::ostream& operator<<(std::ostream& Stream, CName& Name)
{
	//wprintf_s(L"USING OPERATOR - OSTREAM !\n");

	// !!! Musim spravit konverziu WCHAR_T na CHAR.
	locale														LocaleDefault=locale("");
	const ctype<wchar_t>&										CTypeUSA=use_facet<ctype<wchar_t>>(LocaleDefault);

	wstring														FirstName=Name.GetFirstName();
	wstring														LastName=Name.GetLastName();

	char														FirstNameBuffer[100];
	char														LastNameBuffer[100];

	CTypeUSA.narrow(FirstName.c_str(),FirstName.c_str()+FirstName.length()+1,' ',FirstNameBuffer);
	CTypeUSA.narrow(LastName.c_str(),LastName.c_str()+LastName.length()+1,' ',LastNameBuffer);

	Stream << FirstNameBuffer;
	Stream << ' ';
	Stream << LastNameBuffer;

	Stream << ' ';

	// !!! Kedze pre INT EXISTUJE OPERATOR<<, tak moze priamo zapisat hodnotu do STREAM.
	Stream << Name.GetAge();

	return(Stream);
}
//-------------------------------------------------------------------------------------------------------
// Pouziva sa pre WCOUT.
std::wostream& operator<<(std::wostream& Stream, CName& Name)
{
	//wprintf_s(L"USING OPERATOR - WOSTREAM !\n");

	// !!! Kedze pouzivam WSTRING, tak mozem PRIAMO PISAT BEZ KONVERZIE do OSTREAM.
	Stream << Name.GetFirstName();
	Stream << ' ';
	Stream << Name.GetLastName();
	Stream << ' ';
	Stream << Name.GetAge();
	
	return(Stream);
}
//-------------------------------------------------------------------------------------------------------
// Pouziva sa pre WCOUT.
std::wistream& operator>>(std::wistream& Stream, CName& Name)
{
	wstring														FirstName;
	wstring														LastName;
	int															Age;

	Stream >> FirstName >> LastName >> Age;

	if (Stream.fail()==false && Stream.bad()==false)
	{
		Name.SetFirstName(FirstName);
		Name.SetLastName(LastName);
		Name.SetAge(Age);
	}
	else
	{
		// !!! Kedze som narusil STREAM, tak nastavim BAD FLAG.
		Stream.setf(ios_base::badbit);
	}

	return(Stream);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CName::CName(void)
{
	MFirstName=L"";
	MLastName=L"";
	MAge=0;
}
//-------------------------------------------------------------------------------------------------------
CName::CName(const CName& Other)
{
	MFirstName=Other.MFirstName;
	MLastName=Other.MLastName;
	MAge=Other.MAge;
}
//-------------------------------------------------------------------------------------------------------
CName::CName(wstring FirstName, wstring LastName, int Age)
{
	MFirstName=FirstName;
	MLastName=LastName;
	MAge=Age;
}
//-------------------------------------------------------------------------------------------------------
CName::~CName(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
wstring& CName::GetFirstName(void)
{
	return(MFirstName);
}
//-------------------------------------------------------------------------------------------------------
wstring& CName::GetLastName(void)
{
	return(MLastName);
}
//-------------------------------------------------------------------------------------------------------
int& CName::GetAge(void)
{
	return(MAge);
}
//-------------------------------------------------------------------------------------------------------
void CName::SetFirstName(wstring& Value)
{
	MFirstName=Value;
}
//-------------------------------------------------------------------------------------------------------
void CName::SetLastName(wstring& Value)
{
	MLastName=Value;
}
//-------------------------------------------------------------------------------------------------------
void CName::SetAge(int Value)
{
	MAge=Value;
}
//-------------------------------------------------------------------------------------------------------
void CName::PrintFullName(void)
{
	wcout << L"Name: [" << MFirstName << L" " << MLastName << L"], Age: [" << MAge << "] !\n";
}
//-------------------------------------------------------------------------------------------------------