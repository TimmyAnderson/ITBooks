//----------------------------------------------------------------------------------------------------------------------
#include "CFriendFunctionsNonTemplateClass2.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Kedze COMPILER NEPOVAZUJE FRIEND DECLARATION za FUNCTION DECLARATION, je nutne vykona explicitnu DECLARATION.
void FriendFunctions2Function2(int Value1, double Value2);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CFriendFunctionsNonTemplateClass2::CFriendFunctionsNonTemplateClass2(const CString& Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
CFriendFunctionsNonTemplateClass2::~CFriendFunctionsNonTemplateClass2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CFriendFunctionsNonTemplateClass2::CallFriendFunctions2Function2(int Value1, double Value2)
{
	// !!!!! COMPILER vola NON-TEMPLATE FUNCTION [void FriendFunctions2Function2(int Value1, double Value2)], a NIE TEMPLATE FUNCTION [void FriendFunctions2Function2(TType1 Value1, TType2 Value2)], pretoze NON-TEMPLATE FUNCTION je definovana na CLASS SCOPE, kym TEMPLATE FUNCTION az na NAMESPACE SCOPE.
	FriendFunctions2Function2(Value1,Value2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FriendFunctions2Function1(int Value1, double Value2)
{
	CFriendFunctionsNonTemplateClass2							Object(L"Timmy");

	// !!!!! Ak je FUNCTION deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
	wcout << L"NON-TEMPLATE FUNCTION 1 - FIELD [" << Object.MField << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void FriendFunctions2Function2(int Value1, double Value2)
{
	CFriendFunctionsNonTemplateClass2							Object(L"Timmy");

	// !!!!! Ak je FUNCTION deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
	wcout << L"NON-TEMPLATE FUNCTION 2 - FIELD [" << Object.MField << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------