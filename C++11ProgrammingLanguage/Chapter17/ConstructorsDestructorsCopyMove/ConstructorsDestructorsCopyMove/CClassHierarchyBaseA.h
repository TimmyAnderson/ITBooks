//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CClassHierarchyBaseA
{
//-----------------------------------------------------------------------------
	private:
		int														MValueA;

	public:
		CClassHierarchyBaseA& operator=(const CClassHierarchyBaseA& Value)
		{
			std::wcout << L"COPY OPERATOR= CClassHierarchyBaseA CALLED !" << std::endl;

			MValueA=Value.GetValueA();

			return(*this);
		}

	public:
		int GetValueA(void) const noexcept
		{
			return(MValueA);
		}

	public:
		CClassHierarchyBaseA(int ValueA)
			: MValueA(ValueA)
		{
			std::wcout << L"CONSTRUCTOR CClassHierarchyBaseA CALLED !" << std::endl;
		}

		CClassHierarchyBaseA(const CClassHierarchyBaseA& Value)
			: MValueA(Value.GetValueA())
		{
			std::wcout << L"COPY CONSTRUCTOR CClassHierarchyBaseA CALLED !" << std::endl;
		}

		virtual ~CClassHierarchyBaseA(void)
		{
			std::wcout << L"DESTRUCTOR ~CClassHierarchyBaseA CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------