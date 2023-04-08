//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
class CBaseClass
{
//-------------------------------------------------------------------------------------------------------
	public:
		virtual void VirtualMethod(void)=0;

	public:
		CBaseClass(void)
		{
			std::wcout << L"CONSTRUCTOR BASE CLASS CALLED !\n" << std::endl;
		}

		CBaseClass(const CBaseClass&)
		{
			std::wcout << L"COPY CONSTRUCTOR BASE CLASS CALLED !\n" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------