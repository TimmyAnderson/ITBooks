//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include "Text.h"
#include "DerivedClass.h"
#include "BasePolymorphism.h"
#include "DerivedPolymorphism.h"
#include "SimpleDerivedClass.h"
#include "NonVirtualClass.h"
#include "VirtualClass.h"
#include "NoVirtualDestructorBase.h"
#include "NoVirtualDestructorDerived.h"
#include "VirtualDestructorBase.h"
#include "VirtualDestructorDerived.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	CDerivedClass												DerivedClass(CText(L"BASE1"),CText(L"BASE2"),CText(L"DERIVED"));

	DerivedClass.PrintAbstractWithImplementation();
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	CDerivedClass												DerivedClass(CText(L"BASE1"),CText(L"BASE2"),CText(L"DERIVED"));

	DerivedClass.PrintNonVirtual();
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	CDerivedPolymorphism										DerivedPolymorphism(L"BASE1",L"BASE2",L"DERIVED");

	// !!!!! Vykona sa KOPIA FIELDS CDerivedPolymorphism::MBaseText1 a CDerivedPolymorphism::MBaseText2 do NOVEJ INSTANCIE CBasePolymorphism.
	// !!!!! Ak by CBasePolymorphism mala pretazeny OPERATOR=, tak by sa volal ten.
	CBasePolymorphism											BasePolymorphism=DerivedPolymorphism;

	// !!! Toto oznaci COMPILER za CHYBU, kedze do DERIVED CLASS NIE JE MOZNE priradit BASE CLASS.
	//CDerivedPolymorphism										Temp=BasePolymorphism;

	// !!! Toto je POLYMORFNE VOLANIE.
	DerivedPolymorphism.Print();

	// !!! Toto je NEPOLYMORFNE VOLANIE, kedze 'BasePolymorphism' obsahuje NOVY OBJEKT typu CBasePolymorphism.
	BasePolymorphism.Print();

	wprintf_s(L"\n");

	// Dokaz, ze sa FIELDS SKOPIROVALI.
	wprintf_s(L"BasePolymorphism.GetBaseText1(): [%s] !\n",BasePolymorphism.GetBaseText1().c_str());
	wprintf_s(L"BasePolymorphism.GetBaseText2(): [%s] !\n",BasePolymorphism.GetBaseText2().c_str());

	CBasePolymorphism*											BaseTestPointer=&BasePolymorphism;
	CBasePolymorphism*											DerivedTestPointer=&DerivedPolymorphism;

	// !!! Dokaz, ze 'BaseTestPointer' je SKUTOCNE TYPU CBasePolymorphism a NIE TYPU CDerivedPolymorphism.
	if (dynamic_cast<CDerivedPolymorphism*>(BaseTestPointer)!=NULL)
	{
		wprintf_s(L"BaseTestPointer IS CDerivedPolymorphism POINTER !\n");
	}
	else
	{
		wprintf_s(L"BaseTestPointer IS NOT CDerivedPolymorphism POINTER !\n");
	}

	// !!! Dokaz, ze 'DerivedTestPointer' je TYPU CDerivedPolymorphism.
	if (dynamic_cast<CDerivedPolymorphism*>(DerivedTestPointer)!=NULL)
	{
		wprintf_s(L"DerivedTestPointer IS CDerivedPolymorphism POINTER !\n");
	}
	else
	{
		wprintf_s(L"DerivedTestPointer IS NOT CDerivedPolymorphism POINTER !\n");
	}

	wprintf_s(L"\n");

	CBasePolymorphism&											Reference=DerivedPolymorphism;
	CBasePolymorphism*											Pointer=&DerivedPolymorphism;

	// !!! Tieto volania su POLYMORFNE.
	Reference.Print();
	Pointer->Print();
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	CSimpleDerivedClass											DerivedClass(L"BASE1",L"BASE2",L"DERIVED");

	// !!! Kedze OPERATOR:: RUSI POLYMORFIZMUS metody sa volaju NEPOLYMORFNE.
	DerivedClass.CSimpleBaseClass1::PrintAbstractWithImplementation();
	DerivedClass.CSimpleBaseClass2::PrintAbstractWithImplementation();

	// !!! Toto hodi CHYBU, ale iba preto, ze GLOBAL SCOPE NEMA tuto funkciu implementovanu.
	//DerivedClass.::PrintAbstractWithImplementation();

}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	int															SizeNonVirtualClass=sizeof(CNonVirtualClass);

	// !!! CLASS je vacsia o SIZEOF(POINTER), lebo obsahuje SKRYTY POINTER na VIRTUAL TABLE.
	int															SizeVirtualClass=sizeof(CVirtualClass);

	wprintf(L"SizeNonVirtualClass: [%d], SizeVirtualClass: [%d] !\n",SizeNonVirtualClass,SizeVirtualClass);
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	CNoVirtualDestructorDerived*								NoVirtualDestructorDerived=new CNoVirtualDestructorDerived;
	CVirtualDestructorDerived*									VirtualDestructorDerived=new CVirtualDestructorDerived;

	// !!! Kedze som NESPRAVIL PRETYPOVANIE na BASE CLASSSES, tak sa volaju DESTRUCTORS pre BASE i DERIVED CLASSES.
	delete(NoVirtualDestructorDerived);
	delete(VirtualDestructorDerived);
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	CNoVirtualDestructorDerived									NoVirtualDestructorDerived;
	CVirtualDestructorDerived									VirtualDestructorDerived;

	// !!! Kedze CNoVirtualDestructorDerived NEMAM FIELDS, tak obsahuje MINIMALNU DLZKU CLASS co je 1 BYTE.
	wprintf_s(L"NoVirtualDestructorDerived SIZE: [%d] !\n",sizeof(NoVirtualDestructorDerived));

	// !!! Je DLHSI ako CNoVirtualDestructorDerived o SIZEOF(POINTER), lebo obsahuje VIRTUALNU METODU - VIRTUAL DESTRUCTOR.
	wprintf_s(L"VirtualDestructorDerived SIZE: [%d] !\n",sizeof(VirtualDestructorDerived));

	// !!! Kedze sa jedna o OBJEKTY a NIE POINTERS, tak sa volaju DESTRUCTORS pre BASE i DERIVED CLASSES.
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	CNoVirtualDestructorDerived*								NoVirtualDestructorDerived=new CNoVirtualDestructorDerived;
	CVirtualDestructorDerived*									VirtualDestructorDerived=new CVirtualDestructorDerived;

	CNoVirtualDestructorBase*									NoVirtualDestructorBase=NoVirtualDestructorDerived;
	CVirtualDestructorBase*										VirtualDestructorBase=VirtualDestructorDerived;

	// !!! Kedze som SPRAVIL PRETYPOVANIE na BASE CLASSSES, tak sa pre CNoVirtualDestructorDerived NEZAVOLA DESTRUCTOR CLASS CVirtualDestructorDerived, kedze NEMA VIRTUAL DESTRUCTOR. Naopak DESTRUCTOR CVirtualDestructorDerived sa ZAVOLA, lebo jeho DESTRUCTOR je VIRTUAL.
	delete(NoVirtualDestructorBase);
	delete(VirtualDestructorBase);
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
	Test8();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------