//----------------------------------------------------------------------------------------------------------------------
#include "CDouble.h"
#include <utility>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CDouble::CDouble(void)
	: MValue(0.0)
{
}
//----------------------------------------------------------------------------------------------------------------------
CDouble::CDouble(double Value)
	: MValue(Value)
{
	IncrementCounter();
}
//----------------------------------------------------------------------------------------------------------------------
CDouble::CDouble(const CDouble& Value)
	: MValue(Value.MValue)
{
	IncrementCounter();
}
//----------------------------------------------------------------------------------------------------------------------
CDouble::CDouble(CDouble&& Value) noexcept
	: MValue(move(Value.MValue))
{
	IncrementCounter();
}
//----------------------------------------------------------------------------------------------------------------------
CDouble::~CDouble(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CDouble& CDouble::operator=(const CDouble& Other)
{
	MValue=Other.MValue;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
CDouble& CDouble::operator=(CDouble&& Other) noexcept
{
	MValue=move(Other.MValue);

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! MEMBER OPERATOR NEVYTVARA TEMPORARY ARRAY.
CDouble& CDouble::operator+=(const CDouble& Value)
{
	MValue+=Value.MValue;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! MEMBER OPERATOR NEVYTVARA TEMPORARY ARRAY.
CDouble& CDouble::operator*=(const CDouble& Value)
{
	MValue*=Value.MValue;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! MEMBER OPERATOR NEVYTVARA TEMPORARY ARRAY.
CDouble& CDouble::operator*=(const double& Value)
{
	MValue*=Value;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CDouble::operator size_t(void) const
{
	size_t														Value=static_cast<size_t>(MValue);

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CDouble::IncrementCounter(void)
{
	MMutex.lock();

	++MCounter;

	MMutex.unlock();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
size_t CDouble::GetCounter(void)
{
	size_t														Value;

	MMutex.lock();

	Value=MCounter;

	MMutex.unlock();

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
void CDouble::ResetCounter(void)
{
	MMutex.lock();

	MCounter=0;

	MMutex.unlock();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
double CDouble::GetValue(void) const
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NON-MEMBER OPERATOR VYTVARA TEMPORARY VALUE.
CDouble operator+(const CDouble& Value1, const CDouble& Value2)
{
	CDouble														Result(Value1.MValue+Value2.MValue);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NON-MEMBER OPERATOR VYTVARA TEMPORARY VALUE.
CDouble operator*(const CDouble& Value1, const CDouble& Value2)
{
	CDouble														Result(Value1.MValue*Value2.MValue);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NON-MEMBER OPERATOR VYTVARA TEMPORARY VALUE.
CDouble operator*(const double& Value1, const CDouble& Value2)
{
	CDouble														Result(Value1*Value2.MValue);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
wostream& operator<<(wostream& Stream, const CDouble& Value)
{
	Stream << Value.MValue;

	return(Stream);
}
//----------------------------------------------------------------------------------------------------------------------