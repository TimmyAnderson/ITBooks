//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <functional>
#include "MyDebug.h"
#include "CString.h"
#include "CDependentName.h"
#include "CLiteralClass.h"
#include "CStaticPolymorphismClass1.h"
#include "CStaticPolymorphismClass2.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
import MMyModule;
#endif
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
template<typename TType>
void TemplateTestTypenameRelaxation1A(typename TType::TYPE Value)
{
	typename TType::TYPE*										Pointer=new typename TType::TYPE(Value);

	wcout << L"TEMPLATE 1A - POINTER [" << Pointer << L"] VALUE [" << (*Pointer) << L"]." << endl;

	delete(Pointer);
	Pointer=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTestTypenameRelaxation1B(typename TType::TYPE Value)
{
	// !!!!! KEYWORD [typename] NIE JE potrebny pri definicii TYPE v OPERATOR [OPERATOR NEW].
	typename TType::TYPE*										Pointer=new TType::TYPE(Value);

	wcout << L"TEMPLATE 1B - POINTER [" << Pointer << L"] VALUE [" << (*Pointer) << L"]." << endl;

	delete(Pointer);
	Pointer=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTestTypenameRelaxation2A(typename TType::TYPE Value)
{
	using														LocalType=typename TType::TYPE;

	LocalType													LocalValue=Value;

	wcout << L"TEMPLATE 2A - VALUE [" << LocalValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTestTypenameRelaxation2B(typename TType::TYPE Value)
{
	using														LocalType=TType::TYPE;

	// !!!!! KEYWORD [typename] NIE JE potrebny pri definicii TYPE v ALIAS.
	LocalType													LocalValue=Value;

	wcout << L"TEMPLATE 2B - VALUE [" << LocalValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
auto TemplateTestTypenameRelaxation3A(typename TType::TYPE Value) -> typename TType::TYPE
{
	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
// !!!!! KEYWORD [typename] NIE JE potrebny pri definicii TYPE v RETURN TRAILING TYPE.
auto TemplateTestTypenameRelaxation3B(typename TType::TYPE Value) -> TType::TYPE
{
	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2=typename TType1::TYPE>
void TemplateTestTypenameRelaxation4A(typename TType1::TYPE Value)
{
	TType2														CopyValue=Value;

	wcout << L"TEMPLATE 4A - VALUE [" << Value << L"] COPY VALUE [" << CopyValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! KEYWORD [typename] NIE JE potrebny pri definicii TYPE v DEFAULT TEMPLATE ARGUMENT.
template<typename TType1, typename TType2=TType1::TYPE>
void TemplateTestTypenameRelaxation4B(typename TType1::TYPE Value)
{
	TType2														CopyValue=Value;

	wcout << L"TEMPLATE 4B - VALUE [" << Value << L"] COPY VALUE [" << CopyValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTestTypenameRelaxation5A(typename TType::TYPE Value)
{
	typename TType::TYPE										CopyValue=static_cast<typename TType::TYPE>(Value);

	wcout << L"TEMPLATE 5A - VALUE [" << Value << L"] COPY VALUE [" << CopyValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTestTypenameRelaxation5B(typename TType::TYPE Value)
{
	// !!!!! KEYWORD [typename] NIE JE potrebny pri definicii TYPE v OPERATOR [OPERATOR static_cast<>()].
	typename TType::TYPE										CopyValue=static_cast<TType::TYPE>(Value);

	wcout << L"TEMPLATE 5B - VALUE [" << Value << L"] COPY VALUE [" << CopyValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTypenameRelaxation(void)
{
	PrintLineSeparator();

	{
		CDependentName::TYPE									Value=100;

		TemplateTestTypenameRelaxation1A<CDependentName>(Value);
	}

	PrintLineSeparator();

	{
		CDependentName::TYPE									Value=200;

		TemplateTestTypenameRelaxation1B<CDependentName>(Value);
	}

	PrintLineSeparator();

	{
		CDependentName::TYPE									Value=100;

		TemplateTestTypenameRelaxation2A<CDependentName>(Value);
	}

	PrintLineSeparator();

	{
		CDependentName::TYPE									Value=200;

		TemplateTestTypenameRelaxation2B<CDependentName>(Value);
	}

	PrintLineSeparator();

	{
		CDependentName::TYPE									Value=100;
		CDependentName::TYPE									ReturnValue=TemplateTestTypenameRelaxation3A<CDependentName>(Value);

		wcout << L"TEMPLATE 3A - RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CDependentName::TYPE									Value=200;
		CDependentName::TYPE									ReturnValue=TemplateTestTypenameRelaxation3B<CDependentName>(Value);

		wcout << L"TEMPLATE 3B - RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CDependentName::TYPE									Value=100;

		TemplateTestTypenameRelaxation4A<CDependentName>(Value);
	}

	PrintLineSeparator();

	{
		CDependentName::TYPE									Value=200;

		TemplateTestTypenameRelaxation4B<CDependentName>(Value);
	}

	PrintLineSeparator();

	{
		CDependentName::TYPE									Value=100;

		TemplateTestTypenameRelaxation5A<CDependentName>(Value);
	}

	PrintLineSeparator();

	{
		CDependentName::TYPE									Value=200;

		TemplateTestTypenameRelaxation5B<CDependentName>(Value);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Instancia LITERAL CLASS MOZE byt pouzita ako NON-TYPE TEMPLATE PARAMETER.
template<CLiteralClass VALUE>
void TemplateNontypeTemplateParametersLiteralType(void)
{
	wcout << L"NON-TYPE TEMPLATE PARAMETER - LITERAL - VALUE 1 [" << VALUE.GetValue1() << L"] VALUE 2 [" << VALUE.GetValue2() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FLOATING POINT VALUE byt pouzita ako NON-TYPE TEMPLATE PARAMETER.
template<double VALUE>
void TemplateNontypeTemplateParametersFloatingPoint(void)
{
	wcout << L"NON-TYPE TEMPLATE PARAMETER - FLOATING POINT - VALUE [" << VALUE << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestNontypeTemplateParameters(void)
{
	PrintLineSeparator();

	{
		static constexpr CLiteralClass							VALUE(100,222.222);

		// !!!!! Instancia LITERAL CLASS MOZE byt pouzita ako NON-TYPE TEMPLATE PARAMETER.
		TemplateNontypeTemplateParametersLiteralType<VALUE>();
	}

	PrintLineSeparator();

	{
		// !!!!! FLOATING POINT VALUE byt pouzita ako NON-TYPE TEMPLATE PARAMETER.
		TemplateNontypeTemplateParametersFloatingPoint<123.456>();
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
void TestConcepts(void)
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
void TestModules(void)
{
	PrintLineSeparator();

#ifdef _MSC_VER
	{
		MyModuleFunction1();
	}

	PrintLineSeparator();

	{
		MyModuleFunction2();
	}

	PrintLineSeparator();

	{
		MyModuleFunction3();
	}

	PrintLineSeparator();

	{
		CMyModuleClass											Object(100);

		wcout << L"MODULE - VALUE [" << Object.GetValue() << L"]." << endl;
	}
#endif

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTypenameRelaxation();
	//TestNontypeTemplateParameters();
	TestConcepts();
	//TestModules();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------