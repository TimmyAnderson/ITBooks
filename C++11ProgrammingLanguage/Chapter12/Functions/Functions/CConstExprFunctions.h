//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "CLiteralType.h"
#include "CException.h"
//-----------------------------------------------------------------------------
constexpr int													CONSTANT=100;
const int														GlobalConstVariable=100;
extern const int												ExternGlobalConstVariable;
extern int														GlobalVariable;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
constexpr int FunctionConstExpr1(int Value1, int Value2)
{
	return(Value1+Value2);
}
//-----------------------------------------------------------------------------
constexpr int FunctionConstExpr2(bool UsePlus, int Value1, int Value2)
{
	// !!! CONSTEXPR FUNCTIONS mozu pouzivat CONDITIONAL EXPRESSIONS.
	return((UsePlus==true) ? (Value1+Value2) : (Value1-Value2));
}
//-----------------------------------------------------------------------------
constexpr int FunctionConstExprWithConditions(bool UsePlus, int Value1, int Value2)
{
	if (UsePlus==true)
	{
		return(Value1+Value2);
	}
	else
	{
		return(Value1-Value2);
	}
}
//-----------------------------------------------------------------------------
constexpr int FunctionConstExprWithCycles(bool UseIncrement, int Value, int NumberOfIterations)
{
	for(int Index=0;Index<NumberOfIterations;Index++)
	{
		if (UseIncrement==true)
		{
			Value++;
		}
		else
		{
			Value--;
		}
	}

	return(Value);
}
//-----------------------------------------------------------------------------
constexpr CLiteralType FunctionConstExprReferenceParameters(const CLiteralType& Value1, const CLiteralType& Value2)
{
	CLiteralType												Value(Value1.GetValue()+Value2.GetValue());

	return(Value);
}
//-----------------------------------------------------------------------------
constexpr int FunctionConstExprThrowingException(bool ThrowException)
{
	if (ThrowException==false)
	{
		return(100);
	}
	else
	{
		throw(CException(L"SOME EXCEPTION !"));
	}
}
//-----------------------------------------------------------------------------
// !!! Kedze CONSTEXPR FUNCTION pouziva CONSTEXPR GLOBAL VARIABLE, FUNCTION generuje COMPILE TIME CONSTANT.
constexpr int FunctionConstExprUsingOutsideData_ConstExprVariable(int Value)
{
	return(CONSTANT+Value);
}
//-----------------------------------------------------------------------------
// !!! Kedze CONSTEXPR FUNCTION pouziva CONST GLOBAL VARIABLE, ktora MA DEFINOVANU VALUE, FUNCTION generuje COMPILE TIME CONSTANT.
constexpr int FunctionConstExprUsingOutsideData_ConstGlobalVariable(int Value)
{
	return(GlobalConstVariable+Value);
}
//-----------------------------------------------------------------------------
// !!! Aj ked CONSTEXPR FUNCTION pouziva CONST GLOBAL VARIABLE, kedze ta je EXTERN a NEMA definovanu VALUE, tak FUNCTION generuje RUN TIME CONSTANT.
constexpr int FunctionConstExprUsingOutsideData_ConstExternGlobalVariable(int Value)
{
	return(ExternGlobalConstVariable+Value);
}
//-----------------------------------------------------------------------------
#ifdef _MSC_VER
// !!! Kedze CONSTEXPR FUNCTION pouziva NON-CONST GLOBAL VARIABLE, generuje iba RUN TIME a NIE COMPILE TIME CONSTANTS.
// !!!!! GCC hodi COMPILATION ERROR.
constexpr int FunctionConstExprUsingOutsideData_NonConstGlobalVariable(int Value)
{
	return(GlobalConstVariable+Value+GlobalVariable);
}
#endif
//-----------------------------------------------------------------------------