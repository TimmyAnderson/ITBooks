//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CClassHierarchyBaseA.h"
#include "CClassHierarchyVirtualBaseA.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CClassHierarchyBaseB1 : public virtual CClassHierarchyVirtualBaseA, public CClassHierarchyBaseA
{
//-----------------------------------------------------------------------------
	private:
		int														MValueB1;

	public:
		CClassHierarchyBaseB1& operator=(const CClassHierarchyBaseB1& Value)
		{
			std::wcout << L"COPY OPERATOR= CClassHierarchyBaseB1 CALLED !" << std::endl;

			CClassHierarchyVirtualBaseA::operator=(Value);
			CClassHierarchyBaseA::operator=(Value);

			MValueB1=Value.GetValueB1();

			return(*this);
		}

	public:
		int GetValueB1(void) const noexcept
		{
			return(MValueB1);
		}

	public:
		CClassHierarchyBaseB1(int ValueVA, int ValueA, int ValueB1)
			: CClassHierarchyVirtualBaseA(ValueVA), CClassHierarchyBaseA(ValueA), MValueB1(ValueB1)
		{
			std::wcout << L"CONSTRUCTOR CClassHierarchyBaseB1 CALLED !" << std::endl;
		}

		CClassHierarchyBaseB1(const CClassHierarchyBaseB1& Value)
			: CClassHierarchyVirtualBaseA(Value), CClassHierarchyBaseA(Value), MValueB1(Value.GetValueB1())
		{
			std::wcout << L"COPY CONSTRUCTOR CClassHierarchyBaseB1 CALLED !" << std::endl;
		}

		virtual ~CClassHierarchyBaseB1(void) override
		{
			std::wcout << L"DESTRUCTOR ~CClassHierarchyBaseB1 CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------