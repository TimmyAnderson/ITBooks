//----------------------------------------------------------------------------------------------------------------------
#include "CFriendClassFriendClassNonTemplate1.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CFriendClassFriendClassNonTemplate1::CFriendClassFriendClassNonTemplate1(const CFriendClassClassMakingFriends1<CString>& Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
CFriendClassFriendClassNonTemplate1::~CFriendClassFriendClassNonTemplate1(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CFriendClassFriendClassNonTemplate1::Print(void) const
{
	// !!! NON TEMPLATE CLASS moze pristupovat k PRIVATE MEMBERS, pretoze bola DECLARED ako FRIEND.
	wcout << L"FRIEND NON TEMPLATE CLASS 1 - VALUE [" << MField.MField << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------