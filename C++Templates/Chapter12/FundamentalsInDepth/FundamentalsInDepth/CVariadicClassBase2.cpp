//----------------------------------------------------------------------------------------------------------------------
#include "CVariadicClassBase2.h"
#include <sstream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CVariadicClassBase2::CVariadicClassBase2(const CString& FieldBase2)
	: MFieldBase2(FieldBase2)
{
}
//----------------------------------------------------------------------------------------------------------------------
CVariadicClassBase2::CVariadicClassBase2(const CVariadicClassBase2& Other)
	: MFieldBase2(Other.MFieldBase2)
{
}
//----------------------------------------------------------------------------------------------------------------------
CVariadicClassBase2::~CVariadicClassBase2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const CString& CVariadicClassBase2::GetFieldBase2(void) const noexcept
{
	return(MFieldBase2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
wstring CVariadicClassBase2::ToString(void) const
{
	wstringstream												Stream;

	Stream << L"BASE CLASS 2 - FIELD BASE 2 [" << MFieldBase2 << L"].";

	return(Stream.str());
}
//----------------------------------------------------------------------------------------------------------------------