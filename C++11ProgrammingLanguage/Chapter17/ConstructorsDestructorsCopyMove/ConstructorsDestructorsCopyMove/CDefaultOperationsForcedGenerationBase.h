//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CDefaultOperationsForcedGenerationBase
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MFieldStringBase;
		int														MFieldIntBase;

	public:
		// !!! COMPILER je PRINUTENY vygenerovat COPY OPERATOR=.
		CDefaultOperationsForcedGenerationBase& operator=(const CDefaultOperationsForcedGenerationBase&)=default;

		// !!! COMPILER je PRINUTENY vygenerovat MOVE OPERATOR=.
		CDefaultOperationsForcedGenerationBase& operator=(CDefaultOperationsForcedGenerationBase&&)=default;

	public:
		const std::wstring& GetFieldStringBase(void) const noexcept
		{
			return(MFieldStringBase);
		}

		int GetFieldIntBase(void) const noexcept
		{
			return(MFieldIntBase);
		}

	public:
		// !!! Ak CLASS obsahuje CUSTOM CONSTRUCTOR, tak sa DEFAULT CONSTRUCTOR NEGENERUJE.
		CDefaultOperationsForcedGenerationBase(void)
			: MFieldStringBase(), MFieldIntBase()
		{
		}

		// !!!!! CLASS moze mat CONSTRUCTOR, ale NESMIE MAT COPY CONSTRUCTOR, MOVE CONSTRUCTOR, COPY OPERATOR=, MOVE OPERATOR= a DESTRUCTOR, inak sa DEFAULT OPERATIONS NEVYGENERUJU.
		CDefaultOperationsForcedGenerationBase(const std::wstring& FieldStringBase, int FieldIntBase)
			: MFieldStringBase(FieldStringBase), MFieldIntBase(FieldIntBase)
		{
		}

		// !!! COMPILER je PRINUTENY vygenerovat COPY CONSTRUCTOR.
		CDefaultOperationsForcedGenerationBase(const CDefaultOperationsForcedGenerationBase&)=default;

		// !!! COMPILER je PRINUTENY vygenerovat MOVE CONSTRUCTOR.
		CDefaultOperationsForcedGenerationBase(CDefaultOperationsForcedGenerationBase&&)=default;

		// !!!!! Kedze sa definoval aj DESTRUCTOR, tak DEFAULT OPERATIONS COMPILER by NEMAL GENEROVAT.
		// !!!!! Bohuzial v praxi tieto OPERATION COMPILER VYGENEROVAL, akurat MOVE OPERATIONS v skutocnosti NEROBIA MOVE OPERATIONS, ale COPY OPERATIONS.
		~CDefaultOperationsForcedGenerationBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------