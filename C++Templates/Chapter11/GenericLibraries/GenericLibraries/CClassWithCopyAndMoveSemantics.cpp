//----------------------------------------------------------------------------------------------------------------------
#include "CClassWithCopyAndMoveSemantics.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CClassWithCopyAndMoveSemantics::CClassWithCopyAndMoveSemantics(void)
	: MField1(0), MField2(0.0)
{
	wcout << L"DEFAULT CONSTRUCTOR CALLED ! FIELD 1 [" << MField1 << L"] FIELD 2 [" << MField2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CClassWithCopyAndMoveSemantics::CClassWithCopyAndMoveSemantics(int Field1, double Field2)
	: MField1(Field1), MField2(Field2)
{
	wcout << L"CONSTRUCTOR CALLED ! FIELD 1 [" << MField1 << L"] FIELD 2 [" << MField2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CClassWithCopyAndMoveSemantics::CClassWithCopyAndMoveSemantics(const CClassWithCopyAndMoveSemantics& Other)
	: MField1(Other.MField1), MField2(Other.MField2)
{
	wcout << L"COPY CONSTRUCTOR CALLED ! FIELD 1 [" << MField1 << L"] FIELD 2 [" << MField2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CClassWithCopyAndMoveSemantics::CClassWithCopyAndMoveSemantics(CClassWithCopyAndMoveSemantics&& Other) noexcept
	: MField1(move(Other.MField1)), MField2(move(Other.MField2))
{
	wcout << L"MOVE CONSTRUCTOR CALLED ! FIELD 1 [" << MField1 << L"] FIELD 2 [" << MField2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CClassWithCopyAndMoveSemantics::~CClassWithCopyAndMoveSemantics(void)
{
	wcout << L"DESTRUCTOR CALLED ! FIELD 1 [" << MField1 << L"] FIELD 2 [" << MField2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CClassWithCopyAndMoveSemantics& CClassWithCopyAndMoveSemantics::operator=(const CClassWithCopyAndMoveSemantics& Other)
{
	MField1=Other.MField1;
	MField2=Other.MField2;

	wcout << L"COPY OPERATOR= CALLED ! FIELD 1 [" << MField1 << L"] FIELD 2 [" << MField2 << L"]." << endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
CClassWithCopyAndMoveSemantics& CClassWithCopyAndMoveSemantics::operator=(CClassWithCopyAndMoveSemantics&& Other) noexcept
{
	MField1=move(Other.MField1);
	MField2=move(Other.MField2);

	wcout << L"MOVE OPERATOR= CALLED ! FIELD 1 [" << MField1 << L"] FIELD 2 [" << MField2 << L"]." << endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CClassWithCopyAndMoveSemantics::GetField1(void) const noexcept
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
double CClassWithCopyAndMoveSemantics::GetField2(void) const noexcept
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------