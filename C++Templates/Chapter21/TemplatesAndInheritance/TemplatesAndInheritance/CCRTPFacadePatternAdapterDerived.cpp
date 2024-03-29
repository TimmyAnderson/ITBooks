//----------------------------------------------------------------------------------------------------------------------
#include "CCRTPFacadePatternAdapterDerived.h"
#include <sstream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCRTPFacadePatternAdapterDerived::CCRTPFacadePatternAdapterDerived(const CString& Prefix, const CString& Value, int IntValue)
	: MPrefix(Prefix), MValue(Value), MIntValue(IntValue)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCRTPFacadePatternAdapterDerived::~CCRTPFacadePatternAdapterDerived(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CString CCRTPFacadePatternAdapterDerived::GetPrefix(void) const
{
	return(MPrefix);
}
//----------------------------------------------------------------------------------------------------------------------
CString CCRTPFacadePatternAdapterDerived::GetValue(void) const
{
	// !!!!! Modifikuje sa cinnost PRIVATE INTERFACE, aby sa demonstrovala funkcionalita ADAPTER PATTERN.

	wstringstream												Stream;

	Stream << MValue;

	Stream << L" INT VALUE [";

	Stream << MIntValue;

	Stream << L"]";

	CString														Value(Stream.str());

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------