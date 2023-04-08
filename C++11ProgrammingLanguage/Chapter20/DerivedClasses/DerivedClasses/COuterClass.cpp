//-----------------------------------------------------------------------------
#include "COuterClass.h"
#include <iostream>
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
COuterClass::CInnerClass::CInnerClass(bool CallOuterClass)
	: MCallOuterClass(CallOuterClass)
{
}
//-----------------------------------------------------------------------------
COuterClass::CInnerClass::~CInnerClass(void)
{
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void COuterClass::CInnerClass::InnerPrivate(void)
{
	wcout << L"METHOD void COuterClass::CInnerClass::InnerPrivate(void) STARTED !" << endl;

	if (MCallOuterClass==true)
	{
		COuterClass												OuterClass(false);

		// !!!!! INNER CLASSES MOZU pristupovat k PRIVATE METHODS OUTER CLASSES.
		OuterClass.OuterPrivate();

		// !!!!! INNER CLASSES MOZU pristupovat k PROTECTED METHODS OUTER CLASSES.
		OuterClass.OuterProtected();

		OuterClass.OuterPublic();
	}

	wcout << L"METHOD void COuterClass::CInnerClass::InnerPrivate(void) FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void COuterClass::CInnerClass::InnerProtected(void)
{
	wcout << L"METHOD void COuterClass::CInnerClass::InnerProtected(void) STARTED !" << endl;

	if (MCallOuterClass==true)
	{
		COuterClass												OuterClass(false);

		// !!!!! INNER CLASSES MOZU pristupovat k PRIVATE METHODS OUTER CLASSES.
		OuterClass.OuterPrivate();

		// !!!!! INNER CLASSES MOZU pristupovat k PROTECTED METHODS OUTER CLASSES.
		OuterClass.OuterProtected();

		OuterClass.OuterPublic();
	}

	wcout << L"METHOD void COuterClass::CInnerClass::InnerProtected(void) FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void COuterClass::CInnerClass::InnerPublic(void)
{
	wcout << L"METHOD void COuterClass::CInnerClass::InnerPublic(void) STARTED !" << endl;

	if (MCallOuterClass==true)
	{
		COuterClass												OuterClass(false);

		// !!!!! INNER CLASSES MOZU pristupovat k PRIVATE METHODS OUTER CLASSES.
		OuterClass.OuterPrivate();

		// !!!!! INNER CLASSES MOZU pristupovat k PROTECTED METHODS OUTER CLASSES.
		OuterClass.OuterProtected();

		OuterClass.OuterPublic();
	}

	wcout << L"METHOD void COuterClass::CInnerClass::InnerPublic(void) FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
COuterClass::COuterClass(bool CallInnerClass)
	: MCallInnerClass(CallInnerClass)
{
}
//-----------------------------------------------------------------------------
COuterClass::~COuterClass(void)
{
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void COuterClass::OuterPrivate(void)
{
	wcout << L"METHOD void COuterClass::OuterPrivate(void) STARTED !" << endl;

	if (MCallInnerClass==true)
	{
		CInnerClass												InnerClass(false);

		// !!! OUTER CLASS NEMA ACCESS CONTROL RIGHTS k PRIVATE MEMBERS INNER CLASS.
		//InnerClass.InnerPrivate();

		// !!! OUTER CLASS NEMA ACCESS CONTROL RIGHTS k PROTECTED MEMBERS INNER CLASS.
		//InnerClass.InnerProtected();

		InnerClass.InnerPublic();
	}

	wcout << L"METHOD void COuterClass::OuterPrivate(void) FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void COuterClass::OuterProtected(void)
{
	wcout << L"METHOD void COuterClass::OuterProtected(void) STARTED !" << endl;

	if (MCallInnerClass==true)
	{
		CInnerClass												InnerClass(false);

		// !!! OUTER CLASS NEMA ACCESS CONTROL RIGHTS k PRIVATE MEMBERS INNER CLASS.
		//InnerClass.InnerPrivate();

		// !!! OUTER CLASS NEMA ACCESS CONTROL RIGHTS k PROTECTED MEMBERS INNER CLASS.
		//InnerClass.InnerProtected();

		InnerClass.InnerPublic();
	}

	wcout << L"METHOD void COuterClass::OuterProtected(void) FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void COuterClass::OuterPublic(void)
{
	wcout << L"METHOD void COuterClass::OuterPublic(void) STARTED !" << endl;

	if (MCallInnerClass==true)
	{
		CInnerClass												InnerClass(false);

		// !!! OUTER CLASS NEMA ACCESS CONTROL RIGHTS k PRIVATE MEMBERS INNER CLASS.
		//InnerClass.InnerPrivate();

		// !!! OUTER CLASS NEMA ACCESS CONTROL RIGHTS k PROTECTED MEMBERS INNER CLASS.
		//InnerClass.InnerProtected();

		InnerClass.InnerPublic();
	}

	wcout << L"METHOD void COuterClass::OuterPublic(void) FINISHED !" << endl;
}
//-----------------------------------------------------------------------------