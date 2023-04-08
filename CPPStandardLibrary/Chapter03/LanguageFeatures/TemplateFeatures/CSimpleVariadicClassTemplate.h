//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <sstream>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
// !!! TYPE PARAMETER [TTypes] reprezentuje TYPE PARAMETER PACK.
template<typename... TTypes>
// !!! Pomocou DERIVATION sa robi EXPANSION TYPE PARAMETER PACK [TTypes].
class CSimpleVariadicClassTemplate
{
//-------------------------------------------------------------------------------------------------------
	private:
		// !!!!! C++ NEUMOZNUJE deklarovat VARIABLES typu TYPE PARAMETER PACK.
		//TTypes												MFields1;
		// !!!!! C++ NEUMOZNUJE deklarovat VARIABLES typu EXPANDED TYPE PARAMETER PACK.
		//TTypes...												MFields2;
		// !!!!! C++ NEUMOZNUJE deklarovat VARIABLES typu EXPANDED TYPE PARAMETER PACK.
		//TTypes												MFields3...;
		// !!!!! C++ NEUMOZNUJE deklarovat VARIABLES typu EXPANDED TYPE PARAMETER PACK.
		//TTypes...												MFields4...;

	private:
		std::wstringstream										MStream;

	private:
		template<typename TFirstParameter, typename... TOtherParameters>
		void Serialize(TFirstParameter FirstParameter, TOtherParameters... OtherParameters)
		{
			MStream << L" [" << FirstParameter << L"]";

			Serialize(OtherParameters...);
		}

		void Serialize(void)
		{
			MStream << L" !" << std::endl;
		}

	public:
		void PrintBuffer(void)
		{
			std::wcout << MStream.str();
		}

	public:
		CSimpleVariadicClassTemplate(TTypes... Parameters)
			: MStream()
		{
			MStream << L"SERIALIZED VALUE";

			Serialize(Parameters...);
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------