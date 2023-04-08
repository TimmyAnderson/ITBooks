//-----------------------------------------------------------------------------
#include "COuterNestedClasses.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
COuterNestedClasses::CNestedClass::CNestedClass(int Value)
	: MNestedField(Value)
{
	wcout << L"NESTED CLASS CONSTRUCTOR CALLED !" << endl;
}
//-----------------------------------------------------------------------------
COuterNestedClasses::CNestedClass::~CNestedClass(void)
{
	wcout << L"NESTED CLASS DESTRUCTOR CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int COuterNestedClasses::CNestedClass::GetNestedField(void) const
{
	return(MNestedField);
}
//-----------------------------------------------------------------------------
void COuterNestedClasses::CNestedClass::PrintNestedField(void) const
{
	wcout << L"METHOD COuterNestedClasses::CNestedClass::PrintNestedField() CALLED with NESTED FIELD [" << MNestedField << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void COuterNestedClasses::CNestedClass::PrintOuterField(const COuterNestedClasses& Object) const
{
	// !!!!! NESTED CLASSES MOZU pristupovat k PRIVATE FIELDS OUTER CLASSES.
	wcout << L"METHOD COuterNestedClasses::CNestedClass::PrintOuterField() CALLED with OUTER FIELD [" << Object.MOuterField << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
COuterNestedClasses::COuterNestedClasses(int Value)
	: MOuterField(Value)
{
	wcout << L"OUTER CLASS CONSTRUCTOR CALLED !" << endl;
}
//-----------------------------------------------------------------------------
COuterNestedClasses::~COuterNestedClasses(void)
{
	wcout << L"OUTER CLASS DESTRUCTOR CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void COuterNestedClasses::PrintNestedField(const CNestedClass& Object) const
{
	// !!!!! OUTER CLASSES NEMOZU pristupovat k PRIVATE FIELDS NESTED CLASSES.
	//wcout << L"METHOD COuterNestedClasses::PrintNestedField() CALLED with NESTED FIELD [" << Object.MNestedField << L"] !" << endl;

	// !!!!! OUTER CLASSES MOZU pristupovat IBA k PUBLIC MEMBERS.
	wcout << L"METHOD COuterNestedClasses::PrintNestedField() CALLED with NESTED FIELD [" << Object.GetNestedField() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void COuterNestedClasses::PrintOuterField(void) const
{
	wcout << L"METHOD COuterNestedClasses::PrintOuterField() CALLED with OUTER FIELD [" << MOuterField << L"] !" << endl;
}
//-----------------------------------------------------------------------------