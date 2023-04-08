//-------------------------------------------------------------------------------------------------------
#include "Int.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
// GLOBALNY OPERATOR.
CInt operator-(CInt& LeftOperand, CInt& RightOperand)
{
	wprintf(L"GLOBAL OPERATOR-(CInt&,CInt&) !\n");

	CInt														Result(LeftOperand.GetValue()-RightOperand.GetValue());

	return(Result);
}
//-------------------------------------------------------------------------------------------------------
// GLOBALNY OPERATOR.
CInt operator-(CInt& LeftOperand, int RightOperand)
{
	wprintf(L"GLOBAL OPERATOR-(CInt&,int) !\n");

	CInt														Result(LeftOperand.GetValue()-RightOperand);

	return(Result);
}
//-------------------------------------------------------------------------------------------------------
// GLOBALNY OPERATOR.
CInt operator*(int LeftOperand, CInt& RightOperand)
{
	wprintf(L"GLOBAL OPERATOR*(int,CInt&) !\n");

	CInt														Result(LeftOperand*RightOperand.GetValue());

	return(Result);
}
//-------------------------------------------------------------------------------------------------------
// GLOBALNY OPERATOR.
// !!! PREFIX OPERATOR.
CInt& operator--(CInt& LeftOperand)
{
	wprintf(L"GLOBAL OPERATOR-- PREFIX !\n");

	int															NewValue=LeftOperand.GetValue()-1;

	LeftOperand.SetValue(NewValue);

	return(LeftOperand);

}
//-------------------------------------------------------------------------------------------------------
// GLOBALNY OPERATOR.
// !!! POSTFIX OPERATOR.
CInt& operator--(CInt& LeftOperand, int DummyOperand)
{
	wprintf(L"GLOBAL OPERATOR-- POSTFIX !\n");

	int															NewValue=LeftOperand.GetValue()-1;

	LeftOperand.SetValue(NewValue);

	return(LeftOperand);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CInt::CInt(void)
	: MValue(0)
{
	wprintf(L"DEFAULT CONSTRUCTOR !\n");
}
//-------------------------------------------------------------------------------------------------------
CInt::CInt(int Value)
	: MValue(Value)
{
	wprintf(L"CONSTRUCTOR [%d] !\n",MValue);
}
//-------------------------------------------------------------------------------------------------------
CInt::CInt(const CInt& Object)
	: MValue(Object.MValue)
{
	wprintf(L"COPY CONSTRUCTOR [%d] !\n",MValue);
}
//-------------------------------------------------------------------------------------------------------
CInt::~CInt(void)
{
	wprintf(L"DESTRUCTOR [%d] !\n",MValue);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CInt CInt::operator+(CInt& RightOperand)
{
	wprintf(L"MEMBER OPERATOR+ !\n");

	CInt														Result(MValue+RightOperand.MValue);

	return(Result);
}
//-------------------------------------------------------------------------------------------------------
CInt CInt::operator-(CInt& RightOperand)
{
	wprintf(L"MEMBER OPERATOR- !\n");

	CInt														Result(MValue-RightOperand.MValue);

	return(Result);
}
//-------------------------------------------------------------------------------------------------------
CInt& CInt::operator=(const CInt& RightOperand)
{
	wprintf(L"MEMBER OPERATOR= !\n");

	MValue=RightOperand.MValue;

	return(*this);
}
//-------------------------------------------------------------------------------------------------------
// !!! PREFIX OPERATOR.
CInt& CInt::operator++(void)
{
	wprintf(L"MEMBER OPERATOR++ PREFIX !\n");

	MValue++;

	return(*this);
}
//-------------------------------------------------------------------------------------------------------
// !!! POSTFIX OPERATOR.
CInt& CInt::operator++(int DummyOperand)
{
	wprintf(L"MEMBER OPERATOR++ POSTFIX !\n");

	MValue++;

	return(*this);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CInt::Print(void)
{
	wprintf_s(L"Value: [%d] !\n",MValue);
}
//-------------------------------------------------------------------------------------------------------