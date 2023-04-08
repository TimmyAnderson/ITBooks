//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CVirtualBase.h"
//-----------------------------------------------------------------------------
class CVirtualDerived : public CVirtualBase
{
//-----------------------------------------------------------------------------
	public:
		virtual void VirtualMethod(void) const override
		{
			std::wcout << "METHOD CVirtualDerived::VirtualMethod() CALLED !" << std::endl;
		}

	public:
		CVirtualDerived(void)
		{
			std::wcout << "CONSTRUCTOR CVirtualDerived::CVirtualDerived() CALLED !" << std::endl;
		}

		CVirtualDerived(const CVirtualDerived& Other)
			: CVirtualBase(Other)
		{
			std::wcout << "COPY CONSTRUCTOR CVirtualDerived::CVirtualDerived() CALLED !" << std::endl;
		}

		virtual ~CVirtualDerived(void) override
		{
			std::wcout << "DESTRUCTOR CVirtualDerived::CVirtualDerived() CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------