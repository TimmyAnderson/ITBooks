//-----------------------------------------------------------------------------
#include "CStaticFieldsAndMethods.h"
//-----------------------------------------------------------------------------
int																CStaticFieldsAndMethods::MStaticField=0;
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CStaticFieldsAndMethods::CStaticFieldsAndMethods(int NonStaticField)
	: MNonStaticField(NonStaticField)
{
	// STATIC FIELD 'MStaticField' sluzi ako OBJECT COUNTER.
	MStaticField++;

	wcout << L"CONSTRUCTOR CALLED !" << endl;
}
//-----------------------------------------------------------------------------
CStaticFieldsAndMethods::~CStaticFieldsAndMethods(void)
{
	// STATIC FIELD 'MStaticField' sluzi ako OBJECT COUNTER.
	MStaticField--;

	wcout << L"DESTRUCTOR CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int CStaticFieldsAndMethods::GetStaticField(void) noexcept
{
	// !!! STATIC METHODS NEMOZU volat NON-STATIC METHODS.
	//GetNonStaticField();

	return(MStaticField);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int CStaticFieldsAndMethods::GetNonStaticField(void) const noexcept
{
	return(MNonStaticField);
}
//-----------------------------------------------------------------------------