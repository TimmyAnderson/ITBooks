//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include "MyDebug.h"
#include "CBase.h"
#include "CDerived1.h"
#include "CDerived2.h"
#include "CCollectionTemplate.h"
#include "CBaseForArrayTest.h"
#include "CDerivedForArrayTest.h"
#include "CWrapper.h"
#include "CBase1.h"
#include "CBase2.h"
#include "CDerivedWithTypeParameter.h"
#include "CList.h"
#include "CListItem.h"
#include "CListItemWithValue.h"
#include "CTemplateList.h"
#include "CTemplateListItem.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
void TestTemplateWithClass(void)
{
	PrintLineSeparator();

	CCollectionTemplate<CBase*>									Collection;

	Collection.AddItem(new CDerived1(L"DERIVED 1 - INSTANCE 1"));
	Collection.AddItem(new CDerived1(L"DERIVED 1 - INSTANCE 2"));
	Collection.AddItem(new CDerived2(L"DERIVED 2 - INSTANCE 1"));
	Collection.AddItem(new CDerived2(L"DERIVED 2 - INSTANCE 2"));

	for (size_t Index=0;Index<Collection.GetNumberOfItems();Index++)
	{
		Collection[Index]->VirtualMethod();
	}

	PrintLineSeparator();

	CBase*														Item=Collection.RemoveItem(2);

	delete(Item);
	Item=nullptr;

	for (size_t Index=0;Index<Collection.GetNumberOfItems();Index++)
	{
		Collection[Index]->VirtualMethod();
	}

	while(Collection.GetNumberOfItems()>0)
	{
		CBase*													Item=Collection.RemoveItem(0);

		delete(Item);
		Item=nullptr;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PrintVector(vector<CBase*>& Vector)
{
	for(CBase* Base : Vector)
	{
		Base->VirtualMethod();
	}
}
//-----------------------------------------------------------------------------
void TestVectorConvesion(void)
{
	PrintLineSeparator();

	vector<CDerived1*>											Vector{new CDerived1(L"1"),new CDerived1(L"2"),new CDerived1(L"3")};

	for(CDerived1* Derived : Vector)
	{
		Derived->VirtualMethod();
	}

	// !!! C++ NEUMOZNUJE implicitnu konverziu COLLECTIONS obsahujucich DERIVED CLASSES na COLLECTIONS obsahujuce BASE CLASSES. Ak by to umoznoval, potom by bolo mozne do 'Vector' ulozit napriklad instanciu [CDerived2] cim by sa narusila garancia, ze 'Vector' obsahuje iba instancie CLASS [CDerived1].
	//PrintVector(Vector);

	for(CDerived1* Derived : Vector)
	{
		delete(Derived);
	}

	Vector.clear();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PrintCustomVector(CCollectionTemplate<CBase*> Vector)
{
	for(CBase* Base : Vector)
	{
		Base->VirtualMethod();
	}
}
//-----------------------------------------------------------------------------
void TestCustomVectorConvesion(void)
{
	PrintLineSeparator();

	CCollectionTemplate<CDerived1*>								Vector{new CDerived1(L"1"),new CDerived1(L"2"),new CDerived1(L"3")};

	for(CDerived1* Derived : Vector)
	{
		Derived->VirtualMethod();
	}

	// !!! Kedze C++ NEUMOZNUJE konverziu z CLASS [CCollectionTemplate<CDerived1*>] na CLASS [CCollectionTemplate<CBase1*>] pouzije sa CUSTOM CONVERSION OPERATOR, ktory CLASS [CCollectionTemplate<>] definuje.
	PrintCustomVector(Vector);

	for(CDerived1* Derived : Vector)
	{
		delete(Derived);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PrintValue(CBase* Value)
{
	Value->VirtualMethod();
}
//-----------------------------------------------------------------------------
void SetValue(CBase** Value)
{
	delete(*Value);

	*Value=new CDerived2(L"DERIVED 2");
}
//-----------------------------------------------------------------------------
void TestPointerToPointerConvesion(void)
{
	PrintLineSeparator();

	CDerived1*													Derived1=new CDerived1(L"DERIVED 1 INSTANCE 1");
	CBase*														Derived2=new CDerived1(L"DERIVED 1 INSTANCE 2");

	// Takuto IMPLICITNU KONVERZIU C++ povoluje.
	PrintValue(Derived1);
	PrintValue(Derived2);

	// Takuto IMPLICITNU KONVERZIU C++ povoluje.
	SetValue(&Derived2);

	// !!! Tuto konverziu C++ NEPOVOLI, pretoze FUNCTION SetValue() ulozi do VARIABLE 'Derived1' instanciu CLASS [CDerived2] cim by sa narusila garancia, ze VARIABLE 'Derived1' mozne obsahovat iba instancie CLASS [CDerived2].
	//SetValue(&Derived1);

	PrintValue(Derived1);
	PrintValue(Derived2);

	delete(Derived1);
	Derived1=nullptr;

	delete(Derived2);
	Derived2=nullptr;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PrintDerivedArray(CDerivedForArrayTest* Array, size_t Length)
{
	for(size_t Index=0;Index<Length;Index++)
	{
		Array[Index].VirtualMethod();
	}
}
//-----------------------------------------------------------------------------
void PrintBaseArray(CBaseForArrayTest* Array, size_t Length)
{
	for(size_t Index=0;Index<Length;Index++)
	{
		Array[Index].VirtualMethod();
	}
}
//-----------------------------------------------------------------------------
void PrintBaseArrayAsPointer(CBaseForArrayTest** Array, size_t Length)
{
	for(size_t Index=0;Index<Length;Index++)
	{
		Array[Index]->VirtualMethod();
	}
}
//-----------------------------------------------------------------------------
void TestClassArray(void)
{
	PrintLineSeparator();

	CDerivedForArrayTest										Array[]{CDerivedForArrayTest(L"1",L"11",L"111"),CDerivedForArrayTest(L"2",L"22",L"222"),CDerivedForArrayTest(L"3",L"33",L"333")};

	// !!! C++ UMOZNI IMPLICIT CONVERSION. Prenos ARRAY NIE JE PROBLEMATICKY, pretoze FUNCTION PrintDerivedArray() pouziva ako PARAMETER ARRAY obsahujuci ITEMS TYPE [CDerivedForArrayTest], ktore maju ROVNAKY SIZEOF() ako ITEMS ARRAY ulozeneho vo VARIABLE 'Array'.
	PrintDerivedArray(Array,CountOf(Array));

	// !!!!! C++ UMOZNI IMPLICIT CONVERSION.
	// !!!!! Volanie FUNCTION vsak sposobi PAD PROGRAMU.
	// !!!!! Dovodom je, ze SIZEOF(CBaseForArrayTest)<SIZEOF(CDerivedForArrayTest). C++ teda bude ocakavat, ze v MEMORY su ulozene za sebou INSTANCIE CLASS [CBaseForArrayTest], ktore su KRATSIE ako SKUTOCNE PRENESENE instancie CLASS [CDerivedForArrayTest].
	//PrintBaseArray(Array,CountOf(Array));

	PrintLineSeparator();

	CDerivedForArrayTest*										ArrayOfPointers[]{&Array[0],&Array[1],&Array[2]};

	// !!!!! Tu problem NENASTANE, pretoze sa prenasa ARRAY obsahujucu ITEMS TYPU [CDerivedForArrayTest*] a SIZEOF(CBaseForArrayTest*)==SIZEOF(CDerivedForArrayTest*). To znaci, ze NEDOJDE k CHYBE pri pristupe k MEMORY.
	PrintBaseArrayAsPointer((CBaseForArrayTest**) ArrayOfPointers,CountOf(ArrayOfPointers));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTemplateItselfDerivation(void)
{
	PrintLineSeparator();

	wstring														Text=L"Timmy Anderson";

	CWrapper<wstring>											Wrapper1(Text);
	CWrapper<void*>												Wrapper2(&Text);
	CWrapper<wstring*>											Wrapper3(&Text);

	Wrapper1.GetValue();

	PrintLineSeparator();

	Wrapper2.GetValue();

	PrintLineSeparator();

	Wrapper3.GetValue();

	PrintLineSeparator();

	Wrapper3.SpecialIsNULL();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTemplateDerivationFromTypeParameter(void)
{
	PrintLineSeparator();

	// TYPE dedi z TYPE [CBase1].
	CDerivedWithTypeParameter<CBase1>							Type1;

	Type1.VirtualMethod();
	Type1.DoSomething();

	PrintLineSeparator();

	// TYPE dedi z TYPE [CBase2].
	CDerivedWithTypeParameter<CBase2>							Type2;

	Type2.VirtualMethod();
	Type2.DoSomething();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PrintItem(CListItemWithValue<int>* Item)
{
	wprintf_s(L"ITEM [%d] !\n",Item->GetValue());
}
//-----------------------------------------------------------------------------
void TestListAsTemplate1(void)
{
	PrintLineSeparator();

	CList<int>													List;
	CListItemWithValue<int>										Value1(1);
	CListItemWithValue<int>										Value2(2);
	CListItemWithValue<int>										Value3(3);
	CListItemWithValue<int>										Value4(4);

	List.Add(&Value1);
	List.Add(&Value2);
	List.Add(&Value3);
	List.Add(&Value4);

	List.Iterate(PrintItem);

	wprintf_s(L"FOUND VALUE [%d] !\n",List.GetFirstItemByValue(3)->GetValue());

	PrintLineSeparator();

	List.Remove(&Value4);
	List.Iterate(PrintItem);

	PrintLineSeparator();

	List.Remove(&Value2);
	List.Iterate(PrintItem);

	PrintLineSeparator();

	List.Remove(&Value3);
	List.Iterate(PrintItem);

	PrintLineSeparator();

	List.Remove(&Value1);
	List.Iterate(PrintItem);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PrintItem(CTemplateListItem<int>* Item)
{
	wprintf_s(L"ITEM [%d] !\n",Item->GetValue());
}
//-----------------------------------------------------------------------------
void TestListAsTemplate2(void)
{
	PrintLineSeparator();

	CTemplateList<int>											List;
	CTemplateListItem<int>										Value1(1);
	CTemplateListItem<int>										Value2(2);
	CTemplateListItem<int>										Value3(3);
	CTemplateListItem<int>										Value4(4);

	List.Add(&Value1);
	List.Add(&Value2);
	List.Add(&Value3);
	List.Add(&Value4);

	List.Iterate(PrintItem);

	wprintf_s(L"FOUND VALUE [%d] !\n",List.GetFirstItemByValue(3)->GetValue());

	PrintLineSeparator();

	List.Remove(&Value4);
	List.Iterate(PrintItem);

	PrintLineSeparator();

	List.Remove(&Value2);
	List.Iterate(PrintItem);

	PrintLineSeparator();

	List.Remove(&Value3);
	List.Iterate(PrintItem);

	PrintLineSeparator();

	List.Remove(&Value1);
	List.Iterate(PrintItem);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTemplateWithClass();
	//TestVectorConvesion();
	//TestCustomVectorConvesion();
	//TestPointerToPointerConvesion();
	//TestClassArray();
	//TestTemplateItselfDerivation();
	//TestTemplateDerivationFromTypeParameter();
	//TestListAsTemplate1();
	TestListAsTemplate2();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------