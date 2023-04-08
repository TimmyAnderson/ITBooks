//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CVirtualDestructorBase.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CVirtualDestructorDerived final : public CVirtualDestructorBase
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		virtual int GetValue(void) const noexcept override
		{
			return(MValue);
		}

	public:
		CVirtualDestructorDerived(int Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CVirtualDestructorDerived CALLED !" << std::endl;
		}

		virtual ~CVirtualDestructorDerived(void)
		{
			std::wcout << L"DESTRUCTOR ~CVirtualDestructorDerived CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------