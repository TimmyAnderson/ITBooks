//-----------------------------------------------------------------------------
#include "CFriendMembersClass2.h"
#include "CFriendMembers.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CFriendMembersClass2::CFriendMembersClass2(void)
{
}
//-----------------------------------------------------------------------------
CFriendMembersClass2::~CFriendMembersClass2(void)
{
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CFriendMembersClass2::Test1(void)
{
	std::wcout << L"METHOD CFriendMembersClass2::Test1() STARTED !" << std::endl;

	CFriendMembers												Instance;

	// !!! Kedze METHOD CFriendMembersClass2::Test1() je FRIEND voci CLASS 'CFriendMembers1', tak ze nej je mozne pristupit k PRIVATE MEMBERS.
	Instance.PrivateMethod();

	// !!! Kedze METHOD CFriendMembersClass2::Test1() je FRIEND voci CLASS 'CFriendMembers1', tak ze nej je mozne pristupit k PROTECTED MEMBERS.
	Instance.ProtectedMethod();

	Instance.PublicMethod();

	std::wcout << L"METHOD CFriendMembersClass2::Test1() FINISHED !" << std::endl;
}
//-----------------------------------------------------------------------------
void CFriendMembersClass2::Test2(void)
{
	std::wcout << L"METHOD CFriendMembersClass2::Test2() STARTED !" << std::endl;

	CFriendMembers												Instance;

	// !!! Kedze METHOD CFriendMembersClass2::Test1() NIE je FRIEND voci CLASS 'CFriendMembers1', tak ze nej NIE JE mozne pristupit k PRIVATE MEMBERS.
	//Instance.PrivateMethod();

	// !!! Kedze METHOD CFriendMembersClass2::Test1() NIE je FRIEND voci CLASS 'CFriendMembers1', tak ze nej NIE JE mozne pristupit k PROTECTED MEMBERS.
	//Instance.ProtectedMethod();

	Instance.PublicMethod();

	std::wcout << L"METHOD CFriendMembersClass2::Test2() FINISHED !" << std::endl;
}
//-----------------------------------------------------------------------------