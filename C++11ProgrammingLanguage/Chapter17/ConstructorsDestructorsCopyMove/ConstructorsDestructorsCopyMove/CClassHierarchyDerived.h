//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "CClassHierarchyBaseB1.h"
#include "CClassHierarchyBaseB2.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CClassHierarchyDerived final : public CClassHierarchyBaseB1, public CClassHierarchyBaseB2
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		CClassHierarchyDerived& operator=(const CClassHierarchyDerived& Value)
		{
			std::wcout << L"COPY OPERATOR= CClassHierarchyDerived CALLED !" << std::endl;

			CClassHierarchyBaseB1::operator=(Value);
			CClassHierarchyBaseB2::operator=(Value);

			MValue=Value.GetValue();

			return(*this);
		}

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

		void Print(const std::wstring& Prefix) const
		{
			std::wcout << Prefix;

			std::wcout << L" ValueVA [" << GetValueVA() << L"]";
			std::wcout << L" ValueA via B1 [" << static_cast<const CClassHierarchyBaseB1*>(this)->GetValueA() << L"]";
			std::wcout << L" ValueA via B2 [" << static_cast<const CClassHierarchyBaseB2*>(this)->GetValueA() << L"]";
			std::wcout << L" ValueB1 [" << GetValueB1() << L"]";
			std::wcout << L" ValueB2 [" << GetValueB2() << L"]";
			std::wcout << L" Value [" << GetValue() << L"]";

			std::wcout << L"] !" << std::endl;
		}

	public:
		CClassHierarchyDerived(int ValueVA, int ValueB1VA, int ValueB1A, int ValueB1, int ValueB2VA, int ValueB2A, int ValueB2, int Value)
			: CClassHierarchyVirtualBaseA(ValueVA), CClassHierarchyBaseB1(ValueB1VA,ValueB1A,ValueB1), CClassHierarchyBaseB2(ValueB2VA,ValueB2A,ValueB2), MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CClassHierarchyDerived CALLED !" << std::endl;
		}

		CClassHierarchyDerived(const CClassHierarchyDerived& Value)
			: CClassHierarchyVirtualBaseA(Value), CClassHierarchyBaseB1(Value), CClassHierarchyBaseB2(Value), MValue(Value.GetValue())
		{
			std::wcout << L"COPY CONSTRUCTOR CClassHierarchyDerived CALLED !" << std::endl;
		}

		virtual ~CClassHierarchyDerived(void) override
		{
			std::wcout << L"DESTRUCTOR ~CClassHierarchyDerived CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------