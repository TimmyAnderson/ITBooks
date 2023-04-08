//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <string.h>
#include <iostream>
#include "MyDebug.h"
#include "CMultipleInterfacesInheritance.h"
#include "CMultipleImplementationsInheritance.h"
#include "CDerivedResolution.h"
#include "CSuperDerivedResolution.h"
#include "CNonVirtualInheritanceDerived.h"
#include "CVirtualInheritanceDerived.h"
#include "CNonVirtualDerived.h"
#include "CVirtualDerived.h"
#include "CClassSizeDerived.h"
#include "CMultipleVirtualInheritanceDerived.h"
#include "CVirtualInheritanceConstructorDerived.h"
#include "CMixinDerived.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PrintValue1(const CBaseInterface1& Interface1)
{
	wcout << L"VALUE 1 [" << Interface1.GetValue1() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void PrintValue2(const CBaseInterface2& Interface2)
{
	wcout << L"VALUE 2 [" << Interface2.GetValue2() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestMultipleInterfacesInheritance(void)
{
	PrintLineSeparator();

	CMultipleInterfacesInheritance								Object(L"AAA",L"BBB");

	PrintValue1(Object);
	PrintValue2(Object);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PrintValue1(const CBaseClass1& Class1)
{
	wcout << L"VALUE 1 [" << Class1.GetValue1() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void PrintValue2(const CBaseClass2& Class2)
{
	wcout << L"VALUE 2 [" << Class2.GetValue2() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestMultipleImplementationsInheritance(void)
{
	PrintLineSeparator();

	CMultipleImplementationsInheritance							Object(L"AAA",L"BBB");

	PrintValue1(Object);
	PrintValue2(Object);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBaseMethodResolution(void)
{
	PrintLineSeparator();

	CDerivedResolution											Derived;

	Derived.DoResolution();

	PrintLineSeparator();

	// Vola sa METHOD z BASE CLASS 'CBaseResolution1'.
	Derived.CBaseResolution1::DoSomething();

	PrintLineSeparator();

	// Vola sa METHOD z BASE CLASS 'CBaseResolution2'.
	Derived.CBaseResolution2::DoSomething();

	PrintLineSeparator();

	Derived.DoSomethingNonOverriden1();

	PrintLineSeparator();
	
	Derived.DoSomethingNonOverriden2();

	PrintLineSeparator();

	CSuperDerivedResolution										SuperDerived;

	SuperDerived.DoGrandchildResolution();

	PrintLineSeparator();

	// Vola sa METHOD z BASE CLASS 'CBaseResolution1'.
	// !!! Ako BASE CLASSS sa pouziva CLASS 'CDerivedResolution'. Ta vsak METHOD DoSomethingNonOverriden1() NEDEFINUJE a tak C++ hlada tuto METHOD v BASE CLASSES.
	SuperDerived.CDerivedResolution::DoSomethingNonOverriden1();

	// Vola sa METHOD z BASE CLASS 'CBaseResolution2'.
	// !!! Ako BASE CLASSS sa pouziva CLASS 'CDerivedResolution'. Ta vsak METHOD DoSomethingNonOverriden2() NEDEFINUJE a tak C++ hlada tuto METHOD v BASE CLASSES.
	SuperDerived.CDerivedResolution::DoSomethingNonOverriden2();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNonVirtualInheritance(void)
{
	PrintLineSeparator();

	{
		CNonVirtualInheritanceDerived							Derived(L"AAA",L"BBB");

		PrintLineSeparator();

		// !!!!! Kedze sa NEPOUZILA VIRTUAL INHERITANCE, tak SHARED BASE CLASS NIE JE mozne volat bez specifikovania konkretnej instancie CLASS 'CNonVirtualInheritanceSuperBase' v ktorej je METHOD PrintValue() definovana.
		//Derived.PrintValue();

		// !!!!! Vola sa verzia METHOD PrintValue(), ktora definovana v CLASS 'CNonVirtualInheritanceSuperBase' a je DERIVED cez CLASS 'CNonVirtualInheritanceBase1'.
		Derived.CNonVirtualInheritanceBase1::PrintValue();

		// !!!!! Vola sa verzia METHOD PrintValue(), ktora definovana v CLASS 'CNonVirtualInheritanceSuperBase' a je DERIVED cez CLASS 'CNonVirtualInheritanceBase2'.
		Derived.CNonVirtualInheritanceBase2::PrintValue();

		PrintLineSeparator();
	}

	PrintLineSeparator();

	wcout << L"CLASS wstring has SIZE [" << sizeof(wstring) << L"] !" << endl;
	wcout << L"CLASS CNonVirtualInheritanceSuperBase has SIZE [" << sizeof(CNonVirtualInheritanceSuperBase) << L"] !" << endl;
	wcout << L"CLASS CNonVirtualInheritanceBase1 has SIZE [" << sizeof(CNonVirtualInheritanceBase1) << L"] !" << endl;
	wcout << L"CLASS CNonVirtualInheritanceBase2 has SIZE [" << sizeof(CNonVirtualInheritanceBase2) << L"] !" << endl;
	wcout << L"CLASS CNonVirtualInheritanceDerived has SIZE [" << sizeof(CNonVirtualInheritanceDerived) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVirtualInheritance(void)
{
	PrintLineSeparator();

	{
		CVirtualInheritanceDerived								Derived(L"AAA",L"BBB",L"CCC");

		PrintLineSeparator();

		// !!!!! Kedze sa POUZILA VIRTUAL INHERITANCE, tak SHARED BASE CLASS JE mozne volat.
		Derived.PrintValue();

		// !!!!! Vola sa verzia METHOD PrintValue(), ktora definovana v CLASS 'CVirtualInheritanceSuperBase' a je SHARED medzi CLASS 'CVirtualInheritanceBase1' a CLASS 'CVirtualInheritanceBase2'.
		Derived.CVirtualInheritanceBase1::PrintValue();

		// !!!!! Vola sa verzia METHOD PrintValue(), ktora definovana v CLASS 'CVirtualInheritanceSuperBase' a je SHARED medzi CLASS 'CVirtualInheritanceBase1' a CLASS 'CVirtualInheritanceBase2'.
		Derived.CVirtualInheritanceBase2::PrintValue();

		// !!!!! Vola sa verzia METHOD PrintValue(), ktora definovana v CLASS 'CVirtualInheritanceSuperBase' a je SHARED medzi CLASS 'CVirtualInheritanceBase1' a CLASS 'CVirtualInheritanceBase2'.
		Derived.CVirtualInheritanceDerived::CVirtualInheritanceBase1::PrintValue();

		// !!!!! Vola sa verzia METHOD PrintValue(), ktora definovana v CLASS 'CVirtualInheritanceSuperBase' a je SHARED medzi CLASS 'CVirtualInheritanceBase1' a CLASS 'CVirtualInheritanceBase2'.
		Derived.CVirtualInheritanceDerived::CVirtualInheritanceBase2::PrintValue();

		PrintLineSeparator();
	}

	PrintLineSeparator();

	wcout << L"CLASS wstring has SIZE [" << sizeof(wstring) << L"] !" << endl;
	wcout << L"CLASS CVirtualInheritanceSuperBase has SIZE [" << sizeof(CVirtualInheritanceSuperBase) << L"] !" << endl;
	wcout << L"CLASS CVirtualInheritanceBase1 has SIZE [" << sizeof(CVirtualInheritanceBase1) << L"] !" << endl;
	wcout << L"CLASS CVirtualInheritanceBase2 has SIZE [" << sizeof(CVirtualInheritanceBase2) << L"] !" << endl;
	wcout << L"CLASS CVirtualInheritanceDerived has SIZE [" << sizeof(CVirtualInheritanceDerived) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestClassSizes(void)
{
	PrintLineSeparator();

	wcout << L"CLASS wstring has SIZE [" << sizeof(wstring) << L"] !" << endl;

	PrintLineSeparator();

	// SIZE=SIZEOF(wstring)=40.
	wcout << L"CLASS CNonVirtualBase has SIZE [" << sizeof(CNonVirtualBase) << L"] !" << endl;
	// SIZE=SIZEOF(wstring)=40.
	wcout << L"CLASS CNonVirtualDerived has SIZE [" << sizeof(CNonVirtualDerived) << L"] !" << endl;

	PrintLineSeparator();

	// SIZE=SIZEOF(wstring)+SIZEOF(POINTER_VT)=40+8=48.
	wcout << L"CLASS CVirtualBase has SIZE [" << sizeof(CVirtualBase) << L"] !" << endl;
	// SIZE=SIZEOF(wstring)+SIZEOF(POINTER_VT)=40+8=48.
	wcout << L"CLASS CVirtualDerived has SIZE [" << sizeof(CVirtualDerived) << L"] !" << endl;

	PrintLineSeparator();

	// SIZE=SIZEOF(wstring)+SIZEOF(POINTER_VT)=40+8=48.
	wcout << L"CLASS CNonVirtualInheritanceSuperBase has SIZE [" << sizeof(CNonVirtualInheritanceSuperBase) << L"] !" << endl;
	// SIZE=SIZEOF(wstring)+SIZEOF(POINTER_VT)=40+8=48.
	wcout << L"CLASS CNonVirtualInheritanceBase1 has SIZE [" << sizeof(CNonVirtualInheritanceBase1) << L"] !" << endl;
	// SIZE=SIZEOF(wstring)+SIZEOF(POINTER_VT)=40+8=48.
	wcout << L"CLASS CNonVirtualInheritanceBase2 has SIZE [" << sizeof(CNonVirtualInheritanceBase2) << L"] !" << endl;
	// SIZE=SIZEOF(CNonVirtualInheritanceBase1)+SIZEOF(CNonVirtualInheritanceBase2)=48+48=96.
	wcout << L"CLASS CNonVirtualInheritanceDerived has SIZE [" << sizeof(CNonVirtualInheritanceDerived) << L"] !" << endl;

	PrintLineSeparator();

	// SIZE=SIZEOF(wstring)+SIZEOF(POINTER_VT)=40+8=48.
	wcout << L"CLASS CVirtualInheritanceSuperBase has SIZE [" << sizeof(CVirtualInheritanceSuperBase) << L"] !" << endl;
	// SIZE=SIZEOF(wstring)+SIZEOF(POINTER_VT)+SIZEOF(POINTER_CVirtualInheritanceSuperBase)=40+8+8=56.
	wcout << L"CLASS CVirtualInheritanceBase1 has SIZE [" << sizeof(CVirtualInheritanceBase1) << L"] !" << endl;
	// SIZE=SIZEOF(wstring)+SIZEOF(POINTER_VT)+SIZEOF(POINTER_CVirtualInheritanceSuperBase)=40+8+8=56.
	wcout << L"CLASS CVirtualInheritanceBase2 has SIZE [" << sizeof(CVirtualInheritanceBase2) << L"] !" << endl;
	// SIZE=SIZEOF(CVirtualInheritanceSuperBase)+SIZEOF(POINTER_VT)+(SIZEOF(CVirtualInheritanceBase1)-SIZEOF(POINTER_CVirtualInheritanceSuperBase))+(SIZEOF(CVirtualInheritanceBase2)-SIZEOF(POINTER_CVirtualInheritanceSuperBase))=40+8+(56-48)+(56-48)=64.
	wcout << L"CLASS CVirtualInheritanceDerived has SIZE [" << sizeof(CVirtualInheritanceDerived) << L"] !" << endl;

	PrintLineSeparator();

	// SIZE=SIZEOF(MValueSuperBase)+SIZEOF(POINTER_VT)=8+8=16.
	wcout << L"CLASS CClassSizeSuperBase has SIZE [" << sizeof(CClassSizeSuperBase) << L"] !" << endl;
	// SIZE=SIZEOF(MValueSuperBase)+SIZEOF(MValueBase1)+SIZEOF(POINTER_CClassSizeSuperBase)+SIZEOF(POINTER_VT)=8+16+8+8=40.
	wcout << L"CLASS CClassSizeBase1 has SIZE [" << sizeof(CClassSizeBase1) << L"] !" << endl;
	// SIZE=SIZEOF(MValueSuperBase)+SIZEOF(MValueBase2)+SIZEOF(POINTER_CClassSizeSuperBase)+SIZEOF(POINTER_VT)=8+24+8+8=48.
	wcout << L"CLASS CClassSizeBase2 has SIZE [" << sizeof(CClassSizeBase2) << L"] !" << endl;
	// SIZE=SIZEOF(MValueSuperBase)+SIZEOF(MValueBase1)+SIZEOF(POINTER_CClassSizeSuperBase_CClassSizeBase1)+SIZEOF(MValueBase2)+SIZEOF(POINTER_CClassSizeSuperBase_CClassSizeBase2)+SIZEOF(MValueDerived)+SIZEOF(POINTER_VT)=8+16+8+24+8+32+8=104.
	wcout << L"CLASS CClassSizeDerived has SIZE [" << sizeof(CClassSizeDerived) << L"] !" << endl;

	PrintLineSeparator();

	// SIZE=SIZEOF(MValueSuperBase1)+SIZEOF(POINTER_VT)=8+8=16.
	wcout << L"CLASS CMultipleVirtualInheritanceSuperBase1 has SIZE [" << sizeof(CMultipleVirtualInheritanceSuperBase1) << L"] !" << endl;
	// SIZE=SIZEOF(MValueSuperBase2)+SIZEOF(POINTER_VT)=16+8=24.
	wcout << L"CLASS CMultipleVirtualInheritanceSuperBase2 has SIZE [" << sizeof(CMultipleVirtualInheritanceSuperBase2) << L"] !" << endl;
	// SIZE=SIZEOF(MValueSuperBase3)+SIZEOF(POINTER_VT)=24+8=32.
	wcout << L"CLASS CMultipleVirtualInheritanceSuperBase3 has SIZE [" << sizeof(CMultipleVirtualInheritanceSuperBase3) << L"] !" << endl;
	// SIZE=SIZEOF(MValueSuperBase1)+SIZEOF(POINTER_CMultipleVirtualInheritanceSuperBase1)+SIZEOF(MValueSuperBase2)+SIZEOF(POINTER_CMultipleVirtualInheritanceSuperBase2)+SIZEOF(MValueSuperBase3)+SIZEOF(POINTER_CMultipleVirtualInheritanceSuperBase3)+SIZEOF(MValueBase1)+SIZEOF(POINTER_VT)=8+8+16+8+24+8+32+8=112.
	wcout << L"CLASS CMultipleVirtualInheritanceBase1 has SIZE [" << sizeof(CMultipleVirtualInheritanceBase1) << L"] !" << endl;
	// SIZE=SIZEOF(MValueSuperBase1)+SIZEOF(POINTER_CMultipleVirtualInheritanceSuperBase1)+SIZEOF(MValueSuperBase2)+SIZEOF(POINTER_CMultipleVirtualInheritanceSuperBase2)+SIZEOF(MValueSuperBase3)+SIZEOF(POINTER_CMultipleVirtualInheritanceSuperBase3)+SIZEOF(MValueBase2)+SIZEOF(POINTER_VT)=8+8+16+8+24+8+40+8=120.
	wcout << L"CLASS CMultipleVirtualInheritanceBase2 has SIZE [" << sizeof(CMultipleVirtualInheritanceBase2) << L"] !" << endl;
	// SIZE=208.
	wcout << L"CLASS CMultipleVirtualInheritanceDerived has SIZE [" << sizeof(CMultipleVirtualInheritanceDerived) << L"] !" << endl;

	PrintLineSeparator();

	CMultipleVirtualInheritanceDerived							Derived;
	CMultipleVirtualInheritanceDerived*							PointerToDerived=&Derived;

	wcout << L"INDEX of MValueBase1 [" << (reinterpret_cast<ptrdiff_t>(&Derived.MValueBase1)-reinterpret_cast<ptrdiff_t>(PointerToDerived)) << L"] !" << endl;
	wcout << L"INDEX of MValueBase2 [" << (reinterpret_cast<ptrdiff_t>(&Derived.MValueBase2)-reinterpret_cast<ptrdiff_t>(PointerToDerived)) << L"] !" << endl;
	wcout << L"INDEX of MValueDerived [" << (reinterpret_cast<ptrdiff_t>(&Derived.MValueDerived)-reinterpret_cast<ptrdiff_t>(PointerToDerived)) << L"] !" << endl;
	wcout << L"INDEX of MValueSuperBase1 [" << (reinterpret_cast<ptrdiff_t>(&Derived.MValueSuperBase1)-reinterpret_cast<ptrdiff_t>(PointerToDerived)) << L"] !" << endl;
	wcout << L"INDEX of MValueSuperBase2 [" << (reinterpret_cast<ptrdiff_t>(&Derived.MValueSuperBase2)-reinterpret_cast<ptrdiff_t>(PointerToDerived)) << L"] !" << endl;
	wcout << L"INDEX of MValueSuperBase3 [" << (reinterpret_cast<ptrdiff_t>(&Derived.MValueSuperBase3)-reinterpret_cast<ptrdiff_t>(PointerToDerived)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"ADDRESS of MValueBase1 ["<< &(Derived.MValueBase1) << L"] !" << endl;
	wcout << L"ADDRESS of MValueBase2 [" << &(Derived.MValueBase2) << L"] !" << endl;
	wcout << L"ADDRESS of MValueDerived [" << &(Derived.MValueDerived) << L"] !" << endl;
	wcout << L"ADDRESS of MValueSuperBase1 [" << &(Derived.MValueSuperBase1) << L"] !" << endl;
	wcout << L"ADDRESS of MValueSuperBase2 [" << &(Derived.MValueSuperBase2) << L"] !" << endl;
	wcout << L"ADDRESS of MValueSuperBase3 [" << &(Derived.MValueSuperBase3) << L"] !" << endl;

	/*
		Struktura CLASS 'CMultipleVirtualInheritanceDerived'. Platna pre VS2017.

		OFFET			VALUE				SIZE
		0				POINTER				8.
		8				MValueBase1			160.
		168				POINTER				8.
		176				MValueBase2			200.
		376				MValueDerived		240.
		616				POINTER				8.
		624				MValueSuperBase1	40.
		664				POINTER				8.
		672				MValueSuperBase2	80.
		752				POINTER				8.
		660				MValueSuperBase3	120.
	*/

	/*
	PrintLineSeparator();

	// Nasledujuci CODE je zavisly od IMPLEMENTACIE C++ a pri inej verzii COMPILER moze sposobit FATAL ERROR.
	char*														Memory=(char*) PointerToDerived;

	ptrdiff_t*													PointerToPointer1=(ptrdiff_t*) &Memory[0];
	ptrdiff_t*													PointerToPointer2=(ptrdiff_t*) &Memory[168];
	ptrdiff_t*													PointerToPointer3=(ptrdiff_t*) &Memory[616];
	ptrdiff_t*													PointerToPointer4=(ptrdiff_t*) &Memory[664];
	ptrdiff_t*													PointerToPointer5=(ptrdiff_t*) &Memory[752];

	ptrdiff_t													Pointer1=*PointerToPointer1;
	ptrdiff_t													Pointer2=*PointerToPointer2;
	ptrdiff_t													Pointer3=*PointerToPointer3;
	ptrdiff_t													Pointer4=*PointerToPointer4;
	ptrdiff_t													Pointer5=*PointerToPointer5;

	wcout << hex;

	wcout << L"VALUE of Pointer1 ["<< Pointer1 << L"] !" << endl;
	wcout << L"VALUE of Pointer2 ["<< Pointer2 << L"] !" << endl;
	wcout << L"VALUE of Pointer3 ["<< Pointer3 << L"] !" << endl;
	wcout << L"VALUE of Pointer4 ["<< Pointer4 << L"] !" << endl;
	wcout << L"VALUE of Pointer5 ["<< Pointer5 << L"] !" << endl;

	wcout << dec;
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVirtualInheritanceConstructorCallOrder(void)
{
	PrintLineSeparator();

	{
		CVirtualInheritanceConstructorDerived					Derived(L"AAA",L"BBB",L"CCC");

		PrintLineSeparator();

		// !!!!! Kedze sa POUZILA VIRTUAL INHERITANCE, tak SHARED BASE CLASS JE mozne volat.
		Derived.PrintValue();

		// !!!!! Vola sa verzia METHOD PrintValue(), ktora definovana v CLASS 'CVirtualInheritanceSuperBase' a je SHARED medzi CLASS 'CVirtualInheritanceConstructorBase1' a CLASS 'CVirtualInheritanceConstructorBase2'.
		Derived.CVirtualInheritanceConstructorBase1::PrintValue();

		// !!!!! Vola sa verzia METHOD PrintValue(), ktora definovana v CLASS 'CVirtualInheritanceSuperBase' a je SHARED medzi CLASS 'CVirtualInheritanceConstructorBase1' a CLASS 'CVirtualInheritanceConstructorBase2'.
		Derived.CVirtualInheritanceConstructorBase2::PrintValue();

		// !!!!! Vola sa verzia METHOD PrintValue(), ktora definovana v CLASS 'CVirtualInheritanceSuperBase' a je SHARED medzi CLASS 'CVirtualInheritanceConstructorBase1' a CLASS 'CVirtualInheritanceConstructorBase2'.
		Derived.CVirtualInheritanceConstructorDerived::CVirtualInheritanceConstructorBase1::PrintValue();

		// !!!!! Vola sa verzia METHOD PrintValue(), ktora definovana v CLASS 'CVirtualInheritanceSuperBase' a je SHARED medzi CLASS 'CVirtualInheritanceConstructorBase1' a CLASS 'CVirtualInheritanceConstructorBase2'.
		Derived.CVirtualInheritanceConstructorDerived::CVirtualInheritanceConstructorBase2::PrintValue();

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMixins(void)
{
	PrintLineSeparator();

	CMixinDerived												Derived;

	Derived.AAA();

	Derived.BBB();

	Derived.CCC();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestMultipleInterfacesInheritance();
	//TestMultipleImplementationsInheritance();
	//TestBaseMethodResolution();
	//TestNonVirtualInheritance();
	//TestVirtualInheritance();
	//TestClassSizes();
	//TestVirtualInheritanceConstructorCallOrder();
	TestMixins();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------