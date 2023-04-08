//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <memory>
#include <iostream>
#include <vector>
#include <functional>
#include <atomic>
#include "MyDebug.h"
#include "CException.h"
#include "CCustomClass.h"
#include "CCyclicReferencesShared1.h"
#include "CCyclicReferencesShared2.h"
#include "CCyclicReferencesWeak1.h"
#include "CCyclicReferencesWeak2.h"
#include "CErrorThisParentShared.h"
#include "CErrorThisChildShared.h"
#include "CSharedPointerOnThis.h"
#include "CSharedPointerOnThisError.h"
#include "CBaseVirtual.h"
#include "CDerivedVirtual.h"
#include "CBaseNonVirtual.h"
#include "CDerivedNonVirtual.h"
#include "CName.h"
#include "CClassWithUniquePointers.h"
#include "CClassWithUniquePointersException.h"
#include "CBaseClass.h"
#include "CDerivedClass.h"
#include "CCustomDeleteFuctionForUniquePointer.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SharedPointerInner(shared_ptr<CCustomClass> Pointer)
{
	wcout << L"SharedPointerInner() - VALUE [" << Pointer->GetValue() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void SharedPointerOuter(shared_ptr<CCustomClass> Pointer)
{
	wcout << L"SharedPointerOuter() - VALUE [" << Pointer->GetValue() << L"] !" << endl;

	SharedPointerInner(Pointer);
}
//-----------------------------------------------------------------------------
void TestSharedPointer1(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wcout << L"TestSharedPointer() - VALUE [" << Pointer->GetValue() << L"] !" << endl;

		SharedPointerOuter(Pointer);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SharedPointerPrintVector(vector<shared_ptr<CCustomClass>> Vector)
{
	for(const shared_ptr<CCustomClass>& Item : Vector)
	{
		wcout << L"VALUE [" << Item->GetValue() << L"] !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestSharedPointer2(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer1(new CCustomClass(L"Timmy Anderson"));
		shared_ptr<CCustomClass>								Pointer2(new CCustomClass(L"Jenny Thompson"));
		vector<shared_ptr<CCustomClass>>						Vector;

		Vector.push_back(Pointer1);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer1);
		Vector.push_back(Pointer1);

		SharedPointerPrintVector(Vector);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SharedPointerPrintVector(vector<shared_ptr<wstring>> Vector)
{
	for(const shared_ptr<wstring>& Item : Vector)
	{
		wcout << L"VALUE [" << *Item << L"] !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestSharedPointer3(void)
{
	PrintLineSeparator();

	{
		shared_ptr<wstring>										Pointer1(new wstring(L"Timmy Anderson"));
		shared_ptr<wstring>										Pointer2(new wstring(L"Jenny Thompson"));
		vector<shared_ptr<wstring>>								Vector;

		Vector.push_back(Pointer1);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer1);
		Vector.push_back(Pointer1);

		SharedPointerPrintVector(Vector);

		PrintLineSeparator();

		// !!! Zmeni sa hodnota oboch OBJECTS na ktore SHARED SMART POINTER referuju pricom tato zmena sa premietne do vsetkych SHARED SMART POINTER, kedze referuju na tieto OBJECTS.
		*Pointer1=L"Timothy Anderson";
		(*Pointer2)[0]=L'Y';

		SharedPointerPrintVector(Vector);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointer4(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wcout << L"BEFORE RESET !" << endl;

		// Uvolni sa predchadzajuci OBJECT a zavola sa pred DESTRUCTOR.
		Pointer.reset(new CCustomClass(L"Jenny Thompson"));

		wcout << L"BEFORE NULL POINTER ASSIGNMENT !" << endl;

		// !!! OPERATR= NIE JE PRETAZENY pre POINTER. Preto COMPILER hodi na tento CODE ERROR.
		//Pointer=new CCustomClass(L"Jenny Thompson");

		// Uvolni sa OBJECT a zavola sa pred DESTRUCTOR.
		Pointer=nullptr;

		wcout << L"AFTER NULL POINTER ASSIGNMENT !" << endl;

		// !!! Kedze tu uz 'Pointer' NEOBSAHUJE ziaden OBJECT, tak sa DESTRUCTOR NEVOLA.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointer5(void)
{
	PrintLineSeparator();

	{
		// !!! FUNCTION make_shared() predstavuje EFEKTIVNEJSI sposob vytvorenia SHARED SMART POINTER.
		shared_ptr<CCustomClass>								Pointer1=make_shared<CCustomClass>(L"Timmy Anderson");
		shared_ptr<CCustomClass>								Pointer2=make_shared<CCustomClass>(L"Jenny Thompson");
		vector<shared_ptr<CCustomClass>>						Vector;

		Vector.push_back(Pointer1);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer1);
		Vector.push_back(Pointer1);

		SharedPointerPrintVector(Vector);

		wcout << L"REFERENCE COUNTER POINTER 1 [" << Pointer1.use_count() << L"] !" << endl;
		wcout << L"REFERENCE COUNTER POINTER 2 [" << Pointer2.use_count() << L"] !" << endl;

		wcout << L"BEFORE CLEAR !" << endl;

		// !!! DESTRUCTORS sa NEVOLAJU, pretoze VARIABLES 'Pointer1' a 'Pointer2' sa referuju na OBJECTS.
		Vector.clear();

		wcout << L"AFTER CLEAR !" << endl;

		wcout << L"REFERENCE COUNTER POINTER 1 [" << Pointer1.use_count() << L"] !" << endl;
		wcout << L"REFERENCE COUNTER POINTER 2 [" << Pointer2.use_count() << L"] !" << endl;

		Pointer1=nullptr;
		Pointer2=nullptr;

		wcout << L"AFTER NULL POINTER ASSIGMENT !" << endl;

		wcout << L"REFERENCE COUNTER POINTER 1 [" << Pointer1.use_count() << L"] !" << endl;
		wcout << L"REFERENCE COUNTER POINTER 2 [" << Pointer2.use_count() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! CUSTOM DELETE FUNCTION NESMIE hadzat EXCEPTIONS.
void CustomDeleter(CCustomClass* ObjectToDelete) noexcept
{
	wcout << L"CUSTOM DELETER was CALLED !" << endl;

	delete(ObjectToDelete);
}
//-----------------------------------------------------------------------------
void TestSharedPointerCustomDeleter(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"),CustomDeleter);

		wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"),[](CCustomClass* ObjectToDelete){wcout << L"CUSTOM DELETER was CALLED !" << endl; delete(ObjectToDelete);});

		wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! CUSTOM DELETE FUNCTION NESMIE hadzat EXCEPTIONS.
void CustomArrayDeleter1(int* ObjectToDelete) noexcept
{
	wcout << L"CUSTOM ARRAY DELETER was CALLED !" << endl;

	delete[](ObjectToDelete);
}
//-----------------------------------------------------------------------------
// !!! CUSTOM DELETE FUNCTION NESMIE hadzat EXCEPTIONS.
void CustomArrayDeleter2(CCustomClass* ObjectToDelete) noexcept
{
	wcout << L"CUSTOM ARRAY DELETER was CALLED !" << endl;

	delete[](ObjectToDelete);
}
//-----------------------------------------------------------------------------
void TestSharedPointerArrays(void)
{
	PrintLineSeparator();

	{
		// !!!!! Ak sa SHARED SMART POINTERS pouzivaju pre ulozenie ARRAYS, je NEVYHNUTNE definovat CUSTOM DELETE FUNCTION v ktorej sa zavola OPERATOR DELETE[].
		shared_ptr<int>											Pointer(new int[10],CustomArrayDeleter1);

		wcout << L"REFERENCE COUNTER [" << Pointer.use_count() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Ak sa SHARED SMART POINTERS pouzivaju pre ulozenie ARRAYS, je NEVYHNUTNE definovat CUSTOM DELETE FUNCTION v ktorej sa zavola OPERATOR DELETE[].
		shared_ptr<CCustomClass>								Pointer(new CCustomClass[5],CustomArrayDeleter2);

		wcout << L"REFERENCE COUNTER [" << Pointer.use_count() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestWeakPointer1(void)
{
	PrintLineSeparator();

	weak_ptr<wstring>											WeakPointer;

	{
		shared_ptr<wstring>										SharedPointer(new wstring(L"Timmy Anderson"));
		vector<shared_ptr<wstring>>								Vector;

		WeakPointer=SharedPointer;

		Vector.push_back(SharedPointer);
		Vector.push_back(SharedPointer);
		Vector.push_back(SharedPointer);

		wcout << L"REFERENCE COUNTER [" << WeakPointer.use_count() << L"] !" << endl;
		wcout << L"EXPIRED [" << *((WeakPointer.expired()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

		// !!! VALUE sa ziskava pomocou METHOD weak_ptr<T>.lock().
		wcout << L"VALUE [" << *(WeakPointer.lock()) << L"] !" << endl;
	}

	wcout << L"AFTER RELEASE - REFERENCE COUNTER [" << WeakPointer.use_count() << L"] !" << endl;
	wcout << L"AFTER RELEASE - EXPIRED [" << ((WeakPointer.expired()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestWeakPointer2(void)
{
	PrintLineSeparator();

	weak_ptr<wstring>											WeakPointer;

	{
		shared_ptr<wstring>										SharedPointer(new wstring(L"Timmy Anderson"));
		vector<shared_ptr<wstring>>								Vector;

		WeakPointer=SharedPointer;

		Vector.push_back(SharedPointer);
		Vector.push_back(SharedPointer);
		Vector.push_back(SharedPointer);

		wcout << L"WEAK POINTER - REFERENCE COUNTER [" << WeakPointer.use_count() << L"] !" << endl;
		wcout << L"WEAK POINTER - EXPIRED [" << ((WeakPointer.expired()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

		// !!! CLASS weak_ptr<T> je mozne konvertovat na CLASS shared_ptr<T>.
		shared_ptr<wstring>										NewSharedPointer(WeakPointer.lock());

		wcout << L"VALUE [" << *NewSharedPointer << L"] !" << endl;

		wcout << L"SHARED POINTER - REFERENCE COUNTER [" << SharedPointer.use_count() << L"] !" << endl;
		wcout << L"NEW SHARED POINTER - REFERENCE COUNTER [" << NewSharedPointer.use_count() << L"] !" << endl;
	}

	wcout << L"AFTER RELEASE - REFERENCE COUNTER [" << WeakPointer.use_count() << L"] !" << endl;
	wcout << L"AFTER RELEASE - EXPIRED [" << ((WeakPointer.expired()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestWeakPointer3(void)
{
	PrintLineSeparator();

	try
	{
		shared_ptr<wstring>										SharedPointer1(new wstring(L"Timmy Anderson"));

		wcout << L"SHARED POINTER 1 [" << *SharedPointer1 << L"] !" << endl;

		weak_ptr<wstring>										WeakPointer(SharedPointer1);

		// !!! VALUE sa ziskava pomocou METHOD weak_ptr<T>.lock().
		wcout << L"WEAK POINTER 1 [" << *(WeakPointer.lock()) << L"] !" << endl;
			
		// SHARED POINTER vytvoreny z WEAK POINTER.
		shared_ptr<wstring>										SharedPointer2(WeakPointer);

		wcout << L"SHARED POINTER 2 [" << *SharedPointer2 << L"] !" << endl;

		wcout << L"WEAK POINTER - REFERENCE COUNTER [" << WeakPointer.use_count() << L"] !" << endl;

		SharedPointer1.reset();

		wcout << L"WEAK POINTER - REFERENCE COUNTER after RESET 1 [" << WeakPointer.use_count() << L"] !" << endl;

		SharedPointer2.reset();

		wcout << L"WEAK POINTER - REFERENCE COUNTER after RESET 2 [" << WeakPointer.use_count() << L"] !" << endl;

		// !!!!! Pri pokuse o vytvorenie SHARED POINTER z PRAZDNEHO WEAK POINTER dojde k hodeniu EXCEPTION.
		shared_ptr<wstring>										SharedPointer3(WeakPointer);

		wcout << L"SHARED POINTER 3 [" << *SharedPointer3 << L"] !" << endl;
	}
	catch(bad_weak_ptr& E)
	{
 		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE vedie k MEMORY LEAK.
void TestCyclicReferencesSharedPointers1(void)
{
	PrintLineSeparator();

	{
		// !!!!! TENTO CODE vedie k MEMORY LEAK.
		shared_ptr<CCyclicReferencesShared1>					Pointer1(new CCyclicReferencesShared1());
		shared_ptr<CCyclicReferencesShared2>					Pointer2(new CCyclicReferencesShared2());

		// !!!!! Vytvori sa CYCLIC REFERENCE.
		Pointer1->SetPointer(Pointer2);
		Pointer2->SetPointer(Pointer1);

		Pointer1->CallOther();
		Pointer2->CallOther();

		// !!!!! Vdaka tomu, ze existuje CYCLIC REFERENCE, tak v DESTRUCTORS CLASS [shared_ptr<T>] NEDOJDE k uvolneniu OBJECT 'CCyclicReferencesShared1' a 'CCyclicReferencesShared2'.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE vedie k MEMORY LEAK.
void TestCyclicReferencesSharedPointers2(void)
{
	PrintLineSeparator();

	weak_ptr<CCyclicReferencesShared1>							WeakPointer1;
	weak_ptr<CCyclicReferencesShared2>							WeakPointer2;

	{
		// !!!!! TENTO CODE vedie k MEMORY LEAK.
		shared_ptr<CCyclicReferencesShared1>					Pointer1(new CCyclicReferencesShared1());
		shared_ptr<CCyclicReferencesShared2>					Pointer2(new CCyclicReferencesShared2());

		WeakPointer1=Pointer1;
		WeakPointer2=Pointer2;

		// !!!!! Vytvori sa CYCLIC REFERENCE.
		Pointer1->SetPointer(Pointer2);
		Pointer2->SetPointer(Pointer1);

		Pointer1->CallOther();
		Pointer2->CallOther();

		// !!!!! Hodnoty REFERENCE COUNTERS oboch SHARED POINTERS budu 2, pretoze existuje CYCLIC REFERENCE.
		wcout << L"IN SCOPE - WEAK POINTER 1 [" << WeakPointer1.use_count() << L"] !" << endl;
		wcout << L"IN SCOPE - WEAK POINTER 2 [" << WeakPointer2.use_count() << L"] !" << endl;

		// !!!!! Vdaka tomu, ze existuje CYCLIC REFERENCE, tak v DESTRUCTORS CLASS [shared_ptr<T>] NEDOJDE k uvolneniu OBJECT 'CCyclicReferencesShared1' a 'CCyclicReferencesShared2'.
	}

	// !!!!! Hodnoty REFERENCE COUNTERS oboch SHARED POINTERS budu 1, co je dovod preco neboli uvolnene.
	wcout << L"OUT of SCOPE - WEAK POINTER 1 [" << WeakPointer1.use_count() << L"] !" << endl;
	wcout << L"OUT of SCOPE - WEAK POINTER 2 [" << WeakPointer2.use_count() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE NESPOSOBI MEMORY LEAK.
void TestCyclicReferencesSharedPointers3(void)
{
	PrintLineSeparator();

	weak_ptr<CCyclicReferencesShared1>							WeakPointer1;
	weak_ptr<CCyclicReferencesShared2>							WeakPointer2;

	{
		// !!!!! TENTO CODE vedie k MEMORY LEAK.
		shared_ptr<CCyclicReferencesShared1>					Pointer1(new CCyclicReferencesShared1());
		shared_ptr<CCyclicReferencesShared2>					Pointer2(new CCyclicReferencesShared2());

		WeakPointer1=Pointer1;
		WeakPointer2=Pointer2;

		// !!!!! Vytvori sa CYCLIC REFERENCE.
		Pointer1->SetPointer(Pointer2);
		Pointer2->SetPointer(Pointer1);

		Pointer1->CallOther();
		Pointer2->CallOther();

		// !!!!! Hodnoty REFERENCE COUNTERS oboch SHARED POINTERS budu 2, pretoze existuje CYCLIC REFERENCE.
		wcout << L"IN SCOPE - WEAK POINTER 1 [" << WeakPointer1.use_count() << L"] !" << endl;
		wcout << L"IN SCOPE - WEAK POINTER 2 [" << WeakPointer2.use_count() << L"] !" << endl;

		// !!! Znizia sa hodnoty REFERENCE COUNTERS.
		Pointer1->GetPointer().reset();
		Pointer2->GetPointer().reset();

		// !!!!! Vdaka tomu, ze sa EXPLICITNE uvolnili CYCLIC REFERENCES, tak v DESTRUCTORS CLASS [shared_ptr<T>] DOJDE k uvolneniu OBJECT 'CCyclicReferencesShared1' a 'CCyclicReferencesShared2'.
	}

	// !!!!! Hodnoty REFERENCE COUNTERS oboch SHARED POINTERS budu 0.
	wcout << L"OUT of SCOPE - WEAK POINTER 1 [" << WeakPointer1.use_count() << L"] !" << endl;
	wcout << L"OUT of SCOPE - WEAK POINTER 2 [" << WeakPointer2.use_count() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCyclicReferencesWeakPointers(void)
{
	PrintLineSeparator();

	{
		// !!!!! TENTO CODE NEVEDIE k MEMORY LEAK, pretoze CYCLIC REFERENCE je realizovana cez CLASS [weak_ptr<T>].
		shared_ptr<CCyclicReferencesWeak1>						Pointer1(new CCyclicReferencesWeak1());
		shared_ptr<CCyclicReferencesWeak2>						Pointer2(new CCyclicReferencesWeak2());

		// !!!!! Vytvori sa CYCLIC REFERENCE cez WEAK POINTERS.
		Pointer1->SetPointer(weak_ptr<CCyclicReferencesWeak2>(Pointer2));
		Pointer2->SetPointer(weak_ptr<CCyclicReferencesWeak1>(Pointer1));

		Pointer1->CallOther();
		Pointer2->CallOther();

		// !!!!! Vdaka tomu, ze CYCLIC REFERENCE je realizovana cez WEAK POINTERS, tak v DESTRUCTORS CLASS [shared_ptr<T>] DOJDE k uvolneniu OBJECT 'CCyclicReferencesShared1' a 'CCyclicReferencesShared2'.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE SPOSOBI MEMORY ACCESS ERROR.
void TestSharedPointerError(void)
{
	PrintLineSeparator();

	{
		wstring*												Data=new wstring(L"Timmy Anderson");
		shared_ptr<wstring>										Pointer1(Data);
		shared_ptr<wstring>										Pointer2(Data);

		wcout << L"POINTER 1 [" << *Pointer1 << L"] !" << endl;
		wcout << L"POINTER 2 [" << *Pointer2 << L"] !" << endl;

		// !!!!! CODE sposobi MEMORY ACCESS ERROR, pretoze VARIABLES 'Pointer1' a 'Pointer2' maju NEZAVISLE REFERENCE COUNTERS a ich DESTRUCTORS sa OBE pokusia zavolat OPERATOR DELETE pre VARIABLE 'Data'.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
void TestSharedPointerOK(void)
{
	PrintLineSeparator();

	{
		wstring*												Data=new wstring(L"Timmy Anderson");
		shared_ptr<wstring>										Pointer1(Data);
		// !!! Namiesto POINTER sa prenasa instancia CLASS [shared_ptr<wstring>].
		shared_ptr<wstring>										Pointer2(Pointer1);

		wcout << L"POINTER 1 [" << *Pointer1 << L"] !" << endl;
		wcout << L"POINTER 2 [" << *Pointer2 << L"] !" << endl;

		// !!!!! CODE NESPOSOBI MEMORY ACCESS ERROR, pretoze VARIABLES 'Pointer1' a 'Pointer2' maju SPOLOCNY REFERENCE COUNTERS, ktory az ked klesne na 0, dojde k uvolneniu VARIABLE 'Data'. VARIABLE 'Data' sa teda uvolni iba raz.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE SPOSOBI MEMORY ACCESS ERROR.
void TestErrorThisShared(void)
{
	PrintLineSeparator();

	{
		// !!!!! TENTO CODE SPOSOBI MEMORY ACCESS ERROR.
		shared_ptr<CErrorThisParentShared>						Pointer1(new CErrorThisParentShared());
		shared_ptr<CErrorThisChildShared>						Pointer2(Pointer1->GetChild());

		Pointer1->CallChild();
		Pointer2->CallParent();

		wcout << L"POINTER 1 REFERENCE COUNTER [" << Pointer1.use_count() << L"] !" << endl;
		wcout << L"POINTER 2 REFERENCE COUNTER [" << Pointer2.use_count() << L"] !" << endl;

		wcout << L"PARENT REFERENCE COUNTER 1 [" << Pointer1->GetReferenceCounter() << L"] !" << endl;
		wcout << L"CHILD REFERENCE COUNTER 2 [" << Pointer2->GetReferenceCounter() << L"] !" << endl;

		// !!!!! Na konci SCOPE instancia CLASS [shared_ptr<CErrorThisParentShared>] vola DESTRUCTOR OBJECT [CErrorThisParentShared], lebo jeho REFERENCE COUNTER je rovny 1.
		// !!!!! Na konci SCOPE instancia CLASS [shared_ptr<CErrorThisChildShared>] NEVOLA DESTRUCTOR OBJECT [CErrorThisParentChild], pretoze jeho REFERENCE COUNTER je rovna 2. Je to preto, lebo instancia CLASS [shared_ptr<CErrorThisChildShared>] referuje na FIELD 'CErrorThisParentShared.MChild', ktory drzi inkrementoval hodnotu REFERENCE COUNTER o 1. Vysledna hodnota je teda 2.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedThisPointerOK1(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CSharedPointerOnThis>						Pointer(new CSharedPointerOnThis());
		
		// !!! Do FIELD sa ulozi THIS POINTER.
		Pointer->SetPointer();

		Pointer->SomeMethod();

		// !!!!! Je NUTNE, aby sa pred koncom FUNCTION uvolnil POINTER NA THIS ulozeny vo FIELD. Ak by sa tak nestalo, potom by doslo k CYCLIC REFERENCE (FIELD obsahuje SHARED POINTER a drzi REFERENCE COUNTER na hodnote>1) a NEDOSLO by k UVOLNENIU MEMORY. Vznikol by tak MEMORY LEAK.
		Pointer->ResetPointer();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedThisPointerOK2(void)
{
	PrintLineSeparator();

	CSharedPointerOnThis*										Pointer=nullptr;

	try
	{
		// !!!!! HODI EXCEPTION, pretoze pri pouziti CLASS [enable_shared_from_this] je NEVYHNUTNE vytvorenu instanciu CLASS [CSharedPointerOnThis] ulozit do instancie CLASS [shared_ptr<T>].
		Pointer=new CSharedPointerOnThis();
		
		// !!! Do FIELD sa ulozi THIS POINTER.
		Pointer->SetPointer();

		Pointer->SomeMethod();

		// !!!!! Je NUTNE, aby sa pred koncom FUNCTION uvolnil POINTER NA THIS ulozeny vo FIELD. Ak by sa tak nestalo, potom by doslo k CYCLIC REFERENCE (FIELD obsahuje SHARED POINTER a drzi REFERENCE COUNTER na hodnote>1) a NEDOSLO by k UVOLNENIU MEMORY. Vznikol by tak MEMORY LEAK.
		Pointer->ResetPointer();

		delete(Pointer);
		Pointer=nullptr;
	}
	catch(bad_weak_ptr& E)
	{
		if (Pointer!=nullptr)
		{
			// !!!!! Je NUTNE, aby sa pred koncom FUNCTION uvolnil POINTER NA THIS ulozeny vo FIELD. Ak by sa tak nestalo, potom by doslo k CYCLIC REFERENCE (FIELD obsahuje SHARED POINTER a drzi REFERENCE COUNTER na hodnote>1) a NEDOSLO by k UVOLNENIU MEMORY. Vznikol by tak MEMORY LEAK.
			Pointer->ResetPointer();

			delete(Pointer);
			Pointer=nullptr;
		}

 		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedThisPointerOK3(void)
{
	PrintLineSeparator();

	try
	{
		CSharedPointerOnThis									Object;
		
		// !!! Do FIELD sa ulozi THIS POINTER.
		// !!!!! HODI EXCEPTION, pretoze pri pouziti CLASS [enable_shared_from_this] je NEVYHNUTNE vytvorit instanciu CLASS [CSharedPointerOnThis] pomocou OPERATOR NEW.
		Object.SetPointer();

		Object.SomeMethod();

		// !!!!! Je NUTNE, aby sa pred koncom FUNCTION uvolnil POINTER NA THIS ulozeny vo FIELD. Ak by sa tak nestalo, potom by doslo k CYCLIC REFERENCE (FIELD obsahuje SHARED POINTER a drzi REFERENCE COUNTER na hodnote>1) a NEDOSLO by k UVOLNENIU MEMORY. Vznikol by tak MEMORY LEAK.
		Object.ResetPointer();
	}
	catch(bad_weak_ptr& E)
	{
 		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedThisPointerError1(void)
{
	PrintLineSeparator();

	try
	{
		// !!!!! Hodi EXCEPTION, pretoze METHOD shared_from_this() je volana v CONSTRUCTOR CLASS [CSharedPointerOnThisError] co CLASS [enable_shared_from_this<T>] NEUMOZNUJE.
		shared_ptr<CSharedPointerOnThisError>					Pointer(new CSharedPointerOnThisError());
		
		Pointer->SomeMethod();
	}
	catch(bad_weak_ptr& E)
	{
 		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedThisPointerError2(void)
{
	PrintLineSeparator();

	CSharedPointerOnThisError*									Pointer=nullptr;

	try
	{
		// !!!!! HODI EXCEPTION, pretoze pri pouziti CLASS [enable_shared_from_this] je NEVYHNUTNE vytvorenu instanciu CLASS [CSharedPointerOnThis] ulozit do instancie CLASS [shared_ptr<T>].
		Pointer=new CSharedPointerOnThisError();
		
		Pointer->SomeMethod();

		delete(Pointer);
		Pointer=nullptr;
	}
	catch(bad_weak_ptr& E)
	{
		if (Pointer!=nullptr)
		{
			delete(Pointer);
			Pointer=nullptr;
		}

 		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedThisPointerError3(void)
{
	PrintLineSeparator();

	try
	{
		// !!!!! HODI EXCEPTION, pretoze pri pouziti CLASS [enable_shared_from_this] je NEVYHNUTNE vytvorit instanciu CLASS [CSharedPointerOnThis] pomocou OPERATOR NEW.
		CSharedPointerOnThisError								Object;
		
		Object.SomeMethod();
	}
	catch(bad_weak_ptr& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointerDynamicCasts(void)
{
	PrintLineSeparator();

	shared_ptr<CBaseVirtual>									Pointer1(new CDerivedVirtual());

	Pointer1->VirtualMethod();

	shared_ptr<CDerivedVirtual>									Pointer2=dynamic_pointer_cast<CDerivedVirtual,CBaseVirtual>(Pointer1);

	if (Pointer2!=nullptr)
	{
		Pointer2->VirtualMethod();
	}
	else
	{
		wcout << L"POINTER 2 is NULL !" << endl;
	}

	shared_ptr<wstring>											Pointer3=dynamic_pointer_cast<wstring,CBaseVirtual>(Pointer1);

	if (Pointer3!=nullptr)
	{
		wcout << L"POINTER 3 is [" << *Pointer3 << L"] !" << endl;
	}
	else
	{
		wcout << L"POINTER 3 is NULL !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointerStaticCasts(void)
{
	PrintLineSeparator();

	/*
	shared_ptr<float>											Pointer1(new float(3.14f));
	// !!!!! COMPILER hodi ERROR, pretoze ako STANDARDNY C++ OPERATOR static_cast<T>(), tak ani FUNCTION static_pointer_cast<T1,T2>() NEPODPORUJU konverzie FLOAT a DOUBLE POINTERS. Dovodom preco static_cast<T>() NA ROZDIEL od STANDARDNEHO PRETYPOVACIEHO OPERATOR () konverzie takychto POINTERS NEPODPORUJE je, ze su POTENCIALNE NEBEZPECNE, pretoze po pretypovani POINTERS odkazuju na TYPE s INOU DLZKOU v BYTES (FLOAT ma 4 BYTES, zatial co DOUBLE ma 8 BYTES). Z bezpecnostnych dovodov su tieto konverzie pomocou OPERATOR static_cast<T>() ZAKAZANE.
	shared_ptr<double>											Pointer2=static_pointer_cast<double,float>(Pointer1);

	wcout << L"DOUBLE VALUE [" << << L"] !" << endl;,*Pointer2);
	*/

	shared_ptr<CBaseVirtual>									Pointer3(new CDerivedVirtual());

	Pointer3->VirtualMethod();

	shared_ptr<CDerivedVirtual>									Pointer4=static_pointer_cast<CDerivedVirtual,CBaseVirtual>(Pointer3);

	Pointer4->VirtualMethod();

	// Konverzia na TYPE 'CBaseVirtual*'.
	shared_ptr<CBaseVirtual>									Pointer5=static_pointer_cast<CBaseVirtual,CDerivedVirtual>(Pointer4);

	Pointer5->VirtualMethod();

	shared_ptr<CBaseVirtual>									Pointer6(new CBaseVirtual());

	Pointer6->VirtualMethod();

	shared_ptr<CDerivedVirtual>									Pointer7=static_pointer_cast<CDerivedVirtual,CBaseVirtual>(Pointer6);

	Pointer7->VirtualMethod();

	PrintLineSeparator();

	// !!! Urobi STATICKU KONVERZIU na 'CBaseNonVirtual*'.
	shared_ptr<CBaseNonVirtual>									Pointer8(new CDerivedNonVirtual());

	Pointer8->NonVirtualMethod();

	shared_ptr<CDerivedNonVirtual>								Pointer9=static_pointer_cast<CDerivedNonVirtual,CBaseNonVirtual>(Pointer8);

	Pointer9->NonVirtualMethod();

	// !!! Urobi STATICKU KONVERZIU na 'CBaseNonVirtual*'.
	shared_ptr<CBaseNonVirtual>									Pointer10=static_pointer_cast<CBaseNonVirtual,CDerivedNonVirtual>(Pointer9);

	Pointer10->NonVirtualMethod();

	shared_ptr<CBaseNonVirtual>									Pointer11(new CBaseNonVirtual());

	Pointer11->NonVirtualMethod();

	shared_ptr<CDerivedNonVirtual>								Pointer12=static_pointer_cast<CDerivedNonVirtual,CBaseNonVirtual>(Pointer11);

	Pointer12->NonVirtualMethod();

	PrintLineSeparator();

	shared_ptr<void>											Pointer13(new wstring(L"Timmy Anderson"));

	// Pretypovanie na 'wstring*'.
	shared_ptr<wstring>											Pointer14=static_pointer_cast<wstring,void>(Pointer13);

	wcout << L"VALUE [" << *Pointer14 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointerConstCasts(void)
{
	PrintLineSeparator();

	shared_ptr<const int>										Pointer1(new const int(10));

	wcout << L"POINTER 1 [" << *Pointer1 << L"] !" << endl;

	shared_ptr<int>												Pointer2=const_pointer_cast<int,const int>(Pointer1);

	wcout << L"POINTER 2 [" << *Pointer2 << L"] !" << endl;

	*Pointer2=20;

	wcout << L"POINTER 1 [" << *Pointer1 << L"] !" << endl;
	wcout << L"POINTER 2 [" << *Pointer2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointerAliasingConstructor(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CName>										Name(new CName(L"Timmy",L"Anderson",12));

		// !!! Pouzije sa ALIASING CONSTRUCTOR, pretoze zivotnost OBJECT 'Name' a jeho FIELDS je zviazana.
		shared_ptr<wstring>										FirstName(Name,&Name->MFirstName);
		shared_ptr<wstring>										LastName(Name,&Name->MLastName);
		shared_ptr<int>											Age(Name,&Name->MAge);

		wcout << L"FIRST NAME [" << *FirstName << L"], LAST NAME [" << *LastName << L"], AGE [" << *Age << L"] !" << endl;

		wcout << L"NAME COUNT [" << Name.use_count() << L"] !" << endl;
		wcout << L"FIRST NAME COUNT [" << FirstName.use_count() << L"] !" << endl;
		wcout << L"LAST NAME COUNT [" << LastName.use_count() << L"] !" << endl;
		wcout << L"AGE COUNT [" << Age.use_count() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointerThreadSafe(void)
{
	PrintLineSeparator();

	{
		shared_ptr<wstring>										SharedPointer;
		shared_ptr<wstring>										LocalPointer(new wstring(L"Timmy Anderson"));

		// !!! Priradenie POINTER ATOMICKYM SPOSOBOM.
		atomic_store(&SharedPointer,LocalPointer);

		// !!! Citanie POINTER ATOMICKYM SPOSOBOM.
		shared_ptr<wstring>										CopiedPointer=atomic_load(&SharedPointer);

		wcout << L"COPIED POINTER [" << CopiedPointer->c_str() << L"] !" << endl;

		wcout << L"LOCAL POINTER [" << LocalPointer.use_count() << L"] !" << endl;
		wcout << L"SHARED POINTER [" << SharedPointer.use_count() << L"] !" << endl;
		wcout << L"COPIED POINTER [" << CopiedPointer.use_count() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointer1(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		// !!! OPERATR= NIE JE PRETAZENY pre POINTER. Preto COMPILER hodi na tento CODE ERROR.
		//Pointer=new CCustomClass(L"Jenny Thompson");

		wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointer2(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;

		// !!! Zavola DESTRUCTOR.
		Pointer.reset();

		if (Pointer!=nullptr)
		{
			wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;
		}
		else
		{
			wcout << L"VALUE is NULL !" << endl;
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointer3(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;

		// !!! NEZAVOLA sa DESTRUCTOR, iba instancia CLASS unique_ptr<CCustomClass> uz NEBUDE odkazovat na povodny POINTER.
		CCustomClass*											InnerPointer=Pointer.release();

		if (Pointer!=nullptr)
		{
			wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;
		}
		else
		{
			wcout << L"VALUE is NULL !" << endl;
		}

		if (InnerPointer!=nullptr)
		{
			wcout << L"INNER VALUE [" << InnerPointer->GetValue() << L"] !" << endl;
		}
		else
		{
			wcout << L"INNER VALUE is NULL !" << endl;
		}

		delete(InnerPointer);
		InnerPointer=nullptr;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointer4(void)
{
	PrintLineSeparator();

	{
		unique_ptr<wstring>										Pointer(new wstring(L"Timmy Anderson"));

		wcout << L"VALUE [" << Pointer->c_str() << L"] !" << endl;

		(*Pointer)[2]=L'M';

		wcout << L"VALUE [" << Pointer->c_str() << L"] !" << endl;

		// !!! FUNCTION unique_ptr<T>.get() vracia POINTER na referovany OBJECT.
		wstring*												InnerPointer=Pointer.get();

		wcout << L"INNER VALUE [" << InnerPointer->c_str() << L"] !" << endl;

		wcout << L"INNER VALUE " << *InnerPointer << L" !" << endl;

		// Pouzitie OPERATOR BOOL.
		if (Pointer!=nullptr)
		{
			wcout << L"POINTER is VALID !" << endl;
		}
		else
		{
			wcout << L"POINTER is NULL !" << endl;
		}

		Pointer.reset();

		// Pouzitie OPERATOR BOOL.
		if (Pointer!=nullptr)
		{
			wcout << L"POINTER is VALID !" << endl;
		}
		else
		{
			wcout << L"POINTER is NULL !" << endl;
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointerAssignment1(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// !!! Povodny OBJECT sa UVOLNI a nahradi sa NOVYM OBJECT.
		Pointer=unique_ptr<CCustomClass>(new CCustomClass(L"Jenny Thompson"));

		wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointerAssignment2(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer1(new CCustomClass(L"Timmy Anderson"));

		wcout << L"POINTER 1 [" << Pointer1->GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// !!!!! COMPILER hodi ERROR, pretoze OPERATOR= s COPY CONSTRUCTOR NIE JE PODPOROVANY.
		//unique_ptr<CCustomClass>								Pointer2(Pointer1);

		unique_ptr<CCustomClass>								Pointer2;

		// !!!!! COMPILER hodi ERROR, pretoze OPERATOR= s COPY SEMANTICS NIE JE PODPOROVANY.
		//Pointer2=Pointer1;

		// !!!!! COMPILER OPERATOR= pre MOVE SEMANTICS PODPORUJE.
		// !!!!! Hodnota 'Pointer1' bude rovna NULL.
		Pointer2=move(Pointer1);

		wcout << L"POINTER 2 [" << Pointer2->GetValue() << L"] !" << endl;

		if (Pointer1!=nullptr)
		{
			wcout << L"POINTER 1 [" << Pointer1->GetValue() << L"] !" << endl;
		}
		else
		{
			wcout << L"POINTER 1 is NULL !" << endl;
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! UNIQUE POINTERS je mozne bez problemov prenasat pomocou REFERENCES.
void UniquePointerByReference(unique_ptr<CCustomClass>& Pointer)
{
	wcout << L"INSIDE UniquePointerByReference() [" << Pointer->GetValue() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
// !!!!! FUNCTION preberie OBJECT ulozeny v PARAMETER 'Pointer'.
void UniquePointerByValue(unique_ptr<CCustomClass> Pointer)
{
	wcout << L"INSIDE UniquePointerByValue() [" << Pointer->GetValue() << L"] !" << endl;

	// !!!!! Tu sa zavola DESTRUCTOR pre OBJECT ulozeny v PARAMETER 'Pointer'.
}
//-----------------------------------------------------------------------------
void TestUniquePointerFunctionCalling(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		PrintLineSeparator();

		wcout << L"BEFORE CALL by REFERENCE !" << endl;

		UniquePointerByReference(Pointer);

		wcout << L"AFTER CALL by REFERENCE !" << endl;

		PrintLineSeparator();

		/*
		wcout << L"BEFORE CALL by VALUE !" << endl;

		// !!!!! COMPILER hodi ERROR, pretoze COPY SEMANTICS NIE JE PODPOROVANA.
		UniquePointerByValue(Pointer);

		wcout << L"AFTER CALL by VALUE !" << endl;
		*/

		wcout << L"BEFORE CALL by VALUE !" << endl;

		// !!!!! Tento CODE COMPILER akceptuje, pretoze MOVE SEMANTICS je POVOLENA.
		// !!!!! Kedze sa pouzila MOVE SEMANTICS, tak OBJECT ulozeny vo VARIABLE 'Pointer' bude PRENESENY do FUNCTION UniquePointerByValue(), ktora tento OBJECT uvolni z MEMORY. To znaci, ze VOLANA FUNCTION UVOLNI OBJECT z MEMORY.
		UniquePointerByValue(move(Pointer));

		wcout << L"AFTER CALL by VALUE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! FUNCTION vytvori NOVY OBJECT pomocou OPERATOR NEW.
unique_ptr<CCustomClass> CreateObject1(wstring Value)
{
	unique_ptr<CCustomClass>									Pointer(new CCustomClass(Value));

	// !!!!! Nie je NUTNE pouzit MOVE SEMANTICS, pretoze C++ ju POUZIJE AUTOMATICKY. Je to preto, lebo CLASS [unique_ptr<T>] ma definovany MOVE CONSTRUCTOR a C++ ho AUTOMATICKY POUZIJE.
	return(Pointer);
}
//-----------------------------------------------------------------------------
void TestUniquePointerReturnValue1(void)
{
	PrintLineSeparator();

	{
		// !!! FUNCTION CreateObject() VYTVORILA OBJECT, no tento sa uvolni AZ v TEJTO FUNCTION.
		unique_ptr<CCustomClass>								Pointer1=CreateObject1(L"Timmy Anderson");

		wcout << L"POINTER 1 [" << Pointer1->GetValue() << L"] !" << endl;

		PrintLineSeparator();

		unique_ptr<CCustomClass>								Pointer2;

		// !!! FUNCTION CreateObject() VYTVORILA OBJECT, no tento sa uvolni AZ v TEJTO FUNCTION.
		Pointer2=CreateObject1(L"Jenny Thompson");

		wcout << L"POINTER 2 [" << Pointer2->GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// !!!!! Aj ked sa RETURN VALUE NEPRIRADI do ZIADNEJ VARIABLE, tato TEMPORARY VARIBLE bude UVOLNENA.
		// !!!!! DESTRUCTOR pre vytvoreny OBJECT sa vola OKAMZITE, teda este PRED skoncenim SCOPE.
		CreateObject1(L"XXX YYY");

		wcout << L"END of SCOPE !" << endl;

		// !!! Teraz sa zavolaju DESTRUCTORS pre VARIABLES 'Pointer1' a 'Pointer2'.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! FUNCTION vytvori NOVY OBJECT pomocou OPERATOR NEW.
unique_ptr<CCustomClass> CreateObject2(wstring Value)
{
	unique_ptr<CCustomClass>									Pointer(new CCustomClass(Value));

	// !!!!! Nie je NUTNE pouzit MOVE SEMANTICS, pretoze C++ ju POUZIJE AUTOMATICKY. Je to preto, lebo CLASS [unique_ptr<T>] ma definovany MOVE CONSTRUCTOR a C++ ho AUTOMATICKY POUZIJE.
	return(Pointer);
}
//-----------------------------------------------------------------------------
void TestUniquePointerReturnValue2(void)
{
	PrintLineSeparator();

	{
		wcout << L"BEFORE CYCLE !" << endl;
		
		for(int Index=0;Index<5;Index++)
		{
			// !!! FUNCTION CreateObject() VYTVORILA OBJECT, no tento sa uvolni AZ v TEJTO FUNCTION.
			unique_ptr<CCustomClass>							Pointer=CreateObject2(L"Timmy Anderson");

			wcout << L"POINTER [" << Pointer->GetValue() << L"] !" << endl;
		}

		wcout << L"AFTER CYCLE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestClassWithUniquePointers(void)
{
	PrintLineSeparator();

	{
		CClassWithUniquePointers								Object(L"Timmy",L"Anderson",12);

		// !!! Kedze CLASS 'CClassWithUniquePointers' NEDEFINOVALA CUSTOM OPERATOR= s COPY SEMANTICS a CLASS [unique_ptr<T>] NEDEKLARUJE CUSTOM OPERATOR= s COPY SEMANTICS, ktoru pouziva vo svojich FIELDS, C++ NIE JE SCHOPNE vytvorit IMPLICITNY OPERATOR= s COPY SEMANTICS a tym padom COMPILER hodi ERROR.
		//Object=Object;

		Object.Print();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestClassWithUniquePointersWithException(void)
{
	PrintLineSeparator();

	try
	{
		// !!! CONSTRUCTOR hodi EXCEPTION pri inicializacii jednotlivych FIELDS. Vdaka pouzitiu CLASS [unique_ptr<T>] na ulozenie POINTERS NEDOJDE k MEMORY LEAK, ako pri pouziti standardnych POINTERS.
		CClassWithUniquePointersException						Object(L"Timmy",L"Anderson",12);

		// !!! Kedze CLASS 'CClassWithUniquePointersException' NEDEFINOVALA CUSTOM OPERATOR= s COPY SEMANTICS a CLASS [unique_ptr<T>] NEDEKLARUJE CUSTOM OPERATOR= s COPY SEMANTICS, ktoru pouziva vo svojich FIELDS, C++ NIE JE SCHOPNE vytvorit IMPLICITNY OPERATOR= s COPY SEMANTICS a tym padom COMPILER hodi ERROR.
		//Object=Object;

		Object.Print();
	}
	catch(CException& E)
	{
		wcout << L"EXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointerArrays1(void)
{
	PrintLineSeparator();

	{
		const int												LENTGH=3;
		// !!! Deklaracia ARRAY.
		unique_ptr<wstring[]>									Array(new wstring[LENTGH]{L"A",L"B",L"C"});

		for(int Index=0;Index<LENTGH;Index++)
		{
			wcout << L"ITEM[" << Index << L"]=[" << Array[Index] << L"] !" << endl;
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointerArrays2(void)
{
	PrintLineSeparator();

	{
		const int												LENTGH=3;
		unique_ptr<CCustomClass[]>								Array(new CCustomClass[LENTGH]{CCustomClass(L"A"),CCustomClass(L"B"),CCustomClass(L"C")});

		wcout << L"BEFORE CYCLE !" << endl;

		for(int Index=0;Index<LENTGH;Index++)
		{
			wcout << L"ITEM[" << Index << L"]=[" << Array[Index].GetValue() << L"] !" << endl;
		}

		wcout << L"AFTER CYCLE !" << endl;

		// !!! Vola sa OPERATOR DELETE[], ktory zavola DESTRUCTORS vsetkych ARRAY ITEMS.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointerArrays3(void)
{
	PrintLineSeparator();

	{
		const int												LENTGH=3;

		// !!! Alokuje sa ARRAY obsahujuci POINTERS na CLASS 'CBaseClass' do ktorych sa ulozia instancie CLASS 'CDerivedClass'.
		unique_ptr<CBaseClass*[]>								Array(new CBaseClass*[LENTGH]{new CDerivedClass(L"A"),new CDerivedClass(L"B"),new CDerivedClass(L"C")});

		wcout << L"BEFORE CYCLE !" << endl;

		for(int Index=0;Index<LENTGH;Index++)
		{
			wcout << L"ITEM[" << Index << L"]=[" << Array[Index]->GetValue() << L"] !" << endl;
		}

		wcout << L"AFTER CYCLE !" << endl;

		// Explicitne sa uvolnia POINTERS.
		for(int Index=0;Index<LENTGH;Index++)
		{
			delete(Array[Index]);
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointerArrays4(void)
{
	PrintLineSeparator();

	{
		const int												LENTGH=3;

		// !!! Alokuje sa ARRAY obsahujuci UNIQUE SMART POINTERS na CLASS 'CBaseClass' do ktorych sa ulozia instancie CLASS 'CDerivedClass'.
		unique_ptr<unique_ptr<CBaseClass>[]>					Array(new unique_ptr<CBaseClass>[LENTGH]{unique_ptr<CBaseClass>(new CDerivedClass(L"A")),unique_ptr<CBaseClass>(new CDerivedClass(L"B")),unique_ptr<CBaseClass>(new CDerivedClass(L"C"))});

		wcout << L"BEFORE CYCLE !" << endl;

		for(int Index=0;Index<LENTGH;Index++)
		{
			wcout << L"ITEM[" << Index << L"]=[" << Array[Index]->GetValue() << L"] !" << endl;
		}

		wcout << L"AFTER CYCLE !" << endl;

		// !!! Vola sa OPERATOR DELETE[], ktory zavola DESTRUCTORS vsetkych ARRAY ITEMS.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MyCustomDeleteFunction(wstring* Pointer)
{
	delete(Pointer);

	wcout << L"CUSTOM DELETE FUNCTION as FUNCTION CALLED !" << endl;
}
//-----------------------------------------------------------------------------
void TestUniquePointerCustomDeleteFunction(void)
{
	PrintLineSeparator();

	{
		// !!! CUSTOM DELETE FUNCTION je definovana ako CUSTOM FUNCTION.
		unique_ptr<wstring,void(*)(wstring*)>					Pointer(new wstring(L"Timmy Anderson"),MyCustomDeleteFunction);

		wcout << L"VALUE [" << Pointer->c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!! CUSTOM DELETE FUNCTION je definovana ako CUSTOM FUNCTION.
		// TYPE PARAMETER je deklarovany pomocou TEMPLATE CLASS [function<T>].
		unique_ptr<wstring,function<void(wstring*)>>			Pointer(new wstring(L"Timmy Anderson"),MyCustomDeleteFunction);

		wcout << L"VALUE [" << Pointer->c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!! CUSTOM DELETE FUNCTION je definovana ako LAMBDA EXPRESSION.
		unique_ptr<wstring,void(*)(wstring*)>					Pointer(new wstring(L"Timmy Anderson"),[](wstring* Pointer){delete(Pointer); wcout << L"CUSTOM DELETE FUNCTION as LAMBDA EXPRESSION CALLED !" << endl;});

		wcout << L"VALUE [" << Pointer->c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CCustomDeleteFuctionForUniquePointer					Functor;

		// !!! CUSTOM DELETE FUNCTION je definovana ako FUNCTOR.
		unique_ptr<wstring,CCustomDeleteFuctionForUniquePointer>	Pointer(new wstring(L"Timmy Anderson"),Functor);

		wcout << L"VALUE [" << Pointer->c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!! CUSTOM DELETE FUNCTION je definovana ako FUNCTOR.
		unique_ptr<wstring,CCustomDeleteFuctionForUniquePointer>	Pointer(new wstring(L"Timmy Anderson"),CCustomDeleteFuctionForUniquePointer());

		wcout << L"VALUE [" << Pointer->c_str() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MyCustomDeleteFunctionForArrays(CCustomClass* Pointer)
{
	delete[](Pointer);

	wcout << L"CUSTOM DELETE FUNCTION for ARRAYS CALLED !" << endl;
}
//-----------------------------------------------------------------------------
void TestUniquePointerCustomDeleteFunctionForArrays(void)
{
	PrintLineSeparator();

	{
		const int												LENTGH=3;
		unique_ptr<CCustomClass[],void(*)(CCustomClass*)>		Array(new CCustomClass[LENTGH]{CCustomClass(L"A"),CCustomClass(L"B"),CCustomClass(L"C")},MyCustomDeleteFunctionForArrays);

		wcout << L"BEFORE CYCLE !" << endl;

		for(int Index=0;Index<LENTGH;Index++)
		{
			wcout << L"ITEM[" << Index << L"]=[" << Array[Index].GetValue() << L"] !" << endl;
		}

		wcout << L"AFTER CYCLE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestSharedPointer1();
	//TestSharedPointer2();
	//TestSharedPointer3();
	//TestSharedPointer4();
	//TestSharedPointer5();
	//TestSharedPointerCustomDeleter();
	//TestSharedPointerArrays();
	//TestWeakPointer1();
	//TestWeakPointer2();
	//TestWeakPointer3();
	// !!!!! TENTO CODE vedie k MEMORY LEAK.
	//TestCyclicReferencesSharedPointers1();
	// !!!!! TENTO CODE vedie k MEMORY LEAK.
	//TestCyclicReferencesSharedPointers2();
	// !!!!! TENTO CODE vedie k MEMORY LEAK.
	//TestCyclicReferencesSharedPointers3();
	//TestCyclicReferencesWeakPointers();
	// !!!!! TENTO CODE SPOSOBI MEMORY ACCESS ERROR.
	//TestSharedPointerError();
	//TestSharedPointerOK();
	// !!!!! TENTO CODE SPOSOBI MEMORY ACCESS ERROR.
	//TestErrorThisShared();
	// !!!!! TENTO CODE SPOSOBI MEMORY LEAK.
	//TestSharedThisPointerOK1();
	//TestSharedThisPointerOK2();
	//TestSharedThisPointerOK3();
	//TestSharedThisPointerError1();
	//TestSharedThisPointerError2();
	//TestSharedThisPointerError3();
	//TestSharedPointerDynamicCasts();
	//TestSharedPointerStaticCasts();
	//TestSharedPointerConstCasts();
	//TestSharedPointerAliasingConstructor();
	//TestSharedPointerThreadSafe();
	//TestUniquePointer1();
	//TestUniquePointer2();
	//TestUniquePointer3();
	//TestUniquePointer4();
	//TestUniquePointerAssignment1();
	//TestUniquePointerAssignment2();
	//TestUniquePointerFunctionCalling();
	//TestUniquePointerReturnValue1();
	//TestUniquePointerReturnValue2();
	//TestClassWithUniquePointers();
	//TestClassWithUniquePointersWithException();
	//TestUniquePointerArrays1();
	//TestUniquePointerArrays2();
	//TestUniquePointerArrays3();
	//TestUniquePointerArrays4();
	//TestUniquePointerCustomDeleteFunction();
	TestUniquePointerCustomDeleteFunctionForArrays();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------