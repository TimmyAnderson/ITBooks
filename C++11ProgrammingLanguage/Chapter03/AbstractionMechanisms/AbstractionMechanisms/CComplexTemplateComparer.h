//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CComplexTemplate.h"
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
class CComplexTemplateComparer
{
//-------------------------------------------------------------------------------------------------------
	public:
		bool operator()(CComplexTemplate<int> Value1, CComplexTemplate<int> Value2)
		{
			if (Value1.MVariable2==Value2.MVariable2)
			{
				return(true);
			}
			else
			{
				return(false);
			}

		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------