//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "DummyBase.h"
//-------------------------------------------------------------------------------------------------------
class CDummyDerived : public CDummyBase
{
	public:
		virtual void PrintText(void);

	public:
		CDummyDerived(void);
		virtual ~CDummyDerived(void);
};
//-------------------------------------------------------------------------------------------------------