//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "Base.h"
//-------------------------------------------------------------------------------------------------------
class CDerived : public CBase
{
	public:
		virtual void PrintError(void);

	public:
		CDerived(void);
		CDerived(const CDerived& Original);
		virtual ~CDerived(void);
};
//-------------------------------------------------------------------------------------------------------