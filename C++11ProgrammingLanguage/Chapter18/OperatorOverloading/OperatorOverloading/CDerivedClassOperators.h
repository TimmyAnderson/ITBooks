//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "CBaseClassOperators.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CDerivedClassOperators final : public CBaseClassOperators
{
//-----------------------------------------------------------------------------
	public:
		virtual CBaseClassOperators operator-(const CBaseClassOperators& Value) override
		{
			std::wcout << "MEMBER CDerivedClassOperators::OPERATOR- CALLED !" << std::endl;

			return(GetValue()-Value.GetValue());
		}

	public:
		CDerivedClassOperators(int Value)
			: CBaseClassOperators(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------