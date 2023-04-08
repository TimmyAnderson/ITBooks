//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CDefaultOperationsGenerationBase
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MFieldStringBase;
		int														MFieldIntBase;

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
		CDefaultOperationsGenerationBase(void)
			: MFieldStringBase(), MFieldIntBase()
		{
		}

		// !!!!! CLASS moze mat CONSTRUCTOR, ale NESMIE MAT COPY CONSTRUCTOR, MOVE CONSTRUCTOR, COPY OPERATOR=, MOVE OPERATOR= a DESTRUCTOR, inak sa DEFAULT OPERATIONS NEVYGENERUJU.
		CDefaultOperationsGenerationBase(const std::wstring& FieldStringBase, int FieldIntBase)
			: MFieldStringBase(FieldStringBase), MFieldIntBase(FieldIntBase)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------