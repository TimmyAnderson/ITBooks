//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CClassHierarchyVirtualBaseA
{
//-----------------------------------------------------------------------------
	private:
		int														MValueVA;

	public:
		CClassHierarchyVirtualBaseA& operator=(const CClassHierarchyVirtualBaseA& Value)
		{
			std::wcout << L"COPY OPERATOR= CClassHierarchyVirtualBaseA CALLED !" << std::endl;

			MValueVA=Value.GetValueVA();

			return(*this);
		}

	public:
		int GetValueVA(void) const noexcept
		{
			return(MValueVA);
		}

	public:
		CClassHierarchyVirtualBaseA(int ValueVA)
			: MValueVA(ValueVA)
		{
			std::wcout << L"CONSTRUCTOR CClassHierarchyVirtualBaseA CALLED !" << std::endl;
		}

		CClassHierarchyVirtualBaseA(const CClassHierarchyVirtualBaseA& Value)
			: MValueVA(Value.GetValueVA())
		{
			std::wcout << L"COPY CONSTRUCTOR CClassHierarchyVirtualBaseA CALLED !" << std::endl;
		}

		virtual ~CClassHierarchyVirtualBaseA(void)
		{
			std::wcout << L"DESTRUCTOR ~CClassHierarchyVirtualBaseA CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------