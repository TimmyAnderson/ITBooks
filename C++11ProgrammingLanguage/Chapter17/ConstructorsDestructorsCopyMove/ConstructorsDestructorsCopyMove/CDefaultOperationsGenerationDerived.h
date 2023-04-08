//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "CDefaultOperationsGenerationBase.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CDefaultOperationsGenerationDerived : public CDefaultOperationsGenerationBase
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MFieldStringDerived;
		int														MFieldIntDerived;

	public:
		const std::wstring& GetFieldStringDerived(void) const noexcept
		{
			return(MFieldStringDerived);
		}

		int GetFieldIntDerived(void) const noexcept
		{
			return(MFieldIntDerived);
		}

	public:
		void Print(const std::wstring& Prefix) const
		{
			std::wcout << Prefix << L" FIELD STRING BASE [" << GetFieldStringBase() << L"] FIELD INT BASE [" << GetFieldIntBase() << L"] FIELD STRING DERIVED [" << MFieldStringDerived << L"] FIELD INT DERIVED [" << MFieldIntDerived << L"] !" << std::endl;
		}

	public:
		// !!! Ak CLASS obsahuje CUSTOM CONSTRUCTOR, tak sa DEFAULT CONSTRUCTOR NEGENERUJE.
		CDefaultOperationsGenerationDerived(void)
			: CDefaultOperationsGenerationBase(), MFieldStringDerived(), MFieldIntDerived()
		{
		}

		// !!!!! CLASS moze mat CONSTRUCTOR, ale NESMIE MAT COPY CONSTRUCTOR, MOVE CONSTRUCTOR, COPY OPERATOR=, MOVE OPERATOR= a DESTRUCTOR, inak sa DEFAULT OPERATIONS NEVYGENERUJU.
		CDefaultOperationsGenerationDerived(const std::wstring& FieldStringBase, int FieldIntBase, const std::wstring& FieldStringDerived, int FieldIntDerived)
			: CDefaultOperationsGenerationBase(FieldStringBase,FieldIntBase), MFieldStringDerived(FieldStringDerived), MFieldIntDerived(FieldIntDerived)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------