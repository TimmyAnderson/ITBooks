//-----------------------------------------------------------------------------
#include "CException.h"
#include "CFunctions.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Function1(void)
{
	wcout << L"FUNCTION Function1() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
void Function2(const CSomeClass& Value1, const CSomeClass& Value2)
{
	wcout << L"FUNCTION Function2() CALLED with VALUE 1 [" << Value1.GetValue() << L"] and VALUE 2 [" << Value2.GetValue() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
CSomeClass Function3(const CSomeClass& Value1, const CSomeClass& Value2)
{
	wcout << L"FUNCTION Function3() CALLED with VALUE 1 [" << Value1.GetValue() << L"] and VALUE 2 [" << Value2.GetValue() << L"] !" << endl;

	return(CSomeClass(L"Some RETURN VALUE !"));
}
//-----------------------------------------------------------------------------
CSomeClass Function4(CSomeClass Value1, CSomeClass Value2)
{
	wcout << L"FUNCTION Function4() CALLED with VALUE 1 [" << Value1.GetValue() << L"] and VALUE 2 [" << Value2.GetValue() << L"] !" << endl;

	return(CSomeClass(L"Some RETURN VALUE !"));
}
//-----------------------------------------------------------------------------
int NormalReturnValueSyntax(int Value1, int Value2)
{
	wcout << L"FUNCTION NormalReturnValueSyntax() CALLED with VALUE 1 [" << Value1 << L"] and VALUE 2 [" << Value2 << L"] !" << endl;

	return(Value1+Value2);
}
//-----------------------------------------------------------------------------
auto NewReturnValueSyntax(int Value1, int Value2) -> int
{
	wcout << L"FUNCTION NewReturnValueSyntax() CALLED with VALUE 1 [" << Value1 << L"] and VALUE 2 [" << Value2 << L"] !" << endl;

	return(Value1+Value2);
}
//-----------------------------------------------------------------------------
void VoidReturnValue1(int Value1, int Value2)
{
	wcout << L"FUNCTION VoidReturnValue1() CALLED with VALUE 1 [" << Value1 << L"] and VALUE 2 [" << Value2 << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void VoidReturnValue2(int Value1, int Value2)
{
	wcout << L"FUNCTION VoidReturnValue2() CALLED with VALUE 1 [" << Value1 << L"] and VALUE 2 [" << Value2 << L"] !" << endl;

	// !!! C++ umoznuje pouzit KEYWORD [return()] aj na FUNCTIONS vracajuce VOID, ak EXPRESSION v KEYWORD [return()] vracia TYPE [void].
	return(VoidReturnValue1(Value1,Value2));
}
//-----------------------------------------------------------------------------
void VoidReturnValue3(int Value1, int Value2)
{
	wcout << L"FUNCTION VoidReturnValue3() CALLED with VALUE 1 [" << Value1 << L"] and VALUE 2 [" << Value2 << L"] !" << endl;

	// !!! C++ umoznuje pouzit KEYWORD [return()] aj na FUNCTIONS vracajuce VOID, ak EXPRESSION v KEYWORD [return()] vracia TYPE [void].
	return(void(Value1+Value2));
}
//-----------------------------------------------------------------------------
[[noreturn]] void NoReturnFunction(int Value1, int Value2)
{
	wcout << L"FUNCTION NoReturnFunction() CALLED with VALUE 1 [" << Value1 << L"] and VALUE 2 [" << Value2 << L"] !" << endl;

	// !!! NO RETURN FUNCTION MOZE hodi EXCEPTION, ale NESMIE skoncit v normalnom toku CODE bud skoncenim FUNCTION, alebo vratenim RETURN VALUE pomocou KEYWORD [return].
	throw(CException(L"SOME EXCEPTION !"));
}
//-----------------------------------------------------------------------------
void UseStaticLocalVariable(int ValueToAdd)
{
	int															AutomaticLocalVariable=100;
	// !!! STATIC LOCAL VARIABLES si zachovavaju svoje VALUES aj medzi opakovanymi volaniami FUNCTIONS.
	static int													StaticLocalVariable=100;

	wcout << L"FUNCTION UseStaticLocalVariable() CALLED with VALUE [" << ValueToAdd << L"] !" << endl;
	wcout << L"FUNCTION UseStaticLocalVariable() AUTOMATIC LOCAL VARIABLE [" << AutomaticLocalVariable << L"] !" << endl;
	wcout << L"FUNCTION UseStaticLocalVariable() STATIC LOCAL VARIABLE [" << StaticLocalVariable << L"] !" << endl;

	AutomaticLocalVariable+=ValueToAdd;
	StaticLocalVariable+=ValueToAdd;

	wcout << L"FUNCTION UseStaticLocalVariable() ADDITION OPERATIONS PERFORMED !" << endl;

	wcout << L"FUNCTION UseStaticLocalVariable() AUTOMATIC LOCAL VARIABLE [" << AutomaticLocalVariable << L"] !" << endl;
	wcout << L"FUNCTION UseStaticLocalVariable() STATIC LOCAL VARIABLE [" << StaticLocalVariable << L"] !" << endl;
}
//-----------------------------------------------------------------------------