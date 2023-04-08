//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CPerson.h"
//-----------------------------------------------------------------------------
class CPersonSortingCriteriaFunctionObject final
{
//-----------------------------------------------------------------------------
	public:
		// Implementuje funkcnost OPERATOR<.
		bool operator()(const CPerson& Value1, const CPerson& Value2)
		{
			if (Value1.GetName()<Value2.GetName())
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------