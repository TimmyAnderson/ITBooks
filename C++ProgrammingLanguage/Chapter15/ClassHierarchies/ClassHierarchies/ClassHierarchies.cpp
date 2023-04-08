//-------------------------------------------------------------------------------------------------------
#pragma warning(disable : 4244)
//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <typeinfo>
#include "Base1.h"
#include "Base2.h"
#include "NonVirtualDerived.h"
#include "BaseVI1.h"
#include "BaseVI2.h"
#include "VirtualDerivedVI.h"
#include "AccessControlBase.h"
#include "AccessControlDerivedPrivate.h"
#include "AccessControlDerivedProtected.h"
#include "AccessControlMostDerivedPrivate.h"
#include "AccessControlMostDerivedProtected.h"
#include "AccessControlDerivedUsingTest.h"
#include "NonPolymorficBase.h"
#include "NonPolymorficDerived.h"
#include "NameBase.h"
#include "NameDerived.h"
#include "NewDelete.h"
#include "NewDeleteDerived.h"
#include "DummyBase.h"
#include "DummyDerived.h"
#include "CovarianceBase.h"
#include "CovarianceDerived.h"
//-------------------------------------------------------------------------------------------------------
CVirtualDerivedVI*												TempPointer=NULL;
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void PrintConversionResult(void* Pointer, wstring Text)
{
	if (Pointer!=NULL)
	{
		wprintf_s(L"CONVERSION [%s] SUCCEEDED !\n",Text.c_str());
	}
	else
	{
		wprintf_s(L"CONVERSION [%s] FAILED !\n",Text.c_str());
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	CNonVirtualDerived											NonVirtualDerived(L"CBase1",L"CBase2",L"CNonVirtualDerived");

	// !!! Kedze metoda je metoda OVERRIDED, tak C++ vie JEDNOZNACNE URCIT, ze sa ma volat DERIVED VERZIA metody v triede CNonVirtualDerived.
	NonVirtualDerived.Overrided();

	// !!! Mozem zavolat i implementacie metody Overrided() v BASE CLASSES.
	NonVirtualDerived.CBase1::Overrided();
	NonVirtualDerived.CBase2::Overrided();

	// !!! Toto kompilator NESKOMPILUJE, kedze nie je jasne ci ma volat verziu metody z CLASS CBase1, alebo CBase2.
	//NonVirtualDerived.NotOverrided();

	// !!! Pri volanie NotOverrided() je treba SPECIFIKOVAT, z ktorej BASE CLASS sa ma metoda volat.
	NonVirtualDerived.CBase1::NotOverrided();
	NonVirtualDerived.CBase2::NotOverrided();
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	CNonVirtualDerived											NonVirtualDerived(L"CBase1",L"CBase2",L"CNonVirtualDerived");

	// !!! Zavola verziu pre WCHAR_T.
	NonVirtualDerived.Ambiguity1(L'A');

	// !!! Zavola verziu pre WCHAR_T.
	NonVirtualDerived.Ambiguity2(L'A');

	wprintf_s(L"\n");

	// !!! Kedze sa NEPOUZIL 'using', tak Ambiguity1() z CBase1 a CBase2 NIE JE PRIAMO PRISTUPNY.
	NonVirtualDerived.Ambiguity1((int) 10);

	// !!! Kedze sa POUZIL 'using', tak Ambiguity2() z CBase1 a CBase2 JE PRIAMO PRISTUPNY.
	NonVirtualDerived.Ambiguity2((int) 10);

	wprintf_s(L"\n");

	// !!! Kedze sa NEPOUZIL 'using', tak Ambiguity1() z CBase1 a CBase2 NIE JE PRIAMO PRISTUPNY.
	NonVirtualDerived.Ambiguity1((double) 10.3);

	// !!! Kedze sa POUZIL 'using', tak Ambiguity2() z CBase1 a CBase2 JE PRIAMO PRISTUPNY.
	NonVirtualDerived.Ambiguity2((double) 10.3);
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	CNonVirtualDerived											NonVirtualDerived(L"CBase1",L"CBase2",L"CNonVirtualDerived");

	// !!! Nejednodznacne volanie metody.
	//NonVirtualDerived.PrintCBaseSharedName();

	// !!! Kazdy CBase objekt ma VLASTNU VERZIU, tak CBase1 aj CBase2 maju VLASTNE VERZIE MCBaseSharedName.
	NonVirtualDerived.CBase1::PrintCBaseSharedName();
	NonVirtualDerived.CBase2::PrintCBaseSharedName();
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	CNonVirtualDerived											NonVirtualDerived(L"CBase1",L"CBase2",L"CNonVirtualDerived");
	CBase1*														PointerBase1=(CBase1*) &NonVirtualDerived;
	CBase2*														PointerBase2=(CBase2*) &NonVirtualDerived;
	CBase*														PointerBaseThroughBase1=(CBase1*) &NonVirtualDerived;
	CBase*														PointerBaseThroughBase2=(CBase2*) &NonVirtualDerived;

	// !!! AMBIGUITY, kedze nie je jasne ci chcem volat verziu Virtual1() zdedenu cez CBase1, alebo zdedenu cez CBase2, ktora ju pretazuje.
	//NonVirtualDerived.Virtual1();

	// Vola sa CBase.Virtual1(), lebo v CBase1 ani CNonVirtualDerived NIE je PRETAZENA.
	PointerBase1->Virtual1();
	// Vola sa CBase2.Virtual1(), lebo CBase2 ju PRETAZUJE.
	PointerBase2->Virtual1();

	// Vola sa CBase.Virtual1(), lebo v CBase1 ani CNonVirtualDerived NIE je PRETAZENA.
	PointerBaseThroughBase1->Virtual1();
	// Vola sa CBase2.Virtual1(), lebo CBase2 ju PRETAZUJE.
	PointerBaseThroughBase2->Virtual1();

	wprintf_s(L"\n");

	// !!! AMBIGUITY, kedze nie je jasne ci chcem volat verziu Virtual1() zdedenu cez CBase1, ktora ju pretazuje, alebo zdedenu cez CBase2, ktora ju pretazuje.
	//NonVirtualDerived.Virtual2();

	// Vola sa CBase1.Virtual2(), lebo CBase1 ju PRETAZUJE.
	PointerBase1->Virtual2();
	// Vola sa CBase2.Virtual2(), lebo CBase2 ju PRETAZUJE.
	PointerBase2->Virtual2();

	// Vola sa CBase1.Virtual2(), lebo CBase1 ju PRETAZUJE.
	PointerBaseThroughBase1->Virtual2();
	// Vola sa CBase2.Virtual2(), lebo CBase2 ju PRETAZUJE.
	PointerBaseThroughBase2->Virtual2();

	wprintf_s(L"\n");

	// !!! NEDOCHADZA k AMBIGUITY, kedze CNonVirtualDerived PERETAZUJE Virtual3() a teda bude sa volat tato verzia.
	NonVirtualDerived.Virtual3();

	// Vola sa CNonVirtualDerived.Virtual3(), lebo CNonVirtualDerived ju PRETAZUJE.
	PointerBase1->Virtual3();
	// Vola sa CNonVirtualDerived.Virtual3(), lebo CNonVirtualDerived ju PRETAZUJE.
	PointerBase2->Virtual3();

	// Vola sa CNonVirtualDerived.Virtual3(), lebo CNonVirtualDerived ju PRETAZUJE.
	PointerBaseThroughBase1->Virtual3();
	// Vola sa CNonVirtualDerived.Virtual3(), lebo CNonVirtualDerived ju PRETAZUJE.
	PointerBaseThroughBase2->Virtual3();
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	CNonVirtualDerived											NonVirtualDerived(L"CBase1",L"CBase2",L"CNonVirtualDerived");
	CBase1*														PointerBase1=(CBase1*) &NonVirtualDerived;
	CBase2*														PointerBase2=(CBase2*) &NonVirtualDerived;

	// !!! Kedze som NEPOUZIL VIRTUALINHERITANCE, tak existuju 2 INSTANCIE CBase.
	PointerBase1->PrintCBaseSharedName();
	PointerBase2->PrintCBaseSharedName();
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	CVirtualDerivedVI											VirtualDerivedVI(L"CBase1",L"CBase2",L"CVirtualDerived");
	CBaseVI1*													PointerBaseVI1=(CBaseVI1*) &VirtualDerivedVI;
	CBaseVI2*													PointerBaseVI2=(CBaseVI2*) &VirtualDerivedVI;

	wprintf_s(L"\n");

	// !!! Kedze som POUZIL VIRTUALINHERITANCE, tak existuje iba 1 INSTANCE CBaseVI.
	PointerBaseVI1->PrintSharedName();
	PointerBaseVI2->PrintSharedName();
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	CVirtualDerivedVI											VirtualDerivedVI(L"CBase1",L"CBase2",L"CNonVirtualDerived");
	CBaseVI1*													PointerBaseVI1=(CBaseVI1*) &VirtualDerivedVI;
	CBaseVI2*													PointerBaseVI2=(CBaseVI2*) &VirtualDerivedVI;
	CBaseVI*													PointerBaseThroughBaseVI1=(CBaseVI1*) &VirtualDerivedVI;
	CBaseVI*													PointerBaseThroughBaseVI2=(CBaseVI2*) &VirtualDerivedVI;

	wprintf_s(L"\n");

	// !!! Nedochadza k AMBIGUITY, kedze sa zavola metoda z CVirtualDerivedVI.
	VirtualDerivedVI.Virtual1();

	// Vola sa CVirtualDerivedVI.Virtual1().
	PointerBaseVI1->Virtual1();
	// Vola sa CVirtualDerivedVI.Virtual1().
	PointerBaseVI2->Virtual1();

	// Vola sa CVirtualDerivedVI.Virtual1().
	PointerBaseThroughBaseVI1->Virtual1();
	// Vola sa CVirtualDerivedVI.Virtual1().
	PointerBaseThroughBaseVI2->Virtual1();

	wprintf_s(L"\n");

	// !!! Nedochadza k AMBIGUITY, kedze sa zavola metoda z CVirtualDerivedVI.
	VirtualDerivedVI.Virtual2();

	// Vola sa CVirtualDerivedVI.Virtual2().
	PointerBaseVI1->Virtual2();
	// Vola sa CVirtualDerivedVI.Virtual2().
	PointerBaseVI2->Virtual2();

	// Vola sa CVirtualDerivedVI.Virtual2().
	PointerBaseThroughBaseVI1->Virtual2();
	// Vola sa CVirtualDerivedVI.Virtual2().
	PointerBaseThroughBaseVI2->Virtual2();

	wprintf_s(L"\n");

	// !!! Nedochadza k AMBIGUITY, kedze sa zavola metoda z CVirtualDerivedVI.
	VirtualDerivedVI.Virtual3();

	// Vola sa CVirtualDerivedVI.Virtual3().
	PointerBaseVI1->Virtual3();
	// Vola sa CVirtualDerivedVI.Virtual3().
	PointerBaseVI2->Virtual3();

	// Vola sa CVirtualDerivedVI.Virtual3().
	PointerBaseThroughBaseVI1->Virtual3();
	// Vola sa CVirtualDerivedVI.Virtual3().
	PointerBaseThroughBaseVI2->Virtual3();
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	CAccessControlDerivedPrivate								Object;

	// Je to PRIVATE metoda.
	//Object.BasePrivate();

	// Je to PROTECTED metoda.
	//Object.BaseProtected();

	// Pouziva sa PRIVATE INHERITANCE a preto ju NIE JE MOZNE VOLAT.
	//Object.BasePublic();

	Object.TestDerivedPrivate();

	/*
	CAccessControlDerivedPrivate								TempObject;
	CAccessControlBase*											Pointer;

	// !!! Zlyha, lebo je pouzita PRIVATE INHERITANCE.
	//Pointer=&TempObject;

	Pointer->ExternalConversionSucceeded(L"CAccessControlDerivedPrivate ---> CAccessControlBase");
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	CAccessControlDerivedProtected								Object;

	// Je to PRIVATE metoda.
	//Object.BasePrivate();

	// Je to PROTECTED METODA.
	//Object.BaseProtected();

	// Pouziva sa PROTECTED INHERITANCE a preto ju NIE JE MOZNE VOLAT.
	//Object.BasePublic();

	Object.TestDerivedProtected();

	/*
	CAccessControlDerivedProtected								TempObject;
	CAccessControlBase*											Pointer;

	// !!! Zlyha, lebo je pouzita PROTECTED INHERITANCE.
	//Pointer=&TempObject;

	Pointer->ExternalConversionSucceeded(L"CAccessControlDerivedProtected ---> CAccessControlBase");
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	CAccessControlMostDerivedPrivate							Object;

	// Je to PRIVATE metoda.
	//Object.BasePrivate();

	// Je to PROTECTED METODA.
	//Object.BaseProtected();

	// Pouziva sa PRIVATE INHERITANCE a preto ju NIE JE MOZNE VOLAT.
	//Object.BasePublic();

	Object.TestDerivedPrivate();

	wprintf_s(L"\n");

	Object.TestMostDerivedPrivate();

	/*
	CAccessControlMostDerivedPrivate							TempObject;
	CAccessControlBase*											Pointer;

	// !!! Zlyha, lebo je pouzita PRIVATE INHERITANCE.
	Pointer=&TempObject;

	Pointer->ExternalConversionSucceeded(L"CAccessControlMostDerivedPrivate ---> CAccessControlBase");
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	CAccessControlMostDerivedProtected							Object;

	// Je to PRIVATE metoda.
	//Object.BasePrivate();

	// Je to PROTECTED METODA.
	//Object.BaseProtected();

	// Pouziva sa PROTECTED INHERITANCE a preto ju NIE JE MOZNE VOLAT.
	//Object.BasePublic();

	Object.TestDerivedProtected();

	wprintf_s(L"\n");

	Object.TestMostDerivedProtected();

	/*
	CAccessControlMostDerivedProtected							TempObject;
	CAccessControlBase*											Pointer;

	// !!! Zlyha, lebo je pouzita PROTECTED INHERITANCE.
	Pointer=&TempObject;

	Pointer->ExternalConversionSucceeded(L"CAccessControlMostDerivedProtected ---> CAccessControlBase");
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	CAccessControlDerivedUsingTest								Object;

	// Je to PRIVATE metoda.
	//Object.BasePrivate();

	// !!! Je to PROTECTED METODA, ktora NEPOUZIVA na zviditelnenie USING DECLARAION a kedze sa pouziva PRIVATE INHERITANCE, tak je NEPRISTUPNA.
	//Object.BaseProtected();

	// !!! Je to PUBLIC METODA, ktora NEPOUZIVA na zviditelnenie USING DECLARAION a kedze sa pouziva PRIVATE INHERITANCE, tak je NEPRISTUPNA.
	//Object.BasePublic();

	// !!! Je to PRIVATE metoda a ta je nepristupna i pre CAccessControlDerivedUsingTest a preto ju ta ANI cez USING DECLARAION NEMOZE SPRISTUPNIT.
	//Object.DummyPrivate();

	// !!! Je to PROTECTED METODA, ktora POUZIVA na zviditelnenie USING DECLARAION. Pouzitie USING DECLARAION je NUTNE, lebo sa pouziva PRIVATE INHERITANCE.
	Object.DummyProtected();

	// !!! Je to PUBLIC METODA, ktora POUZIVA na zviditelnenie USING DECLARAION. Pouzitie USING DECLARAION je NUTNE, lebo sa pouziva PRIVATE INHERITANCE.
	Object.DummyPublic();


	wprintf_s(L"\n");

	Object.Test();
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	// Trieda NEOBSAHUJE VIRTUAL INHERITANCE.
	CNonVirtualDerived											Object(L"CBase1",L"CBase2",L"CNonVirtualDerived");
	CNonVirtualDerived*											Pointer=&Object;
	CBase1*														Base1;
	CBase2*														Base2;

	CBase*														BaseFrom1;
	CBase*														BaseFrom2;

	PrintConversionResult(Base1=dynamic_cast<CBase1*>(Pointer),L"CNonVirtualDerived ---> CBase1");
	PrintConversionResult(Base2=dynamic_cast<CBase2*>(Pointer),L"CNonVirtualDerived ---> CBase2");

	// !!! Hodi KOMPILACNU CHYBU, pretoze konverzia je UNAMBIGUOUS.
	//PrintConversionResult(dynamic_cast<CBase*>(Pointer),L"CNonVirtualDerived ---> CBase");

	PrintConversionResult(dynamic_cast<CNonVirtualDerived*>(Base1),L"CBase1 ---> CNonVirtualDerived");
	PrintConversionResult(dynamic_cast<CNonVirtualDerived*>(Base2),L"CBase2 ---> CNonVirtualDerived");

	PrintConversionResult(BaseFrom1=dynamic_cast<CBase*>(Base1),L"CBase1 ---> CBase");
	PrintConversionResult(BaseFrom2=dynamic_cast<CBase*>(Base2),L"CBase2 ---> CBase");

	// !!! Konverzie medzi SIBLING CLASSES v dedicskej hierarchii.
	PrintConversionResult(dynamic_cast<CBase2*>(Base1),L"CBase1 ---> CBase2");
	PrintConversionResult(dynamic_cast<CBase1*>(Base2),L"CBase2 ---> CBase1");

	PrintConversionResult(dynamic_cast<CNonVirtualDerived*>(BaseFrom1),L"CBase ---> CNonVirtualDerived");
	PrintConversionResult(dynamic_cast<CNonVirtualDerived*>(BaseFrom2),L"CBase ---> CNonVirtualDerived");

	// !!! Umyselne CHYBNE KONVERZIE.
	PrintConversionResult(dynamic_cast<CVirtualDerivedVI*>(BaseFrom1),L"CBase ---> CVirtualDerivedVI");
	PrintConversionResult(dynamic_cast<CVirtualDerivedVI*>(BaseFrom2),L"CBase ---> CVirtualDerivedVI");

	try
	{
		// !!! Konverzie REFERENCE. Ak ZLYHA, tak HODI EXCEPTION.
		dynamic_cast<CBase1&>(Object);

		wprintf_s(L"CONVERSION [%s] SUCCEEDED !\n",L"CNonVirtualDerived& ---> CBase1&");
	}
	catch(bad_cast&)
	{
		wprintf_s(L"CONVERSION [%s] FAILED !\n",L"CNonVirtualDerived& ---> CBase1&");
	}
		
	try
	{
		// !!! Konverzie REFERENCE. Ak ZLYHA, tak HODI EXCEPTION.
		dynamic_cast<CBase2&>(Object);

		wprintf_s(L"CONVERSION [%s] SUCCEEDED !\n",L"CNonVirtualDerived& ---> CBase2&");
	}
	catch(bad_cast&)
	{
		wprintf_s(L"CONVERSION [%s] FAILED !\n",L"CNonVirtualDerived& ---> CBase2&");
	}

	try
	{
		// !!! Konverzie REFERENCE. Ak ZLYHA, tak HODI EXCEPTION.
		// !!! Umyselne CHYBNA KONVERZIA.
		dynamic_cast<CBaseVI1&>(Object);

		wprintf_s(L"CONVERSION [%s] SUCCEEDED !\n",L"CNonVirtualDerived& ---> CBaseVI1&");
	}
	catch(bad_cast&)
	{
		wprintf_s(L"CONVERSION [%s] FAILED !\n",L"CNonVirtualDerived& ---> CBaseVI1&");
	}
		
	try
	{
		// !!! Konverzie REFERENCE. Ak ZLYHA, tak HODI EXCEPTION.
		// !!! Umyselne CHYBNA KONVERZIA.
		dynamic_cast<CBaseVI2&>(Object);

		wprintf_s(L"CONVERSION [%s] SUCCEEDED !\n",L"CNonVirtualDerived& ---> CBaseVI2&");
	}
	catch(bad_cast&)
	{
		wprintf_s(L"CONVERSION [%s] FAILED !\n",L"CNonVirtualDerived& ---> CBaseVI2&");
	}

	CAccessControlMostDerivedPrivate							AccessObject;
	CAccessControlMostDerivedPrivate*							AccessObjectPointer=&AccessObject;

	// !!! Konverzia PREBEHNE, lebo INHERITANCE medzi CAccessControlMostDerivedPrivate a CAccessControlMostDerivedPrivate je typu PUBLIC.
	PrintConversionResult(dynamic_cast<CAccessControlDerivedPrivate*>(AccessObjectPointer),L"CAccessControlMostDerivedPrivate ---> CAccessControlDerivedPrivate");

	// !!! COMPILER HODI WARNING, lebo INHERITANCE medzi CAccessControlMostDerivedPrivate a CAccessControlMostDerivedPrivate je typu PRIVATE. Vysledkom konverzie je NULL.
	//PrintConversionResult(dynamic_cast<CAccessControlBase*>(AccessObjectPointer),L"CAccessControlMostDerivedPrivate ---> CAccessControlBase");

	// !!! Trieda pouziva VIRTUAL INHERITANCE.
	CVirtualDerivedVI											VirtualDerivedVI(L"CBase1",L"CBase2",L"CNonVirtualDerived");
	CVirtualDerivedVI*											VirtualDerivedVIPointer=&VirtualDerivedVI;
	CBaseVI*													VirtualBaseVIPointer;

	// !!! Kedze CBaseVI je dedeny VIRTUALNE z CBaseVI1 a CBaseVI2, tak KONVERZIA ZBEHNE.
	PrintConversionResult(VirtualBaseVIPointer=dynamic_cast<CBaseVI*>(VirtualDerivedVIPointer),L"CVirtualDerivedVI ---> CBaseVI");

	// !!! Kedze CBaseVI je dedeny VIRTUALNE z CBaseVI1 a CBaseVI2, tak KONVERZIA ZBEHNE.
	PrintConversionResult(dynamic_cast<CVirtualDerivedVI*>(VirtualBaseVIPointer),L"CBaseVI ---> CVirtualDerivedVI");

	// !!! KONVERZIA ZBEHNE, kedze sa NEPOUZIVA VIRTUALNA DEDICNOST a 'BaseFrom1' a 'BaseFrom2' ukazuju na SVOJE V KOPIE objektu CBase.
	PrintConversionResult(dynamic_cast<CNonVirtualDerived*>(BaseFrom1),L"CBase ---> CNonVirtualDerived");
	PrintConversionResult(dynamic_cast<CNonVirtualDerived*>(BaseFrom2),L"CBase ---> CNonVirtualDerived");

	CNonPolymorficDerived										NonPolymorficObject;
	CNonPolymorficDerived*										NonPolymorficDerivedPointer=&NonPolymorficObject;
	CNonPolymorficBase*											NonPolymorficBasePointer;

	// !!! Toto COMPLIER AKCEPTUJE, lebo pri konverzii z DERIVED na BASE NIE JE VYZADOVANE, aby typy boli POLYMORFNE.
	PrintConversionResult(NonPolymorficBasePointer=dynamic_cast<CNonPolymorficBase*>(NonPolymorficDerivedPointer),L"CNonPolymorficDerived ---> CNonPolymorficBase");

	// !!!!! COMPILER hodi CHYBU, pretoze DYNAMIC CAST pri konverzii z BASE na DERIVED VYZADUJE, aby TARGET CLASS (CNonPolymorficBase) bol POLYMORFNY.
	//PrintConversionResult(dynamic_cast<CNonPolymorficDerived*>(NonPolymorficBasePointer),L"CNonPolymorficBase -> CNonPolymorficDerived");
}
//-------------------------------------------------------------------------------------------------------
void Test14(void)
{
	CNonVirtualDerived											Object(L"CBase1",L"CBase2",L"CNonVirtualDerived");
	CNonVirtualDerived*											Pointer=&Object;
	CBase1*														Base1;
	CBase2*														Base2;

	CBase*														BaseFrom1;
	CBase*														BaseFrom2;

	PrintConversionResult(Base1=static_cast<CBase1*>(Pointer),L"CNonVirtualDerived ---> CBase1");
	PrintConversionResult(Base2=static_cast<CBase2*>(Pointer),L"CNonVirtualDerived ---> CBase2");

	// !!! Hodi KOMPILACNU CHYBU, pretoze konverzia je UNAMBIGUOUS.
	//PrintConversionResult(static_cast<CBase*>(Pointer),L"CNonVirtualDerived ---> CBase");

	PrintConversionResult(static_cast<CNonVirtualDerived*>(Base1),L"CBase1 ---> CNonVirtualDerived");
	PrintConversionResult(static_cast<CNonVirtualDerived*>(Base2),L"CBase2 ---> CNonVirtualDerived");

	PrintConversionResult(BaseFrom1=static_cast<CBase*>(Base1),L"CBase1 ---> CBase");
	PrintConversionResult(BaseFrom2=static_cast<CBase*>(Base2),L"CBase2 ---> CBase");

	// !!! Konverzie medzi SIBLING CLASSES v dedicskej hierarchii static_cast<>() NEUMOZNUJE.
	//PrintConversionResult(static_cast<CBase2*>(Base1),L"CBase1 ---> CBase2");
	//PrintConversionResult(static_cast<CBase1*>(Base2),L"CBase2 ---> CBase1");

	// !!! OPERATOR static_cast<>() NEDOKAZE na ROZDIEL od static_cast<>() vykonat KONVERZIU ak v dedicskej hierarchii sa vyskytuje jedna CLASS VIACKRAT.
	//PrintConversionResult(static_cast<CNonVirtualDerived*>(BaseFrom1),L"CBase ---> CNonVirtualDerived");
	//PrintConversionResult(static_cast<CNonVirtualDerived*>(BaseFrom2),L"CBase ---> CNonVirtualDerived");
}
//-------------------------------------------------------------------------------------------------------
void Test15(void)
{
	CNonVirtualDerived											Object(L"CBase1",L"CBase2",L"CNonVirtualDerived");
	CNonVirtualDerived*											Pointer=&Object;
	CNonVirtualDerived*											PointerTemp=&Object;
	CNonVirtualDerived&											Reference=Object;
	CBase1*														PointerBase1=&Object;
	CBase2*														PointerBase2=&Object;
	CBase*														PointerRootBase1=PointerBase1;
	CBase*														PointerRootBase2=PointerBase2;

	printf_s("Type: [%s] !\n",typeid(Object).name());
	printf_s("Type: [%s] !\n",typeid(Pointer).name());
	printf_s("Type: [%s] !\n",typeid(Reference).name());
	printf_s("Type: [%s] !\n",typeid(&Pointer).name());

	// !!! Nevracia SKUTOCNY TYP, ale TYP daneho POINTER - kedze zistujem typ POINTER a NIE TYP OBJEKTU.
	printf_s("Type: [%s] !\n",typeid(PointerBase1).name());
	// !!! Nevracia SKUTOCNY TYP, ale TYP daneho POINTER - kedze zistujem typ POINTER a NIE TYP OBJEKTU.
	printf_s("Type: [%s] !\n",typeid(PointerBase2).name());

	// !!! Vracia SKUTOCNY TYP - kedze zistujem TYP OBJEKTU.
	printf_s("Type: [%s] !\n",typeid(*PointerBase1).name());
	// !!! Vracia SKUTOCNY TYP - kedze zistujem TYP OBJEKTU.
	printf_s("Type: [%s] !\n",typeid(*PointerBase2).name());

	// !!! Nevracia SKUTOCNY TYP, ale TYP daneho POINTER - kedze zistujem typ POINTER a NIE TYP OBJEKTU.
	printf_s("Type: [%s] !\n",typeid(PointerRootBase1).name());
	// !!! Nevracia SKUTOCNY TYP, ale TYP daneho POINTER - kedze zistujem typ POINTER a NIE TYP OBJEKTU.
	printf_s("Type: [%s] !\n",typeid(PointerRootBase2).name());

	// !!! Vracia SKUTOCNY TYP - kedze zistujem TYP OBJEKTU.
	printf_s("Type: [%s] !\n",typeid(*PointerRootBase1).name());
	// !!! Vracia SKUTOCNY TYP - kedze zistujem TYP OBJEKTU.
	printf_s("Type: [%s] !\n",typeid(*PointerRootBase2).name());

	printf_s("Type: [%s] !\n",typeid(int).name());
	printf_s("Type: [%s] !\n",typeid(int*).name());
	printf_s("Type: [%s] !\n",typeid(int&).name());
	printf_s("Type: [%s] !\n",typeid(int[100]).name());
	printf_s("Type: [%s] !\n",typeid(int[]).name());

	try
	{
		// !!! NEHODI EXCEPTION, lebo PRIMITIVNE TYPY (NULL je INT) je ENUMEROVANY v COMPILE-TIME.
		printf_s("Type: [%s] !\n",typeid(NULL).name());
	}
	catch(bad_typeid&)
	{
		wprintf_s(L"EXCEPTION !\n");
	}

	try
	{
		CVirtualDerivedVI*										TempPointer=NULL;

		// !!! Nehodi EXCEPTION.
		printf_s("Type: [%s] !\n",typeid(TempPointer).name());
	}
	catch(bad_typeid&)
	{
		wprintf_s(L"EXCEPTION !\n");
	}

	try
	{
		CBaseVI*												BasePointer=TempPointer;

		// !!! Nehodi EXCEPTION.
		printf_s("Type: [%s] !\n",typeid(BasePointer).name());
	}
	catch(bad_typeid&)
	{
		wprintf_s(L"EXCEPTION !\n");
	}

	const std::type_info&										Type1=typeid(Pointer);
	const std::type_info&										Type2=typeid(PointerTemp);
	const std::type_info&										Type3=typeid(int);

	if (Type1==Type2)
	{
		wprintf_s(L"Type1==Type2 !\n");
	}
	else
	{
		wprintf_s(L"Type1!=Type2 !\n");
	}

	if (Type1!=Type3)
	{
		wprintf_s(L"Type1!=Type3 !\n");
	}
	else
	{
		wprintf_s(L"Type1==Type3 !\n");
	}

	printf_s("Type.hash_code(): [%d] !\n",typeid(int).hash_code());
	printf_s("Type.hash_code(): [%d] !\n",typeid(1000).hash_code());
}
//-------------------------------------------------------------------------------------------------------
void Test16(void)
{
	CNameBase													Name1(L"Timmy",L"Anderson",12);
	CNameBase													Name2(L"Jenny",L"Thompson",13);
	CNameBase*													PName1=new CNameBase(L"Timmy",L"Anderson",12);
	CNameBase*													PName2=new CNameBase(L"Jenny",L"Thompson",13);

	// Definujem MEMBER REFERENCE premenne.
	wstring														CNameBase::*FirstName;
	wstring														CNameBase::*LastName;
	int															CNameBase::*Age;
	// Funkcia.
	wstring														(CNameBase::*Print)();

	// Inicializujem MEMBER REFERENCE premenne na jednotlive MEMBERS.
	FirstName=&CNameBase::MFirstName;
	LastName=&CNameBase::MLastName;
	Age=&CNameBase::MAge;
	Print=&CNameBase::GetFullName;

	// Volam MEMBER REFERENCE premenne pre rozlicne ROZLICNE objekty.
	wprintf_s(L"Name1.*FirstName: [%s] !\n",(Name1.*FirstName).c_str());
	wprintf_s(L"Name1.*LastName: [%s] !\n",(Name1.*LastName).c_str());
	wprintf_s(L"Name1.*Age: [%d] !\n",(Name1.*Age));
	// Vola sa FUNKCIA.
	wprintf_s(L"(Name1.*Print)(): [%s] !\n",((Name1.*Print)().c_str()));

	wprintf_s(L"\n");

	// Volam MEMBER REFERENCE premenne pre rozlicne ROZLICNE objekty.
	wprintf_s(L"Name2.*FirstName: [%s] !\n",(Name2.*FirstName).c_str());
	wprintf_s(L"Name2.*LastName: [%s] !\n",(Name2.*LastName).c_str());
	wprintf_s(L"Name2.*Age: [%d] !\n",(Name2.*Age));
	// Vola sa FUNKCIA.
	wprintf_s(L"(Name2.*Print)(): [%s] !\n",((Name2.*Print)().c_str()));
	
	wprintf_s(L"\n");

	// Volam MEMBER REFERENCE premenne CEZ POINTER pre rozlicne ROZLICNE objekty.
	wprintf_s(L"PName1->*FirstName: [%s] !\n",(PName1->*FirstName).c_str());
	wprintf_s(L"PName1->*LastName: [%s] !\n",(PName1->*LastName).c_str());
	wprintf_s(L"PName1->*Age: [%d] !\n",(PName1->*Age));
	// Vola sa FUNKCIA.
	wprintf_s(L"(PName1->*Print)(): [%s] !\n",((PName1->*Print)().c_str()));

	wprintf_s(L"\n");

	// Volam MEMBER REFERENCE premenne CEZ POINTER pre rozlicne ROZLICNE objekty.
	wprintf_s(L"PName2->*FirstName: [%s] !\n",(PName2->*FirstName).c_str());
	wprintf_s(L"PName2->*LastName: [%s] !\n",(PName2->*LastName).c_str());
	wprintf_s(L"PName2->*Age: [%d] !\n",(PName2->*Age));
	// Vola sa FUNKCIA.
	wprintf_s(L"(PName2->*Print)(): [%s] !\n",((PName2->*Print)().c_str()));

	delete(PName1);
	delete(PName2);

	wprintf_s(L"\n");

	CNameBase													BaseName(L"Timmy",L"Anderson",12);
	CNameDerived												DerivedName(L"Timmy",L"Anderson",12);

	// Funkcia.
	wstring														(CNameBase::*BasePrint)();
	// Funkcia.
	wstring														(CNameDerived::*DerivedPrint)();

	// !!! Toto priradenie je OK, lebo do CNameBase sa priradzuje MEMBER na CNameBase.
	BasePrint=&CNameBase::GetFullName;

	// !!! Toto priradenie je OK, lebo do CNameDerived sa priradzuje MEMBER na CNameDerived.
	DerivedPrint=&CNameDerived::DerivedClassGetFullName;

	wprintf_s(L"(BaseName.*BasePrint)(): [%s] !\n",((BaseName.*BasePrint)().c_str()));
	wprintf_s(L"(DerivedName.*DerivedPrint)(): [%s] !\n",((DerivedName.*DerivedPrint)().c_str()));

	// !!! Toto priradenie ALYHA, lebo do CNameBase sa priradzuje MEMBER na CNameDerived co NIE JE MOZNE.
	//BasePrint=&CNameDerived::DerivedClassGetFullName;

	// !!! Toto priradenie je OK, lebo do CNameDerived je mozne priradit MEMBER na CNameBase.
	DerivedPrint=&CNameBase::GetFullName;

	//wprintf_s(L"(BaseName.*BasePrint)(): [%s] !\n",((BaseName.*BasePrint)().c_str()));
	wprintf_s(L"(DerivedName.*DerivedPrint)(): [%s] !\n",((DerivedName.*DerivedPrint)().c_str()));

	wprintf_s(L"\n");

	CNameDerived*												Pointer=&DerivedName;

	wstring														(CNameDerived::*PolymorismTest)();

	PolymorismTest=&CNameDerived::VirtualMethod;

	// !!! Demonstracia, ze POINTER na MEMBER RESPEKTUJE POLYMORFIZMUS. Nasledujca metoda sa zavola POLYMORFNE.
	wprintf_s(L"(Pointer->*PolymorismTest)(): [%s] !\n",((Pointer->*PolymorismTest)().c_str()));

	/*
	wstring														(CNameBase::*StaticTest)();

	// !!! STATIC METHODS do POINTER to MEMBER NIE JE MOZNE PRIRADZOVAT.
	StaticTest=&CNameBase::StaticMethod;

	wprintf_s(L"(BaseName.*StaticTest)(): [%s] !\n",((BaseName.*StaticTest)().c_str()));
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test17(void)
{
	CCovarianceDerived											Object;
	CCovarianceBase*											Pointer1=&Object;
	CCovarianceDerived*											Pointer2=&Object;
	
	// !!! Ukazka COVARIANCE. Aj ked sa jedna o TU ISTU OVERRIDE METHOD, tak pre BASE a DERIVED CLASS vracaju ROZLICNE TYPY.
	CDummyBase*													DummyBase=Pointer1->GetDummy();
	CCovarianceBase*											CovarianceBase=Pointer1->GetCovariance();

	CDummyDerived*												DummyDerived=Pointer2->GetDummy();
	CCovarianceDerived*											CovarianceDerived=Pointer2->GetCovariance();

	DummyBase->PrintText();
	CovarianceBase->PrintText();

	DummyDerived->PrintText();
	CovarianceDerived->PrintText();
}
//-------------------------------------------------------------------------------------------------------
void Test18(void)
{
	wstring														Param1(L"XXX");
	wstring														Param2(L"YYY");

	// !!! Vola sa PRETAZENY OPERATOR.
	CNewDelete*													NewDelete1=new CNewDelete();
	CNewDelete*													NewDelete2=new (Param1) CNewDelete();
	CNewDelete*													NewDelete3=new (Param1,Param2) CNewDelete();

	delete(NewDelete1);
	// !!!!! OPERATOR DELETE NEMA specialnu syntax pomocou, ktorej by sa dalo zavolat DELETE s VIACERYMI PARAMETRAMI.
	NewDelete2->operator delete(NewDelete2,Param1);
	NewDelete3->operator delete(NewDelete3,Param1,Param2);
}
//-------------------------------------------------------------------------------------------------------
void Test19(void)
{
	wstring														Param1(L"XXX");
	wstring														Param2(L"YYY");

	// !!! Vola sa PRETAZENY OPERATOR[].
	CNewDeleteDerived*											NewDelete1=new CNewDeleteDerived();
	CNewDeleteDerived*											NewDelete2=new (Param1) CNewDeleteDerived();
	CNewDeleteDerived*											NewDelete3=new (Param1,Param2) CNewDeleteDerived();

	delete(NewDelete1);
	// !!!!! OPERATOR DELETE NEMA specialnu syntax pomocou, ktorej by sa dalo zavolat DELETE s VIACERYMI PARAMETRAMI.
	NewDelete2->operator delete(NewDelete2,Param1);
	NewDelete3->operator delete(NewDelete3,Param1,Param2);
}
//-------------------------------------------------------------------------------------------------------
void Test20(void)
{
	wstring														Param1(L"XXX");
	wstring														Param2(L"YYY");

	// !!! Vola sa PRETAZENY OPERATOR[].
	CNewDelete*													Array1=new CNewDelete[6];

	wprintf_s(L"Array1 [%p] !\n",Array1);

	// !!! Vola sa PRETAZENY DELETE[].
	delete[](Array1);

	// !!! Vola sa PRETAZENY OPERATOR[].
	CNewDelete*													Array2=new (sizeof(size_t),Param1,Param2) CNewDelete[6];

	wprintf_s(L"Array2 [%p] !\n",Array2);

	// !!!!! OPERATOR DELETE[] NEMA specialnu syntax pomocou, ktorej by sa dalo zavolat DELETE[] s VIACERYMI PARAMETRAMI.
	// !!!!! Z POINTER na Array2 je treba ODRATAT sizeof(size_t), pretoze Array2 v skutocnosti obsahuje hodnotu AllocatedBuffer+sizeof(size_t). V sizeof(size_t) je ulozenych POCET alokovanych ITEMS.
	Array2->operator delete[]((__int8*)Array2-sizeof(size_t),sizeof(size_t),Param1,Param2);
}
//-------------------------------------------------------------------------------------------------------
void Test21(void)
{
	wstring														Param1(L"XXX");
	wstring														Param2(L"YYY");

	// !!! Vola sa PRETAZENY OPERATOR[].
	CNewDeleteDerived*											Array1=new CNewDeleteDerived[6];

	// !!! Vola sa PRETAZENY DELETE[].
	delete[](Array1);

	// !!! Vola sa PRETAZENY OPERATOR[].
	CNewDeleteDerived*											Array2=new (sizeof(size_t),Param1,Param2) CNewDeleteDerived[6];

	wprintf_s(L"Array2 [%p] !\n",Array2);

	// !!!!! OPERATOR DELETE[] NEMA specialnu syntax pomocou, ktorej by sa dalo zavolat DELETE[] s VIACERYMI PARAMETRAMI.
	// !!!!! Z POINTER na Array2 je treba ODRATAT sizeof(size_t), pretoze Array2 v skutocnosti obsahuje hodnotu AllocatedBuffer+sizeof(size_t). V sizeof(size_t) je ulozenych POCET alokovanych ITEMS.
	Array2->operator delete[]((__int8*)Array2-sizeof(size_t),sizeof(size_t),Param1,Param2);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	//Test8();
	//Test9();
	//Test10();
	//Test11();
	//Test12();
	//Test13();
	//Test14();
	//Test15();
	//Test16();
	//Test17();
	//Test18();
	//Test19();
	//Test20();
	Test21();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------