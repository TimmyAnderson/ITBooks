//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "AccessControlBase.h"
//-------------------------------------------------------------------------------------------------------
// !!! Pouzijem PRIVATE INHERITANCE.
class CAccessControlDerivedUsingTest : private CAccessControlBase
{
	public:
		void Test(void);

	// !!!!! Pouzijem USING DECLARATIONS pre SPRISTUPNENIE MEMBERS, ktore by boli MIMO tejto CLASS NEPRISTUPNE.
	public:
		// !!! Spristupnit MEMBERS, ktore su pre SAMOTNU CLASS NEPRISTUPNE NIE JE MOZNE.
		//using CAccessControlBase::DummyPrivate;
		// !!!!! Spristupnim MEMBER, ktory by inak bol NEPRISTUPNY mimo tejto CLASS.
		using CAccessControlBase::DummyProtected;
		// !!!!! Spristupnim MEMBER, ktory by inak bol NEPRISTUPNY mimo tejto CLASS.
		using CAccessControlBase::DummyPublic;

	public:
		CAccessControlDerivedUsingTest(void);
		virtual ~CAccessControlDerivedUsingTest(void);
};
//-------------------------------------------------------------------------------------------------------