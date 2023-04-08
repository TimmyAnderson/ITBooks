//-----------------------------------------------------------------------------
#include "CustomManipulators.h"
#include <sstream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Alokuje sa INDEX do CUSTOM DATA ARRAY, ktory sa pouziva ako IDENTIFIER na pristup ku CUSTOM DATA.
const int														CUSTOM_DATA_INT_INDEX=std::ios_base::xalloc();
const int														CUSTOM_DATA_VOID_POINTER_INDEX=std::ios_base::xalloc();
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
wostream& AddIntegerCustomData(wostream& Stream, int ValueToSet)
{
	// !!! Do C++ STREAM OBJECT sa pridaju CUSTOM DATA.
	Stream.iword(CUSTOM_DATA_INT_INDEX)=ValueToSet;

	return(Stream);
}
//-----------------------------------------------------------------------------
wostream& AddVoidPointerCustomData(wostream& Stream, const std::wstring& ValueToSet)
{
	wstring*													Value=static_cast<wstring*>(Stream.pword(CUSTOM_DATA_VOID_POINTER_INDEX));

	if (Value!=nullptr)
	{
		delete(Value);
	}

	wstringstream												StringStream;

	StringStream << ValueToSet;

	// !!!!! MEMORY je alokovana DYNAMICKY, a preto je ju NUTNE UVOLNIT volanim OPERATOR DELETE. OPERATOR DELETE sa vola v USER DEFINED CALLBACK, ktory musi byt zaregistrovany pre dany C++ STREAM OBJECT.
	wstring*													NewValue=new wstring(StringStream.str());

	// !!! Do C++ STREAM OBJECT sa pridaju CUSTOM DATA.
	Stream.pword(CUSTOM_DATA_VOID_POINTER_INDEX)=NewValue;

	return(Stream);
}
//-----------------------------------------------------------------------------