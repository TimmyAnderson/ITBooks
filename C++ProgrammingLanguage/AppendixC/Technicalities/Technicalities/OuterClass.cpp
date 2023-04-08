//-------------------------------------------------------------------------------------------------------
#include "OuterClass.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
COuterClass::COuterClass(void)
{
}
//-------------------------------------------------------------------------------------------------------
COuterClass::~COuterClass(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void COuterClass::OuterPrivate(void)
{
	CInnerClass													IC;
	static bool													JustOnce=true;

	if (JustOnce==false)
	{
		return;
	}

	JustOnce=false;


	// Nema ACCESS CONTROL RIGHTS.
	//IC.InnerPrivate();
	// Nema ACCESS CONTROL RIGHTS.
	//IC.InnerProtected();
	IC.InnerPublic();

	wprintf_s(L"void COuterClass::OuterPrivate(void) CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void COuterClass::OuterProtected(void)
{
	CInnerClass													IC;
	static bool													JustOnce=true;

	if (JustOnce==false)
	{
		return;
	}

	JustOnce=false;

	// Nema ACCESS CONTROL RIGHTS.
	//IC.InnerPrivate();
	// Nema ACCESS CONTROL RIGHTS.
	//IC.InnerProtected();
	IC.InnerPublic();

	wprintf_s(L"void COuterClass::OuterProtected(void) CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void COuterClass::OuterPublic(void)
{
	CInnerClass													IC;
	static bool													JustOnce=true;

	if (JustOnce==false)
	{
		return;
	}

	JustOnce=false;

	// Nema ACCESS CONTROL RIGHTS.
	//IC.InnerPrivate();
	// Nema ACCESS CONTROL RIGHTS.
	//IC.InnerProtected();
	IC.InnerPublic();

	wprintf_s(L"void COuterClass::OuterPublic(void) CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
COuterClass::CInnerClass::CInnerClass(void)
{
}
//-------------------------------------------------------------------------------------------------------
COuterClass::CInnerClass::~CInnerClass(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void COuterClass::CInnerClass::InnerPrivate(void)
{
	COuterClass													OC;
	static bool													JustOnce=true;

	if (JustOnce==false)
	{
		return;
	}

	JustOnce=false;

	// !!! Nema ACCESS CONTROL RIGHTS.
	OC.OuterPrivate();
	// !!! Nema ACCESS CONTROL RIGHTS.
	OC.OuterProtected();
	OC.OuterPublic();

	wprintf_s(L"void COuterClass::CInnerClass::InnerPrivate(void) CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void COuterClass::CInnerClass::InnerProtected(void)
{
	COuterClass													OC;
	static bool													JustOnce=true;

	if (JustOnce==false)
	{
		return;
	}

	JustOnce=false;

	// !!! Nema ACCESS CONTROL RIGHTS.
	// !!!!! Podla knihy by C++ NEMAL UMOZNIT ACCESS, avsak Visual C++ pristup UMOZNUJE.
	OC.OuterPrivate();
	// !!! Nema ACCESS CONTROL RIGHTS.
	// !!!!! Podla knihy by C++ NEMAL UMOZNIT ACCESS, avsak Visual C++ pristup UMOZNUJE.
	OC.OuterProtected();
	OC.OuterPublic();

	wprintf_s(L"void COuterClass::CInnerClass::InnerProtected(void) CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void COuterClass::CInnerClass::InnerPublic(void)
{
	COuterClass													OC;
	static bool													JustOnce=true;

	if (JustOnce==false)
	{
		return;
	}

	JustOnce=false;

	// Nema ACCESS CONTROL RIGHTS.
	// !!!!! Podla knihy by C++ NEMAL UMOZNIT ACCESS, avsak Visual C++ pristup UMOZNUJE.
	OC.OuterPrivate();
	// Nema ACCESS CONTROL RIGHTS.
	// !!!!! Podla knihy by C++ NEMAL UMOZNIT ACCESS, avsak Visual C++ pristup UMOZNUJE.
	OC.OuterProtected();
	OC.OuterPublic();

	wprintf_s(L"void COuterClass::CInnerClass::InnerPublic(void) CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------