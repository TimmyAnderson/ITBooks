//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CDefaultOperationsGeneration final
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MFieldString;
		int														MFieldInt;

	public:
		const std::wstring& GetFieldString(void) const noexcept
		{
			return(MFieldString);
		}

		int GetFieldInt(void) const noexcept
		{
			return(MFieldInt);
		}

	public:
		void Print(const std::wstring& Prefix) const
		{
			std::wcout << Prefix << L" FIELD STRING [" << MFieldString << L"] FIELD INT [" << MFieldInt << L"] !" << std::endl;
		}

	public:
		// !!! Ak CLASS obsahuje CUSTOM CONSTRUCTOR, tak sa DEFAULT CONSTRUCTOR NEGENERUJE.
		CDefaultOperationsGeneration(void)
			: MFieldString(), MFieldInt()
		{
		}

		// !!!!! CLASS moze mat CONSTRUCTOR, ale NESMIE MAT COPY CONSTRUCTOR, MOVE CONSTRUCTOR, COPY OPERATOR=, MOVE OPERATOR= a DESTRUCTOR, inak sa DEFAULT OPERATIONS NEVYGENERUJU.
		CDefaultOperationsGeneration(const std::wstring& FieldString, int FieldInt)
			: MFieldString(FieldString), MFieldInt(FieldInt)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------