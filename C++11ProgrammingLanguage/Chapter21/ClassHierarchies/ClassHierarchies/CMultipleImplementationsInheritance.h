//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CBaseClass1.h"
#include "CBaseClass2.h"
//-------------------------------------------------------------------------------------------------------
class CMultipleImplementationsInheritance : public CBaseClass1, public CBaseClass2
{
//-------------------------------------------------------------------------------------------------------
	public:
		CMultipleImplementationsInheritance(const std::wstring& Value1, const std::wstring& Value2)
			: CBaseClass1(Value1), CBaseClass2(Value2)
		{
		}

		virtual ~CMultipleImplementationsInheritance(void) override
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------