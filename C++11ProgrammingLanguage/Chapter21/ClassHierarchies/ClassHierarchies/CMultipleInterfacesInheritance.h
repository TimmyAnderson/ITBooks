//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CBaseInterface1.h"
#include "CBaseInterface2.h"
//-------------------------------------------------------------------------------------------------------
class CMultipleInterfacesInheritance : public CBaseInterface1, public CBaseInterface2
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue1;
		std::wstring											MValue2;

	public:
		virtual const std::wstring& GetValue1(void) const noexcept override
		{
			return(MValue1);
		}

		virtual const std::wstring& GetValue2(void) const noexcept override
		{
			return(MValue2);
		}

	public:
		CMultipleInterfacesInheritance(const std::wstring& Value1, const std::wstring& Value2)
			: MValue1(Value1), MValue2(Value2)
		{
		}

		virtual ~CMultipleInterfacesInheritance(void) override
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------