//----------------------------------------------------------------------------------------------------------------------
#include "CFunctionObjectOperatorConversionToReferenceToFunction.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CFunctionObjectOperatorConversionToReferenceToFunction::CallbackFunction(const CString& Value1, int Value2, double Value3)
{
	wcout << L"METHOD [void CFunctionObjectOperatorConversionToReferenceToFunction::CallbackFunction(const CString& Value1, int Value2, double Value3)(const CString& Value1, int Value2, double Value3)] CALLED with VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] VALUE 3 [" << Value3 << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION OBJECT implementuje CONVERSION OPERATOR na REFERENCE na FUNCTION.
CFunctionObjectOperatorConversionToReferenceToFunction::operator MyFunctionType&(void) const
{
	wcout << L"CONVERSION OPERATOR TO REFERENCE TO FUNCTION CALLED." << endl;

#ifdef _MSC_VER
	MyFunctionType&												FunctionReference=CFunctionObjectOperatorConversionToReferenceToFunction::CallbackFunction;

	// !!!!! Z nejakeho dovodu VISUAL C++ nedokaze vratit priamo FUNCTION REFERENCE a je treba ho najprv ulozit do TEMPORARY VARIABLE a az nasledne vratit ako RETURN VALUE.
	return(FunctionReference);
#else
	return(CFunctionObjectOperatorConversionToReferenceToFunction::CallbackFunction);
#endif
}
//----------------------------------------------------------------------------------------------------------------------