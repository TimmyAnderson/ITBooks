//----------------------------------------------------------------------------------------------------------------------
#include "CFriendFunctionsNonTemplateClass3.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CFriendFunctionsNonTemplateClass3::CFriendFunctionsNonTemplateClass3(const CString& Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
CFriendFunctionsNonTemplateClass3::~CFriendFunctionsNonTemplateClass3(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FriendFunctions3Function1(int Value1, double Value2)
{
	CFriendFunctionsNonTemplateClass3							Object(L"Timmy");

	// !!!!! Ak je FUNCTION deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
	wcout << L"NON-TEMPLATE FUNCTION - FIELD [" << Object.MField << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------