//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <functional>
#include <vector>
#include <list>
#include "MyDebug.h"
#include "CString.h"
#include "CDynamicPolymorphismBase.h"
#include "CDynamicPolymorphismDerived1.h"
#include "CDynamicPolymorphismDerived2.h"
#include "CStaticPolymorphismClass1.h"
#include "CStaticPolymorphismClass2.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestDynamicPolymorphism(void)
{
	PrintLineSeparator();

	{
		CDynamicPolymorphismDerived1							Object;
		const CDynamicPolymorphismBase&							Reference=Object;

		Reference.Print();
	}

	PrintLineSeparator();

	{
		CDynamicPolymorphismDerived2							Object;
		const CDynamicPolymorphismBase&							Reference=Object;

		Reference.Print();
	}

	PrintLineSeparator();

	{
		CDynamicPolymorphismDerived1							Object1;
		CDynamicPolymorphismDerived2							Object2;
		vector<const CDynamicPolymorphismBase*>					Collection;

		Collection.push_back(&Object1);
		Collection.push_back(&Object2);

		for(const CDynamicPolymorphismBase* Pointer : Collection)
		{
			Pointer->Print();
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
void TemplateStaticPolymorphism1(const vector<TItem>& Collection)
{
	for(TItem Item : Collection)
	{
		Item->Print();
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void TemplateStaticPolymorphism2(TType1 Value1, TType2 Value2)
{
	int															Difference=(Value1.GetValue()-Value2.GetValue());

	wcout << L"DIFFERENCE [" << Difference << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestStaticPolymorphism(void)
{
	PrintLineSeparator();

	{
		CStaticPolymorphismClass1								Object1;
		CStaticPolymorphismClass1								Object2;
		vector<const CStaticPolymorphismClass1*>				Collection;

		Collection.push_back(&Object1);
		Collection.push_back(&Object2);

		TemplateStaticPolymorphism1(Collection);
	}

	PrintLineSeparator();

	{
		CStaticPolymorphismClass2								Object1;
		CStaticPolymorphismClass2								Object2;
		vector<const CStaticPolymorphismClass2*>				Collection;

		Collection.push_back(&Object1);
		Collection.push_back(&Object2);

		TemplateStaticPolymorphism1(Collection);
	}

	PrintLineSeparator();

	{
		CStaticPolymorphismClass1								Object1;
		CStaticPolymorphismClass2								Object2;

		TemplateStaticPolymorphism2(Object1,Object2);
	}

	PrintLineSeparator();

	{
		CStaticPolymorphismClass2								Object1;
		CStaticPolymorphismClass1								Object2;

		TemplateStaticPolymorphism2(Object1,Object2);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONCEPT definuje STATIC INTERFACE.
template<typename TType>
concept ConceptStaticPolymorphismInterface1=requires(TType Object)
{
//----------------------------------------------------------------------------------------------------------------------
	{Object->Print()} -> same_as<void>;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONCEPT definuje STATIC INTERFACE.
template<typename TType>
concept ConceptStaticPolymorphismInterface2=requires(TType Object)
{
//----------------------------------------------------------------------------------------------------------------------
	{Object.GetValue()} -> convertible_to<int>;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
requires ConceptStaticPolymorphismInterface1<TItem>
void TemplateStaticPolymorphismWithConcepts1(const vector<TItem>& Collection)
{
	for(TItem Item : Collection)
	{
		Item->Print();
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
requires ConceptStaticPolymorphismInterface2<TType1> && ConceptStaticPolymorphismInterface2<TType2>
void TemplateStaticPolymorphismWithConcepts2(TType1 Value1, TType2 Value2)
{
	int															Difference=(Value1.GetValue()-Value2.GetValue());

	wcout << L"DIFFERENCE [" << Difference << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestStaticPolymorphismWithConcepts(void)
{
	PrintLineSeparator();

	{
		CStaticPolymorphismClass1								Object1;
		CStaticPolymorphismClass1								Object2;
		vector<const CStaticPolymorphismClass1*>				Collection;

		Collection.push_back(&Object1);
		Collection.push_back(&Object2);

		TemplateStaticPolymorphismWithConcepts1(Collection);
	}

	PrintLineSeparator();

	{
		CStaticPolymorphismClass2								Object1;
		CStaticPolymorphismClass2								Object2;
		vector<const CStaticPolymorphismClass2*>				Collection;

		Collection.push_back(&Object1);
		Collection.push_back(&Object2);

		TemplateStaticPolymorphismWithConcepts1(Collection);
	}

	PrintLineSeparator();

	{
		CStaticPolymorphismClass1								Object1;
		CStaticPolymorphismClass2								Object2;

		TemplateStaticPolymorphismWithConcepts2(Object1,Object2);
	}

	PrintLineSeparator();

	{
		CStaticPolymorphismClass2								Object1;
		CStaticPolymorphismClass1								Object2;

		TemplateStaticPolymorphismWithConcepts2(Object1,Object2);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TIterator>
void TemplateGenericProgrammingPrintMax(TIterator Begin, TIterator End)
{
	TIterator													Iterator=Begin;
	TType														MaximumValue={};
	bool														HasMaximum=false;

	while(Iterator!=End)
	{
		TType													Value=(*Iterator);

		if (HasMaximum==false)
		{
			MaximumValue=Value;

			HasMaximum=true;
		}
		else
		{
			if (MaximumValue<Value)
			{
				MaximumValue=Value;
			}
		}

		++Iterator;
	}

	if (HasMaximum==true)
	{
		wcout << L"MAXIMUM VALUE is VALUE [" << MaximumValue << L"]." << endl;
	}
	else
	{
		wcout << L"COLLECTION is EMPTY." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestGenericProgramming(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection;

		Collection.push_back(200);
		Collection.push_back(300);
		Collection.push_back(400);
		Collection.push_back(100);

		TemplateGenericProgrammingPrintMax<int>(Collection.cbegin(),Collection.cend());
	}

	PrintLineSeparator();

	{
		list<int>												Collection;

		Collection.push_back(200);
		Collection.push_back(300);
		Collection.push_back(400);
		Collection.push_back(100);

		TemplateGenericProgrammingPrintMax<int>(Collection.cbegin(),Collection.cend());
	}

	PrintLineSeparator();

	{
		vector<int>												Collection;

		TemplateGenericProgrammingPrintMax<int>(Collection.cbegin(),Collection.cend());
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestDynamicPolymorphism();
	//TestStaticPolymorphism();
	//TestStaticPolymorphismWithConcepts();
	TestGenericProgramming();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------