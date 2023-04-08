//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CBaseForArrayTest.h"
//-------------------------------------------------------------------------------------------------------
class CDerivedForArrayTest : public CBaseForArrayTest
{
//-------------------------------------------------------------------------------------------------------
	protected:
		std::wstring											MValue1;
		std::wstring											MValue2;

	public:
		virtual void VirtualMethod(void)
		{
			wprintf_s(L"VALUE [%ls], VALUE 1 [%ls], VALUE 2 [%ls] !\n",MValue.c_str(),MValue1.c_str(),MValue2.c_str());
		}

	public:
		CDerivedForArrayTest(std::wstring Value, std::wstring Value1, std::wstring Value2)
			: CBaseForArrayTest(Value), MValue1(Value1), MValue2(Value2)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------