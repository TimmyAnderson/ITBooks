//----------------------------------------------------------------------------------------------------------------------
#include "CTemplateFunctionFullSpecializationODR.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DEFINITION TEMPLATE FUNCTION SPECIALIZATION.
// !!!!! Kdze TEMPLATE FUNCTION SPECIALIZATIONS su bezne NON-TEMPLATE FUNCTIONS, MUSIA splnat ONE DEFINITION RULE.
template<>
void TemplateFunctionFullSpecializationODR<double>(double Value)
{
	wcout << L"TEMPLATE FUNCTION SPECIALIZATION <double> - ONE DEFINITION RULE - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------