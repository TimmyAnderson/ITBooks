//----------------------------------------------------------------------------------------------------------------------
#include "CFunctionObjectOperatorConversionToPointerToFunction.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CFunctionObjectOperatorConversionToPointerToFunction::CallbackFunction(const CString& Value1, int Value2, double Value3)
{
	wcout << L"METHOD [void CFunctionObjectOperatorConversionToPointerToFunction::CallbackFunction(const CString& Value1, int Value2, double Value3)] CALLED with VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] VALUE 3 [" << Value3 << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION OBJECT implementuje CONVERSION OPERATOR na POINTER na FUNCTION.
CFunctionObjectOperatorConversionToPointerToFunction::operator MyFunctionType*(void) const
{
	wcout << L"CONVERSION OPERATOR TO POINTER TO FUNCTION CALLED." << endl;

	return(&CFunctionObjectOperatorConversionToPointerToFunction::CallbackFunction);
}
//----------------------------------------------------------------------------------------------------------------------