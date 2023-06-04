//----------------------------------------------------------------------------------------------------------------------
#include "CFunctionObjectAndSurrogate.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CFunctionObjectAndSurrogate::SomeFunction1(double Value1, int Value2, int Value3)
{
	wcout << L"METHOD [void CFunctionObjectAndSurrogate::SomeFunction1(double Value1, int Value2, int Value3)] CALLED with VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] VALUE 3 [" << Value3 << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void CFunctionObjectAndSurrogate::SomeFunction2(double Value1, int Value2, wstring Value3)
{
	wcout << L"METHOD [void CFunctionObjectAndSurrogate::SomeFunction2(double Value1, int Value2, wstring Value3)] CALLED with VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] VALUE 3 [" << Value3 << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void CFunctionObjectAndSurrogate::SomeFunction3(double Value1, int Value2)
{
	wcout << L"METHOD [void SomeFunction3(double Value1, int Value2)] CALLED with VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CFunctionObjectAndSurrogate::operator()(double Value1, double Value2) const
{
	wcout << L"METHOD [void operator()(double Value1, double Value2) const] CALLED with VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CFunctionObjectAndSurrogate::operator MyFunctionType1*(void) const
{
	return(&CFunctionObjectAndSurrogate::SomeFunction1);
}
//----------------------------------------------------------------------------------------------------------------------
CFunctionObjectAndSurrogate::operator MyFunctionType2&(void) const
{
#ifdef _MSC_VER
	MyFunctionType2&											FunctionReference=CFunctionObjectAndSurrogate::SomeFunction2;

	// !!!!! Z nejakeho dovodu VISUAL C++ nedokaze vratit priamo FUNCTION REFERENCE a je treba ho najprv ulozit do TEMPORARY VARIABLE a az nasledne vratit ako RETURN VALUE.
	return(FunctionReference);
#else
	return(CFunctionObjectAndSurrogate::SomeFunction2);
#endif
}
//----------------------------------------------------------------------------------------------------------------------
CFunctionObjectAndSurrogate::operator MyFunctionType3*(void) const
{
	return(&CFunctionObjectAndSurrogate::SomeFunction3);
}
//----------------------------------------------------------------------------------------------------------------------