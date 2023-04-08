//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CNonUniqueConversionBase1.h"
#include "CNonUniqueConversionBase2.h"
//-----------------------------------------------------------------------------
// !!!!! NEPOUZIVA sa VIRTUAL INHERITANCE.
class CNonUniqueConversionDerived : public CNonUniqueConversionBase1, public CNonUniqueConversionBase2
{
//-----------------------------------------------------------------------------
	public:
		CNonUniqueConversionDerived(void)
		{
		}

		virtual ~CNonUniqueConversionDerived(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------