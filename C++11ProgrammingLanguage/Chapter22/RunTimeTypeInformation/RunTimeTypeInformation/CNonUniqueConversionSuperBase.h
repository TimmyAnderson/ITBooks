//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
class CNonUniqueConversionSuperBase
{
//-----------------------------------------------------------------------------
	public:
		virtual void PublicMethod(void) const
		{
			std::wcout << L"METHOD CNonUniqueConversionSuperBase::PublicMethod() CALLED !" << std::endl;
		}

	public:
		CNonUniqueConversionSuperBase(void)
		{
		}

		virtual ~CNonUniqueConversionSuperBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------