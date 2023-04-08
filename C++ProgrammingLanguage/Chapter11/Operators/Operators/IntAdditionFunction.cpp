//-------------------------------------------------------------------------------------------------------
#include "IntAdditionFunction.h"
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CIntAdditionFunction::CIntAdditionFunction(bool AddOrRemove, int Value)
	: MAddOrRemove(AddOrRemove), MValue(Value)
{
}
//-------------------------------------------------------------------------------------------------------
CIntAdditionFunction::~CIntAdditionFunction(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int CIntAdditionFunction::operator()(CInt& Value)
{
	if (MAddOrRemove==true)
	{
		int														NewValue=Value.GetValue()+MValue;

		Value.SetValue(NewValue);

		wprintf_s(L"OPERATOR() for [%d] CALLED !\n",Value.GetValue());

		return(NewValue);
	}
	else
	{
		int														NewValue=Value.GetValue()-MValue;

		Value.SetValue(NewValue);

		wprintf_s(L"OPERATOR() for [%d] CALLED !\n",Value.GetValue());

		return(NewValue);
	}
}
//-------------------------------------------------------------------------------------------------------