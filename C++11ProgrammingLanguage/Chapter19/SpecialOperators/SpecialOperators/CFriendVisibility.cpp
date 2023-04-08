//-----------------------------------------------------------------------------
#include "CFriendVisibility.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
namespace FRIENDS
{
//-----------------------------------------------------------------------------
	CFriendVisibility::CFriendVisibility(void)
	{
	}
//-----------------------------------------------------------------------------
	CFriendVisibility::~CFriendVisibility(void)
	{
	}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	void CFriendVisibility::PrivateMethod(void)
	{
		std::wcout << L"METHOD CFriendVisibility::PrivateMethod() CALLED !" << std::endl;
	}
//-----------------------------------------------------------------------------
	void CFriendVisibility::ProtectedMethod(void)
	{
		std::wcout << L"METHOD CFriendVisibility::ProtectedMethod() CALLED !" << std::endl;
	}
//-----------------------------------------------------------------------------
	void CFriendVisibility::PublicMethod(void)
	{
		std::wcout << L"METHOD CFriendVisibility::PublicMethod() CALLED !" << std::endl;
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void FriendVisibilityFunction(void)
{
	std::wcout << L"FUNCTION FriendVisibilityFunction() STARTED !" << std::endl;

	FRIENDS::CFriendVisibility									Object;

	// !!!!! PRIVATE a PROTECTED METHODS SU PRISTUPNE vo FUNCTION FriendVisibilityFunction(), pretoze tak je FRIEND voci CLASS 'CFriendVisibility', a zaroven je definovane SKOR ako sa pouzil KEYWORD [friend].
	Object.PrivateMethod();
	Object.ProtectedMethod();
	Object.PublicMethod();

	std::wcout << L"FUNCTION FriendVisibilityFunction() FINISHED !" << std::endl;
}
//-----------------------------------------------------------------------------