//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CDefaultOperationsForcedGeneration final
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MFieldString;
		int														MFieldInt;

	public:
		// !!! COMPILER je PRINUTENY vygenerovat COPY OPERATOR=.
		CDefaultOperationsForcedGeneration& operator=(const CDefaultOperationsForcedGeneration&)=default;

		// !!! COMPILER je PRINUTENY vygenerovat MOVE OPERATOR=.
		CDefaultOperationsForcedGeneration& operator=(CDefaultOperationsForcedGeneration&&)=default;

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
		CDefaultOperationsForcedGeneration(void)
			: MFieldString(), MFieldInt()
		{
		}

		// !!!!! CLASS moze mat CONSTRUCTOR, ale NESMIE MAT COPY CONSTRUCTOR, MOVE CONSTRUCTOR, COPY OPERATOR=, MOVE OPERATOR= a DESTRUCTOR, inak sa DEFAULT OPERATIONS NEVYGENERUJU.
		CDefaultOperationsForcedGeneration(const std::wstring& FieldString, int FieldInt)
			: MFieldString(FieldString), MFieldInt(FieldInt)
		{
		}

		// !!! COMPILER je PRINUTENY vygenerovat COPY CONSTRUCTOR.
		CDefaultOperationsForcedGeneration(const CDefaultOperationsForcedGeneration&)=default;

		// !!! COMPILER je PRINUTENY vygenerovat MOVE CONSTRUCTOR.
		CDefaultOperationsForcedGeneration(CDefaultOperationsForcedGeneration&&)=default;

		// !!!!! Kedze sa definoval aj DESTRUCTOR, tak DEFAULT OPERATIONS COMPILER by NEMAL GENEROVAT.
		// !!!!! Bohuzial v praxi tieto OPERATION COMPILER VYGENEROVAL, akurat MOVE OPERATIONS v skutocnosti NEROBIA MOVE OPERATIONS, ale COPY OPERATIONS.
		~CDefaultOperationsForcedGeneration(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------