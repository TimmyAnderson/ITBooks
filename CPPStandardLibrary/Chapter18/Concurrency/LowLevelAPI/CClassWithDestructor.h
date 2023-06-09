//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CClassWithDestructor
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MText;

	public:
		void Do(void)
		{
		}

	public:
		CClassWithDestructor(std::wstring Text)
			: MText(Text)
		{
		}

		~CClassWithDestructor(void)
		{
			std::wcout << L"DESTRUCTOR for [" << MText << L"] CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------