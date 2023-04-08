//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CDefaultConstructorGeneration final
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
		// !!! COMPILER sa prinuti vygenerovat DEFAULT CONSTRUCTOR.
		// !!!!! FIELDS PRIMITIVE TYPES vsak tento CONSTRUCTOR ponecha NENAINICIALIZOVANE.
		CDefaultConstructorGeneration(void)=default;

		// !!!!! CLASS moze mat CONSTRUCTOR, ale NESMIE MAT COPY CONSTRUCTOR, MOVE CONSTRUCTOR, COPY OPERATOR=, MOVE OPERATOR= a DESTRUCTOR, inak sa DEFAULT OPERATIONS NEVYGENERUJU.
		CDefaultConstructorGeneration(const std::wstring& FieldString, int FieldInt)
			: MFieldString(FieldString), MFieldInt(FieldInt)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------