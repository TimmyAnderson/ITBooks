//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
class CBase1
{
//-------------------------------------------------------------------------------------------------------
	public:
		virtual void VirtualMethod(void)=0;

	public:
		virtual void DoSomething(void)
		{
			wprintf_s(L"METHOD CBase1::DoSomething() CALLED !\n");
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------