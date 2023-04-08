//-----------------------------------------------------------------------------
#include "CFriendVisibilityTest.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
namespace FRIENDS
{
//-----------------------------------------------------------------------------
	CFriendVisibilityTest::CFriendVisibilityTest(void)
	{
	}
//-----------------------------------------------------------------------------
	CFriendVisibilityTest::~CFriendVisibilityTest(void)
	{
	}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	void CFriendVisibilityTest::Test(void)
	{
		std::wcout << L"METHOD CFriendVisibilityTest::Test() STARTED !" << std::endl;

		CFriendVisibility										Object;

		// !!!!! PRIVATE a PROTECTED METHODS SU PRISTUPNE v CLASS 'CFriendVisibilityTest', pretoze CLASS 'CFriendVisibilityTest' je FRIEND CLASS CLASS 'CFriendVisibility', a zaroven su definovane v ROVNAKOM NAMESPACE.
		Object.PrivateMethod();
		Object.ProtectedMethod();
		Object.PublicMethod();

		std::wcout << L"METHOD CFriendVisibilityTest::Test() FINISHED !" << std::endl;
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------