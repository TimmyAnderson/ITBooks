//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
class CVirtualBase
{
//-----------------------------------------------------------------------------
	public:
		virtual void VirtualMethod(void) const
		{
			std::wcout << "METHOD CVirtualBase::VirtualMethod() CALLED !" << std::endl;
		}

	public:
		CVirtualBase(void)
		{
			std::wcout << "CONSTRUCTOR CVirtualBase::CVirtualBase() CALLED !" << std::endl;
		}

		CVirtualBase(const CVirtualBase&)
		{
			std::wcout << "COPY CONSTRUCTOR CVirtualBase::CVirtualBase() CALLED !" << std::endl;
		}

		virtual ~CVirtualBase(void)
		{
			std::wcout << "DESTRUCTOR CVirtualBase::~CVirtualBase() CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------