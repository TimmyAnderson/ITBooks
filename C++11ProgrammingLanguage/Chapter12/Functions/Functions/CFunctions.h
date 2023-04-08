//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "CSomeClass.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Function1(void);
void Function2(const CSomeClass& Value1, const CSomeClass& Value2);
CSomeClass Function3(const CSomeClass& Value1, const CSomeClass& Value2);
CSomeClass Function4(CSomeClass Value1, CSomeClass Value2);
int NormalReturnValueSyntax(int Value1, int Value2);
// Nova SYNTAX pre RETURN VALUES.
auto NewReturnValueSyntax(int Value1, int Value2) -> int;
void VoidReturnValue1(int Value1, int Value2);
void VoidReturnValue2(int Value1, int Value2);
void VoidReturnValue3(int Value1, int Value2);
//-----------------------------------------------------------------------------
inline int FunctionInline(int Value1, int Value2)
{
	return(Value1+Value2);
}
//-----------------------------------------------------------------------------
[[noreturn]] void NoReturnFunction(int Value1, int Value2);
//-----------------------------------------------------------------------------
void UseStaticLocalVariable(int ValueToAdd);
//-----------------------------------------------------------------------------