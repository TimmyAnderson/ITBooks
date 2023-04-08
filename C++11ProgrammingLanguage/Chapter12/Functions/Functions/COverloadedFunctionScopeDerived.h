//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "COverloadedFunctionScopeBase.h"
//-----------------------------------------------------------------------------
class COverloadedFunctionScopeDerived : public COverloadedFunctionScopeBase
{
//-----------------------------------------------------------------------------
	public:
		void OverloadedMethod(double Parameter)
		{
			std::wcout << L"METHOD OverloadedMethod(DOUBLE) CALLED with Parameter [" << Parameter << L"] !" << std::endl;
		}

	public:
		void TestOverloadedFunction(void)
		{
			int													Integer=100;
			double												Double=123.456789987;

			// !!!!! Zavola sa METHOD COverloadedFunctionScopeDerived::OverloadedMethod(DOUBLE), pretoze METHOD COverloadedFunctionScopeBase::OverloadedMethod(INT) je definovana v PARENT CLASS, ktory NIE JE v CURRENT SCOPE a tym padom sa IGNORUJE pri OVERLOADED FUNCTION RESOLUTION.
			OverloadedMethod(Integer);

			OverloadedMethod(Double);
		}

	public:
		COverloadedFunctionScopeDerived(void)
		{
		}

		virtual ~COverloadedFunctionScopeDerived(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------