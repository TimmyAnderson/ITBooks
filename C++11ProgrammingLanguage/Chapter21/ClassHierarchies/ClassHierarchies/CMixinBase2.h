//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CMixinSuperBase.h"
//-------------------------------------------------------------------------------------------------------
class CMixinBase2 : public virtual CMixinSuperBase
{
//-------------------------------------------------------------------------------------------------------
	public:
		virtual void BBB(void) const override
		{
			std::wcout << L"METHOD CMixinBase2::BBB() CALLED !" << std::endl;
		}

		virtual void CCC(void) const override
		{
			std::wcout << L"METHOD CMixinBase2::CCC() CALLED !" << std::endl;
		}

	public:
		CMixinBase2(void)
		{
		}

		virtual ~CMixinBase2(void) override
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------