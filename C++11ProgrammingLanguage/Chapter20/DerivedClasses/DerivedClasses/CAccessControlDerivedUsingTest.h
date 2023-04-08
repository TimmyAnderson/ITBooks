//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "CAccessControlBase.h"
//-----------------------------------------------------------------------------
// !!! Pouzije sa PRIVATE INHERITANCE.
class CAccessControlDerivedUsingTest : private CAccessControlBase
{
//-----------------------------------------------------------------------------
	public:
		void Test(void);

	// !!!!! Pouzije sa USING DECLARATIONS pre SPRISTUPNENIE MEMBERS, ktore by boli MIMO tejto CLASS NEPRISTUPNE.
	public:
		// !!! Spristupnit MEMBERS, ktore su pre SAMOTNU CLASS NEPRISTUPNE NIE JE MOZNE.
		//using CAccessControlBase::DummyPrivate;
		// !!!!! Spristupni sa MEMBER, ktory by inak bol NEPRISTUPNY mimo tejto CLASS.
		using CAccessControlBase::DummyProtected;
		// !!!!! Spristupni sa MEMBER, ktory by inak bol NEPRISTUPNY mimo tejto CLASS.
		using CAccessControlBase::DummyPublic;

	public:
		CAccessControlDerivedUsingTest(void);
		virtual ~CAccessControlDerivedUsingTest(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------