//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "VirtualDestructorBase.h"
//-------------------------------------------------------------------------------------------------------
class CVirtualDestructorDerived : public CVirtualDestructorBase
{
	public:
		CVirtualDestructorDerived(void);
		virtual ~CVirtualDestructorDerived(void);
};
//-------------------------------------------------------------------------------------------------------