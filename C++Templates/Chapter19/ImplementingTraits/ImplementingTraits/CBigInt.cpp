//----------------------------------------------------------------------------------------------------------------------
#include "CBigInt.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CBigInt::CBigInt(long long Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CBigInt::~CBigInt(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CBigInt& CBigInt::operator+=(const CBigInt& Other)
{
	MValue+=Other.MValue;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
wostream& operator<<(std::wostream& Stream, const CBigInt& Value)
{
	Stream << Value.MValue;

	return(Stream);
}
//----------------------------------------------------------------------------------------------------------------------