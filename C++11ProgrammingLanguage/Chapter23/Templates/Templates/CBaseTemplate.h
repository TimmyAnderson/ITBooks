//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
template<typename TType>
class CBaseTemplate
{
//-------------------------------------------------------------------------------------------------------
	public:
		virtual void TestFunction(void)
		{
			wprintf_s(L"FUNCTION CBaseTemplate::TestFunction() CALLED !\n");
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------