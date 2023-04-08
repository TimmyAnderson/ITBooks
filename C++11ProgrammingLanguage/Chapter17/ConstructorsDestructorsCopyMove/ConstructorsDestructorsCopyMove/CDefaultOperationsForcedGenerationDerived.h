//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "CDefaultOperationsForcedGenerationBase.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CDefaultOperationsForcedGenerationDerived : public CDefaultOperationsForcedGenerationBase
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MFieldStringDerived;
		int														MFieldIntDerived;

	public:
		// !!! COMPILER je PRINUTENY vygenerovat COPY OPERATOR=.
		CDefaultOperationsForcedGenerationDerived& operator=(const CDefaultOperationsForcedGenerationDerived&)=default;

		// !!! COMPILER je PRINUTENY vygenerovat MOVE OPERATOR=.
		CDefaultOperationsForcedGenerationDerived& operator=(CDefaultOperationsForcedGenerationDerived&&)=default;


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
		CDefaultOperationsForcedGenerationDerived(void)
			: CDefaultOperationsForcedGenerationBase(), MFieldStringDerived(), MFieldIntDerived()
		{
		}

		// !!!!! CLASS moze mat CONSTRUCTOR, ale NESMIE MAT COPY CONSTRUCTOR, MOVE CONSTRUCTOR, COPY OPERATOR=, MOVE OPERATOR= a DESTRUCTOR, inak sa DEFAULT OPERATIONS NEVYGENERUJU.
		CDefaultOperationsForcedGenerationDerived(const std::wstring& FieldStringBase, int FieldIntBase, const std::wstring& FieldStringDerived, int FieldIntDerived)
			: CDefaultOperationsForcedGenerationBase(FieldStringBase,FieldIntBase), MFieldStringDerived(FieldStringDerived), MFieldIntDerived(FieldIntDerived)
		{
		}

		// !!! COMPILER je PRINUTENY vygenerovat COPY CONSTRUCTOR.
		CDefaultOperationsForcedGenerationDerived(const CDefaultOperationsForcedGenerationDerived&)=default;

		// !!! COMPILER je PRINUTENY vygenerovat MOVE CONSTRUCTOR.
		CDefaultOperationsForcedGenerationDerived(CDefaultOperationsForcedGenerationDerived&&)=default;

		// !!!!! Kedze sa definoval aj DESTRUCTOR, tak DEFAULT OPERATIONS COMPILER by NEMAL GENEROVAT.
		// !!!!! Bohuzial v praxi tieto OPERATION COMPILER VYGENEROVAL, akurat MOVE OPERATIONS v skutocnosti NEROBIA MOVE OPERATIONS, ale COPY OPERATIONS.
		~CDefaultOperationsForcedGenerationDerived(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------