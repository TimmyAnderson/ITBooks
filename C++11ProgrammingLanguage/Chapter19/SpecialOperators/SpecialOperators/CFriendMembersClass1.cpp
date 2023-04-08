//-----------------------------------------------------------------------------
#include "CFriendMembersClass1.h"
#include "CFriendMembers.h"
#include "CFriendTemplateClass.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CFriendMembersClass1::CFriendMembersClass1(void)
{
}
//-----------------------------------------------------------------------------
CFriendMembersClass1::~CFriendMembersClass1(void)
{
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CFriendMembersClass1::Test(void)
{
	std::wcout << L"METHOD CFriendMembersClass1::Test() STARTED !" << std::endl;

	CFriendMembers												Instance;

	// !!! Kedze CLASS 'CFriendMembersClass1' je FRIEND voci CLASS 'CFriendMembers', tak ze nej je mozne pristupit k PRIVATE MEMBERS.
	Instance.PrivateMethod();

	// !!! Kedze CLASS 'CFriendMembersClass1' je FRIEND voci CLASS 'CFriendMembers', tak ze nej je mozne pristupit k PROTECTED MEMBERS.
	Instance.ProtectedMethod();

	Instance.PublicMethod();

	std::wcout << L"METHOD CFriendMembersClass1::Test() FINISHED !" << std::endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CFriendMembersClass1::TestTemplateClass1(void)
{
	std::wcout << L"METHOD CFriendMembersClass1::TestTemplateClass1() STARTED !" << std::endl;

	CFriendTemplateClass<CFriendMembersClass1,CFriendMembersClass2>	Object;

	Object.PrivateMethod();
	Object.ProtectedMethod();
	Object.PublicMethod();

	std::wcout << L"METHOD CFriendMembersClass1::TestTemplateClass1() FINISHED !" << std::endl;
}
//-----------------------------------------------------------------------------
void CFriendMembersClass1::TestTemplateClass2(void)
{
	std::wcout << L"METHOD CFriendMembersClass1::TestTemplateClass2() STARTED !" << std::endl;

	CFriendTemplateClass<CFriendMembersClass1,CFriendMembersClass2>	Object;

	Object.PrivateMethod();
	Object.ProtectedMethod();
	Object.PublicMethod();

	std::wcout << L"METHOD CFriendMembersClass1::TestTemplateClass2() FINISHED !" << std::endl;
}
//-----------------------------------------------------------------------------