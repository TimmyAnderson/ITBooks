//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
class COverloadedFunctionScopeBase
{
//-----------------------------------------------------------------------------
	public:
		void OverloadedMethod(int Parameter)
		{
			std::wcout << L"METHOD COverloadedFunctionScopeBase::OverloadedMethod(INT) CALLED with Parameter [" << Parameter << L"] !" << std::endl;
		}

	public:
		COverloadedFunctionScopeBase(void)
		{
		}

		virtual ~COverloadedFunctionScopeBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------