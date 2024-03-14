//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <algorithm>
#include "MyDebug.h"
#include "CString.h"
#include "CException.h"
#include "CTypePointer.h"
#include "CTypeNonPointer.h"
#include "SHasDereference.h"
#include "CArchetypeConvertibleToBool1.h"
#include "CArchetypeConvertibleToBool2.h"
#include "CArchetypeEqualityComparable1.h"
#include "CArchetypeEqualityComparable2.h"
#include "CTracerSort.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#pragma warning( disable : 26498 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void LongErrorMessageTemplateLevel4(TType& Value)
{
	// !!! Ak TYPE nie je POINTER, tak COMPILER generuje ERROR.
	*Value=999;

	wcout << L"POINTER was SET." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void LongErrorMessageTemplateLevel3(TType& Value)
{
	LongErrorMessageTemplateLevel4(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void LongErrorMessageTemplateLevel2(typename TType::TYPE Value)
{
	LongErrorMessageTemplateLevel3(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void LongErrorMessageTemplateLevel1(const TType&, typename TType::TYPE DefaultValue)
{
	typename TType::TYPE										Value=DefaultValue;

	LongErrorMessageTemplateLevel2<TType>(Value);
}
//----------------------------------------------------------------------------------------------------------------------
void TestLongErrorMessage(void)
{
	PrintLineSeparator();

	{
		CTypePointer											Object;
		int														Value=100;
		int*													PointerToValue=&Value;

		wcout << L"VALUE [" << Value << L"]." << endl;

		// !!!!! CODE NEGENERUJE COMPILATION ERROR, lebo TYPE [CTypePointer::TYPE] je POINTER TYPE.
		LongErrorMessageTemplateLevel1(Object,PointerToValue);

		wcout << L"VALUE [" << Value << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		CTypeNonPointer											Object;
		int														Value=100;

		wcout << L"VALUE [" << Value << L"]." << endl;

		// !!!!! CODE GENERUJE COMPILATION ERROR, lebo TYPE [CTypeNonPointer::TYPE] NIE je POINTER TYPE.
		LongErrorMessageTemplateLevel1(Object,Value);

		wcout << L"VALUE [" << Value << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ShallowInstantiationIgnore(const TType&)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ShallowInstantiationTemplateLevel4(TType& Value)
{
	// !!! Ak TYPE nie je POINTER, tak COMPILER generuje ERROR.
	*Value=999;

	wcout << L"POINTER was SET." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ShallowInstantiationTemplateLevel3(TType& Value)
{
	ShallowInstantiationTemplateLevel4(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ShallowInstantiationTemplateLevel2(typename TType::TYPE Value)
{
	ShallowInstantiationTemplateLevel3(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ShallowInstantiationTemplateLevel1(const TType&, typename TType::TYPE DefaultValue)
{
	// !!!!! INTERNAL CLASS, ktora vykona CHECK, ci TYPE [TType::TYPE] je mozne DEREFERENCOVAT.
	// !!!!! Kontrola sa robi na NAJVYSSEJ urovni TEMPLATE CHAIN.
	// !!!!! CODE CLASS sa NIKDY NEVOLA. Sluzi IBA na SKORU DIAGNOSTIKU TEMPLATE ERROR.
	class CShallowChecks
	{
		void DereferenceCheck(typename TType::TYPE Value)
		{
			ShallowInstantiationIgnore(*Value);
		}
	};

	typename TType::TYPE										Value=DefaultValue;

	ShallowInstantiationTemplateLevel2<TType>(Value);
}
//----------------------------------------------------------------------------------------------------------------------
void TestShallowInstantiation(void)
{
	PrintLineSeparator();

	{
		CTypePointer											Object;
		int														Value=100;
		int*													PointerToValue=&Value;

		wcout << L"VALUE [" << Value << L"]." << endl;

		// !!!!! CODE NEGENERUJE COMPILATION ERROR, lebo TYPE [CTypePointer::TYPE] je POINTER TYPE.
		ShallowInstantiationTemplateLevel1(Object,PointerToValue);

		wcout << L"VALUE [" << Value << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		CTypeNonPointer											Object;
		int														Value=100;

		wcout << L"VALUE [" << Value << L"]." << endl;

		// !!!!! CODE GENERUJE COMPILATION ERROR, lebo TYPE [CTypeNonPointer::TYPE] NIE je POINTER TYPE.
		ShallowInstantiationTemplateLevel1(Object,Value);

		wcout << L"VALUE [" << Value << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void StaticAssertTemplateLevel4(TType& Value)
{
	// !!!!! STATIC ASSERT zjednodusuje detekciu TEMPLATE ERRORS.
	static_assert(SHasDereference<TType>::VALUE,"TYPE [TType] is NOT DEREFENCEABLE.");

	// !!! Ak TYPE nie je POINTER, tak COMPILER generuje ERROR.
	*Value=999;

	wcout << L"POINTER was SET." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void StaticAssertTemplateLevel3(TType& Value)
{
	StaticAssertTemplateLevel4(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void StaticAssertTemplateLevel2(typename TType::TYPE Value)
{
	StaticAssertTemplateLevel3(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void StaticAssertTemplateLevel1(const TType&, typename TType::TYPE DefaultValue)
{
	typename TType::TYPE										Value=DefaultValue;

	StaticAssertTemplateLevel2<TType>(Value);
}
//----------------------------------------------------------------------------------------------------------------------
void TestStaticAssert(void)
{
	PrintLineSeparator();

	{
		CTypePointer											Object;
		int														Value=100;
		int*													PointerToValue=&Value;

		wcout << L"VALUE [" << Value << L"]." << endl;

		// !!!!! CODE NEGENERUJE COMPILATION ERROR, lebo TYPE [CTypePointer::TYPE] je POINTER TYPE.
		StaticAssertTemplateLevel1(Object,PointerToValue);

		wcout << L"VALUE [" << Value << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		CTypeNonPointer											Object;
		int														Value=100;

		wcout << L"VALUE [" << Value << L"]." << endl;

		// !!!!! CODE GENERUJE COMPILATION ERROR, lebo TYPE [CTypeNonPointer::TYPE] NIE je POINTER TYPE.
		StaticAssertTemplateLevel1(Object,Value);

		wcout << L"VALUE [" << Value << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
size_t AchertypesTemplateToTest1(const TType* Array, size_t Size, const TType& Value)
{
	size_t														Index=0;

	// !!! Pouziva sa OPERATOR [OPERATOR!=].
	while(Index!=Size && Array[Index]!=Value)
	{
		++Index;
	}

	return(Index);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
size_t AchertypesTemplateToTest2(const TType* Array, size_t Size, const TType& Value)
{
	size_t														Index=0;

	// !!! Pouziva sa OPERATOR [OPERATOR==] a na vysledok sa aplikuje OPERATOR [OPERATOR!].
	while(Index!=Size && !(Array[Index]==Value))
	{
		++Index;
	}

	return(Index);
}
//----------------------------------------------------------------------------------------------------------------------
void TestAchertypes(void)
{
	PrintLineSeparator();

	{
		int														Array[]={2,5,3,7,4,8};
		int														Value=5;
		
		constexpr size_t										SIZE=(sizeof(Array)/sizeof(Array[0]));

		size_t													Index=AchertypesTemplateToTest1(Array,SIZE,Value);

		wcout << L"TEMPLATE TO TEST 1 - VALUE [" << Value << L"] - INDEX [" << Index << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Array[]={2,5,3,7,4,8};
		int														Value=5;
		
		constexpr size_t										SIZE=(sizeof(Array)/sizeof(Array[0]));

		size_t													Index=AchertypesTemplateToTest2(Array,SIZE,Value);

		wcout << L"TEMPLATE TO TEST 2 - VALUE [" << Value << L"] - INDEX [" << Index << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		CArchetypeEqualityComparable1							Array[]={CArchetypeEqualityComparable1{},CArchetypeEqualityComparable1{},CArchetypeEqualityComparable1{},CArchetypeEqualityComparable1{},CArchetypeEqualityComparable1{},CArchetypeEqualityComparable1{}};
		CArchetypeEqualityComparable1							Value{};
		
		constexpr size_t										SIZE=(sizeof(Array)/sizeof(Array[0]));

		// !!!!! COMPILER hodi ERROR, pretoze ACHERTYPE CLASS [CArchetypeEqualityComparable1] NEMA definovany OPERATOR [OPERATOR==], ktory TEMPLATE FUNCTION [size_t AchertypesTemplateToTest1(const TType* Array, size_t Size, const TType& Value)] vyzaduje.
		size_t													Index=AchertypesTemplateToTest1(Array,SIZE,Value);

		wcout << L"TEMPLATE TO TEST 1 - INDEX [" << Index << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		CArchetypeEqualityComparable1							Array[]={CArchetypeEqualityComparable1{},CArchetypeEqualityComparable1{},CArchetypeEqualityComparable1{},CArchetypeEqualityComparable1{},CArchetypeEqualityComparable1{},CArchetypeEqualityComparable1{}};
		CArchetypeEqualityComparable1							Value{};
		
		constexpr size_t										SIZE=(sizeof(Array)/sizeof(Array[0]));

		// !!!!! TEST sice prejde, ale je NEDOSTATOCNY, pretoze ACHERTYPE [CArchetypeEqualityComparable1] nevykonava test ci na RETURN VALUE TYPE OPERATOR [OPERATOR!=], ktory je TYPE [CArchetypeConvertibleToBool1] je mozne aplikovat OPERATOR [OPERATOR!]. TEMPLATE FUNCTION [size_t AchertypesTemplateToTest2(const TType* Array, size_t Size, const TType& Value)] pritom pouzitie OPERATOR [OPERATOR!] VYZADUJE.
		size_t													Index=AchertypesTemplateToTest2(Array,SIZE,Value);

		wcout << L"TEMPLATE TO TEST 2 - INDEX [" << Index << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		CArchetypeEqualityComparable2							Array[]={CArchetypeEqualityComparable2{},CArchetypeEqualityComparable2{},CArchetypeEqualityComparable2{},CArchetypeEqualityComparable2{},CArchetypeEqualityComparable2{},CArchetypeEqualityComparable2{}};
		CArchetypeEqualityComparable2							Value{};
		
		constexpr size_t										SIZE=(sizeof(Array)/sizeof(Array[0]));

		// !!!!! TEST spravne NEPREJDE a COMPILER hodi ERROR, pretoze ACHERTYPE [CArchetypeEqualityComparable2] vykonava test ci na RETURN VALUE TYPE OPERATOR [OPERATOR!=], ktory je TYPE [CArchetypeConvertibleToBool2] je mozne aplikovat OPERATOR [OPERATOR!], ktory vyzaduje TEMPLATE FUNCTION [size_t AchertypesTemplateToTest2(const TType* Array, size_t Size, const TType& Value)]. A kedze OPERATOR [OPERATOR!=] je pre TYPE [CArchetypeConvertibleToBool2] DELETED, tak COMPILER spravne hodi ERROR.
		size_t													Index=AchertypesTemplateToTest2(Array,SIZE,Value);

		wcout << L"TEMPLATE TO TEST 2 - INDEX [" << Index << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTracers(void)
{
	PrintLineSeparator();

	{
		CTracerSort::Reset();

		CTracerSort												Array[]={3,4,2,0,1};

		constexpr size_t										SIZE=(sizeof(Array)/sizeof(Array[0]));

		wcout << L"UNSORTED VALUES:" << endl;

		for(size_t Index=0;Index<SIZE;++Index)
		{
			wcout << L"\tINDEX [" << Index << L"] - VALUE [" << Array[Index].GetValue() << L"]." << endl;
		}

		sort<>(&Array[0],(&Array[SIZE-1]+1));

		wcout << L"SORTED VALUES:" << endl;

		for(size_t Index=0;Index<SIZE;++Index)
		{
			wcout << L"\tINDEX [" << Index << L"] - VALUE [" << Array[Index].GetValue() << L"]." << endl;
		}

		wcout << L"!!!!! SORT [" << SIZE << L"] - CREATED [" << CTracerSort::GetCreations() << L"] DESTROYED [" << CTracerSort::GetDestructions() << L"] ASSIGNED [" << CTracerSort::GetAssignments() << L"] COMPARED [" << CTracerSort::GetComparisons() << L"] MAX LIVE [" << CTracerSort::GetMaxLive() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTracerSort::Reset();

		CTracerSort												Array[]={7,3,5,6,4,2,0,1,9,8};

		constexpr size_t										SIZE=(sizeof(Array)/sizeof(Array[0]));

		wcout << L"UNSORTED VALUES:" << endl;

		for(size_t Index=0;Index<SIZE;++Index)
		{
			wcout << L"\tINDEX [" << Index << L"] - VALUE [" << Array[Index].GetValue() << L"]." << endl;
		}

		sort<>(&Array[0],(&Array[SIZE-1]+1));

		wcout << L"SORTED VALUES:" << endl;

		for(size_t Index=0;Index<SIZE;++Index)
		{
			wcout << L"\tINDEX [" << Index << L"] - VALUE [" << Array[Index].GetValue() << L"]." << endl;
		}

		wcout << L"!!!!! SORT [" << SIZE << L"] - CREATED [" << CTracerSort::GetCreations() << L"] DESTROYED [" << CTracerSort::GetDestructions() << L"] ASSIGNED [" << CTracerSort::GetAssignments() << L"] COMPARED [" << CTracerSort::GetComparisons() << L"] MAX LIVE [" << CTracerSort::GetMaxLive() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestLongErrorMessage();
	//TestShallowInstantiation();
	//TestStaticAssert();
	//TestAchertypes();
	TestTracers();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------