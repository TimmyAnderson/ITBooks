//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CDeletedDefaultOperations final
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MFieldString;
		int														MFieldInt;

	public:
		// !!! DELETED COPY OPERATOR= zabrani generovaniu DEFAULT COPY OPERATOR=.
		CDeletedDefaultOperations& operator=(const CDeletedDefaultOperations&)=delete;

		// !!! Kedze CLASS obsahuje aspon 1 DELETED DEFAULT OPERATION, C++ standardne NEGENERUJE ZIADNU DEFAULT OPERATION. Preto je COMPILER nutne pomocou SYNTAXE [OPERATION=default] prinutit vygenerovat DEFAULT MOVE OPERATOR=.
		CDeletedDefaultOperations& operator=(CDeletedDefaultOperations&&)=default;

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
		CDeletedDefaultOperations(void)
			: MFieldString(), MFieldInt()
		{
		}

		CDeletedDefaultOperations(const std::wstring& FieldString, int FieldInt)
			: MFieldString(FieldString), MFieldInt(FieldInt)
		{
		}

		// !!! DELETED COPY OPERATOR= zabrani generovaniu DEFAULT COPY CONSTRUCTOR.
		CDeletedDefaultOperations(const CDeletedDefaultOperations&)=delete;

		// !!! Kedze CLASS obsahuje aspon 1 DELETED DEFAULT OPERATION, C++ standardne NEGENERUJE ZIADNU DEFAULT OPERATION. Preto je COMPILER nutne pomocou SYNTAXE [OPERATION=default] prinutit vygenerovat DEFAULT MOVE CONSTRUCTOR.
		CDeletedDefaultOperations(CDeletedDefaultOperations&&)=default;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------