//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CExplicitConstructors
{
//-----------------------------------------------------------------------------
	private:
		int														MFieldInt;
		std::wstring											MFieldString;

	public:
		void Print(void) const
		{
			std::wcout << L"FIELD INT [" << MFieldInt << L"] FIELD STRING [" << MFieldString << L"] !" << std::endl;
		}

	public:
		CExplicitConstructors(void)
			: MFieldInt(), MFieldString()
		{
			std::wcout << L"DEFAULT CONSTRUCTOR CALLED !" << std::endl;
		}

		CExplicitConstructors(const wchar_t* Param)
			: MFieldInt(), MFieldString(Param)
		{
			std::wcout << L"CONSTRUCTOR(CONST WCHAR_T*) CALLED with PARAMETERS (" << Param << L") !" << std::endl;
		}

		explicit CExplicitConstructors(int Param)
			: MFieldInt(Param), MFieldString()
		{
			std::wcout << L"EXPLICIT CONSTRUCTOR(INT) CALLED with PARAMETERS (" << Param << L") !" << std::endl;
		}

		CExplicitConstructors(const wchar_t* Param1, int Param2)
			: MFieldInt(Param2), MFieldString(Param1)
		{
			std::wcout << L"CONSTRUCTOR(CONST WCHAR_T*,INT) CALLED with PARAMETERS (" << Param1 << L"," << Param2 << L") !" << std::endl;
		}

		// !!! EXPLICIT CONSTRUCTORS mozu mat aj VIACERO PARAMETERS.
		explicit CExplicitConstructors(int Param1, const wchar_t* Param2)
			: MFieldInt(Param1), MFieldString(Param2)
		{
			std::wcout << L"EXPLICIT CONSTRUCTOR(INT,CONST WCHAR_T*) CALLED with PARAMETERS (" << Param1 << L"," << Param2 << L") !" << std::endl;
		}

		template<typename TType>
		CExplicitConstructors(std::initializer_list<TType>)=delete;

		virtual ~CExplicitConstructors(void)
		{
			std::wcout << L"DESTRUCTOR CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------