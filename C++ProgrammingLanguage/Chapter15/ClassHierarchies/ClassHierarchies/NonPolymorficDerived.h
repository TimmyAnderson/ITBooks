//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "NonPolymorficBase.h"
//-------------------------------------------------------------------------------------------------------
class CNonPolymorficDerived : public CNonPolymorficBase
{
	public:
		CNonPolymorficDerived(void);
		// !!! CLASS je NEPOLYMORFNA a teda NESMIE MAT VIRTUALNY DESTUCTOR.
		~CNonPolymorficDerived(void);
};
//-------------------------------------------------------------------------------------------------------