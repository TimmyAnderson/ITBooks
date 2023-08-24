//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION NON-TEMPLATE FUNCTION.
void FriendFunctions2Function1(int Value1, double Value2);
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION TEMPLATE FUNCTION.
template<typename TType1, typename TType2>
void FriendFunctions2Function1(TType1 Value1, TType2 Value2);
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION TEMPLATE FUNCTION.
template<typename TType1, typename TType2>
void FriendFunctions2Function2(TType1 Value1, TType2 Value2);
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION NON-TEMPLATE FUNCTION.
// !!!!! Ak by tu FUNCTION DECLARATION NEBOLA, tak by COMPILER tuto FUNCTION v inom [.CPP] FILE NENASIEL.
void FriendFunctions2Function3(int Value1, double Value2);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CFriendFunctionsNonTemplateClass2 final
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Ako FRIEND FUNCTION sa DEFINUJE NON-TEMPLATE FUNCTION [void FriendFunctions2Function1(int Value1, double Value2)], ale NIE TEMPLATE FUNCTION [void FriendFunctions2Function1(TType1 Value1, TType2 Value2)].
	friend void FriendFunctions2Function1(int Value1, double Value2);

	// !!! Ako FRIEND FUNCTION sa DEFINUJE NON-TEMPLATE FUNCTION [void FriendFunctions2Function2(int Value1, double Value2)], ale NIE TEMPLATE FUNCTION [void FriendFunctions2Function2(TType1 Value1, TType2 Value2)].
	// !!! Kedze FUNCTION [void FriendFunctions2Function2(int Value1, double Value2)] NEBOLA predtym DECLARED, tak je DECLARED tu pri definicii FRIEND FUNCTION.
	// !!!!!! Vyzera to, ze COMPILER NEPOVAZUJE FRIEND DECLARATION za FUNCTION DECLARATION.
	friend void FriendFunctions2Function2(int Value1, double Value2);

	// !!!!! FRIEND FUNCTION DECLARATION obsahuje aj FUNCTION DEFINITION.
	friend void FriendFunctions2Function3(int Value1, double Value2)
	{
		CFriendFunctionsNonTemplateClass2						Object(L"Timmy");

		// !!!!! Ak je FUNCTION deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
		std::wcout << L"NON-TEMPLATE FUNCTION 3 - FIELD [" << Object.MField << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << std::endl;
	}

	private:
		CString													MField;

	public:
		static void CallFriendFunctions2Function2(int Value1, double Value2);

	public:
		CFriendFunctionsNonTemplateClass2(const CString& MField);
		virtual ~CFriendFunctionsNonTemplateClass2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DEFINITION TEMPLATE FUNCTION.
template<typename TType1, typename TType2>
void FriendFunctions2Function1(TType1 Value1, TType2 Value2)
{
	CFriendFunctionsNonTemplateClass2							Object(L"Timmy");

	// !!!!! Ak je FUNCTION deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
	std::wcout << L"TEMPLATE FUNCTION 1 - FIELD [" << Object.MField << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! DEFINITION TEMPLATE FUNCTION.
template<typename TType1, typename TType2>
void FriendFunctions2Function2(TType1 Value1, TType2 Value2)
{
	CFriendFunctionsNonTemplateClass2							Object(L"Timmy");

	// !!!!! Ak je FUNCTION deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
	std::wcout << L"TEMPLATE FUNCTION 2 - FIELD [" << Object.MField << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------