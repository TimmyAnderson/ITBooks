//----------------------------------------------------------------------------------------------------------------------
#include "CLookUpUnQualifiedNamesDerived.h"
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
CString															MBaseField(L"GLOBAL - BASE FIELD");
CString															MDerivedField(L"GLOBAL - DERIVED FIELD");
CString															MSharedField(L"GLOBAL - SHARED FIELD");
CString															InClassLookUpUnQualifiedNamesGlobalVariable(L"GLOBAL - GLOBAL VARIABLE");
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CLookUpUnQualifiedNamesDerived::CLookUpUnQualifiedNamesDerived(const CString& BaseField, const CString& SharedFieldBase, const CString& DerivedField, const CString& SharedFieldDerived)
	: CLookUpUnQualifiedNamesBase(BaseField,SharedFieldBase), MDerivedField(DerivedField), MSharedField(SharedFieldDerived)
{
}
//----------------------------------------------------------------------------------------------------------------------
CLookUpUnQualifiedNamesDerived::~CLookUpUnQualifiedNamesDerived(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CLookUpUnQualifiedNamesDerived::TestClassMethodLookUpUnQualifiedNames1(void) const
{
	{
		CString													MBaseField(L"LOCAL - BASE FIELD");
		CString													MDerivedField(L"LOCAL - DERIVED FIELD");
		CString													MSharedField(L"LOCAL - SHARED FIELD");

		// !!!!! Pristupuje sa k LOCAL VARIABLE 'MBaseField'.
		wcout << L"IN LOCAL SCOPE - MBaseField [" << MBaseField << L"]." << endl;

		// !!!!! Pristupuje sa k LOCAL VARIABLE 'MDerivedField'.
		wcout << L"IN LOCAL SCOPE - MDerivedField [" << MDerivedField << L"]." << endl;

		// !!!!! Pristupuje sa k LOCAL VARIABLE 'MSharedField'.
		wcout << L"IN LOCAL SCOPE - MSharedField [" << MSharedField << L"]." << endl;
	}

	PrintLineSeparator();

	// !!!!! Pristupuje sa k FIELD 'MBaseField'.
	wcout << L"IN METHOD SCOPE - MBaseField [" << MBaseField << L"]." << endl;

	// !!!!! Pristupuje sa k FIELD 'MDerivedField'.
	wcout << L"IN METHOD SCOPE - MDerivedField [" << MDerivedField << L"]." << endl;

	// !!!!! Pristupuje sa k FIELD 'MSharedField' CLASS 'CLookUpUnQualifiedNamesDerived'.
	wcout << L"IN METHOD SCOPE - MSharedField [" << MSharedField << L"]." << endl;

	// !!!!! Pristupuje sa ku GLOBAL VARIABLE 'InClassLookUpUnQualifiedNamesGlobalVariable'.
	wcout << L"IN METHOD SCOPE - InClassLookUpUnQualifiedNamesGlobalVariable [" << InClassLookUpUnQualifiedNamesGlobalVariable << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CLookUpUnQualifiedNamesDerived::TestClassMethodLookUpUnQualifiedNames2(const CString& MBaseField, const CString& MDerivedField, const CString& MSharedField) const
{
	{
		CString													MBaseField(L"LOCAL - BASE FIELD");
		CString													MDerivedField(L"LOCAL - DERIVED FIELD");
		CString													MSharedField(L"LOCAL - SHARED FIELD");

		// !!!!! Pristupuje sa k LOCAL VARIABLE 'MBaseField'.
		wcout << L"IN LOCAL SCOPE - MBaseField [" << MBaseField << L"]." << endl;

		// !!!!! Pristupuje sa k LOCAL VARIABLE 'MDerivedField'.
		wcout << L"IN LOCAL SCOPE - MDerivedField [" << MDerivedField << L"]." << endl;

		// !!!!! Pristupuje sa k LOCAL VARIABLE 'MSharedField'.
		wcout << L"IN LOCAL SCOPE - MSharedField [" << MSharedField << L"]." << endl;
	}

	PrintLineSeparator();

	// !!!!! Pristupuje sa k METHOD PARAMETER 'MBaseField'.
	wcout << L"IN METHOD SCOPE - MBaseField [" << MBaseField << L"]." << endl;

	// !!!!! Pristupuje sa k METHOD PARAMETER 'MDerivedField'.
	wcout << L"IN METHOD SCOPE - MDerivedField [" << MDerivedField << L"]." << endl;

	// !!!!! Pristupuje sa k METHOD PARAMETER 'MSharedField'.
	wcout << L"IN METHOD SCOPE - MSharedField [" << MSharedField << L"]." << endl;

	// !!!!! Pristupuje sa ku GLOBAL VARIABLE 'InClassLookUpUnQualifiedNamesGlobalVariable'.
	wcout << L"IN METHOD SCOPE - InClassLookUpUnQualifiedNamesGlobalVariable [" << InClassLookUpUnQualifiedNamesGlobalVariable << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------