//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include "MyDebug.h"
#include "CDerivedClass.h"
#include "CConstructorDerivedClass.h"
#include "CExplicitQualificationSuperDerived.h"
#include "CVirtualDerived.h"
#include "COverrideDerived.h"
#include "CFinalMethodSuperDerived.h"
#include "CFinalClassDerived.h"
#include "CMethodHidingDerived.h"
#include "CMethodHidingUncoverDerived.h"
#include "CConstructorInheritanceDerived.h"
#include "CReturnValueCovarianceDerived.h"
#include "CPureVirtualDerived.h"
#include "CMemberAccessRightDerived.h"
#include "CFriendMembers.h"
#include "CFriendMembersClass1.h"
#include "CFriendMembersClass2.h"
#include "CAccessControlBase.h"
#include "CAccessControlDerivedPrivate.h"
#include "CAccessControlDerivedProtected.h"
#include "CAccessControlDerivedUsingTest.h"
#include "CAccessControlMostDerivedPrivate.h"
#include "CAccessControlMostDerivedProtected.h"
#include "COuterClass.h"
#include "CUsingDeclarationAccessRightsDerived.h"
#include "CPointersToFields.h"
#include "CPointersToMethodsDerived.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestClassInheritance(void)
{
	PrintLineSeparator();

	CDerivedClass												Derived(L"AAA",111,L"BBB",2);

	wcout << L"BASE FIELDS [" << Derived.PrintBaseClassFields() << L"] !" << endl;

	wcout << L"DERIVED FIELDS [" << Derived.PrintDerivedClassFields() << L"] !" << endl;
	
	wcout << L"ALL FIELDS [" << Derived.PrintAllFields() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConstructorDestructor(void)
{
	PrintLineSeparator();

	{
		CConstructorDerivedClass								Derived;

		Derived.DoSomething();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVirtualMethods(void)
{
	PrintLineSeparator();

	{
		CVirtualBase*												BasePointer=new CVirtualDerived();

		// Volanie VIRTUAL METHOD cez POINTER.
		BasePointer->VirtualMethod();

		delete(BasePointer);
	}

	PrintLineSeparator();

	{
		CVirtualDerived												Derived;
		CVirtualBase&												BaseReference=Derived;

		// Volanie VIRTUAL METHOD cez REFERENCE.
		BaseReference.VirtualMethod();
	}

	PrintLineSeparator();

	{
		CVirtualDerived												Derived;

		// !!! Pri volani sa NEPOUZIJE POLYMORPHISM, pretoze sa pristupuje cez OBJECT a nie cez POINTER ci REFERENCE.
		Derived.VirtualMethod();

		// !!! Pouzije sa COPY CONSTRUCTOR, ktory vytvori KOPIU CLASS 'CVirtualBase' z OBJECT 'Derived'.
		CVirtualBase												Base=Derived;

		// !!! Pri volani sa NEPOUZIJE POLYMORPHISM a vola sa METHOD z BASE CLASS 'CVirtualBase'.
		Base.VirtualMethod();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestExplicitQualification(void)
{
	PrintLineSeparator();

	CExplicitQualificationDerived											Derived;

	Derived.DoResolution();

	PrintLineSeparator();

	// Vola sa METHOD z BASE CLASS 'CExplicitQualificationBase1'.
	Derived.CExplicitQualificationBase1::Overridden();

	PrintLineSeparator();

	// Vola sa METHOD z BASE CLASS 'CExplicitQualificationBase2'.
	Derived.CExplicitQualificationBase2::Overridden();

	PrintLineSeparator();

	Derived.NonOverridden1();

	PrintLineSeparator();
	
	Derived.NonOverridden2();

	PrintLineSeparator();

	CExplicitQualificationSuperDerived							SuperDerived;

	SuperDerived.DoGrandchildResolution();

	PrintLineSeparator();

	// Vola sa METHOD z BASE CLASS 'CExplicitQualificationBase1'.
	// !!! Ako BASE CLASSS sa pouziva CLASS 'CExplicitQualificationDerived'. Ta vsak METHOD NonOverridden1() NEDEFINUJE a tak C++ hlada tuto METHOD v BASE CLASSES.
	SuperDerived.CExplicitQualificationDerived::NonOverridden1();

	// Vola sa METHOD z BASE CLASS 'CExplicitQualificationBase2'.
	// !!! Ako BASE CLASSS sa pouziva CLASS 'CExplicitQualificationDerived'. Ta vsak METHOD NonOverridden2() NEDEFINUJE a tak C++ hlada tuto METHOD v BASE CLASSES.
	SuperDerived.CExplicitQualificationDerived::NonOverridden2();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOverrideKeyword(void)
{
	PrintLineSeparator();

	COverrideDerived											Derived;
	COverrideBase&												Base=Derived;

	Base.VirtualMethod();

	Base.NonVirtualMethod();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFinalMethodKeyword(void)
{
	PrintLineSeparator();

	CFinalMethodSuperDerived									SuperDerived;
	CFinalMethodBase&											BaseSuperDerived=SuperDerived;

	BaseSuperDerived.VirtualMethod1();
	BaseSuperDerived.VirtualMethod2();

	PrintLineSeparator();

	CFinalMethodDerived											Derived;
	CFinalMethodBase&											BaseDerived=Derived;

	BaseDerived.VirtualMethod1();
	BaseDerived.VirtualMethod2();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFinalClassKeyword(void)
{
	PrintLineSeparator();

	CFinalClassBase												Base;

	Base.VirtualMethod1();
	Base.VirtualMethod2();

	/*
	PrintLineSeparator();

	// CLASS 'CFinalClassDerived' je ZAKOMENTOVANA, pretoze jej BASE CLASS 'CFinalClassBase' je deklarovana ako FINAL a tym padom CLASS 'CFinalClassDerived' z nej NEMOZE byt DERIVED.
	CFinalClassDerived											Derived;
	CFinalClassBase&											BaseReference=Derived;

	BaseReference.VirtualMethod1();
	BaseReference.VirtualMethod2();
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMethodHiding(void)
{
	PrintLineSeparator();

	CMethodHidingDerived										Derived;

	// !!!!! Zavola sa METHOD CMethodHidingDerived::Method1(DOUBLE), namiesto prototypovo vhodnejsej METHOD CMethodHidingBase::Method1(INT). Je to preto, lebo C++ NEPODPORUJE METHOD OVERLOADING medzi BASE a DERIVED CLASSES.
	Derived.Method1(100);

	Derived.Method2(100);

	// !!!!! COMPILER hodi ERROR, pretoze METHOD CMethodHidingDerived::Method2(DOUBLE) PREKRYLA METHOD CMethodHidingBase::Method2(INT,INT) a to aj NAPRIEK TOMU, ze obe METHODS maju ROZNY POCET PARAMETERS.
	//Derived.Method2(100,100);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMethodHidingUncover(void)
{
	PrintLineSeparator();

	CMethodHidingUncoverDerived									Derived;

	// !!! Volaju sa METHODS z CLASS 'CMethodHidingUncoverDerived'.
	Derived.Method1(100.1);
	Derived.Method2(100);
	Derived.ProtectedMethod(100.1);
	Derived.PublicMethod(100.1);

	PrintLineSeparator();

	// !!!!! Volaju sa METHODS z CLASS 'CMethodHidingUncoverBase', ktore boli do CLASS 'CMethodHidingUncoverDerived' vytiahnute pomocou USING.
	Derived.Method1(100);
	Derived.Method2(100,200);

	PrintLineSeparator();

	// !!!!! Vola sa METHOD CMethodHidingUncoverBase::ProtectedMethod(INT) a to AJ NAPRIEK TOMU, ze v CLASS 'CMethodHidingUncoverBase' bola deklarovana ako PROTECTED. Pri prenose METHOD do CLASS 'CMethodHidingUncoverDerived' vsak USING SYNTAX bola aplikovana v PUBLIC BLOCK, a preto je METHOD PRISTUPNA.
	Derived.ProtectedMethod(100);

	// !!!!! COMPILER hodi ERROR, pretoze METHOD CMethodHidingUncoverBase::PublicMethod(INT) sice BOLA prenesena do CLASS 'CMethodHidingUncoverDerived', no USING SYNTAX bola aplikovana v PRIVATE BLOCK a tym padom je METHOD NEPRISTUPNA.
	//Derived.PublicMethod(100);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConstructorInheritance(void)
{
	PrintLineSeparator();

	{
		// CONSTRUCTOR je definovany PRIAMO v CLASS 'CConstructorInheritanceDerived'.
		CConstructorInheritanceDerived								Derived(100,100,100);

		Derived.DoSomething();
	}

	PrintLineSeparator();

	{
		// CONSTRUCTOR bol PRENESENY z CLASS 'CConstructorInheritanceBase'.
		CConstructorInheritanceDerived								Derived(100,100);

		Derived.DoSomething();
	}

	PrintLineSeparator();

	{
		// CONSTRUCTOR bol PRENESENY z CLASS 'CConstructorInheritanceBase'.
		CConstructorInheritanceDerived								Derived(100);

		Derived.DoSomething();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReturnValueCovariance(void)
{
	PrintLineSeparator();

	CReturnValueCovarianceDerived								Derived;
	CReturnValueCovarianceBase&									Base=Derived;

	Derived.DoSomething();
	Base.DoSomething();

	PrintLineSeparator();

	// !!! Aplikuje sa COVARIANCE. Aj ked METHOD CReturnValueCovarianceBase::VirtualMethod() ako RETURN VALUE deklarovala POINTER na CLASS 'CReturnValueCovarianceBase', tak OVERRIDDEN METHOD CReturnValueCovarianceDerived::VirtualMethod() vracia POINTER na 'CReturnValueCovarianceDerived'.
	CReturnValueCovarianceDerived*								PointerToDerived=Derived.VirtualMethod();

	PointerToDerived->DoSomething();

	delete(PointerToDerived);

	PrintLineSeparator();

	CReturnValueCovarianceBase*									PointerToBase=Base.VirtualMethod();

	PointerToBase->DoSomething();

	delete(PointerToBase);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPureVirtualMethods(void)
{
	PrintLineSeparator();

	CPureVirtualDerived											Derived;
	CPureVirtualBase&											Base=Derived;

	Base.PureVirtualMethod();

	PrintLineSeparator();

	// !!! Vola aj PURE VIRTUAL METHOD z CLASS 'CPureVirtualBase'.
	Base.PureVirtualMethodWithDefinition();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMemberAccessRights(void)
{
	PrintLineSeparator();

	CMemberAccessRightDerived									Derived;

	Derived.Test();

	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze PRIVATE METHODS NIE JE mozne volat z DERIVED CLASSES.
	//Derived.PrivateMethod();

	// !!! COMPILER hodi ERROR, pretoze PROTECTED METHODS NIE JE mozne volat mimo CLASS ci DERIVED CLASSES.
	//Derived.ProtectedMethod();

	Derived.PublicMethod();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFriends(void)
{
	PrintLineSeparator();

	CFriendMembersClass1										Members1;

	Members1.Test();

	PrintLineSeparator();

	CFriendMembersClass2										Members2;

	Members2.Test1();

	PrintLineSeparator();

	Members2.Test2();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInheritanceAccessRights1(void)
{
	PrintLineSeparator();

	CAccessControlDerivedPrivate								Object;

	// Je to PRIVATE METHOD.
	//Object.BasePrivate();

	// Je to PROTECTED METHOD.
	//Object.BaseProtected();

	// !!! Pouziva sa PRIVATE INHERITANCE a preto ju NIE JE MOZNE VOLAT.
	//Object.BasePublic();

	Object.TestDerivedPrivate();

	/*
	PrintLineSeparator();

	CAccessControlDerivedPrivate								TempObject;

	// !!! CONVERSION ZLYHA, pretoze je pouzita PRIVATE INHERITANCE.
	CAccessControlBase&											Reference=TempObject;

	Reference.ExternalConversionSucceeded(L"CAccessControlDerivedPrivate ---> CAccessControlBase");
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInheritanceAccessRights2(void)
{
	PrintLineSeparator();

	CAccessControlDerivedProtected								Object;

	// Je to PRIVATE METHOD.
	//Object.BasePrivate();

	// Je to PROTECTED METHOD.
	//Object.BaseProtected();

	// !!! Pouziva sa PROTECTED INHERITANCE a preto ju NIE JE MOZNE VOLAT.
	//Object.BasePublic();

	Object.TestDerivedProtected();

	/*
	PrintLineSeparator();

	CAccessControlDerivedProtected								TempObject;

	// !!! CONVERSION ZLYHA, pretoze je pouzita PROTECTED INHERITANCE.
	CAccessControlBase&											Reference=TempObject;

	Reference.ExternalConversionSucceeded(L"CAccessControlDerivedProtected ---> CAccessControlBase");
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInheritanceAccessRights3(void)
{
	PrintLineSeparator();

	CAccessControlMostDerivedPrivate							Object;

	// Je to PRIVATE METHOD.
	//Object.BasePrivate();

	// Je to PROTECTED METHOD.
	//Object.BaseProtected();

	// Pouziva sa PRIVATE INHERITANCE a preto ju NIE JE MOZNE VOLAT.
	//Object.BasePublic();

	Object.TestDerivedPrivate();

	PrintLineSeparator();

	Object.TestMostDerivedPrivate();

	/*
	PrintLineSeparator();

	CAccessControlMostDerivedPrivate							TempObject;

	// !!! CONVERSION ZLYHA, pretoze je pouzita PRIVATE INHERITANCE.
	CAccessControlBase&											Reference=TempObject;

	Reference.ExternalConversionSucceeded(L"CAccessControlMostDerivedPrivate ---> CAccessControlBase");
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInheritanceAccessRights4(void)
{
	PrintLineSeparator();

	CAccessControlMostDerivedProtected							Object;

	// Je to PRIVATE METHOD.
	//Object.BasePrivate();

	// Je to PROTECTED METHOD.
	//Object.BaseProtected();

	// Pouziva sa PROTECTED INHERITANCE a preto ju NIE JE MOZNE VOLAT.
	//Object.BasePublic();

	Object.TestDerivedProtected();

	PrintLineSeparator();

	Object.TestMostDerivedProtected();

	/*
	PrintLineSeparator();

	CAccessControlMostDerivedProtected							TempObject;

	// !!! CONVERSION ZLYHA, pretoze je pouzita PROTECTED INHERITANCE.
	CAccessControlBase&											Reference=TempObject;

	Reference.ExternalConversionSucceeded(L"CAccessControlMostDerivedProtected ---> CAccessControlBase");
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInheritanceAccessRights5(void)
{
	PrintLineSeparator();

	CAccessControlDerivedUsingTest								Object;

	// Je to PRIVATE METHOD.
	//Object.BasePrivate();

	// !!! Je to PROTECTED METHOD, ktora NEPOUZIVA na zviditelnenie USING DECLARAION a kedze sa pouziva PRIVATE INHERITANCE, tak je NEPRISTUPNA.
	//Object.BaseProtected();

	// !!! Je to PUBLIC METHOD, ktora NEPOUZIVA na zviditelnenie USING DECLARAION a kedze sa pouziva PRIVATE INHERITANCE, tak je NEPRISTUPNA.
	//Object.BasePublic();

	// !!! Je to PRIVATE METHOD a ta je nepristupna i pre CLASS 'CAccessControlDerivedUsingTest', a preto ju ta ANI cez USING DECLARAION NEMOZE SPRISTUPNIT.
	//Object.DummyPrivate();

	// !!! Je to PROTECTED METHOD, ktora POUZIVA na zviditelnenie USING DECLARAION. Pouzitie USING DECLARAION je NUTNE, lebo sa pouziva PRIVATE INHERITANCE.
	Object.DummyProtected();

	PrintLineSeparator();

	// !!! Je to PUBLIC METHOD, ktora POUZIVA na zviditelnenie USING DECLARAION. Pouzitie USING DECLARAION je NUTNE, lebo sa pouziva PRIVATE INHERITANCE.
	Object.DummyPublic();
	
	PrintLineSeparator();

	Object.Test();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAccessRightOuterInnerClass(void)
{
	PrintLineSeparator();

	COuterClass													OuterClass(true);

	// !!! CLASS je pristupna LEBO je definovana ako PUBLIC. Ak by bola PRIVATE, tak by NEBOLA PRISTUPNA.
	COuterClass::CInnerClass									InnerClass(true);

	OuterClass.OuterPublic();

	PrintLineSeparator();

	InnerClass.InnerPublic();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUsingDeclarationAccessRights(void)
{
	PrintLineSeparator();

	CUsingDeclarationAccessRightsDerived						Derived;

	Derived.Test();

	PrintLineSeparator();

	Derived.PublicMethod();

	PrintLineSeparator();

	// !!! PROTECTED METHOD CUsingDeclarationAccessRightsBase::ProtectedMethod() bola v CLASS 'CUsingDeclarationAccessRightsDerived' spristupnena pomocou USING SYNTAX.
	Derived.ProtectedMethod();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ProcessPointersToFields(wstring CPointersToFields::*PointerToString, int CPointersToFields::*PointerToInt)
{
	CPointersToFields											Object;
	CPointersToFields*											PointerToObject=&Object;

	// !!!!! Kedze VARIABLE 'PointerToString' je uz nastavena na FIELD 'MString2', je ju mozne hned aplikovat.
	PointerToObject->*PointerToString=L"Timmy Anderson";

	// !!!!! Kedze VARIABLE 'PointerToInt' je uz nastavena na FIELD 'MInt2', je ju mozne hned aplikovat.
	PointerToObject->*PointerToInt=12;

	// !!!!! POINTERS na FIELDS su interne implementovane ako INDEXES do CLASS a nie ako realne POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"VARIABLES - PointerToString [" << PointerToString << L"] PointerToInt [" << PointerToInt << L"] !" << endl;

	// !!!!! POINTERS na FIELDS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"VARIABLES - PointerToString [%p] PointerToInt [%p] !\n",PointerToString,PointerToInt);

	Object.Print();
}
//-----------------------------------------------------------------------------
void TestPointersToFields(void)
{
	PrintLineSeparator();

	CPointersToFields											Object1;
	CPointersToFields*											PointerToObject1=&Object1;

	wstring														CPointersToFields::*PointerToString=nullptr;
	int															CPointersToFields::*PointerToInt=nullptr;

	// !!!!! POINTERS na FIELDS su interne implementovane ako INDEXES do CLASS a nie ako realne POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"VARIABLES - PointerToString [" << PointerToString << L"] PointerToInt [" << PointerToInt << L"] !" << endl;

	// !!!!! POINTERS na FIELDS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"VARIABLES - PointerToString [%p] PointerToInt [%p] !\n",PointerToString,PointerToInt);

	Object1.Print();

	PrintLineSeparator();

	// !!! COMPILER hodi ERROR. FIELD 'MPrivate' je oznaceny ako PRIVATE, a preto k nemu NIE JE mozne pristupovat cez POINTERS to FIELDS.
	//PointerToString=&CPointersToFields::MPrivate;

	// !!! COMPILER hodi ERROR. FIELD 'MStatic' je STATIC FIELD, ktore NIE JE mozne priradzovat do POINTERS to FIELDS.
	//PointerToString=&CPointersToFields::MStatic;

	// !!! Do POINTERS na FIELDS sa priradia FIELDS.
	PointerToString=&CPointersToFields::MString1;
	PointerToInt=&CPointersToFields::MInt1;

	// !!!!! POINTERS na FIELDS su interne implementovane ako INDEXES do CLASS a nie ako realne POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"VARIABLES - PointerToString [" << PointerToString << L"] PointerToInt [" << PointerToInt << L"] !" << endl;

	// !!!!! POINTERS na FIELDS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"VARIABLES - PointerToString [%p] PointerToInt [%p] !\n",PointerToString,PointerToInt);

	// !!! POINTERS na FIELDS sa aplikuju na OBJECT.
	Object1.*PointerToString=L"AAA";
	Object1.*PointerToInt=10;

	Object1.Print();

	PrintLineSeparator();

	// !!! Do POINTERS na FIELDS sa priradia ine FIELDS.
	PointerToString=&CPointersToFields::MString2;
	PointerToInt=&CPointersToFields::MInt2;

	// !!!!! POINTERS na FIELDS su interne implementovane ako INDEXES do CLASS a nie ako realne POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"VARIABLES - PointerToString [" << PointerToString << L"] PointerToInt [" << PointerToInt << L"] !" << endl;

	// !!!!! POINTERS na FIELDS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"VARIABLES - PointerToString [%p] PointerToInt [%p] !\n",PointerToString,PointerToInt);

	// !!! POINTERS na FIELDS sa aplikuju na POINTER na OBJECT.
	PointerToObject1->*PointerToString=L"BBB";
	PointerToObject1->*PointerToInt=20;

	Object1.Print();

	PrintLineSeparator();

	ProcessPointersToFields(PointerToString,PointerToInt);

	PrintLineSeparator();

	CPointersToFields											Object2;
	CPointersToFields*											PointerToObject2=&Object2;

	// !!!!! POINTERS na FIELDS su interne implementovane ako INDEXES do CLASS a nie ako realne POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"VARIABLES - PointerToString [" << PointerToString << L"] PointerToInt [" << PointerToInt << L"] !" << endl;

	// !!!!! POINTERS na FIELDS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"VARIABLES - PointerToString [%p] PointerToInt [%p] !\n",PointerToString,PointerToInt);

	// !!!!! Kedze VARIABLE 'PointerToString' je uz nastavena na FIELD 'MString2', je ju mozne hned aplikovat na INY OBJECT.
	PointerToObject2->*PointerToString=L"Jenny Thompson";

	// !!!!! Kedze VARIABLE 'PointerToInt' je uz nastavena na FIELD 'MInt2', je ju mozne hned aplikovat na INY OBJECT.
	PointerToObject2->*PointerToInt=13;

	PointerToObject2->Print();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPointersToMethods(void)
{
	PrintLineSeparator();

	CPointersToMethodsBase										Object1(L"XXX");
	CPointersToMethodsBase*										PointerToObject1=&Object1;

	void														(CPointersToMethodsBase::*PointerToMethod0Parameters)(void) const=nullptr;
	void														(CPointersToMethodsBase::*PointerToMethod1Parameters)(const wstring&) const=nullptr;
	void														(CPointersToMethodsBase::*PointerToMethod2Parameters)(const wstring&,int) const=nullptr;

	wcout << L"METHODS - PointerToMethod0Parameters [" << PointerToMethod0Parameters << L"] PointerToMethod1Parameters [" << PointerToMethod1Parameters << L"] PointerToMethod2Parameters [" << PointerToMethod2Parameters << L"] !" << endl;
	wprintf(L"METHODS - PointerToMethod0Parameters [%p] PointerToMethod1Parameters [%p] PointerToMethod2Parameters [%p] !\n",PointerToMethod0Parameters,PointerToMethod1Parameters,PointerToMethod2Parameters);

	PrintLineSeparator();

	// !!! COMPILER hodi ERROR. METHOD CPointersToMethodsBase::PrivateMethod() je oznacena ako PRIVATE, a preto k nemu NIE JE mozne pristupovat cez POINTERS to METHODS.
	//PointerToMethod0Parameters=&CPointersToMethodsBase::PrivateMethod;

	// !!! COMPILER hodi ERROR. METHOD CPointersToMethodsBase::StaticMethod() je STATIC METHOD, ktore NIE JE mozne priradzovat do POINTERS to METHODS.
	//PointerToMethod0Parameters=&CPointersToMethodsBase::StaticMethod;

	// !!! Do POINTERS na METHODS sa priradia NON-VIRTUAL METHODS.
	PointerToMethod0Parameters=&CPointersToMethodsBase::NonVirtualMethod1;
	PointerToMethod1Parameters=&CPointersToMethodsBase::NonVirtualMethod1;
	PointerToMethod2Parameters=&CPointersToMethodsBase::NonVirtualMethod1;

	// !!!!! POINTERS na METHODS su interne implementovane ako klasicke POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"METHODS - PointerToMethod0Parameters [" << PointerToMethod0Parameters << L"] PointerToMethod1Parameters [" << PointerToMethod1Parameters << L"] PointerToMethod2Parameters [" << PointerToMethod2Parameters << L"] !" << endl;

	// !!!!! POINTERS na METHODS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"METHODS - PointerToMethod0Parameters [%p] PointerToMethod1Parameters [%p] PointerToMethod2Parameters [%p] !\n",PointerToMethod0Parameters,PointerToMethod1Parameters,PointerToMethod2Parameters);

	// !!! POINTERS na METHODS sa aplikuju na OBJECT.
	(Object1.*PointerToMethod0Parameters)();
	(Object1.*PointerToMethod1Parameters)(L"AAA");
	(Object1.*PointerToMethod2Parameters)(L"AAA",10);
	
	PrintLineSeparator();

	// !!! Do POINTERS na METHODS sa priradia ine NON-VIRTUAL METHODS.
	PointerToMethod0Parameters=&CPointersToMethodsBase::NonVirtualMethod2;
	PointerToMethod1Parameters=&CPointersToMethodsBase::NonVirtualMethod2;
	PointerToMethod2Parameters=&CPointersToMethodsBase::NonVirtualMethod2;

	// !!!!! POINTERS na METHODS su interne implementovane ako klasicke POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"METHODS - PointerToMethod0Parameters [" << PointerToMethod0Parameters << L"] PointerToMethod1Parameters [" << PointerToMethod1Parameters << L"] PointerToMethod2Parameters [" << PointerToMethod2Parameters << L"] !" << endl;

	// !!!!! POINTERS na METHODS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"METHODS - PointerToMethod0Parameters [%p] PointerToMethod1Parameters [%p] PointerToMethod2Parameters [%p] !\n",PointerToMethod0Parameters,PointerToMethod1Parameters,PointerToMethod2Parameters);

	// !!! POINTERS na METHODS sa aplikuju na POINTER na OBJECT.
	(PointerToObject1->*PointerToMethod0Parameters)();
	(PointerToObject1->*PointerToMethod1Parameters)(L"BBB");
	(PointerToObject1->*PointerToMethod2Parameters)(L"BBB",20);

	PrintLineSeparator();

	// !!! Do POINTERS na METHODS sa priradia VIRTUAL METHODS.
	PointerToMethod0Parameters=&CPointersToMethodsBase::VirtualMethod1;
	PointerToMethod1Parameters=&CPointersToMethodsBase::VirtualMethod1;
	PointerToMethod2Parameters=&CPointersToMethodsBase::VirtualMethod1;

	// !!!!! POINTERS na METHODS su interne implementovane ako INDEXES do CLASS a nie ako realne POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"METHODS - PointerToMethod0Parameters [" << PointerToMethod0Parameters << L"] PointerToMethod1Parameters [" << PointerToMethod1Parameters << L"] PointerToMethod2Parameters [" << PointerToMethod2Parameters << L"] !" << endl;

	// !!!!! POINTERS na METHODS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"METHODS - PointerToMethod0Parameters [%p] PointerToMethod1Parameters [%p] PointerToMethod2Parameters [%p] !\n",PointerToMethod0Parameters,PointerToMethod1Parameters,PointerToMethod2Parameters);

	// !!! POINTERS na METHODS sa aplikuju na OBJECT.
	(Object1.*PointerToMethod0Parameters)();
	(Object1.*PointerToMethod1Parameters)(L"CCC");
	(Object1.*PointerToMethod2Parameters)(L"CCC",30);

	PrintLineSeparator();

	// !!! Do POINTERS na METHODS sa priradia ine VIRTUAL METHODS.
	PointerToMethod0Parameters=&CPointersToMethodsBase::VirtualMethod2;
	PointerToMethod1Parameters=&CPointersToMethodsBase::VirtualMethod2;
	PointerToMethod2Parameters=&CPointersToMethodsBase::VirtualMethod2;

	// !!!!! POINTERS na METHODS su interne implementovane ako INDEXES do CLASS a nie ako realne POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"METHODS - PointerToMethod0Parameters [" << PointerToMethod0Parameters << L"] PointerToMethod1Parameters [" << PointerToMethod1Parameters << L"] PointerToMethod2Parameters [" << PointerToMethod2Parameters << L"] !" << endl;

	// !!!!! POINTERS na METHODS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"METHODS - PointerToMethod0Parameters [%p] PointerToMethod1Parameters [%p] PointerToMethod2Parameters [%p] !\n",PointerToMethod0Parameters,PointerToMethod1Parameters,PointerToMethod2Parameters);

	// !!! POINTERS na METHODS sa aplikuju na POINTER na OBJECT.
	(PointerToObject1->*PointerToMethod0Parameters)();
	(PointerToObject1->*PointerToMethod1Parameters)(L"DDD");
	(PointerToObject1->*PointerToMethod2Parameters)(L"DDD",40);

	PrintLineSeparator();

	CPointersToMethodsBase										Object2(L"YYY");
	CPointersToMethodsBase*										PointerToObject2=&Object2;

	// !!!!! POINTERS na METHODS su interne implementovane ako INDEXES do CLASS a nie ako realne POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"METHODS - PointerToMethod0Parameters [" << PointerToMethod0Parameters << L"] PointerToMethod1Parameters [" << PointerToMethod1Parameters << L"] PointerToMethod2Parameters [" << PointerToMethod2Parameters << L"] !" << endl;

	// !!!!! POINTERS na METHODS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"METHODS - PointerToMethod0Parameters [%p] PointerToMethod1Parameters [%p] PointerToMethod2Parameters [%p] !\n",PointerToMethod0Parameters,PointerToMethod1Parameters,PointerToMethod2Parameters);

	// !!!!! Kedze VARIABLE 'PointerToMethod0Parameters' je uz nastavena na METHOD VirtualMethod2(), je ju mozne okamzite aplikovat na INY OBJECT.
	(PointerToObject2->*PointerToMethod0Parameters)();

	// !!!!! Kedze VARIABLE 'PointerToMethod1Parameters' je uz nastavena na METHOD VirtualMethod2(), je ju mozne okamzite aplikovat na INY OBJECT.
	(PointerToObject2->*PointerToMethod1Parameters)(L"EEE");

	// !!!!! Kedze VARIABLE 'PointerToMethod2Parameters' je uz nastavena na METHOD VirtualMethod2(), je ju mozne okamzite aplikovat na INY OBJECT.
	(PointerToObject2->*PointerToMethod2Parameters)(L"EEE",50);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPointersToMethodsWithInheritance(void)
{
	PrintLineSeparator();

	CPointersToMethodsDerived									Object1(L"XXX");
	CPointersToMethodsBase*										PointerToObject1=&Object1;

	void														(CPointersToMethodsBase::*PointerToMethod0Parameters)(void) const=nullptr;
	void														(CPointersToMethodsBase::*PointerToMethod1Parameters)(const wstring&) const=nullptr;
	void														(CPointersToMethodsBase::*PointerToMethod2Parameters)(const wstring&,int) const=nullptr;

	wcout << L"METHODS - PointerToMethod0Parameters [" << PointerToMethod0Parameters << L"] PointerToMethod1Parameters [" << PointerToMethod1Parameters << L"] PointerToMethod2Parameters [" << PointerToMethod2Parameters << L"] !" << endl;
	wprintf(L"METHODS - PointerToMethod0Parameters [%p] PointerToMethod1Parameters [%p] PointerToMethod2Parameters [%p] !\n",PointerToMethod0Parameters,PointerToMethod1Parameters,PointerToMethod2Parameters);

	PrintLineSeparator();

	// !!! COMPILER hodi ERROR. METHOD CPointersToMethodsBase::PrivateMethod() je oznacena ako PRIVATE, a preto k nemu NIE JE mozne pristupovat cez POINTERS to METHODS.
	//PointerToMethod0Parameters=&CPointersToMethodsBase::PrivateMethod;

	// !!! Do POINTERS na METHODS sa priradia NON-VIRTUAL METHODS.
	PointerToMethod0Parameters=&CPointersToMethodsBase::NonVirtualMethod1;
	PointerToMethod1Parameters=&CPointersToMethodsBase::NonVirtualMethod1;
	PointerToMethod2Parameters=&CPointersToMethodsBase::NonVirtualMethod1;

	// !!!!! POINTERS na METHODS su interne implementovane ako klasicke POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"METHODS - PointerToMethod0Parameters [" << PointerToMethod0Parameters << L"] PointerToMethod1Parameters [" << PointerToMethod1Parameters << L"] PointerToMethod2Parameters [" << PointerToMethod2Parameters << L"] !" << endl;

	// !!!!! POINTERS na METHODS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"METHODS - PointerToMethod0Parameters [%p] PointerToMethod1Parameters [%p] PointerToMethod2Parameters [%p] !\n",PointerToMethod0Parameters,PointerToMethod1Parameters,PointerToMethod2Parameters);

	// !!! POINTERS na METHODS sa aplikuju na OBJECT.
	(Object1.*PointerToMethod0Parameters)();
	(Object1.*PointerToMethod1Parameters)(L"AAA");
	(Object1.*PointerToMethod2Parameters)(L"AAA",10);
	
	PrintLineSeparator();

	// !!! Do POINTERS na METHODS sa priradia ine NON-VIRTUAL METHODS.
	PointerToMethod0Parameters=&CPointersToMethodsBase::NonVirtualMethod2;
	PointerToMethod1Parameters=&CPointersToMethodsBase::NonVirtualMethod2;
	PointerToMethod2Parameters=&CPointersToMethodsBase::NonVirtualMethod2;

	// !!!!! POINTERS na METHODS su interne implementovane ako klasicke POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"METHODS - PointerToMethod0Parameters [" << PointerToMethod0Parameters << L"] PointerToMethod1Parameters [" << PointerToMethod1Parameters << L"] PointerToMethod2Parameters [" << PointerToMethod2Parameters << L"] !" << endl;

	// !!!!! POINTERS na METHODS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"METHODS - PointerToMethod0Parameters [%p] PointerToMethod1Parameters [%p] PointerToMethod2Parameters [%p] !\n",PointerToMethod0Parameters,PointerToMethod1Parameters,PointerToMethod2Parameters);

	// !!! POINTERS na METHODS sa aplikuju na POINTER na OBJECT.
	(PointerToObject1->*PointerToMethod0Parameters)();
	(PointerToObject1->*PointerToMethod1Parameters)(L"BBB");
	(PointerToObject1->*PointerToMethod2Parameters)(L"BBB",20);

	PrintLineSeparator();

	// !!! Do POINTERS na METHODS sa priradia VIRTUAL METHODS.
	PointerToMethod0Parameters=&CPointersToMethodsBase::VirtualMethod1;
	PointerToMethod1Parameters=&CPointersToMethodsBase::VirtualMethod1;
	PointerToMethod2Parameters=&CPointersToMethodsBase::VirtualMethod1;

	// !!!!! POINTERS na METHODS su interne implementovane ako INDEXES do CLASS a nie ako realne POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"METHODS - PointerToMethod0Parameters [" << PointerToMethod0Parameters << L"] PointerToMethod1Parameters [" << PointerToMethod1Parameters << L"] PointerToMethod2Parameters [" << PointerToMethod2Parameters << L"] !" << endl;

	// !!!!! POINTERS na METHODS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"METHODS - PointerToMethod0Parameters [%p] PointerToMethod1Parameters [%p] PointerToMethod2Parameters [%p] !\n",PointerToMethod0Parameters,PointerToMethod1Parameters,PointerToMethod2Parameters);

	// !!! POINTERS na METHODS sa aplikuju na OBJECT.
	// !!!!! Volaju sa METHODS z CLASS 'CPointersToMethodsDerived'. INHERITANCE sa vsak NEAPLIKUJE, pretoze sa PRIAMO PRISTUPUJE ku CLASS 'CPointersToMethodsDerived'.
	(Object1.*PointerToMethod0Parameters)();
	(Object1.*PointerToMethod1Parameters)(L"CCC");
	(Object1.*PointerToMethod2Parameters)(L"CCC",30);

	PrintLineSeparator();

	// !!! Do POINTERS na METHODS sa priradia ine VIRTUAL METHODS.
	PointerToMethod0Parameters=&CPointersToMethodsBase::VirtualMethod2;
	PointerToMethod1Parameters=&CPointersToMethodsBase::VirtualMethod2;
	PointerToMethod2Parameters=&CPointersToMethodsBase::VirtualMethod2;

	// !!!!! POINTERS na METHODS su interne implementovane ako INDEXES do CLASS a nie ako realne POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"METHODS - PointerToMethod0Parameters [" << PointerToMethod0Parameters << L"] PointerToMethod1Parameters [" << PointerToMethod1Parameters << L"] PointerToMethod2Parameters [" << PointerToMethod2Parameters << L"] !" << endl;

	// !!!!! POINTERS na METHODS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"METHODS - PointerToMethod0Parameters [%p] PointerToMethod1Parameters [%p] PointerToMethod2Parameters [%p] !\n",PointerToMethod0Parameters,PointerToMethod1Parameters,PointerToMethod2Parameters);

	// !!! POINTERS na METHODS sa aplikuju na POINTER na OBJECT.
	// !!!!! Volaju sa METHODS z CLASS 'CPointersToMethodsDerived'. INHERITANCE sa APLIKUJE, pretoze sa VARIABLE 'PointerToObject' aj ked je TYPE 'CPointersToMethodsBase' referuje na TYPE 'CPointersToMethodsDerived'.
	(PointerToObject1->*PointerToMethod0Parameters)();
	(PointerToObject1->*PointerToMethod1Parameters)(L"DDD");
	(PointerToObject1->*PointerToMethod2Parameters)(L"DDD",40);

	PrintLineSeparator();

	CPointersToMethodsDerived									Object2(L"YYY");
	CPointersToMethodsBase*										PointerToObject2=&Object2;

	// !!!!! POINTERS na METHODS su interne implementovane ako INDEXES do CLASS a nie ako realne POINTERS. CLASS 'wcout' vsak vypisuje iba BOOLEAN hodnotu ci je POINTER na MEMBER nastaveny, alebo nie.
	wcout << L"METHODS - PointerToMethod0Parameters [" << PointerToMethod0Parameters << L"] PointerToMethod1Parameters [" << PointerToMethod1Parameters << L"] PointerToMethod2Parameters [" << PointerToMethod2Parameters << L"] !" << endl;

	// !!!!! POINTERS na METHODS su korektne vypisovane pomocou FUNCTION wprintf().
	wprintf(L"METHODS - PointerToMethod0Parameters [%p] PointerToMethod1Parameters [%p] PointerToMethod2Parameters [%p] !\n",PointerToMethod0Parameters,PointerToMethod1Parameters,PointerToMethod2Parameters);

	// !!!!! Kedze VARIABLE 'PointerToMethod0Parameters' je uz nastavena na METHOD VirtualMethod2(), je ju mozne okamzite aplikovat na INY OBJECT.
	(PointerToObject2->*PointerToMethod0Parameters)();

	// !!!!! Kedze VARIABLE 'PointerToMethod1Parameters' je uz nastavena na METHOD VirtualMethod2(), je ju mozne okamzite aplikovat na INY OBJECT.
	(PointerToObject2->*PointerToMethod1Parameters)(L"EEE");

	// !!!!! Kedze VARIABLE 'PointerToMethod2Parameters' je uz nastavena na METHOD VirtualMethod2(), je ju mozne okamzite aplikovat na INY OBJECT.
	(PointerToObject2->*PointerToMethod2Parameters)(L"EEE",50);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPointersToMethodsContravariance(void)
{
	PrintLineSeparator();

	CPointersToMethodsDerived									Object(L"XXX");
	CPointersToMethodsBase*										PointerToBase=&Object;
	CPointersToMethodsDerived*									PointerToDerived=&Object;

	void														(CPointersToMethodsBase::*PointerToMethod0ParametersBase)(void) const=nullptr;
	void														(CPointersToMethodsBase::*PointerToMethod1ParametersBase)(const wstring&) const=nullptr;
	void														(CPointersToMethodsBase::*PointerToMethod2ParametersBase)(const wstring&,int) const=nullptr;
	void														(CPointersToMethodsDerived::*PointerToMethod0ParametersDerived)(void) const=nullptr;
	void														(CPointersToMethodsDerived::*PointerToMethod1ParametersDerived)(const wstring&) const=nullptr;
	void														(CPointersToMethodsDerived::*PointerToMethod2ParametersDerived)(const wstring&,int) const=nullptr;

	PointerToMethod0ParametersBase=&CPointersToMethodsBase::VirtualMethod1;
	PointerToMethod1ParametersBase=&CPointersToMethodsBase::VirtualMethod1;
	PointerToMethod2ParametersBase=&CPointersToMethodsBase::VirtualMethod1;

	PointerToMethod0ParametersDerived=&CPointersToMethodsDerived::VirtualMethod1;
	PointerToMethod1ParametersDerived=&CPointersToMethodsDerived::VirtualMethod1;
	PointerToMethod2ParametersDerived=&CPointersToMethodsDerived::VirtualMethod1;

	(PointerToBase->*PointerToMethod0ParametersBase)();
	(PointerToBase->*PointerToMethod1ParametersBase)(L"AAA");
	(PointerToBase->*PointerToMethod2ParametersBase)(L"AAA",10);

	PrintLineSeparator();

	(PointerToDerived->*PointerToMethod0ParametersDerived)();
	(PointerToDerived->*PointerToMethod1ParametersDerived)(L"BBB");
	(PointerToDerived->*PointerToMethod2ParametersDerived)(L"BBB",20);

	PrintLineSeparator();

	// !!!!! Do POINTERS na MEMBERS referujucich na BASE CLASSES NIE JE mozne priradit MEMBERS z DERIVED CLASSES. Je to dosledok toho, ze POINTER na MEMBER odkazujuci na DERIVED CLASS moze odkazovat na MEMBER, ktory v BASE CLASS NIE JE DEFINOVANY a ak by sa umoznilo toto priradenie, POINTER by odkazoval na NEEXISTUJUCI MEMBER.
	// !!!!! COMPILER pre nasledujuci CODE hodi ERROR.
	//PointerToMethod0ParametersBase=PointerToMethod0ParametersDerived;
	//PointerToMethod1ParametersBase=PointerToMethod1ParametersDerived;
	//PointerToMethod2ParametersBase=PointerToMethod2ParametersDerived;

	// !!!!! Do POINTERS na MEMBERS referujucich na DERIVED CLASSES je mozne priradzovat MEMBERS z BASE CLASSES, pretoze DERIVED CLASSES obsahuju VSETKY MEMBERS BASE CLASSES a tak NEHROZI ze by POINTER referoval na NEEXISTUJUCI MEMBER.
	PointerToMethod0ParametersDerived=PointerToMethod0ParametersBase;
	PointerToMethod1ParametersDerived=PointerToMethod1ParametersBase;
	PointerToMethod2ParametersDerived=PointerToMethod2ParametersBase;

	(PointerToDerived->*PointerToMethod0ParametersDerived)();
	(PointerToDerived->*PointerToMethod1ParametersDerived)(L"CCC");
	(PointerToDerived->*PointerToMethod2ParametersDerived)(L"CCC",30);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPointersToOperators(void)
{
	PrintLineSeparator();

	CPointersToMethodsBase										Object1(L"XXX");
	CPointersToMethodsBase*										PointerToObject1=&Object1;

	bool														(CPointersToMethodsBase::*Operator)(const CPointersToMethodsBase&) const=nullptr;

	wcout << L"OPERATORS - Operator [" << Operator << L"] !" << endl;
	wprintf(L"OPERATORS - Operator [%p] !\n",Operator);

	PrintLineSeparator();

	// !!! Do POINTER na OPERATOR sa priradi OPERATOR.
	Operator=&CPointersToMethodsBase::operator==;

	wcout << L"OPERATORS - Operator [" << Operator << L"] !" << endl;
	wprintf(L"OPERATORS - Operator [%p] !\n",Operator);

	// !!! POINTER na OPERATOR sa aplikuje na OBJECT.
	(Object1.*Operator)(Object1);

	PrintLineSeparator();

	// !!! Do POINTER na OPERATOR sa priradi iny OPERATOR.
	Operator=&CPointersToMethodsBase::operator!=;

	wcout << L"OPERATORS - Operator [" << Operator << L"] !" << endl;
	wprintf(L"OPERATORS - Operator [%p] !\n",Operator);

	// !!! POINTER na OPERATOR sa aplikuje na POINTER na OBJECT.
	(PointerToObject1->*Operator)(Object1);

	PrintLineSeparator();

	CPointersToMethodsBase										Object2(L"YYY");
	CPointersToMethodsBase*										PointerToObject2=&Object2;

	wcout << L"OPERATORS - Operator [" << Operator << L"] !" << endl;
	wprintf(L"OPERATORS - Operator [%p] !\n",Operator);

	// !!!!! Kedze VARIABLE 'Operator' je uz nastavena na OPERATOR!=, je ju mozne okamzite aplikovat na INY OBJECT.
	(PointerToObject2->*Operator)(Object2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestClassInheritance();
	//TestConstructorDestructor();
	//TestVirtualMethods();
	//TestExplicitQualification();
	//TestOverrideKeyword();
	//TestFinalMethodKeyword();
	//TestFinalClassKeyword();
	//TestMethodHiding();
	//TestMethodHidingUncover();
	//TestConstructorInheritance();
	//TestReturnValueCovariance();
	//TestPureVirtualMethods();
	//TestMemberAccessRights();
	//TestFriends();
	//TestInheritanceAccessRights1();
	//TestInheritanceAccessRights2();
	//TestInheritanceAccessRights3();
	//TestInheritanceAccessRights4();
	//TestInheritanceAccessRights5();
	//TestAccessRightOuterInnerClass();
	//TestUsingDeclarationAccessRights();
	//TestPointersToFields();
	//TestPointersToMethods();
	//TestPointersToMethodsWithInheritance();
	//TestPointersToMethodsContravariance();
	//TestPointersToOperators();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------