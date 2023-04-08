//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CBase.h"
#include <string>
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
class CDerived1 : public CBase
{
//-------------------------------------------------------------------------------------------------------
	public:
		virtual void VirtualMethod(void)
		{
			wprintf_s(L"METHOD CDerived1::VirtualMethod() CALLED for VALUE [%ls] !\n",MValue.c_str());
		}

	public:
		CDerived1(std::wstring Value)
			: CBase(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------