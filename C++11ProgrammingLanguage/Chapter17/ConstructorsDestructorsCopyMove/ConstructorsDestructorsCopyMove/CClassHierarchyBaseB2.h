//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CClassHierarchyBaseA.h"
#include "CClassHierarchyVirtualBaseA.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CClassHierarchyBaseB2 : public virtual CClassHierarchyVirtualBaseA, public CClassHierarchyBaseA
{
//-----------------------------------------------------------------------------
	private:
		int														MValueB2;

	public:
		CClassHierarchyBaseB2& operator=(const CClassHierarchyBaseB2& Value)
		{
			std::wcout << L"COPY OPERATOR= CClassHierarchyBaseB2 CALLED !" << std::endl;

			CClassHierarchyVirtualBaseA::operator=(Value);
			CClassHierarchyBaseA::operator=(Value);

			MValueB2=Value.GetValueB2();

			return(*this);
		}

	public:
		int GetValueB2(void) const noexcept
		{
			return(MValueB2);
		}

	public:
		CClassHierarchyBaseB2(int ValueVA, int ValueA, int ValueB2)
			: CClassHierarchyVirtualBaseA(ValueVA), CClassHierarchyBaseA(ValueA), MValueB2(ValueB2)
		{
			std::wcout << L"CONSTRUCTOR CClassHierarchyBaseB2 CALLED !" << std::endl;
		}

		CClassHierarchyBaseB2(const CClassHierarchyBaseB2& Value)
			: CClassHierarchyVirtualBaseA(Value), CClassHierarchyBaseA(Value), MValueB2(Value.GetValueB2())
		{
			std::wcout << L"COPY CONSTRUCTOR CClassHierarchyBaseB2 CALLED !" << std::endl;
		}

		virtual ~CClassHierarchyBaseB2(void) override
		{
			std::wcout << L"DESTRUCTOR ~CClassHierarchyBaseB2 CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------