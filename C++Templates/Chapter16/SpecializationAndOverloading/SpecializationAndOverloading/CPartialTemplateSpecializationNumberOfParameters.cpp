//----------------------------------------------------------------------------------------------------------------------
#include "CPartialTemplateSpecializationNumberOfParameters.h"
#include <sstream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CPartialTemplateSpecializationNumberOfParametersTest::CPartialTemplateSpecializationNumberOfParametersTest(int Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CPartialTemplateSpecializationNumberOfParametersTest::~CPartialTemplateSpecializationNumberOfParametersTest(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CString CPartialTemplateSpecializationNumberOfParametersTest::ToString1(int Parameter) const
{
	wstringstream												Stream;

	Stream << L"TO STRING 1 - VALUE [" << MValue << L"] PARAMETER [" << Parameter << L"].";

	CString														Text(Stream.str());

	return(Text);
}
//----------------------------------------------------------------------------------------------------------------------
CString CPartialTemplateSpecializationNumberOfParametersTest::ToString2(double Parameter) const
{
	wstringstream												Stream;

	Stream << L"TO STRING 2 - VALUE [" << MValue << L"] PARAMETER [" << Parameter << L"].";

	CString														Text(Stream.str());

	return(Text);
}
//----------------------------------------------------------------------------------------------------------------------