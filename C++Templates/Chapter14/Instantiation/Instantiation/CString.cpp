//----------------------------------------------------------------------------------------------------------------------
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CString::CString(void)
	: MField()
{
}
//----------------------------------------------------------------------------------------------------------------------
CString::CString(const wchar_t* Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
CString::CString(const wstring& Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
CString::~CString(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const wstring& CString::GetField(void) const noexcept
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
wostream& operator<<(wostream& Stream, const CString& Value)
{
	Stream << Value.MField;

	return(Stream);
}
//----------------------------------------------------------------------------------------------------------------------